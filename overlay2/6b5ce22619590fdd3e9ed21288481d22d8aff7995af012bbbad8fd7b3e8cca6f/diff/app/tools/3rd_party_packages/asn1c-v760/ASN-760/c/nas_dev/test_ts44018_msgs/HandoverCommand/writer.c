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
   TS44018Msg_HandoverCommand data;
   TS44018Msg_HandoverCommand* pvalue = &data;

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
   pdu.msgType = ASN1V_ts44018Msg_mt_HandoverCommand;
   pdu.data.t = T_TS44018Msgs_DL_DCCH_Messages_obj_HandoverCommand;
   pdu.data.u.obj_HandoverCommand = pvalue;


   asn1Init_TS44018Msg_HandoverCommand (pvalue);

   pvalue->cellDescr.bcch_arfcn_high = 2;

   pvalue->cellDescr.ncc = 3;

   pvalue->cellDescr.bcc = 2;

   pvalue->cellDescr.bcch_arfcn_low = 117;

   pvalue->descrFirstChannelAfterTime.channel_type_and_TDMA_offset = 21;

   pvalue->descrFirstChannelAfterTime.tn = 3;

   pvalue->descrFirstChannelAfterTime.tsc = 0;

   pvalue->descrFirstChannelAfterTime.component_4.t =  1;

   pvalue->descrFirstChannelAfterTime.component_4.u.choice_1.maio = 11;

   pvalue->descrFirstChannelAfterTime.component_4.u.choice_1.hsn = 43;

   pvalue->handoverReference = 125;

   pvalue->powerCommandAndAccessType.atc = 0;

   pvalue->powerCommandAndAccessType.epc_mode = 0;

   pvalue->powerCommandAndAccessType.fpc_epc = 0;

   pvalue->powerCommandAndAccessType.power_level = 4;

   pvalue->m.synchronizationIndicationPresent = 1;

   pvalue->synchronizationIndication.nci = 0;

   pvalue->synchronizationIndication.rot = 0;

   pvalue->synchronizationIndication.si = 2;

   pvalue->m.freqShortListAfterTimePresent = 1;

   pvalue->freqShortListAfterTime.component_1 = 2;

   pvalue->freqShortListAfterTime.spare_bit = 2;

   pvalue->freqShortListAfterTime.component_3.t =  4;
   pvalue->freqShortListAfterTime.component_3.u.range_128[0] = 0xbe;
   pvalue->freqShortListAfterTime.component_3.u.range_128[1] = 0xa9;
   pvalue->freqShortListAfterTime.component_3.u.range_128[2] = 0xb9;
   pvalue->freqShortListAfterTime.component_3.u.range_128[3] = 0x39;
   pvalue->freqShortListAfterTime.component_3.u.range_128[4] = 0xb;
   pvalue->freqShortListAfterTime.component_3.u.range_128[5] = 0xb9;
   pvalue->freqShortListAfterTime.component_3.u.range_128[6] = 0x41;
   pvalue->freqShortListAfterTime.component_3.u.range_128[7] = 0xa3;
   pvalue->freqShortListAfterTime.component_3.u.range_128[8] = 0x33;

   pvalue->m.freqListAfterTimePresent = 1;
   pvalue->freqListAfterTime.length = 0; /* length will be calculated */

   pvalue->freqListAfterTime.component_2.t =  2;

   pvalue->freqListAfterTime.component_2.u.choice_2.spare_bit = 0;

   pvalue->freqListAfterTime.component_2.u.choice_2.component_2.t =  2;
   pvalue->freqListAfterTime.component_2.u.choice_2.component_2.u.range_512.numbits = 17;
   {
      OSOCTET* bitData = (OSOCTET*) rtxMemAlloc (pctxt,3);
      bitData[0] = 0x6a;
      bitData[1] = 0x6a;
      bitData[2] = 0x6a;
      pvalue->freqListAfterTime.component_2.u.choice_2.component_2.u.range_512.data = (const OSOCTET*)bitData;
   }

   pvalue->m.cellChannelDescrPresent = 1;
   pvalue->cellChannelDescr.t =  2;

   pvalue->cellChannelDescr.u.choice_2.spare_bit = 0;

   pvalue->cellChannelDescr.u.choice_2.component_2.t =  1;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_1024[0] = 0x41;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_1024[1] = 0x66;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_1024[2] = 0xf6;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_1024[3] = 0xb2;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_1024[4] = 0xa7;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_1024[5] = 0x3e;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_1024[6] = 0x7;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_1024[7] = 0x74;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_1024[8] = 0x57;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_1024[9] = 0xec;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_1024[10] = 0xe4;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_1024[11] = 0x2b;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_1024[12] = 0xe;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_1024[13] = 0xc7;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_1024[14] = 0xa4;
   pvalue->cellChannelDescr.u.choice_2.component_2.u.range_1024[15] = 0x22;

   pvalue->m.descrMultislotConfigPresent = 1;
   pvalue->descrMultislotConfig.length = 0; /* length will be calculated */

   pvalue->descrMultislotConfig.da = 28;

   pvalue->descrMultislotConfig.m.uaPresent = 1;
   pvalue->descrMultislotConfig.ua = 58;

   /* zero elements */

   pvalue->m.modeFirstChannelPresent = 1;
   pvalue->modeFirstChannel = 31;

   pvalue->m.modeChannelSet2Present = 1;
   pvalue->modeChannelSet2 = 228;

   pvalue->m.modeChannelSet3Present = 1;
   pvalue->modeChannelSet3 = 173;

   pvalue->m.modeChannelSet4Present = 1;
   pvalue->modeChannelSet4 = 175;

   pvalue->m.modeChannelSet5Present = 1;
   pvalue->modeChannelSet5 = 73;

   pvalue->m.modeChannelSet6Present = 1;
   pvalue->modeChannelSet6 = 187;

   pvalue->m.modeChannelSet7Present = 1;
   pvalue->modeChannelSet7 = 26;

   pvalue->m.modeChannelSet8Present = 1;
   pvalue->modeChannelSet8 = 210;

   pvalue->m.descrSecondChannelAfterTimePresent = 1;

   pvalue->descrSecondChannelAfterTime.channel_type_and_TDMA_offset = 13;

   pvalue->descrSecondChannelAfterTime.tn = 6;

   pvalue->descrSecondChannelAfterTime.tsc = 3;

   pvalue->descrSecondChannelAfterTime.component_4.t =  1;

   pvalue->descrSecondChannelAfterTime.component_4.u.choice_1.maio = 51;

   pvalue->descrSecondChannelAfterTime.component_4.u.choice_1.hsn = 16;

   pvalue->m.modeSecondChannelPresent = 1;
   pvalue->modeSecondChannel = 79;

   pvalue->m.freqChannelSequenceAfterTimePresent = 1;

   pvalue->freqChannelSequenceAfterTime.spare_bit = 0;

   pvalue->freqChannelSequenceAfterTime.lowest_arfcn = 119;

   pvalue->freqChannelSequenceAfterTime.inc_skip.elem[0] = 8;

   pvalue->freqChannelSequenceAfterTime.inc_skip.elem[1] = 14;

   pvalue->freqChannelSequenceAfterTime.inc_skip.elem[2] = 2;

   pvalue->freqChannelSequenceAfterTime.inc_skip.elem[3] = 0;

   pvalue->freqChannelSequenceAfterTime.inc_skip.elem[4] = 13;

   pvalue->freqChannelSequenceAfterTime.inc_skip.elem[5] = 13;

   pvalue->freqChannelSequenceAfterTime.inc_skip.elem[6] = 1;

   pvalue->freqChannelSequenceAfterTime.inc_skip.elem[7] = 0;

   pvalue->freqChannelSequenceAfterTime.inc_skip.elem[8] = 12;

   pvalue->freqChannelSequenceAfterTime.inc_skip.elem[9] = 10;

   pvalue->freqChannelSequenceAfterTime.inc_skip.elem[10] = 13;

   pvalue->freqChannelSequenceAfterTime.inc_skip.elem[11] = 14;

   pvalue->freqChannelSequenceAfterTime.inc_skip.elem[12] = 10;

   pvalue->freqChannelSequenceAfterTime.inc_skip.elem[13] = 5;

   pvalue->freqChannelSequenceAfterTime.inc_skip.elem[14] = 12;

   pvalue->freqChannelSequenceAfterTime.inc_skip.elem[15] = 14;

   pvalue->m.mobileAllocationAfterTimePresent = 1;

   pvalue->mobileAllocationAfterTime.length = 4;

   pvalue->mobileAllocationAfterTime.mac.numbits = 32;
   pvalue->mobileAllocationAfterTime.mac.data[0] = 0x5e;
   pvalue->mobileAllocationAfterTime.mac.data[1] = 0x30;
   pvalue->mobileAllocationAfterTime.mac.data[2] = 0x35;
   pvalue->mobileAllocationAfterTime.mac.data[3] = 0x3d;


   pvalue->m.startingTimePresent = 1;

   pvalue->startingTime.t1prime = 28;

   pvalue->startingTime.t3 = 50;

   pvalue->startingTime.spare_bit = 23;

   pvalue->m.realTimeDifferencePresent = 1;
   pvalue->realTimeDifference.length = 0; /* length will be calculated */

   pvalue->realTimeDifference.value = 111;

   pvalue->m.timingAdvancePresent = 1;
   pvalue->timingAdvance = 24;

   pvalue->m.freqShortListBeforeTimePresent = 1;

   pvalue->freqShortListBeforeTime.component_1 = 2;

   pvalue->freqShortListBeforeTime.spare_bit = 0;

   pvalue->freqShortListBeforeTime.component_3.t =  3;
   pvalue->freqShortListBeforeTime.component_3.u.range_256[0] = 0x1d;
   pvalue->freqShortListBeforeTime.component_3.u.range_256[1] = 0x1b;
   pvalue->freqShortListBeforeTime.component_3.u.range_256[2] = 0x7b;
   pvalue->freqShortListBeforeTime.component_3.u.range_256[3] = 0x45;
   pvalue->freqShortListBeforeTime.component_3.u.range_256[4] = 0xf7;
   pvalue->freqShortListBeforeTime.component_3.u.range_256[5] = 0x72;
   pvalue->freqShortListBeforeTime.component_3.u.range_256[6] = 0xbc;
   pvalue->freqShortListBeforeTime.component_3.u.range_256[7] = 0x9d;
   pvalue->freqShortListBeforeTime.component_3.u.range_256[8] = 0x36;

   pvalue->m.freqListBeforeTimePresent = 1;
   pvalue->freqListBeforeTime.length = 0; /* length will be calculated */

   pvalue->freqListBeforeTime.component_2.t =  2;

   pvalue->freqListBeforeTime.component_2.u.choice_2.spare_bit = 1;

   pvalue->freqListBeforeTime.component_2.u.choice_2.component_2.t =  1;
   pvalue->freqListBeforeTime.component_2.u.choice_2.component_2.u.range_1024.numbits = 11;
   {
      OSOCTET* bitData = (OSOCTET*) rtxMemAlloc (pctxt,2);
      bitData[0] = 0x39;
      bitData[1] = 0x4a;
      pvalue->freqListBeforeTime.component_2.u.choice_2.component_2.u.range_1024.data = (const OSOCTET*)bitData;
   }

   pvalue->m.descrFirstChannelBeforeTimePresent = 1;

   pvalue->descrFirstChannelBeforeTime.channel_type_and_TDMA_offset = 1;

   pvalue->descrFirstChannelBeforeTime.tn = 6;

   pvalue->descrFirstChannelBeforeTime.tsc = 6;

   pvalue->descrFirstChannelBeforeTime.component_4.t =  1;

   pvalue->descrFirstChannelBeforeTime.component_4.u.choice_1.maio = 58;

   pvalue->descrFirstChannelBeforeTime.component_4.u.choice_1.hsn = 0;

   pvalue->m.descrSecondChannelBeforeTimePresent = 1;

   pvalue->descrSecondChannelBeforeTime.channel_type_and_TDMA_offset = 18;

   pvalue->descrSecondChannelBeforeTime.tn = 0;

   pvalue->descrSecondChannelBeforeTime.tsc = 0;

   pvalue->descrSecondChannelBeforeTime.component_4.t =  2;

   pvalue->descrSecondChannelBeforeTime.component_4.u.choice_2.spare_bit = 1;

   pvalue->descrSecondChannelBeforeTime.component_4.u.choice_2.arfcn = 617;

   pvalue->m.freqChannelSequneceBeforeTimePresent = 1;

   pvalue->freqChannelSequneceBeforeTime.spare_bit = 0;

   pvalue->freqChannelSequneceBeforeTime.lowest_arfcn = 105;

   pvalue->freqChannelSequneceBeforeTime.inc_skip.elem[0] = 6;

   pvalue->freqChannelSequneceBeforeTime.inc_skip.elem[1] = 6;

   pvalue->freqChannelSequneceBeforeTime.inc_skip.elem[2] = 1;

   pvalue->freqChannelSequneceBeforeTime.inc_skip.elem[3] = 12;

   pvalue->freqChannelSequneceBeforeTime.inc_skip.elem[4] = 8;

   pvalue->freqChannelSequneceBeforeTime.inc_skip.elem[5] = 4;

   pvalue->freqChannelSequneceBeforeTime.inc_skip.elem[6] = 5;

   pvalue->freqChannelSequneceBeforeTime.inc_skip.elem[7] = 5;

   pvalue->freqChannelSequneceBeforeTime.inc_skip.elem[8] = 0;

   pvalue->freqChannelSequneceBeforeTime.inc_skip.elem[9] = 5;

   pvalue->freqChannelSequneceBeforeTime.inc_skip.elem[10] = 1;

   pvalue->freqChannelSequneceBeforeTime.inc_skip.elem[11] = 12;

   pvalue->freqChannelSequneceBeforeTime.inc_skip.elem[12] = 10;

   pvalue->freqChannelSequneceBeforeTime.inc_skip.elem[13] = 8;

   pvalue->freqChannelSequneceBeforeTime.inc_skip.elem[14] = 3;

   pvalue->freqChannelSequneceBeforeTime.inc_skip.elem[15] = 12;

   pvalue->m.mobileAllocationBeforeTimePresent = 1;

   pvalue->mobileAllocationBeforeTime.length = 9;

   pvalue->mobileAllocationBeforeTime.mac.numbits = 72;
   pvalue->mobileAllocationBeforeTime.mac.data[0] = 0x36;
   pvalue->mobileAllocationBeforeTime.mac.data[1] = 0x4e;
   pvalue->mobileAllocationBeforeTime.mac.data[2] = 0x59;
   pvalue->mobileAllocationBeforeTime.mac.data[3] = 0x71;
   pvalue->mobileAllocationBeforeTime.mac.data[4] = 0x6e;
   pvalue->mobileAllocationBeforeTime.mac.data[5] = 0x69;
   pvalue->mobileAllocationBeforeTime.mac.data[6] = 0x55;
   pvalue->mobileAllocationBeforeTime.mac.data[7] = 0x32;
   pvalue->mobileAllocationBeforeTime.mac.data[8] = 0x68;

   pvalue->m.cipherModeSettingPresent = 1;

   pvalue->cipherModeSetting.algorithm_id = 0;

   pvalue->cipherModeSetting.sc = 0;

   pvalue->m.vgcsTargetModeIndicationPresent = 1;
   pvalue->vgcsTargetModeIndication.length = 0; /* length will be calculated */

   pvalue->vgcsTargetModeIndication.target_mode = 0;

   pvalue->vgcsTargetModeIndication.group_cipher_key_num = 13;

   pvalue->vgcsTargetModeIndication.spare = 1;

   pvalue->m.multirateConfigPresent = 1;

   pvalue->multirateConfig.multirate_speech_version = TS44018IE_Multirate_Configuration_multirate_speech_version_v1;

   pvalue->multirateConfig.nscb = 0;

   pvalue->multirateConfig.icmi = 0;

   pvalue->multirateConfig.start_mode = 2;

   pvalue->multirateConfig.amr_codec_modes = 166;

   /* zero elements */

   pvalue->m.dynamicArfcnMappingPresent = 1;
   pvalue->dynamicArfcnMapping.length_of_dynamic_arfcn_mapping = 0; /* length will be calculated */

   /* zero elements */

   pvalue->m.vgcsCipheringParametersPresent = 1;

   pvalue->vgcsCipheringParameters.b22_count = 0;

   pvalue->vgcsCipheringParameters.cell_global_count = 2;

   pvalue->vgcsCipheringParameters.m.cell_identityPresent = 1;
   pvalue->vgcsCipheringParameters.cell_identity = 134;

   pvalue->vgcsCipheringParameters.m.location_area_identificationPresent = 1;
   {
      static const OSOCTET testdata[] = { 
      0x9b, 0x1d, 0xfe, 0x5b, 0xd3 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->vgcsCipheringParameters.location_area_identification, 5, testdata, 5);
   }

   pvalue->vgcsCipheringParameters.m.vstk_randPresent = 1;
   pvalue->vgcsCipheringParameters.vstk_rand[0] = 0x51;
   pvalue->vgcsCipheringParameters.vstk_rand[1] = 0x35;
   pvalue->vgcsCipheringParameters.vstk_rand[2] = 0x3;
   pvalue->vgcsCipheringParameters.vstk_rand[3] = 0x36;
   pvalue->vgcsCipheringParameters.vstk_rand[4] = 0xe8;

   pvalue->m.dedicatedServiceInformationPresent = 1;

   pvalue->dedicatedServiceInformation.spare_bit = 77;

   pvalue->dedicatedServiceInformation.sis = 0;

   pvalue->m.plmnIndexPresent = 1;

   pvalue->plmnIndex.plmn_index = 2;

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
