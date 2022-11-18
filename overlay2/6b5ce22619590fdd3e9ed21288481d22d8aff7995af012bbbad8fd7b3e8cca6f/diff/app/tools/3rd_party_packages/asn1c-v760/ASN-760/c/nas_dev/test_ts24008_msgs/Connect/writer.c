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
   TS24008Msg_Connect data;
   TS24008Msg_Connect* pvalue = &data;
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


   asn1Init_TS24008Msg_PDU (&pdu);
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_callCtrl;
   pdu.msgType = ASN1V_mt_Connect;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_Connect;
   pdu.data.u.obj_Connect = pvalue;

   asn1Init_TS24008Msg_Connect (pvalue);

   pvalue->m.facilityPresent = 1;
   pvalue->facility.numocts = 17;
   pvalue->facility.data = (OSOCTET*) rtxMemAlloc (pctxt, 17);
   {
      static const OSOCTET testdata[] = {
      0xd9, 0xa3, 0x0b, 0xf5, 0xb4, 0x84, 0x9f, 0x5f,
      0x0b, 0x2d, 0x76, 0xef, 0x89, 0xd2, 0x72, 0x2b,
      0x56 };
      OSCRTLMEMCPY ((void*)pvalue->facility.data, testdata, 17);
   }

   pvalue->m.progressIndPresent = 1;
   pvalue->progressInd.octet3.codingStandard = TS24008IE_CodingStandard_q931;
   pvalue->progressInd.octet3.location = TS24008IE_PILocation_privLocal;
   pvalue->progressInd.description = 20;

   pvalue->m.connNumberPresent = 1;
   pvalue->connNumber.octet3.typeOfNumber = TS24008IE_NumberTypes_shortCode;
   pvalue->connNumber.octet3.numberingPlanID = TS24008IE_NumberPlans_national;
   pvalue->connNumber.m.octet3aPresent = 1;
   pvalue->connNumber.octet3a.presentationIndicator = 0;
   pvalue->connNumber.octet3a.spare = 5;
   pvalue->connNumber.octet3a.screeningIndicator = 1;
   pvalue->connNumber.m.numberPresent = 1;
   pvalue->connNumber.number = "b2774";

   pvalue->m.connSubaddrPresent = 1;
   pvalue->connSubaddr.m.octet3Present = 1;
   pvalue->connSubaddr.octet3.typeOfSubaddr = TS24008IE_SubAddressTypes_userSpecified;
   pvalue->connSubaddr.octet3.oddEvenIndicator = 0;
   pvalue->connSubaddr.octet3.spare = 5;

   pvalue->m.user_userPresent = 1;
   pvalue->user_user.uupd = 234;
   pvalue->user_user.m.uuInfoPresent = 1;
   pvalue->user_user.uuInfo.numocts = 9;
   pvalue->user_user.uuInfo.data = (OSOCTET*) rtxMemAlloc (pctxt, 9);
   {
      static const OSOCTET testdata[] = {
      0x80, 0x98, 0xa2, 0x89, 0x9b, 0xd2, 0xe9, 0x31,
      0x29 };
      OSCRTLMEMCPY ((void*)pvalue->user_user.uuInfo.data, testdata, 9);
   }

   pvalue->m.ssVersionPresent = 1;
   pvalue->ssVersion.numocts = 9;
   pvalue->ssVersion.data = (OSOCTET*) rtxMemAlloc (pctxt, 9);
   {
      static const OSOCTET testdata[] = {
      0x3a, 0x28, 0xc2, 0xbc, 0xcc, 0x50, 0x6b, 0xa2,
      0xba };
      OSCRTLMEMCPY ((void*)pvalue->ssVersion.data, testdata, 9);
   }

   pvalue->m.streamIdPresent = 1;
   pvalue->streamId.value = 126;

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
