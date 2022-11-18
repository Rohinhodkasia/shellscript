EXTERN int NASEnc_TS24501IE_RejectedNSSAI (OSCTXT* pctxt,
   TS24501IE_RejectedNSSAI* pvalue)
{
   int ret = 0;
   OSSIZE startIndex;

   RTXCTXTPUSHTYPENAME (pctxt, "RejectedNSSAI");

   /* encode length */

   RTXCTXTPUSHELEMNAME (pctxt, "length");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, 0, 4);
   if (ret < 0) return LOG_RTERR (pctxt, ret);
   startIndex = rtxCtxtGetBitOffset (pctxt);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode cause */

   RTXCTXTPUSHELEMNAME (pctxt, "cause");

   ret = NASEnc_TS24501IE_RejectedNSSAI_cause (pctxt, pvalue->cause);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode sst */

   RTXCTXTPUSHELEMNAME (pctxt, "sst");

   ret = NASEnc_TS24501IE_SST (pctxt, pvalue->sst);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode sd */

   RTXCTXTPUSHELEMNAME (pctxt, "sd");
   if (pvalue->m.sdPresent) {

      ret = NASEnc_TS24501IE_SD (pctxt, pvalue->sd);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

   }
   RTXCTXTPOPELEMNAME (pctxt);

   if (rtxCtxtTestFlag(pctxt, OSCONTCLOSED)) {
      if (!OSRTBYTEALIGNED(pctxt)) return LOG_RTERRNEW(pctxt, ASN_E_BAD_ALIGN);
      rtxCtxtClearFlag(pctxt, OSCONTCLOSED);
   }
   else {
      rtxByteAlign (pctxt);
   }

   {
      OSSIZE endIndex = rtxCtxtGetBitOffset (pctxt);
      pvalue->length = (OSUINT8)((endIndex - startIndex)/8);
      rtxCtxtSetBitOffset (pctxt, startIndex - 4);
      ret = rtxMergeBits (pctxt, pvalue->length, 4);
      if (ret < 0) return LOG_RTERR (pctxt, ret);
      rtxCtxtSetBitOffset (pctxt, endIndex);
   }

   if (!((pvalue->length >= 1 && pvalue->length <= 15))) {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddIntParm (pctxt, (int)pvalue->length);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

