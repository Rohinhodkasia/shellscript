/* Custom encode function (TS24008MsgEnc_DetachAccept.c) */

EXTERN int NASEnc_TS24008Msg_DetachAccept (OSCTXT* pctxt
   , TS24008Msg_DetachAccept* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "DetachAccept");

   /* encode forceToStandby (this should only be done in mobile originating 
      direction) */

   if (pvalue->m.forceToStandbyPresent) {
      RTXCTXTPUSHELEMNAME (pctxt, "forceToStandby");

      /* encode spare bits */
      ret = rtxEncBits (pctxt, 0, 4);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      /* encode value */
      ret = NASEnc_TS24008IE_ForceToStandbyValue (pctxt, &pvalue->
         forceToStandby);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTXCTXTPOPELEMNAME (pctxt);
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
