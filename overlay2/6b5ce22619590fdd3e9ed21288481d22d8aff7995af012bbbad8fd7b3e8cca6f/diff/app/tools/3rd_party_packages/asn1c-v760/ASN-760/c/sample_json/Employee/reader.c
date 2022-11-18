/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxStreamFile.h"

int main (int argc, char** argv)
{
   PersonnelRecord employee;
   OSCTXT       ctxt;
   int          i, stat;
   const char*  filename = "message.json";
   OSBOOL       trace = TRUE, verbose = FALSE;

   DECLARE_MEMLEAK_DETECTOR;

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

   /* Init context structure */

   if (rtInitContext (&ctxt) != 0) {
      printf ("Error initializing context\n");
      return -1;
   }
   stat = rtxStreamFileCreateReader (&ctxt, filename);

   if (stat != 0) {
      printf ("Unable to open %s for reading.\n", filename);
      rtxErrPrint(&ctxt);
      rtFreeContext(&ctxt);
      return stat;
   }

   rtxSetDiag (&ctxt, verbose);

   /* Decode */
   asn1Init_PersonnelRecord (&employee);

   stat = asn1JsonDec_PersonnelRecord (&ctxt, &employee);
   if (0 != stat) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   if (trace) {
      printf ("Decode of PersonnelRecord was successful\n");
      printf ("Decoded record:\n");
      asn1Print_PersonnelRecord ("Employee", &employee);
   }

   rtFreeContext (&ctxt);

   return 0;
}
