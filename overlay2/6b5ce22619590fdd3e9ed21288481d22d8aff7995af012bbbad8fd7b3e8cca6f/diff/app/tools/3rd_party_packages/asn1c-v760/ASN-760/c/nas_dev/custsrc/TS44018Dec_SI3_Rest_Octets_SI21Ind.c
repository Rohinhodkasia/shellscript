   /* For system-Information-21-Indicator, the specification says, "This field
      is only present if "WHERE" information is not contained in SI 3 Rest 
      Octets".
   */

   RTXCTXTPUSHELEMNAME (pctxt, "system-Information-21-Indicator");
   
   if (!pvalue->scheduling_if_and_where.m.wherePresent) 
   {
      ret = NASDec_TS44018IE_System_Information_21_Indicator (pctxt, &pvalue
         ->system_Information_21_Indicator);
      if (ret < 0) return LOG_RTERR (pctxt, ret);
      pvalue->m.system_Information_21_IndicatorPresent = 1;
   }

   RTXCTXTPOPELEMNAME (pctxt);

