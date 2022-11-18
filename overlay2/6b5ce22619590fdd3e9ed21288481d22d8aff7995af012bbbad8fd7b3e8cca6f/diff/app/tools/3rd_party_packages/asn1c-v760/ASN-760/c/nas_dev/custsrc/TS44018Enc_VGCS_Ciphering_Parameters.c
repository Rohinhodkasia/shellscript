EXTERN int NASEnc_TS44018IE_VGCS_Ciphering_Parameters (OSCTXT* pctxt
   , TS44018IE_VGCS_Ciphering_Parameters* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "VGCS-Ciphering-Parameters");

   /* encode spare */

   RTXCTXTPUSHELEMNAME (pctxt, "spare");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, 0, 2);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode rand-ind */

   RTXCTXTPUSHELEMNAME (pctxt, "rand-ind");
   RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

   ret = rtxEncBit (pctxt, pvalue->m.vstk_randPresent);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode lac-ind */

   RTXCTXTPUSHELEMNAME (pctxt, "lac-ind");
   RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

   ret = rtxEncBit (pctxt, pvalue->m.location_area_identificationPresent);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode cell-ind */

   RTXCTXTPUSHELEMNAME (pctxt, "cell-ind");
   RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

   ret = rtxEncBit (pctxt, pvalue->m.cell_identityPresent);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode b22-count */

   RTXCTXTPUSHELEMNAME (pctxt, "b22-count");
   if (!((pvalue->b22_count <= OSUINTCONST(1)))) {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddIntParm (pctxt, (int)pvalue->b22_count);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, pvalue->b22_count, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode cell-global-count */

   RTXCTXTPUSHELEMNAME (pctxt, "cell-global-count");
   if (!((pvalue->cell_global_count <= OSUINTCONST(3)))) {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddIntParm (pctxt, (int)pvalue->cell_global_count);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, pvalue->cell_global_count, 2);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode cell-identity */

   RTXCTXTPUSHELEMNAME (pctxt, "cell-identity");

   if (pvalue->m.cell_identityPresent) {
      RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

      ret = rtxEncUInt32 (pctxt, pvalue->cell_identity, 1);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);
   }
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode location-area-identification */

   RTXCTXTPUSHELEMNAME (pctxt, "location-area-identification");

   if (pvalue->m.location_area_identificationPresent) {
      RTDIAG_NEWBITFIELD (pctxt, "OCTET STRING");

      ret = rtxEncBitsFromByteArray (pctxt, pvalue->location_area_identification, 40);

      RTDIAG_SETBITFLDCOUNT (pctxt);
   }
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode vstk_rand */

   if (pvalue->m.vstk_randPresent) {
      RTXCTXTPUSHELEMNAME (pctxt, "vstk_rand");

      RTDIAG_NEWBITFIELD (pctxt, "BIT STRING");

      ret = rtxEncBitsFromByteArray (pctxt, pvalue->vstk_rand, 36);

      RTDIAG_SETBITFLDCOUNT (pctxt);
  
      RTXCTXTPOPELEMNAME (pctxt);

      /* encode spare2 */

      RTXCTXTPUSHELEMNAME (pctxt, "spare2");

      RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

      ret = rtxEncBits (pctxt, 0, 4);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);
      RTXCTXTPOPELEMNAME (pctxt);
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}