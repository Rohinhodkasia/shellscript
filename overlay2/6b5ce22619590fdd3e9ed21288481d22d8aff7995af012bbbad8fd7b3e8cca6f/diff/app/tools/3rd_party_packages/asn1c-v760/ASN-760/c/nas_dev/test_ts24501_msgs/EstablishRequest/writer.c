#include "TS24501Msgs.h"
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
   TS24501Msg_PDU pdu;
   TS24501Msg_EstablishRequest data;
   TS24501Msg_EstablishRequest* pvalue = &data;
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
      printf ("rtInitContext failed; status = %d\n", ret);
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

   asn1Init_TS24501Msg_PDU (&pdu);
#if 1
   pdu.m.secHdrPresent = 0;
#else
   pdu.m.secHdrPresent = 1;
   pdu.secHdr.protoDiscr = TS24501Msg_NAS5GProtoDiscr_mobMgmt5G;
   pdu.secHdr.secHdrType = TS24501Msg_NAS5GSecHdrType_integProt;
   pdu.secHdr.msgAuthCode = 7000;
   pdu.secHdr.seqNumber  = 140;
#endif
   pdu.protoDiscr = TS24501Msg_NAS5GProtoDiscr_sessMgmt5G;
   pdu.hdrData.u.sm.pduSessIdent = TS24501Msg_PDUSessionIdentity_pduId8;
   pdu.hdrData.u.sm.procTransIdent = 3;

   asn1SetTC_TS24501Msg_PDU_obj_EstablishRequest5G (&ctxt, &pdu, pvalue);

   asn1Init_TS24501Msg_EstablishRequest (pvalue);

   pvalue->integProtMaxRate.maxUEDataRateUplink = 0;
   pvalue->integProtMaxRate.maxUEDataRateDownlink = 255;   

   pvalue->m.pduSessionTypePresent = 1;
   pvalue->pduSessionType.sessionType = TS24501IE_SessionType_st_ipv4v6;

   pvalue->m.sscModePresent = 1;
   pvalue->sscMode.sscMode = TS24501IE_SSCModeValue_ssc_mode3;

   pvalue->m.capabilityPresent = 1;
   pvalue->capability.length = 0; /* Calculated automatically */
   pvalue->capability.tpmic = 1;
   pvalue->capability.atsll = TS24501IE_ATSSSModes_activeOnly;
   pvalue->capability.epts1 = 0;
   pvalue->capability.mh6Pdu = 1;
   pvalue->capability.rqos = 0;
   pvalue->capability.m.octet4Present = 1;
   pvalue->capability.octet4.nonDefQosRule = 1;

   pvalue->m.maxPktFiltersPresent = 1;
   pvalue->maxPktFilters.maxFilters = 185;

   pvalue->m.extProtoCfgOptsPresent = 1;
   pvalue->extProtoCfgOpts.octet4.configProtocol = 0;

   pvalue->m._v16ExtPresent = TRUE;

   OSCRTLMEMSET(&pvalue->headerCompressionCfg, 0,
                sizeof(TS24501IE_HeaderCompressionConfig));
   pvalue->m.headerCompressionCfgPresent = TRUE;
   pvalue->headerCompressionCfg.length = 0;
   pvalue->headerCompressionCfg.p0x0104 = TRUE;
   pvalue->headerCompressionCfg.p0x0102 = TRUE;
   pvalue->headerCompressionCfg.p0x0004 = TRUE;
   pvalue->headerCompressionCfg.p0x0002 = TRUE;
   pvalue->headerCompressionCfg.maxCID[0] = 0xef;
   pvalue->headerCompressionCfg.maxCID[1] = 0x01;
   pvalue->headerCompressionCfg.m.addlCompressParamsTypePresent = 1;
   pvalue->headerCompressionCfg.addlCompressParamsType = 4;
   pvalue->headerCompressionCfg.m.addlCompressParamsContainerPresent = 1;
   pvalue->headerCompressionCfg.addlCompressParamsContainer.numocts = 1;
   pvalue->headerCompressionCfg.addlCompressParamsContainer.data =
                 (OSOCTET *)rtxMemAlloc(&ctxt, 1);
   {
      static const OSOCTET testdata[] = { 0x34 };
      OSCRTLSAFEMEMCPY(
        (void *)pvalue->headerCompressionCfg.addlCompressParamsContainer.data, 1, testdata, 1);
   }

   pvalue->m.dsttPortMacAddrPresent = TRUE;
   pvalue->dsttPortMacAddr.length = 0; /* Calculated automatically */
   pvalue->dsttPortMacAddr.contents[0] = 0xab;
   pvalue->dsttPortMacAddr.contents[1] = 0xcd;
   pvalue->dsttPortMacAddr.contents[2] = 0x23;
   pvalue->dsttPortMacAddr.contents[3] = 0x45;
   pvalue->dsttPortMacAddr.contents[4] = 0x67;
   pvalue->dsttPortMacAddr.contents[5] = 0x89;

   pvalue->m.portMgmtInfoContainerPresent = TRUE;
   pvalue->portMgmtInfoContainer.length = 0;  /* Calculated automatically */
   pvalue->portMgmtInfoContainer.container.numocts = 1;
   pvalue->portMgmtInfoContainer.container.data = (OSOCTET *)rtxMemAlloc(&ctxt, 1);
   {
      static const OSOCTET testdata[] = { 0xff };
      OSCRTLSAFEMEMCPY(
        (void *)pvalue->portMgmtInfoContainer.container.data, 1, testdata, 1);
   }

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24501Msg_PDU (&ctxt, &pdu);
   if (0 != ret) {
      printf ("encode PDU failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "");
      printf ("\n");
      rtxFreeContext (&ctxt);
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
