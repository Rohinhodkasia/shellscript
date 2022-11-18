{
   /* calculate length */
   OSUINT32 i;
   pvalue->length = 1;
   for (i = 0; i < pvalue->pcoUnits.n; i++) {
      pvalue->length += (pvalue->pcoUnits.elem[i].contents.numocts + 3);
   }

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   if (pvalue->length >= 3 && pvalue->length <= 253) {
      ret = rtxEncUInt32 (pctxt, pvalue->length, 1);
      if (ret < 0) return LOG_RTERR (pctxt, ret);
   }
   else {
      return LOG_RTERR (pctxt, RTERR_INVLEN);
   }

   RTDIAG_SETBITFLDCOUNT (pctxt);
}
