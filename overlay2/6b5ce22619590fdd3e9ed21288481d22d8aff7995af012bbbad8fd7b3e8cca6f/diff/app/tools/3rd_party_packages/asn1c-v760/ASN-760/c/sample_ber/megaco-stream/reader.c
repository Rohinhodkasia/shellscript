/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "MEDIA-GATEWAY-CONTROL.h"
#include "rtxsrc/rtxStreamFile.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxMemLeakCheck.h"

#define MAXMSGLEN 1024

int main (int argc, char** argv)
{
   MegacoMessage megacoMessage;
   OSCTXT	ctxt;
   int		i, stat;
   char*        filename = "msg25.bin";
   OSBOOL     trace = TRUE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) rtxSetGlobalDiag (1);
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [ -v ] [ -i <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Init context for stream first */

   if ((stat = berStrmInitContext (&ctxt)) != 0) {
      printf ("Initialization failed, status %d\n", stat);
      return -1;
   }

   /* Open the input stream to read data */

   stat = rtxStreamFileCreateReader (&ctxt, filename);

   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   /* Decode */

   stat = asn1BSD_MegacoMessage (&ctxt, &megacoMessage, ASN1EXPL, 0);
   if (stat == 0) {
      if (trace) {
         printf ("Decode was successful\n");
         printf ("Decoded record:\n");
         asn1Print_MegacoMessage ("megacoMessage", &megacoMessage);
      }
   }
   else {
      printf ("decode failed\n");
      rtxErrPrint (&ctxt);
      return -1;
   }

   berStrmFreeContext (&ctxt);
   return 0;
}

