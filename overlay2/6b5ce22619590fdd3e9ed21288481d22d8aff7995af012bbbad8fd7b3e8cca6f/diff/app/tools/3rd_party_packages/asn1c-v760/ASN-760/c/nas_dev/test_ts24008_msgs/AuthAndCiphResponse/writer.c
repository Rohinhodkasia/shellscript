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
   TS24008Msg_AuthAndCiphResponse data;
   TS24008Msg_AuthAndCiphResponse* pvalue = &data;
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

   asn1Init_TS24008Msg_PDU (&pdu);
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_gprsMobMgmt;
   pdu.msgType = ASN1V_mt_AuthAndCiphResponse;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_AuthAndCiphResponse;
   pdu.data.u.obj_AuthAndCiphResponse = pvalue;

   asn1Init_TS24008Msg_AuthAndCiphResponse (pvalue);
   pvalue->spare = 0;
   pvalue->acRefNumber = 5;
   pvalue->m.authRespParamPresent = 1;
   {
      static const OSOCTET testdata[] = {
      0x41, 0x8d, 0x73, 0x73 };
      OSCRTLMEMCPY ((void*)pvalue->authRespParam.data, testdata, 4);
   }

   pvalue->m.imeisvPresent = 1;
   pvalue->imeisv.t =  T_TS24008IE_MobileIdentity_tmgi;
   pvalue->imeisv.u.tmgi.mbmsSessIdInd = 1;
   pvalue->imeisv.u.tmgi.mccMncInd = 1;
   {
      static const OSOCTET testdata[] = {
      0xfa, 0xd0, 0x74 };
      OSCRTLMEMCPY ((void*)pvalue->imeisv.u.tmgi.mbmsServiceID, testdata, 3);
   }
   rtxStrncpy(pvalue->imeisv.u.tmgi.mcc_mnc.mcc,
              sizeof(pvalue->imeisv.u.tmgi.mcc_mnc.mcc), "901", 4);
   rtxStrncpy(pvalue->imeisv.u.tmgi.mcc_mnc.mnc,
              sizeof(pvalue->imeisv.u.tmgi.mcc_mnc.mnc), "87a", 4);
   pvalue->imeisv.u.tmgi.mbmsSessionID = 102;

   pvalue->m.authRespParamExtPresent = 1;
   {
      static const OSOCTET testdata[] = {
      0xca };
      pvalue->authRespParamExt.numocts = 1;
      OSCRTLMEMCPY ((void*)pvalue->authRespParamExt.data, testdata, 1);
   }

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24008Msg_PDU (&ctxt, &pdu);
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
