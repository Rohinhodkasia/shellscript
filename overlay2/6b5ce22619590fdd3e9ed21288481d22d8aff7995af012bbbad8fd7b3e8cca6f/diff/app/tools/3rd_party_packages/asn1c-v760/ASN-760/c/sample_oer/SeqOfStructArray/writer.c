/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.4.A, Date: 22-Dec-2010.
 */
#include "Test.h"
#include "rtxsrc/rtxCommon.h"

#include "rtxsrc/rtxPrint.h"
#include "rtxsrc/rtxStreamMemory.h"

int main (int argc, char** argv)
{
   TestSeq* pdata;
   OSCTXT     ctxt;
   OSOCTET*   msgptr;
   int        i, stat;
   OSSIZE     len;
   OSBOOL     trace = TRUE;
   OSBOOL     verbose = FALSE;
   const char* filename = "message.dat";

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [-v] [-o <filename>]  [-notrace]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
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

   pdata = asn1Test_TestSeq (&ctxt);

   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_TestSeq ("data", pdata);
      printf ("\n");
   }

   /* Create memory output stream */
   stat = rtxStreamMemoryCreateWriter (&ctxt, 0, 0);
   if (stat < 0) {
      printf ("Create memory output stream failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }

   /* Encode */
   stat = OEREnc_TestSeq (&ctxt, pdata);

   msgptr = rtxStreamMemoryGetBuffer (&ctxt, &len);

   if (trace) {
      printf ("Hex dump of encoded record:\n");
      rtxHexDump (msgptr, len);
   }
   if (stat < 0) {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }
   /* Write the encoded message out to the output file */
   stat = rtxFileWriteBinary (filename, msgptr, len);
   if (stat < 0) {
      printf ("Write to file failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }

   rtFreeContext (&ctxt);

   return 0;
}
