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
   TS44018IE_P1_Rest_Octets value;
   TS44018IE_P1_Rest_Octets* pvalue = &value;
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

   asn1Init_TS44018IE_P1_Rest_Octets (pvalue);
   pvalue->m.component_1Present = 1;

   pvalue->component_1.nln_pch = 1;

   pvalue->component_1.nln_status_PCH = 0;

   pvalue->m.priority1Present = 1;
   pvalue->priority1 = 4;

   pvalue->m.priority2Present = 1;
   pvalue->priority2 = 4;

   pvalue->m.group_Call_informationPresent = 0;

   pvalue->m.packet_Page_Indication_1Present = 1;
   pvalue->packet_Page_Indication_1 = TS44018IE_LHType_lbit;

   pvalue->m.packet_Page_Indication_2Present = 1;
   pvalue->packet_Page_Indication_2 = TS44018IE_LHType_hbit;

   pvalue->m.component_7Present = 1;

   pvalue->component_7.m.component_1Present = 1;
   pvalue->component_7.component_1.t =  4;

   pvalue->component_7.component_1.u.choice_4.cell_global_count = 0;

   pvalue->component_7.component_1.u.choice_4.reduced_GCR = 32182;

   pvalue->component_7.component_1.u.choice_4.vstk_rand[0] = 0xe6;
   pvalue->component_7.component_1.u.choice_4.vstk_rand[1] = 0xe5;
   pvalue->component_7.component_1.u.choice_4.vstk_rand[2] = 0x1f;
   pvalue->component_7.component_1.u.choice_4.vstk_rand[3] = 0xa3;
   pvalue->component_7.component_1.u.choice_4.vstk_rand[4] = 0x43;

   pvalue->component_7.m.component_2Present = 1;

   pvalue->component_7.component_2.m.mbms_Notification_1Present = 1;
   pvalue->component_7.component_2.mbms_Notification_1.t =  1;

   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.m.component_1Present = 1;

   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.m.frequency_ParametersPresent = 1;

   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.tsc = 6;
   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.t = 3;
   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.maio = 15;
   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.hsn = 14;
   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.n = 3;
   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem = rtxMemAllocArray(pctxt, 3, OSUINT8);
   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[0] = 7;
   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[1] = 8;
   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.rfl_number_list.elem[2] = 9;
   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.t = 1;
   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_length = 0;
   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_bitmap.numbits = 1;
   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_1.gprs_Mobile_Allocation.component_3.u.choice_1.ma_bitmap.data[0] = 0x80;

   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_p_t_m_channel_description.dl_timeslot_allocation = 37;

   pvalue->component_7.component_2.mbms_Notification_1.u.choice_1.component_1.mbms_Session_Parameters_List.n = 0;

   pvalue->component_7.component_2.m.mbms_Notification_2Present = 1;
   pvalue->component_7.component_2.mbms_Notification_2.m.mbms_Channel_Parameters_IEPresent = 1;
   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.t =  1;
   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.m.component_1Present = 1;
   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.m.frequency_ParametersPresent = 1;
   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.tsc = 6;
   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.t = 4;
   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_2.maio = 9;
   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_2.hsn = 10;
   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_2.length_of_MA_Frequency_List_contents = 1;
   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_2.ma_Frequency_List_contents.numocts = 4;
   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_2.ma_Frequency_List_contents.data[0] = 0xAB;
   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_2.ma_Frequency_List_contents.data[1] = 0xCD;
   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_2.ma_Frequency_List_contents.data[2] = 0xEF;
   pvalue->component_7.component_2.mbms_Notification_2.mbms_Channel_Parameters_IE.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.direct_encoding_2.ma_Frequency_List_contents.data[3] = 0xAB;


   pvalue->component_7.component_2.m.mbms_InformationPresent = 1;

   /* zero elements */

   pvalue->component_7.component_2.mbms_Information.m.component_2Present = 1;

   pvalue->component_7.component_2.mbms_Information.component_2.same_as_notification_flag = 1;

   /* zero elements */

   /* zero elements */

   pvalue->m.component_8Present = 1;

   pvalue->component_8.m.amr_ConfigPresent = 1;
   pvalue->component_8.amr_Config = 7;

   pvalue->m.component_9Present = 0;

   pvalue->m.component_10Present = 0;

   pvalue->m.ipa_SupportPresent = 1;
   pvalue->ipa_Support = 1;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_P1_Rest_Octets (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode P1_Rest_Octets failed; status = %d\n", ret);
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
