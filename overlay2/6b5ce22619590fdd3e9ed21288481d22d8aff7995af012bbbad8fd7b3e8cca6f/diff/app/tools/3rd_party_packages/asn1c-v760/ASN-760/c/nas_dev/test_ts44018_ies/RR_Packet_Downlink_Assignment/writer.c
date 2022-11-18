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
   TS44018IE_RR_Packet_Downlink_Assignment value;
   TS44018IE_RR_Packet_Downlink_Assignment* pvalue = &value;
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

   asn1Init_TS44018IE_RR_Packet_Downlink_Assignment (pvalue);
   pvalue->length = 0; /* length will be calculated */

   pvalue->mac_mode = 2;

   pvalue->rlc_mode = 0;

   pvalue->timeslot_allocation = 6;

   pvalue->packet_Timing_Advance.m.timing_advance_valuePresent = 1;
   pvalue->packet_Timing_Advance.timing_advance_value = 30;

   pvalue->packet_Timing_Advance.m.component_2Present = 1;

   pvalue->packet_Timing_Advance.component_2.timing_advance_index = 13;

   pvalue->packet_Timing_Advance.component_2.timing_advance_timeslot_number = 2;

   pvalue->m.component_6Present = 1;

   pvalue->component_6.p0 = 0;

   pvalue->component_6.component_2 = 0;

   pvalue->component_6.pr_mode = 0;

   pvalue->m.power_Control_ParametersPresent = 1;

   pvalue->power_Control_Parameters.alpha = 10;

   pvalue->power_Control_Parameters.m.gamma_tn0Present = 1;
   pvalue->power_Control_Parameters.gamma_tn0 = 20;

   pvalue->power_Control_Parameters.m.gamma_tn1Present = 1;
   pvalue->power_Control_Parameters.gamma_tn1 = 15;

   pvalue->power_Control_Parameters.m.gamma_tn2Present = 1;
   pvalue->power_Control_Parameters.gamma_tn2 = 21;

   pvalue->power_Control_Parameters.m.gamma_tn3Present = 1;
   pvalue->power_Control_Parameters.gamma_tn3 = 18;

   pvalue->power_Control_Parameters.m.gamma_tn4Present = 1;
   pvalue->power_Control_Parameters.gamma_tn4 = 24;

   pvalue->power_Control_Parameters.m.gamma_tn5Present = 1;
   pvalue->power_Control_Parameters.gamma_tn5 = 6;

   pvalue->power_Control_Parameters.m.gamma_tn6Present = 1;
   pvalue->power_Control_Parameters.gamma_tn6 = 11;

   pvalue->power_Control_Parameters.m.gamma_tn7Present = 1;
   pvalue->power_Control_Parameters.gamma_tn7 = 5;

   pvalue->m.downlink_tfi_assignmentPresent = 1;
   pvalue->downlink_tfi_assignment = 18;

   pvalue->component_9 = 0;

   pvalue->m.component_10Present = 1;

   pvalue->component_10.m.component_1Present = 1;

   pvalue->component_10.component_1.egprs_Window_Size = 27;

   pvalue->component_10.component_1.link_quality_measurement_mode = 2;

   pvalue->component_10.m.packet_Extended_Timing_AdvancePresent = 1;
   pvalue->component_10.packet_Extended_Timing_Advance = 1;

   pvalue->component_10.m.component_3Present = 1;

   /* zero elements */

   pvalue->component_10.component_3.m.component_2Present = 1;

   pvalue->component_10.component_3.component_2.fanr = 0;

   /* zero elements */

   pvalue->component_10.component_3.component_2.downlink_EGPRS_Level = 2;

   pvalue->component_10.component_3.component_2.m.component_4Present = 1;

   pvalue->component_10.component_3.component_2.component_4.m.component_1Present = 1;
   /* zero elements */

   pvalue->component_10.component_3.component_2.component_4.m.component_2Present = 1;
   /* zero elements */

   pvalue->component_10.component_3.component_2.component_4.m.component_3Present = 1;

   pvalue->component_10.component_3.component_2.component_4.component_3.m.component_1Present = 1;

   pvalue->component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_2.downlink_tfi_assignment = 9;

   pvalue->component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_2.rlc_mode = 0;

   pvalue->component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_2.m.egprs_Window_SizePresent = 1;
   pvalue->component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_2.egprs_Window_Size = 23;

   pvalue->component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_2.pfi = 66;

   pvalue->component_10.component_3.component_2.component_4.component_3.component_1.m.rlc_Entity_3Present = 1;

   pvalue->component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_3.downlink_tfi_assignment = 12;

   pvalue->component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_3.rlc_mode = 0;

   pvalue->component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_3.m.egprs_Window_SizePresent = 1;
   pvalue->component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_3.egprs_Window_Size = 10;

   pvalue->component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_3.pfi = 122;

   pvalue->component_10.component_3.component_2.component_4.component_3.m.component_2Present = 1;

   /* zero elements */

   /* zero elements */

   /* zero elements */

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_RR_Packet_Downlink_Assignment (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode RR_Packet_Downlink_Assignment failed; status = %d\n", ret);
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
