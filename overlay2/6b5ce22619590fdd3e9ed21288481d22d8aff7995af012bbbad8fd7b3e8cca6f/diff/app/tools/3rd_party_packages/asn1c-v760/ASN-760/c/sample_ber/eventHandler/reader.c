/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "printHandler.h"
#include "rtsrc/asn1CEvtHndlr.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

int main (int argc, char** argv)
{
   PersonnelRecord employee;
   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN];
   OSBOOL       verbose = FALSE;
   OSBOOL       trace = TRUE;
   FILE*        fp;
   const char*  filename = "message.dat";
   int		i, stat;
   OSSIZE       len;
   Asn1NamedCEventHandler printHandler;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
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

   /* Read input file into a memory buffer */

   if (fp = fopen (filename, "rb")) {
      len = fread (msgbuf, 1, sizeof(msgbuf), fp);
   }
   else {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }
   /* initialize print handler */
   initializePrintHandler(&printHandler, "employee");

   /* Create a new context structure */
   if (rtInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);
  
   stat = xd_setp64 (&ctxt, msgbuf, len, 0, 0, 0);

   /* Add event handler to list */
   rtAddEventHandler (&ctxt, &printHandler);

   /* Call compiler generated decode function */
   stat = asn1D_PersonnelRecord (&ctxt, &employee, ASN1EXPL, 0);

   if (stat == 0) {
      if (trace) {
         printf ("decode of PersonnelRecord was successful\n");
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
