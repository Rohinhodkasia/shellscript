
#include <stdio.h>
#include "TS44018Misc.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxPrintStream.h"
#include "rt3gppsrc/rtx3GPP.h"

void TS44018IE_printArfcns(OSUINT16* values, OSSIZE count)
{
   printf("[");
   for(; count>0; count--) {
      printf("%u%s", *values, count > 1 ? "," : "");
      values++;
   }
   printf("]");
}


int TS44018IE_Cell_Channel_Description_decodeARFCN( OSCTXT* pctxt, 
                                 TS44018IE_Cell_Channel_Description* pccd,
                                 OSUINT16** pArfcns, OSUINT16* pArfcnCount)
{
   int ret = 0;
   OS3GPP_FREQ_LIST_FMT format;
   OSOCTET* data;
   OSUINT16 numbits;

   if ( pccd->t == 1 ) {
      /*bitmap0 format*/
      format = OS3GPP_FREQ_LIST_FMT_BITMAP0;
      data = pccd->u.bitmap0.bitmap0;
      numbits = 124;
   }
   else if ( pccd->t == 2 ) {
      switch (pccd->u.choice_2.component_2.t) {
         case T_Cell_Channel_Description_choice_2_component_2_range_1024 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_1024;
            data = pccd->u.choice_2.component_2.u.range_1024;
            numbits = 123;
            break;
         case T_Cell_Channel_Description_choice_2_component_2_range_512 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_512;
            data = pccd->u.choice_2.component_2.u.range_512;
            numbits = 121;
            break;
         case T_Cell_Channel_Description_choice_2_component_2_range_256 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_256;
            data = pccd->u.choice_2.component_2.u.range_256;
            numbits = 121;
            break;
         case T_Cell_Channel_Description_choice_2_component_2_range_128 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_128;
            data = pccd->u.choice_2.component_2.u.range_128;
            numbits = 121;
            break;
         case T_Cell_Channel_Description_choice_2_component_2_variable_bitmap :
            format = OS3GPP_FREQ_LIST_FMT_VAR_BITMAP;
            data = pccd->u.choice_2.component_2.u.variable_bitmap;
            numbits = 121;
            break;
         default: return LOG_RTERRNEW(pctxt, RTERR_BADVALUE);
      }
   }
   else return LOG_RTERRNEW(pctxt, RTERR_BADVALUE);

   ret = rtx3GPPDecARFCN(pctxt, format, data, numbits,
            pArfcns, pArfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);

   return ret;
}


int TS44018IE_Frequency_Short_List_decodeARFCN( OSCTXT* pctxt, 
                                 TS44018IE_Frequency_Short_List* pdata,
                                 OSUINT16** pArfcns, OSUINT16* pArfcnCount)
{
   int ret = 0;
   OS3GPP_FREQ_LIST_FMT format;
   OSOCTET* data;
   OSUINT16 numbits;
   
   switch (pdata->component_3.t) {
      case T_Frequency_Short_List_component_3_range_1024 :
         format = OS3GPP_FREQ_LIST_FMT_RANGE_1024;
         data = pdata->component_3.u.range_1024;
         numbits = 67;
         break;
      case T_Frequency_Short_List_component_3_range_512 :
         format = OS3GPP_FREQ_LIST_FMT_RANGE_512;
         data = pdata->component_3.u.range_512;
         numbits = 65;
         break;
      case T_Frequency_Short_List_component_3_range_256 :
         format = OS3GPP_FREQ_LIST_FMT_RANGE_256;
         data = pdata->component_3.u.range_256;
         numbits = 65;
         break;
      case T_Frequency_Short_List_component_3_range_128 :
         format = OS3GPP_FREQ_LIST_FMT_RANGE_128;
         data = pdata->component_3.u.range_128;
         numbits = 65;
         break;
      case T_Frequency_Short_List_component_3_variable_bitmap :
         format = OS3GPP_FREQ_LIST_FMT_VAR_BITMAP;
         data = pdata->component_3.u.variable_bitmap;
         numbits = 65;
         break;
      default: return LOG_RTERRNEW(pctxt, RTERR_BADVALUE);
   }

   ret = rtx3GPPDecARFCN(pctxt, format, data, numbits, pArfcns, pArfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);

   return ret;
}


