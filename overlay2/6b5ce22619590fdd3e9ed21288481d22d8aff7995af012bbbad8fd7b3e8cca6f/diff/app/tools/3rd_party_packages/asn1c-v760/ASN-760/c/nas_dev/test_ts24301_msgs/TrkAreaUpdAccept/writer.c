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
   TS24301Msg_TrkAreaUpdAccept data;
   TS24301Msg_TrkAreaUpdAccept* pvalue = &data;
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
   asn1SetTC_TS24301Msg_PDU_obj_TrkAreaUpdAccept (&ctxt, &pdu, pvalue);

   asn1Init_TS24301Msg_TrkAreaUpdAccept (pvalue);

   pvalue->spare = 0;
   pvalue->epsUpdateResult.spare = 0;
   pvalue->epsUpdateResult.result = 1;

   pvalue->m.t3412ValuePresent = 1;
   pvalue->t3412Value.unit = 5;
   pvalue->t3412Value.timerValue = 30;

   pvalue->m.gutiPresent = 1;
   pvalue->guti.length = 0; /* will be calculated */
   pvalue->guti.filler = 12;
   pvalue->guti.oddEvenInd = 0;
   pvalue->guti.typeOfIdent = TS24301IE_EPSMobileIdentity_typeOfIdent_imsi;

   switch (pvalue->guti.typeOfIdent) {
      /* guti */
      case 6:
         rtxStrncpy (pvalue->guti.content.u.guti.mcc_mnc.mcc, 4, "250", 3);
         rtxStrncpy (pvalue->guti.content.u.guti.mcc_mnc.mnc, 4, "39", 3);
         {
            static const OSOCTET testdata[] = {
            0x6c, 0x16 };
            OSCRTLMEMCPY ((void*)pvalue->guti.content.u.guti.mmeGroupID, testdata, 2);
         }
         pvalue->guti.content.u.guti.mmeCode = 15;
         {
            static const OSOCTET testdata[] = {
            0x07, 0x5b, 0x40, 0xe8 };
            OSCRTLMEMCPY ((void*)pvalue->guti.content.u.guti.tmsi, testdata, 4);
         }
         break;

      /* imsi */
      case 1:
         rtxStrncpy (pvalue->guti.content.u.imsi, sizeof(pvalue->guti.content.u.imsi), "40407123456789", 15);
         break;

      /* imei */
      case 3:
         rtxStrncpy (pvalue->guti.content.u.imei, sizeof(pvalue->guti.content.u.imei), "40407123456789", 15);
         break;
   }

   pvalue->m.taiListPresent = 1;
   pvalue->taiList.length = 0; /* will be calculated */

   pvalue->taiList.idents.n = 1;
   pvalue->taiList.idents.elem[0].spare = 0;
   pvalue->taiList.idents.elem[0].typeOfList = 0;
   pvalue->taiList.idents.elem[0].numElements = 0; /* +1 */

   switch (pvalue->taiList.idents.elem[0].typeOfList) {
      /* partTrkIdentList0 */
      case 0:
         rtxStrncpy (pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.mcc_mnc.mcc, 4, "260", 3);
         rtxStrncpy (pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.mcc_mnc.mnc, 4, "03", 3);

         pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.n = 1;
         {
            static const OSOCTET testdata[] = {
            0xd5, 0xb0 };
            OSCRTLMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.elem[0].data, testdata, 2);
         }

         break;

      /* partTrkIdentList1 */
      case 1:
         rtxStrncpy (pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList1.mcc_mnc.mcc, 4, "412", 3);
         rtxStrncpy (pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList1.mcc_mnc.mnc, 4, "01", 3);

         {
            static const OSOCTET testdata[] = {
            0x60, 0x39 };
            OSCRTLMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList1.tac.data, testdata, 2);
         }

         break;

      /* partTrkIdentList2 */
      case 2:
         pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList2.n = 1;
         rtxStrncpy (pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList2.elem[0].mcc_mnc.mcc, 4, "641", 3);
         rtxStrncpy (pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList2.elem[0].mcc_mnc.mnc, 4, "11", 3);

         {
            static const OSOCTET testdata[] = {
            0x28, 0x7a };
            OSCRTLMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList2.elem[0].tac.data, testdata, 2);
         }
         break;

   }

   pvalue->m.epsBearerContextStatusPresent = 1;
   pvalue->epsBearerContextStatus.ebi7 = 0;
   pvalue->epsBearerContextStatus.ebi6 = 0;
   pvalue->epsBearerContextStatus.ebi5 = 0;
   pvalue->epsBearerContextStatus.ebi4 = 0;
   pvalue->epsBearerContextStatus.ebi3 = 0;
   pvalue->epsBearerContextStatus.ebi2 = 0;
   pvalue->epsBearerContextStatus.ebi1 = 0;
   pvalue->epsBearerContextStatus.ebi0 = 1;
   pvalue->epsBearerContextStatus.ebi15 = 0;
   pvalue->epsBearerContextStatus.ebi14 = 0;
   pvalue->epsBearerContextStatus.ebi13 = 1;
   pvalue->epsBearerContextStatus.ebi12 = 0;
   pvalue->epsBearerContextStatus.ebi11 = 1;
   pvalue->epsBearerContextStatus.ebi10 = 1;
   pvalue->epsBearerContextStatus.ebi9 = 0;
   pvalue->epsBearerContextStatus.ebi8 = 1;

   pvalue->m.locAreaIdentPresent = 1;

   rtxStrncpy (pvalue->locAreaIdent.mcc_mnc.mcc, 4, "250", 3);
   rtxStrncpy (pvalue->locAreaIdent.mcc_mnc.mnc, 4, "05", 3);

   pvalue->locAreaIdent.lac = 16694;

   pvalue->m.msIdentityPresent = 1;
   pvalue->msIdentity.t =  5;
   pvalue->msIdentity.u.tmgi.mbmsSessIdInd = 1;
   pvalue->msIdentity.u.tmgi.mccMncInd = 1;
   {
      static const OSOCTET testdata[] = {
      0x0e, 0x3b, 0x14 };
      OSCRTLMEMCPY ((void*)pvalue->msIdentity.u.tmgi.mbmsServiceID, testdata, 3);
   }

   rtxStrncpy (pvalue->msIdentity.u.tmgi.mcc_mnc.mcc, 4, "525", 3);
   rtxStrncpy (pvalue->msIdentity.u.tmgi.mcc_mnc.mnc, 4, "01", 3);

   pvalue->msIdentity.u.tmgi.mbmsSessionID = 174;

   pvalue->m.emmCausePresent = 1;
   pvalue->emmCause = TS24301IE_EMMCause_imsiUnkInHSS;

   pvalue->m.t3402ValuePresent = 1;
   pvalue->t3402Value.unit = 0;
   pvalue->t3402Value.timerValue = 7;

   pvalue->m.t3423ValuePresent = 1;
   pvalue->t3423Value.unit = 5;
   pvalue->t3423Value.timerValue = 27;

   pvalue->m.equivalentPLMNsPresent = 1;
   pvalue->equivalentPLMNs.n = 1;
   rtxStrncpy (pvalue->equivalentPLMNs.elem[0].mcc, 4, "456", 3);
   rtxStrncpy (pvalue->equivalentPLMNs.elem[0].mnc, 4, "02", 3);

   pvalue->m.emergencyNumberListPresent = 1;
   pvalue->emergencyNumberList.length = 0; /* will be calculated */
   pvalue->emergencyNumberList.numbers.n = 1;
   pvalue->emergencyNumberList.numbers.elem[0].length = 0;
   pvalue->emergencyNumberList.numbers.elem[0].spare = 0;
   pvalue->emergencyNumberList.numbers.elem[0].catValue = 18;
   pvalue->emergencyNumberList.numbers.elem[0].digits = "37b##1";

   pvalue->m.epsNetworkFeatureSupportPresent = 1;
   pvalue->epsNetworkFeatureSupport.length = 1;
   pvalue->epsNetworkFeatureSupport.cpCIoT = 0;
   pvalue->epsNetworkFeatureSupport.erNoPDN = 1;
   pvalue->epsNetworkFeatureSupport.esr = 1;
   pvalue->epsNetworkFeatureSupport.csLCS = 2;
   pvalue->epsNetworkFeatureSupport.epcLCS = 0;
   pvalue->epsNetworkFeatureSupport.emcBS = 1;
   pvalue->epsNetworkFeatureSupport.imsVoPS = 1;

   pvalue->m.addnUpdateResultPresent = 1;
   pvalue->addnUpdateResult.spare = 2;
   pvalue->addnUpdateResult.value = TS24301IE_AddnUpdateResult_value_noInfo;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

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
