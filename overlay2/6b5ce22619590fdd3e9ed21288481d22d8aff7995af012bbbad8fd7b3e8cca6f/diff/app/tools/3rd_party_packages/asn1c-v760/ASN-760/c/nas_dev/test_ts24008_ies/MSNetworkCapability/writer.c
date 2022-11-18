#include "TS24008IES.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300
TS24008IE_MSNetworkCapability*
    test_TS24008IE_MSNetworkCapability (OSCTXT* pctxt);

int main (int argc, char** argv)
{
   TS24008IE_MSNetworkCapability* pvalue;
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

   pvalue = test_TS24008IE_MSNetworkCapability (&ctxt);

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24008IE_MSNetworkCapability (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode MSNetworkCapability failed; status = %d\n", ret);
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

TS24008IE_MSNetworkCapability*
    test_TS24008IE_MSNetworkCapability (OSCTXT* pctxt)
{
   TS24008IE_MSNetworkCapability* pvalue =
      rtxMemAllocType (pctxt, TS24008IE_MSNetworkCapability);

   asn1Init_TS24008IE_MSNetworkCapability (pvalue);

   /* Populate the Boolean type */
   pvalue->m.octet1Present = 1;
   pvalue->octet1.gea1 = 1;
   pvalue->octet1.smCapDeicatedChan = 0;
   pvalue->octet1.smCapGPRSChan = 1;
   pvalue->octet1.ucs2Support = 1;
   pvalue->octet1.ssScreeningInd = 1;
   pvalue->octet1.soLSACap = 1;
   pvalue->octet1.revisionLevelInd = 0;

   pvalue->m.octet2Present = 1;
   pvalue->octet2.pfcFeatureMode = 1;
   pvalue->octet2.extendedGEA = 26;
   pvalue->octet2.lcsVACap = 1;

   pvalue->m.octet3Present = 1;
   pvalue->octet3.psInterRATHOToUTRANIuModeCap = 0;
   pvalue->octet3.psInterRATHOToEUTRANS1ModeCap = 0;
   pvalue->octet3.emmCombinedProcCap = 1;
   pvalue->octet3.isrSupport = 1;
   pvalue->octet3.srvccToGERAN_UTRANCap = 0;
   pvalue->octet3.epcCap = 0;
   pvalue->octet3.nfCapability = TRUE;
   pvalue->octet3.geranNetShareCap = TRUE;

   pvalue->spareBits.numbits = 0;

   return (pvalue);
}
