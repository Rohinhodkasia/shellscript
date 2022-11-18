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
   TS44018IE_SI4_Rest_Octets value;
   TS44018IE_SI4_Rest_Octets* pvalue = &value;
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

   asn1Init_TS44018IE_SI4_Rest_Octets (pvalue);
   pvalue->m.si4_Rest_Octets_OPresent = 1;

   pvalue->si4_Rest_Octets_O.m.optional_Selection_ParametersPresent = 1;

   pvalue->si4_Rest_Octets_O.optional_Selection_Parameters.m.selection_ParametersPresent = 1;

   pvalue->si4_Rest_Octets_O.optional_Selection_Parameters.selection_Parameters.cbq = 0;

   pvalue->si4_Rest_Octets_O.optional_Selection_Parameters.selection_Parameters.cell_reselect_offset = 36;

   pvalue->si4_Rest_Octets_O.optional_Selection_Parameters.selection_Parameters.temporary_offset = 1;

   pvalue->si4_Rest_Octets_O.optional_Selection_Parameters.selection_Parameters.penalty_time = 14;

   pvalue->si4_Rest_Octets_O.m.optional_Power_OffsetPresent = 1;

   pvalue->si4_Rest_Octets_O.optional_Power_Offset.m.power_OffsetPresent = 1;
   pvalue->si4_Rest_Octets_O.optional_Power_Offset.power_Offset = 0;

   pvalue->si4_Rest_Octets_O.m.gprs_IndicatorPresent = 1;

   pvalue->si4_Rest_Octets_O.gprs_Indicator.ra_colour = 1;

   pvalue->si4_Rest_Octets_O.gprs_Indicator.si13_position = 0;

   pvalue->m.component_2Present = 1;
   pvalue->component_2.t =  2;

   pvalue->component_2.u.si4_Rest_Octets_S.m.si4_LSA_ParametersPresent = 1;

   pvalue->component_2.u.si4_Rest_Octets_S.si4_LSA_Parameters.prio_thr = 2;

   pvalue->component_2.u.si4_Rest_Octets_S.si4_LSA_Parameters.lsa_offset = 6;

   pvalue->component_2.u.si4_Rest_Octets_S.si4_LSA_Parameters.m.component_3Present = 1;

   pvalue->component_2.u.si4_Rest_Octets_S.si4_LSA_Parameters.component_3.mcc = 1422;

   pvalue->component_2.u.si4_Rest_Octets_S.si4_LSA_Parameters.component_3.mnc = 3150;

   pvalue->component_2.u.si4_Rest_Octets_S.m.cell_IdentityPresent = 1;
   pvalue->component_2.u.si4_Rest_Octets_S.cell_Identity = 27389;

   pvalue->component_2.u.si4_Rest_Octets_S.m.lsa_ID_informationPresent = 1;

   pvalue->component_2.u.si4_Rest_Octets_S.lsa_ID_information.first.t =  1;
   pvalue->component_2.u.si4_Rest_Octets_S.lsa_ID_information.first.u.lsa_id = 11790;

   pvalue->component_2.u.si4_Rest_Octets_S.lsa_ID_information.additional.n = 2;
   pvalue->component_2.u.si4_Rest_Octets_S.lsa_ID_information.additional.elem = rtxMemAllocArrayZ (pctxt, 2, TS44018IE_LSA_identity);
   pvalue->component_2.u.si4_Rest_Octets_S.lsa_ID_information.additional.elem[0].t =  1;
   pvalue->component_2.u.si4_Rest_Octets_S.lsa_ID_information.additional.elem[0].u.lsa_id = 5040;

   pvalue->component_2.u.si4_Rest_Octets_S.lsa_ID_information.additional.elem[1].t =  2;
   pvalue->component_2.u.si4_Rest_Octets_S.lsa_ID_information.additional.elem[1].u.shortLSA_ID = 562;

   pvalue->component_2.u.si4_Rest_Octets_S.m.component_4Present = 1;

   pvalue->component_2.u.si4_Rest_Octets_S.component_4.cbq3 = 1;

   pvalue->component_2.u.si4_Rest_Octets_S.component_4.m.si13alt_PositionPresent = 1;
   pvalue->component_2.u.si4_Rest_Octets_S.component_4.si13alt_Position = 0;


   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_SI4_Rest_Octets (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode SI4_Rest_Octets failed; status = %d\n", ret);
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
