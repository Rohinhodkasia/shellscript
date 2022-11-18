#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018Msg_ImmediateAssignment*
    asn1Test_TS44018Msg_ImmediateAssignment (OSCTXT* pctxt)
{
   TS44018Msg_ImmediateAssignment* pvalue = rtxMemAllocType (pctxt, TS44018Msg_ImmediateAssignment);
   asn1Init_TS44018Msg_ImmediateAssignment (pvalue);

   pvalue->dedicatedModeOrTBF.spare_bit = 0;

   pvalue->dedicatedModeOrTBF.tma = 0;

   pvalue->dedicatedModeOrTBF.downlink = 0;

   pvalue->dedicatedModeOrTBF.tbf_or_dedicated = 0;

   pvalue->pageMode.spare_bit = 0;

   pvalue->pageMode.pm = 2;

   pvalue->channelDescr.channel_type_and_TDMA_offset = 9;

   pvalue->channelDescr.tn = 4;

   pvalue->channelDescr.tsc = 0;

   pvalue->channelDescr.component_4.t =  1;

   pvalue->channelDescr.component_4.u.choice_1.maio = 58;

   pvalue->channelDescr.component_4.u.choice_1.hsn = 16;

   pvalue->requestReference.ra = 118;

   pvalue->requestReference.t1prime = 9;

   pvalue->requestReference.t3 = 28;

   pvalue->requestReference.t2 = 9;

   pvalue->timingAdvance = 19;

   pvalue->mobileAllocation.length = 20;

   pvalue->mobileAllocation.mac.numbits = 160;
   pvalue->mobileAllocation.mac.data[0] = 0x60;
   pvalue->mobileAllocation.mac.data[1] = 0x54;
   pvalue->mobileAllocation.mac.data[2] = 0x43;
   pvalue->mobileAllocation.mac.data[3] = 0x66;
   pvalue->mobileAllocation.mac.data[4] = 0x70;
   pvalue->mobileAllocation.mac.data[5] = 0x40;
   pvalue->mobileAllocation.mac.data[6] = 0x59;
   pvalue->mobileAllocation.mac.data[7] = 0x50;
   pvalue->mobileAllocation.mac.data[8] = 0x63;
   pvalue->mobileAllocation.mac.data[9] = 0x6b;
   pvalue->mobileAllocation.mac.data[10] = 0x72;
   pvalue->mobileAllocation.mac.data[11] = 0x3e;
   pvalue->mobileAllocation.mac.data[12] = 0x65;
   pvalue->mobileAllocation.mac.data[13] = 0x6b;
   pvalue->mobileAllocation.mac.data[14] = 0x63;
   pvalue->mobileAllocation.mac.data[15] = 0x3e;
   pvalue->mobileAllocation.mac.data[16] = 0x6c;
   pvalue->mobileAllocation.mac.data[17] = 0x44;
   pvalue->mobileAllocation.mac.data[18] = 0x75;
   pvalue->mobileAllocation.mac.data[19] = 0x71;

   pvalue->m.startingTimePresent = 1;

   pvalue->startingTime.t1prime = 0;

   pvalue->startingTime.t3 = 46;

   pvalue->startingTime.spare_bit = 5;
   return (pvalue);
}


TS44018IE_IA_Rest_Octets* asn1Test_TS44018IE_IA_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_IA_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_IA_Rest_Octets);
   asn1Init_TS44018IE_IA_Rest_Octets (pvalue);

   pvalue->t =  4;

   pvalue->u.choice_4.component_1.t =  2;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.tlli = 12318;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.m.component_2Present = 1;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_2.tfi_assignment = 15;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_2.rlc_mode = 0;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_2.m.alphaPresent = 1;
   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_2.alpha = 10;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_2.gamma = 13;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_2.polling = 0;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_2.ta_valid = 0;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.m.timing_advance_indexPresent = 1;
   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.timing_advance_index = 8;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.m.tbf_starting_timePresent = 1;
   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.tbf_starting_time = 28097;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.m.component_5Present = 1;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_5.p0 = 5;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_5.component_2 = 0;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_5.pr_mode = 0;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.m.component_6Present = 1;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_6.egprs_Window_Size = 19;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_6.link_quality_measurement_mode = 1;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_6.m.bep_period2Present = 1;
   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_6.bep_period2 = 12;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.m.component_7Present = 1;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_7.m.pfiPresent = 1;
   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_7.pfi = 18;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.m.component_8Present = 1;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_8.m.npm_Transfer_TimePresent = 1;
   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_8.npm_Transfer_Time = 15;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_8.component_2.t =  2;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_8.component_2.u.choice_2.event_based_fanr = 0;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_8.component_2.u.choice_2.pdch_pair_indication = 4;

   pvalue->u.choice_4.component_1.u.packet_Downlink_Assignment.component_8.downlink_EGPRS_Level = 2;

   pvalue->u.choice_4.m.component_2Present = 1;

   pvalue->u.choice_4.component_2.implicit_Reject_CS = 0;

   pvalue->u.choice_4.component_2.implicit_Reject_PS = 0;
   return (pvalue);
}


int main (int argc, char** argv)
{
   TS44018Msg_L2_PSEUDO_LEN_PDU pdu;

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

   asn1Init_TS44018Msg_L2_PSEUDO_LEN_PDU (&pdu);
   pdu.l3HdrOpts.t = 1;
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;
   pdu.msgType = ASN1V_ts44018Msg_mt_ImmediateAssignment;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_ImmediateAssignment;
   pdu.data.u.obj_ImmediateAssignment = 
      asn1Test_TS44018Msg_ImmediateAssignment(pctxt);

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_ImmediateAssignment;
   pdu.restOctets.u.obj_ImmediateAssignment = 
      asn1Test_TS44018IE_IA_Rest_Octets(pctxt);


   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_L2_PSEUDO_LEN_PDU (&ctxt, &pdu);
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
