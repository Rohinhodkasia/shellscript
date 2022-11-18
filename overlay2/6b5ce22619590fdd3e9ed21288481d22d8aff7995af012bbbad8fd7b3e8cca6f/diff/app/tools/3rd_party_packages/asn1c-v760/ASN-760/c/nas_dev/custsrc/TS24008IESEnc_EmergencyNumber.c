EXTERN int NASEnc_TS24008IE_EmergencyNumber (OSCTXT* pctxt
   , TS24008IE_EmergencyNumber* pvalue)
{
   int ret = 0;
   OSUINT8 len;

   RTXCTXTPUSHTYPENAME (pctxt, "EmergencyNumber");

   /* encode length */

   ret = NAS_Get_TS24008IE_EmergencyNumberLength (pvalue, &len);
   if (0 == ret) {
      RTDIAG_NEWBITFIELD (pctxt, "length");

      ret = rtxWriteBytes (pctxt, &len, 1);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);
   }
   else {
      return LOG_RTERR (pctxt, ret);
   }

   /* encode spare */

   ret = rtxEncBits (pctxt, 0, 3);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   /* encode catValue */

   RTXCTXTPUSHELEMNAME (pctxt, "catValue");
   if (pvalue->catValue <= 31) {
      RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

      ret = rtxEncBits (pctxt, pvalue->catValue, 5);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);
   }
   else {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddUIntParm (pctxt, pvalue->catValue);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode digits */

   RTXCTXTPUSHELEMNAME (pctxt, "digits");

   ret = NASEnc_TS24008IE_TBCDString (pctxt, pvalue->digits);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
