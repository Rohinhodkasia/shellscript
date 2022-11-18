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
   TS24008Msg_ActivatePDPCtxtReq data;
   TS24008Msg_ActivatePDPCtxtReq* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_ActivatePDPCtxtReq;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_ActivatePDPCtxtReq;
   pdu.data.u.obj_ActivatePDPCtxtReq = pvalue;

   asn1Init_TS24008Msg_ActivatePDPCtxtReq (pvalue);
   pvalue->requestedNSAPI.spare = 0;
   pvalue->requestedNSAPI.value = 10;
   pvalue->requestedLLCSAPI.spare = 7;
   pvalue->requestedLLCSAPI.value = TS24008IE_SAPIValues_sapi9;
   pvalue->requestedQOS.length = 13;
   pvalue->requestedQOS.spare1 = 0;
   pvalue->requestedQOS.delayClass = 5;
   pvalue->requestedQOS.reliabilityClass = 5;
   pvalue->requestedQOS.peakThroughput = 13;
   pvalue->requestedQOS.spare2 = 0;
   pvalue->requestedQOS.precedenceClass = 3;
   pvalue->requestedQOS.spare3 = 0;
   pvalue->requestedQOS.meanThroughput = 13;
   pvalue->requestedQOS.trafficClass = 3;
   pvalue->requestedQOS.deliveryOrder = 2;
   pvalue->requestedQOS.deliveryErroneousSDU = 3;
   pvalue->requestedQOS.maxSDUSize = 97;
   pvalue->requestedQOS.maxUplinkBR = 69;
   pvalue->requestedQOS.maxDownlinkBR = 206;
   pvalue->requestedQOS.residualBER = 3;
   pvalue->requestedQOS.sduErrorRatio = 8;
   pvalue->requestedQOS.transferDelay = 22;
   pvalue->requestedQOS.trafficHandlingPrio = 0;
   pvalue->requestedQOS.guaranteedUplinkBR = 33;
   pvalue->requestedQOS.guaranteedDownlinkBR = 204;
   pvalue->requestedQOS.spare4 = 2;
   pvalue->requestedQOS.signallingIndication = 1;
   pvalue->requestedQOS.sourceStatsDescriptor = 1;
   pvalue->requestedQOS.extBitRate.n = 4;
   pvalue->requestedQOS.extBitRate.elem[0] = 222;
   pvalue->requestedQOS.extBitRate.elem[1] = 220;
   pvalue->requestedQOS.extBitRate.elem[2] = 17;
   pvalue->requestedQOS.extBitRate.elem[3] = 213;
   pvalue->requestedPDPAddr.spare = 0;
   pvalue->requestedPDPAddr.pdpTypeOrg = 7;
   pvalue->requestedPDPAddr.pdpTypeNum = 192;
   {
      pvalue->requestedPDPAddr.addressInfo.numocts = 0;
   }
   pvalue->m.accessPointNamePresent = 1;

   rtxStrcpy (pvalue->accessPointName, sizeof(pvalue->accessPointName),
              "province1.mnc012.mcc345.gprs");

   pvalue->m.protocolConfigOptionsPresent = 1;
   pvalue->protocolConfigOptions.length = 0; /* calculated on encode */
   pvalue->protocolConfigOptions.octet3.configProtocol = 0;
   pvalue->m.requestTypePresent = 1;
   pvalue->requestType.value = TS24008IE_ReqTypeValues_rlos;

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
