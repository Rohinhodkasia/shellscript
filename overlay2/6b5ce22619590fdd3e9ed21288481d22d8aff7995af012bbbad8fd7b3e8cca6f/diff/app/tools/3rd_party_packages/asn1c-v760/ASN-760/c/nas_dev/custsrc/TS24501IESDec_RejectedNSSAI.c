EXTERN int NASDec_TS24501IE_RejectedNSSAI (OSCTXT* pctxt,
   TS24501IE_RejectedNSSAI* pvalue)
{
   OSSIZE endIndex;
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "RejectedNSSAI");

   OSCRTLMEMSET (&pvalue->m, 0, sizeof(pvalue->m));

   /* decode length */

   RTXCTXTPUSHELEMNAME (pctxt, "length");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->length, 4);
   if (0 != ret) return LOG_RTERR (pctxt, ret);
   endIndex = rtxCtxtGetBitOffset (pctxt) + (pvalue->length) * 8;
   endIndex += 4; // Above calculation does not include 4-bit "cause" field...

   if (!((pvalue->length >= 1 && pvalue->length <= 15))) {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddIntParm (pctxt, (int)pvalue->length);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* decode cause */

   RTXCTXTPUSHELEMNAME (pctxt, "cause");

   ret = NASDec_TS24501IE_RejectedNSSAI_cause (pctxt, &pvalue->cause);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   ret = rtxCtxtPushContainerBytes(pctxt, pvalue->length);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   if (rtxCtxtGetBitOffset(pctxt) > endIndex)
      return LOG_RTERR (pctxt, RTERR_INVLEN);

   /* decode sst */

   RTXCTXTPUSHELEMNAME (pctxt, "sst");

   ret = NASDec_TS24501IE_SST (pctxt, &pvalue->sst);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   if (rtxCtxtGetBitOffset(pctxt) > endIndex)
      return LOG_RTERR (pctxt, RTERR_INVLEN);

   /* decode sd */

   if (rtxCtxtContainerHasRemBits(pctxt))  {
      RTXCTXTPUSHELEMNAME (pctxt, "sd");
      ret = NASDec_TS24501IE_SD (pctxt, &pvalue->sd);
      if (ret < 0) return LOG_RTERR (pctxt, ret);
      pvalue->m.sdPresent = 1;
      RTXCTXTPOPELEMNAME (pctxt);

   }
   if (rtxCtxtGetBitOffset(pctxt) > endIndex)
      return LOG_RTERR (pctxt, RTERR_INVLEN);

   rtxCtxtSetBitOffset(pctxt, endIndex);
   rtxCtxtPopContainer(pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

