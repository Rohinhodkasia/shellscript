#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300


TS44018IE_SI2quater_Rest_Octets*
    asn1Test_TS44018IE_SI2quater_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_SI2quater_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_SI2quater_Rest_Octets);
   asn1Init_TS44018IE_SI2quater_Rest_Octets (pvalue);

   pvalue->ba_ind = 0;

   pvalue->a3G_BA_IND = 0;

   pvalue->mp_change_mark = 0;

   pvalue->si2quater_INDEX = 1;

   pvalue->si2quater_COUNT = 1;

   pvalue->m.measurement_Parameters_DescriptionPresent = 1;

   pvalue->measurement_Parameters_Description.report_type = 0;

   pvalue->measurement_Parameters_Description.serving_band_reporting = 2;

   pvalue->m.gprs_Real_Time_Difference_DescriptionPresent = 1;

   pvalue->gprs_Real_Time_Difference_Description.m.component_1Present = 1;

   pvalue->gprs_Real_Time_Difference_Description.component_1.m.ba_Index_Start_RTDPresent = 1;
   pvalue->gprs_Real_Time_Difference_Description.component_1.ba_Index_Start_RTD = 5;

   pvalue->gprs_Real_Time_Difference_Description.component_1.rtd.n = 1;
   pvalue->gprs_Real_Time_Difference_Description.component_1.rtd.elem = rtxMemAllocArrayZ (pctxt, 1, OSUINT8);
   pvalue->gprs_Real_Time_Difference_Description.component_1.rtd.elem[0] = 0;

   /* zero elements */

   pvalue->gprs_Real_Time_Difference_Description.m.component_2Present = 1;

   pvalue->gprs_Real_Time_Difference_Description.component_2.m.ba_Index_Start_RTDPresent = 1;
   pvalue->gprs_Real_Time_Difference_Description.component_2.ba_Index_Start_RTD = 9;

   pvalue->gprs_Real_Time_Difference_Description.component_2.rtd.n = 2;
   pvalue->gprs_Real_Time_Difference_Description.component_2.rtd.elem = rtxMemAllocArrayZ (pctxt, 2, OSUINT16);
   pvalue->gprs_Real_Time_Difference_Description.component_2.rtd.elem[0] = 1947;

   pvalue->gprs_Real_Time_Difference_Description.component_2.rtd.elem[1] = 303;

   /* zero elements */

   pvalue->m.gprs_BSIC_DescriptionPresent = 1;

   pvalue->gprs_BSIC_Description.m.ba_Index_Start_BSICPresent = 1;
   pvalue->gprs_BSIC_Description.ba_Index_Start_BSIC = 15;

   pvalue->gprs_BSIC_Description.bsic = 21;

   pvalue->gprs_BSIC_Description.number_Remaining_BSIC = 1;

   pvalue->gprs_BSIC_Description.component_4.n = 1;
   pvalue->gprs_BSIC_Description.component_4.elem[0].frequency_Scrolling = 0;
   pvalue->gprs_BSIC_Description.component_4.elem[0].bsic = 22;

   /* zero elements */

   pvalue->m.gprs_REPORT_PRIORITY_DescriptionPresent = 1;

   pvalue->gprs_REPORT_PRIORITY_Description.number_Cells = 54;

   pvalue->gprs_REPORT_PRIORITY_Description.rep_priority.numbits = 54;
   pvalue->gprs_REPORT_PRIORITY_Description.rep_priority.data[0] = 0x5d;
   pvalue->gprs_REPORT_PRIORITY_Description.rep_priority.data[1] = 0x4a;
   pvalue->gprs_REPORT_PRIORITY_Description.rep_priority.data[2] = 0x39;
   pvalue->gprs_REPORT_PRIORITY_Description.rep_priority.data[3] = 0x63;
   pvalue->gprs_REPORT_PRIORITY_Description.rep_priority.data[4] = 0x67;
   pvalue->gprs_REPORT_PRIORITY_Description.rep_priority.data[5] = 0x61;
   pvalue->gprs_REPORT_PRIORITY_Description.rep_priority.data[6] = 0x4d;

   pvalue->m.gprs_MEASUREMENT_Parameters_DescriptionPresent = 1;

   pvalue->gprs_MEASUREMENT_Parameters_Description.report_type = 0;

   pvalue->gprs_MEASUREMENT_Parameters_Description.reporting_rate = 0;

   pvalue->gprs_MEASUREMENT_Parameters_Description.invalid_bsic_reporting = 0;

   pvalue->gprs_MEASUREMENT_Parameters_Description.m.multiband_reportingPresent = 1;
   pvalue->gprs_MEASUREMENT_Parameters_Description.multiband_reporting = 1;

   pvalue->gprs_MEASUREMENT_Parameters_Description.m.serving_band_reportingPresent = 1;
   pvalue->gprs_MEASUREMENT_Parameters_Description.serving_band_reporting = 2;

   pvalue->gprs_MEASUREMENT_Parameters_Description.scale_ord = 2;

   pvalue->gprs_MEASUREMENT_Parameters_Description.m.component_7Present = 1;

   pvalue->gprs_MEASUREMENT_Parameters_Description.component_7.a900_REPORTING_OFFSET = 6;

   pvalue->gprs_MEASUREMENT_Parameters_Description.component_7.a900_REPORTING_THRESHOLD = 4;

   pvalue->gprs_MEASUREMENT_Parameters_Description.m.component_8Present = 1;

   pvalue->gprs_MEASUREMENT_Parameters_Description.component_8.a1800_REPORTING_OFFSET = 4;

   pvalue->gprs_MEASUREMENT_Parameters_Description.component_8.a1800_REPORTING_THRESHOLD = 5;

   pvalue->gprs_MEASUREMENT_Parameters_Description.m.component_9Present = 1;

   pvalue->gprs_MEASUREMENT_Parameters_Description.component_9.a400_REPORTING_OFFSET = 2;

   pvalue->gprs_MEASUREMENT_Parameters_Description.component_9.a400_REPORTING_THRESHOLD = 5;

   pvalue->gprs_MEASUREMENT_Parameters_Description.m.component_10Present = 1;

   pvalue->gprs_MEASUREMENT_Parameters_Description.component_10.a1900_REPORTING_OFFSET = 1;

   pvalue->gprs_MEASUREMENT_Parameters_Description.component_10.a1900_REPORTING_THRESHOLD = 5;

   pvalue->gprs_MEASUREMENT_Parameters_Description.m.component_11Present = 1;

   pvalue->gprs_MEASUREMENT_Parameters_Description.component_11.a850_REPORTING_OFFSET = 3;

   pvalue->gprs_MEASUREMENT_Parameters_Description.component_11.a850_REPORTING_THRESHOLD = 0;

   pvalue->m.nc_Measurement_ParametersPresent = 1;

   pvalue->nc_Measurement_Parameters.network_control_order = 2;

   pvalue->nc_Measurement_Parameters.m.component_2Present = 1;

   pvalue->nc_Measurement_Parameters.component_2.nc_non_drx_period = 5;

   pvalue->nc_Measurement_Parameters.component_2.nc_reporting_period_i = 0;

   pvalue->nc_Measurement_Parameters.component_2.nc_reporting_period_t = 2;

   pvalue->m.component_12Present = 1;
   pvalue->component_12.extension_length = 0; /* length will be calculated */

   pvalue->component_12.si2q_Extension_Information.m.ccn_Support_DescriptionPresent = 1;

   pvalue->component_12.si2q_Extension_Information.ccn_Support_Description.number_Cells = 4;

   pvalue->component_12.si2q_Extension_Information.ccn_Support_Description.ccn_supported.numbits = 4;
   pvalue->component_12.si2q_Extension_Information.ccn_Support_Description.ccn_supported.data[0] = 0x6a;

   pvalue->m.a3G_Neighbour_Cell_DescriptionPresent = 1;

   pvalue->a3G_Neighbour_Cell_Description.m.index_Start_3GPresent = 1;
   pvalue->a3G_Neighbour_Cell_Description.index_Start_3G = 88;

   pvalue->a3G_Neighbour_Cell_Description.m.absolute_Index_Start_EMRPresent = 1;
   pvalue->a3G_Neighbour_Cell_Description.absolute_Index_Start_EMR = 21;

   pvalue->a3G_Neighbour_Cell_Description.m.utran_FDD_DescriptionPresent = 1;

   pvalue->a3G_Neighbour_Cell_Description.utran_FDD_Description.m.bandwidth_FDDPresent = 1;
   pvalue->a3G_Neighbour_Cell_Description.utran_FDD_Description.bandwidth_FDD = 0;

   /* zero elements */

   pvalue->a3G_Neighbour_Cell_Description.m.utran_TDD_DescriptionPresent = 1;

   pvalue->a3G_Neighbour_Cell_Description.utran_TDD_Description.m.bandwidth_TDDPresent = 1;
   pvalue->a3G_Neighbour_Cell_Description.utran_TDD_Description.bandwidth_TDD = 5;

   /* zero elements */

   pvalue->m.a3G_Measurement_Parameters_DescriptionPresent = 1;

   pvalue->a3G_Measurement_Parameters_Description.qsearch_I = 10;

   pvalue->a3G_Measurement_Parameters_Description.qsearch_C_Initial = 0;

   pvalue->a3G_Measurement_Parameters_Description.m.component_3Present = 1;

   pvalue->a3G_Measurement_Parameters_Description.component_3.fdd_Qoffset = 10;

   pvalue->a3G_Measurement_Parameters_Description.component_3.fdd_rep_quant = 0;

   pvalue->a3G_Measurement_Parameters_Description.component_3.fdd_multirat_reporting = 1;

   pvalue->a3G_Measurement_Parameters_Description.component_3.fdd_Qmin = 1;

   pvalue->a3G_Measurement_Parameters_Description.m.component_4Present = 1;

   pvalue->a3G_Measurement_Parameters_Description.component_4.tdd_Qoffset = 10;

   pvalue->a3G_Measurement_Parameters_Description.component_4.tdd_multirat_reporting = 2;

   pvalue->m.gprs_3G_MEASUREMENT_Parameters_DescriptionPresent = 1;

   pvalue->gprs_3G_MEASUREMENT_Parameters_Description.qsearch_P = 3;

   pvalue->gprs_3G_MEASUREMENT_Parameters_Description.ignored = 0;

   pvalue->gprs_3G_MEASUREMENT_Parameters_Description.m.component_3Present = 1;

   pvalue->gprs_3G_MEASUREMENT_Parameters_Description.component_3.fdd_rep_quant = 0;

   pvalue->gprs_3G_MEASUREMENT_Parameters_Description.component_3.fdd_multirat_reporting = 0;

   pvalue->gprs_3G_MEASUREMENT_Parameters_Description.m.component_4Present = 1;

   pvalue->gprs_3G_MEASUREMENT_Parameters_Description.component_4.fdd_reporting_offset = 0;

   pvalue->gprs_3G_MEASUREMENT_Parameters_Description.component_4.fdd_reporting_threshold = 1;

   pvalue->gprs_3G_MEASUREMENT_Parameters_Description.m.tdd_multirat_reportingPresent = 1;
   pvalue->gprs_3G_MEASUREMENT_Parameters_Description.tdd_multirat_reporting = 2;

   pvalue->gprs_3G_MEASUREMENT_Parameters_Description.m.component_6Present = 1;

   pvalue->gprs_3G_MEASUREMENT_Parameters_Description.component_6.tdd_reporting_offset = 3;

   pvalue->gprs_3G_MEASUREMENT_Parameters_Description.component_6.tdd_reporting_threshold = 2;

   pvalue->m.component_16Present = 1;

   pvalue->component_16.m.a3G_Additional_Measurement_Parameters_DescriptionPresent = 1;

   pvalue->component_16.a3G_Additional_Measurement_Parameters_Description.fdd_Qmin_Offset = 0;

   pvalue->component_16.a3G_Additional_Measurement_Parameters_Description.fdd_RSCPmin = 2;

   pvalue->component_16.m.a3G_ADDITIONAL_MEASUREMENT_Parameters_Description_2Present = 1;

   pvalue->component_16.a3G_ADDITIONAL_MEASUREMENT_Parameters_Description_2.m.fdd_reporting_threshold_2Present = 1;
   pvalue->component_16.a3G_ADDITIONAL_MEASUREMENT_Parameters_Description_2.fdd_reporting_threshold_2 = 42;

   pvalue->component_16.m.component_3Present = 1;

   pvalue->component_16.component_3.a3G_CCN_ACTIVE = 0;

   pvalue->component_16.component_3.m.component_2Present = 1;

   pvalue->component_16.component_3.component_2.m.component_1Present = 1;

   pvalue->component_16.component_3.component_2.component_1.a700_REPORTING_OFFSET = 5;

   pvalue->component_16.component_3.component_2.component_1.a700_REPORTING_THRESHOLD = 1;

   pvalue->component_16.component_3.component_2.m.component_2Present = 1;

   pvalue->component_16.component_3.component_2.component_2.a810_REPORTING_OFFSET = 2;

   pvalue->component_16.component_3.component_2.component_2.a810_REPORTING_THRESHOLD = 1;

   pvalue->component_16.component_3.component_2.m.component_3Present = 1;

   pvalue->component_16.component_3.component_2.component_3.m.priority_and_E_UTRAN_Parameters_DescriptionPresent = 1;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.m.serving_Cell_Priority_Parameters_DescriptionPresent = 1;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.serving_Cell_Priority_Parameters_Description.geran_priority = 1;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.serving_Cell_Priority_Parameters_Description.thresh_Priority_Search = 11;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.serving_Cell_Priority_Parameters_Description.thresh_GSM_low = 5;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.serving_Cell_Priority_Parameters_Description.h_prio = 2;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.serving_Cell_Priority_Parameters_Description.t_Reselection = 0;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.m.a3G_Priority_Parameters_DescriptionPresent = 1;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.a3G_Priority_Parameters_Description.utran_Start = 0;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.a3G_Priority_Parameters_Description.utran_Stop = 0;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.a3G_Priority_Parameters_Description.m.component_3Present = 1;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.a3G_Priority_Parameters_Description.component_3.default_utran_priority = 2;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.a3G_Priority_Parameters_Description.component_3.default_thresh_utran = 25;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.a3G_Priority_Parameters_Description.component_3.default_utran_qrxlevmin = 26;

   /* zero elements */

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.m.e_UTRAN_Parameters_DescriptionPresent = 1;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_utran_ccn_active = 0;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Start = 0;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Stop = 0;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.m.e_UTRAN_Measurement_Parameters_DescriptionPresent = 1;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.qsearch_C_E_UTRAN = 14;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.e_utran_rep_quant = 0;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.e_utran_multirat_reporting = 1;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.t =  2;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.m.component_1Present = 1;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_1.e_utran_fdd_measurement_report_offset = 56;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_1.m.e_utran_fdd_reporting_threshold_2Present = 1;
   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_1.e_utran_fdd_reporting_threshold_2 = 16;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_1.m.e_utran_fdd_reporting_offsetPresent = 1;
   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_1.e_utran_fdd_reporting_offset = 2;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.m.component_2Present = 1;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_2.e_utran_tdd_measurement_report_offset = 24;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_2.m.e_utran_tdd_reporting_threshold_2Present = 1;
   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_2.e_utran_tdd_reporting_threshold_2 = 61;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_2.m.e_utran_tdd_reporting_offsetPresent = 1;
   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.component_2.e_utran_tdd_reporting_offset = 5;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.e_UTRAN_Measurement_Parameters_Description.component_4.u.choice_2.reporting_granularity = 0;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.m.gprs_E_UTRAN_Measurement_Parameters_DescriptionPresent = 1;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.gprs_E_UTRAN_Measurement_Parameters_Description.qsearch_P_E_UTRAN = 6;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.gprs_E_UTRAN_Measurement_Parameters_Description.e_utran_rep_quant = 0;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.gprs_E_UTRAN_Measurement_Parameters_Description.e_utran_multirat_reporting = 0;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.gprs_E_UTRAN_Measurement_Parameters_Description.m.component_4Present = 1;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.gprs_E_UTRAN_Measurement_Parameters_Description.component_4.e_utran_fdd_reporting_threshold = 1;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.gprs_E_UTRAN_Measurement_Parameters_Description.component_4.m.e_utran_fdd_reporting_threshold_2Present = 1;
   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.gprs_E_UTRAN_Measurement_Parameters_Description.component_4.e_utran_fdd_reporting_threshold_2 = 4;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.gprs_E_UTRAN_Measurement_Parameters_Description.component_4.m.e_utran_fdd_reporting_offsetPresent = 1;
   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.gprs_E_UTRAN_Measurement_Parameters_Description.component_4.e_utran_fdd_reporting_offset = 0;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.gprs_E_UTRAN_Measurement_Parameters_Description.m.component_5Present = 1;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.gprs_E_UTRAN_Measurement_Parameters_Description.component_5.e_utran_tdd_reporting_threshold = 0;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.gprs_E_UTRAN_Measurement_Parameters_Description.component_5.m.e_utran_tdd_reporting_threshold_2Present = 1;
   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.gprs_E_UTRAN_Measurement_Parameters_Description.component_5.e_utran_tdd_reporting_threshold_2 = 48;

   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.gprs_E_UTRAN_Measurement_Parameters_Description.component_5.m.e_utran_tdd_reporting_offsetPresent = 1;
   pvalue->component_16.component_3.component_2.component_3.priority_and_E_UTRAN_Parameters_Description.e_UTRAN_Parameters_Description.gprs_E_UTRAN_Measurement_Parameters_Description.component_5.e_utran_tdd_reporting_offset = 4;

   /* zero elements */

   /* zero elements */

   /* zero elements */

   pvalue->component_16.component_3.component_2.component_3.m.a3G_CSG_DescriptionPresent = 1;

   /* zero elements */

   pvalue->component_16.component_3.component_2.component_3.a3G_CSG_Description.component_2.n = 2;
   pvalue->component_16.component_3.component_2.component_3.a3G_CSG_Description.component_2.elem = rtxMemAllocArrayZ (pctxt, 2, TS44018IE_A3G_CSG_Description_struct_component_2_element);
   pvalue->component_16.component_3.component_2.component_3.a3G_CSG_Description.component_2.elem[0].t =  1;
   pvalue->component_16.component_3.component_2.component_3.a3G_CSG_Description.component_2.elem[0].u.csg_fdd_uarfcn = 15805;

   pvalue->component_16.component_3.component_2.component_3.a3G_CSG_Description.component_2.elem[1].t =  2;
   pvalue->component_16.component_3.component_2.component_3.a3G_CSG_Description.component_2.elem[1].u.csg_tdd_uarfcn = 8259;

   pvalue->component_16.component_3.component_2.component_3.m.e_UTRAN_CSG_DescriptionPresent = 1;

   /* zero elements */

   pvalue->component_16.component_3.component_2.component_3.e_UTRAN_CSG_Description.csg_earfcn_list.n = 3;
   pvalue->component_16.component_3.component_2.component_3.e_UTRAN_CSG_Description.csg_earfcn_list.elem = rtxMemAllocArrayZ (pctxt, 3, OSUINT16);
   pvalue->component_16.component_3.component_2.component_3.e_UTRAN_CSG_Description.csg_earfcn_list.elem[0] = 54907;

   pvalue->component_16.component_3.component_2.component_3.e_UTRAN_CSG_Description.csg_earfcn_list.elem[1] = 31645;

   pvalue->component_16.component_3.component_2.component_3.e_UTRAN_CSG_Description.csg_earfcn_list.elem[2] = 20366;

   pvalue->component_16.component_3.component_2.component_3.m.component_4Present = 1;

   pvalue->component_16.component_3.component_2.component_3.component_4.m.enhanced_Cell_Reselection_Parameters_DescriptionPresent = 1;
   /* zero elements */

   pvalue->component_16.component_3.component_2.component_3.component_4.m.csg_Cells_Reporting_DescriptionPresent = 1;

   pvalue->component_16.component_3.component_2.component_3.component_4.csg_Cells_Reporting_Description.m.utran_CSG_Cells_Reporting_DescriptionPresent = 1;

   pvalue->component_16.component_3.component_2.component_3.component_4.csg_Cells_Reporting_Description.utran_CSG_Cells_Reporting_Description.m.component_1Present = 1;

   pvalue->component_16.component_3.component_2.component_3.component_4.csg_Cells_Reporting_Description.utran_CSG_Cells_Reporting_Description.component_1.utran_csg_fdd_reporting_threshold = 0;

   pvalue->component_16.component_3.component_2.component_3.component_4.csg_Cells_Reporting_Description.utran_CSG_Cells_Reporting_Description.component_1.utran_csg_fdd_reporting_threshold_2 = 23;

   pvalue->component_16.component_3.component_2.component_3.component_4.csg_Cells_Reporting_Description.utran_CSG_Cells_Reporting_Description.m.utran_csg_tdd_reporting_thresholdPresent = 1;
   pvalue->component_16.component_3.component_2.component_3.component_4.csg_Cells_Reporting_Description.utran_CSG_Cells_Reporting_Description.utran_csg_tdd_reporting_threshold = 3;

   pvalue->component_16.component_3.component_2.component_3.component_4.csg_Cells_Reporting_Description.m.e_UTRAN_CSG_Cells_Reporting_DescriptionPresent = 1;

   pvalue->component_16.component_3.component_2.component_3.component_4.csg_Cells_Reporting_Description.e_UTRAN_CSG_Cells_Reporting_Description.m.component_1Present = 1;

   pvalue->component_16.component_3.component_2.component_3.component_4.csg_Cells_Reporting_Description.e_UTRAN_CSG_Cells_Reporting_Description.component_1.e_utran_csg_fdd_reporting_threshold = 3;

   pvalue->component_16.component_3.component_2.component_3.component_4.csg_Cells_Reporting_Description.e_UTRAN_CSG_Cells_Reporting_Description.component_1.e_utran_csg_fdd_reporting_threshold_2 = 17;

   pvalue->component_16.component_3.component_2.component_3.component_4.csg_Cells_Reporting_Description.e_UTRAN_CSG_Cells_Reporting_Description.m.component_2Present = 1;

   pvalue->component_16.component_3.component_2.component_3.component_4.csg_Cells_Reporting_Description.e_UTRAN_CSG_Cells_Reporting_Description.component_2.e_utran_csg_tdd_reporting_threshold = 1;

   pvalue->component_16.component_3.component_2.component_3.component_4.csg_Cells_Reporting_Description.e_UTRAN_CSG_Cells_Reporting_Description.component_2.e_utran_csg_fdd_reporting_threshold_2 = 43;

   pvalue->component_16.component_3.component_2.component_3.component_4.m.component_3Present = 1;

   pvalue->component_16.component_3.component_2.component_3.component_4.component_3.m.init_pwr_redPresent = 1;
   pvalue->component_16.component_3.component_2.component_3.component_4.component_3.init_pwr_red = 0;

   pvalue->component_16.component_3.component_2.component_3.component_4.component_3.nc2_CSG_PCCN_permitted = 0;
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
   pdu.msgType = ASN1V_ts44018Msg_mt_SystemInformationType2quater;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType2quater;

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType2quater;
   pdu.restOctets.u.obj_SystemInformationType2quater =
      asn1Test_TS44018IE_SI2quater_Rest_Octets(pctxt);


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
