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
   TS24501Msg_RegRequest data;
   TS24501Msg_RegRequest* pvalue = &data;
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
   pdu.secHdr.secHdrType = TS24501Msg_NAS5GSecHdrType_integProtAnd5GSecCtxt;
   pdu.secHdr.msgAuthCode = 4000;
   pdu.secHdr.seqNumber = 30;
   pdu.hdrData.u.mm.secHdrType = TS24501Msg_NAS5GSecHdrType_noSec;
#endif

   asn1SetTC_TS24501Msg_PDU_obj_RegRequest5G (&ctxt, &pdu, pvalue);

   asn1Init_TS24501Msg_RegRequest (pvalue);

   pvalue->registrationType.forBit = 1;
   pvalue->registrationType.regisType = TS24501IE_RegistrationTypeValue_emergency;

   pvalue->nasKeySetIdent.tsc = 0;
   pvalue->nasKeySetIdent.ident = 2;

   pvalue->mobileId.t = T_TS24501IE_MobileIdentity_none;

   pvalue->m.capabilityPresent = 1;
   OSCRTLMEMSET(&pvalue->capability, 0,
                sizeof(TS24501IE_MMCapability));
   pvalue->capability.length = 0; /* length will be calculated */
   pvalue->capability.sgc = 1;
   pvalue->capability.cpCIoT = 0;
   pvalue->capability.restrictedEC = 0;
   pvalue->capability.handoverSupported = 1;
   pvalue->capability.s1Supported = 1;
   pvalue->capability.m.octet4Present = 1;
   pvalue->capability.octet4.v2xcnpc5 = 1;
   pvalue->capability.octet4.v2xcepc5 = 1;
   pvalue->capability.m.octet5Present = 1;
   pvalue->capability.octet5.proSel2relay = 1;
   pvalue->capability.octet5.proSedd = 1;
   pvalue->capability.octet5.cag = 1;
   pvalue->capability.m.octet6Present = 1;
   pvalue->capability.octet6.proSel3rmt = 1;
   pvalue->capability.octet6.proSel3relay = 1;
   pvalue->capability.m.sparePresent = 0;

   pvalue->m.securityCapabilityPresent = 1;
   OSCRTLMEMSET(&pvalue->securityCapability, 0,
                sizeof(TS24501IE_UESecurityCapability));
   pvalue->securityCapability.length = 0; /* length will be calculated */
   pvalue->securityCapability.ea0 = 1;
   pvalue->securityCapability.ea5 = 1;
   pvalue->securityCapability.ia1 = 1;
   pvalue->securityCapability.ia4 = 1;
   pvalue->securityCapability.ia7 = 1;
   pvalue->securityCapability.m.octet5Present = 1;
   pvalue->securityCapability.octet5.eea0 = 1;
   pvalue->securityCapability.octet5.eea6 = 1;

   pvalue->m.requestedNSSAIPresent = 1;
   pvalue->requestedNSSAI.length = 0; /* length will be calculated */
   pvalue->requestedNSSAI.contents.n = 1;
   pvalue->requestedNSSAI.contents.elem[0].length = 0; /* length will be calculated */
   pvalue->requestedNSSAI.contents.elem[0].sst = 170;
   pvalue->requestedNSSAI.contents.elem[0].m.sdPresent = TRUE;
   pvalue->requestedNSSAI.contents.elem[0].sd = 8746971;
   pvalue->requestedNSSAI.contents.elem[0].m.mappedSSTPresent = TRUE;
   {
      static const OSOCTET testdata[] = { 
      0xe1 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->requestedNSSAI.contents.elem[0].mappedSST, 1, testdata, 1);
   }
   pvalue->requestedNSSAI.contents.elem[0].m.mappedSDPresent = TRUE;
   {
      static const OSOCTET testdata[] = { 
      0x99, 0x9a, 0x4b };
      OSCRTLSAFEMEMCPY ((void*)pvalue->requestedNSSAI.contents.elem[0].mappedSD, 3, testdata, 3);
   }

   pvalue->m.lastVisitedTAIPresent = 1;
   rtxStrncpy (pvalue->lastVisitedTAI.mcc_mnc.mcc, 4, "410", 3);
   rtxStrncpy (pvalue->lastVisitedTAI.mcc_mnc.mnc, 4, "01", 3);
   {
      static const OSOCTET testdata[] = { 
      0xbe, 0x0a, 0x77 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->lastVisitedTAI.tac.data, 3, testdata, 3);
   }

   pvalue->m.s1NetworkCapabilityPresent = 1;
   pvalue->s1NetworkCapability.length = 0; /* length will be calculated */
   pvalue->s1NetworkCapability.epsEncryptAlgs.eea0 = 1;
   pvalue->s1NetworkCapability.epsEncryptAlgs.x128_eea1 = 0;
   pvalue->s1NetworkCapability.epsEncryptAlgs.x128_eea2 = 0;
   pvalue->s1NetworkCapability.epsEncryptAlgs.eea3 = 0;
   pvalue->s1NetworkCapability.epsEncryptAlgs.eea4 = 1;
   pvalue->s1NetworkCapability.epsEncryptAlgs.eea5 = 0;
   pvalue->s1NetworkCapability.epsEncryptAlgs.eea6 = 0;
   pvalue->s1NetworkCapability.epsEncryptAlgs.eea7 = 0;
   pvalue->s1NetworkCapability.epsIntegAlgs.eia0 = 1;
   pvalue->s1NetworkCapability.epsIntegAlgs.eia1 = 1;
   pvalue->s1NetworkCapability.epsIntegAlgs.eia2 = 0;
   pvalue->s1NetworkCapability.epsIntegAlgs.eia3 = 1;
   pvalue->s1NetworkCapability.epsIntegAlgs.eia4 = 0;
   pvalue->s1NetworkCapability.epsIntegAlgs.eia5 = 0;
   pvalue->s1NetworkCapability.epsIntegAlgs.eia6 = 0;
   pvalue->s1NetworkCapability.epsIntegAlgs.eia7 = 1;
   pvalue->s1NetworkCapability.m.umtsEncryptAlgsPresent = 1;
   pvalue->s1NetworkCapability.umtsEncryptAlgs.uea0 = 1;
   pvalue->s1NetworkCapability.umtsEncryptAlgs.uea1 = 0;
   pvalue->s1NetworkCapability.umtsEncryptAlgs.uea2 = 1;
   pvalue->s1NetworkCapability.umtsEncryptAlgs.uea3 = 0;
   pvalue->s1NetworkCapability.umtsEncryptAlgs.uea4 = 0;
   pvalue->s1NetworkCapability.umtsEncryptAlgs.uea5 = 0;
   pvalue->s1NetworkCapability.umtsEncryptAlgs.uea6 = 0;
   pvalue->s1NetworkCapability.umtsEncryptAlgs.uea7 = 0;
   pvalue->s1NetworkCapability.m.octet6Present = 1;
   pvalue->s1NetworkCapability.octet6.ucs2 = 1;
   pvalue->s1NetworkCapability.octet6.umtsIntegAlgs.uia1 = 0;
   pvalue->s1NetworkCapability.octet6.umtsIntegAlgs.uia2 = 1;
   pvalue->s1NetworkCapability.octet6.umtsIntegAlgs.uia3 = 1;
   pvalue->s1NetworkCapability.octet6.umtsIntegAlgs.uia4 = 1;
   pvalue->s1NetworkCapability.octet6.umtsIntegAlgs.uia5 = 0;
   pvalue->s1NetworkCapability.octet6.umtsIntegAlgs.uia6 = 0;
   pvalue->s1NetworkCapability.octet6.umtsIntegAlgs.uia7 = 0;
   pvalue->s1NetworkCapability.m.octet7Present = 1;
   pvalue->s1NetworkCapability.octet7.proSedd = 0;
   pvalue->s1NetworkCapability.octet7.proSe = 0;
   pvalue->s1NetworkCapability.octet7.h245_ash = 0;
   pvalue->s1NetworkCapability.octet7.acc_csfb = 1;
   pvalue->s1NetworkCapability.octet7.lpp = 0;
   pvalue->s1NetworkCapability.octet7.lcs = 1;
   pvalue->s1NetworkCapability.octet7.x1xSR_VCC = 1;
   pvalue->s1NetworkCapability.octet7.nf = 1;
   pvalue->s1NetworkCapability.m.octet8Present = 1;
   pvalue->s1NetworkCapability.octet8.ePCO = 0;
   pvalue->s1NetworkCapability.octet8.hc_CP_CIoT = 1;
   pvalue->s1NetworkCapability.octet8.erwoPDN = 1;
   pvalue->s1NetworkCapability.octet8.s1_Udata = 1;
   pvalue->s1NetworkCapability.octet8.upCIoT = 1;
   pvalue->s1NetworkCapability.octet8.cpCIoT = 1;
   pvalue->s1NetworkCapability.octet8.prose_relay = 0;
   pvalue->s1NetworkCapability.octet8.proSedc = 1;
   pvalue->s1NetworkCapability.m.octet9Present = 1;
   pvalue->s1NetworkCapability.octet9.bearers = 1;
   pvalue->s1NetworkCapability.octet9.sgc = 0;
   pvalue->s1NetworkCapability.octet9.n1Mode = 1;
   pvalue->s1NetworkCapability.octet9.dcnr = 0;
   pvalue->s1NetworkCapability.octet9.cpBackoff = 1;
   pvalue->s1NetworkCapability.octet9.restrictEC = 0;
   pvalue->s1NetworkCapability.octet9.v2xPC5 = 1;
   pvalue->s1NetworkCapability.octet9.multDRB = 1;

   pvalue->m.uplinkStatPresent = 1;
   pvalue->uplinkStat.length = 0; /* length will be calculated */
   OSCRTLMEMSET(pvalue->uplinkStat.psi.elem, 0,
                sizeof(pvalue->uplinkStat.psi.elem));
   pvalue->uplinkStat.psi.elem[3] = TRUE;
   pvalue->uplinkStat.psi.elem[6] = TRUE;
   pvalue->uplinkStat.psi.elem[9] = TRUE;

   pvalue->m.sessionStatPresent = 1;
   pvalue->sessionStat.length = 10;
   OSCRTLMEMSET(pvalue->sessionStat.psi.elem, 0,
                sizeof(pvalue->sessionStat.psi.elem));
   pvalue->sessionStat.psi.elem[0] = TRUE;
   pvalue->sessionStat.psi.elem[5] = TRUE;
   pvalue->sessionStat.psi.elem[10] = TRUE;

   pvalue->m.micoIndPresent = 1;
   pvalue->micoInd.sprti = 1;
   pvalue->micoInd.raai = 0;

   pvalue->m.ueStatPresent = 1;
   pvalue->ueStat.length = 0; // Calculated automatically...
   pvalue->ueStat.n1RegStatus = 1;
   pvalue->ueStat.s1RegStatus = 0;

   pvalue->m.ueUsagePresent = 1;
   pvalue->ueUsage.length = 0; // Calculated automatically...
   pvalue->ueUsage.usage = 0;

   pvalue->m.containerTypePresent = TRUE;
   pvalue->containerType = TS24501IE_PayloadContainerType_uePolicy;
   pvalue->m.containerPresent = 1;
   pvalue->container.u.uePolicy.contents.numocts = 2;
   pvalue->container.u.uePolicy.contents.data = (OSOCTET*) rtxMemAlloc(&ctxt, 2);
   {
      static const OSOCTET testdata[] = { 0xc2, 0x39 };
      OSCRTLSAFEMEMCPY(
        (void *)pvalue->container.u.uePolicy.contents.data, 2, testdata, 2);
   }

   pvalue->m.updateTypePresent = 1;
   pvalue->updateType.length = 0; // Calculated automatically...
   pvalue->updateType.epsPnbCIoT = 2;
   pvalue->updateType.pnbCIoT = 3;
   pvalue->updateType.ngranUpd = 1;
   pvalue->updateType.smsReq = 0;

   pvalue->m._v16ExtPresent = 1;
   pvalue->m.ueRadioCapabilityIdPresent = 1;
   pvalue->ueRadioCapabilityId.length = 0; // Calculated automatically...
   pvalue->ueRadioCapabilityId.capId.numocts = 1;
   pvalue->ueRadioCapabilityId.capId.data = (OSOCTET *)rtxMemAlloc(&ctxt, 1);
   {
      static const OSOCTET testdata[] = { 0xff };
      OSCRTLSAFEMEMCPY((void *)pvalue->ueRadioCapabilityId.capId.data, 1,
                       testdata, 1);
   }

   pvalue->m.reqMappedNSSAIPresent = 1;
   pvalue->reqMappedNSSAI.length = 0;  // Calculated automatically...
   pvalue->reqMappedNSSAI.contents.n = 1;
   pvalue->reqMappedNSSAI.contents.elem[0].length = 4;
   pvalue->reqMappedNSSAI.contents.elem[0].mappedSST[0] = 0xee;
   pvalue->reqMappedNSSAI.contents.elem[0].m.mappedSDPresent = TRUE;
   pvalue->reqMappedNSSAI.contents.elem[0].mappedSD.numocts = 3;
   pvalue->reqMappedNSSAI.contents.elem[0].mappedSD.data =
                    (OSOCTET *)rtxMemAlloc(&ctxt, 3);
   {
      static const OSOCTET testdata[] = { 0xdd, 0xcc, 0xbb };
      OSCRTLSAFEMEMCPY((void *)pvalue->reqMappedNSSAI.contents.elem[0].mappedSD.data,
                       3, testdata, 3);
   }

   pvalue->m.addlInfoRequestedPresent = 1;
   pvalue->addlInfoRequested.cipherKey = TRUE;

   pvalue->m.wusAssistInfoPresent = 1;
   pvalue->wusAssistInfo.types.n = 1;
   pvalue->wusAssistInfo.types.elem[0].infoType = TS24301IE_InformationType_itUEPagingProbInfo;
   pvalue->wusAssistInfo.types.elem[0].infoValue = 30;

   pvalue->m.n5gcIndPresent = 1;
   pvalue->n5gcInd.n5gcReg = TRUE;

   pvalue->m.reqNBN1ParamsPresent = 1;
   pvalue->reqNBN1Params.drxValue = 11;

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
