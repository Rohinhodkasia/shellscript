/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxFile.h"

int main (int argc, char** argv)
{
   PersonnelRecord employee;
   OSCTXT       ctxt;
   OSOCTET*     pMsgBuf;
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = 1;
   const char*  filename = "message.dat";
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
            printf ("usage: reader -a | -u [-v] [-i <filename>]\n");
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

   stat = rtxFileReadBinary(&ctxt, filename, &pMsgBuf, &len);
   if (0 != stat) {
      printf ("Error opening %s for read access\n", filename);
      return stat;
   }

   pu_setBuffer (&ctxt, pMsgBuf, len, aligned);
   pu_setTrace (&ctxt, trace);

   asn1Init_PersonnelRecord (&employee);

   /* Call compiler generated decode function */

   stat = asn1PD_PersonnelRecord (&ctxt, &employee);

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      pu_bindump (&ctxt, "employee");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode of PersonnelRecord was successful\n");
         asn1Print_PersonnelRecord ("Employee", &employee);
      }
   }
   else {
       printf ("decode of PersonnelRecord failed\n");
       rtxErrPrint (&ctxt);
       return -1;
   }

   rtFreeContext (&ctxt);

   return 0;
}
