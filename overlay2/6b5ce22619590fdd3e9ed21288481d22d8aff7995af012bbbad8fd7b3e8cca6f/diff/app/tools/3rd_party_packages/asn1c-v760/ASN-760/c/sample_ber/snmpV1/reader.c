/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "RFC1157-SNMP.h"
#include "RFC1213-MIB.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxFile.h"

int main (int argc, char** argv)
{
   Message      snmpMessage;
   OSCTXT	ctxt;
   OSOCTET*	msgbuf;
   OSSIZE       len;
   int		i, stat;
   const char*  filename = "message.dat";
   OSBOOL       trace = TRUE, verbose = FALSE;

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

   /* Init context structure */

   if (rtInitContext (&ctxt) != 0) {
      printf ("Error initializing context\n");
      return -1;
   }

   rtxSetDiag (&ctxt, verbose);

   /* Read input file into a memory buffer */

   stat = rtxFileReadBinary (&ctxt, filename, &msgbuf, &len);
   if (0 != stat) {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }

   stat = xd_setp64 (&ctxt, msgbuf, len, 0, 0, 0);
   if (0 != stat) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   /* Decode */

   stat = asn1D_Message (&ctxt, &snmpMessage, ASN1EXPL, 0);
   if (stat == 0) {
      if (trace) {
         printf ("Decode was successful\n");
         printf ("Decoded record:\n");
         asn1Print_Message ("snmpMessage", &snmpMessage);
      }
   }
   else {
      printf ("decode of SNMP message failed\n");
      rtxErrPrint (&ctxt);
      return -1;
   }

   rtFreeContext (&ctxt);
   return 0;
}

