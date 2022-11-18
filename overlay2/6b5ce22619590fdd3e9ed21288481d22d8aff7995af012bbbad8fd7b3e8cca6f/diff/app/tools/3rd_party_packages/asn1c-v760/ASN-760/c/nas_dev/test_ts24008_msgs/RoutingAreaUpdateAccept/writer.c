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
   TS24008Msg_RoutingAreaUpdateAccept data;
   TS24008Msg_RoutingAreaUpdateAccept* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_RoutingAreaUpdateAccept;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_RoutingAreaUpdateAccept;
   pdu.data.u.obj_RoutingAreaUpdateAccept = pvalue;

   asn1Init_TS24008Msg_RoutingAreaUpdateAccept (pvalue);

   pvalue->forceToStandby.spare = 0;
   pvalue->forceToStandby.value = 5;
   pvalue->updateResult.fop = 1;
   pvalue->updateResult.value = 0;
   pvalue->periodicRAUpdateTimer.unit = 1;
   pvalue->periodicRAUpdateTimer.timerValue = 29;
   rtxStrncpy(pvalue->routingAreaIdent.mcc_mnc.mcc,
              sizeof(pvalue->routingAreaIdent.mcc_mnc.mcc), "05b", 4);
   rtxStrncpy(pvalue->routingAreaIdent.mcc_mnc.mnc,
              sizeof(pvalue->routingAreaIdent.mcc_mnc.mnc), "234", 4);

   pvalue->routingAreaIdent.lac = 1930;
   pvalue->routingAreaIdent.rac = 3;

   pvalue->m.pTMSISignaturePresent = 1;
   {
      static const OSOCTET testdata[] = {
      0x3e, 0xd3, 0x2c };
      OSCRTLMEMCPY ((void*)pvalue->pTMSISignature.value, testdata, 3);
   }

   pvalue->m.allocatedPTMSIPresent = 1;
   pvalue->allocatedPTMSI.t =  T_TS24008IE_MobileIdentity_imeisv;
   rtxStrncpy(pvalue->allocatedPTMSI.u.imeisv,
              sizeof(pvalue->allocatedPTMSI.u.imeisv), "3216543b72acc0bc", 17);

   pvalue->m.msIdentityPresent = 1;
   pvalue->msIdentity.t =  T_TS24008IE_MobileIdentity_imeisv;
   rtxStrncpy(pvalue->msIdentity.u.imeisv,
              sizeof(pvalue->msIdentity.u.imeisv), "6b2b43b842435787", 17);

   pvalue->m.receiveNPDUNumberListPresent = 1;
   pvalue->receiveNPDUNumberList.length = 3;
   pvalue->receiveNPDUNumberList.receiveNPDUNumber.n = 2;
   pvalue->receiveNPDUNumberList.receiveNPDUNumber.elem =
      rtxMemAllocArrayZ (&ctxt, 2, TS24008IE_ReceiveNPDUNumber);
   pvalue->receiveNPDUNumberList.receiveNPDUNumber.elem[0].nsapi = 5;
   pvalue->receiveNPDUNumberList.receiveNPDUNumber.elem[0].numberValue = 126;
   pvalue->receiveNPDUNumberList.receiveNPDUNumber.elem[1].nsapi = 7;
   pvalue->receiveNPDUNumberList.receiveNPDUNumber.elem[1].numberValue = 226;

   pvalue->m.negotiatedREADYTimerValuePresent = 1;
   pvalue->negotiatedREADYTimerValue.unit = 3;
   pvalue->negotiatedREADYTimerValue.timerValue = 7;

   pvalue->m.gmmCausePresent = 1;
   pvalue->gmmCause = 163;

   pvalue->m.t3302ValuePresent = 1;
   pvalue->t3302Value.value.unit = 1;
   pvalue->t3302Value.value.timerValue = 14;

   pvalue->m.cellNotificationPresent = 1;

   pvalue->m.equivalentPLMNsPresent = 1;
   pvalue->equivalentPLMNs.n = 1;
   rtxStrncpy(pvalue->equivalentPLMNs.elem[0].mcc,
              sizeof(pvalue->equivalentPLMNs.elem[0].mcc), "989", 4);
   rtxStrncpy(pvalue->equivalentPLMNs.elem[0].mnc,
              sizeof(pvalue->equivalentPLMNs.elem[0].mnc), "*#6", 4);

   pvalue->m.pdpContextStatusPresent = 1;
   {
      static const OSOCTET testdata[] = {
      0x24, 0x19 };
      OSCRTLMEMCPY ((void*)pvalue->pdpContextStatus.value, testdata, 2);
   }

   pvalue->m.netFeatureSupportPresent = 1;
   pvalue->netFeatureSupport.lcs_molr = 0;
   pvalue->netFeatureSupport.mbms = 1;
   pvalue->netFeatureSupport.imsVoPS = 0;
   pvalue->netFeatureSupport.emcBS = 0;

   pvalue->m.emergencyNumListPresent = 1;
   pvalue->emergencyNumList.length = 0; /* will be calculated */
   pvalue->emergencyNumList.numbers.n = 2;
   pvalue->emergencyNumList.numbers.elem[0].length = 0; /* will be calculated */
   pvalue->emergencyNumList.numbers.elem[0].spare = 0;
   pvalue->emergencyNumList.numbers.elem[0].catValue = 19;
   pvalue->emergencyNumList.numbers.elem[0].digits = "a6*776#";
   pvalue->emergencyNumList.numbers.elem[1].length = 0; /* will be calculated */
   pvalue->emergencyNumList.numbers.elem[1].spare = 0;
   pvalue->emergencyNumList.numbers.elem[1].catValue = 20;
   pvalue->emergencyNumList.numbers.elem[1].digits = "12345678";

   pvalue->m.mbmsContextStatusPresent = 1;
   {
      pvalue->mbmsContextStatus.numocts = 0;
   }

   pvalue->m.requestedMSInfoPresent = 1;
   pvalue->requestedMSInfo.i_RAT = 1;
   pvalue->requestedMSInfo.i_RAT2 = 1;
   pvalue->requestedMSInfo.spare = 1;

   pvalue->m.t3319ValuePresent = 1;
   pvalue->t3319Value.value.unit = 7;
   pvalue->t3319Value.value.timerValue = 20;

   pvalue->m.t3323ValuePresent = 1;
   pvalue->t3323Value.value.unit = 6;
   pvalue->t3323Value.value.timerValue = 4;

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
   /* Verify buffer is byte-aligned */
   OSRTASSERT (ctxt.buffer.bitOffset == 8 || ctxt.buffer.bitOffset == 0);

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
