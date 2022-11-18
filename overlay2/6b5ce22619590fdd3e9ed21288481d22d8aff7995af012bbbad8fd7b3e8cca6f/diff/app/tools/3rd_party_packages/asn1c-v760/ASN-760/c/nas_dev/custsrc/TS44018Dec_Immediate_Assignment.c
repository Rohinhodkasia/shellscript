EXTERN int NASDec_TS44018Msg_ImmediateAssignment (OSCTXT* pctxt
   , TS44018Msg_ImmediateAssignment* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "ImmediateAssignment");

   OSCRTLMEMSET (&pvalue->m, 0, sizeof(pvalue->m));

   /* decode dedicatedModeOrTBF */

   RTXCTXTPUSHELEMNAME (pctxt, "dedicatedModeOrTBF");

   ret = NASDec_TS44018IE_Dedicated_mode_or_TBF (pctxt, &pvalue->
      dedicatedModeOrTBF);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode pageMode */

   RTXCTXTPUSHELEMNAME (pctxt, "pageMode");

   ret = NASDec_TS44018IE_Page_Mode (pctxt, &pvalue->pageMode);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   if ( pvalue->dedicatedModeOrTBF.tbf_or_dedicated == 0 ) 
   {
      /* dedicated mode - channelDescr shall be present */

      /* decode channelDescr */
      pvalue->m.channelDescrPresent = 1;
      RTXCTXTPUSHELEMNAME (pctxt, "channelDescr");
   
      ret = NASDec_TS44018IE_Channel_Description (pctxt, &pvalue->
         channelDescr);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTXCTXTPOPELEMNAME (pctxt);
   }
   else {
      /* TBF assignment.  packetChannelDescr is present */

      /* decode packetChannelDescr */
      pvalue->m.packetChannelDescrPresent = 1;
      RTXCTXTPUSHELEMNAME (pctxt, "packetChannelDescr");
   
      ret = NASDec_TS44018IE_Packet_Channel_Description (pctxt, &pvalue->
         packetChannelDescr);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTXCTXTPOPELEMNAME (pctxt);
   }


   /* decode requestReference */

   RTXCTXTPUSHELEMNAME (pctxt, "requestReference");

   ret = NASDec_TS44018IE_Request_Reference (pctxt, &pvalue->requestReference
      );
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode timingAdvance */

   RTXCTXTPUSHELEMNAME (pctxt, "timingAdvance");

   ret = NASDec_TS44018IE_Timing_Advance (pctxt, &pvalue->timingAdvance);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode mobileAllocation */

   RTXCTXTPUSHELEMNAME (pctxt, "mobileAllocation");

   ret = NASDec_TS44018IE_Mobile_Allocation (pctxt, &pvalue->mobileAllocation
      );
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   {
      int lastRow = 0;
      OSUINT8 iei, lastIEI = 0;

      while (rtxCtxtContainerHasRemBits(pctxt)) {
         OSUINT8 skipBytes = 0;
         OSBOOL comprReqd = FALSE;

         /* Decode IEI */
         RTDIAG_NEWBITFIELD (pctxt, "IEI");

         ret = rtxDecBitsToByte (pctxt, &iei, 8);
         if (ret == RTERR_ENDOFBUF) break;
         else if (0 != ret) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);

         switch (iei) {
            case 124: {
               if (lastRow == 0) {
                  /* decode startingTime */
                  RTXCTXTPUSHELEMNAME (pctxt, "startingTime");

                  ret = NASDec_TS44018IE_Starting_Time (pctxt, &pvalue->
                     startingTime);
                  if (ret < 0) return LOG_RTERR (pctxt, ret);
                  pvalue->m.startingTimePresent = 1;

                  lastRow = 1;

                  RTXCTXTPOPELEMNAME (pctxt);
               }
               else {
                  skipBytes = 2;
               }
               break;
            }
            default: {
               if (!(iei & 0x80)) {
                  ret = rtxDecBitsToByte (pctxt, &skipBytes, 8);
                  if (0 != ret) return LOG_RTERR (pctxt, ret);

                  comprReqd = (OSBOOL)((iei & 0x0F) == 0);
               }
            }
         }

         if (skipBytes != 0) {
            ret = rtxSkipBits (pctxt, skipBytes * 8);
            if (0 != ret) return LOG_RTERR (pctxt, ret);
         }

         if (comprReqd && iei != lastIEI) {
            rtxErrAddIntParm (pctxt, iei);
            LOG_RTERRNEW (pctxt, RTERR_UNKNOWNIE);
         }

         lastIEI = iei;
      }
   }
   ret = rtxErrGetStatus (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}