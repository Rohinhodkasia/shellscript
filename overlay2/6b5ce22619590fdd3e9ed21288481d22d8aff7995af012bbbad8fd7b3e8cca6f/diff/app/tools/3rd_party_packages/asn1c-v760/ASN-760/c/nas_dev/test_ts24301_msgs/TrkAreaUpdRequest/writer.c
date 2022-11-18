#include "TS24301Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"
#include "rt3gppsrc/rt3gppNasSec.h"

#define MAXMSGLEN 300

int main (int argc, char** argv)
{
   TS24301Msg_PDU pdu;
   TS24301Msg_TrkAreaUpdRequest data;
   TS24301Msg_TrkAreaUpdRequest* pvalue = &data;
   OSCTXT	ctxt;
   OSCTXT*	pctxt = &ctxt;
   OSOCTET	msgbuf[MAXMSGLEN], *msgptr;
   const char*  filename = "message.dat";
   OSSIZE       len;
   int		i, ret;
   OSBOOL verbose = FALSE;
   OSCrypt128Key integKey = {
      0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
      0x98, 0x76, 0x54, 0x32, 0x10, 0xfe, 0xdc, 0xba
   };
   OSCrypt128Key encryptKey = {
      0x98, 0x76, 0x54, 0x32, 0x10, 0xfe, 0xdc, 0xba,
      0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef
   };

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

   ret = rtx3gppSecInitialize(&ctxt);
   if (0 != ret) {
      rtxErrPrint (&ctxt);
   }

   ret = rtx3gppAssignAlgorithmKeys (&ctxt, &integKey, &encryptKey,
      OS3GPPSecAlgorithm_AES, OS3GPPSecAlgorithm_AES);
   if ( ret == RTERR_NOTSUPP ) {
      printf ("Warning: unable to set AES algorithm; falling back to "
              "NULL algorithm.\n");
      rtxErrReset (&ctxt);
      ret = rtx3gppAssignAlgorithmKeys (&ctxt, NULL, NULL, 
         OS3GPPSecAlgorithm_NULL_ALG, OS3GPPSecAlgorithm_NULL_ALG);
   }
   if (0 != ret) {
      rtxErrPrint (&ctxt);
   }

   ctxt.p3gppSec->count = 15;
   ctxt.p3gppSec->bearerId = 0;
   ctxt.p3gppSec->direction = 0; /*uplink*/

   /* Populate data structure */

   asn1Init_TS24301Msg_PDU (&pdu);
   pdu.m.secHdrPresent = 1;
   pdu.secHdr.secHdrType = TS24007L3_SecHdrType_integProt;
   pdu.secHdr.protoDiscr = TS24007L3_ProtoDiscr_epsMobMgmt;
   pdu.secHdr.msgAuthCode = 12345678;
   pdu.secHdr.seqNumber  = 1;
   pdu.l3HdrOpts.t = T_TS24007L3_L3HdrOptions_secHdr;
   pdu.l3HdrOpts.u.secHdr = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_epsMobMgmt;
   asn1SetTC_TS24301Msg_PDU_obj_TrkAreaUpdRequest (&ctxt, &pdu, pvalue);

   asn1Init_TS24301Msg_TrkAreaUpdRequest (pvalue);

   pvalue->nasKeySetIdentifier.tsc = 0;

   pvalue->nasKeySetIdentifier.ident = 3;

   pvalue->epsUpdateType.active = 0;

   pvalue->epsUpdateType.value = 6;

   pvalue->oldGUTI.length = 0; /* length will be calculated */

   pvalue->oldGUTI.filler = 10;

   pvalue->oldGUTI.oddEvenInd = 0;

   pvalue->oldGUTI.typeOfIdent = TS24301IE_EPSMobileIdentity_typeOfIdent_imsi;

   switch (pvalue->oldGUTI.typeOfIdent) {
      /* guti */
      case 6:

         rtxStrncpy (pvalue->oldGUTI.content.u.guti.mcc_mnc.mcc, 4, "505", 3);
         rtxStrncpy (pvalue->oldGUTI.content.u.guti.mcc_mnc.mnc, 4, "06", 3);

         {
            static const OSOCTET testdata[] = {
            0x3c, 0xd8 };
            OSCRTLMEMCPY ((void*)pvalue->oldGUTI.content.u.guti.mmeGroupID, testdata, 2);
         }

         pvalue->oldGUTI.content.u.guti.mmeCode = 107;

         {
            static const OSOCTET testdata[] = {
            0xb3, 0x7c, 0x98, 0x83 };
            OSCRTLMEMCPY ((void*)pvalue->oldGUTI.content.u.guti.tmsi, testdata, 4);
         }
         break;

      /* imsi */
      case 1:
         rtxStrncpy (pvalue->oldGUTI.content.u.imsi, sizeof(pvalue->oldGUTI.content.u.imsi), "33805123456789", 15);
         break;

      /* imei */
      case 3:
         rtxStrncpy (pvalue->oldGUTI.content.u.imei, sizeof(pvalue->oldGUTI.content.u.imei), "33805123456789", 15);
         break;
   }

   pvalue->m.nonCurrNativeNASKeySetIdentPresent = 1;

   pvalue->nonCurrNativeNASKeySetIdent.tsc = 0;

   pvalue->nonCurrNativeNASKeySetIdent.ident = 5;

   pvalue->m.gprsCiphKeySeqNumPresent = 1;

   pvalue->gprsCiphKeySeqNum.spare = 0;

   pvalue->gprsCiphKeySeqNum.value = 1;

   pvalue->m.oldP_TMSISignaturePresent = 1;

   {
      static const OSOCTET testdata[] = {
      0x81, 0x99, 0xf8 };
      OSCRTLMEMCPY ((void*)pvalue->oldP_TMSISignature.value, testdata, 3);
   }

   pvalue->m.additionalGUTIPresent = 1;
   pvalue->additionalGUTI.length = 0; /* length will be calculated */

   pvalue->additionalGUTI.filler = 14;

   pvalue->additionalGUTI.oddEvenInd = 0;

   pvalue->additionalGUTI.typeOfIdent = TS24301IE_EPSMobileIdentity_typeOfIdent_imsi;

   switch (pvalue->additionalGUTI.typeOfIdent) {
      /* guti */
      case 6:

         rtxStrncpy (pvalue->additionalGUTI.content.u.guti.mcc_mnc.mcc, 4, "266", 3);
         rtxStrncpy (pvalue->additionalGUTI.content.u.guti.mcc_mnc.mnc, 4, "01", 3);

         {
            static const OSOCTET testdata[] = {
            0x50, 0x7b };
            OSCRTLMEMCPY ((void*)pvalue->additionalGUTI.content.u.guti.mmeGroupID, testdata, 2);
         }

         pvalue->additionalGUTI.content.u.guti.mmeCode = 24;

         {
            static const OSOCTET testdata[] = {
            0x35, 0xde, 0x0a, 0x40 };
            OSCRTLMEMCPY ((void*)pvalue->additionalGUTI.content.u.guti.tmsi, testdata, 4);
         }
         break;

      /* imsi */
      case 1:
         rtxStrncpy (pvalue->additionalGUTI.content.u.imsi, sizeof(pvalue->additionalGUTI.content.u.imsi), "24702123456789", 15);
         break;

      /* imei */
      case 3:
         rtxStrncpy (pvalue->additionalGUTI.content.u.imei, sizeof(pvalue->additionalGUTI.content.u.imei), "24702123456789", 15);
         break;
   }

   pvalue->m.noncePresent = 1;
   {
      static const OSOCTET testdata[] = {
      0x82, 0x61, 0x3e, 0xbd };
      OSCRTLMEMCPY ((void*)pvalue->nonce.data, testdata, 4);
   }

   pvalue->m.ueNetworkCapabilityPresent = 1;
   pvalue->ueNetworkCapability.length = 0; /* length will be calculated */

   pvalue->ueNetworkCapability.epsEncryptAlgs.eea0 = 1;

   pvalue->ueNetworkCapability.epsEncryptAlgs.x128_eea1 = 0;

   pvalue->ueNetworkCapability.epsEncryptAlgs.x128_eea2 = 0;

   pvalue->ueNetworkCapability.epsEncryptAlgs.eea3 = 0;

   pvalue->ueNetworkCapability.epsEncryptAlgs.eea4 = 1;

   pvalue->ueNetworkCapability.epsEncryptAlgs.eea5 = 0;

   pvalue->ueNetworkCapability.epsEncryptAlgs.eea6 = 1;

   pvalue->ueNetworkCapability.epsEncryptAlgs.eea7 = 1;

   pvalue->ueNetworkCapability.epsIntegAlgs.eia0 = 0;

   pvalue->ueNetworkCapability.epsIntegAlgs.eia1 = 0;

   pvalue->ueNetworkCapability.epsIntegAlgs.eia2 = 1;

   pvalue->ueNetworkCapability.epsIntegAlgs.eia3 = 1;

   pvalue->ueNetworkCapability.epsIntegAlgs.eia4 = 1;

   pvalue->ueNetworkCapability.epsIntegAlgs.eia5 = 1;

   pvalue->ueNetworkCapability.epsIntegAlgs.eia6 = 1;

   pvalue->ueNetworkCapability.epsIntegAlgs.eia7 = 0;

   pvalue->ueNetworkCapability.m.umtsEncryptAlgsPresent = 1;
   pvalue->ueNetworkCapability.umtsEncryptAlgs.uea0 = 0;
   pvalue->ueNetworkCapability.umtsEncryptAlgs.uea1 = 1;
   pvalue->ueNetworkCapability.umtsEncryptAlgs.uea2 = 1;
   pvalue->ueNetworkCapability.umtsEncryptAlgs.uea3 = 0;
   pvalue->ueNetworkCapability.umtsEncryptAlgs.uea4 = 0;
   pvalue->ueNetworkCapability.umtsEncryptAlgs.uea5 = 1;
   pvalue->ueNetworkCapability.umtsEncryptAlgs.uea6 = 0;
   pvalue->ueNetworkCapability.umtsEncryptAlgs.uea7 = 1;

   pvalue->ueNetworkCapability.m.octet6Present = 1;
   pvalue->ueNetworkCapability.octet6.ucs2 = 0;
   pvalue->ueNetworkCapability.octet6.umtsIntegAlgs.uia1 = 1;
   pvalue->ueNetworkCapability.octet6.umtsIntegAlgs.uia2 = 1;
   pvalue->ueNetworkCapability.octet6.umtsIntegAlgs.uia3 = 0;
   pvalue->ueNetworkCapability.octet6.umtsIntegAlgs.uia4 = 1;
   pvalue->ueNetworkCapability.octet6.umtsIntegAlgs.uia5 = 0;
   pvalue->ueNetworkCapability.octet6.umtsIntegAlgs.uia6 = 1;
   pvalue->ueNetworkCapability.octet6.umtsIntegAlgs.uia7 = 1;

   pvalue->ueNetworkCapability.m.octet7Present = 1;
   pvalue->ueNetworkCapability.octet7.proSedd = 0;
   pvalue->ueNetworkCapability.octet7.proSe = 0;
   pvalue->ueNetworkCapability.octet7.h245_ash = 1;
   pvalue->ueNetworkCapability.octet7.acc_csfb = 0;
   pvalue->ueNetworkCapability.octet7.lpp = 1;
   pvalue->ueNetworkCapability.octet7.lcs = 0;
   pvalue->ueNetworkCapability.octet7.x1xSR_VCC = 1;
   pvalue->ueNetworkCapability.octet7.nf = 0;

   pvalue->ueNetworkCapability.spare4.numocts = 0;

   pvalue->m.lastVisitedRegisteredTAIPresent = 1;

   rtxStrncpy (pvalue->lastVisitedRegisteredTAI.mcc_mnc.mcc, 4, "525", 3);
   rtxStrncpy (pvalue->lastVisitedRegisteredTAI.mcc_mnc.mnc, 4, "03", 3);

   {
      static const OSOCTET testdata[] = {
      0xb0, 0xb };
      OSCRTLMEMCPY ((void*)pvalue->lastVisitedRegisteredTAI.tac.data, testdata, 2);
   }

   pvalue->m.drxParameterPresent = 1;

   pvalue->drxParameter.splitPGCycleCode = 173;

   pvalue->drxParameter.lenCoefAndValue = 7;

   pvalue->drxParameter.splitOnCCCH = 0;

   pvalue->drxParameter.nonDRXTimer = 6;

   pvalue->m.ueRadioCapInfoUpdateNeededPresent = 1;

   pvalue->ueRadioCapInfoUpdateNeeded.spare = 1;

   pvalue->ueRadioCapInfoUpdateNeeded.value = 0;

   pvalue->m.epsBearerContextStatusPresent = 1;

   pvalue->epsBearerContextStatus.ebi7 = 1;

   pvalue->epsBearerContextStatus.ebi6 = 0;

   pvalue->epsBearerContextStatus.ebi5 = 1;

   pvalue->epsBearerContextStatus.ebi4 = 0;

   pvalue->epsBearerContextStatus.ebi3 = 1;

   pvalue->epsBearerContextStatus.ebi2 = 0;

   pvalue->epsBearerContextStatus.ebi1 = 1;

   pvalue->epsBearerContextStatus.ebi0 = 1;

   pvalue->epsBearerContextStatus.ebi15 = 1;

   pvalue->epsBearerContextStatus.ebi14 = 0;

   pvalue->epsBearerContextStatus.ebi13 = 0;

   pvalue->epsBearerContextStatus.ebi12 = 0;

   pvalue->epsBearerContextStatus.ebi11 = 1;

   pvalue->epsBearerContextStatus.ebi10 = 0;

   pvalue->epsBearerContextStatus.ebi9 = 1;

   pvalue->epsBearerContextStatus.ebi8 = 1;

   pvalue->m.msNetworkCapabilityPresent = 1;
   pvalue->msNetworkCapability.length = 0; /* length will be calculated */

   pvalue->msNetworkCapability.m.octet1Present =
      pvalue->msNetworkCapability.m.octet2Present =
      pvalue->msNetworkCapability.m.octet3Present =
      pvalue->msNetworkCapability.m.octet4Present = 1;

   pvalue->msNetworkCapability.octet1.gea1 = 0;
   pvalue->msNetworkCapability.octet1.smCapDeicatedChan = 0;
   pvalue->msNetworkCapability.octet1.smCapGPRSChan = 0;
   pvalue->msNetworkCapability.octet1.ucs2Support = 0;
   pvalue->msNetworkCapability.octet1.ssScreeningInd = 2;
   pvalue->msNetworkCapability.octet1.soLSACap = 1;
   pvalue->msNetworkCapability.octet1.revisionLevelInd = 0;
   pvalue->msNetworkCapability.octet2.pfcFeatureMode = 1;
   pvalue->msNetworkCapability.octet2.extendedGEA = 60;
   pvalue->msNetworkCapability.octet2.lcsVACap = 0;

   pvalue->msNetworkCapability.octet3.psInterRATHOToUTRANIuModeCap = 1;
   pvalue->msNetworkCapability.octet3.psInterRATHOToEUTRANS1ModeCap = 0;
   pvalue->msNetworkCapability.octet3.emmCombinedProcCap = 0;
   pvalue->msNetworkCapability.octet3.isrSupport = 0;
   pvalue->msNetworkCapability.octet3.srvccToGERAN_UTRANCap = 1;
   pvalue->msNetworkCapability.octet3.epcCap = 0;
   pvalue->msNetworkCapability.octet3.nfCapability = 1;
   pvalue->msNetworkCapability.octet3.geranNetShareCap = 0;

   pvalue->msNetworkCapability.octet4.userPlaneIntegProtSupp = 1;
   pvalue->msNetworkCapability.octet4.gia_4 = 1;
   pvalue->msNetworkCapability.octet4.gia_5 = 0;
   pvalue->msNetworkCapability.octet4.gia_6 = 1;
   pvalue->msNetworkCapability.octet4.gia_7 = 1;
   pvalue->msNetworkCapability.octet4.epcoIeIndicator = 0;
   pvalue->msNetworkCapability.octet4.restrictUseEnhancedCovCap = 1;
   pvalue->msNetworkCapability.octet4.dualConnEutraNRCap = 0;

   // pvalue->msNetworkCapability.m.spareBitsPresent = 1;
   pvalue->msNetworkCapability.spareBits.numbits = 11;
   {
      OSOCTET* bitData = (OSOCTET*) rtxMemAlloc (pctxt,2);
      bitData[0] = 0x4f;
      bitData[1] = 0x39;
      pvalue->msNetworkCapability.spareBits.data = (const OSOCTET*)bitData;
   }

   pvalue->m.oldLocAreaIdentPresent = 1;

   rtxStrncpy (pvalue->oldLocAreaIdent.mcc_mnc.mcc, 4, "547", 3);
   rtxStrncpy (pvalue->oldLocAreaIdent.mcc_mnc.mnc, 4, "20", 3);

   pvalue->oldLocAreaIdent.lac = 12004;

   pvalue->m.tmsiStatusPresent = 1;

   pvalue->tmsiStatus.spare = 3;

   pvalue->tmsiStatus.flag = 0;

   pvalue->m.mobileStationClassmark2Present = 1;

   pvalue->mobileStationClassmark2.m.cm1Present = 1;

   pvalue->mobileStationClassmark2.cm1.spare = 0;

   pvalue->mobileStationClassmark2.cm1.revLevel = 0;

   pvalue->mobileStationClassmark2.cm1.esInd = 0;

   pvalue->mobileStationClassmark2.cm1.a5_1_alg = 1;

   pvalue->mobileStationClassmark2.cm1.rfPowerCap = TS24008IE_RFPowerCapValues_class4;

   pvalue->mobileStationClassmark2.m.octet4Present = 1;

   pvalue->mobileStationClassmark2.octet4.spare = 0;

   pvalue->mobileStationClassmark2.octet4.psCapability = 0;

   pvalue->mobileStationClassmark2.octet4.ssScreeningInd = 2;

   pvalue->mobileStationClassmark2.octet4.smCapability = 1;

   pvalue->mobileStationClassmark2.octet4.vbsNotifRecept = 1;

   pvalue->mobileStationClassmark2.octet4.vgcsNotifRecept = 0;

   pvalue->mobileStationClassmark2.octet4.fcFreqCap = 0;

   pvalue->mobileStationClassmark2.m.octet5Present = 1;

   pvalue->mobileStationClassmark2.octet5.cm3 = 1;

   pvalue->mobileStationClassmark2.octet5.spare = 0;

   pvalue->mobileStationClassmark2.octet5.lcsvaCap = 1;

   pvalue->mobileStationClassmark2.octet5.ucs2Treatment = 0;

   pvalue->mobileStationClassmark2.octet5.soLSA = 1;

   pvalue->mobileStationClassmark2.octet5.cmsp = 1;

   pvalue->mobileStationClassmark2.octet5.a5_3_alg = 1;

   pvalue->mobileStationClassmark2.octet5.a5_2_alg = 1;

   pvalue->m.mobileStationClassmark3Present = 1;
   pvalue->mobileStationClassmark3.length = 0; /* length will be calculated */

   pvalue->mobileStationClassmark3.spare = 0;

   pvalue->mobileStationClassmark3.multiband.supported = TS24008IE_MBSEnum_mbs0;

   pvalue->mobileStationClassmark3.multiband.a5bits.a5_7 = 0;

   pvalue->mobileStationClassmark3.multiband.a5bits.a5_6 = 0;

   pvalue->mobileStationClassmark3.multiband.a5bits.a5_5 = 1;

   pvalue->mobileStationClassmark3.multiband.a5bits.a5_4 = 0;

   pvalue->mobileStationClassmark3.m.rSupportPresent = 1;
   pvalue->mobileStationClassmark3.rSupport = 2;

   pvalue->mobileStationClassmark3.m.hscsdMultiSlotCapPresent = 1;
   pvalue->mobileStationClassmark3.hscsdMultiSlotCap = 0;

   pvalue->mobileStationClassmark3.ucs2Treatment = 1;

   pvalue->mobileStationClassmark3.extMeasurementCap = 0;

   pvalue->mobileStationClassmark3.m.msMeasurementCapPresent = 1;

   pvalue->mobileStationClassmark3.msMeasurementCap.smsValue = 4;

   pvalue->mobileStationClassmark3.msMeasurementCap.smValue = 14;

   pvalue->mobileStationClassmark3.m.msPositioningMethodCapPresent = 1;
   pvalue->mobileStationClassmark3.msPositioningMethodCap = 29;

   pvalue->mobileStationClassmark3.m.ecsdMultiSlotCapPresent = 1;
   pvalue->mobileStationClassmark3.ecsdMultiSlotCap = 21;

   pvalue->mobileStationClassmark3.m.an_8_PSKStructPresent = 1;

   pvalue->mobileStationClassmark3.an_8_PSKStruct.modulationCap = 0;

   pvalue->mobileStationClassmark3.an_8_PSKStruct.m.rfPowerCap1Present = 1;
   pvalue->mobileStationClassmark3.an_8_PSKStruct.rfPowerCap1 = 2;

   pvalue->mobileStationClassmark3.an_8_PSKStruct.m.rfPowerCap2Present = 1;
   pvalue->mobileStationClassmark3.an_8_PSKStruct.rfPowerCap2 = 2;

   pvalue->mobileStationClassmark3.m.gsm400StructPresent = 1;

   pvalue->mobileStationClassmark3.gsm400Struct.bandsSupported = TS24008IE_GSM400Struct_bandsSupported_band1;

   pvalue->mobileStationClassmark3.gsm400Struct.assocRadioCap = 13;

   pvalue->mobileStationClassmark3.m.gsm850AssocRadioCapPresent = 1;
   pvalue->mobileStationClassmark3.gsm850AssocRadioCap = 1;

   pvalue->mobileStationClassmark3.m.gsm1900AssocRadioCapPresent = 1;
   pvalue->mobileStationClassmark3.gsm1900AssocRadioCap = 9;

   pvalue->mobileStationClassmark3.umtsFDDRadioAccessTechCap = 0;

   pvalue->mobileStationClassmark3.umts384McpsTDDRadioAccessTechCap = 0;

   pvalue->mobileStationClassmark3.cdma2000RadioAccessTechCap = 0;

   pvalue->mobileStationClassmark3.m.dtmGPRSStructPresent = 1;

   pvalue->mobileStationClassmark3.dtmGPRSStruct.dtmGPRSMultiSlotClass = 1;

   pvalue->mobileStationClassmark3.dtmGPRSStruct.singleSlotDTM = 0;

   pvalue->mobileStationClassmark3.dtmGPRSStruct.m.dtmEGPRSMultiSlotClassPresent = 1;
   pvalue->mobileStationClassmark3.dtmGPRSStruct.dtmEGPRSMultiSlotClass = 2;

   pvalue->mobileStationClassmark3.m.singleBandSupportPresent = 1;
   pvalue->mobileStationClassmark3.singleBandSupport = 10;

   pvalue->mobileStationClassmark3.m.gsm750AssocRadioCapPresent = 1;
   pvalue->mobileStationClassmark3.gsm750AssocRadioCap = 5;

   pvalue->mobileStationClassmark3.umts1_28McpsTDDRadioAccessTechCap = 1;

   pvalue->mobileStationClassmark3.geranFeaturePackage1 = 1;

   pvalue->mobileStationClassmark3.m.extDtmGPRSStructPresent = 1;

   pvalue->mobileStationClassmark3.extDtmGPRSStruct.extDtmGPRSMultiSlotClass = 2;

   pvalue->mobileStationClassmark3.extDtmGPRSStruct.extDtmEGPRSMultiSlotClass = 1;

   pvalue->mobileStationClassmark3.m.highMultislotCapPresent = 1;
   pvalue->mobileStationClassmark3.highMultislotCap = 0;

   pvalue->mobileStationClassmark3.m.geranIuModeCapPresent = 1;
   pvalue->mobileStationClassmark3.geranIuModeCap.length = 0; /* length will be calculated */

   pvalue->mobileStationClassmark3.geranIuModeCap.floIuCap = 0;

   pvalue->mobileStationClassmark3.geranIuModeCap.spareBits.numbits = 3;
   pvalue->mobileStationClassmark3.geranIuModeCap.spareBits.data[0] = 0x67;

   pvalue->mobileStationClassmark3.geranFeaturePackage2 = 1;

   pvalue->mobileStationClassmark3.gmskMultislotPowerProfile = 1;

   pvalue->mobileStationClassmark3.multislotPowerProfile8PSK = 2;

   pvalue->mobileStationClassmark3.m.tgsm400StructPresent = 1;

   pvalue->mobileStationClassmark3.tgsm400Struct.bandsSupported = TS24008IE_GSM400Struct_bandsSupported_band1;

   pvalue->mobileStationClassmark3.tgsm400Struct.assocRadioCap = 2;

   pvalue->mobileStationClassmark3.zerobit = 0;

   pvalue->mobileStationClassmark3.downlinkAdvancedRcvrPerf = 0;

   pvalue->mobileStationClassmark3.dtmEnhancementsCap = 1;

   pvalue->mobileStationClassmark3.m.dtmGPRSStruct2Present = 1;

   pvalue->mobileStationClassmark3.dtmGPRSStruct2.dtmGPRSHighMultiSlotClass = 6;

   pvalue->mobileStationClassmark3.dtmGPRSStruct2.offsetRequired = 0;

   pvalue->mobileStationClassmark3.dtmGPRSStruct2.m.dtmEGPRSHighMultiSlotClassPresent = 1;
   pvalue->mobileStationClassmark3.dtmGPRSStruct2.dtmEGPRSHighMultiSlotClass = 1;

   pvalue->mobileStationClassmark3.repeatedACCHCap = 1;

   pvalue->mobileStationClassmark3.m.gsm710AssocRadioCapPresent = 1;
   pvalue->mobileStationClassmark3.gsm710AssocRadioCap = 11;

   pvalue->mobileStationClassmark3.m.tgsm810AssocRadioCapPresent = 1;
   pvalue->mobileStationClassmark3.tgsm810AssocRadioCap = 14;

   pvalue->mobileStationClassmark3.cipheringModeSettingCap = 1;

   pvalue->mobileStationClassmark3.additionalPositioningCap = 1;

   pvalue->mobileStationClassmark3.e_UTRA_FDD_support = 0;

   pvalue->mobileStationClassmark3.e_UTRA_TDD_support = 1;

   pvalue->mobileStationClassmark3.e_UTRA_MeasAndReportSupport = 0;

   pvalue->mobileStationClassmark3.priorityBasedReselectionSupport = 1;

   pvalue->mobileStationClassmark3.uTRA_CSG_Cells_Reporting = 0;

   pvalue->mobileStationClassmark3.vAMOS_Level = 2;

   pvalue->mobileStationClassmark3.tighterCapability = 0;

   pvalue->mobileStationClassmark3.selCiphOf_DL_SACCH = 1;

   pvalue->mobileStationClassmark3.m.spareBitsPresent = 1;
   pvalue->mobileStationClassmark3.spareBits.numbits = 2;
   {
      OSOCTET* bitData = (OSOCTET*) rtxMemAlloc (pctxt,1);
      bitData[0] = 0x31;
      pvalue->mobileStationClassmark3.spareBits.data = (const OSOCTET*)bitData;
   }

   pvalue->m.supportedCodecsPresent = 1;
   pvalue->supportedCodecs.length = 0; /* length will be calculated */

   pvalue->supportedCodecs.codecs.n = 1;

   pvalue->supportedCodecs.codecs.elem[0].sysID = 19;

   {
      static const OSOCTET testdata[] = {
      0xa0 };
      pvalue->supportedCodecs.codecs.elem[0].codecBitmap.numocts = 1;
      OSCRTLMEMCPY ((void*)pvalue->supportedCodecs.codecs.elem[0].codecBitmap.data, testdata, 1);
   }

   pvalue->m.addnUpdateTypePresent = 1;

   pvalue->addnUpdateType.pnb_CIoT = 
      TS24301IE_AddnUpdateType_pnb_CIoT_noAddInfo;

   /* Populate the Boolean type */
   pvalue->addnUpdateType.saf = 0;

   /* Populate the Boolean type */
   pvalue->addnUpdateType.autv = 0;

   pvalue->m._v16ExtPresent = 1;
   pvalue->m.ueRadioCapIdAvailPresent = 1;
   pvalue->ueRadioCapIdAvail.value = 7;

   pvalue->m.requestedWUSAssistInfoPresent = 1;
   pvalue->requestedWUSAssistInfo.types.n = 1;
   pvalue->requestedWUSAssistInfo.types.elem[0].infoType = TS24301IE_InformationType_itUEPagingProbInfo;
   pvalue->requestedWUSAssistInfo.types.elem[0].infoValue = 30;

   pvalue->m.nbs1DRXParamPresent = 1;
   pvalue->nbs1DRXParam.drxValue = 10;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24301Msg_PDU (&ctxt, &pdu);
   if (0 != ret) {
      printf ("encode PDU failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "");
      printf ("\n");
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
