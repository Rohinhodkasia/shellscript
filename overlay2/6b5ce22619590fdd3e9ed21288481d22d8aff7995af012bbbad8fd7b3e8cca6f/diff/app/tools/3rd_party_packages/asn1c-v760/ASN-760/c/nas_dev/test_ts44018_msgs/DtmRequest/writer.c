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
   TS44018Msg_DtmRequest data;
   TS44018Msg_DtmRequest* pvalue = &data;

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

   asn1Init_TS44018Msg_UL_DCCH_PDU (&pdu);
   pdu.l3HdrOpts.t = 1;
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;
   pdu.msgType = ASN1V_ts44018Msg_mt_DtmRequest;
   pdu.data.t = T_TS44018Msgs_UL_DCCH_Messages_obj_DtmRequest;
   pdu.data.u.obj_DtmRequest = pvalue;


   asn1Init_TS44018Msg_DtmRequest (pvalue);

   pvalue->tlli = 28055;

   pvalue->channelRequestDescr2.length = 0; /* length will be calculated */

   pvalue->channelRequestDescr2.packet_establishment_cause = 0;

   pvalue->channelRequestDescr2.channel_Request_Description.peak_throughput_class = 1;

   pvalue->channelRequestDescr2.channel_Request_Description.radio_priority = 0;

   pvalue->channelRequestDescr2.channel_Request_Description.rlc_mode = 0;

   pvalue->channelRequestDescr2.channel_Request_Description.llc_pdu_type = 0;

   pvalue->channelRequestDescr2.channel_Request_Description.rlc_octet_count = 31174;

   pvalue->channelRequestDescr2.m.pfiPresent = 1;
   pvalue->channelRequestDescr2.pfi = 104;

   pvalue->channelRequestDescr2.multiple_TBF_Capability = 0;

   pvalue->channelRequestDescr2.m.component_6Present = 1;

   pvalue->channelRequestDescr2.component_6.rlc_Non_persistent_Mode_Capability = 0;

   pvalue->channelRequestDescr2.component_6.reduced_Latency_Capability = 0;

   pvalue->channelRequestDescr2.component_6.uplink_EGPRS2 = 1;

   pvalue->channelRequestDescr2.component_6.downlink_EGPRS2 = 1;

   pvalue->channelRequestDescr2.component_6.m.component_5Present = 1;

   pvalue->channelRequestDescr2.component_6.component_5.emst_MS_Capability = 0;

   pvalue->channelRequestDescr2.component_6.component_5.m.component_2Present = 1;

   pvalue->channelRequestDescr2.component_6.component_5.component_2.emsr_MS_Capability = 0;

   pvalue->channelRequestDescr2.component_6.component_5.component_2.m.fanr_CapabilityPresent = 1;
   pvalue->channelRequestDescr2.component_6.component_5.component_2.fanr_Capability = 0;

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
