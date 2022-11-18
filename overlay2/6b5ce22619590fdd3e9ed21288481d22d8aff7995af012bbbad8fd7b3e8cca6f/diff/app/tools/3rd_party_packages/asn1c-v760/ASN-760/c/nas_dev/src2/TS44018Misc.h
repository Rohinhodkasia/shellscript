#ifndef TS44018MISC_H
#define TS44018MISC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "TS44018IES.h"

/**
 * The *_decodeARFCN helper methods declared in this header don't do very much
 * more than call rtx3GPPDecARFCN to decode the ARFCN list, but they are
 * convenient in that they use the fields of the IE and knowledge of the IE's
 * layout to determine the parameters to pass to rtx3GPPDecARFCN.
 */

/**
 * Print the given array of values to standard out.
 */
EXTERN void TS44018IE_printArfcns(OSUINT16* values, OSSIZE count);

/**
 * Decode the ARFCNs in a Cell-Channel-Description IE
 * 
 * @param pctxt   Pointer to context.
 * @param pdata    Pointer to Cell Channel Description IE
 * @param pArfcns Pointer to ARFCN array; receives a newly allocated array.
 * @param pArfcnCount   Pointer to # of ARFCNs; receives # of ARFCNs
 */
EXTERN int TS44018IE_Cell_Channel_Description_decodeARFCN( OSCTXT* pctxt, 
                                 TS44018IE_Cell_Channel_Description* pdata,
                                 OSUINT16** pArfcns, OSUINT16* pArfcnCount);

/**
 * Decode the ARFCNs in an Extended-Measurement-Frequency-List IE
 * 
 * @param pctxt   Pointer to context.
 * @param pdata    Pointer to IE
 * @param pArfcns Pointer to ARFCN array; receives a newly allocated array.
 * @param pArfcnCount   Pointer to # of ARFCNs; receives # of ARFCNs
 */
EXTERN int TS44018IE_Extended_Measurement_Frequency_List_decodeARFCN( OSCTXT* pctxt, 
                                 TS44018IE_Extended_Measurement_Frequency_List* pdata,
                                 OSUINT16** pArfcns, OSUINT16* pArfcnCount);
/**
 * Decode the ARFCNs in a Frequency-List IE
 * 
 * @param pctxt   Pointer to context.
 * @param pdata    Pointer to IE
 * @param pArfcns Pointer to ARFCN array; receives a newly allocated array.
 * @param pArfcnCount   Pointer to # of ARFCNs; receives # of ARFCNs
 */
EXTERN int TS44018IE_Frequency_List_decodeARFCN( OSCTXT* pctxt, 
                                 TS44018IE_Frequency_List* pdata,
                                 OSUINT16** pArfcns, OSUINT16* pArfcnCount);

/**
 * Decode the ARFCNs in a Frequency-Short-List IE
 * 
 * @param pctxt   Pointer to context.
 * @param pdata    Pointer to IE
 * @param pArfcns Pointer to ARFCN array; receives a newly allocated array.
 * @param pArfcnCount   Pointer to # of ARFCNs; receives # of ARFCNs
 */
EXTERN int TS44018IE_Frequency_Short_List_decodeARFCN( OSCTXT* pctxt, 
                                 TS44018IE_Frequency_Short_List* pdata,
                                 OSUINT16** pArfcns, OSUINT16* pArfcnCount);


/**
 * Decode the ARFCNs in a Frequency-Short-List-2 IE
 * 
 * @param pctxt   Pointer to context.
 * @param pdata    Pointer to IE
 * @param pArfcns Pointer to ARFCN array; receives a newly allocated array.
 * @param pArfcnCount   Pointer to # of ARFCNs; receives # of ARFCNs
 */
EXTERN int TS44018IE_Frequency_Short_List_2_decodeARFCN( OSCTXT* pctxt, 
                                 TS44018IE_Frequency_Short_List_2* pdata,
                                 OSUINT16** pArfcns, OSUINT16* pArfcnCount);



/**
 * Decode the ARFCNs in a Neighbour-Cell-Description IE
 * 
 * @param pctxt   Pointer to context.
 * @param pdata    Pointer to IE
 * @param pArfcns Pointer to ARFCN array; receives a newly allocated array.
 * @param pArfcnCount   Pointer to # of ARFCNs; receives # of ARFCNs
 */
EXTERN int TS44018IE_Neighbour_Cell_Description_decodeARFCN( OSCTXT* pctxt, 
                                 TS44018IE_Neighbour_Cell_Description* pdata,
                                 OSUINT16** pArfcns, OSUINT16* pArfcnCount);

/**
 * Decode the ARFCNs in a Neighbour-Cell-Description_2 IE
 * 
 * @param pctxt   Pointer to context.
 * @param pdata    Pointer to IE
 * @param pArfcns Pointer to ARFCN array; receives a newly allocated array.
 * @param pArfcnCount   Pointer to # of ARFCNs; receives # of ARFCNs
 */
EXTERN int TS44018IE_Neighbour_Cell_Description_2_decodeARFCN( OSCTXT* pctxt, 
                                 TS44018IE_Neighbour_Cell_Description_2* pdata,
                                 OSUINT16** pArfcns, OSUINT16* pArfcnCount);

#ifdef __cplusplus
}
#endif

#endif