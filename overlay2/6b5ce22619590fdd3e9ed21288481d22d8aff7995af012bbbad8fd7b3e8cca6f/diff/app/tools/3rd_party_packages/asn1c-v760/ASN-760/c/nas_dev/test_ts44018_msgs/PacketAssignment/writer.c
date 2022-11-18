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
   TS44018Msg_PacketAssignment data;
   TS44018Msg_PacketAssignment* pvalue = &data;

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
   pdu.msgType = ASN1V_ts44018Msg_mt_PacketAssignment;
   pdu.data.t = T_TS44018Msgs_DL_DCCH_Messages_obj_PacketAssignment;
   pdu.data.u.obj_PacketAssignment = pvalue;


   asn1Init_TS44018Msg_PacketAssignment (pvalue);

   pvalue->gprsBroadcastInfo.length = 0; /* length will be calculated */

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.nmo = 2;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.t3168 = 5;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.t3192 = 3;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.drx_timer_max = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.access_burst_type = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.control_ack_type = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.bs_cv_max = 10;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.m.component_8Present = 1;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_8.pan_dec = 5;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_8.pan_inc = 2;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_8.pan_max = 1;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.m.component_9Present = 1;
   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Length = 0; /* length will be calculated */

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.m.component_1Present = 1;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.component_1.m.component_1Present = 1;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.component_1.component_1.egprs_packet_channel_request = 0;

   pvalue->gprsBroadcastInfo.gprs_Cell_Options.component_9.extension_Information.component_1.component_1.bep_period = 9;

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

   pvalue->gprsBroadcastInfo.gprs_Power_Control_Parameters.alpha = 12;

   pvalue->gprsBroadcastInfo.gprs_Power_Control_Parameters.t_avg_w = 12;

   pvalue->gprsBroadcastInfo.gprs_Power_Control_Parameters.t_avg_t = 16;

   pvalue->gprsBroadcastInfo.gprs_Power_Control_Parameters.pc_meas_chan = 0;

   pvalue->gprsBroadcastInfo.gprs_Power_Control_Parameters.n_avg_i = 6;

   pvalue->m.descrUplinkPacketChannelAssignmentPresent = 1;
   pvalue->descrUplinkPacketChannelAssignment.length = 0; /* length will be calculated */

   pvalue->descrUplinkPacketChannelAssignment.channel_coding_command = 1;

   pvalue->descrUplinkPacketChannelAssignment.tlli_block_channel_coding = 0;

   pvalue->descrUplinkPacketChannelAssignment.packet_Timing_Advance.m.timing_advance_valuePresent = 1;
   pvalue->descrUplinkPacketChannelAssignment.packet_Timing_Advance.timing_advance_value = 16;

   pvalue->descrUplinkPacketChannelAssignment.packet_Timing_Advance.m.component_2Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.packet_Timing_Advance.component_2.timing_advance_index = 0;

   pvalue->descrUplinkPacketChannelAssignment.packet_Timing_Advance.component_2.timing_advance_timeslot_number = 5;

   pvalue->descrUplinkPacketChannelAssignment.component_5.t =  1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.extended_Dynamic_Allocation = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.m.component_2Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_2.p0 = 4;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_2.pr_mode = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.usf_granularity = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.m.uplink_tfi_assignmentPresent = 1;
   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.uplink_tfi_assignment = 23;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_5 = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.t =  2;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.alpha = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.m.component_2Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.component_2.usf_tn0 = 3;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.component_2.gamma_tn0 = 27;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.m.component_3Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.component_3.usf_tn1 = 2;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.component_3.gamma_tn1 = 21;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.m.component_4Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.component_4.usf_tn2 = 5;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.component_4.gamma_tn2 = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.m.component_5Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.component_5.usf_tn3 = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.component_5.gamma_tn3 = 26;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.m.component_6Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.component_6.usf_tn4 = 3;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.component_6.gamma_tn4 = 14;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.m.component_7Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.component_7.usf_tn5 = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.component_7.gamma_tn5 = 22;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.m.component_8Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.component_8.usf_tn6 = 4;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.component_8.gamma_tn6 = 27;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.m.component_9Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.component_9.usf_tn7 = 5;

   pvalue->descrUplinkPacketChannelAssignment.component_5.u.dynamic_Allocation.component_6.u.choice_2.component_9.gamma_tn7 = 6;

   pvalue->descrUplinkPacketChannelAssignment.m.component_6Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_6.m.component_1Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_1.egprs_mcs_mode = 9;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_1.resegment = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_1.egprs_Window_Size = 27;

   pvalue->descrUplinkPacketChannelAssignment.component_6.m.packet_Extended_Timing_AdvancePresent = 1;
   pvalue->descrUplinkPacketChannelAssignment.component_6.packet_Extended_Timing_Advance = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_6.m.component_3Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.m.rlc_modePresent = 1;
   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.rlc_mode = 0;

   /* zero elements */

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.uplink_EGPRS_Level = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.m.pulse_FormatPresent = 1;
   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.pulse_Format.t =  2;
   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.pulse_Format.u.pulse_Format_Coding_2.t =  2;
   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.pulse_Format.u.pulse_Format_Coding_2.u.non_Hopping_Carrier_Pulse_Format.t =  2;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.m.component_5Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_5.m.component_1Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_5.component_1.reported_timeslots = 23;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_5.component_1.tsh = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.m.component_6Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.m.component_1Present = 1;
   /* zero elements */

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.m.component_2Present = 1;
   /* zero elements */

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.m.component_3Present = 1;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.component_3.component_1.t =  1;
   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.component_3.component_1.u.emst_NW_Capability = 0;

   pvalue->descrUplinkPacketChannelAssignment.component_6.component_3.component_6.component_3.m.component_2Present = 1;

   /* zero elements */

   /* zero elements */

   /* zero elements */

   pvalue->m.descrDownlinkPacketChannelAssignmentPresent = 1;
   pvalue->descrDownlinkPacketChannelAssignment.length = 0; /* length will be calculated */

   pvalue->descrDownlinkPacketChannelAssignment.mac_mode = 2;

   pvalue->descrDownlinkPacketChannelAssignment.rlc_mode = 0;

   pvalue->descrDownlinkPacketChannelAssignment.timeslot_allocation = 202;

   pvalue->descrDownlinkPacketChannelAssignment.packet_Timing_Advance.m.timing_advance_valuePresent = 1;
   pvalue->descrDownlinkPacketChannelAssignment.packet_Timing_Advance.timing_advance_value = 2;

   pvalue->descrDownlinkPacketChannelAssignment.packet_Timing_Advance.m.component_2Present = 1;

   pvalue->descrDownlinkPacketChannelAssignment.packet_Timing_Advance.component_2.timing_advance_index = 10;

   pvalue->descrDownlinkPacketChannelAssignment.packet_Timing_Advance.component_2.timing_advance_timeslot_number = 2;

   pvalue->descrDownlinkPacketChannelAssignment.m.component_6Present = 1;

   pvalue->descrDownlinkPacketChannelAssignment.component_6.p0 = 4;

   pvalue->descrDownlinkPacketChannelAssignment.component_6.component_2 = 0;

   pvalue->descrDownlinkPacketChannelAssignment.component_6.pr_mode = 0;

   pvalue->descrDownlinkPacketChannelAssignment.m.power_Control_ParametersPresent = 1;

   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.alpha = 6;

   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.m.gamma_tn0Present = 1;
   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.gamma_tn0 = 14;

   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.m.gamma_tn1Present = 1;
   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.gamma_tn1 = 6;

   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.m.gamma_tn2Present = 1;
   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.gamma_tn2 = 15;

   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.m.gamma_tn3Present = 1;
   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.gamma_tn3 = 10;

   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.m.gamma_tn4Present = 1;
   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.gamma_tn4 = 9;

   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.m.gamma_tn5Present = 1;
   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.gamma_tn5 = 21;

   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.m.gamma_tn6Present = 1;
   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.gamma_tn6 = 13;

   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.m.gamma_tn7Present = 1;
   pvalue->descrDownlinkPacketChannelAssignment.power_Control_Parameters.gamma_tn7 = 3;

   pvalue->descrDownlinkPacketChannelAssignment.m.downlink_tfi_assignmentPresent = 1;
   pvalue->descrDownlinkPacketChannelAssignment.downlink_tfi_assignment = 9;

   pvalue->descrDownlinkPacketChannelAssignment.component_9 = 0;

   pvalue->descrDownlinkPacketChannelAssignment.m.component_10Present = 1;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.m.component_1Present = 1;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_1.egprs_Window_Size = 11;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_1.link_quality_measurement_mode = 2;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.m.packet_Extended_Timing_AdvancePresent = 1;
   pvalue->descrDownlinkPacketChannelAssignment.component_10.packet_Extended_Timing_Advance = 2;

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

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_2.downlink_tfi_assignment = 16;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_2.rlc_mode = 0;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_2.m.egprs_Window_SizePresent = 1;
   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_2.egprs_Window_Size = 14;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_2.pfi = 121;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.m.rlc_Entity_3Present = 1;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_3.downlink_tfi_assignment = 3;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_3.rlc_mode = 0;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_3.m.egprs_Window_SizePresent = 1;
   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_3.egprs_Window_Size = 0;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.component_1.rlc_Entity_3.pfi = 81;

   pvalue->descrDownlinkPacketChannelAssignment.component_10.component_3.component_2.component_4.component_3.m.component_2Present = 1;

   /* zero elements */

   /* zero elements */

   /* zero elements */

   pvalue->m.freqListC2Present = 1;
   pvalue->freqListC2.length = 0; /* length will be calculated */

   pvalue->freqListC2.component_2.t =  2;

   pvalue->freqListC2.component_2.u.choice_2.spare_bit = 0;

   pvalue->freqListC2.component_2.u.choice_2.component_2.t =  1;
   pvalue->freqListC2.component_2.u.choice_2.component_2.u.range_1024.numbits = 11;
   {
      OSOCTET* bitData = (OSOCTET*) rtxMemAlloc (pctxt, 2);
      bitData[0] = 0x3f;
      bitData[1] = 0x4f;
      pvalue->freqListC2.component_2.u.choice_2.component_2.u.range_1024.data = (const OSOCTET*)bitData;
   }

   pvalue->m.mobileAllocationC2Present = 1;

   pvalue->mobileAllocationC2.length = 2;

   pvalue->mobileAllocationC2.mac.numbits = 16;
   pvalue->mobileAllocationC2.mac.data[0] = 0x40;
   pvalue->mobileAllocationC2.mac.data[1] = 0x3d;

   pvalue->m.channelDescrC2Present = 1;

   pvalue->channelDescrC2.tsc = 2;

   pvalue->channelDescrC2.component_2.t =  2;

   pvalue->channelDescrC2.component_2.u.choice_2.spare_bit = 0;

   pvalue->channelDescrC2.component_2.u.choice_2.arfcn = 319;

   pvalue->m.descrDownlinkPacketChannelAssignmentType2Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.length = 0; /* length will be calculated */

   pvalue->descrDownlinkPacketChannelAssignmentType2.rlc_mode = 0;

   pvalue->descrDownlinkPacketChannelAssignmentType2.m.component_3Present = 1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_3.p0_c1 = 6;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_3.pr_mode_c1 = 0;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_3.m.component_3Present = 1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_3.component_3.p0_c2 = 13;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_3.component_3.pr_mode_c2 = 0;

   pvalue->descrDownlinkPacketChannelAssignmentType2.m.power_Control_Parameters_C1Present = 1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.alpha = 12;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.m.gamma_tn0Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.gamma_tn0 = 9;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.m.gamma_tn1Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.gamma_tn1 = 2;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.m.gamma_tn2Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.gamma_tn2 = 21;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.m.gamma_tn3Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.gamma_tn3 = 3;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.m.gamma_tn4Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.gamma_tn4 = 1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.m.gamma_tn5Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.gamma_tn5 = 12;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.m.gamma_tn6Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.gamma_tn6 = 13;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.m.gamma_tn7Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C1.gamma_tn7 = 14;

   pvalue->descrDownlinkPacketChannelAssignmentType2.m.power_Control_Parameters_C2Present = 1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.alpha = 0;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.m.gamma_tn0Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.gamma_tn0 = 28;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.m.gamma_tn1Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.gamma_tn1 = 13;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.m.gamma_tn2Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.gamma_tn2 = 3;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.m.gamma_tn3Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.gamma_tn3 = 21;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.m.gamma_tn4Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.gamma_tn4 = 11;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.m.gamma_tn5Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.gamma_tn5 = 14;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.m.gamma_tn6Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.gamma_tn6 = 29;

   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.m.gamma_tn7Present = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.power_Control_Parameters_C2.gamma_tn7 = 24;

   pvalue->descrDownlinkPacketChannelAssignmentType2.m.downlink_tfi_assignmentPresent = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.downlink_tfi_assignment = 0;

   pvalue->descrDownlinkPacketChannelAssignmentType2.egprs_Window_Size = 28;

   pvalue->descrDownlinkPacketChannelAssignmentType2.link_quality_measurement_mode = 0;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_9.t =  2;
   pvalue->descrDownlinkPacketChannelAssignmentType2.component_9.u.choice_2.t =  1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_9.u.choice_2.u.choice_1.component_1.t =  2;

   /* zero elements */

   pvalue->descrDownlinkPacketChannelAssignmentType2.downlink_EGPRS_Level = 0;

   pvalue->descrDownlinkPacketChannelAssignmentType2.m.component_11Present = 1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.m.component_1Present = 1;
   /* zero elements */

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.m.component_2Present = 1;
   /* zero elements */

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.m.component_3Present = 1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.m.component_1Present = 1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_2.downlink_tfi_assignment = 24;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_2.rlc_mode = 0;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_2.m.egprs_Window_SizePresent = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_2.egprs_Window_Size = 18;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_2.pfi = 91;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.m.rlc_Entity_3Present = 1;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_3.downlink_tfi_assignment = 6;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_3.rlc_mode = 0;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_3.m.egprs_Window_SizePresent = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_3.egprs_Window_Size = 23;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_1.rlc_Entity_3.pfi = 2;

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.m.component_2Present = 1;

   /* zero elements */

   /* zero elements */

   /* zero elements */

   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_2.m.egprs_Packet_Downlink_Ack_Nack_Type_3_SupportPresent = 1;
   pvalue->descrDownlinkPacketChannelAssignmentType2.component_11.component_3.component_2.egprs_Packet_Downlink_Ack_Nack_Type_3_Support = 0;

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
      printf ("\n");
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "");
      printf ("\n");
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
