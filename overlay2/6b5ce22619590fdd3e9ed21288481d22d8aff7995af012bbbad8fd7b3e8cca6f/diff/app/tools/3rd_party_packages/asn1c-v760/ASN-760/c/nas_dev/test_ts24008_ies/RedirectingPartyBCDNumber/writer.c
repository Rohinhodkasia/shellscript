#include "TS24008IES.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300
TS24008IE_RedirectingPartyBCDNumber*
    test_TS24008IE_RedirectingPartyBCDNumber (OSCTXT* pctxt);

int main (int argc, char** argv)
{
   TS24008IE_RedirectingPartyBCDNumber* pvalue;
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

   pvalue = test_TS24008IE_RedirectingPartyBCDNumber (&ctxt);

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24008IE_RedirectingPartyBCDNumber (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode RedirectingPartyBCDNumber failed; status = %d\n", ret);
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

TS24008IE_RedirectingPartyBCDNumber*
    test_TS24008IE_RedirectingPartyBCDNumber (OSCTXT* pctxt)
{
   TS24008IE_RedirectingPartyBCDNumber* pvalue =
      rtxMemAllocType (pctxt, TS24008IE_RedirectingPartyBCDNumber);
   asn1Init_TS24008IE_RedirectingPartyBCDNumber (pvalue);

   /* Start SEQUENCE or SET 10 */

   /* Populate the Integer type */
   pvalue->octet3.typeOfNumber = TS24008IE_NumberTypes_international;

   /* Populate the Integer type */
   pvalue->octet3.numberingPlanID = TS24008IE_NumberPlans_telex;

   pvalue->m.octet3aPresent = 1;

   /* Populate the Integer type */
   pvalue->octet3a.presentationIndicator = 1;

   /* Populate the Integer type */
   pvalue->octet3a.spare = 0;

   /* Populate the Integer type */
   pvalue->octet3a.screeningIndicator = 1;

   /* Populate the Character String */
   pvalue->m.numberPresent = 1;
   pvalue->number = "11223";
   /* End SEQUENCE or SET 10 */
   return (pvalue);
}

