#include "TS44018Msgs.h"
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
   TS44018Msg_UL_DCCH_PDU pdu;
   TS44018Msg_Cdma2000ClassmarkChange data;
   TS44018Msg_Cdma2000ClassmarkChange* pvalue = &data;

   OSCTXT	ctxt;
   OSCTXT*  pctxt = &ctxt;
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

   asn1Init_TS44018Msg_UL_DCCH_PDU (&pdu);
   pdu.l3HdrOpts.t = 1;
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;
   pdu.msgType = ASN1V_ts44018Msg_mt_Cdma2000ClassmarkChange;
   pdu.data.t = T_TS44018Msgs_UL_DCCH_Messages_obj_Cdma2000ClassmarkChange;
   pdu.data.u.obj_Cdma2000ClassmarkChange = pvalue;


   asn1Init_TS44018Msg_Cdma2000ClassmarkChange (pvalue);

   pvalue->terminalInfo.numocts = 5;
   pvalue->terminalInfo.data = (OSOCTET*) rtxMemAlloc (pctxt, 5);
   {
      static const OSOCTET testdata[] = {
      0xa4, 0xcf, 0xad, 0x6b, 0xf5 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->terminalInfo.data, 5, testdata, 5);
   }

   pvalue->securityStatus.numocts = 18;
   pvalue->securityStatus.data = (OSOCTET*) rtxMemAlloc (pctxt, 18);
   {
      static const OSOCTET testdata[] = {
      0x61, 0xbd, 0x65, 0xe0, 0xee, 0x0e, 0x33, 0xd6, 
      0x1a, 0xc0, 0x4f, 0xd9, 0x0e, 0xd0, 0xa6, 0x68, 
      0x4d, 0x85 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->securityStatus.data, 18, testdata, 18);
   }

   pvalue->bandClassInfo.numocts = 12;
   pvalue->bandClassInfo.data = (OSOCTET*) rtxMemAlloc (pctxt, 12);
   {
      static const OSOCTET testdata[] = {
      0x51, 0xe9, 0x58, 0x2e, 0x23, 0x96, 0xde, 0x22, 
      0x3e, 0x3b, 0x05, 0x2 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->bandClassInfo.data, 12, testdata, 12);
   }

   pvalue->powerClassInfo.numocts = 16;
   pvalue->powerClassInfo.data = (OSOCTET*) rtxMemAlloc (pctxt, 16);
   {
      static const OSOCTET testdata[] = {
      0x36, 0xfd, 0xb0, 0x14, 0xdf, 0x9e, 0xb7, 0xfb, 
      0x83, 0xa3, 0xcf, 0xe3, 0x6e, 0x84, 0x29, 0x1d };
      OSCRTLSAFEMEMCPY ((void*)pvalue->powerClassInfo.data, 16, testdata, 16);
   }

   pvalue->operatingModeInfo.numocts = 2;
   pvalue->operatingModeInfo.data = (OSOCTET*) rtxMemAlloc (pctxt, 2);
   {
      static const OSOCTET testdata[] = {
      0x5a, 0x9b };
      OSCRTLSAFEMEMCPY ((void*)pvalue->operatingModeInfo.data, 2, testdata, 2);
   }

   pvalue->serviceOptionInfo.numocts = 7;
   pvalue->serviceOptionInfo.data = (OSOCTET*) rtxMemAlloc (pctxt, 7);
   {
      static const OSOCTET testdata[] = {
      0x28, 0xfa, 0x96, 0xd1, 0x44, 0xcb, 0xf5 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->serviceOptionInfo.data, 7, testdata, 7);
   }

   pvalue->multiplexOptionInfo.numocts = 6;
   pvalue->multiplexOptionInfo.data = (OSOCTET*) rtxMemAlloc (pctxt, 6);
   {
      static const OSOCTET testdata[] = {
      0xa4, 0x7b, 0xab, 0x4d, 0x29, 0x15 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->multiplexOptionInfo.data, 6, testdata, 6);
   }

   pvalue->powerControlInfo.numocts = 16;
   pvalue->powerControlInfo.data = (OSOCTET*) rtxMemAlloc (pctxt, 16);
   {
      static const OSOCTET testdata[] = {
      0xf2, 0xe8, 0x1f, 0x48, 0x70, 0x2d, 0xbf, 0xae, 
      0xa1, 0x31, 0x15, 0x9a, 0x7c, 0x1e, 0xb8, 0x22 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->powerControlInfo.data, 16, testdata, 16);
   }

   pvalue->capabilityInfo.numocts = 4;
   pvalue->capabilityInfo.data = (OSOCTET*) rtxMemAlloc (pctxt, 4);
   {
      static const OSOCTET testdata[] = {
      0x25, 0x26, 0x11, 0x4b };
      OSCRTLSAFEMEMCPY ((void*)pvalue->capabilityInfo.data, 4, testdata, 4);
   }

   pvalue->channelConfigCapabilityInfo.numocts = 15;
   pvalue->channelConfigCapabilityInfo.data = (OSOCTET*) rtxMemAlloc (pctxt, 15);
   {
      static const OSOCTET testdata[] = {
      0xe4, 0xa0, 0x83, 0xc9, 0x4e, 0x13, 0x15, 0x09, 
      0x38, 0xea, 0x9a, 0x4d, 0x61, 0x8e, 0x51 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->channelConfigCapabilityInfo.data, 15, testdata, 15);
   }

   pvalue->extendedMultiplexOptionInfo.numocts = 12;
   pvalue->extendedMultiplexOptionInfo.data = (OSOCTET*) rtxMemAlloc (pctxt, 12);
   {
      static const OSOCTET testdata[] = {
      0xeb, 0x8c, 0x5c, 0x9d, 0xc2, 0x54, 0x9e, 0xfb, 
      0x38, 0x1d, 0x31, 0xd0 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->extendedMultiplexOptionInfo.data, 12, testdata, 12);
   }

   pvalue->bandSubclassInfo.numocts = 2;
   pvalue->bandSubclassInfo.data = (OSOCTET*) rtxMemAlloc (pctxt, 2);
   {
      static const OSOCTET testdata[] = {
      0x43, 0xbd };
      OSCRTLSAFEMEMCPY ((void*)pvalue->bandSubclassInfo.data, 2, testdata, 2);
   }

   pvalue->encryptionCapability.numocts = 2;
   pvalue->encryptionCapability.data = (OSOCTET*) rtxMemAlloc (pctxt, 2);
   {
      static const OSOCTET testdata[] = {
      0x23, 0xdb };
      OSCRTLSAFEMEMCPY ((void*)pvalue->encryptionCapability.data, 2, testdata, 2);
   }

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_UL_DCCH_PDU (&ctxt, &pdu);
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