int TS44018IE_Extended_Measurement_Frequency_List_decodeARFCN( OSCTXT* pctxt, 
                                 TS44018IE_Extended_Measurement_Frequency_List* pdata,
                                 OSUINT16** pArfcns, OSUINT16* pArfcnCount)
{
   int ret = 0;
   OS3GPP_FREQ_LIST_FMT format;
   OSOCTET* data;
   OSUINT16 numbits;

   if ( pdata->t == 1 ) {
      /*bitmap0 format*/
      format = OS3GPP_FREQ_LIST_FMT_BITMAP0;
      data = pdata->u.bitmap0.bitmap0;
      numbits = 124;
   }
   else if ( pdata->t == 2 ) {
      switch (pdata->u.choice_2.component_3.t) {
         case T_Extended_Measurement_Frequency_List_choice_2_component_3_range_1024 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_1024;
            data = pdata->u.choice_2.component_3.u.range_1024;
            numbits = 123;
            break;
         case T_Extended_Measurement_Frequency_List_choice_2_component_3_range_512 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_512;
            data = pdata->u.choice_2.component_3.u.range_512;
            numbits = 121;
            break;
         case T_Extended_Measurement_Frequency_List_choice_2_component_3_range_256 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_256;
            data = pdata->u.choice_2.component_3.u.range_256;
            numbits = 121;
            break;
         case T_Extended_Measurement_Frequency_List_choice_2_component_3_range_128 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_128;
            data = pdata->u.choice_2.component_3.u.range_128;
            numbits = 121;
            break;
         case T_Extended_Measurement_Frequency_List_choice_2_component_3_variable_bitmap :
            format = OS3GPP_FREQ_LIST_FMT_VAR_BITMAP;
            data = pdata->u.choice_2.component_3.u.variable_bitmap;
            numbits = 121;
            break;
         default: return LOG_RTERRNEW(pctxt, RTERR_BADVALUE);
      }
   }
   else return LOG_RTERRNEW(pctxt, RTERR_BADVALUE);

   ret = rtx3GPPDecARFCN(pctxt, format, data, numbits, pArfcns, pArfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);

   return ret;
}


int TS44018IE_Frequency_Short_List_2_decodeARFCN( OSCTXT* pctxt, 
                                 TS44018IE_Frequency_Short_List_2* pdata,
                                 OSUINT16** pArfcns, OSUINT16* pArfcnCount)
{
   int ret = 0;
   OS3GPP_FREQ_LIST_FMT format;
   OSOCTET* data;
   OSUINT16 numbits;
   
   switch (pdata->component_3.t) {
      case T_Frequency_Short_List_2_component_3_range_1024 :
         format = OS3GPP_FREQ_LIST_FMT_RANGE_1024;
         data = pdata->component_3.u.range_1024;
         numbits = 51;
         break;
      case T_Frequency_Short_List_2_component_3_range_512 :
         format = OS3GPP_FREQ_LIST_FMT_RANGE_512;
         data = pdata->component_3.u.range_512;
         numbits = 49;
         break;
      case T_Frequency_Short_List_2_component_3_range_256 :
         format = OS3GPP_FREQ_LIST_FMT_RANGE_256;
         data = pdata->component_3.u.range_256;
         numbits = 49;
         break;
      case T_Frequency_Short_List_2_component_3_range_128 :
         format = OS3GPP_FREQ_LIST_FMT_RANGE_128;
         data = pdata->component_3.u.range_128;
         numbits = 49;
         break;
      case T_Frequency_Short_List_2_component_3_variable_bitmap :
         format = OS3GPP_FREQ_LIST_FMT_VAR_BITMAP;
         data = pdata->component_3.u.variable_bitmap;
         numbits = 49;
         break;
      default: return LOG_RTERRNEW(pctxt, RTERR_BADVALUE);
   }

   ret = rtx3GPPDecARFCN(pctxt, format, data, numbits, pArfcns, pArfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);

   return ret;
}


int TS44018IE_Frequency_List_decodeARFCN( OSCTXT* pctxt, 
                                 TS44018IE_Frequency_List* pdata,
                                 OSUINT16** pArfcns, OSUINT16* pArfcnCount)
{
   int ret = 0;
   OS3GPP_FREQ_LIST_FMT format;
   const OSOCTET* data;
   OSUINT32 numbits;

   if ( pdata->component_2.t == 1 ) {
      /*bitmap0 format*/
      format = OS3GPP_FREQ_LIST_FMT_BITMAP0;
      data = pdata->component_2.u.bitmap0.bitmap0;
      numbits = 124;
   }
   else if ( pdata->component_2.t == 2 ) {
      switch (pdata->component_2.u.choice_2.component_2.t) {
         case T_Frequency_List_component_2_choice_2_component_2_range_1024 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_1024;
            data = pdata->component_2.u.choice_2.component_2.u.range_1024.data;
            numbits = pdata->component_2.u.choice_2.component_2.u.range_1024.numbits;
            break;
         case T_Frequency_List_component_2_choice_2_component_2_range_512 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_512;
            data = pdata->component_2.u.choice_2.component_2.u.range_512.data;
            numbits = pdata->component_2.u.choice_2.component_2.u.range_512.numbits;
            break;
         case T_Frequency_List_component_2_choice_2_component_2_range_256 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_256;
            data = pdata->component_2.u.choice_2.component_2.u.range_256.data;
            numbits = pdata->component_2.u.choice_2.component_2.u.range_256.numbits;
            break;
         case T_Frequency_List_component_2_choice_2_component_2_range_128 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_128;
            data = pdata->component_2.u.choice_2.component_2.u.range_128.data;
            numbits = pdata->component_2.u.choice_2.component_2.u.range_128.numbits;
            break;
         case T_Frequency_List_component_2_choice_2_component_2_variable_bitmap :
            format = OS3GPP_FREQ_LIST_FMT_VAR_BITMAP;
            data = pdata->component_2.u.choice_2.component_2.u.variable_bitmap.data;
            numbits = pdata->component_2.u.choice_2.component_2.u.variable_bitmap.numbits;
            break;
         default: return LOG_RTERRNEW(pctxt, RTERR_BADVALUE);
      }
   }
   else return LOG_RTERRNEW(pctxt, RTERR_BADVALUE);

   if ( numbits > 65535 ) return LOG_RTERRNEW(pctxt, RTERR_BADVALUE);
   
   ret = rtx3GPPDecARFCN(pctxt, format, data, (OSUINT16) numbits, 
                                                         pArfcns, pArfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);

   return ret;
}


