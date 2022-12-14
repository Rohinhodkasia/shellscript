/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.0A, Date: 21-Jun-2006.
 */
#include "ExtChoice.h"
#include "rtxsrc/rtxCommon.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
   AliasAddressList msgData;
   AliasAddress_transportID transId;
   AliasAddress* pAliasAddress;
   OSUNICHAR    unicodeStr[100];
   OSCTXT       ctxt;
   OSBOOL       trace = TRUE, verbose = FALSE;
   const char*  filename = "message.xml";
   int          i, stat;

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>] [ -cxer ]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Init context */

   stat = rtXmlInitContext (&ctxt);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Populate structure of generated type */

   rtxDListInit (&msgData);

   pAliasAddress = rtxMemAllocType (&ctxt, AliasAddress); 
   pAliasAddress->t = T_AliasAddress_e164;
   pAliasAddress->u.e164 = OSUTF8("#39047752,937");
   rtxDListAppend (&ctxt, &msgData, pAliasAddress);

   pAliasAddress = rtxMemAllocType (&ctxt, AliasAddress); 
   pAliasAddress->t = T_AliasAddress_h323_ID;
   pAliasAddress->u.h323_ID.nchars = 
      rtxUTF8ToUnicode (&ctxt, OSUTF8("TESTSTRING"), 
                        unicodeStr, sizeof(unicodeStr));
   pAliasAddress->u.h323_ID.data = unicodeStr;
   rtxDListAppend (&ctxt, &msgData, pAliasAddress);

   pAliasAddress = rtxMemAllocType (&ctxt, AliasAddress); 
   pAliasAddress->t = T_AliasAddress_url_ID;
   pAliasAddress->u.url_ID = OSUTF8("http://www.obj-sys.com");
   rtxDListAppend (&ctxt, &msgData, pAliasAddress);

   pAliasAddress = rtxMemAllocType (&ctxt, AliasAddress); 
   pAliasAddress->t = T_AliasAddress_transportID;
   transId.transportAddress = OSUTF8("Truck");
   transId.aInt = 111;
   pAliasAddress->u.transportID = &transId;
   rtxDListAppend (&ctxt, &msgData, pAliasAddress);

   pAliasAddress = rtxMemAllocType (&ctxt, AliasAddress); 
   pAliasAddress->t = T_AliasAddress_email_ID;
   pAliasAddress->u.email_ID = OSUTF8("objective@obj-sys.com");
   rtxDListAppend (&ctxt, &msgData, pAliasAddress);

   pAliasAddress = rtxMemAllocType (&ctxt, AliasAddress); 
   pAliasAddress->t = T_AliasAddress_partyNumber;
   pAliasAddress->u.partyNumber = 555;
   rtxDListAppend (&ctxt, &msgData, pAliasAddress);

   /* Encode */

   stat = rtXmlSetEncBufPtr (&ctxt, 0, 0);

   if (stat == 0)
      stat = XmlEnc_AliasAddressList_PDU (&ctxt, &msgData);

   if (stat == 0) {
      if (trace) {
         printf ("encoded XML message:\n");
         puts ((char*)rtXmlGetEncBufPtr(&ctxt));
         printf ("\n");
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      return (stat);
   }

   /* Write the encoded message out to the output file */

   stat = rtXmlWriteToFile (&ctxt, filename);
   if (0 != stat) {
      printf ("Error opening %s for write access\n", filename);
      rtxErrPrint (&ctxt);
   }
   rtxFreeContext (&ctxt);

   return 0;
}
