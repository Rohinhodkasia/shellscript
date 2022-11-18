/* This test driver program encodes a data record and writes the 
   encoded result to an output file. */

#include <stdio.h>
#include <stdlib.h>
#include "PKCS15TokenInfo.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 4096

int main (int argc, char** argv)
{
   TokenInfo    msgData;
   int	        i, stat;
   OSBOOL       verbose = FALSE, trace = TRUE, cxer = FALSE;
   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN];
   OSOCTET      msgbuf1[100];
   OSCTXT       ctxt1;
   OSOCTET      msgbuf2[400];
   OSOCTET      param2[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
   OSCTXT       ctxt2;
   OSOCTET      serialNumber[] = {
      0x15, 0x97, 0x52, 0x22, 0x25, 0x15, 0x40, 0x12, 0x40
   } ;
   const char* filename = "message.xml";
   SecurityEnvironmentInfo seRec;
   AlgorithmInfo algorithmInfo[4];
   FILE* fp;

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

   /* Encode */

   if (rtXmlInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);

   rtXmlSetEncBufPtr(&ctxt, msgbuf, sizeof(msgbuf));
   if (cxer) rtxCtxtSetFlag(&ctxt, OSXMLC14N);

   /* Encode open type parameters */

   if (rtXmlInitContext (&ctxt1) != 0) {
      rtxErrPrint (&ctxt1);
      return -1;
   }
   rtxSetDiag (&ctxt1, verbose);
   rtXmlSetEncBufPtr (&ctxt1, msgbuf1, sizeof(msgbuf1));
   rtxCtxtSetFlag(&ctxt1, OSASN1XER);
   rtxCtxtSetFlag(&ctxt1, OSXMLC14N);

   
   rtXmlEncEmptyElement (&ctxt1, OSUTF8("NULL"), 0, 0, TRUE);

   if (rtXmlInitContext (&ctxt2) != 0) {
      rtxErrPrint (&ctxt2);
      return -1;
   }
   rtxSetDiag (&ctxt2, verbose);
   rtXmlSetEncBufPtr (&ctxt2, msgbuf2, sizeof(msgbuf2));
   rtxCtxtSetFlag(&ctxt2, OSASN1XER);
   rtxCtxtSetFlag(&ctxt2, OSXMLC14N);
   rtXmlEncHexBinary (&ctxt2, sizeof(param2), param2, OSUTF8("OCTET_STRING"), 0);

   memset (&msgData, 0, sizeof (msgData));

   /* Populate Security Environment Info array */

   rtxDListInit (&msgData.seInfo);

   memset (&seRec, 0, sizeof (seRec));

   seRec.se = 1;
   seRec.owner.numids = 3;
   seRec.owner.subid[0] = 1;
   seRec.owner.subid[1] = 0;
   seRec.owner.subid[2] = 0;

   rtxDListAppend (&ctxt, &msgData.seInfo, &seRec);

   /* Populate supported Algorithms array */

   memset (algorithmInfo, 0, sizeof(algorithmInfo));
   rtxDListInit (&msgData.supportedAlgorithms);

   algorithmInfo[0].reference = 1;
   algorithmInfo[0].algorithm = 1;
   algorithmInfo[0].parameters.numocts = rtxCtxtGetMsgLen(&ctxt1);
   algorithmInfo[0].parameters.data = msgbuf1;
   algorithmInfo[0].supportedOperations.numbits = 7;
   rtxSetBit(algorithmInfo[0].supportedOperations.data,
      algorithmInfo[0].supportedOperations.numbits,
      Operations_hash);
   algorithmInfo[0].m.algIdPresent = TRUE;
   algorithmInfo[0].algId.numids = 6;
   algorithmInfo[0].algId.subid[0] = 1;
   algorithmInfo[0].algId.subid[1] = 3;
   algorithmInfo[0].algId.subid[2] = 14;
   algorithmInfo[0].algId.subid[3] = 3;
   algorithmInfo[0].algId.subid[4] = 2;
   algorithmInfo[0].algId.subid[5] = 26;
   rtxDListAppend (&ctxt, &msgData.supportedAlgorithms, &algorithmInfo[0]);

   algorithmInfo[1].reference = 2;
   algorithmInfo[1].algorithm = 2;
   algorithmInfo[1].parameters.numocts = rtxCtxtGetMsgLen(&ctxt1);
   algorithmInfo[1].parameters.data = msgbuf1;
   algorithmInfo[1].supportedOperations.numbits = 2;
   rtxSetBit(algorithmInfo[1].supportedOperations.data,
      algorithmInfo[1].supportedOperations.numbits,
      Operations_compute_signature);
   algorithmInfo[1].m.algIdPresent = TRUE;
   algorithmInfo[1].algId.numids = 8;
   algorithmInfo[1].algId.subid[0] = 1;
   algorithmInfo[1].algId.subid[1] = 3;
   algorithmInfo[1].algId.subid[2] = 36;
   algorithmInfo[1].algId.subid[3] = 3;
   algorithmInfo[1].algId.subid[4] = 4;
   algorithmInfo[1].algId.subid[5] = 3;
   algorithmInfo[1].algId.subid[6] = 2;
   algorithmInfo[1].algId.subid[7] = 1;
   rtxDListAppend (&ctxt, &msgData.supportedAlgorithms, &algorithmInfo[1]);

   algorithmInfo[2].reference = 3;
   algorithmInfo[2].algorithm = 3;
   algorithmInfo[2].parameters.numocts = rtxCtxtGetMsgLen(&ctxt1);
   algorithmInfo[2].parameters.data = msgbuf1;
   algorithmInfo[2].supportedOperations.numbits = 3;
   rtxSetBit(algorithmInfo[2].supportedOperations.data,
      algorithmInfo[2].supportedOperations.numbits,
      Operations_compute_checksum);
   rtxSetBit(algorithmInfo[2].supportedOperations.data,
      algorithmInfo[2].supportedOperations.numbits,
      Operations_verify_checksum);
   algorithmInfo[2].m.algIdPresent = TRUE;
   algorithmInfo[2].algId.numids = 3;
   algorithmInfo[2].algId.subid[0] = 1;
   algorithmInfo[2].algId.subid[1] = 0;
   algorithmInfo[2].algId.subid[2] = 0;
   rtxDListAppend (&ctxt, &msgData.supportedAlgorithms, &algorithmInfo[2]);

   algorithmInfo[3].reference = 4;
   algorithmInfo[3].algorithm = 4;
   algorithmInfo[3].parameters.numocts = rtxCtxtGetMsgLen(&ctxt2);
   algorithmInfo[3].parameters.data = msgbuf2;
   algorithmInfo[3].supportedOperations.numbits = 6;
   rtxSetBit(algorithmInfo[3].supportedOperations.data,
      algorithmInfo[3].supportedOperations.numbits,
      Operations_decipher);
   rtxSetBit(algorithmInfo[3].supportedOperations.data,
      algorithmInfo[3].supportedOperations.numbits,
      Operations_encipher);
   algorithmInfo[3].m.algIdPresent = TRUE;
   algorithmInfo[3].algId.numids = 6;
   algorithmInfo[3].algId.subid[0] = 1;
   algorithmInfo[3].algId.subid[1] = 2;
   algorithmInfo[3].algId.subid[2] = 840;
   algorithmInfo[3].algId.subid[3] = 113549;
   algorithmInfo[3].algId.subid[4] = 3;
   algorithmInfo[3].algId.subid[5] = 7;
   rtxDListAppend (&ctxt, &msgData.supportedAlgorithms, &algorithmInfo[3]);

   /* Populate structure of generated type */

   msgData.version = v1;
   msgData.serialNumber.numocts = sizeof (serialNumber);
   msgData.serialNumber.data = serialNumber;
   msgData.m.manufacturerIDPresent = TRUE;
   msgData.manufacturerID = "XY, Inc.";
   msgData.m.labelPresent = TRUE;
   msgData.label = "Digital signature card";
   msgData.tokenflags.numbits = 3;
   rtxSetBit(msgData.tokenflags.data,
      msgData.tokenflags.numbits,
      TokenFlags_prnGeneration);
   msgData.m.seInfoPresent = TRUE;
   msgData.m.supportedAlgorithmsPresent = TRUE;
   msgData.m.issuerIdPresent = TRUE;
   msgData.issuerId = "wxy";
   msgData.m.holderIdPresent = TRUE;
   msgData.holderId = "vwx";
   
   /* Encode */

   stat = XmlEnc_TokenInfo_PDU (&ctxt, &msgData);

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

   rtFreeContext (&ctxt2);
   rtFreeContext (&ctxt1);
   rtFreeContext (&ctxt);
   return 0;
}
