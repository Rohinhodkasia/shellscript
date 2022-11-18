/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.0A, Date: 20-May-2006.
 */
#include "Cap.h"
#include "rtxsrc/rtxCommon.h"

#include <stdio.h>
#include <stdlib.h>
#include "rtxsrc/rtxStreamFile.h"

int main (int argc, char** argv)
{
   Alert data;
   OSCTXT      ctxt;
   OSBOOL      trace = TRUE, verbose = FALSE;
   const char* filename = "message.xml";
   int         i, stat;

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

   /* Initialize context structure */
   stat = rtXmlInitContext (&ctxt);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Decode */
   stat = rtxStreamFileOpen (&ctxt, filename, OSRTSTRMF_INPUT);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }

   /* Call compiler generated decode function */
   stat = XmlDec_Alert_PDU (&ctxt, &data);
   if (stat != 0) {
      printf ("decode of data failed\n");
      rtxErrPrint (&ctxt);
      rtxStreamClose (&ctxt);
      return -1;
   }
   if (trace) {
      asn1Print_Alert ("Data", &data);
   }
   rtFreeContext (&ctxt);

   return 0;
}
