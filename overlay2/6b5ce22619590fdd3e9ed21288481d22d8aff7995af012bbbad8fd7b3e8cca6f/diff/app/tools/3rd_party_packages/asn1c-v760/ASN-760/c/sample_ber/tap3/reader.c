/**
 * This test driver program reads an encoded record from a TAP3 file 
 * and decodes it and displays the results..
 */
#include <stdio.h>
#include <stdlib.h>
#include "TAP-0311.h"
#include "rtxsrc/rtxStreamFile.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxMemLeakCheck.h"

int main (int argc, char** argv)
{
   DataInterChange dataInterChange;
   OSCTXT	ctxt;
   int		i, stat;
   const char*  filename = "message.dat";
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

   /* Init context for stream access */

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

   /* Call compiler generated decode function */

   stat = asn1BSD_DataInterChange (&ctxt, &dataInterChange, ASN1EXPL, 0);

   if (stat == 0) {
      if (trace) {
         printf ("Decode of DataInterChange was successful\n");
         asn1Print_DataInterChange ("DataInterChange", &dataInterChange);
      }
   }
   else {
      rtxErrPrint (&ctxt); 
      printf ("Decode of DataInterChange failed\n");
      return -1;
   }

   berStrmFreeContext (&ctxt);

   return 0;
}
