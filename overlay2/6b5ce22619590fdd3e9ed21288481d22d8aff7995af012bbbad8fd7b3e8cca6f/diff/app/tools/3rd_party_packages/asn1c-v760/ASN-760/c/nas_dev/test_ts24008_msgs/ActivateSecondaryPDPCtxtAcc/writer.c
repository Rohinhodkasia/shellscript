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
   TS24008Msg_ActivateSecondaryPDPCtxtAcc data;
   TS24008Msg_ActivateSecondaryPDPCtxtAcc* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_ActivateSecondaryPDPCtxtAcc;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_ActivateSecondaryPDPCtxtAcc;
   pdu.data.u.obj_ActivateSecondaryPDPCtxtAcc = pvalue;

   asn1Init_TS24008Msg_ActivateSecondaryPDPCtxtAcc (pvalue);
   pvalue->negotiatedLLCSAPI.spare = 0;
   pvalue->negotiatedLLCSAPI.value = TS24008IE_SAPIValues_unassigned;
   pvalue->negotiatedQOS.length = 7;
   pvalue->negotiatedQOS.spare1 = 0;
   pvalue->negotiatedQOS.delayClass = 1;
   pvalue->negotiatedQOS.reliabilityClass = 0;
   pvalue->negotiatedQOS.peakThroughput = 5;
   pvalue->negotiatedQOS.spare2 = 0;
   pvalue->negotiatedQOS.precedenceClass = 6;
   pvalue->negotiatedQOS.spare3 = 0;
   pvalue->negotiatedQOS.meanThroughput = 22;
   pvalue->negotiatedQOS.trafficClass = 6;
   pvalue->negotiatedQOS.deliveryOrder = 0;
   pvalue->negotiatedQOS.deliveryErroneousSDU = 5;
   pvalue->negotiatedQOS.maxSDUSize = 102;
   pvalue->negotiatedQOS.maxUplinkBR = 126;
   pvalue->negotiatedQOS.maxDownlinkBR = 184;
   pvalue->negotiatedQOS.residualBER = 3;
   pvalue->negotiatedQOS.sduErrorRatio = 11;
   pvalue->negotiatedQOS.transferDelay = 52;
   pvalue->negotiatedQOS.trafficHandlingPrio = 1;
   pvalue->negotiatedQOS.guaranteedUplinkBR = 239;
   pvalue->negotiatedQOS.guaranteedDownlinkBR = 250;
   pvalue->negotiatedQOS.spare4 = 0;
   pvalue->negotiatedQOS.signallingIndication = 1;
   pvalue->negotiatedQOS.sourceStatsDescriptor = 13;
   pvalue->negotiatedQOS.extBitRate.n = 4;
   pvalue->negotiatedQOS.extBitRate.elem[0] = 144;
   pvalue->negotiatedQOS.extBitRate.elem[1] = 8;
   pvalue->negotiatedQOS.extBitRate.elem[2] = 0;
   pvalue->negotiatedQOS.extBitRate.elem[3] = 80;
   pvalue->radioPriority.value = 1;
   pvalue->m.packetFlowIdentPresent = 1;
   pvalue->packetFlowIdent.spare = 0;
   pvalue->packetFlowIdent.value = 35;
   pvalue->m.protocolConfigOptionsPresent = 1;
   pvalue->protocolConfigOptions.length = 214;
   pvalue->protocolConfigOptions.octet3.spare = 13;
   pvalue->protocolConfigOptions.octet3.configProtocol = 1;

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
