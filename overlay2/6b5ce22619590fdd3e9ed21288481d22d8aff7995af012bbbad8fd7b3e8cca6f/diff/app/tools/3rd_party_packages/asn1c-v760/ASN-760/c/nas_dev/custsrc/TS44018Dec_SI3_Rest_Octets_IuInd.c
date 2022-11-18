   /* The specification says: "Iu Indicator is included if and only if GPRS is
      not supported and Iu mode is supported in the cell." 
   */

   RTXCTXTPUSHELEMNAME (pctxt, "iu-Indicator");

   if ( iuModeSupported && !pvalue->m.gprs_IndicatorPresent )
   {
      ret = NASDec_TS44018IE_Iu_Indicator (pctxt, &pvalue->iu_Indicator);
      if (ret < 0) return LOG_RTERR (pctxt, ret);
      pvalue->m.iu_IndicatorPresent = 1;
   }

   RTXCTXTPOPELEMNAME (pctxt);
