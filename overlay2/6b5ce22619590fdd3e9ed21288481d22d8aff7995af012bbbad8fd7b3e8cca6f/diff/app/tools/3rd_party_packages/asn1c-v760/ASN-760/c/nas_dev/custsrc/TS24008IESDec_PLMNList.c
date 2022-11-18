EXTERN int NASDec_TS24008IE_PLMNList (OSCTXT* pctxt, TS24008IE_PLMNList* pvalue
   )
{
   OSUINT8 i, length;
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "PLMNList");

   /* Decode length */
   RTDIAG_NEWBITFIELD (pctxt, "length");

   ret = rtxReadBytes (pctxt, &length, 1);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   if (length == 0) return 0;

   /* Each entry is 3 bytes in length, so length must be a multiple of 3 */
   if (length % 3 != 0) return LOG_RTERR (pctxt, RTERR_INVLEN);
   else pvalue->n = length / 3;

   for (i = 0; i < pvalue->n; i++) {
      RTXCTXTPUSHARRAYELEMNAME (pctxt, "elem", i);

      ret = NASDec_TS24008IE_MCCMNCPair (pctxt, &pvalue->elem[i]);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTXCTXTPOPARRAYELEMNAME (pctxt);
   }
   pvalue->n = i;

   if (!((pvalue->n >= 1 && pvalue->n <= 15))) {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddIntParm (pctxt, (int)pvalue->n);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
