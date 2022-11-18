EXTERN int NASEnc_TS24008IE_MultibandSupported (OSCTXT* pctxt
   , TS24008IE_MultibandSupported* pvalue)
{
   int ret = 0;
   RTXCTXTPUSHTYPENAME (pctxt, "MultibandSupported");

   /* encode supported */

   RTXCTXTPUSHELEMNAME (pctxt, "supported");

   ret = NASEnc_TS24008IE_MBSEnum (pctxt, pvalue->supported);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode a5bits */

   RTXCTXTPUSHELEMNAME (pctxt, "a5bits");

   ret = NASEnc_TS24008IE_A5Bits (pctxt, &pvalue->a5bits);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   if (pvalue->supported != TS24008IE_MBSEnum_mbs0) {
      OSUINT8 value = 0;
      if (pvalue->supported == TS24008IE_MBSEnum_mbs5 ||
          pvalue->supported == TS24008IE_MBSEnum_mbs6) {
         /* set next field parameters to assocRadioCap2 */
         if (pvalue->assocRadioCap2 <= 15) {
            value = pvalue->assocRadioCap2;
            RTXCTXTPUSHELEMNAME (pctxt, "assocRadioCap2");
         }
         else {
            rtxErrAddElemNameParm (pctxt);
            rtxErrAddUIntParm (pctxt, pvalue->assocRadioCap2);
            return LOG_RTERR (pctxt, RTERR_CONSVIO);
         }
      }
      else {
         RTXCTXTPUSHELEMNAME (pctxt, "spare");
      }

      /* encode value (assocCap2 or spare) */

      RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

      ret = rtxEncBits (pctxt, value, 4);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);
      RTXCTXTPOPELEMNAME (pctxt);

      /* encode assocRadioCap1 */

      RTXCTXTPUSHELEMNAME (pctxt, "assocRadioCap1");

      if (pvalue->assocRadioCap1 <= 15) {
         RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

         ret = rtxEncBits (pctxt, pvalue->assocRadioCap1, 4);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);
      }
      else {
         rtxErrAddElemNameParm (pctxt);
         rtxErrAddUIntParm (pctxt, pvalue->assocRadioCap1);
         return LOG_RTERR (pctxt, RTERR_CONSVIO);
      }

      RTXCTXTPOPELEMNAME (pctxt);
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
