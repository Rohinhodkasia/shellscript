EXTERN int NASDec_TS24008IE_AccessPointName (OSCTXT* pctxt
   , TS24008IE_AccessPointName pvalue)
{
   int ret = 0;
   OSOCTET len, rlen = 0, seglen;

   RTXCTXTPUSHTYPENAME (pctxt, "AccessPointName");

   RTDIAG_NEWBITFIELD (pctxt, "length");

   ret = rtxReadBytes (pctxt, &len, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   /* loop to read segments */

   while (!OSRTENDOFBUF (pctxt) && rlen < len) {
      /* decode segment length */
      RTDIAG_NEWBITFIELD (pctxt, "segment length");

      ret = rtxReadBytes (pctxt, &seglen, 1);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);

      rlen += (seglen + 1);
      if (rlen > len) return LOG_RTERR (pctxt, RTERR_INVLEN);

      /* decode segment content */
      RTDIAG_NEWBITFIELD (pctxt, "IA5String");

      ret = rtxReadBytes (pctxt, (OSOCTET*)pvalue, seglen);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);

      pvalue += seglen;
      *pvalue++ = (rlen < len) ? '.' : '\0';
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
