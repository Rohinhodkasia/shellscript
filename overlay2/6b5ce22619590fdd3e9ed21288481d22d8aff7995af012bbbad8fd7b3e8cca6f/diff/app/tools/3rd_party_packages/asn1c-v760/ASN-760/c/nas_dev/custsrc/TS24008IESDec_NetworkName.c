EXTERN int NASDec_TS24008IE_NetworkName 
(OSCTXT* pctxt, TS24008IE_NetworkName* pvalue)
{
   char* pstr;
   int ret = 0;
   RTXCTXTPUSHTYPENAME (pctxt, "NetworkName");

   /* decode length */

   RTXCTXTPUSHELEMNAME (pctxt, "length");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->length, 8);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode ext */

   RTXCTXTPUSHELEMNAME (pctxt, "ext");

   RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

   ret = rtxDecBit (pctxt, &pvalue->ext);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode codingScheme */

   RTXCTXTPUSHELEMNAME (pctxt, "codingScheme");

   ret = NASDec_TS24008IE_NetworkName_codingScheme (pctxt, &pvalue->
      codingScheme);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode addCI */

   RTXCTXTPUSHELEMNAME (pctxt, "addCI");

   RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

   ret = rtxDecBit (pctxt, &pvalue->addCI);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode numSpareBitsInLastOct */

   RTXCTXTPUSHELEMNAME (pctxt, "numSpareBitsInLastOct");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->numSpareBitsInLastOct, 3);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode textString */

   if (pvalue->length > 1) {
      RTXCTXTPUSHELEMNAME (pctxt, "textString");

      pstr = (char*) rtxMemAlloc (pctxt, pvalue->length);
      if (0 == pstr) return LOG_RTERR (pctxt, RTERR_NOMEM);

      ret = rtxReadBytes (pctxt, (OSOCTET*)pstr, pvalue->length - 1);
      pstr[pvalue->length - 1] = '\0';
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      pvalue->textString = pstr;

      RTXCTXTPOPELEMNAME (pctxt);
   }
   else {
      pvalue->textString = 0;
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
