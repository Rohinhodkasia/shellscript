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
   TS24301Msg_AuthFailure data;
   TS24301Msg_AuthFailure* pvalue = &data;
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

   asn1Init_TS24301Msg_PDU (&pdu);
   pdu.m.secHdrPresent = 1;
   pdu.secHdr.secHdrType = TS24007L3_SecHdrType_integProt;
   pdu.secHdr.protoDiscr = TS24007L3_ProtoDiscr_epsMobMgmt;
   pdu.secHdr.msgAuthCode = 12345678;
   pdu.secHdr.seqNumber  = 1;
   pdu.l3HdrOpts.t = T_TS24007L3_L3HdrOptions_secHdr;
   pdu.l3HdrOpts.u.secHdr = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_epsMobMgmt;
   asn1SetTC_TS24301Msg_PDU_obj_AuthFailure (&ctxt, &pdu, pvalue);

   asn1Init_TS24301Msg_AuthFailure (pvalue);
   pvalue->emmCause = TS24301IE_EMMCause_imsiUnkInHSS;
   pvalue->m.authFailureParamPresent = 1;
   {
      static const OSOCTET testdata[] = {
      0xd9, 0xa8, 0x3b, 0x16, 0xef, 0x11, 0x91, 0xd5,
      0xa7, 0x3d, 0xdc, 0x1e, 0xf0, 0xd };
      OSCRTLMEMCPY ((void*)pvalue->authFailureParam.param, testdata, 14);
   }

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
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "");
      printf ("\n");
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
