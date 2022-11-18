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
   TS24501Msg_ControlPlaneServReq data;
   TS24501Msg_ControlPlaneServReq* pvalue = &data;
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
   pdu.secHdr.msgAuthCode = 36000;
   pdu.secHdr.seqNumber  = 240;
   pdu.hdrData.u.mm.secHdrType = TS24501Msg_NAS5GSecHdrType_noSec;

   asn1SetTC_TS24501Msg_PDU_obj_ControlPlaneServReq5G (&ctxt, &pdu, pvalue);

   asn1Init_TS24501Msg_ControlPlaneServReq (pvalue);

   pvalue->nasKeySetIdent.tsc = 0;
   pvalue->nasKeySetIdent.ident = 6;

   pvalue->ctrlPlaneServType.value = 4;

   pvalue->m.pduSessionIdPresent = 1;
   pvalue->pduSessionId = 160;

   pvalue->m.releaseAssistIndicationPresent = 1;
   pvalue->releaseAssistIndication.ddx = TS24301IE_ReleaseAssistInd_ddx_ddxSingleDLTrans;

   pvalue->m._v16ExtPresent = TRUE;
   pvalue->m.nasMsgContainerPresent = 1;
   pvalue->nasMsgContainer.length = 0; /* length will be calculated */
   pvalue->nasMsgContainer.contents.data = (OSOCTET *)rtxMemAlloc(&ctxt, 4);
   {
      static const OSOCTET testdata[] = { 
      0xbe, 0x97, 0xf1, 0x28 };
      pvalue->nasMsgContainer.contents.numocts = 4;
      OSCRTLSAFEMEMCPY ((void*)pvalue->nasMsgContainer.contents.data, 4, testdata, 4);
   }

   pvalue->m.ciotSmallDataContainerPresent = 1;
   pvalue->ciotSmallDataContainer.length = 0; /* length will be calculated */
   pvalue->ciotSmallDataContainer.dataType =
               TS24501IE_CIoTDataTypes_ciotCtrlPlaneUserData;
   pvalue->ciotSmallDataContainer.containerContents.u.ctrlPlaneUserData.ddx = 2;
   pvalue->ciotSmallDataContainer.containerContents.u.ctrlPlaneUserData.pduSessionId = 7;
   pvalue->ciotSmallDataContainer.contents.numocts = 4;
   pvalue->ciotSmallDataContainer.contents.data =
               (OSOCTET *)rtxMemAlloc(&ctxt, 4);
   {
      static const OSOCTET testdata[] = { 0xfb, 0xea, 0xd9, 0xc8 };
      OSCRTLSAFEMEMCPY(
        (void *)pvalue->ciotSmallDataContainer.contents.data, 4, testdata, 4);
   }

   pvalue->m._v17ExtPresent = TRUE;
   pvalue->m.allowedPduSessStatPresent = 1;
   OSCRTLMEMSET(&pvalue->allowedPduSessStat.psi, 0,
                sizeof(pvalue->allowedPduSessStat.psi));
   pvalue->allowedPduSessStat.psi.elem[0] = TRUE;
   pvalue->allowedPduSessStat.psi.elem[5] = TRUE;
   pvalue->allowedPduSessStat.psi.elem[10] = TRUE;
   pvalue->allowedPduSessStat.psi.elem[15] = TRUE;

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
