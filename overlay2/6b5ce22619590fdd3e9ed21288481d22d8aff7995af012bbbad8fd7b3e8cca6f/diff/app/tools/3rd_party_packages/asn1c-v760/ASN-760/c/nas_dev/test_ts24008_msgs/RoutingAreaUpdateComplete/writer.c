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
   TS24008Msg_RoutingAreaUpdateComplete data;
   TS24008Msg_RoutingAreaUpdateComplete* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_RoutingAreaUpdateComplete;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_RoutingAreaUpdateComplete;
   pdu.data.u.obj_RoutingAreaUpdateComplete = pvalue;

   asn1Init_TS24008Msg_RoutingAreaUpdateComplete (pvalue);

   pvalue->m.receiveNPDUNumberListPresent = 1;
   pvalue->receiveNPDUNumberList.length = 3;
   pvalue->receiveNPDUNumberList.receiveNPDUNumber.n = 2;
   pvalue->receiveNPDUNumberList.receiveNPDUNumber.elem =
      rtxMemAllocArrayZ (&ctxt, 2, TS24008IE_ReceiveNPDUNumber);
   pvalue->receiveNPDUNumberList.receiveNPDUNumber.elem[0].nsapi = 5;
   pvalue->receiveNPDUNumberList.receiveNPDUNumber.elem[0].numberValue = 126;
   pvalue->receiveNPDUNumberList.receiveNPDUNumber.elem[1].nsapi = 7;
   pvalue->receiveNPDUNumberList.receiveNPDUNumber.elem[1].numberValue = 226;

   pvalue->m.interRATInfoContainerPresent = 1;
   {
      static const OSOCTET testdata[] = {
      0xb };
      pvalue->interRATInfoContainer.numocts = 1;
      OSCRTLMEMCPY ((void*)pvalue->interRATInfoContainer.data, testdata, 1);
   }

   pvalue->m.eUTRANInterRATInfoContainerPresent = 1;
   pvalue->eUTRANInterRATInfoContainer.numocts = 4;
   pvalue->eUTRANInterRATInfoContainer.data = (OSOCTET*) rtxMemAlloc (&ctxt, 4);
   {
      static const OSOCTET testdata[] = {
      0x16, 0x71, 0x53, 0x4b };
      OSCRTLMEMCPY ((void*)pvalue->eUTRANInterRATInfoContainer.data, testdata, 4);
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
