/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include "TS24008Msgs.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxPrintStream.h"

int main (int argc, char** argv)
{
   TS24008Msg_PDU data;
   OSCTXT	ctxt;
   OSOCTET*     msgbuf;
   const char*  filename = "message.dat";
   const char*  hexmsg = 0;
   int          i, ret;
   OSSIZE       len;
   OSBOOL       verbose = FALSE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-hex")) {
            if (i < argc) {
               hexmsg = argv[++i];
            }
            else {
               printf ("hex message text argument missing\n");
               return -1;
            }
         }
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

   if (0 != hexmsg) {
      int res = rtxHexCharsToBinCount (hexmsg, 0);
      if (res >= 0) {
         msgbuf = (OSOCTET*) rtxMemAlloc (&ctxt, res);
         if (0 == msgbuf) return RTERR_NOMEM;

         res = rtxHexCharsToBin (hexmsg, 0, msgbuf, res);
         if (res < 0) return res;
         else len = (OSSIZE) res;
      }
   }
   else {
      /* Read input file into a memory buffer */

      ret = rtxFileReadBinary (&ctxt, filename, &msgbuf, &len);
      if (0 != ret) {
         printf ("Error opening %s for read access\n", filename);
         rtxErrPrint (&ctxt);
         return ret;
      }
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

   ret = NASDec_TS24008Msg_PDU (&ctxt, &data);

   if (verbose) {
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "");
      printf ("\n");
   }

   if (0 != ret) {
      printf ("decode PDU failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }

   /* Print fields */

   if (verbose) {
      /* Register print-to-stream callback function */
      rtxSetPrintStream (&ctxt, &rtxPrintStreamToStdoutCB, 0);

      /* Invoke generated print-to-stream function */
      asn1PrtToStrm_TS24008Msg_PDU (&ctxt, "PDU", &data);
   }

   rtxFreeContext (&ctxt);

   return 0;
}
