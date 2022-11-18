/* Custom decode function (TS24008MsgDec_DetachAccept.c) */

EXTERN int NASDec_TS24008Msg_DetachAccept (OSCTXT* pctxt
   , TS24008Msg_DetachAccept* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "DetachAccept");

   OSCRTLMEMSET (&pvalue->m, 0, sizeof(pvalue->m));

   /* The OS3GMOBORIG flag is checked in the context to determine if 
      this is a mobile-originated message.  The user must set this 
      explicitly before calling the decode PDU function. */

   if (rtxCtxtTestFlag (pctxt, OS3GMOBORIG)) {
      /* 3G originated, forceToStandby flag should be present */
      RTXCTXTPUSHELEMNAME (pctxt, "forceToStandby");

      /* skip spare bits */
      ret = rtxSkipBits (pctxt, 4);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      /* decode IE value */
      ret = NASDec_TS24008IE_ForceToStandbyValue (pctxt, &pvalue->
         forceToStandby);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      pvalue->m.forceToStandbyPresent = 1;

      RTXCTXTPOPELEMNAME (pctxt);
   }

   ret = rtx3GPPDecL3NonImperative (pctxt, FALSE);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
