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
   TS24008Msg_DeactivatePDPCtxtReq data;
   TS24008Msg_DeactivatePDPCtxtReq* pvalue = &data;
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


   asn1Init_TS24008Msg_PDU (&pdu);
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_sessMgmt;
   pdu.msgType = ASN1V_mt_DeactivatePDPCtxtReq;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_DeactivatePDPCtxtReq;
   pdu.data.u.obj_DeactivatePDPCtxtReq = pvalue;

   asn1Init_TS24008Msg_DeactivatePDPCtxtReq (pvalue);

   pvalue->smCause = 20;

   pvalue->m.tearDownIndicatorPresent = 1;
   pvalue->tearDownIndicator.tdiFlag = FALSE;

   pvalue->m.protocolConfigOptionsPresent = 1;
   pvalue->protocolConfigOptions.octet3.configProtocol = 6;

   pvalue->m.mbmsPCOPresent = 1;
   pvalue->mbmsPCO.numocts = 17;
   pvalue->mbmsPCO.data = (OSOCTET*) rtxMemAlloc (&ctxt, 17);
   {
      static const OSOCTET testdata[] = {
      0x74, 0xdd, 0x14, 0xa3, 0x76, 0x7a, 0xae, 0xe3,
      0x5e, 0x3a, 0xaf, 0xb6, 0x22, 0x09, 0x9d, 0xee,
      0xd3 };
      OSCRTLMEMCPY ((void*)pvalue->mbmsPCO.data, testdata, 17);
   }

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24008Msg_PDU (&ctxt, &pdu);

   if (verbose) {
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "");
      printf ("\n");
   }

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
