{
   OSUINT8 transId = OSRTMIN (pvalue->l3HdrOpts.u.transId.value, 7);
   RTXCTXTPUSHELEMNAME (pctxt, "value");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, transId, 3);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);
}
