EXTERN int NASDec_TS24008IE_MobileStationClassmark2 (OSCTXT* pctxt
   , TS24008IE_MobileStationClassmark2* pvalue)
{
   int ret = 0;
   OSUINT8 len;

   RTXCTXTPUSHTYPENAME (pctxt, "MobileStationClassmark2");

   OSCRTLMEMSET (&pvalue->m, 0, sizeof(pvalue->m));

   /* Decode length */
   RTDIAG_NEWBITFIELD (pctxt, "length");

   ret = rtxReadBytes (pctxt, &len, 1);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   if (len > 0) {
      /* decode cm1 */
      RTXCTXTPUSHELEMNAME (pctxt, "cm1");

      ret = NASDec_TS24008IE_MobileStationClassmark1 (pctxt, &pvalue->cm1);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTXCTXTPOPELEMNAME (pctxt);
      pvalue->m.cm1Present = 1;
   }

   if (len > 1) {
      /* decode octet4 */
      RTXCTXTPUSHELEMNAME (pctxt, "octet4");

      ret = NASDec_TS24008IE_MobileStationClassmark2_octet4 
         (pctxt, &pvalue->octet4);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTXCTXTPOPELEMNAME (pctxt);
      pvalue->m.octet4Present = 1;
   }

   if (len > 2) {
      /* decode octet5 */
      RTXCTXTPUSHELEMNAME (pctxt, "octet5");

      ret = NASDec_TS24008IE_MobileStationClassmark2_octet5 
         (pctxt, &pvalue->octet5);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTXCTXTPOPELEMNAME (pctxt);
      pvalue->m.octet5Present = 1;
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
