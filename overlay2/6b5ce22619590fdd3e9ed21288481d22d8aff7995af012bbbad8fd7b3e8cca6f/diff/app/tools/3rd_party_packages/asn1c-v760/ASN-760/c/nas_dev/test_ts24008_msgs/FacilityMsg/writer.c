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
   TS24008Msg_FacilityMsg data;
   TS24008Msg_FacilityMsg* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_FacilityMsg;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_FacilityMsg;
   pdu.data.u.obj_FacilityMsg = pvalue;

   asn1Init_TS24008Msg_FacilityMsg (pvalue);

   pvalue->facility.numocts = 18;
   pvalue->facility.data = (OSOCTET*) rtxMemAlloc (&ctxt, 18);
   {
      static const OSOCTET testdata[] = {
      0xc8, 0x9f, 0x94, 0x4e, 0x0c, 0x2a, 0x32, 0x09,
      0xb6, 0x58, 0xd4, 0x54, 0x6e, 0xbf, 0xfc, 0xc0,
      0x18, 0x18 };
      OSCRTLMEMCPY ((void*)pvalue->facility.data, testdata, 18);
   }

   pvalue->m.ssVersionPresent = 1;
   pvalue->ssVersion.numocts = 9;
   pvalue->ssVersion.data = (OSOCTET*) rtxMemAlloc (&ctxt, 9);
   {
      static const OSOCTET testdata[] = {
      0x94, 0x73, 0x44, 0x84, 0x73, 0x94, 0xb9, 0xee,
      0x62 };
      OSCRTLMEMCPY ((void*)pvalue->ssVersion.data, testdata, 9);
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
