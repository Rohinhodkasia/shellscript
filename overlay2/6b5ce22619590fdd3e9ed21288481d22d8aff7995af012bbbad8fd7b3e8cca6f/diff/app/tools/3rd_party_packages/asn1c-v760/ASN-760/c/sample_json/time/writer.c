/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.6.B, Date: 19-Dec-2012.
 */
#include "TimeString.h"
#include "rtxsrc/rtxCommon.h"

#include "rtxsrc/rtxPrint.h"
#include "rtxsrc/rtxStreamFile.h"

int main (int argc, char** argv)
{
   TimesSeq* pdata;
   OSCTXT     ctxt;
   int        i, stat;
   OSBOOL     trace = TRUE;
   OSBOOL     verbose = FALSE;
   const char* filename = "message.json";

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

   pdata = asn1Test_TimesSeq (&ctxt);

   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_TimesSeq ("data", pdata);
      printf ("\n");
   }

   /* Create file output stream */
   stat = rtxStreamFileCreateWriter (&ctxt, filename);
   if (stat < 0) {
      printf ("Create file output stream failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }

   /* Encode */
   stat = asn1JsonEnc_TimesSeq (&ctxt, pdata);
   if (stat < 0) {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }
   else if (trace) {
      printf ("Output file written successfully.\n");
   }

   rtFreeContext (&ctxt);

   return 0;
}
