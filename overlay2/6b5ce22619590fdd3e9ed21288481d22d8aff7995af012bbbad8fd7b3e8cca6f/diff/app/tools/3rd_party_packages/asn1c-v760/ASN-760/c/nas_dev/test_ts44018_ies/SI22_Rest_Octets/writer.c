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
   TS44018IE_SI22_Rest_Octets value;
   TS44018IE_SI22_Rest_Octets* pvalue = &value;
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

   asn1Init_TS44018IE_SI22_Rest_Octets (pvalue);
   pvalue->si_22_change_mark = 2;

   pvalue->si_22_index = 0;

   pvalue->si_22_count = 5;

   pvalue->m.network_Sharing_InformationPresent = 1;

   pvalue->network_Sharing_Information.si23_Indicator = 0;

   pvalue->network_Sharing_Information.common_PLMN_Allowed = 0;

   pvalue->network_Sharing_Information.m.common_PLMN_PS_ACCPresent = 1;
   pvalue->network_Sharing_Information.common_PLMN_PS_ACC = 22863;

   pvalue->network_Sharing_Information.nb_Additional_PLMNs = 0;

   pvalue->network_Sharing_Information.component_5.n = 1;

   pvalue->network_Sharing_Information.component_5.elem[0].m.mccPresent = 1;
   pvalue->network_Sharing_Information.component_5.elem[0].mcc = 2192;

   pvalue->network_Sharing_Information.component_5.elem[0].mnc = 1631;

   pvalue->network_Sharing_Information.component_5.elem[0].ncc_Permitted = 156;

   pvalue->network_Sharing_Information.component_5.elem[0].m.additional_ACCPresent = 1;
   pvalue->network_Sharing_Information.component_5.elem[0].additional_ACC = 753;

   pvalue->network_Sharing_Information.component_5.elem[0].m.component_5Present = 1;

   pvalue->network_Sharing_Information.component_5.elem[0].component_5.m.ps_accPresent = 1;
   pvalue->network_Sharing_Information.component_5.elem[0].component_5.ps_acc = 28500;


   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_SI22_Rest_Octets (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode SI22_Rest_Octets failed; status = %d\n", ret);
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
