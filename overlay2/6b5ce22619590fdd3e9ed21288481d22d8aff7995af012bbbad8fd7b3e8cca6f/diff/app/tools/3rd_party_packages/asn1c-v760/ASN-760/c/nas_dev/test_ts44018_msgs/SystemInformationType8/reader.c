/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include "TS44018Msgs.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxPrintStream.h"

int DecSI8 (OSCTXT* pctxt, const OSOCTET* msgbuf, OSSIZE len, OSBOOL verbose)
{
   TS44018IE_SI8_Rest_Octets data;
   int          ret;

   /* Set message buffer pointer. Cast away const-ness to avoid warning. */

   ret = rtxCtxtSetBufPtr (pctxt, (OSOCTET*) msgbuf, len);
   if (0 != ret) {
      printf ("rtxCtxtSetBufPtr failed; status = %d\n", ret);
      rtxErrPrint (pctxt);
      return ret;
   }

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (pctxt);
   }

   /* Call decode function */
   /* Here we're assuming ACS = 1, meaning SI4_Rest_Octets_O is present */
   ret = NASDec_TS44018IE_SI8_Rest_Octets (pctxt, &data, TRUE );

   if (verbose) {
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (pctxt->pBitFldList, "");
      printf ("\n");
   }

   if (0 != ret) {
      printf ("decode SI 8 Rest Octets failed; status = %d\n", ret);
      rtxErrPrint (pctxt);
   }

   /* Print fields */

   if (verbose) {
      /* Invoke generated print-to-stream function */
      asn1PrtToStrm_TS44018IE_SI8_Rest_Octets(pctxt, "SI8 Rest Octets", &data);
   }

   return 0;
}


int main (int argc, char** argv)
{
   TS44018Msg_L2_PSEUDO_LEN_PDU data;
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

   ret = NASDec_TS44018Msg_L2_PSEUDO_LEN_PDU (&ctxt, &data);

   if (verbose) {
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "");
      printf ("\n");
   }

   if (0 != ret) {
      printf ("decode PDU failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
   }

   /* Print fields */

   if (verbose) {
      /* Register print-to-stream callback function */
      rtxSetPrintStream (&ctxt, &rtxPrintStreamToStdoutCB, 0);

      /* Invoke generated print-to-stream function */
      asn1PrtToStrm_TS44018Msg_L2_PSEUDO_LEN_PDU (&ctxt, "PDU", &data);
   }

   DecSI8 (&ctxt, data.restOctets.u.obj_SystemInformationType8->data,
            data.restOctets.u.obj_SystemInformationType8->numocts, verbose);

   rtxFreeContext (&ctxt);

   return 0;
}
