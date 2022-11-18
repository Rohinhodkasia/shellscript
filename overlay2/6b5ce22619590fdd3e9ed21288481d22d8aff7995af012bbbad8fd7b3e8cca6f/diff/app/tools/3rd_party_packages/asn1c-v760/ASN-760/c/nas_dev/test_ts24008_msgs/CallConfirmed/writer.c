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
   TS24008Msg_CallConfirmed data;
   TS24008Msg_CallConfirmed* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_CallConfirmed;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_CallConfirmed;
   pdu.data.u.obj_CallConfirmed = pvalue;

   asn1Init_TS24008Msg_CallConfirmed (pvalue);
   pvalue->repeatInd = 5;
   pvalue->m.bearerCap1Present = 1;
   pvalue->bearerCap1.octet3.radioChannelRequirement = 2;
   pvalue->bearerCap1.octet3.nonstandardCoding = 0;
   pvalue->bearerCap1.octet3.packetXferMode = 1;
   pvalue->bearerCap1.octet3.infoXferCap = TS24008IE_InfoXferCap_speech;

   pvalue->bearerCap1.m.octet4Present = 0;
   pvalue->bearerCap1.m.octet5Present = 0;
   pvalue->bearerCap1.m.octet5aPresent = 0;
   pvalue->bearerCap1.m.octet5bPresent = 0;
   pvalue->bearerCap1.m.octet6Present = 0;
   pvalue->bearerCap1.m.octet6aPresent = 0;
   pvalue->bearerCap1.m.octet6bPresent = 0;
   pvalue->bearerCap1.m.octet6cPresent = 0;
   pvalue->bearerCap1.m.octet6dPresent = 0;
   pvalue->bearerCap1.m.octet6ePresent = 0;
   pvalue->bearerCap1.m.octet6fPresent = 0;
   pvalue->bearerCap1.m.octet6gPresent = 0;
   pvalue->bearerCap1.m.octet7Present = 0;

   pvalue->m.bearerCap2Present = 1;
   pvalue->bearerCap2.octet3.radioChannelRequirement = 2;
   pvalue->bearerCap2.octet3.nonstandardCoding = 0;
   pvalue->bearerCap2.octet3.packetXferMode = 0;
   pvalue->bearerCap2.octet3.infoXferCap = TS24008IE_InfoXferCap_speech;
   
   pvalue->bearerCap2.m.octet4Present = 0;
   pvalue->bearerCap2.m.octet5Present = 0;
   pvalue->bearerCap2.m.octet5aPresent = 0;
   pvalue->bearerCap2.m.octet5bPresent = 0;
   pvalue->bearerCap2.m.octet6Present = 0;
   pvalue->bearerCap2.m.octet6aPresent = 0;
   pvalue->bearerCap2.m.octet6bPresent = 0;
   pvalue->bearerCap2.m.octet6cPresent = 0;
   pvalue->bearerCap2.m.octet6dPresent = 0;
   pvalue->bearerCap2.m.octet6ePresent = 0;
   pvalue->bearerCap2.m.octet6fPresent = 0;
   pvalue->bearerCap2.m.octet6gPresent = 0;
   pvalue->bearerCap2.m.octet7Present = 0;

   pvalue->m.causePresent = 1;
   pvalue->cause.octet3.codingStandard = TS24008IE_CodingStandard_q931;
   pvalue->cause.octet3.spare = 0;
   pvalue->cause.octet3.location = TS24008IE_Location_user;
   pvalue->cause.m.recommendationPresent = 1;
   pvalue->cause.recommendation = 22;
   pvalue->cause.causeValue = 56;

   pvalue->m.callCtrlCapPresent = 1;
   pvalue->callCtrlCap.length = 239;
   pvalue->callCtrlCap.maxNumSupportedBearers = 3;
   pvalue->callCtrlCap.mcat = 0;
   pvalue->callCtrlCap.enicm = 0;
   pvalue->callCtrlCap.pcp = 1;
   pvalue->callCtrlCap.dtmf = 0;
   pvalue->callCtrlCap.spare = 4;
   pvalue->callCtrlCap.maxNumSpeechBearers = 5;

   pvalue->m.streamIdPresent = 1;
   pvalue->streamId.value = 132;

   pvalue->m.supportedCodecsPresent = 1;
   pvalue->supportedCodecs.length = 209;

   pvalue->supportedCodecs.codecs.n = 1;
   pvalue->supportedCodecs.codecs.elem[0].sysID = 0;
   {
      static const OSOCTET testdata[] = { 0x37 };
      pvalue->supportedCodecs.codecs.elem[0].codecBitmap.numocts = 1;
      OSCRTLMEMCPY ((void*)pvalue->supportedCodecs.codecs.elem[0].codecBitmap.data, testdata, 1);
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
