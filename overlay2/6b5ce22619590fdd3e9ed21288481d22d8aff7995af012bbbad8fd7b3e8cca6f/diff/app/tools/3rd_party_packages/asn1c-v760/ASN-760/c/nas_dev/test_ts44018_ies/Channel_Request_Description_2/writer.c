#include "TS44018IES.h"
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
   TS44018IE_Channel_Request_Description_2 value;
   TS44018IE_Channel_Request_Description_2* pvalue = &value;
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

   asn1Init_TS44018IE_Channel_Request_Description_2 (pvalue);
   pvalue->length = 0; /* length will be calculated */

   pvalue->packet_establishment_cause = 1;

   pvalue->channel_Request_Description.peak_throughput_class = 2;

   pvalue->channel_Request_Description.radio_priority = 2;

   pvalue->channel_Request_Description.rlc_mode = 0;

   pvalue->channel_Request_Description.llc_pdu_type = 0;

   pvalue->channel_Request_Description.rlc_octet_count = 30393;

   pvalue->m.pfiPresent = 1;
   pvalue->pfi = 93;

   pvalue->multiple_TBF_Capability = 0;

   pvalue->m.component_6Present = 1;

   pvalue->component_6.rlc_Non_persistent_Mode_Capability = 0;

   pvalue->component_6.reduced_Latency_Capability = 0;

   pvalue->component_6.uplink_EGPRS2 = 0;

   pvalue->component_6.downlink_EGPRS2 = 1;

   pvalue->component_6.m.component_5Present = 1;

   pvalue->component_6.component_5.emst_MS_Capability = 0;

   pvalue->component_6.component_5.m.component_2Present = 1;

   pvalue->component_6.component_5.component_2.emsr_MS_Capability = 0;

   pvalue->component_6.component_5.component_2.m.fanr_CapabilityPresent = 1;
   pvalue->component_6.component_5.component_2.fanr_Capability = 0;


   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_Channel_Request_Description_2 (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode Channel_Request_Description_2 failed; status = %d\n", ret);
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
