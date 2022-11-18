EXTERN int NASDec_TS44018IE_Multirate_Configuration (OSCTXT* pctxt
   , TS44018IE_Multirate_Configuration* pvalue)
{
   OSSIZE endIndex;
   OSUINT8 length;
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "Multirate_Configuration");

   /* decode length */

   RTXCTXTPUSHELEMNAME (pctxt, "length");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &length, 8);
   if (0 != ret) return LOG_RTERR (pctxt, ret);
   endIndex = rtxCtxtGetBitOffset (pctxt) + length * 8;

   ret = rtxCtxtPushContainerBytes(pctxt, length);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   if (rtxCtxtGetBitOffset(pctxt) == endIndex) { rtxCtxtPopContainer(pctxt); return 0; }
   if (rtxCtxtGetBitOffset(pctxt) > endIndex)
      return LOG_RTERR (pctxt, RTERR_INVLEN);

   /* decode multirate-speech-version */

   RTXCTXTPUSHELEMNAME (pctxt, "multirate-speech-version");

   ret = NASDec_TS44018IE_Multirate_Configuration_multirate_speech_version (pctxt, 
      &pvalue->multirate_speech_version);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   if (rtxCtxtGetBitOffset(pctxt) == endIndex) { rtxCtxtPopContainer(pctxt); return 0; }
   if (rtxCtxtGetBitOffset(pctxt) > endIndex)
      return LOG_RTERR (pctxt, RTERR_INVLEN);

   /* decode nscb */

   RTXCTXTPUSHELEMNAME (pctxt, "nscb");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->nscb, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   if (rtxCtxtGetBitOffset(pctxt) == endIndex) { rtxCtxtPopContainer(pctxt); return 0; }
   if (rtxCtxtGetBitOffset(pctxt) > endIndex)
      return LOG_RTERR (pctxt, RTERR_INVLEN);

   /* decode icmi */

   RTXCTXTPUSHELEMNAME (pctxt, "icmi");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->icmi, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   if (rtxCtxtGetBitOffset(pctxt) == endIndex) { rtxCtxtPopContainer(pctxt); return 0; }
   if (rtxCtxtGetBitOffset(pctxt) > endIndex)
      return LOG_RTERR (pctxt, RTERR_INVLEN);

   /* decode spare */

   RTXCTXTPUSHELEMNAME (pctxt, "spare");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxSkipBits(pctxt, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   if (rtxCtxtGetBitOffset(pctxt) == endIndex) { rtxCtxtPopContainer(pctxt); return 0; }
   if (rtxCtxtGetBitOffset(pctxt) > endIndex)
      return LOG_RTERR (pctxt, RTERR_INVLEN);

   /* decode start-mode */

   RTXCTXTPUSHELEMNAME (pctxt, "start-mode");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->start_mode, 2);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   if (rtxCtxtGetBitOffset(pctxt) == endIndex) { rtxCtxtPopContainer(pctxt); return 0; }
   if (rtxCtxtGetBitOffset(pctxt) > endIndex)
      return LOG_RTERR (pctxt, RTERR_INVLEN);

   /* decode amr-codec-modes */

   RTXCTXTPUSHELEMNAME (pctxt, "amr-codec-modes");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->amr_codec_modes, 8);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   if (rtxCtxtGetBitOffset(pctxt) == endIndex) { rtxCtxtPopContainer(pctxt); return 0; }
   if (rtxCtxtGetBitOffset(pctxt) > endIndex)
      return LOG_RTERR (pctxt, RTERR_INVLEN);

   /* decode params */   

   RTXCTXTPUSHELEMNAME (pctxt, "params");

   {
      OSUINT8 i;
      OSUINT8 modes = pvalue->amr_codec_modes;
      OSUINT8 numModes = 0;

      /* count how many modes are specified in amr_code_modes (i.e., how many
         bits are set). There should be 1 - 4 modes */
      while(modes != 0 ) 
      {
         if ( modes % 2 ) numModes++;
         modes = modes >> 1;
      }
      if ( numModes > 4 ) numModes = 4;   /* shouldn't be more than 4 */
      
      /* there are numModes - 1 repetitions of the params */
      for (i = 0; i < numModes - 1; i++) {
         RTXCTXTPUSHARRAYELEMNAME (pctxt, "elem", i);

         /* decode threshold */

         RTXCTXTPUSHELEMNAME (pctxt, "threshold");

         RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

         ret = rtxDecBitsToByte (pctxt, &pvalue->params.elem[i].threshold, 6);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);

         RTXCTXTPOPELEMNAME (pctxt);

         /* decode hysteresis */

         RTXCTXTPUSHELEMNAME (pctxt, "hysteresis");

         RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

         ret = rtxDecBitsToByte (pctxt, &pvalue->params.elem[i].hysteresis, 4);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);

         RTXCTXTPOPELEMNAME (pctxt);

         RTXCTXTPOPARRAYELEMNAME (pctxt);

      }
      pvalue->params.n = i;
   }
   if (!(pvalue->params.n <= 3)) {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddIntParm (pctxt, (int)pvalue->params.n);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }

   RTXCTXTPOPELEMNAME (pctxt);

   if (rtxCtxtGetBitOffset(pctxt) > endIndex)
      return LOG_RTERR (pctxt, RTERR_INVLEN);

   rtxCtxtSetBitOffset(pctxt, endIndex);
   rtxCtxtPopContainer(pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}