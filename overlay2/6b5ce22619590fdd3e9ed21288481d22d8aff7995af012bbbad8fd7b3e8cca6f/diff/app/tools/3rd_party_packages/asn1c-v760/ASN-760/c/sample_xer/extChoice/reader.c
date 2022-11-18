/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "ExtChoice.h"
#include "rtxsrc/rtxStreamFile.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

int main (int argc, char** argv)
{
   AliasAddressList msgData;
   OSCTXT	ctxt;
   int		i, stat;
   const char* filename = "message.xml";
   OSBOOL       verbose = FALSE, trace = TRUE;

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

   stat = XmlDec_AliasAddressList_PDU (&ctxt, &msgData);
   if (stat == 0) {
      if (trace) {
         printf ("Decode of AliasAddressList was successful\n");
         printf ("Decoded record:\n");
         asn1Print_AliasAddressList ("extChoice", &msgData);
      }
   }
   else {
      printf ("decode of AliasAddressList failed\n");
      rtxErrPrint (&ctxt);
      return -1;
   }

   rtxStreamClose (&ctxt);
   rtFreeContext (&ctxt);
   return 0;
}

