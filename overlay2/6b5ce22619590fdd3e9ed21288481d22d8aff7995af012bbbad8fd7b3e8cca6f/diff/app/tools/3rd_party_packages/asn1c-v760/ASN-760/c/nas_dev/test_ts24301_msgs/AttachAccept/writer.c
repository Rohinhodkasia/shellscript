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
   TS24301Msg_AttachAccept data;
   TS24301Msg_AttachAccept* pvalue = &data;
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

   asn1Init_TS24301Msg_PDU (&pdu);
   pdu.m.secHdrPresent = 1;
   pdu.secHdr.secHdrType = TS24007L3_SecHdrType_integProt;
   pdu.secHdr.protoDiscr = TS24007L3_ProtoDiscr_epsMobMgmt;
   pdu.secHdr.msgAuthCode = 12345678;
   pdu.secHdr.seqNumber  = 1;
   pdu.l3HdrOpts.t = T_TS24007L3_L3HdrOptions_secHdr;
   pdu.l3HdrOpts.u.secHdr = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_epsMobMgmt;
   asn1SetTC_TS24301Msg_PDU_obj_AttachAccept (&ctxt, &pdu, pvalue);

   asn1Init_TS24301Msg_AttachAccept (pvalue);

   pvalue->spare = 8;
   pvalue->result.spare = 0;
   pvalue->result.result = TS24301IE_EPSAttachResultValues_combinedAttach;
   pvalue->t3412Value.unit = 2;
   pvalue->t3412Value.timerValue = 24;
   pvalue->taiList.length = 94;
   pvalue->taiList.idents.n = 1;
   pvalue->taiList.idents.elem[0].spare = 0;
   pvalue->taiList.idents.elem[0].typeOfList = 0;
   pvalue->taiList.idents.elem[0].numElements = 0; /* +1 */

   rtxStrncpy(pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.mcc_mnc.mcc,
              sizeof(pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.mcc_mnc.mcc),
			  "454", 4);

   rtxStrncpy(pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.mcc_mnc.mnc,
              sizeof(pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.mcc_mnc.mnc),
			  "07", 4);

   pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.n = 1;
   {
      static const OSOCTET testdata[] = { 0x41, 0x49 };
      OSCRTLMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.
                    u.partTrkIdentList0.tacs.elem[0].data, testdata, 2);
   }

   TS24301Msg_PDU_SM pdu_SM;
   TS24301Msg_ActvDfltEPSBearerCtxtReq data_SM;
   TS24301Msg_ActvDfltEPSBearerCtxtReq* pvalue_SM = &data_SM;
   const char *pName = "uad5gn.au-net.ne.jp.mnc051.mcc440.gprs";

   pdu_SM.l3HdrOpts.t = T_TS24007L3_L3HdrOptions_epsBearerIdent;
   pdu_SM.l3HdrOpts.u.epsBearerIdent = TS24007L3_EPSBearerIdentity_id5;
   pdu_SM.protoDiscr = TS24007L3_ProtoDiscr_epsSessMgmt;
   pdu_SM.pti.u.value = 0;
   asn1SetTC_TS24301Msg_PDU_SM_obj_ActvDfltEPSBearerCtxtReq(&ctxt, &pdu_SM, pvalue_SM);
   OSCRTLMEMSET(&data_SM, 0, sizeof(TS24301Msg_ActvDfltEPSBearerCtxtReq));

   pvalue->esmMessageContainer.length = 0; /* length will be calculated */
   pvalue_SM->epsQoS.length = 0; /* length will be calculated */
   pvalue_SM->epsQoS.qci = 9;
   rtxStrncpy(pvalue_SM->accessPointName, sizeof(pvalue_SM->accessPointName),
              pName, strlen(pName));
   pvalue_SM->pdnAddress.length = 0; /* length will be calculated */
   pvalue_SM->pdnAddress.pdnTypeValue = TS24301IE_PDNTypeValue_ipv4v6;
   {
      static const OSOCTET testdata[] = {
      0x00, 0x00, 0x00, 0x08, 0x0d, 0x49, 0x97, 0x01, 0x0a, 0xb1, 0x20, 0x70 };
      pvalue_SM->pdnAddress.pdnAddrInfo.numocts = 12;
      OSCRTLMEMCPY((void *)pvalue_SM->pdnAddress.pdnAddrInfo.data,
                   testdata, 12);
   }
   pvalue_SM->m.apn_AMBRPresent = 1;
   pvalue_SM->apn_AMBR.length = 0; /* length will be calculated */
   pvalue_SM->apn_AMBR.apnAmbrforDL = 254;
   pvalue_SM->apn_AMBR.apnAmbrforUL = 254;
   pvalue->esmMessageContainer.pduSm = pdu_SM;

   pvalue->m.gutiPresent = 1;
   pvalue->guti.oddEvenInd = TRUE;
   pvalue->guti.typeOfIdent = TS24301IE_EPSMobileIdentity_typeOfIdent_guti;

   rtxStrncpy(pvalue->guti.content.u.guti.mcc_mnc.mcc,
              sizeof(pvalue->guti.content.u.guti.mcc_mnc.mcc), "454", 4);
   rtxStrncpy(pvalue->guti.content.u.guti.mcc_mnc.mnc,
              sizeof(pvalue->guti.content.u.guti.mcc_mnc.mnc), "07", 4);
   {
      static const OSOCTET testdata[] = {
      0x1b, 0x38 };
      OSCRTLMEMCPY ((void*)pvalue->guti.content.u.guti.mmeGroupID, testdata, 2);
   }

   pvalue->guti.content.u.guti.mmeCode = 251;
   {
      static const OSOCTET testdata[] = {
      0xd9, 0x1f, 0xe5, 0xf8 };
      OSCRTLMEMCPY ((void*)pvalue->guti.content.u.guti.tmsi, testdata, 4);
   }

   pvalue->m.locAreaIdentPresent = 1;
   rtxStrncpy(pvalue->locAreaIdent.mcc_mnc.mcc,
              sizeof(pvalue->locAreaIdent.mcc_mnc.mcc), "454", 4);
   rtxStrncpy(pvalue->locAreaIdent.mcc_mnc.mnc,
              sizeof(pvalue->locAreaIdent.mcc_mnc.mnc), "07", 4);
   pvalue->locAreaIdent.lac = 23163;

   pvalue->m.msIdentityPresent = 1;
   pvalue->msIdentity.t =  2;
   rtxStrncpy(pvalue->msIdentity.u.imei,
              sizeof(pvalue->msIdentity.u.imei), "050b8*23870*6c2", 16);

   pvalue->m.emmCausePresent = 1;
   pvalue->emmCause = TS24301IE_EMMCause_imsiUnkInHSS;

   pvalue->m.t3402Present = 1;
   pvalue->t3402.unit = 6;
   pvalue->t3402.timerValue = 26;

   pvalue->m.t3423Present = 1;
   pvalue->t3423.unit = 0;
   pvalue->t3423.timerValue = 3;

   pvalue->m.equivPLMNsPresent = 1;
   pvalue->equivPLMNs.n = 1;
   rtxStrncpy(pvalue->equivPLMNs.elem[0].mcc,
              sizeof(pvalue->equivPLMNs.elem[0].mcc), "405", 4);
   rtxStrncpy(pvalue->equivPLMNs.elem[0].mnc,
              sizeof(pvalue->equivPLMNs.elem[0].mnc), "025", 4);

   pvalue->m.emergNumListPresent = 1;
   pvalue->emergNumList.length = 0; /* will be calculated */
   pvalue->emergNumList.numbers.n = 1;
   pvalue->emergNumList.numbers.elem[0].length = 0;
   pvalue->emergNumList.numbers.elem[0].spare = 0;
   pvalue->emergNumList.numbers.elem[0].catValue = 10;
   pvalue->emergNumList.numbers.elem[0].digits = "5c";

   pvalue->m.epsNetFeatSuppPresent = 1;
   pvalue->epsNetFeatSupp.length = 1;
   pvalue->epsNetFeatSupp.cpCIoT = 0;
   pvalue->epsNetFeatSupp.erNoPDN = 1;
   pvalue->epsNetFeatSupp.esr = 0;
   pvalue->epsNetFeatSupp.csLCS = 2;
   pvalue->epsNetFeatSupp.epcLCS = 0;
   pvalue->epsNetFeatSupp.emcBS = 0;
   pvalue->epsNetFeatSupp.imsVoPS = 1;

   pvalue->m.addnUpdateResultPresent = 1;
   pvalue->addnUpdateResult.spare = 0;
   pvalue->addnUpdateResult.value = TS24301IE_AddnUpdateResult_value_noInfo;

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
