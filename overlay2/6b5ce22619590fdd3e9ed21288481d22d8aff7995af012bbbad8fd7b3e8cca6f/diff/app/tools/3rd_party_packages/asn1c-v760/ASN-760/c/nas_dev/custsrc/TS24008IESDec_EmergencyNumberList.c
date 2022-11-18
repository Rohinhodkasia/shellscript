EXTERN int NASDec_TS24008IE_EmergencyNumberList (OSCTXT* pctxt
   , TS24008IE_EmergencyNumberList* pvalue)
{
   OSUINT8 len;
   int ret;

   RTXCTXTPUSHTYPENAME (pctxt, "EmergencyNumberList");

   /* Decode length */
   RTDIAG_NEWBITFIELD (pctxt, "length");

   ret = rtxDecBitsToByte (pctxt, &len, 8);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   pvalue->n = 0;

   if (len > 0) {
      TS24008IE_EmergencyNumber* pdata;
      OSSIZE offset = 0;

      while (offset < len) {
         if (pvalue->n < 10) {
            RTXCTXTPUSHARRAYELEMNAME (pctxt, "elem", pvalue->n);

            pdata = &pvalue->elem[pvalue->n++];

            ret = NASDec_TS24008IE_EmergencyNumber (pctxt, pdata);
            if (ret < 0) return LOG_RTERR (pctxt, ret);

            RTXCTXTPOPARRAYELEMNAME (pctxt);
         }
         else {
            rtxErrAddElemNameParm (pctxt);
            rtxErrAddIntParm (pctxt, pvalue->n);
            return LOG_RTERR (pctxt, RTERR_CONSVIO);
         }

         /* Total length of emergency number record is returned in ret */

         offset += ret;
      }
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret >= 0) ? 0 : ret;
}
