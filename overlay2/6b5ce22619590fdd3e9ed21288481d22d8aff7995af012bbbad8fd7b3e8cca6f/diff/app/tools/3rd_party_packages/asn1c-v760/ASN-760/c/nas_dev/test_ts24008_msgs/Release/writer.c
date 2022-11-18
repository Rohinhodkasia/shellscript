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
   TS24008Msg_Release data;
   TS24008Msg_Release* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_Release;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_Release;
   pdu.data.u.obj_Release = pvalue;

   asn1Init_TS24008Msg_Release (pvalue);

   pvalue->m.causePresent = 1;
   pvalue->cause.octet3.codingStandard = TS24008IE_CodingStandard_q931;
   pvalue->cause.octet3.spare = 0;
   pvalue->cause.octet3.location = TS24008IE_Location_user;
   pvalue->cause.m.recommendationPresent = 1;
   pvalue->cause.recommendation = 71;
   pvalue->cause.causeValue = 105;

   pvalue->m.secondCausePresent = 1;
   pvalue->secondCause.octet3.codingStandard = TS24008IE_CodingStandard_q931;
   pvalue->secondCause.octet3.spare = 0;
   pvalue->secondCause.octet3.location = TS24008IE_Location_user;
   pvalue->secondCause.m.recommendationPresent = 1;
   pvalue->secondCause.recommendation = 30;
   pvalue->secondCause.causeValue = 101;

   pvalue->m.facilityPresent = 1;
   pvalue->facility.numocts = 11;
   pvalue->facility.data = (OSOCTET*) rtxMemAlloc (&ctxt, 11);
   {
      static const OSOCTET testdata[] = {
      0x09, 0xf6, 0x46, 0xdd, 0xc2, 0x10, 0x79, 0xbf,
      0xc2, 0x4e, 0xf1 };
      OSCRTLMEMCPY ((void*)pvalue->facility.data, testdata, 11);
   }

   pvalue->m.user_userPresent = 1;
   pvalue->user_user.length = 69;
   pvalue->user_user.uupd = 17;
   pvalue->user_user.m.uuInfoPresent = 1;
   pvalue->user_user.uuInfo.numocts = 15;
   pvalue->user_user.uuInfo.data = (OSOCTET*) rtxMemAlloc (&ctxt, 15);
   {
      static const OSOCTET testdata[] = {
      0xd8, 0x2d, 0xf0, 0x34, 0x82, 0x41, 0xf8, 0xec,
      0x13, 0xe5, 0xee, 0xa7, 0x4b, 0xd2, 0x4 };
      OSCRTLMEMCPY ((void*)pvalue->user_user.uuInfo.data, testdata, 15);
   }

   pvalue->m.ssVersionPresent = 1;
   pvalue->ssVersion.numocts = 13;
   pvalue->ssVersion.data = (OSOCTET*) rtxMemAlloc (&ctxt, 13);
   {
      static const OSOCTET testdata[] = {
      0x39, 0x3a, 0xd2, 0xc1, 0xdb, 0xe5, 0xcc, 0x02,
      0x04, 0x44, 0xec, 0x46, 0xd8 };
      OSCRTLMEMCPY ((void*)pvalue->ssVersion.data, testdata, 13);
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
