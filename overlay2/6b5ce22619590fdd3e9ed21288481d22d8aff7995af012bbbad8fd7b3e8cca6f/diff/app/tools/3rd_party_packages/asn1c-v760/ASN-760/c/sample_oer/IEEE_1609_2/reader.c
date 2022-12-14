/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.2.A, Date: 27-Jun-2017.
 */
#include "IEEE1609dot2.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxDiagBitTrace.h"

int main (int argc, char** argv)
{
   Certificate data;
   OSCTXT      ctxt;
   OSOCTET*    pMsgBuf;
   OSBOOL      trace = TRUE, verbose = FALSE;
   const char* filename = "message.dat";
   int         i, stat;
   OSSIZE      len;

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [-v] [-i <filename>] [-notrace]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
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

   /* Read input file into a memory buffer */
   stat = rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len);
   if (0 == stat) {
      stat = rtxInitContextBuffer (&ctxt, pMsgBuf, len);
   }
   if (0 != stat) {
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }

   asn1Init_Certificate (&data);

   /* Call compiler generated decode function */
   stat = OERDec_Certificate (&ctxt, &data);
   if (stat != 0) {
      printf ("decode of data failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return -1;
   }

   if (trace) {
      asn1Print_Certificate ("Data", &data);
   }

   rtFreeContext (&ctxt);

   return 0;
}
