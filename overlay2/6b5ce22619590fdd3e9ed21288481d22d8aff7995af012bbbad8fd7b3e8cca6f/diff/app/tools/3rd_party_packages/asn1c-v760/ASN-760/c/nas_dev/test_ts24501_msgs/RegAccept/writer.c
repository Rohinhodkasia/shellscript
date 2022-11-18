#include "TS24501Msgs.h"
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
   TS24501Msg_PDU pdu;
   TS24501Msg_RegAccept data;
   TS24501Msg_RegAccept* pvalue = &data;
   OSCTXT	ctxt;
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

   asn1Init_TS24501Msg_PDU (&pdu);
   pdu.m.secHdrPresent = 1;
   pdu.secHdr.protoDiscr = TS24501Msg_NAS5GProtoDiscr_mobMgmt5G;
   pdu.secHdr.secHdrType = TS24501Msg_NAS5GSecHdrType_integProtAnd5GSecCtxt;
   pdu.secHdr.msgAuthCode = 30000;
   pdu.secHdr.seqNumber = 60;
   pdu.hdrData.u.mm.secHdrType = TS24501Msg_NAS5GSecHdrType_noSec;

   asn1SetTC_TS24501Msg_PDU_obj_RegAccept5G (&ctxt, &pdu, pvalue);

   asn1Init_TS24501Msg_RegAccept (pvalue);

   pvalue->regResult.emergencyRegistered = 0;
   pvalue->regResult.nssaa = 0;
   pvalue->regResult.smsAllowed = 1;
   pvalue->regResult.regResult = TS24501IE_RegistrationResultValue_accessAndNonAccess;

   pvalue->m.gutiPresent = 1;
   pvalue->guti.t = T_TS24501IE_MobileIdentity_guti;
   rtxStrncpy (pvalue->guti.u.guti.mcc_mnc.mcc, 4, "294", 3);
   rtxStrncpy (pvalue->guti.u.guti.mcc_mnc.mnc, 4, "01", 3);
   pvalue->guti.u.guti.amfRegionID = 23;
   pvalue->guti.u.guti.amfSetID = 4;
   pvalue->guti.u.guti.amfPointer = 10;
   {
      static const OSOCTET testdata[] = { 
      0x11, 0x79, 0x71, 0x86 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->guti.u.guti.tmsi, 4, testdata, 4);
   }

   pvalue->m.plmnListPresent = 1;
   pvalue->plmnList.n = 1;
   rtxStrncpy (pvalue->plmnList.elem[0].mcc, 4, "286", 3);
   rtxStrncpy (pvalue->plmnList.elem[0].mnc, 4, "03", 3);

   pvalue->m.taiListPresent = 1;
   pvalue->taiList.length = 0; /* length will be calculated */
   pvalue->taiList.idents.n = 2;

   pvalue->taiList.idents.elem[0].typeOfList = 1;
   pvalue->taiList.idents.elem[0].numElements = 0; // = 1 element
   rtxStrncpy(
      pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList1.mcc_mnc.mcc,
      4, "310", 3);
   rtxStrncpy(
      pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList1.mcc_mnc.mnc,
      4, "26", 3);
   {
      static const OSOCTET testdata[] = { 0x84, 0x68, 0x83 };
      OSCRTLSAFEMEMCPY(
        (void *)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList1.tac.data,
        3, testdata, 3);
   }

   pvalue->taiList.idents.elem[1].typeOfList = 2;
   pvalue->taiList.idents.elem[1].numElements = 2;
   pvalue->taiList.idents.elem[1].elements.u.partTrkIdentList2.n = 3;
   rtxStrncpy(
      pvalue->taiList.idents.elem[1].elements.u.partTrkIdentList2.elem[0].mcc_mnc.mcc,
      4, "123", 3);
   rtxStrncpy(
      pvalue->taiList.idents.elem[1].elements.u.partTrkIdentList2.elem[0].mcc_mnc.mnc,
      4, "21", 3);
   {
      static const OSOCTET testdata[] = { 0x01, 0x23, 0x45 };
      OSCRTLSAFEMEMCPY(
        (void *)pvalue->taiList.idents.elem[1].elements.u.partTrkIdentList2.elem[0].tac.data,
        3, testdata, 3);
   }
   rtxStrncpy(
      pvalue->taiList.idents.elem[1].elements.u.partTrkIdentList2.elem[1].mcc_mnc.mcc,
      4, "456", 3);
   rtxStrncpy(
      pvalue->taiList.idents.elem[1].elements.u.partTrkIdentList2.elem[1].mcc_mnc.mnc,
      4, "22", 3);
   {
      static const OSOCTET testdata[] = { 0x67, 0x89, 0xab };
      OSCRTLSAFEMEMCPY(
        (void *)pvalue->taiList.idents.elem[1].elements.u.partTrkIdentList2.elem[1].tac.data,
        3, testdata, 3);
   }
   rtxStrncpy(
      pvalue->taiList.idents.elem[1].elements.u.partTrkIdentList2.elem[2].mcc_mnc.mcc,
      4, "789", 3);
   rtxStrncpy(
      pvalue->taiList.idents.elem[1].elements.u.partTrkIdentList2.elem[2].mcc_mnc.mnc,
      4, "33", 3);
   {
      static const OSOCTET testdata[] = { 0xcd, 0xef, 0x00 };
      OSCRTLSAFEMEMCPY(
        (void *)pvalue->taiList.idents.elem[1].elements.u.partTrkIdentList2.elem[2].tac.data,
        3, testdata, 3);
   }

   pvalue->m.allowedNSSAIPresent = 1;
   pvalue->allowedNSSAI.length = 0; /* length will be calculated */
   pvalue->allowedNSSAI.contents.n = 1;
   pvalue->allowedNSSAI.contents.elem[0].length = 0; /* length will be calculated */
   pvalue->allowedNSSAI.contents.elem[0].sst = 41;
   pvalue->allowedNSSAI.contents.elem[0].m.sdPresent = TRUE;
   pvalue->allowedNSSAI.contents.elem[0].sd = 1639727;
   pvalue->allowedNSSAI.contents.elem[0].m.mappedSSTPresent = TRUE;
   {
      static const OSOCTET testdata[] = { 
      0x65 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->allowedNSSAI.contents.elem[0].mappedSST, 1, testdata, 1);
   }
   pvalue->allowedNSSAI.contents.elem[0].m.mappedSDPresent = TRUE;
   {
      static const OSOCTET testdata[] = { 
      0x8d, 0x0b, 0x76 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->allowedNSSAI.contents.elem[0].mappedSD, 3, testdata, 3);
   }

   pvalue->m.netSupportPresent = 1;
   pvalue->netSupport.length = 0; /* length will be calculated */
   pvalue->netSupport.mpsInd = 1;
   pvalue->netSupport.interNetworkWithoutN26Ind = 1;
   pvalue->netSupport.emfInd = 2;
   pvalue->netSupport.emcInd = 1;
   pvalue->netSupport.imsVoPSN3GPPInd = 1;
   pvalue->netSupport.imsVoPS3GPPInd = 0;
   pvalue->netSupport.m.octet4Present = 1;
   pvalue->netSupport.octet4.upCIoT = 0;
   pvalue->netSupport.octet4.hcCpCIoT = 0;
   pvalue->netSupport.octet4.n3Data = 1;
   pvalue->netSupport.octet4.cpCIoT = 1;
   pvalue->netSupport.octet4.restrictedEC = 1;
   pvalue->netSupport.octet4.mcsi = 0;
   pvalue->netSupport.octet4.emcn3 = 0;
   pvalue->netSupport.m.octet5Present = 1;
   pvalue->netSupport.octet5.pr = 1;
   pvalue->netSupport.octet5.rpr = 0;
   pvalue->netSupport.octet5.piv = 0;
   pvalue->netSupport.octet5.ncr = 1;
   pvalue->netSupport.octet5.ehcCpCIoT = 1;
   pvalue->netSupport.octet5.atsInd = 0;
   pvalue->netSupport.octet5.lcs = 1;

   pvalue->m.sessionStatPresent = 1;
   pvalue->sessionStat.length = 0; /* length will be calculated */
   OSCRTLMEMSET(pvalue->sessionStat.psi.elem, 0,
                sizeof(pvalue->sessionStat.psi.elem));
   pvalue->sessionStat.psi.elem[0] = TRUE;
   pvalue->sessionStat.psi.elem[5] = TRUE;
   pvalue->sessionStat.psi.elem[10] = TRUE;

   pvalue->m.reactivateRsltCausePresent = 1;
   pvalue->reactivateRsltCause.length = 0; /* length will be calculated */
   pvalue->reactivateRsltCause.reactivateCause.n = 1;
   pvalue->reactivateRsltCause.reactivateCause.elem[0].sessionId = 30;
   pvalue->reactivateRsltCause.reactivateCause.elem[0].cause = 3;

   pvalue->m.micoIndPresent = 1;
   pvalue->micoInd.sprti = 1;
   pvalue->micoInd.raai = 0;

   pvalue->m.t3512Present = 1;
   pvalue->t3512.length = 0; /* length will be calculated */
   pvalue->t3512.unit = TS24008IE_GPRSTimer3_unit_valIncrMult10Mins;
   pvalue->t3512.timerValue = 12;

   pvalue->m.non3GPPDeregTimerPresent = 1;
   pvalue->non3GPPDeregTimer.length = 0; /* length will be calculated */
   pvalue->non3GPPDeregTimer.value.unit = 2;
   pvalue->non3GPPDeregTimer.value.timerValue = 24;

   pvalue->m.emergencyNumListPresent = 1;
   pvalue->emergencyNumList.length = 0; /* length will be calculated */
   pvalue->emergencyNumList.numbers.n = 1;
   pvalue->emergencyNumList.numbers.elem[0].length = 0; /* length will be calculated */
   pvalue->emergencyNumList.numbers.elem[0].spare = 0;
   pvalue->emergencyNumList.numbers.elem[0].catValue = 10;
   pvalue->emergencyNumList.numbers.elem[0].digits = "ca7201";

   pvalue->m.eapMessagePresent = 1;
   pvalue->eapMessage.length = 0; // Calculated automatically...
   pvalue->eapMessage.packetFormat.code = TS24501IE_EAPFormatCode_request;
   pvalue->eapMessage.packetFormat.id = 11;
   pvalue->eapMessage.packetFormat.length = 8;
   pvalue->eapMessage.packetFormat.data.numocts = 4;
   pvalue->eapMessage.packetFormat.data.data = (OSOCTET*) rtxMemAlloc(&ctxt, 4);
   {
      static const OSOCTET tmpdata[] = { 0xb6, 0xdd, 0xc4, 0x9c };
      OSCRTLSAFEMEMCPY((void*)pvalue->eapMessage.packetFormat.data.data, 4, tmpdata, 4);
   }

   pvalue->m._v16ExtPresent = 1;
   pvalue->m.ueRadioCapIdDeletionIndicationPresent = 1;
   pvalue->ueRadioCapIdDeletionIndication.deletionReq = 1;

   pvalue->m.cipherKeyDataPresent = TRUE;
   asn1Init_TS24501IE_CipherDataSet(&pvalue->cipherKeyData.dataSet.elem[0]);
   pvalue->cipherKeyData.length = 0;  // Calculated automatically...
   pvalue->cipherKeyData.dataSet.n = 1;
   pvalue->cipherKeyData.dataSet.elem[0].cipherKey[0] = 0x01;
   pvalue->cipherKeyData.dataSet.elem[0].c0Len = 2;
   pvalue->cipherKeyData.dataSet.elem[0].c0.data = (OSOCTET*) rtxMemAlloc(&ctxt, 2);
   pvalue->cipherKeyData.dataSet.elem[0].c0.numocts = 2;
   {
      static const OSOCTET tmpdata[] = { 0x01, 0x76 };
      OSCRTLSAFEMEMCPY((void*)pvalue->cipherKeyData.dataSet.elem[0].c0.data, 2, tmpdata, 2);
   }
   pvalue->cipherKeyData.dataSet.elem[0].eutraPosSIBLen = 4;
   memset(pvalue->cipherKeyData.dataSet.elem[0].eutraPosSIBType.elem, 0,
          sizeof(pvalue->cipherKeyData.dataSet.elem[0].eutraPosSIBType.elem));
   pvalue->cipherKeyData.dataSet.elem[0].eutraPosSIBType.elem[0] = TRUE;
   pvalue->cipherKeyData.dataSet.elem[0].eutraPosSIBType.elem[5] = TRUE;
   pvalue->cipherKeyData.dataSet.elem[0].eutraPosSIBType.elem[10] = TRUE;
   pvalue->cipherKeyData.dataSet.elem[0].nrPosSIBLen = 5;
   memset(pvalue->cipherKeyData.dataSet.elem[0].nrPosSIBType.elem, 0,
          sizeof(pvalue->cipherKeyData.dataSet.elem[0].nrPosSIBType.elem));
   pvalue->cipherKeyData.dataSet.elem[0].nrPosSIBType.elem[15] = TRUE;
   pvalue->cipherKeyData.dataSet.elem[0].nrPosSIBType.elem[20] = TRUE;
   pvalue->cipherKeyData.dataSet.elem[0].nrPosSIBType.elem[25] = TRUE;
   pvalue->cipherKeyData.dataSet.elem[0].validityStartTime.year = 20;
   pvalue->cipherKeyData.dataSet.elem[0].validityStartTime.month = 4;
   pvalue->cipherKeyData.dataSet.elem[0].validityStartTime.day = 1;
   pvalue->cipherKeyData.dataSet.elem[0].validityStartTime.hour = 3;
   pvalue->cipherKeyData.dataSet.elem[0].validityStartTime.minute = 30;
   pvalue->cipherKeyData.dataSet.elem[0].validityDuration = 500;
   pvalue->cipherKeyData.dataSet.elem[0].taiList.length = 0;  // Calculated automatically...
   pvalue->cipherKeyData.dataSet.elem[0].taiList.idents.n = 1;
   pvalue->cipherKeyData.dataSet.elem[0].taiList.idents.elem[0].typeOfList = 1;
   rtxStrncpy(
      pvalue->cipherKeyData.dataSet.elem[0].taiList.idents.elem[0].elements.u.partTrkIdentList1.mcc_mnc.mcc,
      4, "640", 3);
   rtxStrncpy(
      pvalue->cipherKeyData.dataSet.elem[0].taiList.idents.elem[0].elements.u.partTrkIdentList1.mcc_mnc.mnc,
      4, "05", 3);
   {
      static const OSOCTET testdata[] = {  0x69, 0xe2, 0x7e };
      OSCRTLSAFEMEMCPY(
        (void *)pvalue->cipherKeyData.dataSet.elem[0].taiList.idents.elem[0].elements.u.partTrkIdentList1.tac.data,
        3, testdata, 3);
   }

   pvalue->m.cagInfoListPresent = TRUE;
   pvalue->cagInfoList.m.entriesPresent = TRUE;
   pvalue->cagInfoList.entries.n = 1;
   pvalue->cagInfoList.entries.elem = rtxMemAllocArrayZ(&ctxt, 1, TS24501IE_CAGEntry);
   pvalue->cagInfoList.entries.elem[0].length = 4;
   rtxStrncpy(pvalue->cagInfoList.entries.elem[0].mcc_mnc.mcc, 4, "410", 3);
   rtxStrncpy(pvalue->cagInfoList.entries.elem[0].mcc_mnc.mnc, 4, "01", 3);
   pvalue->cagInfoList.entries.elem[0].cagOnly = TRUE;

   pvalue->m.truncatedConfigPresent = TRUE;
   pvalue->truncatedConfig.truncatedAMFId = 5;
   pvalue->truncatedConfig.truncatedAMFPtr = 15;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24501Msg_PDU (&ctxt, &pdu);
   if (0 != ret) {
      printf ("encode PDU failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "");
      printf ("\n");
      rtxFreeContext (&ctxt);
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
