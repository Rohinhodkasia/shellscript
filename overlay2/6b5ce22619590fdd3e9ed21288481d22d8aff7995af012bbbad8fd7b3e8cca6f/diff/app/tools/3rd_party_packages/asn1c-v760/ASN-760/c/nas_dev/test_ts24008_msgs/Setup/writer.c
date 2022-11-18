#include "TS24008Msgs.h"
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
   TS24008Msg_PDU pdu;
   TS24008Msg_Setup data;
   TS24008Msg_Setup* pvalue = &data;
   OSCTXT	ctxt;
   OSCTXT*	pctxt = &ctxt;
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

   asn1Init_TS24008Msg_PDU (&pdu);
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_callCtrl;
   pdu.msgType = ASN1V_mt_Setup;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_Setup;
   pdu.data.u.obj_Setup = pvalue;

   asn1Init_TS24008Msg_Setup (pvalue);
   pvalue->m.bcRepeatIndPresent = 1;
   pvalue->bcRepeatInd = TS24008IE_RepeatIndicator_fallbackSupp;
   pvalue->m.bearerCapability1Present = 1;

   pvalue->bearerCapability1.octet3.radioChannelRequirement = 0;
   pvalue->bearerCapability1.octet3.nonstandardCoding = 1;
   pvalue->bearerCapability1.octet3.packetXferMode = 0;
   pvalue->bearerCapability1.octet3.infoXferCap = TS24008IE_InfoXferCap_speech;

   pvalue->bearerCapability1.m.octet3aPresent = 1;
   pvalue->bearerCapability1.octet3a.coding = 0;
   pvalue->bearerCapability1.octet3a.ctm = 0;
   pvalue->bearerCapability1.octet3a.spare = 0;
   pvalue->bearerCapability1.octet3a.speechVersion = 4;

   pvalue->m.bearerCapability2Present = 1;

   pvalue->bearerCapability2.octet3.radioChannelRequirement = 0;
   pvalue->bearerCapability2.octet3.nonstandardCoding = 1;
   pvalue->bearerCapability2.octet3.packetXferMode = 0;
   pvalue->bearerCapability2.octet3.infoXferCap = TS24008IE_InfoXferCap_speech;

   pvalue->bearerCapability2.m.octet3aPresent = 1;
   pvalue->bearerCapability2.octet3a.coding = 1;
   pvalue->bearerCapability2.octet3a.ctm = 1;
   pvalue->bearerCapability2.octet3a.spare = 0;
   pvalue->bearerCapability2.octet3a.speechVersion = 8;

   pvalue->m.facilityPresent = 1;
   pvalue->facility.numocts = 16;
   pvalue->facility.data = (OSOCTET*) rtxMemAlloc (pctxt, 16);
   {
      static const OSOCTET testdata[] = {
         0xa1, 0x0e, 0x02, 0x01, 0x01, 0x02, 0x01, 0x0c,
         0x30, 0x06, 0x04, 0x01, 0x12, 0x82, 0x01, 0x34
      } ;
      OSCRTLMEMCPY ((void*)pvalue->facility.data, testdata, 16);
   }
   pvalue->m.progressIndPresent = 1;
   pvalue->progressInd.length = 205;
   pvalue->progressInd.octet3.codingStandard = TS24008IE_CodingStandard_q931;
   pvalue->progressInd.octet3.spare = 0;
   pvalue->progressInd.octet3.location = TS24008IE_PILocation_beyond;
   pvalue->progressInd.description = 0;
   pvalue->m.signal_Present = 1;
   pvalue->signal_ = TS24008IE_Signal_answerOn;
   pvalue->m.callingPartyNumberPresent = 1;
   pvalue->callingPartyNumber.octet3.typeOfNumber = TS24008IE_NumberTypes_network;
   pvalue->callingPartyNumber.octet3.numberingPlanID = TS24008IE_NumberPlans_unk;
   pvalue->callingPartyNumber.m.octet3aPresent = 0;
   pvalue->callingPartyNumber.m.numberPresent = 1;
   pvalue->callingPartyNumber.number = "109";
   pvalue->m.callingPartySubaddressPresent = 1;
   pvalue->callingPartySubaddress.m.octet3Present = 1;
   pvalue->callingPartySubaddress.octet3.typeOfSubaddr = TS24008IE_SubAddressTypes_nsap;
   pvalue->callingPartySubaddress.octet3.oddEvenIndicator = 0;
   pvalue->callingPartySubaddress.octet3.spare = 1;

   pvalue->m.calledPartyNumberPresent = 1;
   pvalue->calledPartyNumber.octet3.typeOfNumber = TS24008IE_NumberTypes_shortCode;
   pvalue->calledPartyNumber.octet3.numberingPlanID = TS24008IE_NumberPlans_reservedCTS;
   pvalue->calledPartyNumber.m.numberPresent = TRUE;
   pvalue->calledPartyNumber.number = "08*21c";
   pvalue->m.calledPartySubaddressPresent = 1;
   pvalue->calledPartySubaddress.m.octet3Present = 1;
   pvalue->calledPartySubaddress.octet3.typeOfSubaddr = TS24008IE_SubAddressTypes_userSpecified;
   pvalue->calledPartySubaddress.octet3.oddEvenIndicator = 1;
   pvalue->calledPartySubaddress.octet3.spare = 3;

   pvalue->m.redirectingPartyNumberPresent = 1;
   pvalue->redirectingPartyNumber.octet3.typeOfNumber = TS24008IE_NumberTypes_unk;
   pvalue->redirectingPartyNumber.octet3.numberingPlanID = TS24008IE_NumberPlans_data;
   pvalue->redirectingPartyNumber.m.octet3aPresent = 1;
   pvalue->redirectingPartyNumber.octet3a.presentationIndicator = 2;
   pvalue->redirectingPartyNumber.octet3a.spare = 2;
   pvalue->redirectingPartyNumber.octet3a.screeningIndicator = 0;
   pvalue->redirectingPartyNumber.m.numberPresent = 1;
   pvalue->redirectingPartyNumber.number = "792977";
   pvalue->m.redirectingPartySubaddressPresent = 1;
   pvalue->redirectingPartySubaddress.m.octet3Present = 1;
   pvalue->redirectingPartySubaddress.octet3.typeOfSubaddr = TS24008IE_SubAddressTypes_nsap;
   pvalue->redirectingPartySubaddress.octet3.oddEvenIndicator = 0;
   pvalue->redirectingPartySubaddress.octet3.spare = 5;

   pvalue->m.llcRepeatIndPresent = 1;
   pvalue->llcRepeatInd = TS24008IE_RepeatIndicator_svcChgFallback;
   pvalue->m.lowLayerCompat1Present = 1;
   {
      pvalue->lowLayerCompat1.numocts = 0;
   }
   pvalue->m.lowLayerCompat2Present = 1;
   {
      pvalue->lowLayerCompat2.numocts = 0;
   }
   pvalue->m.hlcRepeatIndPresent = 1;
   pvalue->hlcRepeatInd = TS24008IE_RepeatIndicator_circular;
   pvalue->m.highLayerCompat1Present = 1;
   pvalue->highLayerCompat1.length = 87;
   pvalue->highLayerCompat1.m.octet3Present = 1;
   pvalue->highLayerCompat1.octet3.codingStandard = TS24008IE_CodingStandard_q931;
   pvalue->highLayerCompat1.octet3.interpretation = 4;
   pvalue->highLayerCompat1.octet3.presentMethOfProtoProf = 2;
   pvalue->highLayerCompat1.m.highLayerCharacteristicsIDPresent = 1;
   pvalue->highLayerCompat1.highLayerCharacteristicsID = 20;
   pvalue->highLayerCompat1.m.extHighLayerCharacteristicsIDPresent = 1;
   pvalue->highLayerCompat1.extHighLayerCharacteristicsID = 4;
   pvalue->m.highLayerCompat2Present = 1;
   pvalue->highLayerCompat2.length = 243;
   pvalue->highLayerCompat2.m.octet3Present = 1;
   pvalue->highLayerCompat2.octet3.codingStandard = TS24008IE_CodingStandard_q931;
   pvalue->highLayerCompat2.octet3.interpretation = 6;
   pvalue->highLayerCompat2.octet3.presentMethOfProtoProf = 1;
   pvalue->highLayerCompat2.m.highLayerCharacteristicsIDPresent = 1;
   pvalue->highLayerCompat2.highLayerCharacteristicsID = 40;
   pvalue->highLayerCompat2.m.extHighLayerCharacteristicsIDPresent = 1;
   pvalue->highLayerCompat2.extHighLayerCharacteristicsID = 50;
   pvalue->m.userUserPresent = 1;
   pvalue->userUser.length = 74;
   pvalue->userUser.uupd = 206;
   pvalue->userUser.m.uuInfoPresent = 1;
   pvalue->userUser.uuInfo.numocts = 11;
   pvalue->userUser.uuInfo.data = (OSOCTET*) rtxMemAlloc (pctxt, 11);
   {
      static const OSOCTET testdata[] = {
      0x31, 0x3f, 0x16, 0xe6, 0xbd, 0x40, 0x30, 0x8d,
      0xe9, 0xbd, 0x6 };
      OSCRTLMEMCPY ((void*)pvalue->userUser.uuInfo.data, testdata, 11);
   }
   pvalue->m.priorityLevelPresent = 1;
   pvalue->priorityLevel.spare = 0;
   pvalue->priorityLevel.callPriority = 4;
   pvalue->m.alertingPatternPresent = 1;
   pvalue->alertingPattern.value = TS24008IE_AlertingValues_pattern9;
   pvalue->m.netCallCtrlCapsPresent = 1;
   pvalue->netCallCtrlCaps.mcs = 1;
   pvalue->m.causeOfNoCLIPresent = 1;
   pvalue->causeOfNoCLI.value = 190;
   pvalue->m.backupBearerCapabilityPresent = 1;

   pvalue->backupBearerCapability.octet3.radioChannelRequirement = 2;
   pvalue->backupBearerCapability.octet3.nonstandardCoding = 1;
   pvalue->backupBearerCapability.octet3.packetXferMode = 1;
   pvalue->backupBearerCapability.octet3.infoXferCap = TS24008IE_InfoXferCap_speech;
   pvalue->backupBearerCapability.m.octet4Present = 1;

   pvalue->backupBearerCapability.octet4.compression = 1;
   pvalue->backupBearerCapability.octet4.structure = 0;
   pvalue->backupBearerCapability.octet4.fullDuplexMode = 0;
   pvalue->backupBearerCapability.octet4.configuration = 0;
   pvalue->backupBearerCapability.octet4.nirr = 0;
   pvalue->backupBearerCapability.octet4.establishment = 1;
   pvalue->backupBearerCapability.m.octet5Present = 1;
   pvalue->backupBearerCapability.m.octet5aPresent = 0;


   pvalue->backupBearerCapability.octet5.accessIdentity = 0;
   pvalue->backupBearerCapability.octet5.rateAdaption = 0;
   pvalue->backupBearerCapability.octet5.signallingAccessProtocol = 5;

   pvalue->backupBearerCapability.m.octet6Present = 1;
   pvalue->backupBearerCapability.m.octet6aPresent = 1;

   pvalue->backupBearerCapability.octet6.layer1Identity = 1;
   pvalue->backupBearerCapability.octet6.userInfoLayer1Protocol = 1;
   pvalue->backupBearerCapability.octet6.asynchronous = 0;

   pvalue->backupBearerCapability.octet6a.twoStopBits = 0;
   pvalue->backupBearerCapability.octet6a.negotiation = 1;
   pvalue->backupBearerCapability.octet6a.data8bits = 0;
   pvalue->backupBearerCapability.octet6a.userRate = 5;

   pvalue->backupBearerCapability.m.octet7Present = 1;

   pvalue->backupBearerCapability.octet7.layer2Identity = 1;
   pvalue->backupBearerCapability.octet7.userInformationLayer2Protocol = 0;
   pvalue->m.ssVersionPresent = 1;
   pvalue->ssVersion.numocts = 2;
   pvalue->ssVersion.data = (OSOCTET*) rtxMemAlloc (pctxt, 2);
   {
      static const OSOCTET testdata[] = {
      0xaf, 0x1 };
      OSCRTLMEMCPY ((void*)pvalue->ssVersion.data, testdata, 2);
   }
   pvalue->m.clirSuppressionPresent = 1;
   pvalue->m.clirInvocationPresent = 1;
   pvalue->m.callCtrlCapPresent = 1;
   pvalue->callCtrlCap.length = 58;
   pvalue->callCtrlCap.maxNumSupportedBearers = 11;
   pvalue->callCtrlCap.mcat = 0;
   pvalue->callCtrlCap.enicm = 1;
   pvalue->callCtrlCap.pcp = 1;
   pvalue->callCtrlCap.dtmf = 1;
   pvalue->callCtrlCap.spare = 2;
   pvalue->callCtrlCap.maxNumSpeechBearers = 11;
   pvalue->m.facilityAdvRecallAlignPresent = 1;
   pvalue->facilityAdvRecallAlign.numocts = 16;
   pvalue->facilityAdvRecallAlign.data = (OSOCTET*) rtxMemAlloc (pctxt, 16);
   {
      static const OSOCTET testdata[] = {
         0xa1, 0x0e, 0x02, 0x01, 0x01, 0x02, 0x01, 0x0c,
         0x30, 0x06, 0x04, 0x01, 0x12, 0x82, 0x01, 0x34
      } ;
      OSCRTLMEMCPY ((void*)pvalue->facilityAdvRecallAlign.data, testdata, 16);
   }
   pvalue->m.facilityRecallAlignNotEssentialPresent = 1;
   pvalue->facilityRecallAlignNotEssential.numocts = 16;
   pvalue->facilityRecallAlignNotEssential.data =
      (OSOCTET*) rtxMemAlloc (pctxt, 16);
   {
      static const OSOCTET testdata[] = {
         0xa1, 0x0e, 0x02, 0x01, 0x01, 0x02, 0x01, 0x0c,
         0x30, 0x06, 0x04, 0x01, 0x12, 0x82, 0x01, 0x34
      } ;
      OSCRTLMEMCPY ((void*)pvalue->facilityRecallAlignNotEssential.data, testdata, 16);
   }
   pvalue->m.streamIdPresent = 1;
   pvalue->streamId.value = 135;
   pvalue->m.supportedCodecsPresent = 1;
   pvalue->supportedCodecs.length = 243;
   pvalue->supportedCodecs.codecs.n = 1;
   pvalue->supportedCodecs.codecs.elem[0].sysID = 250;
   {
      static const OSOCTET testdata[] = {
      0xcb };
      pvalue->supportedCodecs.codecs.elem[0].codecBitmap.numocts = 1;
      OSCRTLMEMCPY ((void*)pvalue->supportedCodecs.codecs.elem[0].codecBitmap.data, testdata, 1);
   }
   pvalue->m.redialPresent = 1;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24008Msg_PDU (&ctxt, &pdu);
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
