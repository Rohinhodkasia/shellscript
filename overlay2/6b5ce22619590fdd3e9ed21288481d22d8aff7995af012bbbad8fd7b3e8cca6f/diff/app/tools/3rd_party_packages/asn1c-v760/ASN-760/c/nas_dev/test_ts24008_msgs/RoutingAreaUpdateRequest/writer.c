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
   TS24008Msg_RoutingAreaUpdateRequest data;
   TS24008Msg_RoutingAreaUpdateRequest* pvalue = &data;
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

   asn1Init_TS24008Msg_PDU (&pdu);
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_gprsMobMgmt;
   pdu.msgType = ASN1V_mt_RoutingAreaUpdateRequest;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_RoutingAreaUpdateRequest;
   pdu.data.u.obj_RoutingAreaUpdateRequest = pvalue;


   asn1Init_TS24008Msg_RoutingAreaUpdateRequest (pvalue);

   pvalue->updateType.for_ = 1;
   pvalue->updateType.value = TS24008IE_UpdateTypeValues_raLaUpdatingImsiAttach;
   pvalue->gprsCiphKeySeq.spare = 0;
   pvalue->gprsCiphKeySeq.value = 3;
   rtxStrncpy(pvalue->oldRoutingAreaId.mcc_mnc.mcc,
              sizeof(pvalue->oldRoutingAreaId.mcc_mnc.mcc), "c43", 4);
   rtxStrncpy(pvalue->oldRoutingAreaId.mcc_mnc.mnc,
              sizeof(pvalue->oldRoutingAreaId.mcc_mnc.mnc), "86a", 4);
   pvalue->oldRoutingAreaId.lac = 25488;
   pvalue->oldRoutingAreaId.rac = 217;

   pvalue->msRACapability.firstRec.accessTechType = 11;

   pvalue->m.oldPTMSISignaturePresent = 1;
   {
      static const OSOCTET testdata[] = {
      0xd9, 0xb1, 0x93 };
      OSCRTLMEMCPY ((void*)pvalue->oldPTMSISignature.value, testdata, 3);
   }

   pvalue->m.reqREADYTimerValuePresent = 1;
   pvalue->reqREADYTimerValue.unit = 6;
   pvalue->reqREADYTimerValue.timerValue = 1;

   pvalue->m.drxParameterPresent = 1;
   pvalue->drxParameter.splitPGCycleCode = 12;
   pvalue->drxParameter.lenCoefAndValue = 14;
   pvalue->drxParameter.splitOnCCCH = 0;
   pvalue->drxParameter.nonDRXTimer = 3;

   pvalue->m.tmsiStatusPresent = 1;
   pvalue->tmsiStatus.spare = 0;
   pvalue->tmsiStatus.flag = 0;

   pvalue->m.pTMSIPresent = 1;
   pvalue->pTMSI.t =  T_TS24008IE_MobileIdentity_imei;
   rtxStrncpy(pvalue->pTMSI.u.imei, sizeof(pvalue->pTMSI.u.imei),
              "8a5c4235842b978", 16);

   pvalue->m.msNetCapabilityPresent = 1;
   pvalue->msNetCapability.m.octet1Present =
      pvalue->msNetCapability.m.octet2Present =
      pvalue->msNetCapability.m.octet3Present = 1;
   pvalue->msNetCapability.octet1.gea1 = 0;
   pvalue->msNetCapability.octet1.smCapDeicatedChan = 0;
   pvalue->msNetCapability.octet1.smCapGPRSChan = 0;
   pvalue->msNetCapability.octet1.ucs2Support = 1;
   pvalue->msNetCapability.octet1.ssScreeningInd = 1;
   pvalue->msNetCapability.octet1.soLSACap = 0;
   pvalue->msNetCapability.octet1.revisionLevelInd = 0;
   pvalue->msNetCapability.octet2.pfcFeatureMode = 0;
   pvalue->msNetCapability.octet2.extendedGEA = 47;
   pvalue->msNetCapability.octet2.lcsVACap = 0;
   pvalue->msNetCapability.octet3.psInterRATHOToUTRANIuModeCap = 1;
   pvalue->msNetCapability.octet3.psInterRATHOToEUTRANS1ModeCap = 0;
   pvalue->msNetCapability.octet3.emmCombinedProcCap = 0;
   pvalue->msNetCapability.octet3.isrSupport = 1;
   pvalue->msNetCapability.octet3.srvccToGERAN_UTRANCap = 1;
   pvalue->msNetCapability.octet3.epcCap = 1;
   pvalue->msNetCapability.octet3.nfCapability = 0;
   pvalue->msNetCapability.octet3.geranNetShareCap = 0;

   {
      static const OSOCTET testdata[] = {
      0x4f, 0xeb };
      OSCRTLMEMCPY ((void*)pvalue->pdpContextStatus.value, testdata, 2);
   }
   pvalue->m.psLCSCapPresent = 1;
   pvalue->psLCSCap.mta_E = 1;
   pvalue->psLCSCap.mta_R = 0;
   pvalue->psLCSCap.apc = 0;
   pvalue->psLCSCap.otd_A = 1;
   pvalue->psLCSCap.otd_B = 1;
   pvalue->psLCSCap.gps_A = 1;
   pvalue->psLCSCap.gps_B = 1;
   pvalue->psLCSCap.gps_C = 1;
   pvalue->psLCSCap.spare = 0;
   pvalue->psLCSCap.motd = 0;
   pvalue->psLCSCap.mta_A = 1;

   pvalue->m.mbmsContextStatusPresent = 1;
   {
      pvalue->mbmsContextStatus.numocts = 0;
   }

   pvalue->m.ueNetCapPresent = 1;
   pvalue->ueNetCap.epsEncryptAlgs.eea0 = 0;
   pvalue->ueNetCap.epsEncryptAlgs.x128_eea1 = 1;
   pvalue->ueNetCap.epsEncryptAlgs.x128_eea2 = 1;
   pvalue->ueNetCap.epsEncryptAlgs.eea3 = 0;
   pvalue->ueNetCap.epsEncryptAlgs.eea4 = 1;
   pvalue->ueNetCap.epsEncryptAlgs.eea5 = 1;
   pvalue->ueNetCap.epsEncryptAlgs.eea6 = 0;
   pvalue->ueNetCap.epsEncryptAlgs.eea7 = 1;

   pvalue->ueNetCap.epsIntegAlgs.eia0 = 0;
   pvalue->ueNetCap.epsIntegAlgs.eia1 = 0;
   pvalue->ueNetCap.epsIntegAlgs.eia2 = 1;
   pvalue->ueNetCap.epsIntegAlgs.eia3 = 0;
   pvalue->ueNetCap.epsIntegAlgs.eia4 = 1;
   pvalue->ueNetCap.epsIntegAlgs.eia5 = 1;
   pvalue->ueNetCap.epsIntegAlgs.eia6 = 0;
   pvalue->ueNetCap.epsIntegAlgs.eia7 = 1;

   pvalue->ueNetCap.m.umtsEncryptAlgsPresent = 1;
   pvalue->ueNetCap.umtsEncryptAlgs.uea0 = 1;
   pvalue->ueNetCap.umtsEncryptAlgs.uea1 = 1;
   pvalue->ueNetCap.umtsEncryptAlgs.uea2 = 1;
   pvalue->ueNetCap.umtsEncryptAlgs.uea3 = 0;
   pvalue->ueNetCap.umtsEncryptAlgs.uea4 = 0;
   pvalue->ueNetCap.umtsEncryptAlgs.uea5 = 0;
   pvalue->ueNetCap.umtsEncryptAlgs.uea6 = 0;
   pvalue->ueNetCap.umtsEncryptAlgs.uea7 = 1;

   pvalue->ueNetCap.m.octet6Present = 1;
   pvalue->ueNetCap.octet6.ucs2 = 1;
   pvalue->ueNetCap.octet6.umtsIntegAlgs.uia1 = 1;
   pvalue->ueNetCap.octet6.umtsIntegAlgs.uia2 = 1;
   pvalue->ueNetCap.octet6.umtsIntegAlgs.uia3 = 0;
   pvalue->ueNetCap.octet6.umtsIntegAlgs.uia4 = 1;
   pvalue->ueNetCap.octet6.umtsIntegAlgs.uia5 = 0;
   pvalue->ueNetCap.octet6.umtsIntegAlgs.uia6 = 1;
   pvalue->ueNetCap.octet6.umtsIntegAlgs.uia7 = 0;

   pvalue->ueNetCap.m.octet7Present = 1;
   pvalue->ueNetCap.octet7.proSedd = 0;
   pvalue->ueNetCap.octet7.proSe = 0;
   pvalue->ueNetCap.octet7.h245_ash = 1;
   pvalue->ueNetCap.octet7.acc_csfb = 1;
   pvalue->ueNetCap.octet7.lpp = 0;
   pvalue->ueNetCap.octet7.lcs = 0;
   pvalue->ueNetCap.octet7.x1xSR_VCC = 0;
   pvalue->ueNetCap.octet7.nf = 1;

   pvalue->ueNetCap.m.octet8Present = 1;
   pvalue->ueNetCap.octet8.ePCO = 1;
   pvalue->ueNetCap.octet8.hc_CP_CIoT = 0;
   pvalue->ueNetCap.octet8.erwoPDN = 1;
   pvalue->ueNetCap.octet8.s1_Udata = 0;
   pvalue->ueNetCap.octet8.upCIoT = 1;
   pvalue->ueNetCap.octet8.cpCIoT = 0;
   pvalue->ueNetCap.octet8.prose_relay = 1;
   pvalue->ueNetCap.octet8.proSedc = 0;

   pvalue->m.addnMobileIdPresent = 1;
   pvalue->addnMobileId.t =  T_TS24008IE_MobileIdentity_tmsi;
   {
      static const OSOCTET testdata[] = {
      0x8f, 0xcb, 0x67, 0xb8 };
      OSCRTLMEMCPY ((void*)pvalue->addnMobileId.u.tmsi, testdata, 4);
   }

   pvalue->m.addnOldRoutingAreaIdPresent = 1;
   rtxStrncpy(pvalue->addnOldRoutingAreaId.value.mcc_mnc.mcc,
              sizeof(pvalue->addnOldRoutingAreaId.value.mcc_mnc.mcc),
              "045", 4);
   rtxStrncpy(pvalue->addnOldRoutingAreaId.value.mcc_mnc.mnc,
              sizeof(pvalue->addnOldRoutingAreaId.value.mcc_mnc.mnc),
              "443", 4);

   pvalue->addnOldRoutingAreaId.value.lac = 17704;
   pvalue->addnOldRoutingAreaId.value.rac = 22;

   pvalue->m.msClassmark2Present = 1;

   pvalue->msClassmark2.m.cm1Present = 1;
   pvalue->msClassmark2.cm1.spare = 0;
   pvalue->msClassmark2.cm1.revLevel = 1;
   pvalue->msClassmark2.cm1.esInd = 1;
   pvalue->msClassmark2.cm1.a5_1_alg = 1;
   pvalue->msClassmark2.cm1.rfPowerCap = TS24008IE_RFPowerCapValues_class1;

   pvalue->msClassmark2.m.octet4Present = 1;
   pvalue->msClassmark2.octet4.spare = 0;
   pvalue->msClassmark2.octet4.psCapability = 0;
   pvalue->msClassmark2.octet4.ssScreeningInd = 0;
   pvalue->msClassmark2.octet4.smCapability = 1;
   pvalue->msClassmark2.octet4.vbsNotifRecept = 1;
   pvalue->msClassmark2.octet4.vgcsNotifRecept = 0;
   pvalue->msClassmark2.octet4.fcFreqCap = 1;

   pvalue->msClassmark2.m.octet5Present = 1;
   pvalue->msClassmark2.octet5.cm3 = 1;
   pvalue->msClassmark2.octet5.spare = 0;
   pvalue->msClassmark2.octet5.lcsvaCap = 0;
   pvalue->msClassmark2.octet5.ucs2Treatment = 1;
   pvalue->msClassmark2.octet5.soLSA = 1;
   pvalue->msClassmark2.octet5.cmsp = 1;
   pvalue->msClassmark2.octet5.a5_3_alg = 0;
   pvalue->msClassmark2.octet5.a5_2_alg = 0;

   pvalue->m.msClassmark3Present = 1;
   pvalue->msClassmark3.spare = 0;
   pvalue->msClassmark3.multiband.supported = TS24008IE_MBSEnum_mbs0;
   pvalue->msClassmark3.multiband.a5bits.a5_7 = 1;
   pvalue->msClassmark3.multiband.a5bits.a5_6 = 0;
   pvalue->msClassmark3.multiband.a5bits.a5_5 = 0;
   pvalue->msClassmark3.multiband.a5bits.a5_4 = 0;

   pvalue->msClassmark3.m.rSupportPresent = 1;
   pvalue->msClassmark3.rSupport = 6;

   pvalue->msClassmark3.m.hscsdMultiSlotCapPresent = 1;
   pvalue->msClassmark3.hscsdMultiSlotCap = 8;
   pvalue->msClassmark3.ucs2Treatment = 0;
   pvalue->msClassmark3.extMeasurementCap = 0;

   pvalue->msClassmark3.m.msMeasurementCapPresent = 1;
   pvalue->msClassmark3.msMeasurementCap.smsValue = 5;
   pvalue->msClassmark3.msMeasurementCap.smValue = 1;

   pvalue->msClassmark3.m.msPositioningMethodCapPresent = 1;
   pvalue->msClassmark3.msPositioningMethodCap = 4;
   pvalue->msClassmark3.m.ecsdMultiSlotCapPresent = 1;
   pvalue->msClassmark3.ecsdMultiSlotCap = 17;

   pvalue->msClassmark3.m.an_8_PSKStructPresent = 1;
   pvalue->msClassmark3.an_8_PSKStruct.modulationCap = 0;
   pvalue->msClassmark3.an_8_PSKStruct.m.rfPowerCap1Present = 1;
   pvalue->msClassmark3.an_8_PSKStruct.rfPowerCap1 = 0;
   pvalue->msClassmark3.an_8_PSKStruct.m.rfPowerCap2Present = 1;
   pvalue->msClassmark3.an_8_PSKStruct.rfPowerCap2 = 0;

   pvalue->msClassmark3.m.gsm400StructPresent = 1;
   pvalue->msClassmark3.gsm400Struct.bandsSupported = TS24008IE_GSM400Struct_bandsSupported_band1;
   pvalue->msClassmark3.gsm400Struct.assocRadioCap = 12;

   pvalue->msClassmark3.m.gsm850AssocRadioCapPresent = 1;
   pvalue->msClassmark3.gsm850AssocRadioCap = 2;

   pvalue->msClassmark3.m.gsm1900AssocRadioCapPresent = 1;
   pvalue->msClassmark3.gsm1900AssocRadioCap = 4;

   pvalue->msClassmark3.umtsFDDRadioAccessTechCap = 1;
   pvalue->msClassmark3.umts384McpsTDDRadioAccessTechCap = 0;
   pvalue->msClassmark3.cdma2000RadioAccessTechCap = 0;

   pvalue->msClassmark3.m.dtmGPRSStructPresent = 1;
   pvalue->msClassmark3.dtmGPRSStruct.dtmGPRSMultiSlotClass = 1;
   pvalue->msClassmark3.dtmGPRSStruct.singleSlotDTM = 1;
   pvalue->msClassmark3.dtmGPRSStruct.m.dtmEGPRSMultiSlotClassPresent = 1;
   pvalue->msClassmark3.dtmGPRSStruct.dtmEGPRSMultiSlotClass = 1;

   pvalue->msClassmark3.m.singleBandSupportPresent = 1;
   pvalue->msClassmark3.singleBandSupport = 7;

   pvalue->msClassmark3.m.gsm750AssocRadioCapPresent = 1;
   pvalue->msClassmark3.gsm750AssocRadioCap = 6;

   pvalue->msClassmark3.umts1_28McpsTDDRadioAccessTechCap = 0;
   pvalue->msClassmark3.geranFeaturePackage1 = 0;
   pvalue->msClassmark3.m.extDtmGPRSStructPresent = 1;

   pvalue->msClassmark3.extDtmGPRSStruct.extDtmGPRSMultiSlotClass = 2;
   pvalue->msClassmark3.extDtmGPRSStruct.extDtmEGPRSMultiSlotClass = 1;

   pvalue->msClassmark3.m.highMultislotCapPresent = 1;
   pvalue->msClassmark3.highMultislotCap = 1;

   pvalue->msClassmark3.m.geranIuModeCapPresent = 1;
   pvalue->msClassmark3.geranIuModeCap.length = 7;
   pvalue->msClassmark3.geranIuModeCap.floIuCap = 1;
   pvalue->msClassmark3.geranFeaturePackage2 = 0;

   pvalue->msClassmark3.gmskMultislotPowerProfile = 1;
   pvalue->msClassmark3.multislotPowerProfile8PSK = 1;

   pvalue->msClassmark3.m.tgsm400StructPresent = 1;
   pvalue->msClassmark3.tgsm400Struct.bandsSupported = TS24008IE_GSM400Struct_bandsSupported_band1;
   pvalue->msClassmark3.tgsm400Struct.assocRadioCap = 10;

   pvalue->msClassmark3.zerobit = 0;
   pvalue->msClassmark3.downlinkAdvancedRcvrPerf = 2;
   pvalue->msClassmark3.dtmEnhancementsCap = 1;

   pvalue->msClassmark3.m.dtmGPRSStruct2Present = 1;
   pvalue->msClassmark3.dtmGPRSStruct2.dtmGPRSHighMultiSlotClass = 2;
   pvalue->msClassmark3.dtmGPRSStruct2.offsetRequired = 1;
   pvalue->msClassmark3.dtmGPRSStruct2.m.dtmEGPRSHighMultiSlotClassPresent = 1;
   pvalue->msClassmark3.dtmGPRSStruct2.dtmEGPRSHighMultiSlotClass = 6;

   pvalue->msClassmark3.repeatedACCHCap = 1;

   pvalue->msClassmark3.m.gsm710AssocRadioCapPresent = 1;
   pvalue->msClassmark3.gsm710AssocRadioCap = 14;

   pvalue->msClassmark3.m.tgsm810AssocRadioCapPresent = 1;
   pvalue->msClassmark3.tgsm810AssocRadioCap = 2;

   pvalue->msClassmark3.cipheringModeSettingCap = 1;
   pvalue->msClassmark3.additionalPositioningCap = 0;
   pvalue->msClassmark3.e_UTRA_FDD_support = 0;
   pvalue->msClassmark3.e_UTRA_TDD_support = 1;
   pvalue->msClassmark3.e_UTRA_MeasAndReportSupport = 1;
   pvalue->msClassmark3.priorityBasedReselectionSupport = 1;

   pvalue->m.supportedCodecsPresent = 1;
   pvalue->supportedCodecs.length = 9;
   pvalue->supportedCodecs.codecs.n = 1;
   pvalue->supportedCodecs.codecs.elem[0].sysID = 122;
   {
      static const OSOCTET testdata[] = {
      0xc9 };
      pvalue->supportedCodecs.codecs.elem[0].codecBitmap.numocts = 1;
      OSCRTLMEMCPY ((void*)pvalue->supportedCodecs.codecs.elem[0].codecBitmap.data, testdata, 1);
   }


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
