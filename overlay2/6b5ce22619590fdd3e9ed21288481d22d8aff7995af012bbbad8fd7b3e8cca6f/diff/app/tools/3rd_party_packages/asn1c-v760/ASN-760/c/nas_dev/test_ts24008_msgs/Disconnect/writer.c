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
   TS24008Msg_Disconnect data;
   TS24008Msg_Disconnect* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_Disconnect;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_Disconnect;
   pdu.data.u.obj_Disconnect = pvalue;

   asn1Init_TS24008Msg_Disconnect (pvalue);
   pvalue->cause.octet3.codingStandard = TS24008IE_CodingStandard_q931;
   pvalue->cause.octet3.spare = 0;
   pvalue->cause.octet3.location = TS24008IE_Location_user;
   pvalue->cause.m.recommendationPresent = 1;
   pvalue->cause.recommendation = 56;
   pvalue->cause.causeValue = 70;

   pvalue->m.facilityPresent = 1;
   pvalue->facility.numocts = 9;
   pvalue->facility.data = (OSOCTET*) rtxMemAlloc (&ctxt, 9);
   {
      static const OSOCTET testdata[] = {
      0xa9, 0x8e, 0x23, 0xec, 0xb9, 0x45, 0x3f, 0xe0,
      0xde };
      OSCRTLMEMCPY ((void*)pvalue->facility.data, testdata, 9);
   }
   pvalue->m.progressIndPresent = 1;
   pvalue->progressInd.length = 211;
   pvalue->progressInd.octet3.codingStandard = TS24008IE_CodingStandard_q931;
   pvalue->progressInd.octet3.spare = 0;
   pvalue->progressInd.octet3.location = TS24008IE_PILocation_user;
   pvalue->progressInd.description = 85;
   pvalue->m.user_userPresent = 1;
   pvalue->user_user.length = 120;
   pvalue->user_user.uupd = 128;
   pvalue->user_user.m.uuInfoPresent = 1;
   pvalue->user_user.uuInfo.numocts = 1;
   pvalue->user_user.uuInfo.data = (OSOCTET*) rtxMemAlloc (&ctxt, 1);
   {
      static const OSOCTET testdata[] = {
      0xdb };
      OSCRTLMEMCPY ((void*)pvalue->user_user.uuInfo.data, testdata, 1);
   }
   pvalue->m.allowedActionsPresent = 1;
   pvalue->allowedActions.ccbs_activation = 0;
   pvalue->allowedActions.spare = 41;
   pvalue->m.ssVersionPresent = 1;
   pvalue->ssVersion.numocts = 17;
   pvalue->ssVersion.data = (OSOCTET*) rtxMemAlloc (&ctxt, 17);
   {
      static const OSOCTET testdata[] = {
      0x35, 0x17, 0xa3, 0xeb, 0xef, 0x21, 0x28, 0x85,
      0x1d, 0x83, 0xce, 0x19, 0x7f, 0x56, 0x5b, 0xeb,
      0xe1 };
      OSCRTLMEMCPY ((void*)pvalue->ssVersion.data, testdata, 17);
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
