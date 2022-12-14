/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.4.A, Date: 27-Nov-2010.
 */
#include "Test.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxPrint.h"

static int processResult (OSCTXT* pctxt, int stat, const char* filename)
{
   const OSOCTET* msgptr = pctxt->buffer.data;
   size_t len = pctxt->buffer.byteIndex;

   printf ("Hex dump of encoded record:\n");
   rtxHexDump (msgptr, len);

   if (stat < 0) {
      printf ("Encoding failed\n");
      rtxErrPrint (pctxt);
      return stat;
   }

   /* Write the encoded message out to the output file */
   stat = rtxFileWriteBinary (filename, msgptr, len);
   if (stat < 0) {
      printf ("Write to file failed\n");
      rtxErrPrint (pctxt);
   }

   return stat;
}

int main (int argc, char** argv)
{
   OSCTXT     ctxt;
   int        i, stat;
   OSBOOL     verbose = FALSE;
   OSOCTET    buffer[100];

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-notrace")) {}
         else {
            printf ("usage: writer [-v]\n");
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

   /* Examples from OER spec */
   /* Example 1 */
   {
      BitStr1 data;
      data.numbits = 12;
      memset (data.data, 0, sizeof(data.data));
      rtxSetBit (data.data, 12, 3);

      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_BitStr1 (&ctxt, data);
      stat = processResult (&ctxt, stat, "Example1.dat");
   }

   /* Example 2 */
   if (stat >= 0) {
      BitStr2 data;
      data.numbits = 20;
      memset (data.data, 0, sizeof(data.data));
      rtxSetBit (data.data, 32, 3);

      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_BitStr2 (&ctxt, data);
      stat = processResult (&ctxt, stat, "Example2.dat");
   }

   /* Example 3 */
   if (stat >= 0) {
      BitStr2 data;
      data.numbits = 14;
      memset (data.data, 0, sizeof(data.data));
      rtxSetBit (data.data, 32, 3);

      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_BitStr2 (&ctxt, data);
      stat = processResult (&ctxt, stat, "Example3.dat");
   }

   /* Example 4 */
   if (stat >= 0) {
      BitStr2 data;
      data.numbits = 14;
      memset (data.data, 0, sizeof(data.data));
      rtxSetBit (data.data, 32, 13);

      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_BitStr2 (&ctxt, data);
      stat = processResult (&ctxt, stat, "Example4.dat");
   }

   /* Example 5 */
   if (stat >= 0) {
      ASN1BitStr32 data;
      data.numbits = 20;
      memset (data.data, 0, sizeof(data.data));
      rtxSetBit (data.data, 32, 3);

      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = oerEncBitStr (&ctxt, data.data, data.numbits);
      stat = processResult (&ctxt, stat, "Example5.dat");
   }

   rtFreeContext (&ctxt);

   return stat;
}
