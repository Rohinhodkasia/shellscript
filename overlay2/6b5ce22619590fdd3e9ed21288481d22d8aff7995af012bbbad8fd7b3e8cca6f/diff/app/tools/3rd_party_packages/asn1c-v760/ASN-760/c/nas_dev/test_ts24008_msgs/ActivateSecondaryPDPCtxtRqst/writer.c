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
   TS24008Msg_ActivateSecondaryPDPCtxtRqst data;
   TS24008Msg_ActivateSecondaryPDPCtxtRqst* pvalue= &data;
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
   pdu.protoDiscr = TS24007L3_ProtoDiscr_sessMgmt;
   pdu.msgType = ASN1V_mt_ActivateSecondaryPDPCtxtRqst;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_ActivateSecondaryPDPCtxtRqst;
   pdu.data.u.obj_ActivateSecondaryPDPCtxtRqst = pvalue;

   asn1Init_TS24008Msg_ActivateSecondaryPDPCtxtRqst (pvalue);
   pvalue->requestedNSAPI.spare = 4;
   pvalue->requestedNSAPI.value = 9;
   pvalue->requestedLLCSAPI.spare = 0;
   pvalue->requestedLLCSAPI.value = TS24008IE_SAPIValues_sapi3;
   // length will be calculated by encoder
   pvalue->requestedQOS.length = 0;
   pvalue->requestedQOS.spare1 = 0;
   pvalue->requestedQOS.delayClass = 4;
   pvalue->requestedQOS.reliabilityClass = 5;
   pvalue->requestedQOS.peakThroughput = 1;
   pvalue->requestedQOS.spare2 = 0;
   pvalue->requestedQOS.precedenceClass = 2;
   pvalue->requestedQOS.spare3 = 2;
   pvalue->requestedQOS.meanThroughput = 29;
   pvalue->requestedQOS.trafficClass = 0;
   pvalue->requestedQOS.deliveryOrder = 1;
   pvalue->requestedQOS.deliveryErroneousSDU = 3;
   pvalue->requestedQOS.maxSDUSize = 37;
   pvalue->requestedQOS.maxUplinkBR = 229;
   pvalue->requestedQOS.maxDownlinkBR = 157;
   pvalue->requestedQOS.residualBER = 3;
   pvalue->requestedQOS.sduErrorRatio = 0;
   pvalue->requestedQOS.transferDelay = 60;
   pvalue->requestedQOS.trafficHandlingPrio = 2;
   pvalue->requestedQOS.guaranteedUplinkBR = 126;
   pvalue->requestedQOS.guaranteedDownlinkBR = 116;
   pvalue->requestedQOS.spare4 = 2;
   pvalue->requestedQOS.signallingIndication = 1;
   pvalue->requestedQOS.sourceStatsDescriptor = 1;
   pvalue->requestedQOS.extBitRate.n = 4;
   pvalue->requestedQOS.extBitRate.elem[0] = 245;
   pvalue->requestedQOS.extBitRate.elem[1] = 4;
   pvalue->requestedQOS.extBitRate.elem[2] = 151;
   pvalue->requestedQOS.extBitRate.elem[3] = 219;
   pvalue->linkedTI.flag = 0;
   pvalue->linkedTI.value = 44;
   pvalue->m.trafficFlowTemplatePresent = 1;
   // length will be calculated by encoder
   pvalue->trafficFlowTemplate.length = 0;
   // this determines packetFilterList choice selection
   pvalue->trafficFlowTemplate.octet1.tftOperationCode =
      TS24008IE_TFTOctet1_tftOperationCode_delPktFilters;
   pvalue->trafficFlowTemplate.octet1.eBit = 0;
   // this value must match number of items in numPacketFilters
   pvalue->trafficFlowTemplate.octet1.numPacketFilters = 14;
   // must match numPacketFilters
   pvalue->trafficFlowTemplate.packetFilterList.u.identifiers.numocts = 14;
   pvalue->trafficFlowTemplate.packetFilterList.u.identifiers.data =
      (OSOCTET*) rtxMemAlloc (&ctxt, 14);
   {
      static const OSOCTET testdata[] = {
      0x82, 0x4c, 0x43, 0xdb, 0xeb, 0xee, 0xcd, 0xba,
      0x50, 0x60, 0x53, 0x8b, 0xee, 0x98 };
      OSCRTLMEMCPY ((void*)pvalue->trafficFlowTemplate.packetFilterList.u.identifiers.data, testdata, 14);
   }
   pvalue->m.protocolConfigOptionsPresent = 1;
   // length will be calculated by encoder
   pvalue->protocolConfigOptions.length = 0;
   pvalue->protocolConfigOptions.octet3.spare = 4;
   pvalue->protocolConfigOptions.octet3.configProtocol = 6;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24008Msg_PDU (&ctxt, &pdu);
   if (0 != ret) {
      printf ("encode PDU failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }
   /* Verify buffer is byte-aligned */

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
