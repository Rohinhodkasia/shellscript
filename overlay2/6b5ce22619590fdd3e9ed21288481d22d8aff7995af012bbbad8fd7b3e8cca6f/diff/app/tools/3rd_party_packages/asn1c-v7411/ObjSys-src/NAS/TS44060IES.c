/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.4.1.1, Date: 02-Jun-2020.
 */
#include "TS44060IES.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxDiagBitTrace.h"

/* TS44060IE_PCID_Group_IE_pcid_list */

int asn1Init_TS44060IE_PCID_Group_IE_pcid_list (
   TS44060IE_PCID_Group_IE_pcid_list* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->elem = 0;
   pvalue->n = 0;
   return 0;
}

/* TS44060IE_PCID_Group_IE_component_3_element_pcid_Pattern */

int asn1Init_TS44060IE_PCID_Group_IE_component_3_element_pcid_Pattern (
   TS44060IE_PCID_Group_IE_component_3_element_pcid_Pattern* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->numbits = 0;
   return 0;
}

/* TS44060IE_PCID_Group_IE_component_3_element */

int asn1Init_TS44060IE_PCID_Group_IE_component_3_element (
   TS44060IE_PCID_Group_IE_component_3_element* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   asn1Init_TS44060IE_PCID_Group_IE_component_3_element_pcid_Pattern (&pvalue->pcid_Pattern);
   return 0;
}

/* TS44060IE__SeqOfTS44060IE_PCID_Group_IE_component_3_element */

int asn1Init_TS44060IE__SeqOfTS44060IE_PCID_Group_IE_component_3_element (
   TS44060IE__SeqOfTS44060IE_PCID_Group_IE_component_3_element* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->elem = 0;
   pvalue->n = 0;
   return 0;
}

/* TS44060IE_PCID_Group_IE */

int asn1Init_TS44060IE_PCID_Group_IE (TS44060IE_PCID_Group_IE* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   asn1Init_TS44060IE_PCID_Group_IE_pcid_list (&pvalue->pcid_list);
   asn1Init_TS44060IE__SeqOfTS44060IE_PCID_Group_IE_component_3_element (&pvalue->component_3);
   return 0;
}

/* TS44060IE_PLMN_ID_struct */

/* TS44060IE_UTRAN_CSG_Measurement_Report_IE */

int asn1Init_TS44060IE_UTRAN_CSG_Measurement_Report_IE (
   TS44060IE_UTRAN_CSG_Measurement_Report_IE* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   return 0;
}

/* TS44060IE_PSC_Group_IE_psc_list */

int asn1Init_TS44060IE_PSC_Group_IE_psc_list (
   TS44060IE_PSC_Group_IE_psc_list* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->elem = 0;
   pvalue->n = 0;
   return 0;
}

/* TS44060IE_PSC_Group_IE_component_2_element_psc_Pattern */

int asn1Init_TS44060IE_PSC_Group_IE_component_2_element_psc_Pattern (
   TS44060IE_PSC_Group_IE_component_2_element_psc_Pattern* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->numbits = 0;
   return 0;
}

/* TS44060IE_PSC_Group_IE_component_2_element */

int asn1Init_TS44060IE_PSC_Group_IE_component_2_element (
   TS44060IE_PSC_Group_IE_component_2_element* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   asn1Init_TS44060IE_PSC_Group_IE_component_2_element_psc_Pattern (&pvalue->psc_Pattern);
   return 0;
}

/* TS44060IE__SeqOfTS44060IE_PSC_Group_IE_component_2_element */

int asn1Init_TS44060IE__SeqOfTS44060IE_PSC_Group_IE_component_2_element (
   TS44060IE__SeqOfTS44060IE_PSC_Group_IE_component_2_element* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->elem = 0;
   pvalue->n = 0;
   return 0;
}

/* TS44060IE_PSC_Group_IE */

