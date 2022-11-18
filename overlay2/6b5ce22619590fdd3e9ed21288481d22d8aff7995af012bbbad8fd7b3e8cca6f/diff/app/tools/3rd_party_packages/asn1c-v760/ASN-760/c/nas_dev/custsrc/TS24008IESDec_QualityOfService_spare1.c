/* decode length */
{
   OSUINT8 length;

   RTXCTXTPOPELEMNAME (pctxt);
   RTDIAG_NEWBITFIELD (pctxt, "length");

   ret = rtxReadBytes (pctxt, &length, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);
   else if (length == 13) {
      pvalue->m.extPresent = 0;
   }
   else if (length == 17) {
      pvalue->m.extPresent = 1;
   }
   else  return LOG_RTERR (pctxt, RTERR_INVLEN);

   RTDIAG_SETBITFLDCOUNT (pctxt);
} 
/* decode spare1 */

RTXCTXTPUSHELEMNAME (pctxt, "spare1");
RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

ret = rtxDecBitsToByte (pctxt, &pvalue->spare1, 2);
if (ret < 0) return LOG_RTERR (pctxt, ret);

RTDIAG_SETBITFLDCOUNT (pctxt);
