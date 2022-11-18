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
   TS24008Msg_ModifyPDPCtxtRqstNetToMS data;
   TS24008Msg_ModifyPDPCtxtRqstNetToMS* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_ModifyPDPCtxtRqstNetToMS;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_ModifyPDPCtxtRqstNetToMS;
   pdu.data.u.obj_ModifyPDPCtxtRqstNetToMS = pvalue;

   asn1Init_TS24008Msg_ModifyPDPCtxtRqstNetToMS (pvalue);

   pvalue->spare = 1;
   pvalue->radioPriority.value = 1;
   pvalue->requestedLLCSAPI.spare = 10;
   pvalue->requestedLLCSAPI.value = TS24008IE_SAPIValues_sapi11;
   pvalue->newQOS.length = 8;
   pvalue->newQOS.spare1 = 1;
   pvalue->newQOS.delayClass = 4;
   pvalue->newQOS.reliabilityClass = 2;
   pvalue->newQOS.peakThroughput = 13;
   pvalue->newQOS.spare2 = 0;
   pvalue->newQOS.precedenceClass = 2;
   pvalue->newQOS.spare3 = 3;
   pvalue->newQOS.meanThroughput = 22;
   pvalue->newQOS.trafficClass = 0;
   pvalue->newQOS.deliveryOrder = 2;
   pvalue->newQOS.deliveryErroneousSDU = 1;
   pvalue->newQOS.maxSDUSize = 81;
   pvalue->newQOS.maxUplinkBR = 100;
   pvalue->newQOS.maxDownlinkBR = 203;
   pvalue->newQOS.residualBER = 3;
   pvalue->newQOS.sduErrorRatio = 4;
   pvalue->newQOS.transferDelay = 42;
   pvalue->newQOS.trafficHandlingPrio = 1;
   pvalue->newQOS.guaranteedUplinkBR = 189;
   pvalue->newQOS.guaranteedDownlinkBR = 6;
   pvalue->newQOS.spare4 = 1;
   pvalue->newQOS.signallingIndication = 0;
   pvalue->newQOS.sourceStatsDescriptor = 11;

   pvalue->newQOS.extBitRate.n = 4;
   pvalue->newQOS.extBitRate.elem[0] = 251;
   pvalue->newQOS.extBitRate.elem[1] = 154;
   pvalue->newQOS.extBitRate.elem[2] = 108;
   pvalue->newQOS.extBitRate.elem[3] = 125;

   pvalue->m.pdpAddressPresent = 1;
   pvalue->pdpAddress.spare = 13;
   pvalue->pdpAddress.pdpTypeOrg = 14;
   pvalue->pdpAddress.pdpTypeNum = 178;
   {
      pvalue->pdpAddress.addressInfo.numocts = 0;
   }

   pvalue->m.packetFlowIdentPresent = 1;
   pvalue->packetFlowIdent.spare = 0;
   pvalue->packetFlowIdent.value = 71;

   pvalue->m.protocolConfigOptionsPresent = 1;
   pvalue->protocolConfigOptions.length = 190;
   pvalue->protocolConfigOptions.octet3.configProtocol = 0;

   pvalue->m.trafficFlowTemplatePresent = 1;
   pvalue->trafficFlowTemplate.length = 9;
   pvalue->trafficFlowTemplate.octet1.tftOperationCode =
      TS24008IE_TFTOctet1_tftOperationCode_createTFT;
   pvalue->trafficFlowTemplate.octet1.eBit = 1;
   pvalue->trafficFlowTemplate.octet1.numPacketFilters = 0;

   pvalue->trafficFlowTemplate.packetFilterList.u.identifiers.numocts = 10;
   pvalue->trafficFlowTemplate.packetFilterList.u.identifiers.data =
      (OSOCTET*) rtxMemAlloc (&ctxt, 10);
   {
      static const OSOCTET testdata[] = {
      0xf4, 0x0f, 0x24, 0xbf, 0x1b, 0x7b, 0x45, 0x23,
      0x25, 0xa5 };
      OSCRTLMEMCPY ((void*)pvalue->trafficFlowTemplate.packetFilterList.u.identifiers.data,
                     testdata, 10);
   }

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
