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
   TS44018Msg_MeasurementReport data;
   TS44018Msg_MeasurementReport* pvalue = &data;

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
   pdu.msgType = ASN1V_ts44018Msg_mt_MeasurementReport;
   pdu.data.t = T_TS44018Msgs_UL_SACCH_Messages_obj_MeasurementReport;
   pdu.data.u.obj_MeasurementReport = pvalue;


   asn1Init_TS44018Msg_MeasurementReport (pvalue);

   pvalue->measurementResults.ba_used = 0;

   pvalue->measurementResults.dtx_used = 0;

   pvalue->measurementResults.rxlev_full_serving_cell = 32;

   pvalue->measurementResults.a3G_BA_USED = 0;

   pvalue->measurementResults.meas_valid = 0;

   pvalue->measurementResults.rxlev_sub_serving_cell = 40;

   pvalue->measurementResults.si23_ba_used = 0;

   pvalue->measurementResults.rxqual_full_serving_cell = 0;

   pvalue->measurementResults.rxqual_sub_serving_cell = 3;

   pvalue->measurementResults.no_ncell_m = 0;

   /* zero elements */

   pvalue->measurementResults.component_11.u.choice_2.m.utran_CSG_Measurement_ReportPresent = 1;

   pvalue->measurementResults.component_11.u.choice_2.utran_CSG_Measurement_Report.utran_cgi = 29672;

   pvalue->measurementResults.component_11.u.choice_2.utran_CSG_Measurement_Report.m.plmn_idPresent = 1;

   pvalue->measurementResults.component_11.u.choice_2.utran_CSG_Measurement_Report.plmn_id.mcc = 1183;

   pvalue->measurementResults.component_11.u.choice_2.utran_CSG_Measurement_Report.plmn_id.mnc = 3422;

   pvalue->measurementResults.component_11.u.choice_2.utran_CSG_Measurement_Report.csg_id = 30717;

   pvalue->measurementResults.component_11.u.choice_2.utran_CSG_Measurement_Report.access_Mode = 0;

   pvalue->measurementResults.component_11.u.choice_2.utran_CSG_Measurement_Report.reporting_quantity = 14;

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
