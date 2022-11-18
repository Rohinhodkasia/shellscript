/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include "TS24008IES.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxPrintStream.h"

int main (int argc, char** argv)
{
   TS24008IE_MobileIdentity data;
   OSCTXT	ctxt;
   OSOCTET*     msgbuf;
   const char*  filenames[] = {
      "message_imsi.dat",
      "message_imei.dat",
      "message_imeisv.dat",
      "message_tmsi.dat",
      "message_tmgi.dat"
   } ;
   int          i, ret;
   OSSIZE       len;
   OSBOOL       verbose = FALSE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else {
            printf ("usage: reader [-v]\n");
            printf ("   -v  verbose mode: print trace info\n");
            return 0;
         }
      }
   }

   /* Initialize context structure */

   ret = rtInitContext (&ctxt);
   if (0 != ret) {
      printf ("rtInitContext failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }
   rtxSetDiag (&ctxt, verbose);

   for (i = 0; i < 5; i++) {
      if (verbose) {
         printf ("\nReading message file %s..\n", filenames[i]);
      }
      /* Read input file into a memory buffer */

      ret = rtxFileReadBinary (&ctxt, filenames[i], &msgbuf, &len);
      if (0 != ret) {
         printf ("Error opening %s for read access\n", filenames[i]);
         rtxErrPrint (&ctxt);
         return ret;
      }

      /* Set message buffer pointer */

      ret = rtxCtxtSetBufPtr (&ctxt, msgbuf, len);
      if (0 != ret) {
         printf ("rtxCtxtSetBufPtr failed; status = %d\n", ret);
         rtxErrPrint (&ctxt);
         return ret;
      }

      /* Enable bit tracing */

      if (verbose) {
         rtxDiagCtxtBitFieldListInit (&ctxt);
      }

      /* Call decode function */

      ret = NASDec_TS24008IE_MobileIdentity (&ctxt, &data);

      if (verbose) {
         printf ("Bit fields:\n");
         rtxDiagBitTracePrint (ctxt.pBitFldList, "");
         printf ("\n");
      }

      if (0 != ret) {
         printf ("decode MobileIdentity failed; status = %d\n", ret);
         rtxErrPrint (&ctxt);
         return ret;
      }

      /* Print fields */

      if (verbose) {
         /* Register print-to-stream callback function */
         rtxSetPrintStream (&ctxt, &rtxPrintStreamToStdoutCB, 0);

         /* Invoke generated print-to-stream function */
         asn1PrtToStrm_TS24008IE_MobileIdentity
            (&ctxt, "MobileIdentity", &data);
      }
   }

   rtxFreeContext (&ctxt);

   return 0;
}
