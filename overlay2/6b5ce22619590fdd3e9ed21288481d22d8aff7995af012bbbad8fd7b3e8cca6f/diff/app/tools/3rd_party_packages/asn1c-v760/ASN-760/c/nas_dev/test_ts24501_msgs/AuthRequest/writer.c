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
   TS24501Msg_AuthRequest data;
   TS24501Msg_AuthRequest* pvalue = &data;
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
   pdu.secHdr.secHdrType = TS24501Msg_NAS5GSecHdrType_integProt;
   pdu.secHdr.msgAuthCode = 12345678;
   pdu.secHdr.seqNumber = 1;
   pdu.hdrData.u.mm.secHdrType = TS24501Msg_NAS5GSecHdrType_noSec;
   pdu.hdrData.u.mm.spare1 = 0;

   asn1SetTC_TS24501Msg_PDU_obj_MMAuthRequest5G (&ctxt, &pdu, pvalue);

   asn1Init_TS24501Msg_AuthRequest (pvalue);
   pvalue->nasKeySetIdent.tsc = 1;
   pvalue->nasKeySetIdent.ident = 5;
   pvalue->abba.numocts = 2;
   pvalue->abba.data = (OSOCTET*) rtxMemAlloc(&ctxt, 2);
   {
      static const OSOCTET testdata[] = { 
      0x26, 0xf4 };
      OSCRTLSAFEMEMCPY((void*)pvalue->abba.data, 2, testdata, 2);
   }

   pvalue->m.authParamRANDPresent = 1;
   {
      static const OSOCTET testdata[] = {
      0x21, 0xfe, 0xa6, 0x04, 0xea, 0x84, 0x28, 0x97,
      0xf3, 0xf9, 0x04, 0x7f, 0xa0, 0x20, 0x6c, 0x15 };
      OSCRTLMEMCPY ((void*)pvalue->authParamRAND.data, testdata, 16);
   }

   pvalue->m.authParamAUTNPresent = 1;
   {
      static const OSOCTET testdata[] = {
      0x18, 0xcf, 0x47, 0x8c, 0xe2, 0xaf, 0xc8, 0xfd,
      0x0f, 0xe4, 0xbb, 0x9c, 0x42, 0xd7, 0xa3, 0x66 };
      OSCRTLMEMCPY ((void*)pvalue->authParamAUTN.autn, testdata, 16);
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
