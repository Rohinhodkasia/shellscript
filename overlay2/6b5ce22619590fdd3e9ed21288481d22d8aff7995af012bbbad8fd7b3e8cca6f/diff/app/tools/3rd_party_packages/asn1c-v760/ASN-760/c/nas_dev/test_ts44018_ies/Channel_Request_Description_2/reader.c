/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include "TS44018IES.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxPrintStream.h"

int main (int argc, char** argv)
{
   TS44018IE_Channel_Request_Description_2 data;
   OSCTXT	ctxt;
   OSOCTET*     msgbuf;
   const char*  filename = "message.dat";
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

   if (verbose) {
      printf ("\nReading message file %s..\n", filename);
   }
   /* Read input file into a memory buffer */

   ret = rtxFileReadBinary (&ctxt, filename, &msgbuf, &len);
   if (0 != ret) {
      printf ("Error opening %s for read access\n", filename);
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

   ret = NASDec_TS44018IE_Channel_Request_Description_2 (&ctxt, &data);

   if (verbose) {
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "Channel_Request_Description_2");
      printf ("\n");
   }

   if (0 != ret) {
      printf ("decode Channel_Request_Description_2 failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }

   /* Print fields */

   if (verbose) {
      /* Register print-to-stream callback function */
      rtxSetPrintStream (&ctxt, &rtxPrintStreamToStdoutCB, 0);

      /* Invoke generated print-to-stream function */
      asn1PrtToStrm_TS44018IE_Channel_Request_Description_2
         (&ctxt, "Channel_Request_Description_2", &data);
   }

   rtxFreeContext (&ctxt);

   return 0;
}
