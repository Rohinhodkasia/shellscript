/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "H4501-Supplementary-ServiceAPDU-Structure.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

int main (int argc, char** argv)
{
   H4501SupplementaryService h450Message;
   OSCTXT  ctxt;
   OSOCTET msgbuf[] = { 
      0x60, 0x10, 0x01, 0x10, 0x00, 0x00, 0x80, 0x09, 
      0x2b, 0x06, 0x01, 0x04, 0x01, 0xb4, 0x0a, 0x02, 
      0x01, 0x0f, 0x40, 0x00, 0x02, 0x00, 0x1e, 0x00, 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
      0x00
   } ;
   OSBOOL       aligned = TRUE, trace = TRUE, verbose = FALSE;
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

   /* Initialize context structure */
   stat = rtInitContext (&ctxt);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }
   rtxSetDiag (&ctxt, verbose);

   pu_setBuffer (&ctxt, msgbuf, sizeof(msgbuf), aligned);
   pu_setTrace (&ctxt, trace);

   /* Call compiler generated decode function */

   stat = asn1PD_H4501SupplementaryService (&ctxt, &h450Message);

   if (trace) {
      printf ("Hex dump of encoded record:\n");
      pu_hexdump (&ctxt);
      printf ("Dump of decoded bit fields:\n");
      pu_bindump (&ctxt, "h450Message");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode was successful\n");
         asn1Print_H4501SupplementaryService ("h450Message", &h450Message);
      }
   }
   else {
       printf ("decode failed\n");
       rtxErrPrint (&ctxt);
       return -1;
   }

   rtFreeContext (&ctxt);

   return 0;
}
