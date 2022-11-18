// This test driver program encodes a data record and writes the encoded 
// result to an output file..

#include <stdio.h>
#include <stdlib.h>
#include "ACSE-1.h"
#include "CMMessageSetVersion1.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxFile.h"

#define MAXMSGLEN 1024

static ASN1OBJID applCtxtNameOID = {
   5,
   { 1, 3, 27, 3, 1 }
} ;

static ASN1OBJID callingAPTitleOID = {
   6,
   { 1, 3, 27, 1, 500, 0 }
} ;

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSOCTET*   msgptr;
   const OSOCTET* msgptr2;
   ASN1T_AP_title_form2 ap_title_form2;
   OSBOOL       verbose = FALSE, trace = TRUE;
   const char*  filename = "message.dat";
   int          i, stat;
   OSSIZE       len;

   // Process command line arguments

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [-v][-o <filename>][-notrace]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Populate CMLogonRequest structure

   ASN1T_CMLogonRequest cmLogonRequest;
   cmLogonRequest.aircraftFlightIdentification = "UA901";

   OSCRTLMEMCPY (cmLogonRequest.cMLongTSAP.rDP, "AB901", 5);
   cmLogonRequest.cMLongTSAP.shortTsap.locSysNselTsel = "4440900901";
   cmLogonRequest.cMLongTSAP.shortTsap.locSysNselTsel.numocts = 10;

   cmLogonRequest.m.facilityDesignationPresent = 1;
   cmLogonRequest.facilityDesignation = "KIADIZDS";

   // Plug structure into CMAircraftMessage variable

   ASN1T_CMAircraftMessage cmMsgData;
   cmMsgData.t = T_CMAircraftMessage_cmLogonRequest;
   cmMsgData.u.cmLogonRequest = &cmLogonRequest;

   // Encode CMAircraftMessage

   ASN1PEREncodeBuffer cmEncodeBuffer (/*aligned*/FALSE);
   ASN1C_CMAircraftMessage cmAircraftMessage (cmEncodeBuffer, cmMsgData);
   cmEncodeBuffer.SetTrace (trace);  // enable bin trace

   stat = cmAircraftMessage.Encode ();

   if (stat == 0) {
      if (trace) {
         cmEncodeBuffer.HexDump ();
         cmEncodeBuffer.BinDump ("cmAircraftMessage");
      }
      msgptr = cmEncodeBuffer.getMsgCopy ();
   }
   else {
      cmEncodeBuffer.printErrorInfo ();
      return stat;
   }
  
   // Populate AARQ PDU structure

   ASN1T_AARQ_apdu aarq;

   aarq.application_context_name = applCtxtNameOID;
   ap_title_form2 = callingAPTitleOID;
   aarq.m.calling_AP_titlePresent = 1;
   aarq.calling_AP_title.t = T_AP_title_ap_title_form2;
   aarq.calling_AP_title.u.ap_title_form2 = &ap_title_form2;

   aarq.m.calling_AE_qualifierPresent = 1;
   aarq.calling_AE_qualifier.t = T_AE_qualifier_ae_qualifier_form2;
   aarq.calling_AE_qualifier.u.ae_qualifier_form2 = 1;

   // Populate external type with info in the encoded request and plug 
   // into the structure..

   ASN1TDynBitStr64 externalData;
   externalData.numbits = cmEncodeBuffer.GetMsgBitCnt ();
   externalData.data = msgptr;

   ASN1T_External externalArray[1];
   externalArray[0].encoding.t = T_External_encoding_arbitrary;
   externalArray[0].encoding.u.arbitrary = &externalData;

   aarq.m.user_informationPresent = 1;
   ASN1C_Association_information uiList(cmEncodeBuffer, aarq.user_information);
   uiList.append (&externalArray[0]);

   // Populate the ACSE structure and encode

   ASN1T_ACSE_apdu acse;
   acse.t = T_ACSE_apdu_aarq;
   acse.u.aarq = &aarq;

   if (trace) {
      printf ("\n");
      printf ("Encoding ACSE AARQ APDU..\n");
      printf ("\n");
   }

   ASN1PEREncodeBuffer acseEncodeBuffer (/*aligned*/FALSE);
   ASN1C_ACSE_apdu acsePDU (acseEncodeBuffer, acse);
   acseEncodeBuffer.SetTrace (trace);  // enable bin trace

   stat = acsePDU.Encode ();

   delete [] msgptr;

   if (stat == 0) {
      if (trace) {
         acseEncodeBuffer.HexDump ();
         acseEncodeBuffer.BinDump ("acse");
      }
      msgptr2 = acseEncodeBuffer.getMsgPtr ();
      len = acseEncodeBuffer.getMsgLen ();
   }
   else {
      acseEncodeBuffer.printErrorInfo ();
      return -1;
   }
  
   // Write the encoded message out to the output file

   stat = rtxFileWriteBinary (filename, msgptr2, len);
   if (stat < 0) {
      printf ("Error writing to file %s, status = %d\n", filename, stat);
   }

   return stat;
}
