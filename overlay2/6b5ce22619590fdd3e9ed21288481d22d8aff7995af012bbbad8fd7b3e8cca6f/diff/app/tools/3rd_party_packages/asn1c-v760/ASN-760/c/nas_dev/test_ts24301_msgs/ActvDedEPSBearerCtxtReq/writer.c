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
   TS24301Msg_ActvDedEPSBearerCtxtReq data;
   TS24301Msg_ActvDedEPSBearerCtxtReq* pvalue = &data;
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
   pdu.msgType = ASN1V_ts24301Msg_mt_ActvDedEPSBearerCtxtReq;
   pdu.data.t = T_TS24301Msgs_TS24301_IE_OBJECTSET_obj_ActvDedEPSBearerCtxtReq;
   pdu.data.u.obj_ActvDedEPSBearerCtxtReq = pvalue;

   asn1Init_TS24301Msg_ActvDedEPSBearerCtxtReq (pvalue);
   pvalue->spare = 11;
   pvalue->linkedEPSBearerIdent = 10;

   pvalue->epsQoS.length = 0; /* length will be calculated */
   pvalue->epsQoS.qci = 177;

   pvalue->tft.length = 0; /* length will be calculated */
   pvalue->tft.octet1.tftOperationCode = TS24008IE_TFTOctet1_tftOperationCode_delPktFilters;
   pvalue->tft.octet1.eBit = 1;
   pvalue->tft.octet1.numPacketFilters = 3;
   switch (pvalue->tft.octet1.tftOperationCode) {
      /* identifiers */
      case 5:
         /* Populate OCTET STRING variable */
         pvalue->tft.packetFilterList.u.identifiers.numocts = 3;
         pvalue->tft.packetFilterList.u.identifiers.data = (OSOCTET*) rtxMemAlloc (&ctxt, 3);
         {
            static const OSOCTET testdata[] = {
            0x2f, 0xc6, 0x9a };
            OSCRTLMEMCPY ((void*)pvalue->tft.packetFilterList.u.identifiers.data, testdata, 3);
         }
         break;

      /* filterItems */
      default:
         /* Start SEQUENCE OF 1272 (level 3) */
         /* zero elements */
         /* End SEQUENCE OF 1272 */
         break;

   }

   pvalue->m.transIdentPresent = 1;
   pvalue->transIdent.flag = 1;
   pvalue->transIdent.value = 1;

   pvalue->m.negotiatedQoSPresent = 1;
   pvalue->negotiatedQoS.length = 0; /* length will be calculated */

   pvalue->negotiatedQoS.spare1 = 2;
   pvalue->negotiatedQoS.delayClass = 4;
   pvalue->negotiatedQoS.reliabilityClass = 5;
   pvalue->negotiatedQoS.peakThroughput = 14;

   pvalue->negotiatedQoS.spare2 = 0;
   pvalue->negotiatedQoS.precedenceClass = 0;

   pvalue->negotiatedQoS.spare3 = 1;
   pvalue->negotiatedQoS.meanThroughput = 21;
   pvalue->negotiatedQoS.trafficClass = 1;
   pvalue->negotiatedQoS.deliveryOrder = 2;
   pvalue->negotiatedQoS.deliveryErroneousSDU = 4;
   pvalue->negotiatedQoS.maxSDUSize = 91;
   pvalue->negotiatedQoS.maxUplinkBR = 181;
   pvalue->negotiatedQoS.maxDownlinkBR = 162;
   pvalue->negotiatedQoS.residualBER = 1;
   pvalue->negotiatedQoS.sduErrorRatio = 12;
   pvalue->negotiatedQoS.transferDelay = 7;
   pvalue->negotiatedQoS.trafficHandlingPrio = 2;
   pvalue->negotiatedQoS.guaranteedUplinkBR = 181;
   pvalue->negotiatedQoS.guaranteedDownlinkBR = 118;
   pvalue->negotiatedQoS.spare4 = 3;
   pvalue->negotiatedQoS.signallingIndication = 1;
   pvalue->negotiatedQoS.sourceStatsDescriptor = 4;

   pvalue->m.negotiatedLLCSAPIPresent = 1;
   pvalue->negotiatedLLCSAPI.spare = 8;
   pvalue->negotiatedLLCSAPI.value = TS24008IE_SAPIValues_sapi11;

   pvalue->m.radioPriorityPresent = 1;
   pvalue->radioPriority.value = 1;

   pvalue->m.packetFlowIdentifierPresent = 1;
   pvalue->packetFlowIdentifier.length = 0; /* length will be calculated */
   pvalue->packetFlowIdentifier.spare = 0;
   pvalue->packetFlowIdentifier.value = 7;

   pvalue->m.protocolConfigOptionsPresent = 1;
   pvalue->protocolConfigOptions.length = 0; /* length will be calculated */
   pvalue->protocolConfigOptions.octet3.spare = 0;
   pvalue->protocolConfigOptions.octet3.configProtocol = 0;
   pvalue->protocolConfigOptions.pcoUnits.n = 0;
   pvalue->protocolConfigOptions.pcoUnits.elem = 0;

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
