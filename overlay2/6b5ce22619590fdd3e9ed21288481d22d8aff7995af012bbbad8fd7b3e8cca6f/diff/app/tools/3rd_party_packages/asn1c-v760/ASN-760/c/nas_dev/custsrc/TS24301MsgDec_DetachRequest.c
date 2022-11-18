EXTERN int NASDec_TS24301Msg_DetachRequest (OSCTXT* pctxt
   , TS24301Msg_DetachRequest* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "DetachRequest");

   /* The OS3GMOBORIG flag is checked in the context to determine if 
      this is a mobile-originated message.  The user must set this 
      explicitly before calling the decode PDU function. */

   pvalue->t = (rtxCtxtTestFlag (pctxt, OS3GMOBORIG)) ?
      1 /* UE (mobile) originated */ : 2 /* network originated */ ;

   /* Decode choice data value */

   switch (pvalue->t)
   {
      /* ueOrig */
      case 1:
         RTXCTXTPUSHELEMNAME (pctxt, "ueOrig");

         ret = NASDec_TS24301Msg_DetachRequestUEOrig (pctxt, &pvalue->u.ueOrig
            );
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* ueTerm */
      case 2:
         RTXCTXTPUSHELEMNAME (pctxt, "ueTerm");

         ret = NASDec_TS24301Msg_DetachRequestUETerm (pctxt, &pvalue->u.ueTerm
            );
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      default:
         return LOG_RTERR (pctxt, RTERR_INVOPT);
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
