#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

int main (int argc, char** argv)
{
   TS44018Msg_UL_SACCH_PDU pdu;
   TS44018Msg_ExtendedMeasurementReport data;
   TS44018Msg_ExtendedMeasurementReport* pvalue = &data;

   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN], *msgptr;
   const char*  filename = "message.dat";
   OSSIZE       len;
   int		i, ret;
   OSBOOL       verbose = FALSE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else {
            printf ("usage: writer [-v]\n");
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

   /* Populate data structure */

   asn1Init_TS44018Msg_UL_SACCH_PDU (&pdu);
   pdu.l3HdrOpts.t = 1;
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;
   pdu.msgType = ASN1V_ts44018Msg_mt_ExtendedMeasurementReport;
   pdu.data.t = T_TS44018Msgs_UL_SACCH_Messages_obj_ExtendedMeasurementReport;
   pdu.data.u.obj_ExtendedMeasurementReport = pvalue;

   pvalue->extendedMeasurementResults.sc_used = 0;

   pvalue->extendedMeasurementResults.dtx_used = 0;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[0] = 47;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[1] = 56;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[2] = 16;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[3] = 52;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[4] = 60;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[5] = 5;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[6] = 45;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[7] = 14;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[8] = 21;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[9] = 47;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[10] = 30;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[11] = 56;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[12] = 44;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[13] = 62;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[14] = 61;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[15] = 14;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[16] = 29;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[17] = 15;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[18] = 36;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[19] = 53;

   pvalue->extendedMeasurementResults.rxlev_carrier.elem[20] = 18;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_UL_SACCH_PDU (&ctxt, &pdu);
   if (0 != ret) {
      printf ("encode PDU failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }
   /* Verify buffer is byte-aligned */
   OSRTASSERT (ctxt.buffer.bitOffset == 8 || ctxt.buffer.bitOffset == 0);

   msgptr = rtxCtxtGetMsgPtr (&ctxt);
   len = rtxCtxtGetMsgLen (&ctxt);


   if (verbose) {
      printf ("Encoding was successful\n");
      printf ("Hex dump of encoded record:\n");
      rtxHexDump (msgptr, len);
      printf ("\n");
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "");
      printf ("\n");
   }

   /* Write encoded message to output file */

   ret = rtxFileWriteBinary (filename, msgptr, len);
   if (0 != ret) {
      printf ("rtxFileWriteBinary failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }

   rtxFreeContext (&ctxt);

   return 0;
}
