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
   TS24008Msg_ActivateMBMSCtxtAcc data;
   TS24008Msg_ActivateMBMSCtxtAcc* pvalue = &data;
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
   pdu.protoDiscr = TS24007L3_ProtoDiscr_sessMgmt;
   pdu.msgType = ASN1V_mt_ActivateMBMSCtxtAcc;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_ActivateMBMSCtxtAcc;
   pdu.data.u.obj_ActivateMBMSCtxtAcc = pvalue;

   asn1Init_TS24008Msg_ActivateMBMSCtxtAcc (pvalue);
   {
      static const OSOCTET testdata[] = {
      0xa6, 0x80, 0x3f };
      OSCRTLMEMCPY ((void*)pvalue->tmgi.mbmsServiceID, testdata, 3);
   }
   pvalue->tmgi.m.mcc_mncPresent = 1;
   rtxStrncpy(pvalue->tmgi.mcc_mnc.mcc,
              sizeof(pvalue->tmgi.mcc_mnc.mcc), "a4a", 4);
   rtxStrncpy(pvalue->tmgi.mcc_mnc.mnc,
              sizeof(pvalue->tmgi.mcc_mnc.mnc), "373", 4);
   pvalue->negotiatedLLCSAPI.value = TS24008IE_SAPIValues_sapi11;
   pvalue->m.mbmsPCOPresent = 1;
   pvalue->mbmsPCO.numocts = 18;
   pvalue->mbmsPCO.data = (OSOCTET*) rtxMemAlloc (&ctxt, 18);
   {
      static const OSOCTET testdata[] = {
      0x91, 0x12, 0x7e, 0x08, 0xf6, 0x66, 0x0a, 0x18,
      0x55, 0x31, 0x36, 0x17, 0xbf, 0x57, 0xd8, 0xc6,
      0xf5, 0x3b };
      OSCRTLMEMCPY ((void*)pvalue->mbmsPCO.data, testdata, 18);
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
