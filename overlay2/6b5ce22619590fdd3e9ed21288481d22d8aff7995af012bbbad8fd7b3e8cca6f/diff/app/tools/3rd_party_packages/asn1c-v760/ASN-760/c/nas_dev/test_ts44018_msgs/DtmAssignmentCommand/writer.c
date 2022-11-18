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
   TS44018Msg_DL_DCCH_PDU pdu;
   TS44018Msg_DtmAssignmentCommand data;
   TS44018Msg_DtmAssignmentCommand* pvalue = &data;

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

   asn1Init_TS44018Msg_DL_DCCH_PDU (&pdu);
   pdu.l3HdrOpts.t = 1;
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;
   pdu.msgType = ASN1V_ts44018Msg_mt_DtmAssignmentCommand;
   pdu.data.t = T_TS44018Msgs_DL_DCCH_Messages_obj_DtmAssignmentCommand;
   pdu.data.u.obj_DtmAssignmentCommand = pvalue;


   asn1Init_TS44018Msg_DtmAssignmentCommand (pvalue);

   pvalue->csPowerCommand.spare_bit = 0;

   pvalue->csPowerCommand.epc_mode = 0;

   pvalue->csPowerCommand.fpc_epc = 0;

   pvalue->csPowerCommand.power_level = 14;

   pvalue->descrCsChannel.channel_type_and_TDMA_offset = 0;

   pvalue->descrCsChannel.tn = 4;

   pvalue->descrCsChannel.tsc = 0;

   pvalue->descrCsChannel.component_4.t =  2;

   pvalue->descrCsChannel.component_4.u.choice_2.spare_bit = 2;

   pvalue->descrCsChannel.component_4.u.choice_2.arfcn = 144;

   pvalue->gprsBroadcastInfo.length = 0; /* length will be calculated */

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.nmo = 2;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.t3168 = 5;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.t3192 = 1;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.drx_timer_max = 4;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.access_burst_type = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.control_ack_type = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.bs_cv_max = 4;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.m.component_8Present = 1;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_8.pan_dec = 6;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_8.pan_inc = 6;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_8.pan_max = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.m.component_9Present = 1;
   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Length = 0; /* length will be calculated */

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.m.component_1Present = 1;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.component_1.m.component_1Present = 1;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.component_1.component_1.egprs_packet_channel_request = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.component_1.component_1.bep_period = 14;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.component_1.pfc_feature_mode = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.component_1.dtm_support = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.component_1.bss_paging_coordination = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.m.component_2Present = 1;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.component_2.ccn_active = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.component_2.nw_ext_utbf = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.m.component_3Present = 1;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.component_3.multiple_tbf_capability = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.component_3.ext_utbf_nodata = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.component_3.dtm_enhancements_capability = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.component_3.m.component_4Present = 1;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.component_3.component_4.dedicated_mode_mbms_notification_support = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.component_3.component_4.mnci_support = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.m.reduced_latency_accessPresent = 1;
   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.reduced_latency_access = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.m.nmo_i_alternatePresent = 1;
   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.nmo_i_alternate = 0;

   pvalue->gprsBroadcastInfo.gprs_Power_Control_Parameters.alpha = 8;

   pvalue->gprsBroadcastInfo.gprs_Power_Control_Parameters.t_avg_w = 12;

   pvalue->gprsBroadcastInfo.gprs_Power_Control_Parameters.t_avg_t = 0;

   pvalue->gprsBroadcastInfo.gprs_Power_Control_Parameters.pc_meas_chan = 0;

   pvalue->gprsBroadcastInfo.gprs_Power_Control_Parameters.n_avg_i = 7;

   pvalue->m.cellChannelDescriptionPresent = 1;
   pvalue->cellChannelDescription.t =  1;

   pvalue->cellChannelDescription.u.bitmap0.spare_bit = 2;

   pvalue->cellChannelDescription.u.bitmap0.bitmap0[0] = 0xa4;
   pvalue->cellChannelDescription.u.bitmap0.bitmap0[1] = 0x1a;
   pvalue->cellChannelDescription.u.bitmap0.bitmap0[2] = 0x6b;
   pvalue->cellChannelDescription.u.bitmap0.bitmap0[3] = 0x1c;
   pvalue->cellChannelDescription.u.bitmap0.bitmap0[4] = 0xc3;
   pvalue->cellChannelDescription.u.bitmap0.bitmap0[5] = 0x50;
   pvalue->cellChannelDescription.u.bitmap0.bitmap0[6] = 0x39;
   pvalue->cellChannelDescription.u.bitmap0.bitmap0[7] = 0xce;
   pvalue->cellChannelDescription.u.bitmap0.bitmap0[8] = 0x6c;
   pvalue->cellChannelDescription.u.bitmap0.bitmap0[9] = 0x5d;
   pvalue->cellChannelDescription.u.bitmap0.bitmap0[10] = 0xda;
   pvalue->cellChannelDescription.u.bitmap0.bitmap0[11] = 0xa1;
   pvalue->cellChannelDescription.u.bitmap0.bitmap0[12] = 0x24;
   pvalue->cellChannelDescription.u.bitmap0.bitmap0[13] = 0x8a;
   pvalue->cellChannelDescription.u.bitmap0.bitmap0[14] = 0x8;
   pvalue->cellChannelDescription.u.bitmap0.bitmap0[15] = 0x5f;

   pvalue->m.channelModePresent = 1;
   pvalue->channelMode = 130;

   pvalue->m.frequencyListPresent = 1;
   pvalue->frequencyList.length = 0; /* length will be calculated */

   pvalue->frequencyList.component_2.t =  2;

   pvalue->frequencyList.component_2.u.choice_2.spare_bit = 1;

   pvalue->frequencyList.component_2.u.choice_2.component_2.t =  3;
   pvalue->frequencyList.component_2.u.choice_2.component_2.u.range_256.numbits = 17;
   {
      OSOCTET* bitData = (OSOCTET*) rtxMemAlloc (pctxt,3);
      bitData[0] = 0x6a;
      bitData[1] = 0x3f;
      bitData[2] = 0xab;
      pvalue->frequencyList.component_2.u.choice_2.component_2.u.range_256.data = (const OSOCTET*)bitData;
   }

   pvalue->m.mobileAllocationPresent = 1;

   pvalue->mobileAllocation.length = 9;

   pvalue->mobileAllocation.mac.numbits = 72;
   pvalue->mobileAllocation.mac.data[0] = 0x44;
   pvalue->mobileAllocation.mac.data[1] = 0x5f;
   pvalue->mobileAllocation.mac.data[2] = 0x70;
   pvalue->mobileAllocation.mac.data[3] = 0x62;
   pvalue->mobileAllocation.mac.data[4] = 0x39;
   pvalue->mobileAllocation.mac.data[5] = 0x59;
   pvalue->mobileAllocation.mac.data[6] = 0x69;
   pvalue->mobileAllocation.mac.data[7] = 0x70;
   pvalue->mobileAllocation.mac.data[8] = 0x6b;

   pvalue->m.descrUplinkPacketChannelAssignmentPresent = 1;
   pvalue->descrUplinkPacketChannelAssignment.length = 0; /* length will be calculated */

   pvalue->descrUplinkPacketChannelAssignment.channel_coding_command = 0;

   pvalue->descrUplinkPacketChannelAssignment.tlli_block_channel_coding = 0;

   pvalue->descrUplinkPacketChannelAssignment.packet_Timing_Advance.m.timing_advance_valuePresent = 1;
   pvalue->descrUplinkPacketChannelAssignment.packet_Timing_Advance.timing_advance_value = 47;

   pvalue->descrUplinkPacketChannelAssignment.packet_Timing_Advance.m.component_2Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.packet_Timing_Advance.component_2.timing_advance_index = 7;

   pvalue->descrUplinkPacketChannelAssignment.packet_Timing_Advance.component_2.timing_advance_timeslot_number = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.t =  2;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.component_1 = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.extended_dynamic_allocation = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.m.component_2Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_2.p0 = 8;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_2.pr_mode = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.m.component_3Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.t =  2;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.alpha = 3;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[0].m.component_1Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[0].component_1.usf_granularity = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[0].component_1.gamma_tn0 = 29;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[1].m.component_1Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[1].component_1.usf_granularity = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[1].component_1.gamma_tn0 = 2;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[2].m.component_1Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[2].component_1.usf_granularity = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[2].component_1.gamma_tn0 = 24;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[3].m.component_1Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[3].component_1.usf_granularity = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[3].component_1.gamma_tn0 = 7;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[4].m.component_1Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[4].component_1.usf_granularity = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[4].component_1.gamma_tn0 = 13;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[5].m.component_1Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[5].component_1.usf_granularity = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[5].component_1.gamma_tn0 = 17;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[6].m.component_1Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[6].component_1.usf_granularity = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[6].component_1.gamma_tn0 = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[7].m.component_1Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[7].component_1.usf_granularity = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.choice_2.multiple_TBF_Allocation.component_3.timeslot_description.u.choice_2.component_2.elem[7].component_1.gamma_tn0 = 25;

   /* zero elements */

   pvalue->descrUplinkPacketChannelAssignment.m.component_6Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_6.m.component_1Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_1.egprs_mcs_mode = 13;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_1.resegment = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_1.egprs_Window_Size = 12;

   pvalue->descrUplinkPacketChannelAssignment.component_6.m.packet_Extended_Timing_AdvancePresent = 1;
   pvalue->descrUplinkPacketChannelAssignment.component_6.packet_Extended_Timing_Advance = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_6.m.component_3Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.m.rlc_modePresent = 1;
   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.rlc_mode = 0;

   /* zero elements */

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.uplink_EGPRS_Level = 2;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.m.pulse_FormatPresent = 1;
   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.pulse_Format.t =  2;
   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.pulse_Format.u.pulse_Format_Coding_2.t =  2;
   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.pulse_Format.u.pulse_Format_Coding_2.u.non_Hopping_Carrier_Pulse_Format.t =  3;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.m.component_5Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_5.m.component_1Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_5.component_1.reported_timeslots = 212;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_5.component_1.tsh = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.m.component_6Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.m.component_1Present = 1;
   /* zero elements */

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.m.component_2Present = 1;
   /* zero elements */

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.m.component_3Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.component_3.component_1.t =  2;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.component_3.component_1.u.choice_2.rlc_Entity_2.uplink_tfi_assignment = 3;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.component_3.component_1.u.choice_2.rlc_Entity_2.rlc_mode = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.component_3.component_1.u.choice_2.rlc_Entity_2.m.egprs_Window_SizePresent = 1;
   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.component_3.component_1.u.choice_2.rlc_Entity_2.egprs_Window_Size = 25;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.component_3.component_1.u.choice_2.rlc_Entity_2.pfi = 78;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.component_3.component_1.u.choice_2.m.rlc_Entity_3Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.component_3.component_1.u.choice_2.rlc_Entity_3.uplink_tfi_assignment = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.component_3.component_1.u.choice_2.rlc_Entity_3.rlc_mode = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.component_3.component_1.u.choice_2.rlc_Entity_3.m.egprs_Window_SizePresent = 1;
   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.component_3.component_1.u.choice_2.rlc_Entity_3.egprs_Window_Size = 27;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.component_3.component_1.u.choice_2.rlc_Entity_3.pfi = 120;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.component_3.m.component_2Present = 1;

   /* zero elements */

   /* zero elements */

   /* zero elements */

   pvalue->m.descrDownlinkPacketChannelAssignmentPresent = 1;
   pvalue->descrDownlinkPacketChannelAssignment.length = 0; /* length will be calculated */

   pvalue->descrDownlinkPacketChannelAssignment.mac_mode = 1;

   pvalue->descrDownlinkPacketChannelAssignment.rlc_mode = 0;

   pvalue->descrDownlinkPacketChannelAssignment.timeslot_allocation = 254;

   pvalue->descrDownlinkPacketChannelAssignment.packet_Timing_Advance.m.timing_advance_valuePresent = 1;
   pvalue->descrDownlinkPacketChannelAssignment.packet_Timing_Advance.timing_advance_value = 50;

   pvalue->descrDownlinkPacketChannelAssignment.packet_Timing_Advance.m.component_2Present = 1;

   pvalue->descrDownlinkPacketChannelAssignment.packet_Timing_Advance.component_2.timing_advance_index = 6;

   pvalue->descrDownlinkPacketChannelAssignment.packet_Timing_Advance.component_2.timing_advance_timeslot_number = 2;

   pvalue->descrDownlinkPacketChannelAssignment.m.component_6Present = 1;

   pvalue->descrDownlinkPacketChannelAssignment.component_6.p0 = 12;

   pvalue->descrDownlinkPacketChannelAssignment.component_6.component_2 = 0;

   pvalue->descrDownlinkPacketChannelAssignment.component_6.pr_mode = 0;

   pvalue->descrDownlinkPacketChannelAssignment.m.power_Control_ParametersPresent = 1;

   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.alpha = 3;

   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.m.gamma_tn0Present = 1;
   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.gamma_tn0 = 26;

   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.m.gamma_tn1Present = 1;
   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.gamma_tn1 = 25;

   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.m.gamma_tn2Present = 1;
   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.gamma_tn2 = 22;

   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.m.gamma_tn3Present = 1;
   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.gamma_tn3 = 26;

   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.m.gamma_tn4Present = 1;
   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.gamma_tn4 = 15;

   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.m.gamma_tn5Present = 1;
   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.gamma_tn5 = 0;

   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.m.gamma_tn6Present = 1;
   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.gamma_tn6 = 28;

   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.m.gamma_tn7Present = 1;
   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.gamma_tn7 = 4;

   pvalue->descrDownlinkPacketChannelAssignment.m.downlink_tfi_assignmentPresent = 1;
   pvalue->descrDownlinkPacketChannelAssignment.downlink_tfi_assignment = 2;

   pvalue->descrDownlinkPacketChannelAssignment.component_9 = 0;

   pvalue->descrDownlinkPacketChannelAssignment.m.component_10Present = 1;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.m.component_1Present = 1;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_1.egprs_Window_Size = 16;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_1.link_quality_measurement_mode = 2;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.m.packet_Extended_Timing_AdvancePresent = 1;
   pvalue->descrDownlinkPacketChannelAssignment.component_10.packet_Extended_Timing_Advance = 1;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.m.component_3Present = 1;

   /* zero elements */

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.m.component_2Present = 1;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.fanr = 0;

   /* zero elements */

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.downlink_EGPRS_Level = 0;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.m.component_4Present = 1;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.m.component_1Present = 1;
   /* zero elements */

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.m.component_2Present = 1;
   /* zero elements */

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.m.component_3Present = 1;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.m.component_1Present = 1;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_2.downlink_tfi_assignment = 5;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_2.rlc_mode = 0;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_2.m.egprs_Window_SizePresent = 1;
   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_2.egprs_Window_Size = 8;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_2.pfi = 77;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.m.rlc_Entity_3Present = 1;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_3.downlink_tfi_assignment = 9;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_3.rlc_mode = 0;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_3.m.egprs_Window_SizePresent = 1;
   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_3.egprs_Window_Size = 14;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_3.pfi = 88;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.m.component_2Present = 1;

   /* zero elements */

   /* zero elements */

   /* zero elements */

   pvalue->m.multiRateConfigPresent = 1;

   pvalue->multiRateConfig.multirate_speech_version = TS44018IE_Multirate_Configuration_multirate_speech_version_v1;

   pvalue->multiRateConfig.nscb = 0;

   pvalue->multiRateConfig.icmi = 0;

   pvalue->multiRateConfig.start_mode = 2;

   pvalue->multiRateConfig.amr_codec_modes = 141;

   /* zero elements */

   pvalue->m.cipheringMOdeSettingPresent = 1;

   pvalue->cipheringMOdeSetting.algorithm_id = 2;

   pvalue->cipheringMOdeSetting.sc = 0;

   pvalue->m.mobileAllocationC2Present = 1;

   pvalue->mobileAllocationC2.length = 3;

   pvalue->mobileAllocationC2.mac.numbits = 24;
   pvalue->mobileAllocationC2.mac.data[0] = 0x5b;
   pvalue->mobileAllocationC2.mac.data[1] = 0x6b;
   pvalue->mobileAllocationC2.mac.data[2] = 0x5c;

   pvalue->m.frequencyListC2Present = 1;
   pvalue->frequencyListC2.length = 0; /* length will be calculated */

   pvalue->frequencyListC2.component_2.t =  1;

   pvalue->frequencyListC2.component_2.u.bitmap0.spare_bit = 1;

   pvalue->frequencyListC2.component_2.u.bitmap0.bitmap0[0] = 0xa5;
   pvalue->frequencyListC2.component_2.u.bitmap0.bitmap0[1] = 0x93;
   pvalue->frequencyListC2.component_2.u.bitmap0.bitmap0[2] = 0xe8;
   pvalue->frequencyListC2.component_2.u.bitmap0.bitmap0[3] = 0x56;
   pvalue->frequencyListC2.component_2.u.bitmap0.bitmap0[4] = 0x9c;
   pvalue->frequencyListC2.component_2.u.bitmap0.bitmap0[5] = 0xc1;
   pvalue->frequencyListC2.component_2.u.bitmap0.bitmap0[6] = 0xb8;
   pvalue->frequencyListC2.component_2.u.bitmap0.bitmap0[7] = 0x81;
   pvalue->frequencyListC2.component_2.u.bitmap0.bitmap0[8] = 0xc8;
   pvalue->frequencyListC2.component_2.u.bitmap0.bitmap0[9] = 0xdf;
   pvalue->frequencyListC2.component_2.u.bitmap0.bitmap0[10] = 0x9e;
   pvalue->frequencyListC2.component_2.u.bitmap0.bitmap0[11] = 0x36;
   pvalue->frequencyListC2.component_2.u.bitmap0.bitmap0[12] = 0xe;
   pvalue->frequencyListC2.component_2.u.bitmap0.bitmap0[13] = 0x13;
   pvalue->frequencyListC2.component_2.u.bitmap0.bitmap0[14] = 0x59;
   pvalue->frequencyListC2.component_2.u.bitmap0.bitmap0[15] = 0x5f;

   pvalue->m.descrDownlinkPacketChannelAssignmentType2Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.length = 0; /* length will be calculated */

   pvalue->descrDownlinkPacketChannelAssignmentType2.rlc_mode = 0;

   pvalue->descrDownlinkPacketChannelAssignmentType2.m.component_3Present = 1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_3.p0_c1 = 5;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_3.pr_mode_c1 = 0;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_3.m.component_3Present = 1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_3.component_3.p0_c2 = 14;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_3.component_3.pr_mode_c2 = 0;

   pvalue->descrDownlinkPacketChannelAssignmentType2.m.power_Control_Parameters_C1Present = 1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.alpha = 2;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.m.gamma_tn0Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.gamma_tn0 = 21;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.m.gamma_tn1Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.gamma_tn1 = 8;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.m.gamma_tn2Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.gamma_tn2 = 25;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.m.gamma_tn3Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.gamma_tn3 = 7;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.m.gamma_tn4Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.gamma_tn4 = 18;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.m.gamma_tn5Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.gamma_tn5 = 5;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.m.gamma_tn6Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.gamma_tn6 = 3;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.m.gamma_tn7Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.gamma_tn7 = 23;

   pvalue->descrDownlinkPacketChannelAssignmentType2.m.power_Control_Parameters_C2Present = 1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.alpha = 14;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.m.gamma_tn0Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.gamma_tn0 = 25;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.m.gamma_tn1Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.gamma_tn1 = 0;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.m.gamma_tn2Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.gamma_tn2 = 28;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.m.gamma_tn3Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.gamma_tn3 = 16;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.m.gamma_tn4Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.gamma_tn4 = 11;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.m.gamma_tn5Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.gamma_tn5 = 23;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.m.gamma_tn6Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.gamma_tn6 = 20;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.m.gamma_tn7Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.gamma_tn7 = 23;

   pvalue->descrDownlinkPacketChannelAssignmentType2.m.downlink_tfi_assignmentPresent = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.downlink_tfi_assignment = 24;

   pvalue->descrDownlinkPacketChannelAssignmentType2.egprs_Window_Size = 8;

   pvalue->descrDownlinkPacketChannelAssignmentType2.link_quality_measurement_mode = 2;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_9.t =  2;
   pvalue->descrDownlinkPacketChannelAssignmentType2.component_9.u.choice_2.t =  1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_9.u.choice_2.u.choice_1.component_1.t =  3;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_9.u.choice_2.u.choice_1.component_1.u.choice_3.downlink_pdch_pairs_c1 = 168;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_9.u.choice_2.u.choice_1.component_1.u.choice_3.uplink_pdch_pairs_c1 = 20;

   /* zero elements */

   pvalue->descrDownlinkPacketChannelAssignmentType2.downlink_EGPRS_Level = 2;

   pvalue->descrDownlinkPacketChannelAssignmentType2.m.component_11Present = 1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.m.component_1Present = 1;
   /* zero elements */

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.m.component_2Present = 1;
   /* zero elements */

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.m.component_3Present = 1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.m.component_1Present = 1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_2.downlink_tfi_assignment = 7;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_2.rlc_mode = 0;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_2.m.egprs_Window_SizePresent = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_2.egprs_Window_Size = 28;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_2.pfi = 16;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.m.rlc_Entity_3Present = 1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_3.downlink_tfi_assignment = 13;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_3.rlc_mode = 0;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_3.m.egprs_Window_SizePresent = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_3.egprs_Window_Size = 29;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_3.pfi = 76;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.m.component_2Present = 1;

   /* zero elements */

   /* zero elements */

   /* zero elements */

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_2.m.egprs_Packet_Downlink_Ack_Nack_Type_3_SupportPresent = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_2.egprs_Packet_Downlink_Ack_Nack_Type_3_Support = 0;

   pvalue->m.channelDescrC2Present = 1;

   pvalue->channelDescrC2.tsc = 5;

   pvalue->channelDescrC2.component_2.t =  1;

   pvalue->channelDescrC2.component_2.u.choice_1.maio = 22;

   pvalue->channelDescrC2.component_2.u.choice_1.hsn = 54;


   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_DL_DCCH_PDU (&ctxt, &pdu);
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
