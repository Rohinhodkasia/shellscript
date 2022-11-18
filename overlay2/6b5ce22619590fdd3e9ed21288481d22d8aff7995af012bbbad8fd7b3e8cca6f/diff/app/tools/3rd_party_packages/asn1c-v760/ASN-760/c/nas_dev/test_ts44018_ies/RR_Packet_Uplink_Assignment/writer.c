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
   TS44018IE_RR_Packet_Uplink_Assignment value;
   TS44018IE_RR_Packet_Uplink_Assignment* pvalue = &value;
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

   asn1Init_TS44018IE_RR_Packet_Uplink_Assignment (pvalue);
   pvalue->length = 0; /* length will be calculated */

   pvalue->channel_coding_command = 2;

   pvalue->tlli_block_channel_coding = 0;

   pvalue->packet_Timing_Advance.m.timing_advance_valuePresent = 1;
   pvalue->packet_Timing_Advance.timing_advance_value = 12;

   pvalue->packet_Timing_Advance.m.component_2Present = 1;

   pvalue->packet_Timing_Advance.component_2.timing_advance_index = 8;

   pvalue->packet_Timing_Advance.component_2.timing_advance_timeslot_number = 6;

   pvalue->component_5.t =  2;

   pvalue->component_5.u.choice_2.component_1 = 0;

   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.extended_dynamic_allocation = 0;

   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.m.component_2Present = 1;

   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_2.p0 = 13;

   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_2.pr_mode = 0;

   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.m.component_3Present = 1;

   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.t =  1;

   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_1.elem[0].m.usf_granularityPresent = 1;
   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_1.elem[0].usf_granularity = 0;

   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_1.elem[1].m.usf_granularityPresent = 1;
   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_1.elem[1].usf_granularity = 0;

   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_1.elem[2].m.usf_granularityPresent = 1;
   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_1.elem[2].usf_granularity = 0;

   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_1.elem[3].m.usf_granularityPresent = 1;
   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_1.elem[3].usf_granularity = 0;

   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_1.elem[4].m.usf_granularityPresent = 1;
   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_1.elem[4].usf_granularity = 0;

   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_1.elem[5].m.usf_granularityPresent = 1;
   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_1.elem[5].usf_granularity = 0;

   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_1.elem[6].m.usf_granularityPresent = 1;
   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_1.elem[6].usf_granularity = 0;

   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_1.elem[7].m.usf_granularityPresent = 1;
   pvalue->component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_1.elem[7].usf_granularity = 0;

   /* zero elements */

   pvalue->m.component_6Present = 1;

   pvalue->component_6.m.component_1Present = 1;

   pvalue->component_6.component_1.egprs_mcs_mode = 13;

   pvalue->component_6.component_1.resegment = 0;

   pvalue->component_6.component_1.egprs_Window_Size = 24;

   pvalue->component_6.m.packet_Extended_Timing_AdvancePresent = 1;
   pvalue->component_6.packet_Extended_Timing_Advance = 1;

   pvalue->component_6.m.component_3Present = 1;

   pvalue->component_6.component_3.m.rlc_modePresent = 1;
   pvalue->component_6.component_3.rlc_mode = 0;

   /* zero elements */

   pvalue->component_6.component_3.uplink_EGPRS_Level = 1;

   pvalue->component_6.component_3.m.pulse_FormatPresent = 1;
   pvalue->component_6.component_3.pulse_Format.t =  1;
   pvalue->component_6.component_3.pulse_Format.u.pulse_Format_Coding_1 = 6;

   pvalue->component_6.component_3.m.component_5Present = 1;

   pvalue->component_6.component_3.component_5.m.component_1Present = 1;

   pvalue->component_6.component_3.component_5.component_1.reported_timeslots = 69;

   pvalue->component_6.component_3.component_5.component_1.tsh = 0;

   pvalue->component_6.component_3.m.component_6Present = 1;

   pvalue->component_6.component_3.component_6.m.component_1Present = 1;
   /* zero elements */

   pvalue->component_6.component_3.component_6.m.component_2Present = 1;
   /* zero elements */

   pvalue->component_6.component_3.component_6.m.component_3Present = 1;

   pvalue->component_6.component_3.component_6.component_3.component_1.t =  1;
   pvalue->component_6.component_3.component_6.component_3.component_1.u.emst_NW_Capability = 0;

   pvalue->component_6.component_3.component_6.component_3.m.component_2Present = 1;

   /* zero elements */

   /* zero elements */

   /* zero elements */

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_RR_Packet_Uplink_Assignment (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode RR_Packet_Uplink_Assignment failed; status = %d\n", ret);
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
