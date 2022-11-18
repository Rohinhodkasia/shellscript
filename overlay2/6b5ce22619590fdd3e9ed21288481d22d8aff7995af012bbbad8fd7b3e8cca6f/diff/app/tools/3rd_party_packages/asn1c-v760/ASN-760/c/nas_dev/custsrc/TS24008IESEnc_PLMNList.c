EXTERN int NASEnc_TS24008IE_PLMNList (OSCTXT* pctxt, TS24008IE_PLMNList* pvalue
   )
{
   OSUINT8 i, length = pvalue->n * 3;
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "PLMNList");

   if (!((pvalue->n >= 1 && pvalue->n <= 15))) {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddIntParm (pctxt, (int)pvalue->n);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }

   /* encode length */
   RTDIAG_NEWBITFIELD (pctxt, "length");

   ret = rtxWriteBytes (pctxt, &length, 1);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   /* encode data */
   for (i = 0; i < pvalue->n; i++) {
      RTXCTXTPUSHARRAYELEMNAME (pctxt, "elem", i);

      ret = NASEnc_TS24008IE_MCCMNCPair (pctxt, &pvalue->elem[i]);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTXCTXTPOPARRAYELEMNAME (pctxt);
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
