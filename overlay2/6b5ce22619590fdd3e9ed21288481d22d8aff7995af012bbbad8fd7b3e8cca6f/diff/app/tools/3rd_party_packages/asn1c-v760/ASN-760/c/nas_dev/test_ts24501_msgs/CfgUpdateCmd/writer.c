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
   TS24501Msg_CfgUpdateCmd data;
   TS24501Msg_CfgUpdateCmd* pvalue = &data;
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
   pdu.secHdr.msgAuthCode = 35000;
   pdu.secHdr.seqNumber  = 250;
   pdu.hdrData.u.mm.secHdrType = TS24501Msg_NAS5GSecHdrType_noSec;

   asn1SetTC_TS24501Msg_PDU_obj_CfgUpdateCmd5G (&ctxt, &pdu, pvalue);

   asn1Init_TS24501Msg_CfgUpdateCmd (pvalue);

   pvalue->m.cfgUpdIndicationPresent = 1;
   pvalue->cfgUpdIndication.regRequested = 1;
   pvalue->cfgUpdIndication.ack = 0;

   pvalue->m.gutiPresent = 1;
   pvalue->guti.t = T_TS24501IE_MobileIdentity_guti;
   rtxStrncpy (pvalue->guti.u.guti.mcc_mnc.mcc, 4, "404", 3);
   rtxStrncpy (pvalue->guti.u.guti.mcc_mnc.mnc, 4, "40", 3);
   pvalue->guti.u.guti.amfRegionID = 40;
   pvalue->guti.u.guti.amfSetID = 8;
   pvalue->guti.u.guti.amfPointer = 2;
   {
      static const OSOCTET testdata[] = { 
      0x9f, 0x14, 0x6b, 0x69 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->guti.u.guti.tmsi, 4, testdata, 4);
   }

   pvalue->m.taiListPresent = 1;
   pvalue->taiList.length = 0; /* length will be calculated */
   pvalue->taiList.idents.n = 1;
   pvalue->taiList.idents.elem[0].typeOfList = 0;
   pvalue->taiList.idents.elem[0].numElements = 8;
   rtxStrncpy (pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.mcc_mnc.mcc, 4, "640", 3);
   rtxStrncpy (pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.mcc_mnc.mnc, 4, "05", 3);
   pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.n = 9;
   {
      static const OSOCTET testdata[] = { 
      0x69, 0xe2, 0x7e };
      OSCRTLSAFEMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.elem[0].data, 3, testdata, 3);
   }
   {
      static const OSOCTET testdata[] = { 
      0xd9, 0xae, 0x68 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.elem[1].data, 3, testdata, 3);
   }
   {
      static const OSOCTET testdata[] = { 
      0x40, 0xc5, 0x28 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.elem[2].data, 3, testdata, 3);
   }
   {
      static const OSOCTET testdata[] = { 
      0xc4, 0x80, 0x51 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.elem[3].data, 3, testdata, 3);
   }
   {
      static const OSOCTET testdata[] = { 
      0x01, 0xfc, 0xa };
      OSCRTLSAFEMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.elem[4].data, 3, testdata, 3);
   }
   {
      static const OSOCTET testdata[] = { 
      0xfa, 0x0f, 0x87 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.elem[5].data, 3, testdata, 3);
   }
   {
      static const OSOCTET testdata[] = { 
      0xfd, 0x4f, 0xe1 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.elem[6].data, 3, testdata, 3);
   }
   {
      static const OSOCTET testdata[] = { 
      0xdf, 0xa3, 0x1 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.elem[7].data, 3, testdata, 3);
   }
   {
      static const OSOCTET testdata[] = { 
      0xf3, 0x8e, 0xe9 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->taiList.idents.elem[0].elements.u.partTrkIdentList0.tacs.elem[8].data, 3, testdata, 3);
   }

   pvalue->m.allowedNSSAIPresent = 1;
   pvalue->allowedNSSAI.length = 0; /* length will be calculated */
   pvalue->allowedNSSAI.contents.n = 1;
   pvalue->allowedNSSAI.contents.elem[0].length = 0; /* length will be calculated */
   pvalue->allowedNSSAI.contents.elem[0].sst = 122;
   pvalue->allowedNSSAI.contents.elem[0].m.sdPresent = TRUE;
   pvalue->allowedNSSAI.contents.elem[0].sd = 1619282;
   pvalue->allowedNSSAI.contents.elem[0].m.mappedSSTPresent = TRUE;
   {
      static const OSOCTET testdata[] = { 
      0x10 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->allowedNSSAI.contents.elem[0].mappedSST, 1, testdata, 1);
   }
   pvalue->allowedNSSAI.contents.elem[0].m.mappedSDPresent = TRUE;
   {
      static const OSOCTET testdata[] = { 
      0xc1, 0x44, 0xaf };
      OSCRTLSAFEMEMCPY ((void*)pvalue->allowedNSSAI.contents.elem[0].mappedSD, 3, testdata, 3);
   }

   pvalue->m.fullNetworkNamePresent = 1;
   pvalue->fullNetworkName.length = 0; /* length will be calculated */
   pvalue->fullNetworkName.ext = 1;
   pvalue->fullNetworkName.codingScheme = TS24008IE_NetworkName_codingScheme_callBcastData;
   pvalue->fullNetworkName.addCI = 0;
   pvalue->fullNetworkName.numSpareBitsInLastOct = 4;
   pvalue->fullNetworkName.textString.u.callBcastData = "KdCJO";

   pvalue->m.localTZPresent = 1;
   pvalue->localTZ = 105;

   pvalue->m.univAndLocalTZPresent = 1;
   pvalue->univAndLocalTZ.year = 23;
   pvalue->univAndLocalTZ.month = 10;
   pvalue->univAndLocalTZ.day = 30;
   pvalue->univAndLocalTZ.hour = 12;
   pvalue->univAndLocalTZ.minute = 10;
   pvalue->univAndLocalTZ.second = 17;
   pvalue->univAndLocalTZ.timezone = 5;

   pvalue->m.dstPresent = 1;
   pvalue->dst.length = 0; /* length will be calculated */
   pvalue->dst.dst = TS24008IE_DaylightSavingTime_dst_dstNoAdjust;

   pvalue->m.micoIndPresent = 1;
   pvalue->micoInd.sprti = 0;
   pvalue->micoInd.raai = 1;

   pvalue->m.rejectedNSSAIPresent = 1;
   pvalue->rejectedNSSAI.length = 0; /* length will be calculated */
   pvalue->rejectedNSSAI.rejectedNSSAI.n = 1;
   pvalue->rejectedNSSAI.rejectedNSSAI.elem[0].length = 4;
   pvalue->rejectedNSSAI.rejectedNSSAI.elem[0].cause = TS24501IE_RejectedNSSAI_cause_unavailInCurrRegisArea;
   pvalue->rejectedNSSAI.rejectedNSSAI.elem[0].sst = 153;
   pvalue->rejectedNSSAI.rejectedNSSAI.elem[0].m.sdPresent = 1;
   pvalue->rejectedNSSAI.rejectedNSSAI.elem[0].sd = 7049671;

   pvalue->m._v16ExtPresent = TRUE;
   pvalue->m.regResultPresent = TRUE;
   pvalue->regResult.emergencyRegistered = TRUE;
   pvalue->regResult.nssaa = FALSE;
   pvalue->regResult.smsAllowed = TRUE;
   pvalue->regResult.regResult = TS24501IE_RegistrationResultValue_accessAndNonAccess;

   pvalue->m.additionalConfigIndicationPresent = TRUE;
   pvalue->additionalConfigIndication.scmr = TRUE;

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
