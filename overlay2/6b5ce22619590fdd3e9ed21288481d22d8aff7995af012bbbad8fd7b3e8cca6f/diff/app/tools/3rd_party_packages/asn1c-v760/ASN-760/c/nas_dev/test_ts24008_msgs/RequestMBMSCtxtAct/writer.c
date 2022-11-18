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
   TS24008Msg_RequestMBMSCtxtAct data;
   TS24008Msg_RequestMBMSCtxtAct* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_RequestMBMSCtxtAct;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_RequestMBMSCtxtAct;
   pdu.data.u.obj_RequestMBMSCtxtAct = pvalue;

   asn1Init_TS24008Msg_RequestMBMSCtxtAct (pvalue);
   pvalue->linkedNSAPI.spare = 8;
   pvalue->linkedNSAPI.value = 6;
   pvalue->offeredMulticastAddr.spare = 6;
   pvalue->offeredMulticastAddr.pdpTypeOrg = 12;
   pvalue->offeredMulticastAddr.pdpTypeNum = 32;
   {
      pvalue->offeredMulticastAddr.addressInfo.numocts = 0;
   }
   rtxStrcpy (pvalue->accessPointName, sizeof(pvalue->accessPointName),
              "province1.mnc012.mcc345.gprs");

   pvalue->m.mbmsPCOPresent = 1;
   pvalue->mbmsPCO.numocts = 10;
   pvalue->mbmsPCO.data = (OSOCTET*) rtxMemAlloc (&ctxt, 10);
   {
      static const OSOCTET testdata[] = {
      0xea, 0xb7, 0x9d, 0x13, 0x51, 0xbf, 0xba, 0xf1,
      0x9a, 0x1e };
      OSCRTLMEMCPY ((void*)pvalue->mbmsPCO.data, testdata, 10);
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
