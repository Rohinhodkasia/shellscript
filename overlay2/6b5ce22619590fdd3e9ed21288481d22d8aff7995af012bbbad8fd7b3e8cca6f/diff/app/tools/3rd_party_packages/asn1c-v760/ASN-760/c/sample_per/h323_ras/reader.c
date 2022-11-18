/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "H323RAS.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxStreamFile.h"

int main (int argc, char** argv)
{
   RasMessage   rasMessage;
   OSCTXT	ctxt;
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   const char*  filename = "message.dat";
   int		i, stat;

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

   stat = rtxStreamFileCreateReader (&ctxt, filename);
   if (0 != stat) {
      printf ("Stream initialization failed.\n");
      rtxErrPrint (&ctxt);
      return stat;
   }
   pu_setAligned (&ctxt, aligned);
   pu_setTrace (&ctxt, trace);

   /* Call compiler generated decode function */

   stat = asn1PD_RasMessage (&ctxt, &rasMessage);

   if (trace) {
      printf ("Hex dump of encoded record:\n");
      pu_hexdump (&ctxt);
      printf ("Dump of decoded bit fields:\n");
      pu_bindump (&ctxt, "rasMessage");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode of RasMessage was successful\n");
         asn1Print_RasMessage ("rasMessage", &rasMessage);
      }
   }
   else {
       printf ("decode of RasMessage failed\n");
       rtxErrPrint (&ctxt);
       return -1;
   }

   rtFreeContext (&ctxt);

   return 0;
}
