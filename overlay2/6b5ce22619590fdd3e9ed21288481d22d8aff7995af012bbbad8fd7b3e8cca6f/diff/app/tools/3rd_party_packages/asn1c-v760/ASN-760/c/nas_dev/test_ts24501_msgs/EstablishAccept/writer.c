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
   TS24501Msg_EstablishAccept data;
   TS24501Msg_EstablishAccept* pvalue = &data;
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
#if 1
   pdu.m.secHdrPresent = 0;
#else
   pdu.m.secHdrPresent = 1;
   pdu.secHdr.protoDiscr = TS24501Msg_NAS5GProtoDiscr_mobMgmt5G;
   pdu.secHdr.secHdrType = TS24501Msg_NAS5GSecHdrType_integProt;
   pdu.secHdr.msgAuthCode = 7000;
   pdu.secHdr.seqNumber  = 140;
#endif
   pdu.protoDiscr = TS24501Msg_NAS5GProtoDiscr_sessMgmt5G;
   pdu.hdrData.u.sm.pduSessIdent = TS24501Msg_PDUSessionIdentity_pduId8;
   pdu.hdrData.u.sm.procTransIdent = 3;

   asn1SetTC_TS24501Msg_PDU_obj_EstablishAccept5G (&ctxt, &pdu, pvalue);

   asn1Init_TS24501Msg_EstablishAccept (pvalue);

   pvalue->pduSessionType.sessionType = TS24501IE_SessionType_st_ipv4v6;
   pvalue->sscMode.sscMode = TS24501IE_SSCModeValue_ssc_mode3;

   pvalue->qosRules.length = 0; // Calculated automatically...
   pvalue->qosRules.rules.n = 2;
   pvalue->qosRules.rules.elem = rtxMemAllocArrayZ(&ctxt, 2,
                                                   TS24501IE_QoSRule);

   pvalue->qosRules.rules.elem[0].ruleId = 6;
   pvalue->qosRules.rules.elem[0].ruleLen = 4;
   pvalue->qosRules.rules.elem[0].ruleOpCode = TS24501IE_RuleOpCodes_modifyAndDelete;
   pvalue->qosRules.rules.elem[0].numPacketFilters = 1;
   pvalue->qosRules.rules.elem[0].packetFilterList.u.modifyAndDelete.n = 1;
   pvalue->qosRules.rules.elem[0].packetFilterList.u.modifyAndDelete.elem[0].filterId = 3;
   pvalue->qosRules.rules.elem[0].precedence = 8;
   pvalue->qosRules.rules.elem[0].flowId = 12;

   pvalue->qosRules.rules.elem[1].ruleId = 1;
   pvalue->qosRules.rules.elem[1].ruleLen = 15;
   pvalue->qosRules.rules.elem[1].ruleOpCode = TS24501IE_RuleOpCodes_createNew;
   pvalue->qosRules.rules.elem[1].dqr = 1;
   pvalue->qosRules.rules.elem[1].numPacketFilters = 1;
   pvalue->qosRules.rules.elem[1].packetFilterList.u.createNew.n = 1;
   pvalue->qosRules.rules.elem[1].packetFilterList.u.createNew.elem[0].filterDirection = 2;
   pvalue->qosRules.rules.elem[1].packetFilterList.u.createNew.elem[0].filterId = 1;
   pvalue->qosRules.rules.elem[1].packetFilterList.u.createNew.elem[0].filterContentLen = 0; // Calculated automatically...
   pvalue->qosRules.rules.elem[1].packetFilterList.u.createNew.elem[0].filterContent.n = 2;
   pvalue->qosRules.rules.elem[1].packetFilterList.u.createNew.elem[0].filterContent.elem =
                          rtxMemAllocArrayZ(&ctxt, 2, TS24501IE_PFComponent);
   pvalue->qosRules.rules.elem[1].packetFilterList.u.createNew.elem[0].filterContent.elem[0].typeId = 1;
   pvalue->qosRules.rules.elem[1].packetFilterList.u.createNew.elem[0].filterContent.elem[1].typeId = 16;
   {
      static const OSOCTET testdata[] = { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 };
      OSCRTLSAFEMEMCPY(
        (void *)pvalue->qosRules.rules.elem[1].packetFilterList.u.createNew.elem[0].filterContent.elem[1].value.u.ipv4Remote,
        8, testdata, 8);
   }
   pvalue->qosRules.rules.elem[1].precedence = 254;
   pvalue->qosRules.rules.elem[1].flowId = 13;

   pvalue->sessionAMBR.unitAmbrDL = 5;
   pvalue->sessionAMBR.sessionAmbrDL = 220;
   pvalue->sessionAMBR.unitAmbrUL = 10;
   pvalue->sessionAMBR.sessionAmbrUL = 75;

   pvalue->m.causePresent = 1;
   pvalue->cause = 38;

   pvalue->m.pduAddressPresent = 1;
   pvalue->pduAddress.length = 0;   /* supplied by encoder */
   pvalue->pduAddress.s16LLA = TRUE;
   pvalue->pduAddress.sessionType = TS24501IE_PDUAddressValues_ipv6;
   {
      static const OSOCTET testdata[] = { 0xf1, 0xb3, 0xc2, 0xa8, 0xab, 0xcd, 0xef, 0x00 };
      OSCRTLSAFEMEMCPY((void *)pvalue->pduAddress.addressInfo.u.addressInfoIpv6, 8,
                       testdata, 8);
   }
   {
      static const OSOCTET testdata[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
      OSCRTLSAFEMEMCPY((void *)pvalue->pduAddress.smfIp6Addr.u.present, 8,
                       testdata, 8);
   }

   pvalue->m.alwaysOnPDUSessionPresent = 1;
   pvalue->alwaysOnPDUSession.apsi = 1;

   pvalue->m.qosFlowDesrPresent = 1;
   pvalue->qosFlowDesr.length = 0; // Calculated automatically...
   pvalue->qosFlowDesr.qosFlowDesr.n = 1;
   pvalue->qosFlowDesr.qosFlowDesr.elem = rtxMemAllocArrayZ(&ctxt, 1,
                                                TS24501IE_QOSFlowDescription);
   pvalue->qosFlowDesr.qosFlowDesr.elem[0].qfi = 20;
   pvalue->qosFlowDesr.qosFlowDesr.elem[0].opCode = TS24501IE_FlowOpCodes_flowModify;
   pvalue->qosFlowDesr.qosFlowDesr.elem[0].eBit = TRUE;
   pvalue->qosFlowDesr.qosFlowDesr.elem[0].numParams = 2;
   pvalue->qosFlowDesr.qosFlowDesr.elem[0].m.paramsListPresent = 1;
   pvalue->qosFlowDesr.qosFlowDesr.elem[0].paramsList.n = 2;
   pvalue->qosFlowDesr.qosFlowDesr.elem[0].paramsList.elem[0].id = TS24501IE_ParameterId_fiveQI;
   pvalue->qosFlowDesr.qosFlowDesr.elem[0].paramsList.elem[0].content.u.fiveQI = 7;
   pvalue->qosFlowDesr.qosFlowDesr.elem[0].paramsList.elem[1].id = TS24501IE_ParameterId_epsBearerIdent;
   pvalue->qosFlowDesr.qosFlowDesr.elem[0].paramsList.elem[1].content.u.epsBearerIdent.value = 6;
   pvalue->qosFlowDesr.qosFlowDesr.elem[0].paramsList.elem[1].content.u.epsBearerIdent.spare = 0;

   pvalue->m.extProtoCfgOptsPresent = 1;
   pvalue->extProtoCfgOpts.octet4.configProtocol = 0;

   pvalue->m._v16ExtPresent = 1;

   pvalue->m.smNetFeatureSupportPresent = 1;
   pvalue->smNetFeatureSupport.eptS1 = TRUE;

   pvalue->m.servingPLMNRateCtrlPresent = 1;
   pvalue->servingPLMNRateCtrl.data[0] = 0x1f;
   pvalue->servingPLMNRateCtrl.data[1] = 0x2e;

   pvalue->m.atsssContainerPresent = 1;
   pvalue->atsssContainer.m.contentsPresent = 1;
   pvalue->atsssContainer.contents.numocts = 4;
   pvalue->atsssContainer.contents.data = (OSOCTET *)rtxMemAlloc(&ctxt, 4);
   {
      static const OSOCTET testdata[] = { 0xf0, 0xe1, 0xb4, 0xa5 };
      OSCRTLSAFEMEMCPY((void *)pvalue->atsssContainer.contents.data, 4,
                       testdata, 4);
   }

   pvalue->m.ctrlPlaneOnlyIndicationPresent = 1;
   pvalue->ctrlPlaneOnlyIndication.cpoi = TRUE;

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
