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
   TS44018IE_SI2ter_Rest_Octets value;
   TS44018IE_SI2ter_Rest_Octets* pvalue = &value;
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

   asn1Init_TS44018IE_SI2ter_Rest_Octets (pvalue);

   pvalue->m.component_1Present = 1;

   pvalue->component_1.si2ter_MP_CHANGE_MARK = 0;

   pvalue->component_1.si2ter_3G_CHANGE_MARK = 0;

   pvalue->component_1.si2ter_INDEX = 1;

   pvalue->component_1.si2ter_COUNT = 0;

   pvalue->component_1.m.utran_FDD_DescriptionPresent = 1;

   pvalue->component_1.utran_FDD_Description.component_1 = 1;

   pvalue->component_1.utran_FDD_Description.fdd_arfcn = 12052;

   pvalue->component_1.utran_FDD_Description.m.bandwidth_FDDPresent = 1;
   pvalue->component_1.utran_FDD_Description.bandwidth_FDD = 6;

   pvalue->component_1.m.utran_TDD_DescriptionPresent = 1;

   pvalue->component_1.utran_TDD_Description.component_1 = 1;

   pvalue->component_1.utran_TDD_Description.tdd_arfcn = 4153;

   pvalue->component_1.utran_TDD_Description.m.bandwidth_TDDPresent = 1;
   pvalue->component_1.utran_TDD_Description.bandwidth_TDD = 1;

   pvalue->component_1.m.a3G_MEASUREMENT_Parameters_DescriptionPresent = 1;

   pvalue->component_1.a3G_MEASUREMENT_Parameters_Description.qsearch_I = 12;

   pvalue->component_1.a3G_MEASUREMENT_Parameters_Description.m.component_2Present = 1;

   pvalue->component_1.a3G_MEASUREMENT_Parameters_Description.component_2.fdd_Qoffset = 0;

   pvalue->component_1.a3G_MEASUREMENT_Parameters_Description.component_2.fdd_Qmin = 3;

   pvalue->component_1.a3G_MEASUREMENT_Parameters_Description.m.tdd_QoffsetPresent = 1;
   pvalue->component_1.a3G_MEASUREMENT_Parameters_Description.tdd_Qoffset = 9;

   pvalue->component_1.m.component_8Present = 1;

   pvalue->component_1.component_8.m.a3G_Additional_Measurement_Parameters_DescriptionPresent = 1;

   pvalue->component_1.component_8.a3G_Additional_Measurement_Parameters_Description.fdd_Qmin_Offset = 5;

   pvalue->component_1.component_8.a3G_Additional_Measurement_Parameters_Description.fdd_RSCPmin = 5;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_SI2ter_Rest_Octets (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode SI2ter_Rest_Octets failed; status = %d\n", ret);
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
