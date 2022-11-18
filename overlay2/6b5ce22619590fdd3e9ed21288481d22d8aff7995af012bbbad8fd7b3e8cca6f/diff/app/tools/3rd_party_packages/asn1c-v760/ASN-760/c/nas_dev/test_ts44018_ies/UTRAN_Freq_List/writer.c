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
   TS44018IE_UTRAN_Freq_List value;
   TS44018IE_UTRAN_Freq_List* pvalue = &value;
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

   asn1Init_TS44018IE_UTRAN_Freq_List (pvalue);

   pvalue->length_of_utran_freq_list = 0; /* length will be calculated */

   pvalue->fdd_arfcn_list.n = 7;
   pvalue->fdd_arfcn_list.elem = rtxMemAllocArrayZ (pctxt, 7, OSUINT16);
   pvalue->fdd_arfcn_list.elem[0] = 4583;

   pvalue->fdd_arfcn_list.elem[1] = 10345;

   pvalue->fdd_arfcn_list.elem[2] = 9756;

   pvalue->fdd_arfcn_list.elem[3] = 10493;

   pvalue->fdd_arfcn_list.elem[4] = 11609;

   pvalue->fdd_arfcn_list.elem[5] = 13953;

   pvalue->fdd_arfcn_list.elem[6] = 8400;

   pvalue->tdd_arfcn_list.n = 4;
   pvalue->tdd_arfcn_list.elem = rtxMemAllocArrayZ (pctxt, 4, OSUINT16);
   pvalue->tdd_arfcn_list.elem[0] = 16378;

   pvalue->tdd_arfcn_list.elem[1] = 7667;

   pvalue->tdd_arfcn_list.elem[2] = 1707;

   pvalue->tdd_arfcn_list.elem[3] = 584;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_UTRAN_Freq_List (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode UTRAN_Freq_List failed; status = %d\n", ret);
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
