#include "Test.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxPrint.h"

int main (int argc, char** argv)
{
   MyString   pdata;
   OSCTXT     ctxt;
   OSOCTET*   msgptr;
   int        i, len, stat;
   OSBOOL     trace = TRUE;
   OSBOOL     verbose = FALSE;
   const char* filename = "message.dat";
   OSOCTET    buffer[100];

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
   rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
   rtxSetDiag (&ctxt, verbose);

   pdata = "1234567890";

   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_MyString ("data", pdata);
      printf ("\n");
   }

   /* Encode */
   stat = OEREnc_MyString (&ctxt, pdata);

   msgptr = ctxt.buffer.data;
   len = ctxt.buffer.byteIndex;

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
