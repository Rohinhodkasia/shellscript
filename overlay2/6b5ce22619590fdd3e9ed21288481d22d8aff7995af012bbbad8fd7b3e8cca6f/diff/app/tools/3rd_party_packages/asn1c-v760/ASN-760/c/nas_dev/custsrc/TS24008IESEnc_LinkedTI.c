EXTERN int NASEnc_TS24008IE_LinkedTI 
(OSCTXT* pctxt, TS24008IE_LinkedTI* pvalue)
{
   OSUINT8 len = (pvalue->value >= 7) ? 2 : 1;
   OSUINT8 tmpval;
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "LinkedTI");

   /* encode length */

   RTXCTXTPUSHELEMNAME (pctxt, "length");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncUInt32 (pctxt, len, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode flag */

   RTXCTXTPUSHELEMNAME (pctxt, "flag");
   RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

   ret = rtxEncBit (pctxt, pvalue->flag);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* If value is less than 7, it it encoded directly in 3 bit field
      here.  Otheriwse 7 is encoded, and value is encoded in next byte. */

   tmpval = OSRTMIN (pvalue->value, 7);
   RTXCTXTPUSHELEMNAME (pctxt, "value");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, tmpval, 3);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode spare */

   RTXCTXTPUSHELEMNAME (pctxt, "spare");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, 0, 4);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode extended value if >= 7 */

   if (pvalue->value >= 7) {
      RTXCTXTPUSHELEMNAME (pctxt, "ext");
      RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

      ret = rtxEncBit (pctxt, 1);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);
      RTXCTXTPOPELEMNAME (pctxt);

      /* encode value */

      RTXCTXTPUSHELEMNAME (pctxt, "value");
      if (!(pvalue->value <= OSUINTCONST(127))) {
         rtxErrAddElemNameParm (pctxt);
         rtxErrAddIntParm (pctxt, (int)pvalue->value);
         return LOG_RTERR (pctxt, RTERR_CONSVIO);
      }

      RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

      ret = rtxEncBits (pctxt, pvalue->value, 7);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);
      RTXCTXTPOPELEMNAME (pctxt);
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

