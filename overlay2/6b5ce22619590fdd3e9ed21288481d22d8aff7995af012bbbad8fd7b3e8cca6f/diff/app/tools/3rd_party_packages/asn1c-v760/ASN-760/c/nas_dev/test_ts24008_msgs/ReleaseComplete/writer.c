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
   TS24008Msg_ReleaseComplete data;
   TS24008Msg_ReleaseComplete* pvalue = &data;
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
   pdu.protoDiscr = TS24007L3_ProtoDiscr_callCtrl;
   pdu.msgType = ASN1V_mt_ReleaseComplete;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_ReleaseComplete;
   pdu.data.u.obj_ReleaseComplete = pvalue;

   asn1Init_TS24008Msg_ReleaseComplete (pvalue);

   pvalue->m.causePresent = 1;
   pvalue->cause.octet3.codingStandard = TS24008IE_CodingStandard_q931;
   pvalue->cause.octet3.spare = 0;
   pvalue->cause.octet3.location = TS24008IE_Location_user;
   pvalue->cause.m.recommendationPresent = 1;
   pvalue->cause.recommendation = 126;
   pvalue->cause.causeValue = 100;

   pvalue->m.facilityPresent = 1;
   pvalue->facility.numocts = 2;
   pvalue->facility.data = (OSOCTET*) rtxMemAlloc (&ctxt, 2);
   {
      static const OSOCTET testdata[] = {
      0x5b, 0x2c };
      OSCRTLMEMCPY ((void*)pvalue->facility.data, testdata, 2);
   }

   pvalue->m.user_userPresent = 1;
   pvalue->user_user.length = 120;
   pvalue->user_user.uupd = 191;
   pvalue->user_user.m.uuInfoPresent = 1;
   pvalue->user_user.uuInfo.numocts = 6;
   pvalue->user_user.uuInfo.data = (OSOCTET*) rtxMemAlloc (&ctxt, 6);
   {
      static const OSOCTET testdata[] = {
      0xf1, 0x4e, 0x85, 0xc2, 0x3d, 0x70 };
      OSCRTLMEMCPY ((void*)pvalue->user_user.uuInfo.data, testdata, 6);
   }
   /* End SEQUENCE or SET 420 */

   pvalue->m.ssVersionPresent = 1;
   pvalue->ssVersion.numocts = 15;
   pvalue->ssVersion.data = (OSOCTET*) rtxMemAlloc (&ctxt, 15);
   {
      static const OSOCTET testdata[] = {
      0x15, 0x2a, 0x3a, 0x39, 0x1d, 0x4f, 0x60, 0xb8,
      0xd1, 0x95, 0x65, 0x75, 0x8f, 0xc9, 0x97 };
      OSCRTLMEMCPY ((void*)pvalue->ssVersion.data, testdata, 15);
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
