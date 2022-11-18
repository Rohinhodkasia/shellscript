{
   RTXCTXTPUSHELEMNAME (pctxt, "l3HdrOpts");

   /* Only skip indicator is decoded at this time.  The t value will be 
      set later after protocol discriminator is decoded. */

   RTXCTXTPUSHELEMNAME (pctxt, "skipInd");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->l3HdrOpts.u.skipInd, 4);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);
}
