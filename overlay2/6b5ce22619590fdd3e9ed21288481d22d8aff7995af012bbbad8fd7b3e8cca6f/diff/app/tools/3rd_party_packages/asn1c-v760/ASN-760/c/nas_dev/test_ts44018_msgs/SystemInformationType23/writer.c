#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018IE_SI23_Rest_Octets* asn1Test_TS44018IE_SI23_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_SI23_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_SI23_Rest_Octets);
   asn1Init_TS44018IE_SI23_Rest_Octets (pvalue);

   pvalue->si_23_3g_ba_ind = 0;

   pvalue->si_23_change_mark = 0;

   pvalue->si_23_index = 1;

   pvalue->si_23_count = 1;

   pvalue->m.irat_Cell_Reselection_InformationPresent = 1;

   pvalue->irat_Cell_Reselection_Information.priority_and_UTRAN_Parameters_Description_for_the_Common_PLMN.m.component_1Present = 1;

   pvalue->irat_Cell_Reselection_Information.priority_and_UTRAN_Parameters_Description_for_the_Common_PLMN.component_1.m.component_1Present = 1;

   pvalue->irat_Cell_Reselection_Information.priority_and_UTRAN_Parameters_Description_for_the_Common_PLMN.component_1.component_1.m.default_utran_priorityPresent = 1;
   pvalue->irat_Cell_Reselection_Information.priority_and_UTRAN_Parameters_Description_for_the_Common_PLMN.component_1.component_1.default_utran_priority = 6;

   pvalue->irat_Cell_Reselection_Information.priority_and_UTRAN_Parameters_Description_for_the_Common_PLMN.component_1.component_1.m.default_THRESH_UTRAN_lowPresent = 1;
   pvalue->irat_Cell_Reselection_Information.priority_and_UTRAN_Parameters_Description_for_the_Common_PLMN.component_1.component_1.default_THRESH_UTRAN_low = 6;

   pvalue->irat_Cell_Reselection_Information.priority_and_UTRAN_Parameters_Description_for_the_Common_PLMN.component_1.component_1.m.default_utran_qrxlevminPresent = 1;
   pvalue->irat_Cell_Reselection_Information.priority_and_UTRAN_Parameters_Description_for_the_Common_PLMN.component_1.component_1.default_utran_qrxlevmin = 3;

   pvalue->irat_Cell_Reselection_Information.priority_and_UTRAN_Parameters_Description_for_the_Common_PLMN.component_1.m.utran_FDD_TDD_DescriptionPresent = 1;

   pvalue->irat_Cell_Reselection_Information.priority_and_UTRAN_Parameters_Description_for_the_Common_PLMN.component_1.utran_FDD_TDD_Description.m.bandwidthPresent = 1;
   pvalue->irat_Cell_Reselection_Information.priority_and_UTRAN_Parameters_Description_for_the_Common_PLMN.component_1.utran_FDD_TDD_Description.bandwidth = 4;

   /* zero elements */

   pvalue->irat_Cell_Reselection_Information.priority_and_E_UTRAN_Parameters_Description_for_the_Common_PLMN.m.component_1Present = 1;

   pvalue->irat_Cell_Reselection_Information.priority_and_E_UTRAN_Parameters_Description_for_the_Common_PLMN.component_1.m.component_1Present = 1;

   pvalue->irat_Cell_Reselection_Information.priority_and_E_UTRAN_Parameters_Description_for_the_Common_PLMN.component_1.component_1.m.default_e_utran_priorityPresent = 1;
   pvalue->irat_Cell_Reselection_Information.priority_and_E_UTRAN_Parameters_Description_for_the_Common_PLMN.component_1.component_1.default_e_utran_priority = 4;

   pvalue->irat_Cell_Reselection_Information.priority_and_E_UTRAN_Parameters_Description_for_the_Common_PLMN.component_1.component_1.m.default_THRESH_E_UTRAN_lowPresent = 1;
   pvalue->irat_Cell_Reselection_Information.priority_and_E_UTRAN_Parameters_Description_for_the_Common_PLMN.component_1.component_1.default_THRESH_E_UTRAN_low = 1;

   pvalue->irat_Cell_Reselection_Information.priority_and_E_UTRAN_Parameters_Description_for_the_Common_PLMN.component_1.component_1.m.default_e_utran_qrxlevminPresent = 1;
   pvalue->irat_Cell_Reselection_Information.priority_and_E_UTRAN_Parameters_Description_for_the_Common_PLMN.component_1.component_1.default_e_utran_qrxlevmin = 20;

   /* zero elements */

   /* zero elements */

   /* zero elements */

   pvalue->irat_Cell_Reselection_Information.priority_and_E_UTRAN_Parameters_Description_for_the_Common_PLMN.component_1.m.enhanced_Cell_Reselection_Parameters_DescriptionPresent = 1;
   /* zero elements */

   pvalue->irat_Cell_Reselection_Information.nb_Additional_PLMNs = 0;

   pvalue->irat_Cell_Reselection_Information.component_4.n = 1;

   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].plmn_index = 0;

   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_UTRAN_Parameters_Description.m.component_1Present = 1;

   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_UTRAN_Parameters_Description.component_1.m.component_1Present = 1;

   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_UTRAN_Parameters_Description.component_1.component_1.m.default_utran_priorityPresent = 1;
   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_UTRAN_Parameters_Description.component_1.component_1.default_utran_priority = 6;

   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_UTRAN_Parameters_Description.component_1.component_1.m.default_THRESH_UTRAN_lowPresent = 1;
   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_UTRAN_Parameters_Description.component_1.component_1.default_THRESH_UTRAN_low = 14;

   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_UTRAN_Parameters_Description.component_1.component_1.m.default_utran_qrxlevminPresent = 1;
   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_UTRAN_Parameters_Description.component_1.component_1.default_utran_qrxlevmin = 24;

   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_UTRAN_Parameters_Description.component_1.m.utran_FDD_TDD_DescriptionPresent = 1;

   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_UTRAN_Parameters_Description.component_1.utran_FDD_TDD_Description.m.bandwidthPresent = 1;
   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_UTRAN_Parameters_Description.component_1.utran_FDD_TDD_Description.bandwidth = 3;
   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_UTRAN_Parameters_Description.component_1.utran_FDD_TDD_Description.repeated_UTRAN_FDD_TDD_Neighbour_Frequency_and_Priority_list.n = 0;

   /* zero elements */

   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_E_UTRAN_Parameters_Description.m.component_1Present = 1;

   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_E_UTRAN_Parameters_Description.component_1.m.component_1Present = 1;

   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_E_UTRAN_Parameters_Description.component_1.component_1.m.default_e_utran_priorityPresent = 1;
   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_E_UTRAN_Parameters_Description.component_1.component_1.default_e_utran_priority = 1;

   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_E_UTRAN_Parameters_Description.component_1.component_1.m.default_THRESH_E_UTRAN_lowPresent = 1;
   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_E_UTRAN_Parameters_Description.component_1.component_1.default_THRESH_E_UTRAN_low = 21;

   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_E_UTRAN_Parameters_Description.component_1.component_1.m.default_e_utran_qrxlevminPresent = 1;
   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_E_UTRAN_Parameters_Description.component_1.component_1.default_e_utran_qrxlevmin = 11;
   
   /* zero elements */
   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_E_UTRAN_Parameters_Description.component_1.repeated_E_UTRAN_Neighbour_Frequency_and_Priority_list.n = 0;

   /* zero elements */
   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_E_UTRAN_Parameters_Description.component_1.repeated_E_UTRAN_Not_Allowed_Cells_list.n = 0;    

   /* zero elements */
   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_E_UTRAN_Parameters_Description.component_1.repeated_E_UTRAN_PCID_to_TA_mapping_list.n = 0;

   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_E_UTRAN_Parameters_Description.component_1.m.enhanced_Cell_Reselection_Parameters_DescriptionPresent = 1;
   /* zero elements */
   pvalue->irat_Cell_Reselection_Information.component_4.elem[0].priority_and_E_UTRAN_Parameters_Description.component_1.enhanced_Cell_Reselection_Parameters_Description.n = 0;

   return (pvalue);
}


int main (int argc, char** argv)
{
   TS44018Msg_L2_PSEUDO_LEN_PDU pdu;

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

   asn1Init_TS44018Msg_L2_PSEUDO_LEN_PDU (&pdu);
   pdu.l3HdrOpts.t = 1;
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;
   pdu.msgType = ASN1V_ts44018Msg_mt_SystemInformationType23;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType23;

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType23;
   pdu.restOctets.u.obj_SystemInformationType23 =
      asn1Test_TS44018IE_SI23_Rest_Octets(pctxt);


   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_L2_PSEUDO_LEN_PDU (&ctxt, &pdu);
   if (0 != ret) {
      printf ("encode PDU failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }
   /* Verify buffer is byte-aligned */
   OSRTASSERT (ctxt.buffer.bitOffset == 8 || ctxt.buffer.bitOffset == 0);

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
