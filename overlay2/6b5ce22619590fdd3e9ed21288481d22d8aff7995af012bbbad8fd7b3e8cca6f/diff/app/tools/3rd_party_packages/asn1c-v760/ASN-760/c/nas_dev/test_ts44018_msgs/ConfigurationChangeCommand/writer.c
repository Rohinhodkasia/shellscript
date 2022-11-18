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
   TS44018Msg_DL_DCCH_PDU pdu;
   TS44018Msg_ConfigurationChangeCommand data;
   TS44018Msg_ConfigurationChangeCommand* pvalue = &data;

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

   asn1Init_TS44018Msg_DL_DCCH_PDU (&pdu);
   pdu.l3HdrOpts.t = 1;
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;
   pdu.msgType = ASN1V_ts44018Msg_mt_ConfigurationChangeCommand;
   pdu.data.t = T_TS44018Msgs_DL_DCCH_Messages_obj_ConfigurationChangeCommand;
   pdu.data.u.obj_ConfigurationChangeCommand = pvalue;


   asn1Init_TS44018Msg_ConfigurationChangeCommand (pvalue);

   pvalue->descriptionMultislotConfig.length = 0; /* length will be calculated */

   pvalue->descriptionMultislotConfig.da = 102;

   pvalue->descriptionMultislotConfig.m.uaPresent = 1;
   pvalue->descriptionMultislotConfig.ua = 41;

   pvalue->descriptionMultislotConfig.channel_sets.n = 5;
   pvalue->descriptionMultislotConfig.channel_sets.elem[0] = 133;

   pvalue->descriptionMultislotConfig.channel_sets.elem[1] = 240;

   pvalue->descriptionMultislotConfig.channel_sets.elem[2] = 169;

   pvalue->descriptionMultislotConfig.channel_sets.elem[3] = 201;

   pvalue->descriptionMultislotConfig.channel_sets.elem[4] = 28;

   pvalue->m.modeChannelSet1Present = 1;
   pvalue->modeChannelSet1 = 39;

   pvalue->m.modeChannelSet2Present = 1;
   pvalue->modeChannelSet2 = 113;

   pvalue->m.modeChannelSet3Present = 1;
   pvalue->modeChannelSet3 = 44;

   pvalue->m.modeChannelSet4Present = 1;
   pvalue->modeChannelSet4 = 200;

   pvalue->m.modeChannelSet5Present = 1;
   pvalue->modeChannelSet5 = 8;

   pvalue->m.modeChannelSet6Present = 1;
   pvalue->modeChannelSet6 = 103;

   pvalue->m.modeChannelSet7Present = 1;
   pvalue->modeChannelSet7 = 36;

   pvalue->m.modeChannelSet8Present = 1;
   pvalue->modeChannelSet8 = 111;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_DL_DCCH_PDU (&ctxt, &pdu);
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
