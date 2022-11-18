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
   TS44018Msg_RR_Short_PD_PDU pdu;
   TS44018Msg_Enhanced_Measurement_report data;
   TS44018Msg_Enhanced_Measurement_report* pvalue = &data;

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

   asn1Init_TS44018Msg_RR_Short_PD_PDU (&pdu);
   pdu.rr_short_PD = 0;
   pdu.msgType = ASN1V_ts44018Msg_mt_enhanced_measurement_report;
   pdu.short_layer_2_header = 0;
   pdu.data.t = T_TS44018Msgs_RR_Short_PD_Messages_obj_enhanced_measurement_report;
   pdu.data.u.obj_enhanced_measurement_report = pvalue;


   asn1Init_TS44018Msg_Enhanced_Measurement_report (pvalue);

   pvalue->ba_used = 0;

   pvalue->a3G_BA_USED = 0;

   pvalue->bsic_Seen = 0;

   pvalue->scale = 0;

   pvalue->m.serving_cell_dataPresent = 1;

   pvalue->serving_cell_data.dtx_used = 0;

   pvalue->serving_cell_data.rxlev_val = 4;

   pvalue->serving_cell_data.rx_qual_full = 6;

   pvalue->serving_cell_data.mean_bep = 19;

   pvalue->serving_cell_data.cv_bep = 4;

   pvalue->serving_cell_data.nbr_rcvd_blocks = 7;

   pvalue->m.component_7Present = 0;

   pvalue->m.component_8Present = 1;

   pvalue->component_8.bitmap_length = 3;

   pvalue->component_8.component_2.n = 4;

   pvalue->component_8.component_2.elem[0].m.reporting_quantityPresent = 1;
   pvalue->component_8.component_2.elem[0].reporting_quantity = 22;
   pvalue->component_8.component_2.elem[1].m.reporting_quantityPresent = 0;
   pvalue->component_8.component_2.elem[2].m.reporting_quantityPresent = 1;
   pvalue->component_8.component_2.elem[2].reporting_quantity = 33;
   pvalue->component_8.component_2.elem[3].m.reporting_quantityPresent = 0;

   pvalue->component_8.m.e_UTRAN_Measurement_ReportPresent = 1;

   pvalue->component_8.e_UTRAN_Measurement_Report.n_e_utran = 0;

   pvalue->component_8.e_UTRAN_Measurement_Report.component_2.n = 1;

   pvalue->component_8.e_UTRAN_Measurement_Report.component_2.elem[0].e_utran_frequency_index = 2;

   pvalue->component_8.e_UTRAN_Measurement_Report.component_2.elem[0].cell_identity = 376;

   pvalue->component_8.e_UTRAN_Measurement_Report.component_2.elem[0].reporting_quantity = 24;

   pvalue->component_8.m.component_4Present = 1;

   pvalue->component_8.component_4.m.utran_CSG_Measurement_ReportPresent = 1;

   pvalue->component_8.component_4.utran_CSG_Measurement_Report.utran_cgi = 10591;

   pvalue->component_8.component_4.utran_CSG_Measurement_Report.m.plmn_idPresent = 1;

   pvalue->component_8.component_4.utran_CSG_Measurement_Report.plmn_id.mcc = 973;

   pvalue->component_8.component_4.utran_CSG_Measurement_Report.plmn_id.mnc = 3185;

   pvalue->component_8.component_4.utran_CSG_Measurement_Report.csg_id = 4872;

   pvalue->component_8.component_4.utran_CSG_Measurement_Report.access_Mode = 0;

   pvalue->component_8.component_4.utran_CSG_Measurement_Report.reporting_quantity = 52;

   pvalue->component_8.component_4.m.si23_ba_usedPresent = 1;
   pvalue->component_8.component_4.si23_ba_used = 0;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_RR_Short_PD_PDU (&ctxt, &pdu);
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
