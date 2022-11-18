/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "ParamType.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxFile.h"

#define MAXMSGLEN 1024

int main (int argc, char** argv)
{
   SignedName   signedName;
   OSCTXT	ctxt;
   OSOCTET*	msgbuf;
   OSBOOL       verbose = FALSE, trace = TRUE;
   const char*  filename = "message.dat";
   int          i, stat;
   OSSIZE       len;

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

   /* Create a new context structure */

   if (rtInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Read input file into a memory buffer */

   stat = rtxFileReadBinary(&ctxt, filename, &msgbuf, &len);
   if (0 != stat) {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }
   if (trace) {
      printf ("Read " OSSIZEFMT " bytes from file %s..\n", len, filename);
   }
   pu_setBuffer (&ctxt, msgbuf, len, TRUE);
   pu_setTrace (&ctxt, trace);
   
   asn1Init_SignedName (&signedName);

   /* Call compiler generated decode function */

   stat = asn1PD_SignedName (&ctxt, &signedName);

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      pu_bindump (&ctxt, "signedName");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode of SignedName was successful\n");
         asn1Print_SignedName ("signedName", &signedName);
      }
   }
   else {
       printf ("decode of SignedName failed\n");
       rtxErrPrint (&ctxt);
   }

   rtFreeContext (&ctxt);

   return stat;
}
