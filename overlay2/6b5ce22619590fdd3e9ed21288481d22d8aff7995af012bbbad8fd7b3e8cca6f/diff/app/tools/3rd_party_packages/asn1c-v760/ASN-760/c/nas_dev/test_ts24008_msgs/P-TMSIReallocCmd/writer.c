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
   TS24008Msg_P_TMSIReallocCmd data;
   TS24008Msg_P_TMSIReallocCmd* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_P_TMSIReallocCmd;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_P_TMSIReallocCmd;
   pdu.data.u.obj_P_TMSIReallocCmd = pvalue;

   asn1Init_TS24008Msg_P_TMSIReallocCmd (pvalue);

   pvalue->allocatedPTMSI.t =  T_TS24008IE_MobileIdentity_tmgi;
   pvalue->allocatedPTMSI.u.tmgi.mbmsSessIdInd = 1;
   pvalue->allocatedPTMSI.u.tmgi.mccMncInd = 1;
   {
      static const OSOCTET testdata[] = {
      0x40, 0xee, 0xbb };
      OSCRTLMEMCPY ((void*)pvalue->allocatedPTMSI.u.tmgi.mbmsServiceID, testdata, 3);
   }

   rtxStrncpy(pvalue->allocatedPTMSI.u.tmgi.mcc_mnc.mcc,
              sizeof(pvalue->allocatedPTMSI.u.tmgi.mcc_mnc.mcc), "369", 4);
   rtxStrncpy(pvalue->allocatedPTMSI.u.tmgi.mcc_mnc.mnc,
              sizeof(pvalue->allocatedPTMSI.u.tmgi.mcc_mnc.mnc), "166", 4);
   pvalue->allocatedPTMSI.u.tmgi.mbmsSessionID = 102;

   rtxStrncpy(pvalue->routingAreaIdent.mcc_mnc.mcc,
              sizeof(pvalue->routingAreaIdent.mcc_mnc.mcc), "#a1", 4);
   rtxStrncpy(pvalue->routingAreaIdent.mcc_mnc.mnc,
              sizeof(pvalue->routingAreaIdent.mcc_mnc.mnc), "6c9", 4);
   pvalue->routingAreaIdent.lac = 8670;
   pvalue->routingAreaIdent.rac = 160;

   pvalue->forceToStandby.spare = 0;
   pvalue->forceToStandby.value = 3;

   pvalue->m.pTMSISignaturePresent = 1;
   {
      static const OSOCTET testdata[] = {
      0xee, 0x1d, 0x9 };
      OSCRTLMEMCPY ((void*)pvalue->pTMSISignature.value, testdata, 3);
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
