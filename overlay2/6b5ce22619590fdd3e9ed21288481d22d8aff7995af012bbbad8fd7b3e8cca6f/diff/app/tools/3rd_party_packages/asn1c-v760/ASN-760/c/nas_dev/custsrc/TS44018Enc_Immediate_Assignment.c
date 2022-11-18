EXTERN int NASEnc_TS44018Msg_ImmediateAssignment (OSCTXT* pctxt
   , TS44018Msg_ImmediateAssignment* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "ImmediateAssignment");

   /* encode dedicatedModeOrTBF */

   RTXCTXTPUSHELEMNAME (pctxt, "dedicatedModeOrTBF");

   ret = NASEnc_TS44018IE_Dedicated_mode_or_TBF (pctxt, &pvalue->
      dedicatedModeOrTBF);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode pageMode */

   RTXCTXTPUSHELEMNAME (pctxt, "pageMode");

   ret = NASEnc_TS44018IE_Page_Mode (pctxt, &pvalue->pageMode);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   if ( pvalue->dedicatedModeOrTBF.tbf_or_dedicated == 0 ) 
   {
      /* dedicated mode - channelDescr shall be present */
      /* encode channelDescr */

      RTXCTXTPUSHELEMNAME (pctxt, "channelDescr");

      ret = NASEnc_TS44018IE_Channel_Description (pctxt, &pvalue->channelDescr
         );
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTXCTXTPOPELEMNAME (pctxt);
   }
   else {
      /* TBF assignment.  packetChannelDescr is present */

      RTXCTXTPUSHELEMNAME (pctxt, "packetChannelDescr");

      ret = NASEnc_TS44018IE_Packet_Channel_Description (pctxt, &pvalue->
         packetChannelDescr);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTXCTXTPOPELEMNAME (pctxt);
   }

   /* encode requestReference */

   RTXCTXTPUSHELEMNAME (pctxt, "requestReference");

   ret = NASEnc_TS44018IE_Request_Reference (pctxt, &pvalue->requestReference
      );
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode timingAdvance */

   RTXCTXTPUSHELEMNAME (pctxt, "timingAdvance");

   ret = NASEnc_TS44018IE_Timing_Advance (pctxt, pvalue->timingAdvance);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode mobileAllocation */

   RTXCTXTPUSHELEMNAME (pctxt, "mobileAllocation");

   ret = NASEnc_TS44018IE_Mobile_Allocation (pctxt, &pvalue->mobileAllocation
      );
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode startingTime */

   RTXCTXTPUSHELEMNAME (pctxt, "startingTime");
   if (pvalue->m.startingTimePresent) {
      if (!OSRTBYTEALIGNED(pctxt)) {
         return LOG_RTERR (pctxt, RTERR_NOTALIGNED);
      }
      RTDIAG_NEWBITFIELD (pctxt, "iei");

      ret = rtxEncBits (pctxt, 0x7c, 8);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);

      ret = NASEnc_TS44018IE_Starting_Time (pctxt, &pvalue->startingTime);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

   }
   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}