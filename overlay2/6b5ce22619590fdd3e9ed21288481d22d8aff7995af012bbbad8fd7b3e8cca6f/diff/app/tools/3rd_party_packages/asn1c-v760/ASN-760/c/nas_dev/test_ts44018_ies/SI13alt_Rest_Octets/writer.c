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
   TS44018IE_SI13alt_Rest_Octets value;
   TS44018IE_SI13alt_Rest_Octets* pvalue = &value;
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

   asn1Init_TS44018IE_SI13alt_Rest_Octets (pvalue);

   pvalue->pbcch_Description.psi1_repeat_period = 5;

   pvalue->pbcch_Description.pb = 12;

   pvalue->pbcch_Description.tn = 2;

   pvalue->pbcch_Description.pbcch_Frequency_Description.tsc = 0;

   pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.t =  3;

   pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.u.direct_encoding_1.maio = 47;

   pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.hsn = 5;

   pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.n = 2;
   pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem = rtxMemAllocArrayZ (pctxt, 2, OSUINT8);
   pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[0] = 4;

   pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[1] = 4;

   pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.t =  1;

   pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_length = 24;

   pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_bitmap.numbits = 25;
   pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_bitmap.data[0] = 0x43;
   pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_bitmap.data[1] = 0x3a;
   pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_bitmap.data[2] = 0x5f;
   pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_bitmap.data[3] = 0x58;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_SI13alt_Rest_Octets (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode SI13alt_Rest_Octets failed; status = %d\n", ret);
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
