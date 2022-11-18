/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "MEDIA-GATEWAY-CONTROL.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

int main (int argc, char** argv)
{
   MegacoMessage megacoMessage;
   OSCTXT	ctxt;
   OSOCTET*	msgbuf;
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = 1;
   const char*  filename = "msg05.bin";
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

   /* Create a new context structure */

   if (rtInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Read input file into a memory buffer */

   stat = rtxFileReadBinary (&ctxt, filename, &msgbuf, &len);
   if (0 != stat) {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }

   pu_setBuffer (&ctxt, msgbuf, len, aligned);
   pu_setTrace (&ctxt, trace);

   /* Call compiler generated decode function */

   stat = asn1PD_MegacoMessage (&ctxt, &megacoMessage);

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      pu_bindump (&ctxt, "megacoMessage");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode of MegacoMessage was successful\n");
         asn1Print_MegacoMessage ("megacoMessage", &megacoMessage);
      }
   }
   else {
       printf ("decode of MegacoMessage failed\n");
       rtxErrPrint (&ctxt);
       return -1;
   }

   rtFreeContext (&ctxt);

   return 0;
}
