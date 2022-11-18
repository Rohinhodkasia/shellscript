/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "InfoObject.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

int main (int argc, char** argv)
{
   Iu_ReleaseCommand releaseCommand;
   ProtocolIE_Field* pField;
   Cause	cause;
   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN];
   OSBOOL       aligned = TRUE, trace = TRUE, verbose = FALSE;
   FILE*        fp;
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

   /* Read input file into a memory buffer */

   if (fp = fopen (filename, "rb")) {
      len = fread (msgbuf, 1, sizeof(msgbuf), fp);
   }
   else {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }

   /* Initialize context structure */

   if (rtInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);
   pu_setBuffer (&ctxt, msgbuf, len, aligned);
   pu_setTrace (&ctxt, trace);

   asn1Init_Iu_ReleaseCommand (&releaseCommand);

   /* Call compiler generated decode function */

   stat = asn1PD_Iu_ReleaseCommand (&ctxt, &releaseCommand);

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      pu_bindump (&ctxt, "releaseCommand");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode was successful\n");
         asn1Print_Iu_ReleaseCommand ("releaseCommand", &releaseCommand);
      }
   }
   else {
       printf ("decode failed\n");
       rtxErrPrint (&ctxt);
       return -1;
   }

   /* Now decode the open type field */

   pField = (ProtocolIE_Field*)
      releaseCommand.protocolIEs.head->data;

   rtxInitContextBuffer (&ctxt, 
                         (OSOCTET*)pField->value.data, 
                         pField->value.numocts);

   stat = asn1PD_Cause (&ctxt, &cause);

   if (stat == 0) {
      if (trace) {
         printf ("decode was successful\n");
         asn1Print_Cause ("cause", &cause);
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