int TS44018IE_Neighbour_Cell_Description_decodeARFCN( OSCTXT* pctxt, 
                                 TS44018IE_Neighbour_Cell_Description* pdata,
                                 OSUINT16** pArfcns, OSUINT16* pArfcnCount)
{
   int ret = 0;
   OS3GPP_FREQ_LIST_FMT format;
   OSOCTET* data;
   OSUINT16 numbits;

   if ( pdata->t == 1 ) {
      /*bitmap0 format*/
      format = OS3GPP_FREQ_LIST_FMT_BITMAP0;
      data = pdata->u.bitmap0.bitmap0;
      numbits = 124;
   }
   else if ( pdata->t == 2 ) {
      switch (pdata->u.choice_2.component_3.t) {
         case T_Neighbour_Cell_Description_choice_2_component_3_range_1024 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_1024;
            data = pdata->u.choice_2.component_3.u.range_1024;
            numbits = 123;
            break;
         case T_Neighbour_Cell_Description_choice_2_component_3_range_512 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_512;
            data = pdata->u.choice_2.component_3.u.range_512;
            numbits = 121;
            break;
         case T_Neighbour_Cell_Description_choice_2_component_3_range_256 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_256;
            data = pdata->u.choice_2.component_3.u.range_256;
            numbits = 121;
            break;
         case T_Neighbour_Cell_Description_choice_2_component_3_range_128 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_128;
            data = pdata->u.choice_2.component_3.u.range_128;
            numbits = 121;
            break;
         case T_Neighbour_Cell_Description_choice_2_component_3_variable_bitmap :
            format = OS3GPP_FREQ_LIST_FMT_VAR_BITMAP;
            data = pdata->u.choice_2.component_3.u.variable_bitmap;
            numbits = 121;
            break;
         default: return LOG_RTERRNEW(pctxt, RTERR_BADVALUE);
      }
   }
   else return LOG_RTERRNEW(pctxt, RTERR_BADVALUE);

   ret = rtx3GPPDecARFCN(pctxt, format, data, numbits, pArfcns, pArfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);

   return ret;
}


int TS44018IE_Neighbour_Cell_Description_2_decodeARFCN( OSCTXT* pctxt, 
                                 TS44018IE_Neighbour_Cell_Description_2* pdata,
                                 OSUINT16** pArfcns, OSUINT16* pArfcnCount)
{
   int ret = 0;
   OS3GPP_FREQ_LIST_FMT format;
   OSOCTET* data;
   OSUINT16 numbits;

   if ( pdata->t == 1 ) {
      /*bitmap0 format*/
      format = OS3GPP_FREQ_LIST_FMT_BITMAP0;
      data = pdata->u.bitmap0.ca_arfcn;
      numbits = 124;
   }
   else if ( pdata->t == 2 ) {
      switch (pdata->u.choice_2.component_3.t) {
         case T_Neighbour_Cell_Description_2_choice_2_component_3_range_1024 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_1024;
            data = pdata->u.choice_2.component_3.u.range_1024;
            numbits = 123;
            break;
         case T_Neighbour_Cell_Description_2_choice_2_component_3_range_512 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_512;
            data = pdata->u.choice_2.component_3.u.range_512;
            numbits = 121;
            break;
         case T_Neighbour_Cell_Description_2_choice_2_component_3_range_256 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_256;
            data = pdata->u.choice_2.component_3.u.range_256;
            numbits = 121;
            break;
         case T_Neighbour_Cell_Description_2_choice_2_component_3_range_128 :
            format = OS3GPP_FREQ_LIST_FMT_RANGE_128;
            data = pdata->u.choice_2.component_3.u.range_128;
            numbits = 121;
            break;
         case T_Neighbour_Cell_Description_2_choice_2_component_3_variable_bitmap :
            format = OS3GPP_FREQ_LIST_FMT_VAR_BITMAP;
            data = pdata->u.choice_2.component_3.u.variable_bitmap;
            numbits = 121;
            break;
         default: return LOG_RTERRNEW(pctxt, RTERR_BADVALUE);
      }
   }
   else return LOG_RTERRNEW(pctxt, RTERR_BADVALUE);

   ret = rtx3GPPDecARFCN(pctxt, format, data, numbits, pArfcns, pArfcnCount);

   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);

   return ret;
}