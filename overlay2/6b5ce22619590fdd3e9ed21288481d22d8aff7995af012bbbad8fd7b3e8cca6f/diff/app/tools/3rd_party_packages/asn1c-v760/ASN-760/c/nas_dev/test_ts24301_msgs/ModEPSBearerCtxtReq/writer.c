#include "TS24301Msgs.h"
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
   TS24301Msg_PDU pdu;
   TS24301Msg_ModEPSBearerCtxtReq data;
   TS24301Msg_ModEPSBearerCtxtReq* pvalue = &data;
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
      printf ("rtxInitContext failed; status = %d\n", ret);
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

   asn1Init_TS24301Msg_PDU (&pdu);

   pdu.m.secHdrPresent = 1;
   pdu.secHdr.secHdrType = TS24007L3_SecHdrType_integProt;
   pdu.secHdr.protoDiscr = TS24007L3_ProtoDiscr_epsMobMgmt;
   pdu.secHdr.msgAuthCode = 12345678;
   pdu.secHdr.seqNumber  = 1;

   pdu.l3HdrOpts.t = T_TS24007L3_L3HdrOptions_epsBearerIdent;
   pdu.l3HdrOpts.u.epsBearerIdent = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_epsSessMgmt;
   pdu.msgType = ASN1V_ts24301Msg_mt_ModEPSBearerCtxtReq;
   pdu.data.t = T_TS24301Msgs_TS24301_IE_OBJECTSET_obj_ModEPSBearerCtxtReq;
   pdu.data.u.obj_ModEPSBearerCtxtReq = pvalue;

   asn1Init_TS24301Msg_ModEPSBearerCtxtReq (pvalue);

   pvalue->m.newEPSQoSPresent = 1;
   pvalue->newEPSQoS.length = 0; /* length will be calculated */
   pvalue->newEPSQoS.qci = 181;

   pvalue->m.tftPresent = 1;
   pvalue->tft.length = 0; /* length will be calculated */
   pvalue->tft.octet1.tftOperationCode = TS24008IE_TFTOctet1_tftOperationCode_delPktFilters;
   pvalue->tft.octet1.eBit = 1;
   pvalue->tft.octet1.numPacketFilters = 3;
   switch (pvalue->tft.octet1.tftOperationCode) {
      case 5:
         pvalue->tft.packetFilterList.u.identifiers.numocts = 17;
         pvalue->tft.packetFilterList.u.identifiers.data =
            (OSOCTET*) rtxMemAlloc (&ctxt, 17);
         {
            static const OSOCTET testdata[] = {
            0x3f, 0x92, 0x49, 0xd2, 0xa5, 0xc5, 0xa1, 0x02,
            0xce, 0x85, 0x1c, 0x9f, 0x8d, 0x2a, 0x74, 0x71,
            0xf1 };
            OSCRTLMEMCPY ((void*)pvalue->tft.packetFilterList.u.identifiers.data, testdata, 17);
         }
         break;

      default:
         break;

   }

   pvalue->m.newQoSPresent = 1;
   pvalue->newQoS.length = 0; /* length will be calculated */

   pvalue->newQoS.spare1 = 0;
   pvalue->newQoS.delayClass = 0;
   pvalue->newQoS.reliabilityClass = 1;
   pvalue->newQoS.peakThroughput = 12;
   pvalue->newQoS.spare2 = 0;
   pvalue->newQoS.precedenceClass = 4;
   pvalue->newQoS.spare3 = 4;
   pvalue->newQoS.meanThroughput = 30;
   pvalue->newQoS.trafficClass = 1;
   pvalue->newQoS.deliveryOrder = 0;
   pvalue->newQoS.deliveryErroneousSDU = 5;
   pvalue->newQoS.maxSDUSize = 246;
   pvalue->newQoS.maxUplinkBR = 194;
   pvalue->newQoS.maxDownlinkBR = 197;
   pvalue->newQoS.residualBER = 4;
   pvalue->newQoS.sduErrorRatio = 2;
   pvalue->newQoS.transferDelay = 28;
   pvalue->newQoS.trafficHandlingPrio = 0;
   pvalue->newQoS.guaranteedUplinkBR = 225;
   pvalue->newQoS.guaranteedDownlinkBR = 91;
   pvalue->newQoS.spare4 = 6;
   pvalue->newQoS.signallingIndication = 1;
   pvalue->newQoS.sourceStatsDescriptor = 7;

   pvalue->m.negotiatedLLCSAPIPresent = 1;
   pvalue->negotiatedLLCSAPI.spare = 4;
   pvalue->negotiatedLLCSAPI.value = TS24008IE_SAPIValues_sapi9;

   pvalue->m.radioPriorityPresent = 1;
   pvalue->radioPriority.value = 1;

   pvalue->m.packetFlowIdentifierPresent = 1;
   pvalue->packetFlowIdentifier.length = 0;  /* length will be calculated */
   pvalue->packetFlowIdentifier.spare = 0;
   pvalue->packetFlowIdentifier.value = 107;
   pvalue->m.apn_AMBRPresent = 1;
   pvalue->apn_AMBR.length = 4;
   pvalue->apn_AMBR.apnAmbrforDL = 203;
   pvalue->apn_AMBR.apnAmbrforUL = 208;

   pvalue->m.protocolConfigOptionsPresent = 1;
   pvalue->protocolConfigOptions.length = 0; /* length will be calculated */
   pvalue->protocolConfigOptions.octet3.configProtocol = 0;
   pvalue->protocolConfigOptions.octet3.spare = 0;
   pvalue->protocolConfigOptions.pcoUnits.elem = 0;
   pvalue->protocolConfigOptions.pcoUnits.n = 0;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24301Msg_PDU (&ctxt, &pdu);
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
