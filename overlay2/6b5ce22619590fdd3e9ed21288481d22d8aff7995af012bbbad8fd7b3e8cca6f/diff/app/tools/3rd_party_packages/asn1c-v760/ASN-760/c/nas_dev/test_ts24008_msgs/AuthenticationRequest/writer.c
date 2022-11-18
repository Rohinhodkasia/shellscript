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
   TS24008Msg_AuthenticationRequest authRequest;
   TS24008Msg_AuthenticationRequest* pvalue = &authRequest;
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

   asn1Init_TS24008Msg_AuthenticationRequest (&authRequest);
   authRequest.ciphKeySeqNum.value = 1;
   for (i = 0; i < 16; i++) {
      authRequest.authParamRAND.data[i] = (OSOCTET)i;
   }
   authRequest.m.authParamAUTNPresent = 1;
   authRequest.authParamAUTN.length = 16;
   for (i = 0; i < 16; i++) {
      authRequest.authParamAUTN.autn[i] = (OSOCTET)(i + 100);
   }

   asn1Init_TS24008Msg_PDU (&pdu);
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_mobMgmt;
   pdu.msgType = ASN1V_mt_AuthenticationRequest;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_AuthenticationRequest;
   pdu.data.u.obj_AuthenticationRequest = &authRequest;

   asn1Init_TS24008Msg_AuthenticationRequest (pvalue);
   pvalue->ciphKeySeqNum.spare = 0;
   pvalue->ciphKeySeqNum.value = 6;
   pvalue->spare = 10;
   {
      static const OSOCTET testdata[] = {
      0x16, 0xc1, 0x7f, 0x78, 0x59, 0xf2, 0x50, 0xcf,
      0x0d, 0x59, 0x0e, 0x03, 0x7e, 0x78, 0x93, 0x8 };
      OSCRTLMEMCPY ((void*)pvalue->authParamRAND.data, testdata, 16);
   }

   pvalue->m.authParamAUTNPresent = 1;
   pvalue->authParamAUTN.length = 245;
   {
      static const OSOCTET testdata[] = {
      0xbb, 0x23, 0x51, 0xa6, 0xa3, 0x24, 0xac, 0xe3,
      0xc2, 0x02, 0x2d, 0xb0, 0x92, 0xfa, 0x53, 0x1c };
      OSCRTLMEMCPY ((void*)pvalue->authParamAUTN.autn, testdata, 16);
   }

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
