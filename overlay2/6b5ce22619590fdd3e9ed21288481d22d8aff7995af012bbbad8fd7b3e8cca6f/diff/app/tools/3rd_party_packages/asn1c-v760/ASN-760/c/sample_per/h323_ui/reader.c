/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.1.A, Date: 02-Nov-2016.
 */
#include "H323-MESSAGES.h"
#include "rtxsrc/rtxCommon.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
   H225H323_UserInformation data;
   OSCTXT      ctxt;
   OSOCTET*    pMsgBuf;
   OSBOOL      aligned = !FALSE;
   OSBOOL      trace = TRUE, verbose = FALSE;
   const char* filename = "message.dat";
   int         i, stat;
   OSSIZE      len;

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [-v] [-i <filename>] [-a|-u] [-notrace]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -notrace  do not display trace info\n");
            return 1;
         }
      }
   }

   /* Initialize context structure */
   stat = rtInitContext (&ctxt);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Read input file into a memory buffer */
   if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }

   pu_setBuffer (&ctxt, pMsgBuf, len, aligned);
   pu_setTrace (&ctxt, trace);

   asn1Init_H225H323_UserInformation (&data);

   /* Call compiler generated decode function */
   stat = asn1PD_H225H323_UserInformation (&ctxt, &data);
   if (stat != 0) {
      printf ("decode of data failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return -1;
   }

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      pu_bindump (&ctxt, "data");
      printf ("\n");
      asn1Print_H225H323_UserInformation ("Data", &data);
   }

   rtFreeContext (&ctxt);

   return 0;
}
