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
   TS44018IE_GPRS_broadcast_information value;
   TS44018IE_GPRS_broadcast_information* pvalue = &value;
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

   asn1Init_TS44018IE_GPRS_broadcast_information (pvalue);

   pvalue->length = 0; /* length will be calculated */

   pvalue->gprs_Cell_Options.nmo = 2;

   pvalue->gprs_Cell_Options.t3168 = 2;

   pvalue->gprs_Cell_Options.t3192 = 2;

   pvalue->gprs_Cell_Options.drx_timer_max = 6;

   pvalue->gprs_Cell_Options.access_burst_type = 0;

   pvalue->gprs_Cell_Options.control_ack_type = 0;

   pvalue->gprs_Cell_Options.bs_cv_max = 10;

   pvalue->gprs_Cell_Options.m.component_8Present = 1;

   pvalue->gprs_Cell_Options.component_8.pan_dec = 3;

   pvalue->gprs_Cell_Options.component_8.pan_inc = 5;

   pvalue->gprs_Cell_Options.component_8.pan_max = 1;

   pvalue->gprs_Cell_Options.m.component_9Present = 1;
   pvalue->gprs_Cell_Options.component_9.extension_Length = 0; /* length will be calculated */

   pvalue->gprs_Cell_Options.component_9.extension_Information.m.component_1Present = 1;

   pvalue->gprs_Cell_Options.component_9.extension_Information.component_1.m.component_1Present = 1;

   pvalue->gprs_Cell_Options.component_9.extension_Information.component_1.component_1.egprs_packet_channel_request = 0;

   pvalue->gprs_Cell_Options.component_9.extension_Information.component_1.component_1.bep_period = 14;

   pvalue->gprs_Cell_Options.component_9.extension_Information.component_1.pfc_feature_mode = 0;

   pvalue->gprs_Cell_Options.component_9.extension_Information.component_1.dtm_support = 0;

   pvalue->gprs_Cell_Options.component_9.extension_Information.component_1.bss_paging_coordination = 0;

   pvalue->gprs_Cell_Options.component_9.extension_Information.m.component_2Present = 1;

   pvalue->gprs_Cell_Options.component_9.extension_Information.component_2.ccn_active = 0;

   pvalue->gprs_Cell_Options.component_9.extension_Information.component_2.nw_ext_utbf = 0;

   pvalue->gprs_Cell_Options.component_9.extension_Information.m.component_3Present = 1;

   pvalue->gprs_Cell_Options.component_9.extension_Information.component_3.multiple_tbf_capability = 0;

   pvalue->gprs_Cell_Options.component_9.extension_Information.component_3.ext_utbf_nodata = 0;

   pvalue->gprs_Cell_Options.component_9.extension_Information.component_3.dtm_enhancements_capability = 0;

   pvalue->gprs_Cell_Options.component_9.extension_Information.component_3.m.component_4Present = 1;

   pvalue->gprs_Cell_Options.component_9.extension_Information.component_3.component_4.dedicated_mode_mbms_notification_support = 0;

   pvalue->gprs_Cell_Options.component_9.extension_Information.component_3.component_4.mnci_support = 0;

   pvalue->gprs_Cell_Options.component_9.extension_Information.m.reduced_latency_accessPresent = 1;
   pvalue->gprs_Cell_Options.component_9.extension_Information.reduced_latency_access = 0;

   pvalue->gprs_Cell_Options.component_9.extension_Information.m.nmo_i_alternatePresent = 1;
   pvalue->gprs_Cell_Options.component_9.extension_Information.nmo_i_alternate = 0;

   pvalue->gprs_Power_Control_Parameters.alpha = 0;

   pvalue->gprs_Power_Control_Parameters.t_avg_w = 30;

   pvalue->gprs_Power_Control_Parameters.t_avg_t = 24;

   pvalue->gprs_Power_Control_Parameters.pc_meas_chan = 0;

   pvalue->gprs_Power_Control_Parameters.n_avg_i = 9;


   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_GPRS_broadcast_information (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode GPRS_broadcast_information failed; status = %d\n", ret);
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
