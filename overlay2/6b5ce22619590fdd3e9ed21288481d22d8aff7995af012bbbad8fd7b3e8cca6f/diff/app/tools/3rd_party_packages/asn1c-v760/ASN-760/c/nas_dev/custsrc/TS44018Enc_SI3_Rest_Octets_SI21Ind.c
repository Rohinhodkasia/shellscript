   /* The user is responsible for making sure system-Information-21-Indicator
      is present when it should be.
      The specification says, "This field is only present if "WHERE" information
      is not contained in SI 3 Rest Octets".
   */

   RTXCTXTPUSHELEMNAME (pctxt, "system-Information-21-Indicator");

   if (pvalue->m.system_Information_21_IndicatorPresent) {

      ret = NASEnc_TS44018IE_System_Information_21_Indicator (pctxt, &pvalue->
         system_Information_21_Indicator);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

   }
   RTXCTXTPOPELEMNAME (pctxt);

