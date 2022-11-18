/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "ExtChoice.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 4096

int main (int argc, char** argv)
{
   AliasAddressList msgData;
   AliasAddress_transportID transId;
   AliasAddress* pAliasAddress;
   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN];
   int		i, stat;
   const char* filename = "message.xml";
   OSBOOL       verbose = FALSE, trace = TRUE, cxer = FALSE;
   FILE *fp;
   ASN1OpenType ot;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else if (!strcmp (argv[i], "-cxer")) cxer = TRUE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>] [ -cxer ]\n");
            printf ("   -cxer          use canonical XER rules (CXER)\n");
            printf ("   -v             verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace       do not display trace info\n");
            return 0;
         }
      }
   }

   /* Init */

   if (rtXmlInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);

   rtXmlSetEncBufPtr(&ctxt, msgbuf, sizeof(msgbuf));
   if (cxer) rtxCtxtSetFlag(&ctxt, OSXMLC14N);

   /* Populate structure of generated type */

   rtxDListInit (&msgData);

   pAliasAddress = rtxMemAllocType (&ctxt, AliasAddress); 
   pAliasAddress->t = T_AliasAddress_e164;
   pAliasAddress->u.e164 = "#39047752,937";
   rtxDListAppend (&ctxt, &msgData, pAliasAddress);

   pAliasAddress = rtxMemAllocType (&ctxt, AliasAddress); 
   pAliasAddress->t = T_AliasAddress_h323_ID;
   rtCToBMPString (&ctxt, 
                   "TESTSTRING", &pAliasAddress->u.h323_ID, 0);
   rtxDListAppend (&ctxt, &msgData, pAliasAddress);

   pAliasAddress = rtxMemAllocType (&ctxt, AliasAddress); 
   pAliasAddress->t = T_AliasAddress_url_ID;
   pAliasAddress->u.url_ID = "http://www.obj-sys.com";
   rtxDListAppend (&ctxt, &msgData, pAliasAddress);

   pAliasAddress = rtxMemAllocType (&ctxt, AliasAddress); 
   pAliasAddress->t = T_AliasAddress_transportID;
   transId.transportAddress = "Truck";
   transId.aInt = 111;
   pAliasAddress->u.transportID = &transId;
   rtxDListAppend (&ctxt, &msgData, pAliasAddress);

   pAliasAddress = rtxMemAllocType (&ctxt, AliasAddress); 
   pAliasAddress->t = T_AliasAddress_email_ID;
   pAliasAddress->u.email_ID = "objective@obj-sys.com";
   rtxDListAppend (&ctxt, &msgData, pAliasAddress);

   pAliasAddress = rtxMemAllocType (&ctxt, AliasAddress); 
   pAliasAddress->t = T_AliasAddress_partyNumber;
   pAliasAddress->u.partyNumber = 555;
   rtxDListAppend (&ctxt, &msgData, pAliasAddress);

   pAliasAddress = rtxMemAllocType (&ctxt, AliasAddress); 
   pAliasAddress->t = T_AliasAddress_extElem1;
   ot.data = 
      (OSOCTET*)"<extension>This is an extension element</extension>";
   ot.numocts = strlen ((const char*)ot.data);
   pAliasAddress->u.extElem1 = &ot;
   rtxDListAppend (&ctxt, &msgData, pAliasAddress);

   /* Encode */

   stat = XmlEnc_AliasAddressList_PDU (&ctxt, &msgData);

   if (stat == 0) {
      if (trace) {
         printf ("encoded XML message:\n");
         printf ((char*)msgbuf);
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      exit (-1);
   }
  
   /* Write the encoded message out to the output file */

   if (fp = fopen (filename, "w")) {
      fputs ((char*)msgbuf, fp);
      fclose (fp);
   }
   else {
      printf ("Error opening %s for write access\n", filename);
      return -1;
   }
   rtFreeContext (&ctxt);
   return 0;
}

