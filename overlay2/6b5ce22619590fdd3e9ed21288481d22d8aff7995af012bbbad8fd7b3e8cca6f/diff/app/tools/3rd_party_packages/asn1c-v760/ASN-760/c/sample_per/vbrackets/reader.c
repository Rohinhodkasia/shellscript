/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "VersionBrackets.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxMemLeakCheck.h"

#define MAXMSGLEN 1024

int main (int argc, char** argv)
{
   TestSequence testSequence;
   OSCTXT	ctxt;
   OSOCTET*	msgbuf;
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
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

   /* Init context structure */

   if (rtInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Read input file into a memory buffer */

   stat = rtxFileReadBinary (&ctxt, filename, &msgbuf, &len);
   if (0 != stat) {
      printf ("Error reading file %s\n", filename);
      return stat;
   }

   pu_setBuffer (&ctxt, msgbuf, len, aligned);
   pu_setTrace (&ctxt, trace);

   /* Call compiler generated decode function */

   stat = asn1PD_TestSequence (&ctxt, &testSequence);

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      pu_bindump (&ctxt, "testSequence");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode of TestSequence was successful\n");
         asn1Print_TestSequence ("testSequence", &testSequence);
      }
   }
   else {
       printf ("decode of TestSequence failed\n");
       rtxErrPrint (&ctxt);
       return -1;
   }

   rtFreeContext (&ctxt);

   return 0;
}
