#include "TS24008IES.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300
TS24008IE_Cause* test_TS24008IE_Cause (OSCTXT* pctxt);

int main (int argc, char** argv)
{
   TS24008IE_Cause* pvalue;
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

   pvalue = test_TS24008IE_Cause (&ctxt);

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24008IE_Cause (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode Cause failed; status = %d\n", ret);
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

TS24008IE_Cause* test_TS24008IE_Cause (OSCTXT* pctxt)
{
   TS24008IE_Cause* pvalue = rtxMemAllocType (pctxt, TS24008IE_Cause);
   asn1Init_TS24008IE_Cause (pvalue);

   /* Start SEQUENCE or SET 130 */

   /* Populate the Enumerated type */
   pvalue->octet3.codingStandard = TS24008IE_CodingStandard_q931;

   /* Populate the Boolean type */
   pvalue->octet3.spare = 0;

   /* Populate the Enumerated type */
   pvalue->octet3.location = TS24008IE_Location_user;

   /* Populate the Integer type */
   pvalue->m.recommendationPresent = 1;
   pvalue->recommendation = 105;

   /* Populate the Integer type */
   pvalue->causeValue = 69;

   /* Populate OCTET STRING variable */
   pvalue->m.diagnosticsPresent = 1;
   {
      static const OSOCTET testdata[] = { 0x01, 0x04 };
      pvalue->diagnostics.numocts = 2;
      OSCRTLMEMCPY ((void*)pvalue->diagnostics.data, testdata, 9);
   }
   /* End SEQUENCE or SET 130 */
   return (pvalue);
}
