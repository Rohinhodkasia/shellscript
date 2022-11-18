/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "BigInt.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

int main (int argc, char** argv)
{
   Dss_Parms    dss;
   OSCTXT	ctxt;
   OSOCTET*     msgptr;
   int		i, len;
   FILE*        fp;
   const char*  filename = "message.dat";
   OSBOOL       verbose = FALSE, trace = TRUE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Encode in a dynamic buffer */
   if (rtInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);
   xe_setp (&ctxt, 0, 0);

   /* Populate structure of generated type */

   dss.p = "0x112233445566778899aabbccddeeff";
   dss.q = "-1234567890123456789012345678901234567890";
   dss.g = "1234567890123456789012345678901234567890";

   if ((len = asn1E_Dss_Parms (&ctxt, &dss, ASN1EXPL)) > 0)
   {
      msgptr = xe_getp (&ctxt);

      if (trace) {
         if (XU_DUMP (msgptr) != 0) 
            printf ("dump of ASN.1 message failed.");
      }
   }
   else {
      rtxErrPrint (&ctxt);
      return -1;
   }
  
   /* Write the encoded message out to the output file */

   if (fp = fopen (filename, "wb")) {
      fwrite (msgptr, 1, len, fp);
      fclose (fp);
   }
   else {
      printf ("Error opening %s for write access\n", filename);
      return -1;
   }

   rtFreeContext (&ctxt);
   return 0;

}
