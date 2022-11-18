EXTERN int NASDec_TS24007L3_L3HdrOptions (OSCTXT* pctxt
   , TS24007L3_L3HdrOptions* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "L3HdrOptions");

   /* Only skip indicator is decoded at this time.  The t value will be 
      set later after protocol discriminator is decoded. */

   RTXCTXTPUSHELEMNAME (pctxt, "skipInd");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   pvalue->t = 1;

   ret = rtxDecBitsToByte (pctxt, &pvalue->u.skipInd, 4);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
