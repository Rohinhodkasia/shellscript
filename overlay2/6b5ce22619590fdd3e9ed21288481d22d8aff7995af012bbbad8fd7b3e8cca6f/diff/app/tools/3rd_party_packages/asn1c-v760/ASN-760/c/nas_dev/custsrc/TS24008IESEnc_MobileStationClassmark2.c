EXTERN int NASEnc_TS24008IE_MobileStationClassmark2 (OSCTXT* pctxt
   , TS24008IE_MobileStationClassmark2* pvalue)
{
   int ret = 0;
   OSUINT8 len = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "MobileStationClassmark2");

   if (pvalue->m.cm1Present) len++;
   if (pvalue->m.octet4Present) len++;
   if (pvalue->m.octet5Present) len++;

   /* Encode length */
   RTDIAG_NEWBITFIELD (pctxt, "length");

   ret = rtxWriteBytes (pctxt, &len, 1);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   /* encode cm1 */

   if (pvalue->m.cm1Present) {
      RTXCTXTPUSHELEMNAME (pctxt, "cm1");

      ret = NASEnc_TS24008IE_MobileStationClassmark1 (pctxt, &pvalue->cm1);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTXCTXTPOPELEMNAME (pctxt);
   }

   /* encode octet4 */

   if (pvalue->m.octet4Present) {
      RTXCTXTPUSHELEMNAME (pctxt, "octet4");

      ret = NASEnc_TS24008IE_MobileStationClassmark2_octet4 (pctxt, &pvalue->
         octet4);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTXCTXTPOPELEMNAME (pctxt);
   }

   /* encode octet5 */

   if (pvalue->m.octet5Present) {
      RTXCTXTPUSHELEMNAME (pctxt, "octet5");

      ret = NASEnc_TS24008IE_MobileStationClassmark2_octet5 (pctxt, &pvalue->
         octet5);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTXCTXTPOPELEMNAME (pctxt);
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