int asn1Init_TS44060IE_PSC_Group_IE (TS44060IE_PSC_Group_IE* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   asn1Init_TS44060IE_PSC_Group_IE_psc_list (&pvalue->psc_list);
   asn1Init_TS44060IE__SeqOfTS44060IE_PSC_Group_IE_component_2_element (&pvalue->component_2);
   return 0;
}

/* TS44060IE_GPRS_Cell_Options_IE_component_8 */

/* TS44060IE_Extension_Information_component_1_component_1 */

/* TS44060IE_Extension_Information_component_1 */

int asn1Init_TS44060IE_Extension_Information_component_1 (
   TS44060IE_Extension_Information_component_1* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   return 0;
}

/* TS44060IE_Extension_Information_component_2 */

/* TS44060IE_Extension_Information_component_3_component_4 */

/* TS44060IE_Extension_Information_component_3 */

int asn1Init_TS44060IE_Extension_Information_component_3 (
   TS44060IE_Extension_Information_component_3* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   return 0;
}

/* TS44060IE_Extension_Information */

int asn1Init_TS44060IE_Extension_Information (
   TS44060IE_Extension_Information* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   asn1Init_TS44060IE_Extension_Information_component_1 (&pvalue->component_1);
   asn1Init_TS44060IE_Extension_Information_component_3 (&pvalue->component_3);
   return 0;
}

/* TS44060IE_GPRS_Cell_Options_IE_component_9 */

int asn1Init_TS44060IE_GPRS_Cell_Options_IE_component_9 (
   TS44060IE_GPRS_Cell_Options_IE_component_9* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   asn1Init_TS44060IE_Extension_Information (&pvalue->extension_Information);
   return 0;
}

/* TS44060IE_GPRS_Cell_Options_IE */

int asn1Init_TS44060IE_GPRS_Cell_Options_IE (
   TS44060IE_GPRS_Cell_Options_IE* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   asn1Init_TS44060IE_GPRS_Cell_Options_IE_component_9 (&pvalue->component_9);
   return 0;
}

/* TS44060IE_GPRS_Power_Control_Parameters_IE */

/* TS44060IE_Packet_Timing_Advance_IE_component_2 */

/* TS44060IE_Packet_Timing_Advance_IE */

int asn1Init_TS44060IE_Packet_Timing_Advance_IE (
   TS44060IE_Packet_Timing_Advance_IE* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   return 0;
}

/* TS44060IE_EGPRS_Modulation_and_Coding_IE */

/* TS44060IE_EGPRS_Window_Size_IE */

/* TS44060IE_EGPRS_Level_IE */

/* TS44060IE_Pulse_Format_Coding_2_struct_choice_1_pulse_Format_Bitmap */

int asn1Init_TS44060IE_Pulse_Format_Coding_2_struct_choice_1_pulse_Format_Bitmap (
   TS44060IE_Pulse_Format_Coding_2_struct_choice_1_pulse_Format_Bitmap* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->numbits = 0;
   return 0;
}

/* TS44060IE_Pulse_Format_Coding_2_struct_choice_1 */

int asn1Init_TS44060IE_Pulse_Format_Coding_2_struct_choice_1 (
   TS44060IE_Pulse_Format_Coding_2_struct_choice_1* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   asn1Init_TS44060IE_Pulse_Format_Coding_2_struct_choice_1_pulse_Format_Bitmap (&pvalue->pulse_Format_Bitmap);
   return 0;
}

/* TS44060IE_Pulse_Format_Coding_2_struct_non_Hopping_Carrier_Pulse_Format */

int asn1Init_TS44060IE_Pulse_Format_Coding_2_struct_non_Hopping_Carrier_Pulse_Format (
   TS44060IE_Pulse_Format_Coding_2_struct_non_Hopping_Carrier_Pulse_Format* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->t = 0;
   return 0;
}

/* TS44060IE_Pulse_Format_Coding_2_struct */

int asn1Init_TS44060IE_Pulse_Format_Coding_2_struct (
   TS44060IE_Pulse_Format_Coding_2_struct* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->t = 0;
   OSCRTLMEMSET (&pvalue->u, 0, sizeof(pvalue->u));
   return 0;
}

