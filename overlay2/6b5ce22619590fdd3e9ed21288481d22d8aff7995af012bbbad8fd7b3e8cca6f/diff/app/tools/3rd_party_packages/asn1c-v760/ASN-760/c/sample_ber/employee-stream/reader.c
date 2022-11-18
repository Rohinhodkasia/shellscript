/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results.                             */

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxStreamFile.h"
#include "rtxsrc/rtxDiag.h"

int main (int argc, char** argv)
{
   PersonnelRecord employee;
   OSCTXT	ctxt;
   int		i, len, stat;
   const char*  filename = "message.dat";
   OSBOOL       trace = TRUE, verbose = FALSE;
   ASN1TAG      tag;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [ -v ] [ -i <filename> ]\n");
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
   rtxSetDiag (&ctxt, verbose);

   /* Open the input stream to read data */

   stat = rtxStreamFileCreateReader (&ctxt, filename);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   if ((stat = berDecStrmPeekTagAndLen (&ctxt, &tag, &len)) != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   /* Decode */

   if (tag == TV_PersonnelRecord) {

      /* Call compiler generated decode function */

      stat = asn1BSD_PersonnelRecord (&ctxt, &employee, ASN1EXPL, 0);
      if (stat == 0) {
         if (trace) {
            printf ("Decode of PersonnelRecord was successful\n");
            printf ("Decoded record:\n");
            asn1Print_PersonnelRecord ("Employee", &employee);
         }
      }
      else {
         printf ("decode of PersonnelRecord failed\n");
         rtxErrPrint (&ctxt);
         return -1;
      }
   }
   else {
      printf ("unexpected tag %hx received\n", tag);
   }

   berStrmFreeContext (&ctxt);

   return 0;
}
