#include "TS24301IES.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

static TS24301IE_EPSMobileIdentity* test_EPSMobileIdentity (OSCTXT* pctxt);

int main (int argc, char** argv)
{
   TS24301IE_EPSMobileIdentity* pvalue;
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

   pvalue = test_EPSMobileIdentity (&ctxt);

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24301IE_EPSMobileIdentity (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode EPSMobileIdentity failed; status = %d\n", ret);
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

static TS24301IE_EPSMobileIdentity_GUTI* test_EPSMobileIdentity_GUTI
(OSCTXT* pctxt, TS24301IE_EPSMobileIdentity_GUTI* pvalue)
{
   asn1Init_TS24301IE_EPSMobileIdentity_GUTI (pvalue);

   rtxStrncpy(pvalue->mcc_mnc.mcc, sizeof(pvalue->mcc_mnc.mcc), "#05", 4);
   rtxStrncpy(pvalue->mcc_mnc.mnc, sizeof(pvalue->mcc_mnc.mnc), "c*3", 4);
   {
      static const OSOCTET testdata[] = {
      0x9d, 0x65 };
      OSCRTLMEMCPY ((void*)pvalue->mmeGroupID, testdata, 2);
   }

   pvalue->mmeCode = 71;

   {
      static const OSOCTET testdata[] = {
      0xe7, 0x87, 0x70, 0xcc };
      OSCRTLMEMCPY ((void*)pvalue->tmsi, testdata, 4);
   }

   return (pvalue);
}

static TS24301IE_EPSMobileIdentity* test_EPSMobileIdentity (OSCTXT* pctxt)
{
   TS24301IE_EPSMobileIdentity* pvalue =
      rtxMemAllocType (pctxt, TS24301IE_EPSMobileIdentity);

   asn1Init_TS24301IE_EPSMobileIdentity (pvalue);
   pvalue->filler = 15;
   pvalue->oddEvenInd = 1;
   pvalue->typeOfIdent = 6;

   test_EPSMobileIdentity_GUTI (pctxt, &pvalue->content.u.guti);

   return (pvalue);
}

