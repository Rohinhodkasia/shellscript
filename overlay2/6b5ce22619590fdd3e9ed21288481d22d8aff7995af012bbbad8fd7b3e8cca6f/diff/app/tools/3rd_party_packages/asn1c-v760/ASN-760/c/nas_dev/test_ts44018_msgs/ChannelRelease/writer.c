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
   TS44018Msg_ChannelRelease data;
   TS44018Msg_ChannelRelease* pvalue = &data;

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
   pdu.msgType = ASN1V_ts44018Msg_mt_ChannelRelease;
   pdu.data.t = T_TS44018Msgs_DL_DCCH_Messages_obj_ChannelRelease;
   pdu.data.u.obj_ChannelRelease = pvalue;


   asn1Init_TS44018Msg_ChannelRelease (pvalue);

   pvalue->rrCause = 155;

   pvalue->m.baRangePresent = 1;
   pvalue->baRange.length = 0; /* length will be calculated */

   pvalue->baRange.num_ranges = 0;

   /* zero elements */

   pvalue->m.groupChannelDescriptionPresent = 1;
   pvalue->groupChannelDescription.length = 0; /* length will be calculated */

   pvalue->groupChannelDescription.channel_type_and_TDMA_offset = 22;

   pvalue->groupChannelDescription.tn = 4;

   pvalue->groupChannelDescription.tsc = 6;

   pvalue->groupChannelDescription.component_5.t =  2;

   pvalue->groupChannelDescription.component_5.u.choice_2.spare_bit = 0;

   pvalue->groupChannelDescription.component_5.u.choice_2.arfcn = 241;

   pvalue->groupChannelDescription.mac.numocts = 3;
   {
      OSOCTET* bitData = (OSOCTET*) rtxMemAlloc (pctxt,1);
      bitData[0] = 0x5e;
      bitData[1] = 0xab;
      bitData[2] = 0xcd;
      pvalue->groupChannelDescription.mac.data = (const OSOCTET*)bitData;
   }

   pvalue->m.groupCipherKeyNumberPresent = 1;
   pvalue->groupCipherKeyNumber = 7;

   pvalue->m.gprsResumptionPresent = 1;

   pvalue->gprsResumption.spare_bit = 3;

   pvalue->gprsResumption.ack = 0;

   pvalue->m.baListPrefPresent = 1;
   pvalue->baListPref.length_of_ba_list_pref = 0; /* length will be calculated */

   /* zero elements */

   pvalue->baListPref.ba_freq_list.n = 7;
   pvalue->baListPref.ba_freq_list.elem = rtxMemAllocArrayZ (pctxt, 7, OSUINT16);
   pvalue->baListPref.ba_freq_list.elem[0] = 420;

   pvalue->baListPref.ba_freq_list.elem[1] = 49;

   pvalue->baListPref.ba_freq_list.elem[2] = 284;

   pvalue->baListPref.ba_freq_list.elem[3] = 878;

   pvalue->baListPref.ba_freq_list.elem[4] = 848;

   pvalue->baListPref.ba_freq_list.elem[5] = 565;

   pvalue->baListPref.ba_freq_list.elem[6] = 265;

   pvalue->m.utranFreqListPresent = 1;
   pvalue->utranFreqList.length_of_utran_freq_list = 0; /* length will be calculated */

   pvalue->utranFreqList.fdd_arfcn_list.n = 4;
   pvalue->utranFreqList.fdd_arfcn_list.elem = rtxMemAllocArrayZ (pctxt, 4, OSUINT16);
   pvalue->utranFreqList.fdd_arfcn_list.elem[0] = 1825;

   pvalue->utranFreqList.fdd_arfcn_list.elem[1] = 298;

   pvalue->utranFreqList.fdd_arfcn_list.elem[2] = 8976;

   pvalue->utranFreqList.fdd_arfcn_list.elem[3] = 2769;

   pvalue->utranFreqList.tdd_arfcn_list.n = 2;
   pvalue->utranFreqList.tdd_arfcn_list.elem = rtxMemAllocArrayZ (pctxt, 2, OSUINT16);
   pvalue->utranFreqList.tdd_arfcn_list.elem[0] = 1356;

   pvalue->utranFreqList.tdd_arfcn_list.elem[1] = 13103;

   pvalue->m.cellChannelDescPresent = 1;
   pvalue->cellChannelDesc.t =  1;

   pvalue->cellChannelDesc.u.bitmap0.spare_bit = 1;

   pvalue->cellChannelDesc.u.bitmap0.bitmap0[0] = 0xe8;
   pvalue->cellChannelDesc.u.bitmap0.bitmap0[1] = 0xb1;
   pvalue->cellChannelDesc.u.bitmap0.bitmap0[2] = 0x3b;
   pvalue->cellChannelDesc.u.bitmap0.bitmap0[3] = 0xe4;
   pvalue->cellChannelDesc.u.bitmap0.bitmap0[4] = 0xf7;
   pvalue->cellChannelDesc.u.bitmap0.bitmap0[5] = 0x2d;
   pvalue->cellChannelDesc.u.bitmap0.bitmap0[6] = 0x1b;
   pvalue->cellChannelDesc.u.bitmap0.bitmap0[7] = 0xe8;
   pvalue->cellChannelDesc.u.bitmap0.bitmap0[8] = 0xbe;
   pvalue->cellChannelDesc.u.bitmap0.bitmap0[9] = 0x9f;
   pvalue->cellChannelDesc.u.bitmap0.bitmap0[10] = 0xb2;
   pvalue->cellChannelDesc.u.bitmap0.bitmap0[11] = 0x10;
   pvalue->cellChannelDesc.u.bitmap0.bitmap0[12] = 0xd7;
   pvalue->cellChannelDesc.u.bitmap0.bitmap0[13] = 0xb3;
   pvalue->cellChannelDesc.u.bitmap0.bitmap0[14] = 0x4e;
   pvalue->cellChannelDesc.u.bitmap0.bitmap0[15] = 0xcf;

   pvalue->m.cellSelIndAfterReleasePresent = 1;
   pvalue->cellSelIndAfterRelease.length = 0; /* length will be calculated */

   pvalue->cellSelIndAfterRelease.component_2.t =  1;
   /* zero elements */

   pvalue->m.enhancedDtmCsReleaseIndPresent = 1;

   pvalue->enhancedDtmCsReleaseInd.spare_bit = 3;

   pvalue->enhancedDtmCsReleaseInd.ind = 0;

   pvalue->m.vgcsCipheringParamsPresent = 1;

   pvalue->vgcsCipheringParams.b22_count = 0;

   pvalue->vgcsCipheringParams.cell_global_count = 1;

   pvalue->vgcsCipheringParams.m.cell_identityPresent = 1;
   pvalue->vgcsCipheringParams.cell_identity = 36;

   pvalue->vgcsCipheringParams.m.location_area_identificationPresent = 1;
   {
      static const OSOCTET testdata[] = { 
      0xde, 0x56, 0x92, 0x79, 0x3a };
      OSCRTLSAFEMEMCPY ((void*)pvalue->vgcsCipheringParams.location_area_identification, 5, testdata, 5);
   }

   pvalue->vgcsCipheringParams.m.vstk_randPresent = 1;
   pvalue->vgcsCipheringParams.vstk_rand[0] = 0x8;
   pvalue->vgcsCipheringParams.vstk_rand[1] = 0x5f;
   pvalue->vgcsCipheringParams.vstk_rand[2] = 0x2;
   pvalue->vgcsCipheringParams.vstk_rand[3] = 0x9b;
   pvalue->vgcsCipheringParams.vstk_rand[4] = 0x9b;

   pvalue->m.groupChannelDesc2Present = 1;
   pvalue->groupChannelDesc2.length = 0; /* length will be calculated */

   pvalue->groupChannelDesc2.channel_type_and_TDMA_offset = 19;

   pvalue->groupChannelDesc2.tn = 1;

   pvalue->groupChannelDesc2.tsc = 1;

   pvalue->groupChannelDesc2.spare_bit = 0;

   pvalue->groupChannelDesc2.maio = 3;

   pvalue->groupChannelDesc2.hsn = 25;

   pvalue->groupChannelDesc2.frequency_Short_List_2.component_1 = 2;

   pvalue->groupChannelDesc2.frequency_Short_List_2.spare_bit = 1;

   pvalue->groupChannelDesc2.frequency_Short_List_2.component_3.t =  1;
   pvalue->groupChannelDesc2.frequency_Short_List_2.component_3.u.range_1024[0] = 0x8;
   pvalue->groupChannelDesc2.frequency_Short_List_2.component_3.u.range_1024[1] = 0xab;
   pvalue->groupChannelDesc2.frequency_Short_List_2.component_3.u.range_1024[2] = 0xdf;
   pvalue->groupChannelDesc2.frequency_Short_List_2.component_3.u.range_1024[3] = 0x28;
   pvalue->groupChannelDesc2.frequency_Short_List_2.component_3.u.range_1024[4] = 0x2a;
   pvalue->groupChannelDesc2.frequency_Short_List_2.component_3.u.range_1024[5] = 0xb0;
   pvalue->groupChannelDesc2.frequency_Short_List_2.component_3.u.range_1024[6] = 0xcb;

   pvalue->m.talkerIdPresent = 1;
   pvalue->talkerId.length = 0; /* length will be calculated */

   pvalue->talkerId.spare_bit = 29;

   pvalue->talkerId.filler = 4;

   pvalue->talkerId.talker_id_field.numocts = 6;
   {
      OSOCTET* bitData = (OSOCTET*) rtxMemAlloc (pctxt,1);
      bitData[0] = 0xa1;
      bitData[1] = 0xb2;
      bitData[2] = 0xc3;
      bitData[3] = 0xd4;
      bitData[4] = 0xe5;
      bitData[5] = 0xf6;
      pvalue->talkerId.talker_id_field.data = (const OSOCTET*)bitData;
   }

   pvalue->m.talkerPriorityStatusPresent = 1;
   pvalue->talkerPriorityStatus.length = 0; /* length will be calculated */

   pvalue->talkerPriorityStatus.es = 0;

   pvalue->talkerPriorityStatus.spare_bit = 0;

   pvalue->talkerPriorityStatus.uai = 0;

   pvalue->talkerPriorityStatus.priority = 5;

   pvalue->m.vgcsAmrConfigPresent = 1;
   pvalue->vgcsAmrConfig.length = 0; /* length will be calculated */

   pvalue->vgcsAmrConfig.amr_config = 9;

   pvalue->vgcsAmrConfig.spare_bit = 8;

   pvalue->m.individualPrioritiesPresent = 1;
   pvalue->individualPriorities.length = 0; /* length will be calculated */

   pvalue->individualPriorities.m.component_2Present = 1;

   pvalue->individualPriorities.component_2.geran_priority = 6;

   pvalue->individualPriorities.component_2.m.a3G_Individual_Priority_Parameters_DescriptionPresent = 1;

   pvalue->individualPriorities.component_2.a3G_Individual_Priority_Parameters_Description.m.default_utran_priorityPresent = 1;
   pvalue->individualPriorities.component_2.a3G_Individual_Priority_Parameters_Description.default_utran_priority = 3;

   /* zero elements */

   pvalue->individualPriorities.component_2.m.e_UTRAN_Individual_Priority_Parameters_DescriptionPresent = 1;

   pvalue->individualPriorities.component_2.e_UTRAN_Individual_Priority_Parameters_Description.m.default_e_utran_priorityPresent = 1;
   pvalue->individualPriorities.component_2.e_UTRAN_Individual_Priority_Parameters_Description.default_e_utran_priority = 0;

   /* zero elements */

   pvalue->individualPriorities.component_2.m.t3230_timeout_valuePresent = 1;
   pvalue->individualPriorities.component_2.t3230_timeout_value = 2;

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