/* TS44060IE_Pulse_Format_IE */

int asn1Init_TS44060IE_Pulse_Format_IE (TS44060IE_Pulse_Format_IE* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->t = 0;
   OSCRTLMEMSET (&pvalue->u, 0, sizeof(pvalue->u));
   return 0;
}

/* TS44060IE_Power_Control_Parameters_IE */

int asn1Init_TS44060IE_Power_Control_Parameters_IE (
   TS44060IE_Power_Control_Parameters_IE* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   return 0;
}

/* TS44060IE_Indirect_encoding_struct_component_3 */

int asn1Init_TS44060IE_Indirect_encoding_struct_component_3 (
   TS44060IE_Indirect_encoding_struct_component_3* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   return 0;
}

/* TS44060IE_Indirect_encoding_struct */

int asn1Init_TS44060IE_Indirect_encoding_struct (
   TS44060IE_Indirect_encoding_struct* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   asn1Init_TS44060IE_Indirect_encoding_struct_component_3 (&pvalue->component_3);
   return 0;
}

/* TS44060IE_GPRS_Mobile_Allocation_IE_rfl_number_list */

int asn1Init_TS44060IE_GPRS_Mobile_Allocation_IE_rfl_number_list (
   TS44060IE_GPRS_Mobile_Allocation_IE_rfl_number_list* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->elem = 0;
   pvalue->n = 0;
   return 0;
}

/* TS44060IE_GPRS_Mobile_Allocation_IE_component_3_choice_1_ma_bitmap */

int asn1Init_TS44060IE_GPRS_Mobile_Allocation_IE_component_3_choice_1_ma_bitmap (
   TS44060IE_GPRS_Mobile_Allocation_IE_component_3_choice_1_ma_bitmap* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->numbits = 0;
   return 0;
}

/* TS44060IE_GPRS_Mobile_Allocation_IE_component_3_choice_1 */

int asn1Init_TS44060IE_GPRS_Mobile_Allocation_IE_component_3_choice_1 (
   TS44060IE_GPRS_Mobile_Allocation_IE_component_3_choice_1* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   asn1Init_TS44060IE_GPRS_Mobile_Allocation_IE_component_3_choice_1_ma_bitmap (&pvalue->ma_bitmap);
   return 0;
}

/* TS44060IE_GPRS_Mobile_Allocation_IE_component_3_choice_2 */

int asn1Init_TS44060IE_GPRS_Mobile_Allocation_IE_component_3_choice_2 (
   TS44060IE_GPRS_Mobile_Allocation_IE_component_3_choice_2* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->elem = 0;
   pvalue->n = 0;
   return 0;
}

/* TS44060IE_GPRS_Mobile_Allocation_IE_component_3 */

int asn1Init_TS44060IE_GPRS_Mobile_Allocation_IE_component_3 (
   TS44060IE_GPRS_Mobile_Allocation_IE_component_3* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->t = 0;
   OSCRTLMEMSET (&pvalue->u, 0, sizeof(pvalue->u));
   return 0;
}

/* TS44060IE_GPRS_Mobile_Allocation_IE */

int asn1Init_TS44060IE_GPRS_Mobile_Allocation_IE (
   TS44060IE_GPRS_Mobile_Allocation_IE* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   asn1Init_TS44060IE_GPRS_Mobile_Allocation_IE_rfl_number_list (&pvalue->rfl_number_list);
   asn1Init_TS44060IE_GPRS_Mobile_Allocation_IE_component_3 (&pvalue->component_3);
   return 0;
}

/* TS44060IE_Direct_encoding_1_struct */

int asn1Init_TS44060IE_Direct_encoding_1_struct (
   TS44060IE_Direct_encoding_1_struct* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   asn1Init_TS44060IE_GPRS_Mobile_Allocation_IE (&pvalue->gprs_Mobile_Allocation);
   return 0;
}

/* TS44060IE_Direct_encoding_2_struct_ma_Frequency_List_contents */

