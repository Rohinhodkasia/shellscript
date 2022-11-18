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
   TS44018IE_RR_Packet_Downlink_Assignment_Type_2 value;
   TS44018IE_RR_Packet_Downlink_Assignment_Type_2* pvalue = &value;
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

   asn1Init_TS44018IE_RR_Packet_Downlink_Assignment_Type_2 (pvalue);
   pvalue->length = 0; /* length will be calculated */

   pvalue->rlc_mode = 0;

   pvalue->m.component_3Present = 1;

   pvalue->component_3.p0_c1 = 9;

   pvalue->component_3.pr_mode_c1 = 0;

   pvalue->component_3.m.component_3Present = 1;

   pvalue->component_3.component_3.p0_c2 = 1;

   pvalue->component_3.component_3.pr_mode_c2 = 0;

   pvalue->m.power_Control_Parameters_C1Present = 1;

   pvalue->power_Control_Parameters_C1.alpha = 9;

   pvalue->power_Control_Parameters_C1.m.gamma_tn0Present = 1;
   pvalue->power_Control_Parameters_C1.gamma_tn0 = 28;

   pvalue->power_Control_Parameters_C1.m.gamma_tn1Present = 1;
   pvalue->power_Control_Parameters_C1.gamma_tn1 = 2;

   pvalue->power_Control_Parameters_C1.m.gamma_tn2Present = 1;
   pvalue->power_Control_Parameters_C1.gamma_tn2 = 19;

   pvalue->power_Control_Parameters_C1.m.gamma_tn3Present = 1;
   pvalue->power_Control_Parameters_C1.gamma_tn3 = 12;

   pvalue->power_Control_Parameters_C1.m.gamma_tn4Present = 1;
   pvalue->power_Control_Parameters_C1.gamma_tn4 = 12;

   pvalue->power_Control_Parameters_C1.m.gamma_tn5Present = 1;
   pvalue->power_Control_Parameters_C1.gamma_tn5 = 30;

   pvalue->power_Control_Parameters_C1.m.gamma_tn6Present = 1;
   pvalue->power_Control_Parameters_C1.gamma_tn6 = 3;

   pvalue->power_Control_Parameters_C1.m.gamma_tn7Present = 1;
   pvalue->power_Control_Parameters_C1.gamma_tn7 = 18;

   pvalue->m.power_Control_Parameters_C2Present = 1;

   pvalue->power_Control_Parameters_C2.alpha = 12;

   pvalue->power_Control_Parameters_C2.m.gamma_tn0Present = 1;
   pvalue->power_Control_Parameters_C2.gamma_tn0 = 30;

   pvalue->power_Control_Parameters_C2.m.gamma_tn1Present = 1;
   pvalue->power_Control_Parameters_C2.gamma_tn1 = 27;

   pvalue->power_Control_Parameters_C2.m.gamma_tn2Present = 1;
   pvalue->power_Control_Parameters_C2.gamma_tn2 = 27;

   pvalue->power_Control_Parameters_C2.m.gamma_tn3Present = 1;
   pvalue->power_Control_Parameters_C2.gamma_tn3 = 24;

   pvalue->power_Control_Parameters_C2.m.gamma_tn4Present = 1;
   pvalue->power_Control_Parameters_C2.gamma_tn4 = 17;

   pvalue->power_Control_Parameters_C2.m.gamma_tn5Present = 1;
   pvalue->power_Control_Parameters_C2.gamma_tn5 = 4;

   pvalue->power_Control_Parameters_C2.m.gamma_tn6Present = 1;
   pvalue->power_Control_Parameters_C2.gamma_tn6 = 24;

   pvalue->power_Control_Parameters_C2.m.gamma_tn7Present = 1;
   pvalue->power_Control_Parameters_C2.gamma_tn7 = 23;

   pvalue->m.downlink_tfi_assignmentPresent = 1;
   pvalue->downlink_tfi_assignment = 21;

   pvalue->egprs_Window_Size = 19;

   pvalue->link_quality_measurement_mode = 1;

   pvalue->component_9.t =  1;

   pvalue->component_9.u.choice_1.fanr = 0;

   /* zero elements */

   pvalue->downlink_EGPRS_Level = 0;

   pvalue->m.component_11Present = 1;

   pvalue->component_11.m.component_1Present = 1;
   /* zero elements */

   pvalue->component_11.m.component_2Present = 1;
   /* zero elements */

   pvalue->component_11.m.component_3Present = 1;

   pvalue->component_11.component_3.m.component_1Present = 1;

   pvalue->component_11.component_3.component_1.rlc_Entity_2.downlink_tfi_assignment = 24;

   pvalue->component_11.component_3.component_1.rlc_Entity_2.rlc_mode = 0;

   pvalue->component_11.component_3.component_1.rlc_Entity_2.m.egprs_Window_SizePresent = 1;
   pvalue->component_11.component_3.component_1.rlc_Entity_2.egprs_Window_Size = 5;

   pvalue->component_11.component_3.component_1.rlc_Entity_2.pfi = 97;

   pvalue->component_11.component_3.component_1.m.rlc_Entity_3Present = 1;

   pvalue->component_11.component_3.component_1.rlc_Entity_3.downlink_tfi_assignment = 29;

   pvalue->component_11.component_3.component_1.rlc_Entity_3.rlc_mode = 0;

   pvalue->component_11.component_3.component_1.rlc_Entity_3.m.egprs_Window_SizePresent = 1;
   pvalue->component_11.component_3.component_1.rlc_Entity_3.egprs_Window_Size = 1;

   pvalue->component_11.component_3.component_1.rlc_Entity_3.pfi = 89;

   pvalue->component_11.component_3.m.component_2Present = 1;

   /* zero elements */

   /* zero elements */

   /* zero elements */

   pvalue->component_11.component_3.component_2.m.egprs_Packet_Downlink_Ack_Nack_Type_3_SupportPresent = 1;
   pvalue->component_11.component_3.component_2.egprs_Packet_Downlink_Ack_Nack_Type_3_Support = 0;


   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_RR_Packet_Downlink_Assignment_Type_2 (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode RR_Packet_Downlink_Assignment_Type_2 failed; status = %d\n", ret);
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
