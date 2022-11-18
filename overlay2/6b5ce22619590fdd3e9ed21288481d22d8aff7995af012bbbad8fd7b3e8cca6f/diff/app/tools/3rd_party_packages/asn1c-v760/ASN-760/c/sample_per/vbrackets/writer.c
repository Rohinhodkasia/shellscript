/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

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
   OSOCTET	msgbuf[MAXMSGLEN], *msgptr;
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   const char*  filename = "message.dat";
   int		i, len, stat, tvalue = 2;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-t")) tvalue = atoi(argv[++i]);
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer -a | -u [ -v ] [ -o <filename>\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -t  choice tag value to encode\n");
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
   pu_setBuffer (&ctxt, msgbuf, sizeof(msgbuf), aligned);
   pu_setTrace (&ctxt, trace);

   /* Populate structure */

   memset (&testSequence, 0, sizeof(testSequence));
   testSequence.item_code = 29;
   testSequence.m.item_namePresent = TRUE;
   testSequence.item_name = "SHERRY";
   testSequence.m.urgencyPresent = TRUE;
   testSequence.urgency = high;
   testSequence.m._v3ExtPresent = TRUE;
   testSequence.alternate_item_code = 45;
   testSequence.m.alternate_item_namePresent = TRUE;
   testSequence.alternate_item_name = "PORT";

   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_TestSequence ("testSequence", &testSequence);
      printf ("\n");
   }

   /* Encode */

   if ((stat = asn1PE_TestSequence (&ctxt, &testSequence)) == 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         pu_hexdump (&ctxt);
         printf ("Binary dump:\n");
         pu_bindump (&ctxt, "testSequence");
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      return -1;
   }
  
   msgptr = pe_GetMsgPtr (&ctxt, &len);

   /* Write the encoded message out to the output file */

   stat = rtxFileWriteBinary (filename, msgptr, len);
   if (0 != stat) {
      printf ("Error writing encoded data to file %s\n", filename);
   }

   rtFreeContext (&ctxt);

   return 0;

}
