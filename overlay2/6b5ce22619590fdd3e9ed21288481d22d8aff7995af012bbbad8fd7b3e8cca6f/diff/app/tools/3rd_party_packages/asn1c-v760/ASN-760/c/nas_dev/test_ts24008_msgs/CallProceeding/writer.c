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
   TS24008Msg_CallProceeding data;
   TS24008Msg_CallProceeding* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_CallProceeding;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_CallProceeding;
   pdu.data.u.obj_CallProceeding = pvalue;

   asn1Init_TS24008Msg_CallProceeding (pvalue);

   pvalue->m.repeatIndPresent = 1;
   pvalue->repeatInd = TS24008IE_RepeatIndicator_circular;
   pvalue->m.bearerCap1Present = 1;
   pvalue->bearerCap1.octet3.radioChannelRequirement = 2;
   pvalue->bearerCap1.octet3.nonstandardCoding = 1;
   pvalue->bearerCap1.octet3.packetXferMode = 0;
   pvalue->bearerCap1.octet3.infoXferCap = TS24008IE_InfoXferCap_speech;


   pvalue->m.bearerCap2Present = 1;
   pvalue->bearerCap2.octet3.radioChannelRequirement = 2;
   pvalue->bearerCap2.octet3.nonstandardCoding = 1;
   pvalue->bearerCap2.octet3.packetXferMode = 0;
   pvalue->bearerCap2.octet3.infoXferCap = TS24008IE_InfoXferCap_speech;
   
   pvalue->bearerCap2.m.octet3aPresent = 1;
   pvalue->bearerCap2.octet3a.coding = 0;
   pvalue->bearerCap2.octet3a.ctm = 0;
   pvalue->bearerCap2.octet3a.spare = 0;
   pvalue->bearerCap2.octet3a.speechVersion = 7;

   pvalue->m.facilityPresent = 1;
   pvalue->facility.numocts = 17;
   pvalue->facility.data = (OSOCTET*) rtxMemAlloc (&ctxt, 17);
   {
      static const OSOCTET testdata[] = {
      0x79, 0xc7, 0xf7, 0x40, 0xa4, 0xa1, 0xbb, 0xc4,
      0x34, 0x4f, 0xf8, 0x2e, 0x46, 0x26, 0xd7, 0x3e,
      0x8e };
      OSCRTLMEMCPY ((void*)pvalue->facility.data, testdata, 17);
   }

   pvalue->m.progressIndPresent = 1;
   pvalue->progressInd.octet3.codingStandard = TS24008IE_CodingStandard_q931;
   pvalue->progressInd.octet3.location = TS24008IE_PILocation_pubRemote;
   pvalue->progressInd.description = 80;

   pvalue->m.priorityGrantedPresent = 1;
   pvalue->priorityGranted.spare = 0;
   pvalue->priorityGranted.callPriority = 5;

   pvalue->m.netCallCtrlCapPresent = 1;
   pvalue->netCallCtrlCap.mcs = 1;

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
      rtxFreeContext (&ctxt);
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
