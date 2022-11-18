#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"
#include  "rt3gppsrc/rtx3GPP.h"

#define MAXMSGLEN 300

int main (int argc, char** argv)
{
   TS44018Msg_DL_DCCH_PDU pdu;
   TS44018Msg_AssignmentCommand acData;
   TS44018Msg_AssignmentCommand* pvalue = &acData;

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
   pdu.msgType = ASN1V_ts44018Msg_mt_AssignmentCommand;
   pdu.data.t = T_TS44018Msgs_DL_DCCH_Messages_obj_AssignmentCommand;
   pdu.data.u.obj_AssignmentCommand = pvalue;


   asn1Init_TS44018Msg_AssignmentCommand (pvalue);

   pvalue->descFirstChannelAfterTime.channel_type_and_TDMA_offset = 19;

   pvalue->descFirstChannelAfterTime.tn = 5;

   pvalue->descFirstChannelAfterTime.tsc = 1;

   pvalue->descFirstChannelAfterTime.component_4.t =  2;

   pvalue->descFirstChannelAfterTime.component_4.u.choice_2.arfcn = 798;

   pvalue->powerCommand.epc_mode = 0;

   pvalue->powerCommand.fpc_epc = 0;

   pvalue->powerCommand.power_level = 30;

   pvalue->m.freqListAfterTimePresent = 1;

   pvalue->freqListAfterTime.length = 0;  /* set by encoder */

   pvalue->freqListAfterTime.component_2.t = 1;
   {
      OSUINT16 arfcns[] = { 4, 124, 9, 1, 8, 15, 16, 101 };
      OSSIZE arfcn_count = sizeof(arfcns) / sizeof(OSUINT16);
      OSSIZE numbits;
      OSOCTET* buffer = pvalue->freqListAfterTime.component_2.u.bitmap0.bitmap0;
      
      ret = rtx3GPPEncARFCN(pctxt, arfcns, arfcn_count, 
               OS3GPP_FREQ_LIST_FMT_BITMAP0, 0 /*range*/, 0 /*f0*/,
               &buffer, 
               sizeof(pvalue->freqListAfterTime.component_2.u.bitmap0.bitmap0 )/*bufferSize*/,
               &numbits );

      if ( ret < 0 ) {
         rtxErrPrint (&ctxt);
         return LOG_RTERR(pctxt, ret);
      }
   }

   pvalue->m.cellChannelDescPresent = 1;
   pvalue->cellChannelDesc.t =  2;

   pvalue->cellChannelDesc.u.choice_2.component_2.t = 
                     T_Cell_Channel_Description_choice_2_component_2_range_1024;

   {
      OSUINT16 arfcns[] = { 528, 68, 55, 22, 26, 10, 28, 4, 5, 14, 7, 11, 8 };
      OSSIZE arfcn_count = sizeof(arfcns) / sizeof(OSUINT16);
      OSUINT16 f0;
      OSUINT16 range;
      OSSIZE numbits;
      OSOCTET* buffer = pvalue->cellChannelDesc.u.choice_2.component_2.u.range_1024;

      rtx3GPPGetARFCNRange(arfcns, arfcn_count, &f0, &range);
      
      ret = rtx3GPPEncARFCN(pctxt, arfcns, arfcn_count, 
               OS3GPP_FREQ_LIST_FMT_RANGE_1024, range, f0,
               &buffer, 16 /*bufferSize*/,
               &numbits );

      if ( ret < 0 ) {
         rtxErrPrint (&ctxt);
         return LOG_RTERR(pctxt, ret);
      }
   }

   pvalue->m.descMultislotConfigPresent = 1;

   pvalue->descMultislotConfig.length = 0;
   pvalue->descMultislotConfig.da = 67;
   pvalue->descMultislotConfig.m.uaPresent = 1;
   pvalue->descMultislotConfig.ua = 99;
   pvalue->descMultislotConfig.channel_sets.n = 0;

   pvalue->m.modeFirstChannelPresent = 1;
   pvalue->modeFirstChannel = 247;

   pvalue->m.modeChannelSet2Present = 1;
   pvalue->modeChannelSet2 = 163;

   pvalue->m.modeChannelSet3Present = 1;
   pvalue->modeChannelSet3 = 201;

   pvalue->m.modeChannelSet4Present = 1;
   pvalue->modeChannelSet4 = 57;

   pvalue->m.modeChannelSet5Present = 1;
   pvalue->modeChannelSet5 = 127;

   pvalue->m.modeChannelSet6Present = 1;
   pvalue->modeChannelSet6 = 119;

   pvalue->m.modeChannelSet7Present = 1;
   pvalue->modeChannelSet7 = 214;

   pvalue->m.modeChannelSet8Present = 1;
   pvalue->modeChannelSet8 = 38;

   pvalue->m.descSecondChannelAfterTimePresent = 1;

   pvalue->descSecondChannelAfterTime.channel_type_and_TDMA_offset = 10;

   pvalue->descSecondChannelAfterTime.tn = 5;

   pvalue->descSecondChannelAfterTime.tsc = 4;

   pvalue->descSecondChannelAfterTime.component_4.t =  1;

   pvalue->descSecondChannelAfterTime.component_4.u.choice_1.maio = 6;

   pvalue->descSecondChannelAfterTime.component_4.u.choice_1.hsn = 50;

   pvalue->m.modeSecondChannelPresent = 1;
   pvalue->modeSecondChannel = 247;

   pvalue->m.mobileAllocationAfterTimePresent = 1;

   pvalue->mobileAllocationAfterTime.length = 6;

   pvalue->mobileAllocationAfterTime.mac.numbits = 48;
   pvalue->mobileAllocationAfterTime.mac.data[0] = 0x49;
   pvalue->mobileAllocationAfterTime.mac.data[1] = 0x6d;
   pvalue->mobileAllocationAfterTime.mac.data[2] = 0x62;
   pvalue->mobileAllocationAfterTime.mac.data[3] = 0x3d;
   pvalue->mobileAllocationAfterTime.mac.data[4] = 0x60;
   pvalue->mobileAllocationAfterTime.mac.data[5] = 0x32;

   pvalue->m.startingTimePresent = 1;

   pvalue->startingTime.t1prime = 0;

   pvalue->startingTime.t3 = 4;

   pvalue->m.frequencyListBeforeTimePresent = 1;

   pvalue->frequencyListBeforeTime.length = 0;  /* set by encoder */

   pvalue->frequencyListBeforeTime.component_2.t = 2;
   {
      OSUINT16 arfcns[] = { 513, 514, 511, 501, 521 };
      OSSIZE arfcn_count = sizeof(arfcns) / sizeof(OSUINT16), numbits;
      OSUINT16 f0;
      OSUINT16 range;
      OSOCTET* data = 0;   /* used to avoid warnings about const-ness, since
                              data in the generated struct is pointer to const.
                           */

      pvalue->frequencyListBeforeTime.component_2.u.choice_2.component_2.t = 5;
      pvalue->frequencyListBeforeTime.component_2.u.choice_2.component_2.u.variable_bitmap.data = 0;
      
      rtx3GPPGetARFCNRange(arfcns, arfcn_count, &f0, &range);

      ret = rtx3GPPEncARFCN(pctxt, arfcns, arfcn_count, 
               OS3GPP_FREQ_LIST_FMT_VAR_BITMAP, range, f0,
               &data, 0 /*bufferSize*/, &numbits);

      pvalue->frequencyListBeforeTime.component_2.u.choice_2.component_2.u.variable_bitmap.numbits = numbits;
      pvalue->frequencyListBeforeTime.component_2.u.choice_2.component_2.u.variable_bitmap.data = data;

      if ( ret < 0 ) {
         rtxErrPrint (&ctxt);
         return LOG_RTERR(pctxt, ret);
      }
   }


   pvalue->m.descFirstChannelBeforeTimePresent = 1;

   pvalue->descFirstChannelBeforeTime.channel_type_and_TDMA_offset = 4;

   pvalue->descFirstChannelBeforeTime.tn = 3;

   pvalue->descFirstChannelBeforeTime.tsc = 3;

   pvalue->descFirstChannelBeforeTime.component_4.t =  2;

   pvalue->descFirstChannelBeforeTime.component_4.u.choice_2.arfcn = 7;

   pvalue->m.descSecondChannelBeforeTimePresent = 1;

   pvalue->descSecondChannelBeforeTime.channel_type_and_TDMA_offset = 20;

   pvalue->descSecondChannelBeforeTime.tn = 1;

   pvalue->descSecondChannelBeforeTime.tsc = 3;

   pvalue->descSecondChannelBeforeTime.component_4.t =  2;

   pvalue->descSecondChannelBeforeTime.component_4.u.choice_2.arfcn = 322;

   pvalue->m.frequencyChannelSequenceBeforeTimePresent = 1;

   pvalue->frequencyChannelSequenceBeforeTime.lowest_arfcn = 92;

   pvalue->frequencyChannelSequenceBeforeTime.inc_skip.elem[0] = 12;

   pvalue->frequencyChannelSequenceBeforeTime.inc_skip.elem[1] = 12;

   pvalue->frequencyChannelSequenceBeforeTime.inc_skip.elem[2] = 0;

   pvalue->frequencyChannelSequenceBeforeTime.inc_skip.elem[3] = 4;

   pvalue->frequencyChannelSequenceBeforeTime.inc_skip.elem[4] = 8;

   pvalue->frequencyChannelSequenceBeforeTime.inc_skip.elem[5] = 12;

   pvalue->frequencyChannelSequenceBeforeTime.inc_skip.elem[6] = 4;

   pvalue->frequencyChannelSequenceBeforeTime.inc_skip.elem[7] = 3;

   pvalue->frequencyChannelSequenceBeforeTime.inc_skip.elem[8] = 5;

   pvalue->frequencyChannelSequenceBeforeTime.inc_skip.elem[9] = 4;

   pvalue->frequencyChannelSequenceBeforeTime.inc_skip.elem[10] = 12;

   pvalue->frequencyChannelSequenceBeforeTime.inc_skip.elem[11] = 3;

   pvalue->frequencyChannelSequenceBeforeTime.inc_skip.elem[12] = 13;

   pvalue->frequencyChannelSequenceBeforeTime.inc_skip.elem[13] = 7;

   pvalue->frequencyChannelSequenceBeforeTime.inc_skip.elem[14] = 6;

   pvalue->frequencyChannelSequenceBeforeTime.inc_skip.elem[15] = 5;

   pvalue->m.mobileAllocationBeforeTimePresent = 1;

   pvalue->mobileAllocationBeforeTime.length = 4;

   pvalue->mobileAllocationBeforeTime.mac.numbits = 32;
   pvalue->mobileAllocationBeforeTime.mac.data[0] = 0x47;
   pvalue->mobileAllocationBeforeTime.mac.data[1] = 0x37;
   pvalue->mobileAllocationBeforeTime.mac.data[2] = 0x40;
   pvalue->mobileAllocationBeforeTime.mac.data[3] = 0x37;

   pvalue->m.cipherModeSettingPresent = 1;

   pvalue->cipherModeSetting.algorithm_id = 6;

   pvalue->cipherModeSetting.sc = 0;

   pvalue->m.vgcsTargetModeIndicationPresent = 1;
   pvalue->vgcsTargetModeIndication.length = 0; /* length will be calculated */

   pvalue->vgcsTargetModeIndication.target_mode = 0;

   pvalue->vgcsTargetModeIndication.group_cipher_key_num = 3;

   pvalue->m.multiRateConfigPresent = 1;
   
   pvalue->multiRateConfig.multirate_speech_version = 1;

   pvalue->multiRateConfig.nscb = 0;

   pvalue->multiRateConfig.icmi = 0;

   pvalue->multiRateConfig.start_mode = 1;

   /* two bits in amr_codec_modes are set so there should be 1 thr/hyst pair. */
   pvalue->multiRateConfig.amr_codec_modes = 0x03;
   pvalue->multiRateConfig.params.n = 1;
   pvalue->multiRateConfig.params.elem[0].threshold = 45;
   pvalue->multiRateConfig.params.elem[0].hysteresis = 7;

   pvalue->m.vgcsCipheringParametersPresent = 1;

   pvalue->vgcsCipheringParameters.b22_count = 0;

   pvalue->vgcsCipheringParameters.cell_global_count = 0;

   pvalue->vgcsCipheringParameters.m.cell_identityPresent = 1;
   pvalue->vgcsCipheringParameters.cell_identity = 187;

   pvalue->vgcsCipheringParameters.m.location_area_identificationPresent = 1;
   pvalue->vgcsCipheringParameters.location_area_identification[0] = 9;
   pvalue->vgcsCipheringParameters.location_area_identification[1] = 8;
   pvalue->vgcsCipheringParameters.location_area_identification[2] = 7;
   pvalue->vgcsCipheringParameters.location_area_identification[3] = 6;
   pvalue->vgcsCipheringParameters.location_area_identification[4] = 5;

   pvalue->vgcsCipheringParameters.m.vstk_randPresent = 1;   
   pvalue->vgcsCipheringParameters.vstk_rand[0] = 0xd3;
   pvalue->vgcsCipheringParameters.vstk_rand[1] = 0x4c;
   pvalue->vgcsCipheringParameters.vstk_rand[2] = 0x3c;
   pvalue->vgcsCipheringParameters.vstk_rand[3] = 0xe5;
   pvalue->vgcsCipheringParameters.vstk_rand[4] = 0xab;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_DL_DCCH_PDU (&ctxt, &pdu);
   if (0 != ret) {
      printf ("encode PDU failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);

      if ( verbose ) {
         printf ("\n");
         printf ("Bit fields:\n");
         rtxDiagBitTracePrint (ctxt.pBitFldList, "");
         printf ("\n");
      }

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

   /* Verify buffer is byte-aligned */
   OSRTASSERT (ctxt.buffer.bitOffset == 8 || ctxt.buffer.bitOffset == 0);

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
