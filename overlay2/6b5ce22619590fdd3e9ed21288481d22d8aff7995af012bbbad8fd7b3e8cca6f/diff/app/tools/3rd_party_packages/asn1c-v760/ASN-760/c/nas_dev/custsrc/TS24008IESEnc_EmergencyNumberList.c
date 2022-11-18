EXTERN int NASEnc_TS24008IE_EmergencyNumberList (OSCTXT* pctxt
   , TS24008IE_EmergencyNumberList* pvalue)
{
   int ret = 0;
   RTXCTXTPUSHTYPENAME (pctxt, "EmergencyNumberList");

   if (pvalue->n > 0) {
      OSSIZE nbytes = 0;
      OSUINT8 i, ub, len;

      /* Calculate and encode length in bytes */
      for (i = 0; i < pvalue->n; i++) {
         ret = NAS_Get_TS24008IE_EmergencyNumberLength (&pvalue->elem[i], &len);
         if (0 == ret) nbytes += (len + 1);
         else return LOG_RTERR (pctxt, ret);
      }

      if (nbytes > 255) return LOG_RTERR (pctxt, RTERR_TOOBIG);
      else ub = (OSUINT8) nbytes;

      RTDIAG_NEWBITFIELD (pctxt, "length");

      ret = rtxWriteBytes (pctxt, &ub, 1);
      if (0 != ret) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);

      /* Encode numbers */
      for (i = 0; i < pvalue->n; i++) {
         RTXCTXTPUSHARRAYELEMNAME (pctxt, "elem", i);

         ret = NASEnc_TS24008IE_EmergencyNumber (pctxt, &pvalue->elem[i]);
         if (0 != ret) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPARRAYELEMNAME (pctxt);
      }
   }
   else {
      /* Encode zero length */
      RTDIAG_NEWBITFIELD (pctxt, "length");

      ret = rtxEncBits (pctxt, 0, 8);
      if (0 != ret) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
