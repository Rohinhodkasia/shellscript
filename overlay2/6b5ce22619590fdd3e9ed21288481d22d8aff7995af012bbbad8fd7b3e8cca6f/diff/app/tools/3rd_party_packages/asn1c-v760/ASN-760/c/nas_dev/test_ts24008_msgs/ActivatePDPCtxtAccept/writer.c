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
   TS24008Msg_ActivatePDPCtxtAccept data;
   TS24008Msg_ActivatePDPCtxtAccept* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_ActivatePDPCtxtAccept;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_ActivatePDPCtxtAccept;
   pdu.data.u.obj_ActivatePDPCtxtAccept = pvalue;

   asn1Init_TS24008Msg_ActivatePDPCtxtAccept (pvalue);
   pvalue->negotiatedLLCSAPI.spare = 0;
   pvalue->negotiatedLLCSAPI.value = TS24008IE_SAPIValues_sapi5;
   pvalue->negotiatedQOS.spare1 = 0;
   pvalue->negotiatedQOS.delayClass = 5;
   pvalue->negotiatedQOS.reliabilityClass = 3;
   pvalue->negotiatedQOS.peakThroughput = 2;
   pvalue->negotiatedQOS.spare2 = 0;
   pvalue->negotiatedQOS.precedenceClass = 3;
   pvalue->negotiatedQOS.spare3 = 1;
   pvalue->negotiatedQOS.meanThroughput = 27;
   pvalue->negotiatedQOS.trafficClass = 2;
   pvalue->negotiatedQOS.deliveryOrder = 0;
   pvalue->negotiatedQOS.deliveryErroneousSDU = 2;
   pvalue->negotiatedQOS.maxSDUSize = 141;
   pvalue->negotiatedQOS.maxUplinkBR = 127;
   pvalue->negotiatedQOS.maxDownlinkBR = 55;
   pvalue->negotiatedQOS.residualBER = 12;
   pvalue->negotiatedQOS.sduErrorRatio = 8;
   pvalue->negotiatedQOS.transferDelay = 44;
   pvalue->negotiatedQOS.trafficHandlingPrio = 0;
   pvalue->negotiatedQOS.guaranteedUplinkBR = 251;
   pvalue->negotiatedQOS.guaranteedDownlinkBR = 172;
   pvalue->negotiatedQOS.spare4 = 5;
   pvalue->negotiatedQOS.signallingIndication = 1;
   pvalue->negotiatedQOS.sourceStatsDescriptor = 2;
   pvalue->negotiatedQOS.extBitRate.n = 4;
   pvalue->negotiatedQOS.extBitRate.elem[0] = 98;
   pvalue->negotiatedQOS.extBitRate.elem[1] = 201;
   pvalue->negotiatedQOS.extBitRate.elem[2] = 53;
   pvalue->negotiatedQOS.extBitRate.elem[3] = 69;
   pvalue->radioPriority.value = 1;
   pvalue->m.pdpAddressPresent = 1;
   pvalue->pdpAddress.spare = 6;
   pvalue->pdpAddress.pdpTypeOrg = 10;
   pvalue->pdpAddress.pdpTypeNum = 193;
   {
      pvalue->pdpAddress.addressInfo.numocts = 0;
   }

   pvalue->m.protocolConfigOptionsPresent = 1;
   pvalue->protocolConfigOptions.octet3.configProtocol = 3;

   pvalue->m.packetFlowIdentPresent = 1;
   pvalue->packetFlowIdent.value = 111;

   pvalue->m.smCausePresent = 1;
   pvalue->smCause = 120;

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
