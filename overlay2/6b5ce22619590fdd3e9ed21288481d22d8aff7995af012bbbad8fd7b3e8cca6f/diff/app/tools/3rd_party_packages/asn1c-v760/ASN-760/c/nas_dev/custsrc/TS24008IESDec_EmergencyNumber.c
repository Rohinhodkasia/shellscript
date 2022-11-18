EXTERN int NASDec_TS24008IE_EmergencyNumber (OSCTXT* pctxt
   , TS24008IE_EmergencyNumber* pvalue)
{
   OSUINT8 len;
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "EmergencyNumber");

   /* decode length */

   RTDIAG_NEWBITFIELD (pctxt, "length");

   ret = rtxReadBytes (pctxt, &len, 1);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   if (len == 0) { return 1; }

   /* skip spare bits */

   ret = rtxSkipBits (pctxt, 3);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   /* decode catValue */

   RTXCTXTPUSHELEMNAME (pctxt, "catValue");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->catValue, 5);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   if (len == 1) { return 2; }

   /* decode digits */

   RTXCTXTPUSHELEMNAME (pctxt, "digits");

   ret = NASDec_TS24008IE_TBCDString (pctxt, &pvalue->digits, len - 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (len + 1);
}
