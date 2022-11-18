/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "SeqOfTest.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

int main (int argc, char** argv)
{
   SeqOf10Ints  seqOf10Ints;
   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN];
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   OSUINT32     ui;
   FILE*        fp;
   const char*  filename = "message.dat";
   int          i, stat;
   OSSIZE       len;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader -a | -u [ -v ] [ -i <filename>\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
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
      if (trace)
         printf ("Read %d bytes from file %s..\n", len, filename);
   }
   else {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }

   /* Create a new context structure */

   if (rtInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);
   pu_setBuffer (&ctxt, msgbuf, len, aligned);
   pu_setTrace (&ctxt, trace);

   /* Call compiler generated decode function */

   stat = asn1PD_SeqOf10Ints (&ctxt, &seqOf10Ints);

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      pu_bindump (&ctxt, "seqOf10Ints");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode of SeqOf10Ints was successful\n");
         printf ("   seqOf10Ints.n = %d\n", seqOf10Ints.n);
         for (ui = 0; ui < seqOf10Ints.n; ui++) {
            printf ("   seqOf10Ints.elem[%d] = %d\n", 
                    ui, seqOf10Ints.elem[ui]);
         }
      }
   }
   else {
       printf ("decode of SeqOf10Ints failed\n");
       rtxErrPrint (&ctxt);
       return -1;
   }

   rtFreeContext (&ctxt);

   return 0;
}