int asn1Init_TS44060IE_Direct_encoding_2_struct_ma_Frequency_List_contents (
   TS44060IE_Direct_encoding_2_struct_ma_Frequency_List_contents* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->numocts = 0;
   return 0;
}

/* TS44060IE_Direct_encoding_2_struct */

int asn1Init_TS44060IE_Direct_encoding_2_struct (
   TS44060IE_Direct_encoding_2_struct* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   asn1Init_TS44060IE_Direct_encoding_2_struct_ma_Frequency_List_contents (&pvalue->ma_Frequency_List_contents);
   return 0;
}

/* TS44060IE_Frequency_Parameters_IE_component_2 */

int asn1Init_TS44060IE_Frequency_Parameters_IE_component_2 (
   TS44060IE_Frequency_Parameters_IE_component_2* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->t = 0;
   OSCRTLMEMSET (&pvalue->u, 0, sizeof(pvalue->u));
   return 0;
}

/* TS44060IE_Frequency_Parameters_IE */

int asn1Init_TS44060IE_Frequency_Parameters_IE (
   TS44060IE_Frequency_Parameters_IE* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   asn1Init_TS44060IE_Frequency_Parameters_IE_component_2 (&pvalue->component_2);
   return 0;
}

/* TS44060IE_MPRACH_Control_Parameters_IE */

int asn1Init_TS44060IE_MPRACH_Control_Parameters_IE (
   TS44060IE_MPRACH_Control_Parameters_IE* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   return 0;
}

/* TS44060IE_MPRACH_description_IE */

int asn1Init_TS44060IE_MPRACH_description_IE (
   TS44060IE_MPRACH_description_IE* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   asn1Init_TS44060IE_Frequency_Parameters_IE (&pvalue->frequency_Parameters);
   asn1Init_TS44060IE_MPRACH_Control_Parameters_IE (&pvalue->mprach_Control_Parameters);
   return 0;
}

/* TS44060IE_MBMS_p_t_m_channel_description_IE */

int asn1Init_TS44060IE_MBMS_p_t_m_channel_description_IE (
   TS44060IE_MBMS_p_t_m_channel_description_IE* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   asn1Init_TS44060IE_Frequency_Parameters_IE (&pvalue->frequency_Parameters);
   return 0;
}

/* TS44060IE_MBMS_Session_Parameters_List_IE_element_mbms_Bearer_Identity */

int asn1Init_TS44060IE_MBMS_Session_Parameters_List_IE_element_mbms_Bearer_Identity (
   TS44060IE_MBMS_Session_Parameters_List_IE_element_mbms_Bearer_Identity* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->numbits = 0;
   return 0;
}

/* TS44060IE_MBMS_Session_Parameters_List_IE_element */

int asn1Init_TS44060IE_MBMS_Session_Parameters_List_IE_element (
   TS44060IE_MBMS_Session_Parameters_List_IE_element* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   asn1Init_TS44060IE_MBMS_Session_Parameters_List_IE_element_mbms_Bearer_Identity (&pvalue->mbms_Bearer_Identity);
   return 0;
}

/* TS44060IE_MBMS_Session_Parameters_List_IE */

int asn1Init_TS44060IE_MBMS_Session_Parameters_List_IE (
   TS44060IE_MBMS_Session_Parameters_List_IE* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->elem = 0;
   pvalue->n = 0;
   return 0;
}

/* TS44060IE_Channel_Request_Description_IE */

/* TS44060IE_TMGI_IE_choice_2 */

/* TS44060IE_TMGI_IE */

int asn1Init_TS44060IE_TMGI_IE (TS44060IE_TMGI_IE* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->t = 0;
   OSCRTLMEMSET (&pvalue->u, 0, sizeof(pvalue->u));
   return 0;
}

/* TS44060IE_MBMS_Channel_Parameters_IE_choice_1_component_1 */

