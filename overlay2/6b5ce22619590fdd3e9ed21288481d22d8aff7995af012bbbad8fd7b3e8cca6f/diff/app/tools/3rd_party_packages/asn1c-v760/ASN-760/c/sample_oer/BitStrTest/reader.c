#include "Test.h"
#include "rtxsrc/rtxCommon.h"
#include "rtsrc/rtPrint.h"

int main (int argc, char** argv)
{
   OSCTXT      ctxt;
   OSOCTET*    pMsgBuf;
   OSBOOL      verbose = FALSE;
   const char* filename;
   int         i, stat;
   size_t      len;

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-notrace")) {}
         else {
            printf ("usage: reader [-v]\n");
            printf ("   -v  verbose mode: print trace info\n");
            return 1;
         }
      }
   }

   /* Initialize context structure */
   stat = rtInitContext (&ctxt);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Decode example 1 */
   { 
      BitStr1 data;
      filename = "Example1.dat";
      if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));
      rtxInitContextBuffer (&ctxt, pMsgBuf, len);

      stat = OERDec_BitStr1 (&ctxt, &data);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return stat;
      }

      asn1Print_BitStr1 ("Example1", &data);
      rtxMemFreePtr (&ctxt, pMsgBuf);
   }

   /* Decode example 2 */
   { 
      BitStr2 data;
      filename = "Example2.dat";
      if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));
      rtxInitContextBuffer (&ctxt, pMsgBuf, len);

      stat = OERDec_BitStr2 (&ctxt, &data);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return stat;
      }

      asn1Print_BitStr2 ("Example2", &data);
      rtxMemFreePtr (&ctxt, pMsgBuf);
   }

   /* Decode example 3 */
   { 
      BitStr2 data;
      filename = "Example3.dat";
      if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));
      rtxInitContextBuffer (&ctxt, pMsgBuf, len);

      stat = OERDec_BitStr2 (&ctxt, &data);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return stat;
      }

      asn1Print_BitStr2 ("Example3", &data);
      rtxMemFreePtr (&ctxt, pMsgBuf);
   }

   /* Decode example 4 */
   { 
      BitStr2 data;
      filename = "Example4.dat";
      if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));
      rtxInitContextBuffer (&ctxt, pMsgBuf, len);

      stat = OERDec_BitStr2 (&ctxt, &data);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return stat;
      }

      asn1Print_BitStr2 ("Example4", &data);
      rtxMemFreePtr (&ctxt, pMsgBuf);
   }

   /* Decode example 5 */
   { 
      ASN1BitStr32 data;
      filename = "Example5.dat";
      if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));
      rtxInitContextBuffer (&ctxt, pMsgBuf, len);

      stat = oerDecBitStr (&ctxt, data.data, sizeof(data.data), &data.numbits);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return stat;
      }

      rtPrintBitStrBraceText ("Example5", data.numbits, data.data);
      rtxMemFreePtr (&ctxt, pMsgBuf);
   }

   rtFreeContext (&ctxt);

   return 0;
}
