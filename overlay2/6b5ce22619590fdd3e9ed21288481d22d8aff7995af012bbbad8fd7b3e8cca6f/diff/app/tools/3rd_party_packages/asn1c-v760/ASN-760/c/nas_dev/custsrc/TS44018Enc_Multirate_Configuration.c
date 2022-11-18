EXTERN int NASEnc_TS44018IE_Multirate_Configuration (OSCTXT* pctxt
   , TS44018IE_Multirate_Configuration* pvalue)
{
   OSSIZE startIndex;
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "Multirate-Configuration");

   /* encode length */

   RTXCTXTPUSHELEMNAME (pctxt, "length");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, 0, 8);
   if (ret < 0) return LOG_RTERR (pctxt, ret);
   startIndex = rtxCtxtGetBitOffset (pctxt);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode multirate-speech-version */

   RTXCTXTPUSHELEMNAME (pctxt, "multirate-speech-version");

   ret = NASEnc_TS44018IE_Multirate_Configuration_multirate_speech_version (pctxt, 
      pvalue->multirate_speech_version);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode nscb */

   RTXCTXTPUSHELEMNAME (pctxt, "nscb");
   if (!((pvalue->nscb <= OSUINTCONST(1)))) {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddIntParm (pctxt, (int)pvalue->nscb);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, pvalue->nscb, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode icmi */

   RTXCTXTPUSHELEMNAME (pctxt, "icmi");
   if (!((pvalue->icmi <= OSUINTCONST(1)))) {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddIntParm (pctxt, (int)pvalue->icmi);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, pvalue->icmi, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode spare */

   RTXCTXTPUSHELEMNAME (pctxt, "spare");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, 0, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode start-mode */

   RTXCTXTPUSHELEMNAME (pctxt, "start-mode");
   if (!((pvalue->start_mode <= OSUINTCONST(3)))) {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddIntParm (pctxt, (int)pvalue->start_mode);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, pvalue->start_mode, 2);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode amr-codec-modes */

   RTXCTXTPUSHELEMNAME (pctxt, "amr-codec-modes");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncUInt32 (pctxt, pvalue->amr_codec_modes, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode params */

   RTXCTXTPUSHELEMNAME (pctxt, "params");
   {
      OSUINT8 i;
      if (!(pvalue->params.n <= 3)) {
         rtxErrAddElemNameParm (pctxt);
         rtxErrAddIntParm (pctxt, (int)pvalue->params.n);
         return LOG_RTERR (pctxt, RTERR_CONSVIO);
      }

      for (i = 0; i < pvalue->params.n; i++) {
         RTXCTXTPUSHARRAYELEMNAME (pctxt, "elem", i);
         /* encode threshold */

         RTXCTXTPUSHELEMNAME (pctxt, "threshold");
         if (!((pvalue->params.elem[i].threshold <= OSUINTCONST(63)))) {
            rtxErrAddElemNameParm (pctxt);
            rtxErrAddIntParm (pctxt, (int)pvalue->params.elem[i].threshold);
            return LOG_RTERR (pctxt, RTERR_CONSVIO);
         }

         RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

         ret = rtxEncBits (pctxt, pvalue->params.elem[i].threshold, 6);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);
         RTXCTXTPOPELEMNAME (pctxt);

         /* encode hysteresis */

         RTXCTXTPUSHELEMNAME (pctxt, "hysteresis");
         if (!((pvalue->params.elem[i].hysteresis <= OSUINTCONST(15)))) {
            rtxErrAddElemNameParm (pctxt);
            rtxErrAddIntParm (pctxt, (int)pvalue->params.elem[i].hysteresis);
            return LOG_RTERR (pctxt, RTERR_CONSVIO);
         }

         RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

         ret = rtxEncBits (pctxt, pvalue->params.elem[i].hysteresis, 4);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);
         RTXCTXTPOPELEMNAME (pctxt);

         RTXCTXTPOPARRAYELEMNAME (pctxt);
      }
   }

   RTXCTXTPOPELEMNAME (pctxt);

   rtxByteAlign (pctxt);

   {
      OSSIZE endIndex = rtxCtxtGetBitOffset (pctxt);
      rtxCtxtSetBitOffset (pctxt, startIndex - 8);
      ret = rtxMergeBits (pctxt, (OSUINT8)(endIndex - startIndex)/8, 8);
      if (ret < 0) return LOG_RTERR (pctxt, ret);
      rtxCtxtSetBitOffset (pctxt, endIndex);
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}