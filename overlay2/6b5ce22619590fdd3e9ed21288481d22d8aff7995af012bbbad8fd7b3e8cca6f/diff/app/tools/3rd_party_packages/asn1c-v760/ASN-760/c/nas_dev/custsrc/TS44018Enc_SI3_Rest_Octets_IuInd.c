   /* The user must specify iu_Indicator is present when it should be.
      The specification says, "Iu Indicator is included if and only if GPRS is
      not supported and Iu mode is supported in the cell."
   */

   RTXCTXTPUSHELEMNAME (pctxt, "iu-Indicator");

   if (pvalue->m.iu_IndicatorPresent) {

      ret = NASEnc_TS44018IE_Iu_Indicator (pctxt, &pvalue->iu_Indicator);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

   }
   RTXCTXTPOPELEMNAME (pctxt);