// This test driver program encodes a data record and writes the 
// encoded result to an output file..

#include <stdio.h>
#include <stdlib.h>
#include "PKCS15TokenInfo.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/osMacros.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSOCTET     msgbuf[1024];
   int         i, len;
   const char* filename = "message.dat";
   OSBOOL      verbose = FALSE, trace = TRUE;

   // Process command line arguments 

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   ASN1BEREncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf));
   encodeBuffer.setDiag (verbose);
   ASN1T_TokenInfo tokenInfo;
   ASN1C_TokenInfo tokenInfoC (encodeBuffer, tokenInfo);

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
   ASN1CBitStr tokenflags (encodeBuffer, tokenInfo.tokenflags.data, 
                           tokenInfo.tokenflags.numbits, 8);
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

   ASN1T_AlgorithmInfo* pAlgorithmInfo;
   ASN1C__SeqOfAlgorithmInfo algInfoList 
      (encodeBuffer, tokenInfo.supportedAlgorithms);

   pAlgorithmInfo = algInfoList.NewElement();
   pAlgorithmInfo->reference = 1;
   pAlgorithmInfo->algorithm = 1;
   OSOCTET pnull[] = { 5, 0 };
   pAlgorithmInfo->parameters.numocts = sizeof(pnull);
   pAlgorithmInfo->parameters.data = pnull;
   ASN1CBitStr supportedOperations1 
      (encodeBuffer, pAlgorithmInfo->supportedOperations.data,
       pAlgorithmInfo->supportedOperations.numbits, 8);
   supportedOperations1.set (ASN1C_Operations::hash);
   pAlgorithmInfo->m.algIdPresent = TRUE;
   ASN1OBJID algId1 = { 6, { 1, 3, 14, 3, 2, 26 } };
   pAlgorithmInfo->algId = algId1;
   algInfoList.Append (pAlgorithmInfo);

   pAlgorithmInfo = algInfoList.NewElement();
   pAlgorithmInfo->reference = 2;
   pAlgorithmInfo->algorithm = 2;
   pAlgorithmInfo->parameters.numocts = sizeof(pnull);
   pAlgorithmInfo->parameters.data = pnull;
   ASN1CBitStr supportedOperations2 
      (encodeBuffer, pAlgorithmInfo->supportedOperations.data,
       pAlgorithmInfo->supportedOperations.numbits, 8);
   supportedOperations2.set (ASN1C_Operations::compute_signature);
   pAlgorithmInfo->m.algIdPresent = TRUE;
   ASN1OBJID algId2 = { 8, { 1, 3, 36, 3, 4, 3, 2, 1 } };
   pAlgorithmInfo->algId = algId2;
   algInfoList.Append (pAlgorithmInfo);

   pAlgorithmInfo = algInfoList.NewElement();
   pAlgorithmInfo->reference = 3;
   pAlgorithmInfo->algorithm = 3;
   pAlgorithmInfo->parameters.numocts = sizeof(pnull);
   pAlgorithmInfo->parameters.data = pnull;
   ASN1CBitStr supportedOperations3 
      (encodeBuffer, pAlgorithmInfo->supportedOperations.data,
       pAlgorithmInfo->supportedOperations.numbits, 8);
   supportedOperations3.set (ASN1C_Operations::compute_checksum);
   supportedOperations3.set (ASN1C_Operations::verify_checksum);
   pAlgorithmInfo->m.algIdPresent = TRUE;
   ASN1OBJID algId3 = { 3, { 1, 0, 0 } };
   pAlgorithmInfo->algId = algId3;
   algInfoList.Append (pAlgorithmInfo);

   pAlgorithmInfo = algInfoList.NewElement();
   pAlgorithmInfo->reference = 4;
   pAlgorithmInfo->algorithm = 4;
   OSOCTET pdata[] = { 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 };
   pAlgorithmInfo->parameters.numocts = sizeof(pdata);
   pAlgorithmInfo->parameters.data = pdata;
   ASN1CBitStr supportedOperations4 
      (encodeBuffer, pAlgorithmInfo->supportedOperations.data,
       pAlgorithmInfo->supportedOperations.numbits, 8);
   supportedOperations4.set (ASN1C_Operations::encipher);
   supportedOperations4.set (ASN1C_Operations::decipher);
   pAlgorithmInfo->m.algIdPresent = TRUE;
   ASN1OBJID algId4 = { 6, { 1, 2, 840, 113549, 3, 7 } };
   pAlgorithmInfo->algId = algId4;
   algInfoList.Append (pAlgorithmInfo);

   tokenInfo.m.issuerIdPresent = TRUE;
   tokenInfo.issuerId = OSUTF8("wxy");
   tokenInfo.m.holderIdPresent = TRUE;
   tokenInfo.holderId = OSUTF8("vwx");

   // Encode 

   const OSOCTET* msgptr;

   if ((len = tokenInfoC.Encode ()) >= 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.HexDump (len);
         printf ("Binary dump:\n");
         encodeBuffer.BinDump ();
      }
      msgptr = encodeBuffer.GetMsgPtr ();
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.PrintErrorInfo ();
      return len;
   }
  
   // Write the encoded message out to the output file

   int ret = rtxFileWriteBinary (filename, msgptr, len);
   if (ret < 0) {
      printf ("Write to file %s failed\n", filename);
      return ret;
   }

   return 0;
}
