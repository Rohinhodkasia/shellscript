/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "BigInt.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

int main (int argc, char** argv)
{
   Dss_Parms    dss;
   OSCTXT       ctxt;
   OSOCTET      msgbuf[MAXMSGLEN];
   int          i, stat;
   OSSIZE       len;
   FILE*        fp;
   const char*  filename = "message.dat";
   OSBOOL       verbose = FALSE, trace = TRUE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -i <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Read input file into a memory buffer */

   if (fp = fopen (filename, "rb")) {
      len = fread (msgbuf, 1, sizeof(msgbuf), fp);
   }
   else {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }

   /* Init context structure */

   if (rtInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);
   xd_setp64 (&ctxt, msgbuf, len, 0, 0, 0);

   /* Decode */

   stat = asn1D_Dss_Parms (&ctxt, &dss, ASN1EXPL, 0);
   if (stat == 0) {
      if (trace) {
         printf ("Decode of BigInt was successful\n");
         printf ("Decoded record:\n");
         asn1Print_Dss_Parms ("dss", &dss);
      }
   }
   else {
      printf ("decode of BigInt failed\n");
      rtxErrPrint (&ctxt);
      return -1;
   }

   rtFreeContext (&ctxt);
   return 0;
}
