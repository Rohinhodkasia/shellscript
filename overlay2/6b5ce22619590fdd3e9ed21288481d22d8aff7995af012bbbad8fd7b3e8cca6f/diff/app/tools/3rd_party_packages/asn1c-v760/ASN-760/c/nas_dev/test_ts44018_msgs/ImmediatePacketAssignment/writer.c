#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018Msg_ImmediatePacketAssignment*
    asn1Test_TS44018Msg_ImmediatePacketAssignment (OSCTXT* pctxt)
{
   TS44018Msg_ImmediatePacketAssignment* pvalue = rtxMemAllocType (pctxt, TS44018Msg_ImmediatePacketAssignment);
   asn1Init_TS44018Msg_ImmediatePacketAssignment (pvalue);

   pvalue->featureIndicator.spare_bit = 1;

   pvalue->featureIndicator.cs_ir = 0;

   pvalue->featureIndicator.ps_ir = 0;

   pvalue->pageMode.spare_bit = 1;

   pvalue->pageMode.pm = 1;

   return (pvalue);
}


TS44018IE_IPA_Rest_Octets* asn1Test_TS44018IE_IPA_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_IPA_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_IPA_Rest_Octets);
   asn1Init_TS44018IE_IPA_Rest_Octets (pvalue);

   pvalue->m.ipa_Uplink_Assignment_structPresent = 1;

   /* zero elements */

   pvalue->ipa_Uplink_Assignment_struct.tn = 4;

   pvalue->ipa_Uplink_Assignment_struct.m.frequency_ParametersPresent = 1;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.tsc = 6;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.t =  3;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.maio = 29;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.hsn = 16;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.n = 7;
   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem = rtxMemAllocArrayZ (pctxt, 7, OSUINT8);
   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[0] = 9;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[1] = 4;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[2] = 3;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[3] = 0;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[4] = 5;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[5] = 8;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[6] = 13;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.t =  1;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_length = 20;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_bitmap.numbits = 21;
   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_bitmap.data[0] = 0x5d;
   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_bitmap.data[1] = 0x4d;
   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_bitmap.data[2] = 0x46;

   pvalue->m.ipa_Downlink_Assignment_structPresent = 1;

   /* zero elements */

   pvalue->ipa_Downlink_Assignment_struct.m.link_quality_measurement_modePresent = 1;
   pvalue->ipa_Downlink_Assignment_struct.link_quality_measurement_mode = 2;

   pvalue->ipa_Downlink_Assignment_struct.rlc_mode = 0;

   pvalue->ipa_Downlink_Assignment_struct.tn = 2;

   pvalue->ipa_Downlink_Assignment_struct.m.frequency_ParametersPresent = 1;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.tsc = 3;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.t =  2;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.indirect_encoding.maio = 57;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.indirect_encoding.ma_number = 6;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.indirect_encoding.m.component_3Present = 1;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.indirect_encoding.component_3.change_mark_1 = 1;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.indirect_encoding.component_3.m.change_mark_2Present = 1;
   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.indirect_encoding.component_3.change_mark_2 = 0;

   pvalue->m.ipa_Single_Block_Uplink_Assignment_structPresent = 1;

   /* zero elements */

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.tn = 2;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.m.frequency_ParametersPresent = 1;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.tsc = 1;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.t =  4;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_2.maio = 26;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_2.hsn = 51;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_2.length_of_MA_Frequency_List_contents = 0;

   {
      static const OSOCTET testdata[] = { 
      0x3c, 0x02, 0x29 };
      pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_2.ma_Frequency_List_contents.numocts = 3;
      OSCRTLSAFEMEMCPY ((void*)pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_2.ma_Frequency_List_contents.data, 3, testdata, 3);
   }

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
   pdu.msgType = ASN1V_ts44018Msg_mt_ImmediatePacketAssignment;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_ImmediatePacketAssignment;
   pdu.data.u.obj_ImmediatePacketAssignment =
      asn1Test_TS44018Msg_ImmediatePacketAssignment(pctxt);

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_ImmediatePacketAssignment;
   pdu.restOctets.u.obj_ImmediatePacketAssignment =
      asn1Test_TS44018IE_IPA_Rest_Octets(pctxt);


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
