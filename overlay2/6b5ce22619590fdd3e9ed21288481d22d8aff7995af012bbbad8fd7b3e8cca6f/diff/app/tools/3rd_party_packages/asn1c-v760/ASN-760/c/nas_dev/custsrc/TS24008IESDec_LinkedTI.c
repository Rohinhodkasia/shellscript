EXTERN int NASDec_TS24008IE_LinkedTI 
(OSCTXT* pctxt, TS24008IE_LinkedTI* pvalue)
{
   OSUINT8 len, tmpval;
   OSBOOL  ext;
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "LinkedTI");

   /* decode length */

   RTXCTXTPUSHELEMNAME (pctxt, "length");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxReadBytes (pctxt, &len, 1);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   if (len == 0 || len > 2)
      return LOG_RTERR (pctxt, RTERR_INVLEN);

   /* decode flag */

   RTXCTXTPUSHELEMNAME (pctxt, "flag");

   RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

   ret = rtxDecBit (pctxt, &pvalue->flag);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* decode value */

   RTXCTXTPUSHELEMNAME (pctxt, "value");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &tmpval, 3);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   if (len == 1) pvalue->value = tmpval;
   else if (tmpval != 7) 
      return LOG_RTERR (pctxt, RTERR_BADVALUE);

   /* skip spare bits */

   RTXCTXTPUSHELEMNAME (pctxt, "spare");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxSkipBits (pctxt, 4);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   if (len == 1) return 0;

   /* decode ext bit */

   RTXCTXTPUSHELEMNAME (pctxt, "ext");
   RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

   ret = rtxDecBit (pctxt, &ext);
   if (ret < 0) return LOG_RTERR (pctxt, ret);
   else if (ext != TRUE) 
      return LOG_RTERR (pctxt, RTERR_BADVALUE);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* decode value */

   RTXCTXTPUSHELEMNAME (pctxt, "value");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->value, 7);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
