/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "Test.h"
#include "rtxsrc/rtxStreamFile.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

int main (int argc, char** argv)
{
   TestType     testData;
   OSCTXT	ctxt;
   int		i, stat;
   const char* filename = "message.xml";
   OSBOOL       verbose = FALSE, trace = TRUE;

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

   DECLARE_MEMLEAK_DETECTOR;

   /* Init context structure */

   if (rtXmlInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Decode */

   rtxStreamInit (&ctxt);
   stat = rtxStreamFileOpen (&ctxt, filename, OSRTSTRMF_INPUT);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }

   /* Call compiler generated decode function */
   stat = XmlDec_TestType_PDU (&ctxt, &testData);
   if (stat == 0) {
      if (trace) {
         printf ("Decode of TestType was successful\n");
         printf ("Decoded record:\n");
         asn1Print_TestType ("testData", &testData);
      }
   }
   else {
      printf ("decode of TestType failed\n");
      rtxErrPrint (&ctxt);
      rtxStreamClose (&ctxt);
      return -1;
   }

   rtxStreamClose (&ctxt);
   rtFreeContext (&ctxt);
   return 0;
}

