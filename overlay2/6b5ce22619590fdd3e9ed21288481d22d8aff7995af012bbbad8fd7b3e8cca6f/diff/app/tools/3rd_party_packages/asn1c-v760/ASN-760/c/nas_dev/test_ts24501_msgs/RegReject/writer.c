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
   TS24501Msg_RegReject data;
   TS24501Msg_RegReject* pvalue = &data;
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
   pdu.m.secHdrPresent = 1;
   pdu.secHdr.protoDiscr = TS24501Msg_NAS5GProtoDiscr_mobMgmt5G;
   pdu.secHdr.secHdrType = TS24501Msg_NAS5GSecHdrType_integProtAnd5GSecCtxt;
   pdu.secHdr.msgAuthCode = 3000;
   pdu.secHdr.seqNumber = 3;
   pdu.hdrData.u.mm.secHdrType = TS24501Msg_NAS5GSecHdrType_noSec;

   asn1SetTC_TS24501Msg_PDU_obj_RegReject5G (&ctxt, &pdu, pvalue);

   asn1Init_TS24501Msg_RegReject (pvalue);

   pvalue->cause = 3;

   pvalue->m.t3346Present = 1;
   pvalue->t3346.value.unit = 1;
   pvalue->t3346.value.timerValue = 10;

   pvalue->m.t3502Present = 1;
   pvalue->t3502.value.unit = 2;
   pvalue->t3502.value.timerValue = 13;

   pvalue->m.eapMessagePresent = 1;
   pvalue->eapMessage.length = 0; // Calculated automatically...
   pvalue->eapMessage.packetFormat.code = TS24501IE_EAPFormatCode_failure;
   pvalue->eapMessage.packetFormat.id = 5;
   pvalue->eapMessage.packetFormat.length = 8;
   pvalue->eapMessage.packetFormat.data.numocts = 4;
   pvalue->eapMessage.packetFormat.data.data = (OSOCTET*) rtxMemAlloc(&ctxt, 4);
   {
      static const OSOCTET tmpdata[] = { 0x70, 0xc6, 0x63, 0x38};
      OSCRTLSAFEMEMCPY((void*)pvalue->eapMessage.packetFormat.data.data, 4, tmpdata, 4);
   }

   pvalue->m._v17ExtPresent = 1;
   pvalue->m.extRejectedNSSAIPresent = 1;
   pvalue->extRejectedNSSAI.length = 0; // Calculated automatically...
   
   pvalue->extRejectedNSSAI.rejectedNSSAI.n = 1;
   pvalue->extRejectedNSSAI.rejectedNSSAI.elem[0].spare = 0;
   pvalue->extRejectedNSSAI.rejectedNSSAI.elem[0].listType = TS24501IE_PERNTypes_pernWithoutTimer;
   pvalue->extRejectedNSSAI.rejectedNSSAI.elem[0].numElems = 1;
   pvalue->extRejectedNSSAI.rejectedNSSAI.elem[0].rejectedSNSSAI.n = 1;
   pvalue->extRejectedNSSAI.rejectedNSSAI.elem[0].rejectedSNSSAI.elem[0].length = 8;
   pvalue->extRejectedNSSAI.rejectedNSSAI.elem[0].rejectedSNSSAI.elem[0].cause = TS24501IE_ExtRejectedNSSAI_cause_unavailInCurrPlmn;
   pvalue->extRejectedNSSAI.rejectedNSSAI.elem[0].rejectedSNSSAI.elem[0].sst = 155;
   pvalue->extRejectedNSSAI.rejectedNSSAI.elem[0].rejectedSNSSAI.elem[0].m.sdPresent = 1;
   pvalue->extRejectedNSSAI.rejectedNSSAI.elem[0].rejectedSNSSAI.elem[0].sd = 56000;
   pvalue->extRejectedNSSAI.rejectedNSSAI.elem[0].rejectedSNSSAI.elem[0].m.mappedSSTPresent = 1;
   pvalue->extRejectedNSSAI.rejectedNSSAI.elem[0].rejectedSNSSAI.elem[0].mappedSST[0] = 0xab;
   pvalue->extRejectedNSSAI.rejectedNSSAI.elem[0].rejectedSNSSAI.elem[0].m.mappedSDPresent = 1;
   pvalue->extRejectedNSSAI.rejectedNSSAI.elem[0].rejectedSNSSAI.elem[0].mappedSD[0] = 0xcd;
   pvalue->extRejectedNSSAI.rejectedNSSAI.elem[0].rejectedSNSSAI.elem[0].mappedSD[1] = 0xef;
   pvalue->extRejectedNSSAI.rejectedNSSAI.elem[0].rejectedSNSSAI.elem[0].mappedSD[2] = 0x01;

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
