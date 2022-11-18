// This test driver program encodes a data record and writes the encoded 
// result to an output file..

#include <stdio.h>
#include <stdlib.h>
#include "ExtChoice.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxmlsrc/rtXmlCppMsgBuf.h"

#define MAXMSGLEN 1024

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSOCTET      msgbuf[MAXMSGLEN];
   const char*  filename = "message.xml";
   int          i, stat, tvalue = 1;
   OSBOOL       verbose = FALSE, trace = TRUE;

   // Process command line arguments 

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>] [ -cxer ]\n");
            printf ("   -v             verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace       do not display trace info\n");
            return 0;
         }
      }
   }

   /* Populate structure */

   OSXMLEncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf));
   encodeBuffer.setDiag (verbose);
   ASN1T_AliasAddressList msgData;
   ASN1C_AliasAddressList aliasAddressList (encodeBuffer, msgData);
   ASN1T_AliasAddress_transportID transId;
   ASN1T_AliasAddress* pAliasAddress;
   
   pAliasAddress = (ASN1T_AliasAddress*) 
      aliasAddressList.memAlloc (sizeof(ASN1T_AliasAddress));
   pAliasAddress->t = T_AliasAddress_e164;
   pAliasAddress->u.e164 = "#39047752,937";
   aliasAddressList.append (pAliasAddress);

   pAliasAddress = (ASN1T_AliasAddress*) 
      aliasAddressList.memAlloc (sizeof(ASN1T_AliasAddress));
   pAliasAddress->t = T_AliasAddress_h323_ID;
   pAliasAddress->u.h323_ID = 
      (ASN1TBMPString*)aliasAddressList.memAlloc (sizeof(ASN1TBMPString));
   rtCToBMPString (encodeBuffer.getCtxtPtr(), 
                   "TESTSTRING", pAliasAddress->u.h323_ID, 0);
   aliasAddressList.append (pAliasAddress);

   pAliasAddress = (ASN1T_AliasAddress*) 
      aliasAddressList.memAlloc (sizeof(ASN1T_AliasAddress));
   pAliasAddress->t = T_AliasAddress_url_ID;
   pAliasAddress->u.url_ID = "http://www.obj-sys.com";
   aliasAddressList.append (pAliasAddress);

   pAliasAddress = (ASN1T_AliasAddress*) 
      aliasAddressList.memAlloc (sizeof(ASN1T_AliasAddress));
   pAliasAddress->t = T_AliasAddress_transportID;
   transId.transportAddress = "Truck";
   transId.aInt = 111;
   pAliasAddress->u.transportID = &transId;
   aliasAddressList.append (pAliasAddress);

   pAliasAddress = (ASN1T_AliasAddress*) 
      aliasAddressList.memAlloc (sizeof(ASN1T_AliasAddress));
   pAliasAddress->t = T_AliasAddress_email_ID;
   pAliasAddress->u.email_ID = "objective@obj-sys.com";
   aliasAddressList.append (pAliasAddress);

   pAliasAddress = (ASN1T_AliasAddress*) 
      aliasAddressList.memAlloc (sizeof(ASN1T_AliasAddress));
   pAliasAddress->t = T_AliasAddress_partyNumber;
   pAliasAddress->u.partyNumber = 555;
   aliasAddressList.append (pAliasAddress);

   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_AliasAddressList ("aliasAddressList", &msgData);
      printf ("\n");
   }

   // Encode

   if ((stat = aliasAddressList.Encode ()) == 0) {
      if (trace) {
         printf ("encoded XML message:\n");
         printf ((const char*)msgbuf);
         printf ("\n");
      }
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      return -1;
   }
  
   // Write the encoded message out to the output file

   if (encodeBuffer.write (filename) < 0) {
      printf ("Error writing XML document to file '%s'\n", filename);
      return -1;
   }

   return 0;
}
