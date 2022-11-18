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
   TS24501Msg_ULNASTrans data;
   TS24501Msg_ULNASTrans* pvalue = &data;
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
   pdu.secHdr.secHdrType =
              TS24501Msg_NAS5GSecHdrType_integProtAnd5GSecCtxt;
   pdu.secHdr.msgAuthCode = 3600;
   pdu.secHdr.seqNumber  = 30;
   pdu.hdrData.u.mm.secHdrType = TS24501Msg_NAS5GSecHdrType_noSec;

   asn1SetTC_TS24501Msg_PDU_obj_ULNASTrans5G (&ctxt, &pdu, pvalue);

   asn1Init_TS24501Msg_ULNASTrans (pvalue);

   pvalue->containerType = TS24501IE_PayloadContainerType_n1SmInfo;

   TS24501Msg_PDU_SM pdu_SM;
   TS24501Msg_ModifyReject data_SM;
   TS24501Msg_ModifyReject* pvalue_SM = &data_SM;

   pdu_SM.protoDiscr = TS24501Msg_NAS5GProtoDiscr_sessMgmt5G;
   pdu_SM.pduSessIdent = TS24501Msg_PDUSessionIdentity_pduId10;
   pdu_SM.procTransIdent = 5;
   asn1SetTC_TS24501Msg_PDU_SM_obj_ModifyReject5G(&ctxt, &pdu_SM, pvalue_SM);
   OSCRTLMEMSET(&data_SM, 0, sizeof(TS24501Msg_ModifyReject));

   pvalue->container.u.n1sm.length = 0; /* length will be calculated */
   pvalue_SM->cause = 111;
   pvalue_SM->m.backoffTimerPresent = 1;
   pvalue_SM->backoffTimer.unit = TS24008IE_GPRSTimer3_unit_valIncrMult320Hrs;
   pvalue_SM->backoffTimer.timerValue = 18;
   pvalue_SM->m._v16ExtPresent = TRUE;
   pvalue_SM->m.reattemptIndPresent = TRUE;
   pvalue_SM->reattemptInd.eplmnc = FALSE;
   pvalue_SM->reattemptInd.ratc = TRUE;
   pvalue->container.u.n1sm.pduSm = pdu_SM;

   pvalue->m.pduSessionIdPresent = 1;
   pvalue->pduSessionId = 57;

   pvalue->m.oldPduSessionIdPresent = 1;
   pvalue->oldPduSessionId = 38;

   pvalue->m.requestTypePresent = 1;
   pvalue->requestType.reqType = TS24501IE_RequestTypes_emerPduSession;

   pvalue->m.snssaiPresent = 1;
   pvalue->snssai.length = 0; // Calculated automatically...
   pvalue->snssai.sst = 120;
   pvalue->snssai.m.sdPresent = TRUE;
   pvalue->snssai.sd = 13021780;
   pvalue->snssai.m.mappedSSTPresent = TRUE;
   {
      static const OSOCTET testdata[] = { 
      0xeb };
      OSCRTLSAFEMEMCPY ((void*)pvalue->snssai.mappedSST, 1, testdata, 1);
   }
   pvalue->snssai.m.mappedSDPresent = TRUE;
   {
      static const OSOCTET testdata[] = { 
      0xf1, 0xb3, 0xc2 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->snssai.mappedSD, 3, testdata, 3);
   }

   pvalue->m.dnnPresent = 1;
   pvalue->dnn.apn.elem = rtxMemAllocArray(&ctxt, 3, const char*);
   pvalue->dnn.apn.n = 3;
   pvalue->dnn.apn.elem[0] = "ZERO";
   pvalue->dnn.apn.elem[1] = "ONE";
   pvalue->dnn.apn.elem[2] = "TWO";

   pvalue->m.addlInfoPresent = 1;
   pvalue->addlInfo.numocts = 1;
   pvalue->addlInfo.data = (OSOCTET*) rtxMemAlloc(&ctxt, 1);
   {
      static const OSOCTET testdata[] = { 0xd8 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->addlInfo.data, 1, testdata, 1);
   }

   pvalue->m._v16ExtPresent = TRUE;
   pvalue->m.maPduSessionInfoPresent = TRUE;
   pvalue->maPduSessionInfo = TS24501IE_MAPDUSessionInfo_networkUpgAllowed;

   pvalue->m.relAssistIndPresent = TRUE;
   pvalue->relAssistInd.ddx = TS24301IE_ReleaseAssistInd_ddx_ddxSingleDLTrans;

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
