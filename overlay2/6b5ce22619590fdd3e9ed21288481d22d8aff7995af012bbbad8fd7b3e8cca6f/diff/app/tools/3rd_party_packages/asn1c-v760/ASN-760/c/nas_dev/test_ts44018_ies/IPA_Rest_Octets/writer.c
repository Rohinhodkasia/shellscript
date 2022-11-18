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
   TS44018IE_IPA_Rest_Octets value;
   TS44018IE_IPA_Rest_Octets* pvalue = &value;
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

   asn1Init_TS44018IE_IPA_Rest_Octets (pvalue);
   pvalue->m.ipa_Uplink_Assignment_structPresent = 1;

   /* zero elements */

   pvalue->ipa_Uplink_Assignment_struct.tn = 3;

   pvalue->ipa_Uplink_Assignment_struct.m.frequency_ParametersPresent = 1;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.tsc = 1;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.t =  4;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_2.maio = 9;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_2.hsn = 45;

   pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_2.length_of_MA_Frequency_List_contents = 0;

   {
      static const OSOCTET testdata[] = { 
      0x39, 0xa8, 0xe9 };
      pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_2.ma_Frequency_List_contents.numocts = 3;
      OSCRTLSAFEMEMCPY ((void*)pvalue->ipa_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_2.ma_Frequency_List_contents.data, 3, testdata, 3);
   }

   pvalue->m.ipa_Downlink_Assignment_structPresent = 1;

   /* zero elements */

   pvalue->ipa_Downlink_Assignment_struct.m.link_quality_measurement_modePresent = 1;
   pvalue->ipa_Downlink_Assignment_struct.link_quality_measurement_mode = 1;

   pvalue->ipa_Downlink_Assignment_struct.rlc_mode = 0;

   pvalue->ipa_Downlink_Assignment_struct.tn = 5;

   pvalue->ipa_Downlink_Assignment_struct.m.frequency_ParametersPresent = 1;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.tsc = 5;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.t =  3;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.maio = 9;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.hsn = 61;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.n = 7;
   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem = rtxMemAllocArrayZ (pctxt, 7, OSUINT8);
   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[0] = 5;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[1] = 5;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[2] = 11;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[3] = 12;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[4] = 4;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[5] = 13;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[6] = 12;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.t =  1;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_length = 21;

   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_bitmap.numbits = 22;
   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_bitmap.data[0] = 0x55;
   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_bitmap.data[1] = 0x53;
   pvalue->ipa_Downlink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_bitmap.data[2] = 0x69;

   pvalue->m.ipa_Single_Block_Uplink_Assignment_structPresent = 1;

   /* zero elements */

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.tn = 5;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.m.frequency_ParametersPresent = 1;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.tsc = 5;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.t =  3;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.maio = 38;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.hsn = 47;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.n = 4;
   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem = rtxMemAllocArrayZ (pctxt, 4, OSUINT8);
   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[0] = 4;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[1] = 3;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[2] = 6;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[3] = 14;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.t =  2;
   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_2.n = 5;
   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_2.elem = rtxMemAllocArrayZ (pctxt, 5, OSUINT8);
   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_2.elem[0] = 12;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_2.elem[1] = 1;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_2.elem[2] = 19;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_2.elem[3] = 26;

   pvalue->ipa_Single_Block_Uplink_Assignment_struct.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_2.elem[4] = 59;



   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_IPA_Rest_Octets (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode IPA_Rest_Octets failed; status = %d\n", ret);
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
