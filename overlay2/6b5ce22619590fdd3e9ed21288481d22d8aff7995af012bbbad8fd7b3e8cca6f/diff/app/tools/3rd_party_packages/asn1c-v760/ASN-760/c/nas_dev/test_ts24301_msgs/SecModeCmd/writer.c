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
   TS24301Msg_SecModeCmd data;
   TS24301Msg_SecModeCmd* pvalue = &data;
   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN], *msgptr;
   const char*  filename = "message.dat";
   OSSIZE       len;
   int		i, ret;
   OSBOOL verbose = FALSE;
   /* 0123456789abcdef9876543210fedcba */
   OSCrypt128Key integKey = {
      0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
      0x98, 0x76, 0x54, 0x32, 0x10, 0xfe, 0xdc, 0xba
   };
   /* 9876543210fedcba0123456789abcdef */
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
   asn1SetTC_TS24301Msg_PDU_obj_SecModeCmd (&ctxt, &pdu, pvalue);

   asn1Init_TS24301Msg_SecModeCmd (pvalue);

   pvalue->selNASSecurityAlgs.spare1 = 0;
   pvalue->selNASSecurityAlgs.typeOfCiph = TS24301IE_NASSecurityAlgorithms_typeOfCiph_eea0;
   pvalue->selNASSecurityAlgs.spare2 = 1;
   pvalue->selNASSecurityAlgs.typeOfProt = TS24301IE_NASSecurityAlgorithms_typeOfProt_eia0;
   pvalue->spare = 4;
   pvalue->nasKeySetIdentifier.tsc = 0;
   pvalue->nasKeySetIdentifier.ident = 0;
   pvalue->replayedUESecurityCapabilities.length = 5;
   pvalue->replayedUESecurityCapabilities.epsEncryptAlgs.eea0 = 0;
   pvalue->replayedUESecurityCapabilities.epsEncryptAlgs.x128_eea1 = 1;
   pvalue->replayedUESecurityCapabilities.epsEncryptAlgs.x128_eea2 = 0;
   pvalue->replayedUESecurityCapabilities.epsEncryptAlgs.eea3 = 1;
   pvalue->replayedUESecurityCapabilities.epsEncryptAlgs.eea4 = 1;
   pvalue->replayedUESecurityCapabilities.epsEncryptAlgs.eea5 = 0;
   pvalue->replayedUESecurityCapabilities.epsEncryptAlgs.eea6 = 0;
   pvalue->replayedUESecurityCapabilities.epsEncryptAlgs.eea7 = 1;

   pvalue->replayedUESecurityCapabilities.epsIntegAlgs.eia0 = 0;
   pvalue->replayedUESecurityCapabilities.epsIntegAlgs.eia1 = 0;
   pvalue->replayedUESecurityCapabilities.epsIntegAlgs.eia2 = 1;
   pvalue->replayedUESecurityCapabilities.epsIntegAlgs.eia3 = 1;
   pvalue->replayedUESecurityCapabilities.epsIntegAlgs.eia4 = 0;
   pvalue->replayedUESecurityCapabilities.epsIntegAlgs.eia5 = 1;
   pvalue->replayedUESecurityCapabilities.epsIntegAlgs.eia6 = 0;
   pvalue->replayedUESecurityCapabilities.epsIntegAlgs.eia7 = 1;

   if (pvalue->replayedUESecurityCapabilities.m.umtsEncryptAlgsPresent) {
      pvalue->replayedUESecurityCapabilities.umtsEncryptAlgs.uea0 = 1;
      pvalue->replayedUESecurityCapabilities.umtsEncryptAlgs.uea1 = 0;
      pvalue->replayedUESecurityCapabilities.umtsEncryptAlgs.uea2 = 1;
      pvalue->replayedUESecurityCapabilities.umtsEncryptAlgs.uea3 = 0;
      pvalue->replayedUESecurityCapabilities.umtsEncryptAlgs.uea4 = 0;
      pvalue->replayedUESecurityCapabilities.umtsEncryptAlgs.uea5 = 1;
      pvalue->replayedUESecurityCapabilities.umtsEncryptAlgs.uea6 = 0;
      pvalue->replayedUESecurityCapabilities.umtsEncryptAlgs.uea7 = 0;
   }

   if (pvalue->replayedUESecurityCapabilities.m.octet6Present) {
      pvalue->replayedUESecurityCapabilities.octet6.spare = 1;
      pvalue->replayedUESecurityCapabilities.octet6.umtsIntegAlgs.uia1 = 0;
      pvalue->replayedUESecurityCapabilities.octet6.umtsIntegAlgs.uia2 = 1;
      pvalue->replayedUESecurityCapabilities.octet6.umtsIntegAlgs.uia3 = 0;
      pvalue->replayedUESecurityCapabilities.octet6.umtsIntegAlgs.uia4 = 0;
      pvalue->replayedUESecurityCapabilities.octet6.umtsIntegAlgs.uia5 = 0;
      pvalue->replayedUESecurityCapabilities.octet6.umtsIntegAlgs.uia6 = 1;
      pvalue->replayedUESecurityCapabilities.octet6.umtsIntegAlgs.uia7 = 1;
   }

   if (pvalue->replayedUESecurityCapabilities.m.octet7Present) {
      pvalue->replayedUESecurityCapabilities.octet7.spare = 1;
      pvalue->replayedUESecurityCapabilities.octet7.gprsIntegAlgs.gea1 = 1;
      pvalue->replayedUESecurityCapabilities.octet7.gprsIntegAlgs.gea2 = 0;
      pvalue->replayedUESecurityCapabilities.octet7.gprsIntegAlgs.gea3 = 1;
      pvalue->replayedUESecurityCapabilities.octet7.gprsIntegAlgs.gea4 = 1;
      pvalue->replayedUESecurityCapabilities.octet7.gprsIntegAlgs.gea5 = 1;
      pvalue->replayedUESecurityCapabilities.octet7.gprsIntegAlgs.gea6 = 1;
      pvalue->replayedUESecurityCapabilities.octet7.gprsIntegAlgs.gea7 = 1;
   }

   pvalue->m.imeisvRequestPresent = 1;
   pvalue->imeisvRequest.spare = 0;
   pvalue->imeisvRequest.value = 5;

   pvalue->m.replayedNoncePresent = 1;
   {
      static const OSOCTET testdata[] = {
      0xc9, 0x80, 0x0a, 0x21 };
      OSCRTLMEMCPY ((void*)pvalue->replayedNonce.data, testdata, 4);
   }

   pvalue->m.noncePresent = 1;
   {
      static const OSOCTET testdata[] = {
      0x44, 0xcd, 0x17, 0x10 };
      OSCRTLMEMCPY ((void*)pvalue->nonce.data, testdata, 4);
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