int asn1Init_TS44060IE_MBMS_Channel_Parameters_IE_choice_1_component_1 (
   TS44060IE_MBMS_Channel_Parameters_IE_choice_1_component_1* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   asn1Init_TS44060IE_MBMS_p_t_m_channel_description_IE (&pvalue->mbms_p_t_m_channel_description);
   asn1Init_TS44060IE_MBMS_Session_Parameters_List_IE (&pvalue->mbms_Session_Parameters_List);
   return 0;
}

/* TS44060IE_MBMS_Channel_Parameters_IE_choice_1 */

int asn1Init_TS44060IE_MBMS_Channel_Parameters_IE_choice_1 (
   TS44060IE_MBMS_Channel_Parameters_IE_choice_1* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   asn1Init_TS44060IE_MBMS_Channel_Parameters_IE_choice_1_component_1 (&pvalue->component_1);
   return 0;
}

/* TS44060IE_MBMS_Channel_Parameters_IE_choice_2 */

int asn1Init_TS44060IE_MBMS_Channel_Parameters_IE_choice_2 (
   TS44060IE_MBMS_Channel_Parameters_IE_choice_2* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   asn1Init_TS44060IE_MPRACH_description_IE (&pvalue->mprach_description);
   return 0;
}

/* TS44060IE_MBMS_Channel_Parameters_IE */

int asn1Init_TS44060IE_MBMS_Channel_Parameters_IE (
   TS44060IE_MBMS_Channel_Parameters_IE* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->t = 0;
   OSCRTLMEMSET (&pvalue->u, 0, sizeof(pvalue->u));
   return 0;
}

/* TS44060IE_MBMS_Session_List_IE_element */

int asn1Init_TS44060IE_MBMS_Session_List_IE_element (
   TS44060IE_MBMS_Session_List_IE_element* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   asn1Init_TS44060IE_TMGI_IE (&pvalue->tmgi);
   return 0;
}

/* TS44060IE_MBMS_Session_List_IE */

int asn1Init_TS44060IE_MBMS_Session_List_IE (
   TS44060IE_MBMS_Session_List_IE* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->elem = 0;
   pvalue->n = 0;
   return 0;
}

/* TS44060IE_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_e_utran_frequency_index_list */

int asn1Init_TS44060IE_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_e_utran_frequency_index_list (
   TS44060IE_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_e_utran_frequency_index_list* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->elem = 0;
   pvalue->n = 0;
   return 0;
}

/* TS44060IE_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_component_2_choice_2 */

int asn1Init_TS44060IE_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_component_2_choice_2 (
   TS44060IE_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_component_2_choice_2* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   return 0;
}

/* TS44060IE_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_component_2 */

int asn1Init_TS44060IE_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_component_2 (
   TS44060IE_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_component_2* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->t = 0;
   OSCRTLMEMSET (&pvalue->u, 0, sizeof(pvalue->u));
   return 0;
}

/* TS44060IE_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct */

int asn1Init_TS44060IE_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct (
   TS44060IE_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   asn1Init_TS44060IE_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_e_utran_frequency_index_list (&pvalue->e_utran_frequency_index_list);
   asn1Init_TS44060IE_Repeated_E_UTRAN_Enhanced_Cell_Reselection_Parameters_struct_component_2 (&pvalue->component_2);
   return 0;
}

/* TS44060IE_Enhanced_Cell_Reselection_Parameters_IE */

int asn1Init_TS44060IE_Enhanced_Cell_Reselection_Parameters_IE (
   TS44060IE_Enhanced_Cell_Reselection_Parameters_IE* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->elem = 0;
   pvalue->n = 0;
   return 0;
}

/* TS44060IE_Global_Packet_Timing_Advance_IE_component_2 */

/* TS44060IE_Global_Packet_Timing_Advance_IE_component_3 */

/* TS44060IE_Global_Packet_Timing_Advance_IE */

int asn1Init_TS44060IE_Global_Packet_Timing_Advance_IE (
   TS44060IE_Global_Packet_Timing_Advance_IE* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->m, 0, sizeof (pvalue->m));
   return 0;
}

