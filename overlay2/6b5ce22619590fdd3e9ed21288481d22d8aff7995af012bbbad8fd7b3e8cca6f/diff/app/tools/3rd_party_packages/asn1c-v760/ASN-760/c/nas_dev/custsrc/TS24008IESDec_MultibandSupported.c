EXTERN int NASDec_TS24008IE_MultibandSupported (OSCTXT* pctxt
   , TS24008IE_MultibandSupported* pvalue)
{
   int ret = 0;
   RTXCTXTPUSHTYPENAME (pctxt, "MultibandSupported");

   /* decode supported */

   RTXCTXTPUSHELEMNAME (pctxt, "supported");

   ret = NASDec_TS24008IE_MBSEnum (pctxt, &pvalue->supported);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode a5bits */

   RTXCTXTPUSHELEMNAME (pctxt, "a5bits");

   ret = NASDec_TS24008IE_A5Bits (pctxt, &pvalue->a5bits);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   if (pvalue->supported != TS24008IE_MBSEnum_mbs0) {
      /* decode assocRadioCap2 */

      RTXCTXTPUSHELEMNAME (pctxt, "assocRadioCap2");

      RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

      ret = rtxDecBitsToByte (pctxt, &pvalue->assocRadioCap2, 4);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);

      RTXCTXTPOPELEMNAME (pctxt);

      /* decode assocRadioCap1 */

      RTXCTXTPUSHELEMNAME (pctxt, "assocRadioCap1");

      RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

      ret = rtxDecBitsToByte (pctxt, &pvalue->assocRadioCap1, 4);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);

      RTXCTXTPOPELEMNAME (pctxt);
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

