#include "TS44018Msgs.h"
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
   TS44018Msg_RR_Short_PD_PDU pdu;
   TS44018Msg_Measurement_information measInfoData;
   TS44018Msg_Measurement_information* pvalue = &measInfoData;

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

   asn1Init_TS44018Msg_RR_Short_PD_PDU (&pdu);
   pdu.rr_short_PD = 0;
   pdu.msgType = ASN1V_ts44018Msg_mt_measurement_information;
   pdu.short_layer_2_header = 0;
   pdu.data.t = T_TS44018Msgs_RR_Short_PD_Messages_obj_measurement_information;
   pdu.data.u.obj_measurement_information = pvalue;


   asn1Init_TS44018Msg_Measurement_information (pvalue);

   pvalue->ba_ind = 0;

   pvalue->a3G_BA_IND = 0;

   pvalue->mp_change_mark = 0;

   pvalue->mi_index = 6;

   pvalue->mi_count = 14;

   pvalue->pwrc = 0;

   pvalue->report_type = 0;

   pvalue->reporting_rate = 0;

   pvalue->invalid_bsic_reporting = 0;

   pvalue->m.real_Time_Difference_DescriptionPresent = 1;

   pvalue->real_Time_Difference_Description.m.component_1Present = 1;

   pvalue->real_Time_Difference_Description.component_1.m.ba_Index_Start_RTDPresent = 1;
   pvalue->real_Time_Difference_Description.component_1.ba_Index_Start_RTD = 24;

   pvalue->real_Time_Difference_Description.component_1.rtd_Struct.n = 2;
   pvalue->real_Time_Difference_Description.component_1.rtd_Struct.elem = rtxMemAllocArrayZ (pctxt, 2, OSUINT8);
   pvalue->real_Time_Difference_Description.component_1.rtd_Struct.elem[0] = 44;
   pvalue->real_Time_Difference_Description.component_1.rtd_Struct.elem[1] = 45;

   pvalue->real_Time_Difference_Description.component_1.rtd_Struct_list.n = 2;
   pvalue->real_Time_Difference_Description.component_1.rtd_Struct_list.elem = rtxMemAllocArrayZ(pctxt, 2, TS44018Msg_RTD6_Struct);
   pvalue->real_Time_Difference_Description.component_1.rtd_Struct_list.elem[0].n = 2;
   pvalue->real_Time_Difference_Description.component_1.rtd_Struct_list.elem[0].elem = rtxMemAllocArrayZ (pctxt, 2, OSUINT8);
   pvalue->real_Time_Difference_Description.component_1.rtd_Struct_list.elem[0].elem[0] = 46;
   pvalue->real_Time_Difference_Description.component_1.rtd_Struct_list.elem[0].elem[1] = 47;

   pvalue->real_Time_Difference_Description.component_1.rtd_Struct_list.elem[1].n = 2;
   pvalue->real_Time_Difference_Description.component_1.rtd_Struct_list.elem[1].elem = rtxMemAllocArrayZ (pctxt, 2, OSUINT8);
   pvalue->real_Time_Difference_Description.component_1.rtd_Struct_list.elem[1].elem[0] = 48;
   pvalue->real_Time_Difference_Description.component_1.rtd_Struct_list.elem[1].elem[1] = 49;


   pvalue->real_Time_Difference_Description.m.component_2Present = 1;

   pvalue->real_Time_Difference_Description.component_2.m.ba_Index_Start_RTDPresent = 1;
   pvalue->real_Time_Difference_Description.component_2.ba_Index_Start_RTD = 10;

   pvalue->real_Time_Difference_Description.component_2.rtd_Struct.n = 3;
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct.elem = rtxMemAllocArrayZ (pctxt, 3, OSUINT16);
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct.elem[0] = 3193;
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct.elem[1] = 3194;
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct.elem[2] = 3195;

   pvalue->real_Time_Difference_Description.component_2.rtd_Struct_list.n = 3;
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct_list.elem = rtxMemAllocArrayZ(pctxt, 3, TS44018Msg_RTD12_Struct);
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct_list.elem[0].n = 3;
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct_list.elem[0].elem = rtxMemAllocArrayZ (pctxt, 3, OSUINT16);
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct_list.elem[0].elem[0] = 3193;
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct_list.elem[0].elem[1] = 3194;
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct_list.elem[0].elem[2] = 3195;

   pvalue->real_Time_Difference_Description.component_2.rtd_Struct_list.elem[1].n = 3;
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct_list.elem[1].elem = rtxMemAllocArrayZ (pctxt, 3, OSUINT16);
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct_list.elem[1].elem[0] = 3196;
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct_list.elem[1].elem[1] = 3197;
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct_list.elem[1].elem[2] = 3198;
   
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct_list.elem[2].n = 3;
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct_list.elem[2].elem = rtxMemAllocArrayZ (pctxt, 3, OSUINT16);
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct_list.elem[2].elem[0] = 3199;
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct_list.elem[2].elem[1] = 3200;
   pvalue->real_Time_Difference_Description.component_2.rtd_Struct_list.elem[2].elem[2] = 3201;


   pvalue->m.bsic_DescriptionPresent = 1;

   pvalue->bsic_Description.m.ba_Index_Start_BSICPresent = 1;
   pvalue->bsic_Description.ba_Index_Start_BSIC = 14;

   pvalue->bsic_Description.bsic = 15;

   pvalue->bsic_Description.number_Remaining_BSIC = 1;

   pvalue->bsic_Description.component_4.n = 1;
   pvalue->bsic_Description.component_4.elem[0].frequency_Scrolling = 1;
   pvalue->bsic_Description.component_4.elem[0].bsic = 14;

   pvalue->m.report_PRIORITY_DescriptionPresent = 1;

   pvalue->report_PRIORITY_Description.number_Cells = 118;

   pvalue->report_PRIORITY_Description.rep_priority.numbits = 118;
   pvalue->report_PRIORITY_Description.rep_priority.data[0] = 0x39;
   pvalue->report_PRIORITY_Description.rep_priority.data[1] = 0x72;
   pvalue->report_PRIORITY_Description.rep_priority.data[2] = 0x39;
   pvalue->report_PRIORITY_Description.rep_priority.data[3] = 0x55;
   pvalue->report_PRIORITY_Description.rep_priority.data[4] = 0x60;
   pvalue->report_PRIORITY_Description.rep_priority.data[5] = 0x40;
   pvalue->report_PRIORITY_Description.rep_priority.data[6] = 0x70;
   pvalue->report_PRIORITY_Description.rep_priority.data[7] = 0x3d;
   pvalue->report_PRIORITY_Description.rep_priority.data[8] = 0x4c;
   pvalue->report_PRIORITY_Description.rep_priority.data[9] = 0x40;
   pvalue->report_PRIORITY_Description.rep_priority.data[10] = 0x70;
   pvalue->report_PRIORITY_Description.rep_priority.data[11] = 0x3e;
   pvalue->report_PRIORITY_Description.rep_priority.data[12] = 0x3e;
   pvalue->report_PRIORITY_Description.rep_priority.data[13] = 0x67;
   pvalue->report_PRIORITY_Description.rep_priority.data[14] = 0x69;
   pvalue->report_PRIORITY_Description.rep_priority.data[15] = 0x51;

   pvalue->m.measurement_Parameters_DescriptionPresent = 1;

   pvalue->measurement_Parameters_Description.m.multiband_reportingPresent = 1;
   pvalue->measurement_Parameters_Description.multiband_reporting = 2;

   pvalue->measurement_Parameters_Description.m.serving_band_reportingPresent = 1;
   pvalue->measurement_Parameters_Description.serving_band_reporting = 2;

   pvalue->measurement_Parameters_Description.scale_ord = 3;

   pvalue->measurement_Parameters_Description.m.component_4Present = 1;

   pvalue->measurement_Parameters_Description.component_4.a900_REPORTING_OFFSET = 0;

   pvalue->measurement_Parameters_Description.component_4.a900_REPORTING_THRESHOLD = 6;

   pvalue->measurement_Parameters_Description.m.component_5Present = 1;

   pvalue->measurement_Parameters_Description.component_5.a1800_REPORTING_OFFSET = 2;

   pvalue->measurement_Parameters_Description.component_5.a1800_REPORTING_THRESHOLD = 4;

   pvalue->measurement_Parameters_Description.m.component_6Present = 1;

   pvalue->measurement_Parameters_Description.component_6.a400_REPORTING_OFFSET = 3;

   pvalue->measurement_Parameters_Description.component_6.a400_REPORTING_THRESHOLD = 0;

   pvalue->measurement_Parameters_Description.m.component_7Present = 1;

   pvalue->measurement_Parameters_Description.component_7.a1900_REPORTING_OFFSET = 4;

   pvalue->measurement_Parameters_Description.component_7.a1900_REPORTING_THRESHOLD = 6;

   pvalue->measurement_Parameters_Description.m.component_8Present = 1;

   pvalue->measurement_Parameters_Description.component_8.a850_REPORTING_OFFSET = 4;

   pvalue->measurement_Parameters_Description.component_8.a850_REPORTING_THRESHOLD = 1;

   pvalue->m.component_14Present = 1;

   pvalue->component_14.extension_length = 63;

   pvalue->component_14.bit.numbits = 64;
   pvalue->component_14.bit.data[0] = 0x6f;
   pvalue->component_14.bit.data[1] = 0x4a;
   pvalue->component_14.bit.data[2] = 0x31;
   pvalue->component_14.bit.data[3] = 0x45;
   pvalue->component_14.bit.data[4] = 0x53;
   pvalue->component_14.bit.data[5] = 0x63;
   pvalue->component_14.bit.data[6] = 0x45;
   pvalue->component_14.bit.data[7] = 0x70;

   pvalue->m.a3G_Neighbour_Cell_DescriptionPresent = 1;

   pvalue->a3G_Neighbour_Cell_Description.m.a3G_WaitPresent = 1;
   pvalue->a3G_Neighbour_Cell_Description.a3G_Wait = 2;

   pvalue->a3G_Neighbour_Cell_Description.m.index_Start_3GPresent = 1;
   pvalue->a3G_Neighbour_Cell_Description.index_Start_3G = 4;

   pvalue->a3G_Neighbour_Cell_Description.m.absolute_Index_Start_EMRPresent = 1;
   pvalue->a3G_Neighbour_Cell_Description.absolute_Index_Start_EMR = 51;

   pvalue->a3G_Neighbour_Cell_Description.m.utran_FDD_DescriptionPresent = 1;

   pvalue->a3G_Neighbour_Cell_Description.utran_FDD_Description.m.bandwidth_FDDPresent = 1;
   pvalue->a3G_Neighbour_Cell_Description.utran_FDD_Description.bandwidth_FDD = 1;
   pvalue->a3G_Neighbour_Cell_Description.utran_FDD_Description
      .repeated_UTRAN_FDD_Neighbour_Cells_list.n = 1;
   pvalue->a3G_Neighbour_Cell_Description.utran_FDD_Description
      .repeated_UTRAN_FDD_Neighbour_Cells_list.elem = rtxMemAlloc(pctxt, 
            1 * sizeof(TS44018Msg_Repeated_UTRAN_FDD_Neighbour_Cells_struct));
   asn1Init_TS44018Msg_Repeated_UTRAN_FDD_Neighbour_Cells_struct(
      &pvalue->a3G_Neighbour_Cell_Description.utran_FDD_Description
      .repeated_UTRAN_FDD_Neighbour_Cells_list.elem[0] );
   pvalue->a3G_Neighbour_Cell_Description.utran_FDD_Description
      .repeated_UTRAN_FDD_Neighbour_Cells_list.elem[0].fdd_arfcn = 256;
   pvalue->a3G_Neighbour_Cell_Description.utran_FDD_Description
      .repeated_UTRAN_FDD_Neighbour_Cells_list.elem[0].fdd_Indic0 = 1;
   pvalue->a3G_Neighbour_Cell_Description.utran_FDD_Description
      .repeated_UTRAN_FDD_Neighbour_Cells_list.elem[0].nr_of_fdd_cells = 2; //p(2) = 19
   pvalue->a3G_Neighbour_Cell_Description.utran_FDD_Description
      .repeated_UTRAN_FDD_Neighbour_Cells_list.elem[0].fdd_CELL_INFORMATION_Field.numbits = 19;

   {
      static OSOCTET data[] = { 0x12, 0x34, 0x56 };
      pvalue->a3G_Neighbour_Cell_Description.utran_FDD_Description
         .repeated_UTRAN_FDD_Neighbour_Cells_list.elem[0].fdd_CELL_INFORMATION_Field.data = data;
   }
      
   
   pvalue->a3G_Neighbour_Cell_Description.m.utran_TDD_DescriptionPresent = 1;

   pvalue->a3G_Neighbour_Cell_Description.utran_TDD_Description.m.bandwidth_TDDPresent = 1;
   pvalue->a3G_Neighbour_Cell_Description.utran_TDD_Description.bandwidth_TDD = 3;
   pvalue->a3G_Neighbour_Cell_Description.utran_TDD_Description
      .repeated_UTRAN_TDD_Neighbour_Cells_list.n = 1;
   pvalue->a3G_Neighbour_Cell_Description.utran_TDD_Description
      .repeated_UTRAN_TDD_Neighbour_Cells_list.elem = rtxMemAlloc(pctxt, 
            1 * sizeof(TS44018Msg_Repeated_UTRAN_TDD_Neighbour_Cells_struct));
   asn1Init_TS44018Msg_Repeated_UTRAN_TDD_Neighbour_Cells_struct(
      &pvalue->a3G_Neighbour_Cell_Description.utran_TDD_Description
      .repeated_UTRAN_TDD_Neighbour_Cells_list.elem[0] );
   pvalue->a3G_Neighbour_Cell_Description.utran_TDD_Description
      .repeated_UTRAN_TDD_Neighbour_Cells_list.elem[0].tdd_arfcn = 256;
   pvalue->a3G_Neighbour_Cell_Description.utran_TDD_Description
      .repeated_UTRAN_TDD_Neighbour_Cells_list.elem[0].tdd_Indic0 = 1;
   pvalue->a3G_Neighbour_Cell_Description.utran_TDD_Description
      .repeated_UTRAN_TDD_Neighbour_Cells_list.elem[0].nr_of_tdd_cells = 2; //q(2) = 17
   pvalue->a3G_Neighbour_Cell_Description.utran_TDD_Description
      .repeated_UTRAN_TDD_Neighbour_Cells_list.elem[0].tdd_CELL_INFORMATION_Field.numbits = 17;

   {
      static OSOCTET data[] = { 0x56, 0x78, 0xFF };
      pvalue->a3G_Neighbour_Cell_Description.utran_TDD_Description
         .repeated_UTRAN_TDD_Neighbour_Cells_list.elem[0].tdd_CELL_INFORMATION_Field.data = data;
   }
   

   pvalue->a3G_Neighbour_Cell_Description.m.cdma2000_DescriptionPresent = 1;

   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.cdma2000_frequency_band = 16;

   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.cdma2000_frequency = 1923;

   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.number_cdma2000_cells = 5;
  
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .n = 5;

   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[0].pilot_PN_offset = 35;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[0].m.component_2Present = 1;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[0].component_2.t = T_CDMA2000_Description_struct_component_4_element_component_2_choice_1;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[0].component_2.u.choice_1.td_mode = 2;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[0].component_2.u.choice_1.td_power_level = 5;

   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[1].pilot_PN_offset = 36;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[1].m.component_2Present = 1;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[1].component_2.t = T_CDMA2000_Description_struct_component_4_element_component_2_choice_2;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[1].component_2.u.choice_2.qof = 0;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[1].component_2.u.choice_2.walsh_len_a = 4;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[1].component_2.u.choice_2.aux_pilot_walsh.numbits = 10;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[1].component_2.u.choice_2.aux_pilot_walsh.data[0] = 0xAD;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[1].component_2.u.choice_2.aux_pilot_walsh.data[1] = 0xA0;

   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[2].pilot_PN_offset = 37;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[2].m.component_2Present = 1;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[2].component_2.t = T_CDMA2000_Description_struct_component_4_element_component_2_choice_3;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[2].component_2.u.choice_3.qof = 2;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[2].component_2.u.choice_3.walsh_len_b = 2;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[2].component_2.u.choice_3.aux_td_walsh.numbits = 8;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[2].component_2.u.choice_3.aux_td_walsh.data[0] = 0xFF;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[2].component_2.u.choice_3.aux_td_power_level = 3;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[2].component_2.u.choice_3.td_mode = 1;


   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[3].pilot_PN_offset = 38;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[3].m.component_2Present = 1;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[3].component_2.t = T_CDMA2000_Description_struct_component_4_element_component_2_choice_4;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[3].component_2.u.choice_4.sr3_prim_pilot = 1;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[3].component_2.u.choice_4.sr3_pilot_power1 = 7;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[3].component_2.u.choice_4.sr3_pilot_power2 = 7;

   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[4].pilot_PN_offset = 39;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[4].m.component_2Present = 1;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[4].component_2.t = T_CDMA2000_Description_struct_component_4_element_component_2_choice_5;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[4].component_2.u.choice_5.sr3_prim_pilot = 1;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[4].component_2.u.choice_5.sr3_pilot_power1 = 7;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[4].component_2.u.choice_5.sr3_pilot_power2 = 7;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[4].component_2.u.choice_5.qof = 2;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[4].component_2.u.choice_5.walsh_len_c = 1;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[4].component_2.u.choice_5.aux_walsh_len.numbits = 7;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[4].component_2.u.choice_5.aux_walsh_len.data[0] = 0xFE;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[4].component_2.u.choice_5.m.component_7Present = 0;
   pvalue->a3G_Neighbour_Cell_Description.cdma2000_Description.component_4
      .elem[4].component_2.u.choice_5.m.component_8Present = 0;

   pvalue->m.a3G_MEASUREMENT_Parameters_DescriptionPresent = 1;

   pvalue->a3G_MEASUREMENT_Parameters_Description.qsearch_C = 11;

   pvalue->a3G_MEASUREMENT_Parameters_Description.fdd_rep_quant = 0;

   pvalue->a3G_MEASUREMENT_Parameters_Description.m.fdd_multirat_reportingPresent = 1;
   pvalue->a3G_MEASUREMENT_Parameters_Description.fdd_multirat_reporting = 1;

   pvalue->a3G_MEASUREMENT_Parameters_Description.m.component_5Present = 1;

   pvalue->a3G_MEASUREMENT_Parameters_Description.component_5.fdd_reporting_offset = 6;

   pvalue->a3G_MEASUREMENT_Parameters_Description.component_5.fdd_reporting_threshold = 4;

   pvalue->a3G_MEASUREMENT_Parameters_Description.m.tdd_multirat_reportingPresent = 1;
   pvalue->a3G_MEASUREMENT_Parameters_Description.tdd_multirat_reporting = 1;

   pvalue->a3G_MEASUREMENT_Parameters_Description.m.component_7Present = 1;

   pvalue->a3G_MEASUREMENT_Parameters_Description.component_7.tdd_reporting_offset = 3;

   pvalue->a3G_MEASUREMENT_Parameters_Description.component_7.tdd_reporting_threshold = 0;

   pvalue->a3G_MEASUREMENT_Parameters_Description.m.cdma2000_multirat_reportingPresent = 1;
   pvalue->a3G_MEASUREMENT_Parameters_Description.cdma2000_multirat_reporting = 0;

   pvalue->a3G_MEASUREMENT_Parameters_Description.m.component_9Present = 1;

   pvalue->a3G_MEASUREMENT_Parameters_Description.component_9.cdma2000_reporting_offset = 2;

   pvalue->a3G_MEASUREMENT_Parameters_Description.component_9.cdma2000_reporting_threshold = 6;

   pvalue->m.component_17Present = 1;

   pvalue->component_17.m.a3G_ADDITIONAL_MEASUREMENT_Parameters_Description_2Present = 1;

   pvalue->component_17.a3G_ADDITIONAL_MEASUREMENT_Parameters_Description_2.m.fdd_reporting_threshold_2Present = 1;
   pvalue->component_17.a3G_ADDITIONAL_MEASUREMENT_Parameters_Description_2.fdd_reporting_threshold_2 = 44;

   pvalue->component_17.m.component_2Present = 1;

   pvalue->component_17.component_2.m.component_1Present = 1;

   pvalue->component_17.component_2.component_1.a700_REPORTING_OFFSET = 1;

   pvalue->component_17.component_2.component_1.a700_REPORTING_THRESHOLD = 3;

   pvalue->component_17.component_2.m.component_2Present = 1;

   pvalue->component_17.component_2.component_2.a810_REPORTING_OFFSET = 0;

   pvalue->component_17.component_2.component_2.a810_REPORTING_THRESHOLD = 1;

   pvalue->component_17.component_2.m.component_3Present = 1;

   pvalue->component_17.component_2.component_3.m.a3G_Supplementary_Parameters_DescriptionPresent = 1;

   pvalue->component_17.component_2.component_3.a3G_Supplementary_Parameters_Description.utran_Start = 0;

   pvalue->component_17.component_2.component_3.a3G_Supplementary_Parameters_Description.utran_Stop = 0;

   pvalue->component_17.component_2.component_3.a3G_Supplementary_Parameters_Description.m.a3G_Measurement_Control_Parameters_DescriptionPresent = 1;

   pvalue->component_17.component_2.component_3.a3G_Supplementary_Parameters_Description
      .a3G_Measurement_Control_Parameters_Description.m.default_Measurement_Control_UTRANPresent = 1;
   pvalue->component_17.component_2.component_3.a3G_Supplementary_Parameters_Description
      .a3G_Measurement_Control_Parameters_Description.default_Measurement_Control_UTRAN = 0;
   pvalue->component_17.component_2.component_3.a3G_Supplementary_Parameters_Description
      .a3G_Measurement_Control_Parameters_Description.repeated_UTRAN_Measurement_Control_Parameters_list.n = 1;
   pvalue->component_17.component_2.component_3.a3G_Supplementary_Parameters_Description
      .a3G_Measurement_Control_Parameters_Description.repeated_UTRAN_Measurement_Control_Parameters_list.elem = rtxMemAlloc(pctxt,
         1 * sizeof(TS44018Msg_Repeated_UTRAN_Measurement_Control_Parameters_struct));

   pvalue->component_17.component_2.component_3.a3G_Supplementary_Parameters_Description
      .a3G_Measurement_Control_Parameters_Description.repeated_UTRAN_Measurement_Control_Parameters_list.elem[0].utran_frequency_index_list.n = 2;
   pvalue->component_17.component_2.component_3.a3G_Supplementary_Parameters_Description
      .a3G_Measurement_Control_Parameters_Description.repeated_UTRAN_Measurement_Control_Parameters_list.elem[0].utran_frequency_index_list.elem = 
      rtxMemAlloc(pctxt, 2 * sizeof(OSUINT8));
   pvalue->component_17.component_2.component_3.a3G_Supplementary_Parameters_Description
      .a3G_Measurement_Control_Parameters_Description.repeated_UTRAN_Measurement_Control_Parameters_list.elem[0].utran_frequency_index_list.elem[0] = 0x0A;
   pvalue->component_17.component_2.component_3.a3G_Supplementary_Parameters_Description
      .a3G_Measurement_Control_Parameters_Description.repeated_UTRAN_Measurement_Control_Parameters_list.elem[0].utran_frequency_index_list.elem[1] = 0x0B;
   pvalue->component_17.component_2.component_3.a3G_Supplementary_Parameters_Description
      .a3G_Measurement_Control_Parameters_Description.repeated_UTRAN_Measurement_Control_Parameters_list.elem[0].measurement_Control_UTRAN = 1;

   pvalue->component_17.component_2.component_3.m.e_UTRAN_Parameters_DescriptionPresent = 1;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Start = 0;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Stop = 0;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.m.e_UTRAN_Measurement_Parameters_DescriptionPresent = 1;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.qsearch_C_E_UTRAN = 14;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.e_utran_rep_quant = 0;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.e_utran_multirat_reporting = 0;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.t =  2;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.m.component_1Present = 1;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_1.e_utran_fdd_measurement_report_offset = 54;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_1.m.e_utran_fdd_reporting_threshold_2Present = 1;
   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_1.e_utran_fdd_reporting_threshold_2 = 12;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_1.m.e_utran_fdd_reporting_offsetPresent = 1;
   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_1.e_utran_fdd_reporting_offset = 5;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.m.component_2Present = 1;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_2.e_utran_tdd_measurement_report_offset = 50;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_2.m.e_utran_tdd_reporting_threshold_2Present = 1;
   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_2.e_utran_tdd_reporting_threshold_2 = 10;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_2.m.e_utran_tdd_reporting_offsetPresent = 1;
   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_2.e_utran_tdd_reporting_offset = 0;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description
      .e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.reporting_granularity = 0;

   /* zero elements */


   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description
      .repeated_E_UTRAN_Not_Allowed_Cells_list.n = 1;
   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description
      .repeated_E_UTRAN_Not_Allowed_Cells_list.elem = rtxMemAlloc(pctxt, 1 * sizeof(TS44018Msg_Repeated_E_UTRAN_Not_Allowed_Cells_struct));
   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description
      .repeated_E_UTRAN_Not_Allowed_Cells_list.elem[0].not_Allowed_Cells.pcid_list.n = 0;
   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description
      .repeated_E_UTRAN_Not_Allowed_Cells_list.elem[0].not_Allowed_Cells.m.pcid_bitmap_groupPresent = 0;
   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description
      .repeated_E_UTRAN_Not_Allowed_Cells_list.elem[0].not_Allowed_Cells.component_3.n = 1;
   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description
      .repeated_E_UTRAN_Not_Allowed_Cells_list.elem[0].not_Allowed_Cells.component_3.elem = rtxMemAlloc(pctxt, 1 * sizeof(TS44060IE_PCID_Group_IE_component_3_element));
   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description
      .repeated_E_UTRAN_Not_Allowed_Cells_list.elem[0].not_Allowed_Cells.component_3.elem[0].pcid_Pattern_length = 3;
   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description
      .repeated_E_UTRAN_Not_Allowed_Cells_list.elem[0].not_Allowed_Cells.component_3.elem[0].pcid_Pattern.numbits = 4;
   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description
      .repeated_E_UTRAN_Not_Allowed_Cells_list.elem[0].not_Allowed_Cells.component_3.elem[0].pcid_Pattern.data[0] = 0xF0;
   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description
      .repeated_E_UTRAN_Not_Allowed_Cells_list.elem[0].not_Allowed_Cells.component_3.elem[0].pcid_pattern_sense = 1;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description
      .repeated_E_UTRAN_Not_Allowed_Cells_list.elem[0].e_utran_frequency_index_list.n = 0;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.m.e_UTRAN_Measurement_Control_Parameters_DescriptionPresent = 1;

   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Control_Parameters_Description.m.default_Measurement_Control_E_UTRANPresent = 1;
   pvalue->component_17.component_2.component_3.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Control_Parameters_Description.default_Measurement_Control_E_UTRAN = 0;

   /* zero elements */

   pvalue->component_17.component_2.component_3.m.e_UTRAN_CSG_DescriptionPresent = 1;
   /* zero elements */

   pvalue->component_17.component_2.component_3.m.component_4Present = 1;

   pvalue->component_17.component_2.component_3.component_4.m.a3G_CSG_DescriptionPresent = 1;

   /* zero elements */

   pvalue->component_17.component_2.component_3.component_4.a3G_CSG_Description.component_2.n = 2;
   pvalue->component_17.component_2.component_3.component_4.a3G_CSG_Description.component_2.elem = rtxMemAllocArrayZ (pctxt, 2, TS44018IE_A3G_CSG_Description_struct_component_2_element);
   pvalue->component_17.component_2.component_3.component_4.a3G_CSG_Description.component_2.elem[0].t =  1;
   pvalue->component_17.component_2.component_3.component_4.a3G_CSG_Description.component_2.elem[0].u.csg_fdd_uarfcn = 8404;

   pvalue->component_17.component_2.component_3.component_4.a3G_CSG_Description.component_2.elem[1].t =  2;
   pvalue->component_17.component_2.component_3.component_4.a3G_CSG_Description.component_2.elem[1].u.csg_tdd_uarfcn = 16069;

   pvalue->component_17.component_2.component_3.component_4.m.utran_CSG_Cells_Reporting_DescriptionPresent = 1;

   pvalue->component_17.component_2.component_3.component_4.utran_CSG_Cells_Reporting_Description.m.component_1Present = 1;

   pvalue->component_17.component_2.component_3.component_4.utran_CSG_Cells_Reporting_Description.component_1.utran_csg_fdd_reporting_threshold = 6;

   pvalue->component_17.component_2.component_3.component_4.utran_CSG_Cells_Reporting_Description.component_1.utran_csg_fdd_reporting_threshold_2 = 10;

   pvalue->component_17.component_2.component_3.component_4.utran_CSG_Cells_Reporting_Description.m.utran_csg_tdd_reporting_thresholdPresent = 1;
   pvalue->component_17.component_2.component_3.component_4.utran_CSG_Cells_Reporting_Description.utran_csg_tdd_reporting_threshold = 0;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_RR_Short_PD_PDU (&ctxt, &pdu);
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
