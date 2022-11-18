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
   TS44018IE_SI19_Rest_Octets value;
   TS44018IE_SI19_Rest_Octets* pvalue = &value;
   OSCTXT	ctxt;
   OSCTXT*  pctxt = &ctxt;
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

   asn1Init_TS44018IE_SI19_Rest_Octets (pvalue);
   pvalue->si19_change_mark = 1;

   pvalue->si19_index = 3;

   pvalue->si19_last = 0;

   pvalue->compact_Neighbour_Cell_Parameters.n = 1;
   pvalue->compact_Neighbour_Cell_Parameters.elem = rtxMemAllocArray(pctxt, 1, TS44018IE_COMPACT_Neighbour_Cell_params_struct_element);
   asn1Init_TS44018IE_COMPACT_Neighbour_Cell_params_struct_element(&pvalue->compact_Neighbour_Cell_Parameters.elem[0]);
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].start_frequency = 45;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].compact_Cell_selection_params.component_1.t = 1;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].compact_Cell_selection_params.component_1.u.bcc = 7;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].compact_Cell_selection_params.cell_barred = 1;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].compact_Cell_selection_params.component_3 = 0;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].compact_Cell_selection_params.la_Different_parameters.m.cell_reselect_hysterisisPresent = 0;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].compact_Cell_selection_params.m.ms_txpwr_max_cchPresent = 0;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].compact_Cell_selection_params.m.rxlev_access_minPresent = 0;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].compact_Cell_selection_params.m.cell_reselect_offsetPresent = 0;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].compact_Cell_selection_params.m.component_8Present = 0;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].compact_Cell_selection_params.m.time_groupPresent = 0;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].compact_Cell_selection_params.m.guar_constant_pwr_blksPresent = 0;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].nr_of_remaining_cells = 1;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].freq_diff_length = 2;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].component_5.n = 1;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].component_5.elem[0].frequency_diff.numbits = 3;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].component_5.elem[0].frequency_diff.data[0] = 0xE0;
   asn1Init_TS44018IE_COMPACT_Cell_Selection_struct(&pvalue->compact_Neighbour_Cell_Parameters.elem[0].component_5.elem[0].compact_Cell_Selection_struct);
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].component_5.elem[0].compact_Cell_Selection_struct.component_1.t = 1;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].component_5.elem[0].compact_Cell_Selection_struct.component_1.u.bcc = 7;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].component_5.elem[0].compact_Cell_Selection_struct.cell_barred = 1;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].component_5.elem[0].compact_Cell_Selection_struct.component_3 = 0;
   pvalue->compact_Neighbour_Cell_Parameters.elem[0].component_5.elem[0].compact_Cell_Selection_struct.la_Different_parameters.m.cell_reselect_hysterisisPresent = 0;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_SI19_Rest_Octets (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode SI19_Rest_Octets failed; status = %d\n", ret);
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
