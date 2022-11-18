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
   TS44018IE_SI9_Rest_Octets value;
   TS44018IE_SI9_Rest_Octets* pvalue = &value;
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

   asn1Init_TS44018IE_SI9_Rest_Octets (pvalue);
   pvalue->m.scheduling_info_listPresent = 1;

   pvalue->scheduling_info_list.scheduling_info.info_type.t =  2;
   pvalue->scheduling_info_list.scheduling_info.info_type.u.info_type_5 = 11;

   pvalue->scheduling_info_list.scheduling_info.positions.position.modulus = 3;

   pvalue->scheduling_info_list.scheduling_info.positions.position.component_1.u.choice_2.relative_position.numbits = 4;
   pvalue->scheduling_info_list.scheduling_info.positions.position.component_1.u.choice_2.relative_position.data[0] = 0x64;

   pvalue->scheduling_info_list.scheduling_info.positions.position.component_1.u.choice_2.bcch_type = 0;

   pvalue->scheduling_info_list.scheduling_info.positions.m.position2Present = 1;

   pvalue->scheduling_info_list.scheduling_info.positions.position2.modulus = 5;

   pvalue->scheduling_info_list.scheduling_info.positions.position2.component_1.u.choice_2.relative_position.numbits = 6;
   pvalue->scheduling_info_list.scheduling_info.positions.position2.component_1.u.choice_2.relative_position.data[0] = 0x44;

   pvalue->scheduling_info_list.scheduling_info.positions.position2.component_1.u.choice_2.bcch_type = 0;

   /* zero elements */

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_SI9_Rest_Octets (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode SI9_Rest_Octets failed; status = %d\n", ret);
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
