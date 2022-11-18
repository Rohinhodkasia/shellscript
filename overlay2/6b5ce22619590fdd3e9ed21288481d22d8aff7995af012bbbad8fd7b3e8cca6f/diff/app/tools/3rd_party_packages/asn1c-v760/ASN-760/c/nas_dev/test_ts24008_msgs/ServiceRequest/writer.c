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
   TS24008Msg_ServiceRequest data;
   TS24008Msg_ServiceRequest* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_ServiceRequest;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_ServiceRequest;
   pdu.data.u.obj_ServiceRequest = pvalue;

   asn1Init_TS24008Msg_ServiceRequest (pvalue);

   pvalue->ciphKeySeqNum.spare = 0;
   pvalue->ciphKeySeqNum.value = 5;
   pvalue->serviceType.spare = 0;
   pvalue->serviceType.value = TS24008IE_ServiceTypeValues_broadcast;
   pvalue->mobileIdentity.t =  T_TS24008IE_MobileIdentity_tmgi;
   pvalue->mobileIdentity.u.tmgi.mbmsSessIdInd = 1;
   pvalue->mobileIdentity.u.tmgi.mccMncInd = 1;
   {
      static const OSOCTET testdata[] = {
      0x4c, 0x49, 0xbb };
      OSCRTLMEMCPY ((void*)pvalue->mobileIdentity.u.tmgi.mbmsServiceID, testdata, 3);
   }
   rtxStrncpy(pvalue->mobileIdentity.u.tmgi.mcc_mnc.mcc,
              sizeof(pvalue->mobileIdentity.u.tmgi.mcc_mnc.mcc), "483", 4);
   rtxStrncpy(pvalue->mobileIdentity.u.tmgi.mcc_mnc.mnc,
              sizeof(pvalue->mobileIdentity.u.tmgi.mcc_mnc.mnc), "523", 4);
   pvalue->mobileIdentity.u.tmgi.mbmsSessionID = 77;

   pvalue->m.pdpContextStatusPresent = 1;
   {
      static const OSOCTET testdata[] = {
      0x72, 0x4f };
      OSCRTLMEMCPY ((void*)pvalue->pdpContextStatus.value, testdata, 2);
   }

   pvalue->m.mbmsContextStatusPresent = 1;
   {
      pvalue->mbmsContextStatus.numocts = 0;
   }

   pvalue->m.uplinkDataStatusPresent = 1;
   {
      static const OSOCTET testdata[] = {
      0x81, 0xc2 };
      OSCRTLMEMCPY ((void*)pvalue->uplinkDataStatus.value, testdata, 2);
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
