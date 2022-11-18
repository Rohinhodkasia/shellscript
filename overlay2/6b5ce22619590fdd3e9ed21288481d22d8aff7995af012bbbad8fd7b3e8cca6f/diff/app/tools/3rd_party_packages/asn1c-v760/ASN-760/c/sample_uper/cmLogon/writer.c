/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "ACSE-1.h"
#include "CMMessageSetVersion1.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxMemLeakCheck.h"

#define MAXMSGLEN 1024

static ASN1OBJID applCtxtNameOID = {
   5,
   { 1, 3, 27, 3, 1 }
} ;

static ASN1OBJID callingAPTitleOID = {
   6,
   { 1, 3, 27, 1, 500, 0 }
} ;

int main (int argc, char** argv)
{
   ACSE_apdu    acse;
   AARQ_apdu    aarq;
   AP_title_form2 ap_title_form2;
   CMAircraftMessage cmAircraftMessage;
   CMLogonRequest cmLogonRequest;
   External     externalArray[1];
   ASN1DynBitStr64 externalData;
   OSCTXT	ctxt, ctxt2;
   OSOCTET	msgbuf[MAXMSGLEN], msgbuf2[MAXMSGLEN], *msgptr;
   const char*  filename = "message.dat";
   int		i, len, stat;
   OSBOOL       trace = TRUE, verbose = FALSE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   if (rtInitContext (&ctxt) != 0) return -1;

   rtxSetDiag (&ctxt, verbose);

   /* Populate CMLogonRequest structure */

   asn1Init_CMLogonRequest (&cmLogonRequest);
   cmLogonRequest.aircraftFlightIdentification = "UA901";

   OSCRTLMEMCPY ((void*)cmLogonRequest.cMLongTSAP.rDP, "AB901", 5);

   OSCRTLMEMCPY ((void*)cmLogonRequest.cMLongTSAP.shortTsap.locSysNselTsel.data,
                 "4440900901", 10);

   cmLogonRequest.cMLongTSAP.shortTsap.locSysNselTsel.numocts = 10;

   cmLogonRequest.m.facilityDesignationPresent = 1;
   cmLogonRequest.facilityDesignation = "KIADIZDS";

   /* Plug structure into CMAircraftMessage variable */

   cmAircraftMessage.t = T_CMAircraftMessage_cmLogonRequest;
   cmAircraftMessage.u.cmLogonRequest = &cmLogonRequest;

   /* Encode CMAircraftMessage */

   pu_setBuffer (&ctxt, msgbuf, sizeof (msgbuf), /* aligned */ FALSE);
   pu_setTrace (&ctxt, trace);

   stat = asn1PE_CMAircraftMessage (&ctxt, &cmAircraftMessage);

   if (stat == 0) {
      if (trace) {
         pu_hexdump (&ctxt);
         pu_bindump (&ctxt, "cmAircraftMessage");
      }
   }
   else {
      rtxErrPrint (&ctxt);
      exit (0);
   }
  
   msgptr = pe_GetMsgPtr (&ctxt, &len);

   /* Populate AARQ PDU structure */

   asn1Init_AARQ_apdu (&aarq);
   rtSetOID (&aarq.application_context_name, &applCtxtNameOID);

   rtSetOID (&ap_title_form2, &callingAPTitleOID);
   aarq.m.calling_AP_titlePresent = 1;
   aarq.calling_AP_title.t = T_AP_title_ap_title_form2;
   aarq.calling_AP_title.u.ap_title_form2 = &ap_title_form2;

   aarq.m.calling_AE_qualifierPresent = 1;
   aarq.calling_AE_qualifier.t = T_AE_qualifier_ae_qualifier_form2;
   aarq.calling_AE_qualifier.u.ae_qualifier_form2 = 1;

   /* Populate external type with info in the encoded request and plug  */
   /* into the structure..                                              */

   externalData.numbits = pe_GetMsgBitCnt (&ctxt);
   externalData.data = msgptr;

   asn1Init_External (&externalArray[0]);
   externalArray[0].encoding.t = T_External_encoding_arbitrary;
   externalArray[0].encoding.u.arbitrary = &externalData;

   aarq.m.user_informationPresent = 1;
   rtxDListInit (&aarq.user_information);
   rtxDListAppend (&ctxt, &aarq.user_information, &externalArray[0]);

   acse.t = T_ACSE_apdu_aarq;
   acse.u.aarq = &aarq;

   /* Encode the request PDU */

   if (trace) {
      printf ("\n");
      printf ("Encoding ACSE AARQ APDU..\n");
      printf ("\n");
   }

   rtInitContext (&ctxt2);
   pu_setBuffer (&ctxt2, msgbuf2, sizeof (msgbuf2), /* aligned */ FALSE);
   pu_setTrace (&ctxt2, trace);

   stat = asn1PE_ACSE_apdu (&ctxt2, &acse);

   if (stat == 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         pu_hexdump (&ctxt2);
         printf ("Binary dump:\n");
         pu_bindump (&ctxt2, "acse");
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt2);
      return -1;
   }
  
   msgptr = pe_GetMsgPtr (&ctxt2, &len);

   /* Write the encoded message out to the output file */

   stat = rtxFileWriteBinary(filename, msgptr, len);
   if (0 != stat) {
      printf ("Error opening %s for write access\n", filename);
      return stat;
   }
      
   if (trace)
      printf ("Wrote %d bytes to file %s..\n", len, filename);

   rtFreeContext (&ctxt);
   rtFreeContext (&ctxt2);

   return 0;

}
