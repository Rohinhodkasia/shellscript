/* encode length */
{
   OSUINT8 length = (pvalue->m.extPresent) ? 17 : 13;
   RTXCTXTPOPELEMNAME (pctxt);
   RTDIAG_NEWBITFIELD (pctxt, "length");

   ret = rtxWriteBytes (pctxt, &length, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
}

RTXCTXTPUSHELEMNAME (pctxt, "spare1");
RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

ret = rtxEncBits (pctxt, 0, 2);
if (ret < 0) return LOG_RTERR (pctxt, ret);

RTDIAG_SETBITFLDCOUNT (pctxt);
