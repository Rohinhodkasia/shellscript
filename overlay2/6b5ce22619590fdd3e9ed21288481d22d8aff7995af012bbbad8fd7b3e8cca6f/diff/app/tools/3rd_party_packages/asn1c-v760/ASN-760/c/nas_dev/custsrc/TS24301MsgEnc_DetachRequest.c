EXTERN int NASEnc_TS24301Msg_DetachRequest (OSCTXT* pctxt
   , TS24301Msg_DetachRequest* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "DetachRequest");

   /* Encode choice data value */

   switch (pvalue->t)
   {
      /* ueOrig */
      case 1:
         RTXCTXTPUSHELEMNAME (pctxt, "ueOrig");

         ret = NASEnc_TS24301Msg_DetachRequestUEOrig (pctxt, &pvalue->u.ueOrig
            );
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* ueTerm */
      case 2:
         RTXCTXTPUSHELEMNAME (pctxt, "ueTerm");

         ret = NASEnc_TS24301Msg_DetachRequestUETerm (pctxt, &pvalue->u.ueTerm
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
