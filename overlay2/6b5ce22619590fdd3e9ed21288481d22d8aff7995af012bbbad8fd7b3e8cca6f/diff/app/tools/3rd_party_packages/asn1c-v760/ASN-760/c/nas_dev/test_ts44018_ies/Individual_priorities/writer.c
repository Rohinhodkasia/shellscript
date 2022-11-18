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
   TS44018IE_Individual_priorities value;
   TS44018IE_Individual_priorities* pvalue = &value;
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

   asn1Init_TS44018IE_Individual_priorities (pvalue);
   pvalue->length = 0; /* length will be calculated */

   pvalue->m.component_2Present = 1;

   pvalue->component_2.geran_priority = 5;

   pvalue->component_2.m.a3G_Individual_Priority_Parameters_DescriptionPresent = 1;

   pvalue->component_2.a3G_Individual_Priority_Parameters_Description.m.default_utran_priorityPresent = 1;
   pvalue->component_2.a3G_Individual_Priority_Parameters_Description.default_utran_priority = 3;

   /* zero elements */

   pvalue->component_2.m.e_UTRAN_Individual_Priority_Parameters_DescriptionPresent = 1;

   pvalue->component_2.e_UTRAN_Individual_Priority_Parameters_Description.m.default_e_utran_priorityPresent = 1;
   pvalue->component_2.e_UTRAN_Individual_Priority_Parameters_Description.default_e_utran_priority = 0;

   /* zero elements */

   pvalue->component_2.m.t3230_timeout_valuePresent = 1;
   pvalue->component_2.t3230_timeout_value = 3;


   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_Individual_priorities (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode Individual_priorities failed; status = %d\n", ret);
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
