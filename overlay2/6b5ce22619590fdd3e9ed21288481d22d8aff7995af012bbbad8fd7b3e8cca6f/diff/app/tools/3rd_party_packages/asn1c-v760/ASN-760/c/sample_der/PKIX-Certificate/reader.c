#include "PKIX1Explicit-2009.h"
#include "AlgorithmInformation-2009.h"
#include "PKIX1Implicit-2009.h"
#include "rtxsrc/rtxCommon.h"

#include <stdio.h>
#include <stdlib.h>

#define MAXREADLEN 1024

int main (int argc, char** argv)
{
   Certificate data;
   OSCTXT      ctxt;
   OSOCTET*    pMsgBuf;
   OSBOOL      trace = TRUE, verbose = FALSE;
   const char* filename = "message.dat";
   int         i, stat;
   OSSIZE      len;

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [-v] [-i <filename>] [-notrace]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
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

   /* Read input file */
   if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }

   stat = xd_setp64 (&ctxt, pMsgBuf, len, 0, 0, 0);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   asn1Init_Certificate (&data);

   /* Call compiler generated decode function */
   stat = asn1D_Certificate (&ctxt, &data, ASN1EXPL, 0);
   if (stat != 0) {
      printf ("decode of data failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return -1;
   }
   if (trace) {
      asn1Print_Certificate ("Data", &data);
   }
   rtFreeContext (&ctxt);

   return 0;
}
