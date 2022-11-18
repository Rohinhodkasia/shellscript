#include "VersionBrackets.h"
#include "rtxsrc/rtxCommon.h"

#include <stdio.h>
#include <stdlib.h>
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

int main (int argc, char** argv)
{
   int        i, stat;
   OSSIZE     len;
   OSBOOL     aligned = TRUE;
   OSBOOL     trace = TRUE;
   OSBOOL     verbose = FALSE;
   const char* filename = "message.dat";
   const OSOCTET* msgptr;

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer -a | -u [-v] [-o <filename>]  [-notrace]\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 1;
         }
      }
   }

   /* Create an instance of the compiler generated class.
      This example uses a dynamic message buffer..*/
   ASN1PEREncodeBuffer encodeBuffer (aligned);
   ASN1T_TestSequence testSequence;
   ASN1C_TestSequence TestSequencePDU (encodeBuffer, testSequence);

   testSequence.item_code = 29;
   testSequence.m.item_namePresent = TRUE;
   testSequence.item_name = "SHERRY";
   testSequence.m.urgencyPresent = TRUE;
   testSequence.urgency = TestSequence_urgency::high;
   testSequence.m._v3ExtPresent = TRUE;
   testSequence.alternate_item_code = 45;
   testSequence.m.alternate_item_namePresent = TRUE;
   testSequence.alternate_item_name = "PORT";

   // Make a copy of the test object
   ASN1T_TestSequence testSequence2;
   TestSequencePDU.getCopy (&testSequence2);

   // Compare copy with original
   char errbuf[1024];
   if (!TestSequencePDU.Equals (&testSequence2, errbuf, sizeof(errbuf))) {
      printf ("Objects are not equal: %s\n", errbuf);
   }

   /* Encode */
   encodeBuffer.setTrace (trace);
   encodeBuffer.setDiag (verbose);

   if ((stat = TestSequencePDU.Encode ()) == 0)
   {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.hexDump ();
         printf ("Binary dump:\n");
         encodeBuffer.binDump ("Data");
      }
      msgptr = encodeBuffer.getMsgPtr ();
      len = encodeBuffer.getMsgLen ();
   }
   else
   {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      return (-1);
   }
   /* Write the encoded message out to the output file */
   stat = rtxFileWriteBinary (filename, msgptr, len);
   if (stat < 0) {
      printf ("Write to file failed\n");
      encodeBuffer.printErrorInfo();
      return stat;
   }

   return 0;
}
