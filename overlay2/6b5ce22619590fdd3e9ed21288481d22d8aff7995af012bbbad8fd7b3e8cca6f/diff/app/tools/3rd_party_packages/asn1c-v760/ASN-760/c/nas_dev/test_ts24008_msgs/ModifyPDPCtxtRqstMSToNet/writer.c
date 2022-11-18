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
   TS24008Msg_ModifyPDPCtxtRqstMSToNet data;
   TS24008Msg_ModifyPDPCtxtRqstMSToNet* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_ModifyPDPCtxtRqstMSToNet;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_ModifyPDPCtxtRqstMSToNet;
   pdu.data.u.obj_ModifyPDPCtxtRqstMSToNet = pvalue;

   asn1Init_TS24008Msg_ModifyPDPCtxtRqstMSToNet (pvalue);
   pvalue->m.requestedLLCSAPIPresent = 1;
   pvalue->requestedLLCSAPI.spare = 6;
   pvalue->requestedLLCSAPI.value = TS24008IE_SAPIValues_unassigned;
   pvalue->m.requestedNewQOSPresent = 1;
   pvalue->requestedNewQOS.length = 14;
   pvalue->requestedNewQOS.spare1 = 1;
   pvalue->requestedNewQOS.delayClass = 6;
   pvalue->requestedNewQOS.reliabilityClass = 0;
   pvalue->requestedNewQOS.peakThroughput = 3;
   pvalue->requestedNewQOS.spare2 = 0;
   pvalue->requestedNewQOS.precedenceClass = 3;
   pvalue->requestedNewQOS.spare3 = 0;
   pvalue->requestedNewQOS.meanThroughput = 25;
   pvalue->requestedNewQOS.trafficClass = 3;
   pvalue->requestedNewQOS.deliveryOrder = 0;
   pvalue->requestedNewQOS.deliveryErroneousSDU = 5;
   pvalue->requestedNewQOS.maxSDUSize = 63;
   pvalue->requestedNewQOS.maxUplinkBR = 189;
   pvalue->requestedNewQOS.maxDownlinkBR = 5;
   pvalue->requestedNewQOS.residualBER = 14;
   pvalue->requestedNewQOS.sduErrorRatio = 11;
   pvalue->requestedNewQOS.transferDelay = 45;
   pvalue->requestedNewQOS.trafficHandlingPrio = 1;
   pvalue->requestedNewQOS.guaranteedUplinkBR = 179;
   pvalue->requestedNewQOS.guaranteedDownlinkBR = 237;
   pvalue->requestedNewQOS.spare4 = 6;
   pvalue->requestedNewQOS.signallingIndication = 0;
   pvalue->requestedNewQOS.sourceStatsDescriptor = 6;
   pvalue->requestedNewQOS.extBitRate.n = 4;
   pvalue->requestedNewQOS.extBitRate.elem[0] = 133;
   pvalue->requestedNewQOS.extBitRate.elem[1] = 137;
   pvalue->requestedNewQOS.extBitRate.elem[2] = 151;
   pvalue->requestedNewQOS.extBitRate.elem[3] = 101;
   pvalue->m.newTFTPresent = 1;
   pvalue->newTFT.length = 65;
   pvalue->newTFT.octet1.tftOperationCode = TS24008IE_TFTOctet1_tftOperationCode_createTFT;
   pvalue->newTFT.octet1.eBit = 1;
   pvalue->newTFT.octet1.numPacketFilters = 0;
   pvalue->newTFT.packetFilterList.u.identifiers.numocts = 10;
   pvalue->newTFT.packetFilterList.u.identifiers.data = (OSOCTET*) rtxMemAlloc (&ctxt, 10);
   {
      static const OSOCTET testdata[] = {
      0xf4, 0x0f, 0x24, 0xbf, 0x1b, 0x7b, 0x45, 0x23,
      0x25, 0xa5 };
      OSCRTLMEMCPY ((void*)pvalue->newTFT.packetFilterList.u.identifiers.data, testdata, 10);
   }
   pvalue->m.protocolConfigOptionsPresent = 1;
   pvalue->protocolConfigOptions.length = 159;
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
