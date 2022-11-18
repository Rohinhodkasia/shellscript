#include "TS44018IES.h"
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
   TS44018IE_SI13_Rest_Octets value;
   TS44018IE_SI13_Rest_Octets* pvalue = &value;
   OSCTXT	ctxt;
   OSCTXT*  pctxt = &ctxt;
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

   asn1Init_TS44018IE_SI13_Rest_Octets (pvalue);
   pvalue->m.component_1Present = 1;

   pvalue->component_1.bcch_change_mark = 3;

   pvalue->component_1.si_change_field = 9;

   pvalue->component_1.m.component_3Present = 1;

   pvalue->component_1.component_3.si13_change_mark = 1;

   pvalue->component_1.component_3.gprs_Mobile_Allocation.hsn = 7;

   pvalue->component_1.component_3.gprs_Mobile_Allocation.rfl_number_list.n = 8;
   pvalue->component_1.component_3.gprs_Mobile_Allocation.rfl_number_list.elem = rtxMemAllocArrayZ (pctxt, 8, OSUINT8);
   pvalue->component_1.component_3.gprs_Mobile_Allocation.rfl_number_list.elem[0] = 9;

   pvalue->component_1.component_3.gprs_Mobile_Allocation.rfl_number_list.elem[1] = 9;

   pvalue->component_1.component_3.gprs_Mobile_Allocation.rfl_number_list.elem[2] = 11;

   pvalue->component_1.component_3.gprs_Mobile_Allocation.rfl_number_list.elem[3] = 5;

   pvalue->component_1.component_3.gprs_Mobile_Allocation.rfl_number_list.elem[4] = 0;

   pvalue->component_1.component_3.gprs_Mobile_Allocation.rfl_number_list.elem[5] = 8;

   pvalue->component_1.component_3.gprs_Mobile_Allocation.rfl_number_list.elem[6] = 10;

   pvalue->component_1.component_3.gprs_Mobile_Allocation.rfl_number_list.elem[7] = 8;

   pvalue->component_1.component_3.gprs_Mobile_Allocation.component_3.t =  2;
   pvalue->component_1.component_3.gprs_Mobile_Allocation.component_3.u.choice_2.n = 3;
   pvalue->component_1.component_3.gprs_Mobile_Allocation.component_3.u.choice_2.elem = rtxMemAllocArrayZ (pctxt, 3, OSUINT8);
   pvalue->component_1.component_3.gprs_Mobile_Allocation.component_3.u.choice_2.elem[0] = 56;

   pvalue->component_1.component_3.gprs_Mobile_Allocation.component_3.u.choice_2.elem[1] = 47;

   pvalue->component_1.component_3.gprs_Mobile_Allocation.component_3.u.choice_2.elem[2] = 62;

   pvalue->component_1.component_4.t =  1;

   pvalue->component_1.component_4.u.choice_1.rac = 94;

   pvalue->component_1.component_4.u.choice_1.spgc_ccch_sup = 0;

   pvalue->component_1.component_4.u.choice_1.priority_access_thr = 0;

   pvalue->component_1.component_4.u.choice_1.network_control_order = 1;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.nmo = 1;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.t3168 = 6;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.t3192 = 2;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.drx_timer_max = 3;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.access_burst_type = 0;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.control_ack_type = 0;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.bs_cv_max = 0;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.m.component_8Present = 1;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_8.pan_dec = 4;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_8.pan_inc = 4;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_8.pan_max = 3;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.m.component_9Present = 1;
   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Length = 0; /* length will be calculated */

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.m.component_1Present = 1;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.component_1.m.component_1Present = 1;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.component_1.component_1.egprs_packet_channel_request = 0;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.component_1.component_1.bep_period = 6;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.component_1.pfc_feature_mode = 0;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.component_1.dtm_support = 0;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.component_1.bss_paging_coordination = 0;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.m.component_2Present = 1;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.component_2.ccn_active = 0;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.component_2.nw_ext_utbf = 0;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.m.component_3Present = 1;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.component_3.multiple_tbf_capability = 0;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.component_3.ext_utbf_nodata = 0;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.component_3.dtm_enhancements_capability = 0;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.component_3.m.component_4Present = 1;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.component_3.component_4.dedicated_mode_mbms_notification_support = 0;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.component_3.component_4.mnci_support = 0;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.m.reduced_latency_accessPresent = 1;
   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.reduced_latency_access = 0;

   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.m.nmo_i_alternatePresent = 1;
   pvalue->component_1.component_4.u.choice_1.gprs_Cell_Options.component_9.extension_Information.nmo_i_alternate = 0;

   pvalue->component_1.component_4.u.choice_1.gprs_Power_Control_Parameters.alpha = 8;

   pvalue->component_1.component_4.u.choice_1.gprs_Power_Control_Parameters.t_avg_w = 16;

   pvalue->component_1.component_4.u.choice_1.gprs_Power_Control_Parameters.t_avg_t = 30;

   pvalue->component_1.component_4.u.choice_1.gprs_Power_Control_Parameters.pc_meas_chan = 0;

   pvalue->component_1.component_4.u.choice_1.gprs_Power_Control_Parameters.n_avg_i = 13;

   pvalue->component_1.m.component_5Present = 1;

   pvalue->component_1.component_5.sgsnr = 0;

   pvalue->component_1.component_5.m.component_2Present = 1;

   pvalue->component_1.component_5.component_2.si_status_ind = 0;

   pvalue->component_1.component_5.component_2.m.component_2Present = 1;

   pvalue->component_1.component_5.component_2.component_2.m.lb_ms_txpwr_max_cchPresent = 1;
   pvalue->component_1.component_5.component_2.component_2.lb_ms_txpwr_max_cch = 9;

   pvalue->component_1.component_5.component_2.component_2.si2n_SUPPORT = 2;

   pvalue->component_1.component_5.component_2.component_2.si_change_alt = TS44018IE_LHType_lbit;
 

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_SI13_Rest_Octets (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode SI13_Rest_Octets failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }

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
