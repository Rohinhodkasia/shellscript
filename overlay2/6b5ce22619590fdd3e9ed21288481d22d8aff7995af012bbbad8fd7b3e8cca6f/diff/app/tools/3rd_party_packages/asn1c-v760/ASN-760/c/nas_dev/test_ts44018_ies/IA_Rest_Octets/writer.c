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
   TS44018IE_IA_Rest_Octets value;
   TS44018IE_IA_Rest_Octets* pvalue = &value;
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

   asn1Init_TS44018IE_IA_Rest_Octets (pvalue);
   pvalue->t = 3;
   pvalue->u.choice_3.frequency_Parameters_before_time.length_of_frequency_parameters = 0; /* length will be calculated */
   pvalue->u.choice_3.frequency_Parameters_before_time.m.component_2Present = 1;
   pvalue->u.choice_3.frequency_Parameters_before_time.component_2.spare = 0;
   pvalue->u.choice_3.frequency_Parameters_before_time.component_2.maio = 55;
   pvalue->u.choice_3.frequency_Parameters_before_time.component_2.mobile_Allocation.numocts = 4;
   pvalue->u.choice_3.frequency_Parameters_before_time.component_2.mobile_Allocation.data = (OSOCTET*) rtxMemAlloc (pctxt, 4);
   {
      static const OSOCTET testdata[] = {
      0xab, 0xcd, 0xef, 0x23 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->u.choice_3.frequency_Parameters_before_time.component_2.mobile_Allocation.data, 4, testdata, 4);
   }


   pvalue->u.choice_3.compressed_Inter_RAT_HO_INFO_IND = TS44018IE_LHType_lbit;


   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_IA_Rest_Octets (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode IA_Rest_Octets failed; status = %d\n", ret);
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
