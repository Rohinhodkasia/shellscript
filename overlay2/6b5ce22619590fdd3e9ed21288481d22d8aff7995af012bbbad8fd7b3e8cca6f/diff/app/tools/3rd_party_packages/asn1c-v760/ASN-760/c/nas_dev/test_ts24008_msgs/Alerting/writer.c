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
   TS24008Msg_Alerting data;
   TS24008Msg_Alerting* pvalue = &data;
   OSCTXT	ctxt;
   OSCTXT*	pctxt = &ctxt;
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
   pdu.msgType = ASN1V_mt_Alerting;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_Alerting;
   pdu.data.u.obj_Alerting = pvalue;

   asn1Init_TS24008Msg_Alerting (pvalue);
   pvalue->m.facilityPresent = 1;
   pvalue->facility.numocts = 1;
   pvalue->facility.data = (OSOCTET*) rtxMemAlloc (pctxt, 1);
   {
      static const OSOCTET testdata[] = {
      0xa6 };
      OSCRTLMEMCPY ((void*)pvalue->facility.data, testdata, 1);
   }
   pvalue->m.progressIndPresent = 1;
   pvalue->progressInd.octet3.codingStandard = TS24008IE_CodingStandard_q931;
   pvalue->progressInd.octet3.location = TS24008IE_PILocation_beyond;
   pvalue->progressInd.description = 58;
   pvalue->m.user_userPresent = 1;
   pvalue->user_user.uupd = 139;
   pvalue->user_user.m.uuInfoPresent = 1;
   pvalue->user_user.uuInfo.numocts = 7;
   pvalue->user_user.uuInfo.data = (OSOCTET*) rtxMemAlloc (pctxt, 7);
   {
      static const OSOCTET testdata[] = {
      0x15, 0x1e, 0x96, 0x4c, 0x08, 0x52, 0x78 };
      OSCRTLMEMCPY ((void*)pvalue->user_user.uuInfo.data, testdata, 7);
   }
   pvalue->m.ssVersionPresent = 1;
   pvalue->ssVersion.numocts = 19;
   pvalue->ssVersion.data = (OSOCTET*) rtxMemAlloc (pctxt, 19);
   {
      static const OSOCTET testdata[] = {
      0x4a, 0x4e, 0xc0, 0x24, 0x4f, 0x7b, 0x25, 0xbb,
      0x36, 0x6c, 0xf2, 0xc9, 0x1f, 0x15, 0x06, 0x5a,
      0xc9, 0xcc, 0x45 };
      OSCRTLMEMCPY ((void*)pvalue->ssVersion.data, testdata, 19);
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
