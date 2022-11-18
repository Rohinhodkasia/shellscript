/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.6.B, Date: 19-Dec-2012.
 */
#include "TimeString.h"
#include "rtxsrc/rtxCommon.h"

#include "rtxsrc/rtxStreamFile.h"

int main (int argc, char** argv)
{
   TimesSeq data;
   OSCTXT      ctxt;
   OSBOOL      trace = TRUE, verbose = FALSE;
   const char* filename = "message.json";
   int         i, stat;

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

   /* Create file input stream */
   stat = rtxStreamFileCreateReader (&ctxt, filename);
   if (0 != stat) {
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }

   asn1Init_TimesSeq (&data);

   /* Call compiler generated decode function */
   stat = asn1JsonDec_TimesSeq (&ctxt, &data);
   if (stat != 0) {
      printf ("decode of data failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return -1;
   }

   if (trace) {
      asn1Print_TimesSeq ("Data", &data);
   }

   rtFreeContext (&ctxt);

   return 0;
}
