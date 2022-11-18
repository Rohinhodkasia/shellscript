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
   TS44018IE_Measurement_Results value;
   TS44018IE_Measurement_Results* pvalue = &value;
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

   pvalue->ba_used = 0;

   pvalue->dtx_used = 0;

   pvalue->rxlev_full_serving_cell = 34;

   pvalue->a3G_BA_USED = 0;

   pvalue->meas_valid = 0;

   pvalue->rxlev_sub_serving_cell = 37;

   pvalue->si23_ba_used = 0;

   pvalue->rxqual_full_serving_cell = 1;

   pvalue->rxqual_sub_serving_cell = 0;

   pvalue->no_ncell_m = 2;     /* no cells */
   pvalue->component_11.u.choice_2.ncell_Report.n = 2;
   pvalue->component_11.u.choice_2.ncell_Report.elem[0].rxlev_ncell = 3;
   pvalue->component_11.u.choice_2.ncell_Report.elem[0].bcch_freq_ncell = 3;
   pvalue->component_11.u.choice_2.ncell_Report.elem[0].bsic_ncell = 3;

   pvalue->component_11.u.choice_2.ncell_Report.elem[1].rxlev_ncell = 5;
   pvalue->component_11.u.choice_2.ncell_Report.elem[1].bcch_freq_ncell = 5;
   pvalue->component_11.u.choice_2.ncell_Report.elem[1].bsic_ncell = 5;
   pvalue->component_11.u.choice_2.m.utran_CSG_Measurement_ReportPresent = 0;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_Measurement_Results (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode Measurement_Results failed; status = %d\n", ret);
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
