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
   TS44018IE_P2_Rest_Octets value;
   TS44018IE_P2_Rest_Octets* pvalue = &value;
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

   asn1Init_TS44018IE_P2_Rest_Octets (pvalue);
   pvalue->m.cn3Present = 1;
   pvalue->cn3 = 3;

   pvalue->m.component_2Present = 1;

   pvalue->component_2.nln_pch = 1;

   pvalue->component_2.nln_status_PCH = 0;

   pvalue->m.priority1Present = 1;
   pvalue->priority1 = 4;

   pvalue->m.priority2Present = 1;
   pvalue->priority2 = 5;

   pvalue->m.priority3Present = 1;
   pvalue->priority3 = 6;

   pvalue->m.packet_Page_Indication_3Present = 1;
   pvalue->packet_Page_Indication_3 = TS44018IE_LHType_lbit;

   pvalue->m.component_7Present = 1;

   pvalue->component_7.m.component_1Present = 1;
   pvalue->component_7.component_1.m.mbms_Notification_3Present = 1;
   pvalue->component_7.component_1.mbms_Notification_3.t =  1;

   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.m.component_1Present = 1;

   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.m.frequency_ParametersPresent = 1;

   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.tsc = 6;
   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.t = 3;
   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.maio = 15;
   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.hsn = 14;
   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.n = 3;
   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem = rtxMemAllocArray(pctxt, 3, OSUINT8);
   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[0] = 7;
   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[1] = 8;
   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[2] = 9;
   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.t = 1;
   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_length = 0;
   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_bitmap.numbits = 1;
   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_bitmap.data[0] = 0x80;

   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.dl_timeslot_allocation = 37;

   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_Session_Parameters_List.n = 0;

   pvalue->component_7.component_1.m.p2_MBMS_InformationPresent = 1;
   pvalue->component_7.component_1.p2_MBMS_Information.mbms_Sessions_List.n = 2;
   pvalue->component_7.component_1.p2_MBMS_Information.mbms_Sessions_List.elem = rtxMemAllocArray(pctxt, 2, TS44060IE_MBMS_Session_List_IE_element);
   pvalue->component_7.component_1.p2_MBMS_Information.mbms_Sessions_List.elem[0].tmgi.t = 1;
   pvalue->component_7.component_1.p2_MBMS_Information.mbms_Sessions_List.elem[0].tmgi.u.mbms_service_id = 11259375;
   pvalue->component_7.component_1.p2_MBMS_Information.mbms_Sessions_List.elem[0].m.mbms_Session_IdentityPresent = 0;
   pvalue->component_7.component_1.p2_MBMS_Information.mbms_Sessions_List.elem[1].tmgi.t = 2;
   pvalue->component_7.component_1.p2_MBMS_Information.mbms_Sessions_List.elem[1].tmgi.u.choice_2.mbms_service_id = 74565;
   pvalue->component_7.component_1.p2_MBMS_Information.mbms_Sessions_List.elem[1].tmgi.u.choice_2.mcc = 0x7bc;
   pvalue->component_7.component_1.p2_MBMS_Information.mbms_Sessions_List.elem[1].tmgi.u.choice_2.mnc = 0xfff;
   pvalue->component_7.component_1.p2_MBMS_Information.mbms_Sessions_List.elem[1].m.mbms_Session_IdentityPresent = 1;
   pvalue->component_7.component_1.p2_MBMS_Information.mbms_Sessions_List.elem[1].mbms_Session_Identity = 43;

   pvalue->component_7.component_1.p2_MBMS_Information.m.mbms_Sessions_List_2Present = 0;
   pvalue->component_7.component_1.p2_MBMS_Information.component_3.n = 0;

   pvalue->m.component_8Present = 0;
   pvalue->m.ipa_SupportPresent = 0;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_P2_Rest_Octets (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode P2_Rest_Octets failed; status = %d\n", ret);
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
