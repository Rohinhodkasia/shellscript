#include "TS24008IES.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300
TS24008IE_QualityOfService* test_TS24008IE_QualityOfService (OSCTXT* pctxt);

int main (int argc, char** argv)
{
   TS24008IE_QualityOfService* pvalue;
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

   pvalue = test_TS24008IE_QualityOfService (&ctxt);

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24008IE_QualityOfService (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode QualityOfService failed; status = %d\n", ret);
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

TS24008IE_QualityOfService* test_TS24008IE_QualityOfService (OSCTXT* pctxt)
{
   TS24008IE_QualityOfService* pvalue =
      rtxMemAllocType (pctxt, TS24008IE_QualityOfService);
   asn1Init_TS24008IE_QualityOfService (pvalue);

   pvalue->spare1 = 0;
   pvalue->delayClass = 1;
   pvalue->reliabilityClass = 5;

   pvalue->peakThroughput = 13;
   pvalue->spare2 = 0;
   pvalue->precedenceClass = 4;

   pvalue->spare3 = 0;
   pvalue->meanThroughput = 24;

   pvalue->trafficClass = 6;
   pvalue->deliveryOrder = 0;
   pvalue->deliveryErroneousSDU = 4;

   pvalue->maxSDUSize = 137;

   pvalue->maxUplinkBR = 249;

   pvalue->maxDownlinkBR = 135;

   pvalue->residualBER = 3;
   pvalue->sduErrorRatio = 10;

   pvalue->transferDelay = 60;
   pvalue->trafficHandlingPrio = 2;

   pvalue->guaranteedUplinkBR = 123;

   pvalue->guaranteedDownlinkBR = 35;

   pvalue->spare4 = 0;
   pvalue->signallingIndication = 1;
   pvalue->sourceStatsDescriptor = 13;

   pvalue->extBitRate.n = 4;
   pvalue->extBitRate.elem[0] = 178; /* max downlink bitrate */
   pvalue->extBitRate.elem[1] = 188; /* guaranteed downlink bitrate */
   pvalue->extBitRate.elem[2] = 93;  /* max uplink bitrate */
   pvalue->extBitRate.elem[3] = 2;   /* guaranteed uplink bitrate */

   return (pvalue);
}

