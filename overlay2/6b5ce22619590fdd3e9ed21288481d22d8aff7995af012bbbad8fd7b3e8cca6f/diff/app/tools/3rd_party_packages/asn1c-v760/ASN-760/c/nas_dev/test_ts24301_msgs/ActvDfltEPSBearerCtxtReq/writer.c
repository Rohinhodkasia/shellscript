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
   TS24301Msg_ActvDfltEPSBearerCtxtReq data;
   TS24301Msg_ActvDfltEPSBearerCtxtReq* pvalue = &data;
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
   pdu.msgType = ASN1V_ts24301Msg_mt_ActvDfltEPSBearerCtxtReq;
   pdu.data.t = T_TS24301Msgs_TS24301_IE_OBJECTSET_obj_ActvDfltEPSBearerCtxtReq;
   pdu.data.u.obj_ActvDfltEPSBearerCtxtReq = pvalue;

   asn1Init_TS24301Msg_ActvDfltEPSBearerCtxtReq (pvalue);

   pvalue->epsQoS.length = 0; /* length will be calculated */
   pvalue->epsQoS.qci = 205;

   rtxStrcpy (pvalue->accessPointName, sizeof(pvalue->accessPointName),
              "province1.mnc012.mcc345.gprs");

   pvalue->pdnAddress.length = 0; /* length will be calculated */
   pvalue->pdnAddress.pdnTypeValue = TS24301IE_PDNTypeValue_ipv4;

   {
      static const OSOCTET testdata[] = {
      0x2f, 0x04, 0x32, 0x11 };
      pvalue->pdnAddress.pdnAddrInfo.numocts = 4;
      OSCRTLMEMCPY ((void*)pvalue->pdnAddress.pdnAddrInfo.data, testdata, 4);
   }

   pvalue->m.transIdentPresent = 1;
   pvalue->transIdent.flag = 0;
   pvalue->transIdent.value = 0;

   pvalue->m.negotiatedQoSPresent = 1;
   pvalue->negotiatedQoS.length = 0; /* length will be calculated */
   pvalue->negotiatedQoS.spare1 = 1;
   pvalue->negotiatedQoS.delayClass = 6;
   pvalue->negotiatedQoS.reliabilityClass = 6;
   pvalue->negotiatedQoS.peakThroughput = 3;
   pvalue->negotiatedQoS.spare2 = 0;
   pvalue->negotiatedQoS.precedenceClass = 5;
   pvalue->negotiatedQoS.spare3 = 6;
   pvalue->negotiatedQoS.meanThroughput = 7;
   pvalue->negotiatedQoS.trafficClass = 6;
   pvalue->negotiatedQoS.deliveryOrder = 2;
   pvalue->negotiatedQoS.deliveryErroneousSDU = 1;
   pvalue->negotiatedQoS.maxSDUSize = 0;
   pvalue->negotiatedQoS.maxUplinkBR = 195;
   pvalue->negotiatedQoS.maxDownlinkBR = 198;
   pvalue->negotiatedQoS.residualBER = 11;
   pvalue->negotiatedQoS.sduErrorRatio = 14;
   pvalue->negotiatedQoS.transferDelay = 42;
   pvalue->negotiatedQoS.trafficHandlingPrio = 1;
   pvalue->negotiatedQoS.guaranteedUplinkBR = 130;
   pvalue->negotiatedQoS.guaranteedDownlinkBR = 229;
   pvalue->negotiatedQoS.spare4 = 1;
   pvalue->negotiatedQoS.signallingIndication = 1;
   pvalue->negotiatedQoS.sourceStatsDescriptor = 1;

   pvalue->m.negotiatedLLCSAPIPresent = 1;
   pvalue->negotiatedLLCSAPI.spare = 10;
   pvalue->negotiatedLLCSAPI.value = TS24008IE_SAPIValues_sapi5;

   pvalue->m.radioPriorityPresent = 1;
   pvalue->radioPriority.value = 1;

   pvalue->m.packetFlowIdentifierPresent = 1;
   pvalue->packetFlowIdentifier.length = 0; /* length will be calculated */
   pvalue->packetFlowIdentifier.spare = 0;
   pvalue->packetFlowIdentifier.value = 20;

   pvalue->m.apn_AMBRPresent = 1;
   pvalue->apn_AMBR.length = 0; /* length will be calculated */
   pvalue->apn_AMBR.apnAmbrforDL = 32;
   pvalue->apn_AMBR.apnAmbrforUL = 194;

   pvalue->m.esmCausePresent = 1;
   pvalue->esmCause = TS24301IE_ESMCause_operDeterBarring;

   pvalue->m.protocolConfigOptionsPresent = 1;
   pvalue->protocolConfigOptions.length = 0; /* length will be calculated */
   pvalue->protocolConfigOptions.octet3.configProtocol = 0;
   pvalue->protocolConfigOptions.octet3.spare = 0;
   pvalue->protocolConfigOptions.pcoUnits.elem = 0;
   pvalue->protocolConfigOptions.pcoUnits.n = 0;

   pvalue->m._v10ExtPresent = 1;
   pvalue->m.connectivityTypePresent = 1;
   pvalue->connectivityType = 11;

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
