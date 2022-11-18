// This test driver program encodes a data record and writes the 
// encoded result to an output file..

#include <stdio.h>
#include <stdlib.h>
#include "PKCS15TokenInfo.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   int	        i, stat;
   const char*  filename = "message.xml";
   OSBOOL       verbose = FALSE, trace = TRUE, cxer = FALSE;

   // Process command line arguments 

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

   // Encode open type parameters

   OSXMLEncodeBuffer encodeBuffer;
   if (cxer) rtxCtxtSetFlag (encodeBuffer.getCtxtPtr(), OSXMLC14N);

   ASN1T_TokenInfo tokenInfo;
   ASN1C_TokenInfo tokenInfoC (encodeBuffer, tokenInfo);
   OSCTXT* pctxt = encodeBuffer.getCtxtPtr();

   // Encode open type parameters

   OSOCTET msgbuf1[100];
   OSCTXT  ctxt1;
   if (rtXmlInitContext (&ctxt1) != 0) {
      rtxErrPrint (&ctxt1);
      return -1;
   }
   rtxSetDiag (&ctxt1, verbose);
   rtXmlSetEncBufPtr (&ctxt1, msgbuf1, sizeof(msgbuf1));
   rtxCtxtSetFlag(&ctxt1, OSASN1XER);
   rtxCtxtSetFlag(&ctxt1, OSXMLC14N);

   rtXmlEncEmptyElement (&ctxt1, OSUTF8("NULL"), 0, 0, TRUE);

   OSOCTET msgbuf2[400];
   OSOCTET param2[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
   OSCTXT  ctxt2;
   if (rtXmlInitContext (&ctxt2) != 0) {
      rtxErrPrint (&ctxt2);
      return -1;
   }
   rtxSetDiag (&ctxt2, verbose);
   rtXmlSetEncBufPtr (&ctxt2, msgbuf2, sizeof(msgbuf2));
   rtxCtxtSetFlag(&ctxt2, OSASN1XER);
   rtxCtxtSetFlag(&ctxt2, OSXMLC14N);
   rtXmlEncHexBinary (&ctxt2, sizeof(param2), param2, OSUTF8("OCTET_STRING"), 0);

   // Populate tokenInfo

   tokenInfo.version = TokenInfo_version::v1;
   OSOCTET serialNumber[] = {
      0x15, 0x97, 0x52, 0x22, 0x25, 0x15, 0x40, 0x12, 0x40
   } ;
   tokenInfo.serialNumber.numocts = sizeof (serialNumber);
   tokenInfo.serialNumber.data = serialNumber;
   tokenInfo.m.manufacturerIDPresent = TRUE;
   tokenInfo.manufacturerID = OSUTF8("XY, Inc.");
   tokenInfo.m.labelPresent = TRUE;
   tokenInfo.label = OSUTF8("Digital signature card");
   ASN1C_TokenFlags tokenflags (encodeBuffer, tokenInfo.tokenflags);
   tokenflags.set (ASN1C_TokenFlags::prnGeneration);

   // Populate Security Environment Info 

   tokenInfo.m.seInfoPresent = TRUE;

   ASN1CSeqOfList seRecList (encodeBuffer, tokenInfo.seInfo);
   ASN1T_SecurityEnvironmentInfo seRec;

   seRec.se = 1;
   seRec.owner.numids = 3;
   seRec.owner.subid[0] = 1;
   seRec.owner.subid[1] = 0;
   seRec.owner.subid[2] = 0;

   seRecList.append (&seRec);

   // Populate supported Algorithms array

   tokenInfo.m.supportedAlgorithmsPresent = TRUE;

   ASN1CSeqOfList algInfoList (encodeBuffer, tokenInfo.supportedAlgorithms);
   ASN1T_AlgorithmInfo* pAlgorithmInfo;

   pAlgorithmInfo = rtxMemAllocType (pctxt, ASN1T_AlgorithmInfo);
   pAlgorithmInfo->reference = 1;
   pAlgorithmInfo->algorithm = 1;
   pAlgorithmInfo->parameters.numocts = rtxCtxtGetMsgLen(&ctxt1);
   pAlgorithmInfo->parameters.data = msgbuf1;
   ASN1C_Operations supportedOperations1 
      (encodeBuffer, pAlgorithmInfo->supportedOperations);
   supportedOperations1.set (ASN1C_Operations::hash);
   pAlgorithmInfo->m.algIdPresent = TRUE;
   ASN1OBJID algId1 = { 6, { 1, 3, 14, 3, 2, 26 } };
   pAlgorithmInfo->algId = algId1;
   algInfoList.append (pAlgorithmInfo);

   pAlgorithmInfo = rtxMemAllocType (pctxt, ASN1T_AlgorithmInfo);
   pAlgorithmInfo->reference = 2;
   pAlgorithmInfo->algorithm = 2;
   pAlgorithmInfo->parameters.numocts = rtxCtxtGetMsgLen(&ctxt1);
   pAlgorithmInfo->parameters.data = msgbuf1;
   ASN1C_Operations supportedOperations2 
      (encodeBuffer, pAlgorithmInfo->supportedOperations);
   supportedOperations2.set (ASN1C_Operations::compute_signature);
   pAlgorithmInfo->m.algIdPresent = TRUE;
   ASN1OBJID algId2 = { 8, { 1, 3, 36, 3, 4, 3, 2, 1 } };
   pAlgorithmInfo->algId = algId2;
   algInfoList.append (pAlgorithmInfo);

   pAlgorithmInfo = rtxMemAllocType (pctxt, ASN1T_AlgorithmInfo);
   pAlgorithmInfo->reference = 3;
   pAlgorithmInfo->algorithm = 3;
   pAlgorithmInfo->parameters.numocts = rtxCtxtGetMsgLen(&ctxt1);
   pAlgorithmInfo->parameters.data = msgbuf1;
   ASN1C_Operations supportedOperations3 
      (encodeBuffer, pAlgorithmInfo->supportedOperations);
   supportedOperations3.set (ASN1C_Operations::compute_checksum);
   supportedOperations3.set (ASN1C_Operations::verify_checksum);
   pAlgorithmInfo->m.algIdPresent = TRUE;
   ASN1OBJID algId3 = { 3, { 1, 0, 0 } };
   pAlgorithmInfo->algId = algId3;
   algInfoList.append (pAlgorithmInfo);

   pAlgorithmInfo = rtxMemAllocType (pctxt, ASN1T_AlgorithmInfo);
   pAlgorithmInfo->reference = 4;
   pAlgorithmInfo->algorithm = 4;
   pAlgorithmInfo->parameters.numocts = rtxCtxtGetMsgLen(&ctxt2);
   pAlgorithmInfo->parameters.data = msgbuf2;
   ASN1C_Operations supportedOperations4 
      (encodeBuffer, pAlgorithmInfo->supportedOperations);
   supportedOperations4.set (ASN1C_Operations::encipher);
   supportedOperations4.set (ASN1C_Operations::decipher);
   pAlgorithmInfo->m.algIdPresent = TRUE;
   ASN1OBJID algId4 = { 6, { 1, 2, 840, 113549, 3, 7 } };
   pAlgorithmInfo->algId = algId4;
   algInfoList.append (pAlgorithmInfo);

   tokenInfo.m.issuerIdPresent = TRUE;
   tokenInfo.issuerId = OSUTF8("wxy");
   tokenInfo.m.holderIdPresent = TRUE;
   tokenInfo.holderId = OSUTF8("vwx");

   // Encode 

   if ((stat = tokenInfoC.Encode ()) == 0) {
      if (trace) {
         printf ("encoded XML message:\n");
         printf ((const char*)encodeBuffer.getMsgPtr());
         printf ("\n");
      }
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      return stat;
   }
  
   // Write the encoded message out to the output file

   if ((stat = encodeBuffer.write (filename)) < 0) {
      printf ("Error writing XML document to file %s\n", filename);
      return stat;
   }

   rtFreeContext (&ctxt2);
   rtFreeContext (&ctxt1);

   return 0;

}
