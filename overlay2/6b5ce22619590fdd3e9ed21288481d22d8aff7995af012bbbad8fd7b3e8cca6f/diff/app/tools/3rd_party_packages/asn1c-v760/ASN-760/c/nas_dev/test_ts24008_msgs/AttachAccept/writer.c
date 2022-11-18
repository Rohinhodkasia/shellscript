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
   TS24008Msg_AttachAccept data;
   TS24008Msg_AttachAccept* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_AttachAccept;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_AttachAccept;
   pdu.data.u.obj_AttachAccept = pvalue;

   asn1Init_TS24008Msg_AttachAccept (pvalue);
   pvalue->attachResult.fop = 1;
   pvalue->attachResult.resultOfAttach = TS24008IE_AttachResultValues_gprsOnly;
   pvalue->forceToStandby.value = 4;
   pvalue->periodicRAUpdateTimer.unit = 5;
   pvalue->periodicRAUpdateTimer.timerValue = 26;
   pvalue->radioPriForSMS.value = 1;
   pvalue->radioPriForTOM8.value = 1;
   rtxStrncpy(pvalue->routingAreaIdent.mcc_mnc.mcc,
              sizeof(pvalue->routingAreaIdent.mcc_mnc.mcc), "#02", 4);
   rtxStrncpy(pvalue->routingAreaIdent.mcc_mnc.mnc,
              sizeof(pvalue->routingAreaIdent.mcc_mnc.mnc), "b3a", 4);
   pvalue->routingAreaIdent.lac = 13530;
   pvalue->routingAreaIdent.rac = 204;
   pvalue->m.pTMSISignaturePresent = 1;
   {
      static const OSOCTET testdata[] = {
      0x97, 0xc1, 0xd };
      OSCRTLMEMCPY ((void*)pvalue->pTMSISignature.value, testdata, 3);
   }
   pvalue->m.negotiatedREADYTimerValuePresent = 1;
   pvalue->negotiatedREADYTimerValue.unit = 3;
   pvalue->negotiatedREADYTimerValue.timerValue = 29;
   pvalue->m.allocatedPTMSIPresent = 1;
   pvalue->allocatedPTMSI.t =  T_TS24008IE_MobileIdentity_imsi;
   rtxStrncpy(pvalue->allocatedPTMSI.u.imsi,
              sizeof(pvalue->allocatedPTMSI.u.imsi), "16455542149210", 15);
   pvalue->m.msIdentityPresent = 1;
   pvalue->msIdentity.t =  T_TS24008IE_MobileIdentity_tmgi;
   pvalue->msIdentity.u.tmgi.mbmsSessIdInd = 1;
   pvalue->msIdentity.u.tmgi.mccMncInd = 1;
   {
      static const OSOCTET testdata[] = {
      0xd2, 0x16, 0x68 };
      OSCRTLMEMCPY ((void*)pvalue->msIdentity.u.tmgi.mbmsServiceID, testdata, 3);
   }
   rtxStrncpy(pvalue->msIdentity.u.tmgi.mcc_mnc.mcc,
              sizeof(pvalue->msIdentity.u.tmgi.mcc_mnc.mcc), "35#", 4);
   rtxStrncpy(pvalue->msIdentity.u.tmgi.mcc_mnc.mnc,
              sizeof(pvalue->msIdentity.u.tmgi.mcc_mnc.mnc), "35b", 4);
   pvalue->msIdentity.u.tmgi.mbmsSessionID = 240;
   pvalue->m.gmmCausePresent = 1;
   pvalue->gmmCause = 129;

   pvalue->m.t3302ValuePresent = 1;
   pvalue->t3302Value.length = 1;
   pvalue->t3302Value.value.unit = 5;
   pvalue->t3302Value.value.timerValue = 21;

   pvalue->m.cellNotificationPresent = 1;

   pvalue->m.equivalentPLMNsPresent = 1;
   pvalue->equivalentPLMNs.n = 1;
   rtxStrncpy(pvalue->equivalentPLMNs.elem[0].mcc,
              sizeof(pvalue->equivalentPLMNs.elem[0].mcc), "93c", 4);
   rtxStrncpy(pvalue->equivalentPLMNs.elem[0].mnc,
              sizeof(pvalue->equivalentPLMNs.elem[0].mnc), "996", 4);

   pvalue->m.netFeatureSupportPresent = 1;
   pvalue->netFeatureSupport.lcs_molr = 0;
   pvalue->netFeatureSupport.mbms = 0;
   pvalue->netFeatureSupport.imsVoPS = 1;
   pvalue->netFeatureSupport.emcBS = 1;

   pvalue->m.emergencyNumListPresent = 1;
   pvalue->emergencyNumList.length = 0; /* will be calculated */
   pvalue->emergencyNumList.numbers.n = 1;
   pvalue->emergencyNumList.numbers.elem[0].spare = 0;
   pvalue->emergencyNumList.numbers.elem[0].catValue = 21;
   pvalue->emergencyNumList.numbers.elem[0].digits = "9#08";

   pvalue->m.requestedMSInfoPresent = 1;
   pvalue->requestedMSInfo.i_RAT = 1;
   pvalue->requestedMSInfo.i_RAT2 = 1;

   pvalue->m.t3319ValuePresent = 1;
   pvalue->t3319Value.value.unit = 4;
   pvalue->t3319Value.value.timerValue = 14;

   pvalue->m.t3323ValuePresent = 1;
   pvalue->t3323Value.value.unit = 3;
   pvalue->t3323Value.value.timerValue = 1;

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
