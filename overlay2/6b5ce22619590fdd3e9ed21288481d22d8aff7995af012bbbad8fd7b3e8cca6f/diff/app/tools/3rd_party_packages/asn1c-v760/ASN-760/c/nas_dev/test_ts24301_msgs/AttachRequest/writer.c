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
   TS24301Msg_AttachRequest data;
   TS24301Msg_AttachRequest* pvalue = &data;
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
   asn1SetTC_TS24301Msg_PDU_obj_AttachRequest (&ctxt, &pdu, pvalue);

   asn1Init_TS24301Msg_AttachRequest (pvalue);

   /* Start SEQUENCE or SET 1074 (level 0) */

   /* Start SEQUENCE or SET 1075 (level 1) */

   /* Populate the Boolean type */
   pvalue->epsAttachType.spare = 0;

   /* Populate the Integer type */
   pvalue->epsAttachType.value = 0;
   /* End SEQUENCE or SET 1075 */

   /* Start SEQUENCE or SET 1076 (level 1) */

   /* Populate the Boolean type */
   pvalue->nasKeySetIdentifier.tsc = 0;

   /* Populate the Integer type */
   pvalue->nasKeySetIdentifier.ident = 4;
   /* End SEQUENCE or SET 1076 */

   /* Start SEQUENCE or SET 1077 (level 1) */

   /* Populate the Integer type */
   pvalue->oldGUTIOrIMSI.length = 16;

   /* Populate the Boolean type */
   pvalue->oldGUTIOrIMSI.oddEvenInd = 1;

   /* Populate the Enumerated type */
   pvalue->oldGUTIOrIMSI.typeOfIdent = 
      TS24301IE_EPSMobileIdentity_typeOfIdent_imsi;

   /* imsi */
   rtxStrncpy (pvalue->oldGUTIOrIMSI.content.u.imsi, 
               sizeof(pvalue->oldGUTIOrIMSI.content.u.imsi), 
               "12345678901234", 14);

   /* End SEQUENCE or SET 1077 */

   /* Start SEQUENCE or SET 1081 (level 1) */

   /* Populate the Integer type */
   pvalue->ueNetworkCapability.length = 8;

   /* Start SEQUENCE or SET 1082 (level 2) */

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.epsEncryptAlgs.eea0 = 0;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.epsEncryptAlgs.x128_eea1 = 0;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.epsEncryptAlgs.x128_eea2 = 0;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.epsEncryptAlgs.eea3 = 1;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.epsEncryptAlgs.eea4 = 0;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.epsEncryptAlgs.eea5 = 1;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.epsEncryptAlgs.eea6 = 1;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.epsEncryptAlgs.eea7 = 1;
   /* End SEQUENCE or SET 1082 */

   pvalue->ueNetworkCapability.epsIntegAlgs.eia0 = 0;
   pvalue->ueNetworkCapability.epsIntegAlgs.eia1 = 0;
   pvalue->ueNetworkCapability.epsIntegAlgs.eia2 = 0;
   pvalue->ueNetworkCapability.epsIntegAlgs.eia3 = 1;
   pvalue->ueNetworkCapability.epsIntegAlgs.eia4 = 0;
   pvalue->ueNetworkCapability.epsIntegAlgs.eia5 = 0;
   pvalue->ueNetworkCapability.epsIntegAlgs.eia6 = 1;
   pvalue->ueNetworkCapability.epsIntegAlgs.eia7 = 1;

   /* Start SEQUENCE or SET 1084 (level 2) */

   pvalue->ueNetworkCapability.m.umtsEncryptAlgsPresent = 1;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.umtsEncryptAlgs.uea0 = 0;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.umtsEncryptAlgs.uea1 = 0;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.umtsEncryptAlgs.uea2 = 1;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.umtsEncryptAlgs.uea3 = 0;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.umtsEncryptAlgs.uea4 = 0;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.umtsEncryptAlgs.uea5 = 1;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.umtsEncryptAlgs.uea6 = 0;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.umtsEncryptAlgs.uea7 = 0;
   /* End SEQUENCE or SET 1084 */

   pvalue->ueNetworkCapability.m.octet6Present = 1;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.octet6.ucs2 = 1;

   /* Start SEQUENCE or SET 1085 (level 2) */

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.octet6.umtsIntegAlgs.uia1 = 0;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.octet6.umtsIntegAlgs.uia2 = 0;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.octet6.umtsIntegAlgs.uia3 = 1;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.octet6.umtsIntegAlgs.uia4 = 0;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.octet6.umtsIntegAlgs.uia5 = 1;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.octet6.umtsIntegAlgs.uia6 = 1;

   /* Populate the Boolean type */
   pvalue->ueNetworkCapability.octet6.umtsIntegAlgs.uia7 = 0;
   /* End SEQUENCE or SET 1085 */

   pvalue->ueNetworkCapability.m.octet7Present = 1;
   pvalue->ueNetworkCapability.octet7.proSedd = 0;
   pvalue->ueNetworkCapability.octet7.proSe = 0;
   pvalue->ueNetworkCapability.octet7.h245_ash = 1;
   pvalue->ueNetworkCapability.octet7.acc_csfb = 0;
   pvalue->ueNetworkCapability.octet7.lpp = 1;
   pvalue->ueNetworkCapability.octet7.lcs = 0;
   pvalue->ueNetworkCapability.octet7.x1xSR_VCC = 1;
   pvalue->ueNetworkCapability.octet7.nf = 0;

   /* Populate OCTET STRING variable */
   {
      pvalue->ueNetworkCapability.spare4.numocts = 0;
   }
   /* End SEQUENCE or SET 1081 */

   /* Populate ESMMessageContainer variable */
   TS24301Msg_PDU_SM pdu_SM;
   TS24301Msg_ESMDataTransport data_SM;
   TS24301Msg_ESMDataTransport* pvalue_SM = &data_SM;

   pdu_SM.l3HdrOpts.t = T_TS24007L3_L3HdrOptions_epsBearerIdent;
   pdu_SM.l3HdrOpts.u.epsBearerIdent = TS24007L3_EPSBearerIdentity_id6;
   pdu_SM.protoDiscr = TS24007L3_ProtoDiscr_epsSessMgmt;
   pdu_SM.pti.u.value = 0;
   asn1SetTC_TS24301Msg_PDU_SM_obj_ESMDataTransport(&ctxt, &pdu_SM, pvalue_SM);
   OSCRTLMEMSET(&data_SM, 0, sizeof(TS24301Msg_ESMDataTransport));

   pvalue->esmMessageContainer.length = 0; /* length will be calculated */
   pvalue_SM->userDataContainer.length = 0; /* length will be calculated */
   pvalue_SM->userDataContainer.contents.data = (OSOCTET *)rtxMemAlloc(&ctxt, 4);
   {
      static const OSOCTET testdata[] = {
      0x08, 0x0d, 0x49, 0x97 };
      pvalue_SM->userDataContainer.contents.numocts = 4;
      OSCRTLMEMCPY((void *)pvalue_SM->userDataContainer.contents.data,
                   testdata, 4);
   }
   pvalue_SM->m.releaseAssistIndPresent = 1;
   pvalue_SM->releaseAssistInd.ddx = TS24301IE_ReleaseAssistInd_ddx_ddxSingleDLTrans;
   pvalue->esmMessageContainer.pduSm = pdu_SM;

   pvalue->m.oldP_TMSISignaturePresent = 1;
   /* Start SEQUENCE or SET 1086 (level 1) */

   /* Populate OCTET STRING variable */
   {
      static const OSOCTET testdata[] = {
      0xc1, 0x9a, 0x12 };
      OSCRTLMEMCPY ((void*)pvalue->oldP_TMSISignature.value, testdata, 3);
   }
   /* End SEQUENCE or SET 1086 */

   pvalue->m.additionalGUTIPresent = 1;
   /* Start SEQUENCE or SET 1087 (level 1) */

   /* Populate the Integer type */
   pvalue->additionalGUTI.length = 16;

   /* Populate the Boolean type */
   pvalue->additionalGUTI.oddEvenInd = 0;

   /* Populate the Enumerated type */
   pvalue->additionalGUTI.typeOfIdent = 
      TS24301IE_EPSMobileIdentity_typeOfIdent_imsi;

   /* imsi */
   rtxStrncpy (pvalue->additionalGUTI.content.u.imsi, 
               sizeof(pvalue->additionalGUTI.content.u.imsi), 
               "123456789012345", 15);

   /* End SEQUENCE or SET 1087 */

   pvalue->m.lastVisitedRegisteredTAIPresent = 1;
   /* Start SEQUENCE or SET 1091 (level 1) */

   /* Start SEQUENCE or SET 1092 (level 2) */

   /* Populate the Character String */
   rtxStrncpy (pvalue->lastVisitedRegisteredTAI.mcc_mnc.mcc, 
               sizeof(pvalue->lastVisitedRegisteredTAI.mcc_mnc.mcc), 
               "199", 4);

   /* Populate the Character String */
   rtxStrncpy (pvalue->lastVisitedRegisteredTAI.mcc_mnc.mnc, 
               sizeof(pvalue->lastVisitedRegisteredTAI.mcc_mnc.mnc), 
               "b48", 4);

   /* End SEQUENCE or SET 1092 */

   /* Populate OCTET STRING variable */
   {
      static const OSOCTET testdata[] = {
      0x68, 0x67 };
      OSCRTLMEMCPY ((void*)pvalue->lastVisitedRegisteredTAI.tac.data, testdata, 2);
   }
   /* End SEQUENCE or SET 1091 */

   pvalue->m.drxParameterPresent = 1;
   /* Start SEQUENCE or SET 1093 (level 1) */

   /* Populate the Integer type */
   pvalue->drxParameter.splitPGCycleCode = 45;

   /* Populate the Integer type */
   pvalue->drxParameter.lenCoefAndValue = 9;

   /* Populate the Boolean type */
   pvalue->drxParameter.splitOnCCCH = 1;

   /* Populate the Integer type */
   pvalue->drxParameter.nonDRXTimer = 2;
   /* End SEQUENCE or SET 1093 */

   pvalue->m.msNetworkCapabilityPresent = 1;
   /* Start SEQUENCE or SET 1094 (level 1) */
   pvalue->msNetworkCapability.m.octet1Present = 
      pvalue->msNetworkCapability.m.octet2Present = 
      pvalue->msNetworkCapability.m.octet3Present =  1;

   /* Populate the Integer type */
   pvalue->msNetworkCapability.length = 7;

   /* Populate the Boolean type */
   pvalue->msNetworkCapability.octet1.gea1 = 1;

   /* Populate the Boolean type */
   pvalue->msNetworkCapability.octet1.smCapDeicatedChan = 0;

   /* Populate the Boolean type */
   pvalue->msNetworkCapability.octet1.smCapGPRSChan = 0;

   /* Populate the Boolean type */
   pvalue->msNetworkCapability.octet1.ucs2Support = 1;

   /* Populate the Integer type */
   pvalue->msNetworkCapability.octet1.ssScreeningInd = 1;

   /* Populate the Boolean type */
   pvalue->msNetworkCapability.octet1.soLSACap = 1;

   /* Populate the Boolean type */
   pvalue->msNetworkCapability.octet1.revisionLevelInd = 0;

   /* Populate the Boolean type */
   pvalue->msNetworkCapability.octet2.pfcFeatureMode = 0;

   /* Populate the Integer type */
   pvalue->msNetworkCapability.octet2.extendedGEA = 12;

   /* Populate the Boolean type */
   pvalue->msNetworkCapability.octet2.lcsVACap = 1;

   /* Populate the Boolean type */
   pvalue->msNetworkCapability.octet3.psInterRATHOToUTRANIuModeCap = 1;

   /* Populate the Boolean type */
   pvalue->msNetworkCapability.octet3.psInterRATHOToEUTRANS1ModeCap = 0;

   /* Populate the Boolean type */
   pvalue->msNetworkCapability.octet3.emmCombinedProcCap = 1;

   /* Populate the Boolean type */
   pvalue->msNetworkCapability.octet3.isrSupport = 1;

   /* Populate the Boolean type */
   pvalue->msNetworkCapability.octet3.srvccToGERAN_UTRANCap = 1;

   /* Populate the Boolean type */
   pvalue->msNetworkCapability.octet3.epcCap = 0;

   /* Populate the Boolean type */
   pvalue->msNetworkCapability.octet3.nfCapability = 0;

   /* Populate the Boolean type */
   pvalue->msNetworkCapability.octet3.geranNetShareCap = 1;

   /* End SEQUENCE or SET 1094 */

   pvalue->m.oldLocAreaIdentPresent = 1;
   /* Start SEQUENCE or SET 1095 (level 1) */

   /* Start SEQUENCE or SET 1096 (level 2) */

   /* Populate the Character String */
   rtxStrncpy (pvalue->oldLocAreaIdent.mcc_mnc.mcc, 
               sizeof(pvalue->oldLocAreaIdent.mcc_mnc.mcc), 
               "0#a", 4);

   /* Populate the Character String */
   rtxStrncpy (pvalue->oldLocAreaIdent.mcc_mnc.mnc, 
               sizeof(pvalue->oldLocAreaIdent.mcc_mnc.mnc), 
               "*1a", 4);

   /* End SEQUENCE or SET 1096 */

   /* Populate the Integer type */
   pvalue->oldLocAreaIdent.lac = 26811;
   /* End SEQUENCE or SET 1095 */

   pvalue->m.tmsiStatusPresent = 1;
   /* Start SEQUENCE or SET 1097 (level 1) */

   /* Populate the Integer type */
   pvalue->tmsiStatus.spare = 3;

   /* Populate the Boolean type */
   pvalue->tmsiStatus.flag = 0;
   /* End SEQUENCE or SET 1097 */

   pvalue->m.mobileStationClassmark2Present = 1;
   /* Start SEQUENCE or SET 1098 (level 1) */

   pvalue->mobileStationClassmark2.m.cm1Present = 1;
   /* Start SEQUENCE or SET 1099 (level 2) */

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark2.cm1.spare = 0;

   /* Populate the Integer type */
   pvalue->mobileStationClassmark2.cm1.revLevel = 2;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark2.cm1.esInd = 1;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark2.cm1.a5_1_alg = 1;

   /* Populate the Integer type */
   pvalue->mobileStationClassmark2.cm1.rfPowerCap = TS24008IE_RFPowerCapValues_class3;
   /* End SEQUENCE or SET 1099 */

   pvalue->mobileStationClassmark2.m.octet4Present = 1;
   /* Start SEQUENCE or SET 1100 (level 2) */

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark2.octet4.spare = 0;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark2.octet4.psCapability = 1;

   /* Populate the Integer type */
   pvalue->mobileStationClassmark2.octet4.ssScreeningInd = 1;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark2.octet4.smCapability = 0;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark2.octet4.vbsNotifRecept = 0;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark2.octet4.vgcsNotifRecept = 1;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark2.octet4.fcFreqCap = 0;
   /* End SEQUENCE or SET 1100 */

   pvalue->mobileStationClassmark2.m.octet5Present = 1;
   /* Start SEQUENCE or SET 1101 (level 2) */

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark2.octet5.cm3 = 0;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark2.octet5.spare = 0;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark2.octet5.lcsvaCap = 0;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark2.octet5.ucs2Treatment = 0;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark2.octet5.soLSA = 1;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark2.octet5.cmsp = 1;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark2.octet5.a5_3_alg = 1;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark2.octet5.a5_2_alg = 1;
   /* End SEQUENCE or SET 1101 */
   /* End SEQUENCE or SET 1098 */

   pvalue->m.mobileStationClassmark3Present = 1;
   /* Start SEQUENCE or SET 1102 (level 1) */

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.spare = 0;

   /* Start SEQUENCE or SET 1103 (level 2) */

   /* Populate the Enumerated type */
   pvalue->mobileStationClassmark3.multiband.supported = TS24008IE_MBSEnum_mbs0;

   /* Start SEQUENCE or SET 1104 (level 3) */

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.multiband.a5bits.a5_7 = 0;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.multiband.a5bits.a5_6 = 1;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.multiband.a5bits.a5_5 = 0;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.multiband.a5bits.a5_4 = 1;
   /* End SEQUENCE or SET 1104 */

   /* End SEQUENCE or SET 1103 */

   pvalue->mobileStationClassmark3.m.rSupportPresent = 1;
   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.rSupport = 4;

   pvalue->mobileStationClassmark3.m.hscsdMultiSlotCapPresent = 1;
   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.hscsdMultiSlotCap = 30;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.ucs2Treatment = 0;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.extMeasurementCap = 0;

   pvalue->mobileStationClassmark3.m.msMeasurementCapPresent = 1;
   /* Start SEQUENCE or SET 1105 (level 2) */

   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.msMeasurementCap.smsValue = 11;

   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.msMeasurementCap.smValue = 14;
   /* End SEQUENCE or SET 1105 */

   pvalue->mobileStationClassmark3.m.msPositioningMethodCapPresent = 1;
   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.msPositioningMethodCap = 10;

   pvalue->mobileStationClassmark3.m.ecsdMultiSlotCapPresent = 1;
   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.ecsdMultiSlotCap = 8;

   pvalue->mobileStationClassmark3.m.an_8_PSKStructPresent = 1;
   /* Start SEQUENCE or SET 1106 (level 2) */

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.an_8_PSKStruct.modulationCap = 1;

   pvalue->mobileStationClassmark3.an_8_PSKStruct.m.rfPowerCap1Present = 1;
   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.an_8_PSKStruct.rfPowerCap1 = 2;

   pvalue->mobileStationClassmark3.an_8_PSKStruct.m.rfPowerCap2Present = 1;
   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.an_8_PSKStruct.rfPowerCap2 = 2;
   /* End SEQUENCE or SET 1106 */

   pvalue->mobileStationClassmark3.m.gsm400StructPresent = 1;
   /* Start SEQUENCE or SET 1107 (level 2) */

   /* Populate the Enumerated type */
   pvalue->mobileStationClassmark3.gsm400Struct.bandsSupported = TS24008IE_GSM400Struct_bandsSupported_band1;

   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.gsm400Struct.assocRadioCap = 5;
   /* End SEQUENCE or SET 1107 */

   pvalue->mobileStationClassmark3.m.gsm850AssocRadioCapPresent = 1;
   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.gsm850AssocRadioCap = 0;

   pvalue->mobileStationClassmark3.m.gsm1900AssocRadioCapPresent = 1;
   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.gsm1900AssocRadioCap = 12;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.umtsFDDRadioAccessTechCap = 1;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.umts384McpsTDDRadioAccessTechCap = 0;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.cdma2000RadioAccessTechCap = 0;

   pvalue->mobileStationClassmark3.m.dtmGPRSStructPresent = 1;
   /* Start SEQUENCE or SET 1108 (level 2) */

   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.dtmGPRSStruct.dtmGPRSMultiSlotClass = 1;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.dtmGPRSStruct.singleSlotDTM = 1;

   pvalue->mobileStationClassmark3.dtmGPRSStruct.m.dtmEGPRSMultiSlotClassPresent = 1;
   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.dtmGPRSStruct.dtmEGPRSMultiSlotClass = 2;
   /* End SEQUENCE or SET 1108 */

   pvalue->mobileStationClassmark3.m.singleBandSupportPresent = 1;
   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.singleBandSupport = 5;

   pvalue->mobileStationClassmark3.m.gsm750AssocRadioCapPresent = 1;
   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.gsm750AssocRadioCap = 8;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.umts1_28McpsTDDRadioAccessTechCap = 0;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.geranFeaturePackage1 = 0;

   pvalue->mobileStationClassmark3.m.extDtmGPRSStructPresent = 1;
   /* Start SEQUENCE or SET 1109 (level 2) */

   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.extDtmGPRSStruct.extDtmGPRSMultiSlotClass = 1;

   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.extDtmGPRSStruct.extDtmEGPRSMultiSlotClass = 0;
   /* End SEQUENCE or SET 1109 */

   pvalue->mobileStationClassmark3.m.highMultislotCapPresent = 1;
   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.highMultislotCap = 1;

   pvalue->mobileStationClassmark3.m.geranIuModeCapPresent = 1;
   /* Start SEQUENCE or SET 1110 (level 2) */

   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.geranIuModeCap.length = 11;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.geranIuModeCap.floIuCap = 1;

   /* Populate BIT STRING variable */
   pvalue->mobileStationClassmark3.geranIuModeCap.spareBits.numbits = 13;
   pvalue->mobileStationClassmark3.geranIuModeCap.spareBits.data[0] = 0x4f;
   pvalue->mobileStationClassmark3.geranIuModeCap.spareBits.data[1] = 0x50;
   /* End SEQUENCE or SET 1110 */

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.geranFeaturePackage2 = 0;

   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.gmskMultislotPowerProfile = 1;

   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.multislotPowerProfile8PSK = 1;

   pvalue->mobileStationClassmark3.m.tgsm400StructPresent = 1;
   /* Start SEQUENCE or SET 1111 (level 2) */

   /* Populate the Enumerated type */
   pvalue->mobileStationClassmark3.tgsm400Struct.bandsSupported = TS24008IE_GSM400Struct_bandsSupported_band1;

   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.tgsm400Struct.assocRadioCap = 12;
   /* End SEQUENCE or SET 1111 */

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.zerobit = 0;

   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.downlinkAdvancedRcvrPerf = 1;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.dtmEnhancementsCap = 1;

   pvalue->mobileStationClassmark3.m.dtmGPRSStruct2Present = 1;
   /* Start SEQUENCE or SET 1112 (level 2) */

   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.dtmGPRSStruct2.dtmGPRSHighMultiSlotClass = 0;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.dtmGPRSStruct2.offsetRequired = 0;

   pvalue->mobileStationClassmark3.dtmGPRSStruct2.m.dtmEGPRSHighMultiSlotClassPresent = 1;
   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.dtmGPRSStruct2.dtmEGPRSHighMultiSlotClass = 6;
   /* End SEQUENCE or SET 1112 */

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.repeatedACCHCap = 0;

   pvalue->mobileStationClassmark3.m.gsm710AssocRadioCapPresent = 1;
   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.gsm710AssocRadioCap = 7;

   pvalue->mobileStationClassmark3.m.tgsm810AssocRadioCapPresent = 1;
   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.tgsm810AssocRadioCap = 14;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.cipheringModeSettingCap = 1;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.additionalPositioningCap = 0;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.e_UTRA_FDD_support = 0;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.e_UTRA_TDD_support = 1;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.e_UTRA_MeasAndReportSupport = 1;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.priorityBasedReselectionSupport = 0;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.uTRA_CSG_Cells_Reporting = 1;

   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.vAMOS_Level = 0;

   /* Populate the Integer type */
   pvalue->mobileStationClassmark3.tighterCapability = 1;

   /* Populate the Boolean type */
   pvalue->mobileStationClassmark3.selCiphOf_DL_SACCH = 0;

   pvalue->mobileStationClassmark3.m.spareBitsPresent = 1;
   /* Populate BIT STRING variable */
   pvalue->mobileStationClassmark3.spareBits.numbits = 10;
   {
      OSOCTET* bitData = (OSOCTET*) rtxMemAlloc (pctxt,2);
      bitData[0] = 0x63;
      bitData[1] = 0x4e;
      pvalue->mobileStationClassmark3.spareBits.data = (const OSOCTET*)bitData;
   }
   /* End SEQUENCE or SET 1102 */

   pvalue->m.supportedCodecsPresent = 1;
   /* Start SEQUENCE or SET 1113 (level 1) */

   /* Populate the Integer type */
   pvalue->supportedCodecs.length = 22;

   /* Start SEQUENCE OF 1114 (level 2) */
   pvalue->supportedCodecs.codecs.n = 1;
   /* Start SEQUENCE or SET 1115 (level 3) */

   /* Populate the Integer type */
   pvalue->supportedCodecs.codecs.elem[0].sysID = 245;

   /* Populate OCTET STRING variable */
   {
      static const OSOCTET testdata[] = {
      0x98 };
      pvalue->supportedCodecs.codecs.elem[0].codecBitmap.numocts = 1;
      OSCRTLMEMCPY ((void*)pvalue->supportedCodecs.codecs.elem[0].codecBitmap.data, testdata, 1);
   }
   /* End SEQUENCE or SET 1115 */

   /* End SEQUENCE OF 1114 */
   /* End SEQUENCE or SET 1113 */

   pvalue->m.addnUpdateTypePresent = 1;
   /* Start SEQUENCE or SET 1116 (level 1) */

   pvalue->addnUpdateType.pnb_CIoT = 
      TS24301IE_AddnUpdateType_pnb_CIoT_noAddInfo;

   /* Populate the Boolean type */
   pvalue->addnUpdateType.saf = 1;

   /* Populate the Boolean type */
   pvalue->addnUpdateType.autv = 1;

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
