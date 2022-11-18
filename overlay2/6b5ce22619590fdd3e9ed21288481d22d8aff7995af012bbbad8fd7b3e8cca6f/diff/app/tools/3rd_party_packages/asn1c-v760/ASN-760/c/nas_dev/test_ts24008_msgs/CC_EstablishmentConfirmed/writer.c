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
   TS24008Msg_CC_EstablishmentConfirmed data;
   TS24008Msg_CC_EstablishmentConfirmed* pvalue = &data;
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
   pdu.protoDiscr = TS24007L3_ProtoDiscr_callCtrl;
   pdu.msgType = ASN1V_mt_CC_EstablishmentConfirmed;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_CC_EstablishmentConfirmed;
   pdu.data.u.obj_CC_EstablishmentConfirmed = pvalue;

   asn1Init_TS24008Msg_CC_EstablishmentConfirmed (pvalue);

   pvalue->m.repeatIndPresent = 1;
   pvalue->repeatInd = TS24008IE_RepeatIndicator_svcChgFallback;

   pvalue->m.bearerCap1Present = 1;
   pvalue->bearerCap1.octet3.radioChannelRequirement = 1;
   pvalue->bearerCap1.octet3.nonstandardCoding = 1;
   pvalue->bearerCap1.octet3.packetXferMode = 1;
   pvalue->bearerCap1.octet3.infoXferCap = TS24008IE_InfoXferCap_digital;
   pvalue->bearerCap1.octet3a.coding = 0;
   pvalue->bearerCap1.octet3a.ctm = 1;
   pvalue->bearerCap1.octet3a.spare = 0;
   pvalue->bearerCap1.octet3a.speechVersion = 6;

   pvalue->bearerCap1.m.octet4Present = 1;
   pvalue->bearerCap1.octet4.compression = 0;
   pvalue->bearerCap1.octet4.structure = 2;
   pvalue->bearerCap1.octet4.fullDuplexMode = 1;
   pvalue->bearerCap1.octet4.configuration = 1;
   pvalue->bearerCap1.octet4.nirr = 1;
   pvalue->bearerCap1.octet4.establishment = 0;

   pvalue->bearerCap1.m.octet5Present = 1;
   pvalue->bearerCap1.m.octet5aPresent = 1;
   pvalue->bearerCap1.m.octet5bPresent = 1;
   pvalue->bearerCap1.octet5.accessIdentity = 1;
   pvalue->bearerCap1.octet5.rateAdaption = 1;
   pvalue->bearerCap1.octet5.signallingAccessProtocol = 6;
   pvalue->bearerCap1.octet5a.otherITC = 2;
   pvalue->bearerCap1.octet5a.otherRateAdaption = 2;
   pvalue->bearerCap1.octet5a.spare = 1;
   pvalue->bearerCap1.octet5b.rateAdaptionHeader = 0;
   pvalue->bearerCap1.octet5b.multipleFrameEstablishment = 1;
   pvalue->bearerCap1.octet5b.protocolSensitiveMode = 1;
   pvalue->bearerCap1.octet5b.fullProtocolNegotiation = 1;
   pvalue->bearerCap1.octet5b.assignorOnly = 1;
   pvalue->bearerCap1.octet5b.uiNegotiation = 0;
   pvalue->bearerCap1.octet5b.spare = 0;

   pvalue->bearerCap1.m.octet6Present = 1;
   pvalue->bearerCap1.m.octet6aPresent = 1;
   pvalue->bearerCap1.octet6.layer1Identity = 0;
   pvalue->bearerCap1.octet6.userInfoLayer1Protocol = 11;
   pvalue->bearerCap1.octet6.asynchronous = 1;
   pvalue->bearerCap1.octet6a.twoStopBits = 1;
   pvalue->bearerCap1.octet6a.negotiation = 0;
   pvalue->bearerCap1.octet6a.data8bits = 1;
   pvalue->bearerCap1.octet6a.userRate = 14;

   pvalue->bearerCap1.m.octet7Present = 1;
   pvalue->bearerCap1.octet7.layer2Identity = 0;
   pvalue->bearerCap1.octet7.userInformationLayer2Protocol = 13;

   pvalue->m.bearerCap2Present = 1;
   pvalue->bearerCap2.octet3.radioChannelRequirement = 2;
   pvalue->bearerCap2.octet3.nonstandardCoding = 0;
   pvalue->bearerCap2.octet3.packetXferMode = 0;
   pvalue->bearerCap2.octet3.infoXferCap = TS24008IE_InfoXferCap_audio;
   pvalue->bearerCap2.m.octet3aPresent = 1;
   pvalue->bearerCap2.octet3a.coding = 0;
   pvalue->bearerCap2.octet3a.ctm = 0;
   pvalue->bearerCap2.octet3a.spare = 0;
   pvalue->bearerCap2.octet3a.speechVersion = 4;

   pvalue->bearerCap2.m.octet4Present = 1;
   pvalue->bearerCap2.octet4.compression = 1;
   pvalue->bearerCap2.octet4.structure = 0;
   pvalue->bearerCap2.octet4.fullDuplexMode = 0;
   pvalue->bearerCap2.octet4.configuration = 0;
   pvalue->bearerCap2.octet4.nirr = 1;
   pvalue->bearerCap2.octet4.establishment = 1;

   pvalue->bearerCap2.m.octet5Present = 1;
   pvalue->bearerCap2.m.octet5aPresent = 1;
   pvalue->bearerCap2.octet5.accessIdentity = 0;
   pvalue->bearerCap2.octet5.rateAdaption = 2;
   pvalue->bearerCap2.octet5.signallingAccessProtocol = 5;
   pvalue->bearerCap2.octet5a.otherITC = 1;
   pvalue->bearerCap2.octet5a.otherRateAdaption = 1;
   pvalue->bearerCap2.octet5a.spare = 6;

   pvalue->bearerCap2.m.octet6Present = 1;
   pvalue->bearerCap2.octet6.layer1Identity = 2;
   pvalue->bearerCap2.octet6.userInfoLayer1Protocol = 11;
   pvalue->bearerCap2.octet6.asynchronous = 1;

   pvalue->bearerCap2.m.octet7Present = 1;
   pvalue->bearerCap2.octet7.layer2Identity = 1;
   pvalue->bearerCap2.octet7.userInformationLayer2Protocol = 18;

   pvalue->m.causePresent = 1;
   pvalue->cause.octet3.codingStandard = TS24008IE_CodingStandard_q931;
   pvalue->cause.octet3.spare = 0;
   pvalue->cause.octet3.location = TS24008IE_Location_user;
   pvalue->cause.m.recommendationPresent = 1;
   pvalue->cause.recommendation = 108;
   pvalue->cause.causeValue = 125;

   pvalue->m.supportedCodecsPresent = 1;
   pvalue->supportedCodecs.length = 175;
   pvalue->supportedCodecs.codecs.n = 1;

   pvalue->supportedCodecs.codecs.elem[0].sysID = 6;
   {
      static const OSOCTET testdata[] = {
      0x2e };
      pvalue->supportedCodecs.codecs.elem[0].codecBitmap.numocts = 1;
      OSCRTLMEMCPY ((void*)pvalue->supportedCodecs.codecs.elem[0].codecBitmap.data, testdata, 1);
   }

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

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
   msgptr = rtxCtxtGetMsgPtr (&ctxt);
   len = rtxCtxtGetMsgLen (&ctxt);

   if (verbose) {
      printf ("Encoding was successful\n");
      printf ("Hex dump of encoded record:\n");
      rtxHexDump (msgptr, len);
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
