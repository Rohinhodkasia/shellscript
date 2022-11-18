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
   TS24008Msg_ModifyPDPCtxtAccNetToMS data;
   TS24008Msg_ModifyPDPCtxtAccNetToMS* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_ModifyPDPCtxtAccNetToMS;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_ModifyPDPCtxtAccNetToMS;
   pdu.data.u.obj_ModifyPDPCtxtAccNetToMS = pvalue;

   asn1Init_TS24008Msg_ModifyPDPCtxtAccNetToMS (pvalue);
   pvalue->m.negotiatedQOSPresent = 1;
   pvalue->negotiatedQOS.length = 14;
   pvalue->negotiatedQOS.spare1 = 2;
   pvalue->negotiatedQOS.delayClass = 2;
   pvalue->negotiatedQOS.reliabilityClass = 5;
   pvalue->negotiatedQOS.peakThroughput = 1;
   pvalue->negotiatedQOS.spare2 = 0;
   pvalue->negotiatedQOS.precedenceClass = 4;
   pvalue->negotiatedQOS.spare3 = 2;
   pvalue->negotiatedQOS.meanThroughput = 13;
   pvalue->negotiatedQOS.trafficClass = 0;
   pvalue->negotiatedQOS.deliveryOrder = 2;
   pvalue->negotiatedQOS.deliveryErroneousSDU = 3;
   pvalue->negotiatedQOS.maxSDUSize = 137;
   pvalue->negotiatedQOS.maxUplinkBR = 228;
   pvalue->negotiatedQOS.maxDownlinkBR = 15;
   pvalue->negotiatedQOS.residualBER = 5;
   pvalue->negotiatedQOS.sduErrorRatio = 7;
   pvalue->negotiatedQOS.transferDelay = 59;
   pvalue->negotiatedQOS.trafficHandlingPrio = 1;
   pvalue->negotiatedQOS.guaranteedUplinkBR = 132;
   pvalue->negotiatedQOS.guaranteedDownlinkBR = 121;
   pvalue->negotiatedQOS.spare4 = 0;
   pvalue->negotiatedQOS.signallingIndication = 0;
   pvalue->negotiatedQOS.sourceStatsDescriptor = 5;
   pvalue->negotiatedQOS.extBitRate.n = 4;
   pvalue->negotiatedQOS.extBitRate.elem[0] = 190;
   pvalue->negotiatedQOS.extBitRate.elem[1] = 89;
   pvalue->negotiatedQOS.extBitRate.elem[2] = 182;
   pvalue->negotiatedQOS.extBitRate.elem[3] = 11;
   pvalue->m.negotiatedLLCSAPIPresent = 1;
   pvalue->negotiatedLLCSAPI.spare = 10;
   pvalue->negotiatedLLCSAPI.value = TS24008IE_SAPIValues_sapi11;
   pvalue->m.newRadioPriorityPresent = 1;
   pvalue->newRadioPriority.value = 1;
   pvalue->m.packetFlowIdentPresent = 1;
   pvalue->packetFlowIdent.spare = 0;
   pvalue->packetFlowIdent.value = 50;
   pvalue->m.protocolConfigOptionsPresent = 1;
   pvalue->protocolConfigOptions.length = 145;
   pvalue->protocolConfigOptions.octet3.spare = 12;
   pvalue->protocolConfigOptions.octet3.configProtocol = 3;

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
