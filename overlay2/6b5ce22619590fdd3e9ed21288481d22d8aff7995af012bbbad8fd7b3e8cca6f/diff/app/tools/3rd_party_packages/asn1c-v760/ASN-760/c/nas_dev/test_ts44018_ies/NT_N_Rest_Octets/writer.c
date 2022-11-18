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
   TS44018IE_NT_N_Rest_Octets value;
   TS44018IE_NT_N_Rest_Octets* pvalue = &value;
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

   asn1Init_TS44018IE_NT_N_Rest_Octets (pvalue);
   pvalue->m.nln_nchPresent = 1;
   pvalue->nln_nch = 0;

   /* zero elements */

   pvalue->m.component_3Present = 1;

   pvalue->component_3.m.cell_global_countPresent = 1;
   pvalue->component_3.cell_global_count = 0;

   pvalue->component_3.list_of_Reduced_GCR.n = 3;
   pvalue->component_3.list_of_Reduced_GCR.elem = rtxMemAllocArrayZ (pctxt, 3, OSUINT32);
   pvalue->component_3.list_of_Reduced_GCR.elem[0] = 5260;

   pvalue->component_3.list_of_Reduced_GCR.elem[1] = 8623;

   pvalue->component_3.list_of_Reduced_GCR.elem[2] = 20191;

   /* zero elements */

   pvalue->m.component_4Present = 1;

   pvalue->component_4.list_of_Emergency_information.n = 9;
   pvalue->component_4.list_of_Emergency_information.elem = rtxMemAllocArrayZ (pctxt, 9, OSUINT8);
   pvalue->component_4.list_of_Emergency_information.elem[0] = 0;

   pvalue->component_4.list_of_Emergency_information.elem[1] = 0;

   pvalue->component_4.list_of_Emergency_information.elem[2] = 0;

   pvalue->component_4.list_of_Emergency_information.elem[3] = 0;

   pvalue->component_4.list_of_Emergency_information.elem[4] = 0;

   pvalue->component_4.list_of_Emergency_information.elem[5] = 0;

   pvalue->component_4.list_of_Emergency_information.elem[6] = 0;

   pvalue->component_4.list_of_Emergency_information.elem[7] = 0;

   pvalue->component_4.list_of_Emergency_information.elem[8] = 0;

   pvalue->component_4.m.priority_Uplink_accessPresent = 1;
   pvalue->component_4.priority_Uplink_access = 0;

   pvalue->component_4.m.component_3Present = 1;

   pvalue->component_4.component_3.m.fr_AMR_ConfigPresent = 1;
   pvalue->component_4.component_3.fr_AMR_Config = 0;

   pvalue->component_4.component_3.m.hr_AMR_ConfigPresent = 1;
   pvalue->component_4.component_3.hr_AMR_Config = 6;

   pvalue->component_4.m.component_4Present = 1;

   pvalue->component_4.component_4.sms_Data_Confidentiality_Ind = 0;

   pvalue->component_4.component_4.sms_Guaranteed_Privacy_Ind = 0;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_NT_N_Rest_Octets (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode NT_N_Rest_Octets failed; status = %d\n", ret);
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
