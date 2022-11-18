/* Custom implementation */

EXTERN int NASEnc_TS24007L3_L3HdrOptions (OSCTXT* pctxt
   , TS24007L3_L3HdrOptions* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "L3HdrOptions");

   /* Encode choice data value */

   switch (pvalue->t)
   {
      /* skipInd */
      case T_TS24007L3_L3HdrOptions_skipInd:
         RTXCTXTPUSHELEMNAME (pctxt, "skipInd");

         if (pvalue->u.skipInd <= 15) {
            RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

            ret = rtxEncBits (pctxt, pvalue->u.skipInd, 4);
            if (ret < 0) return LOG_RTERR (pctxt, ret);

            RTDIAG_SETBITFLDCOUNT (pctxt);
         }
         else {
            rtxErrAddElemNameParm (pctxt);
            rtxErrAddUIntParm (pctxt, pvalue->u.skipInd);
            return LOG_RTERR (pctxt, RTERR_CONSVIO);
         }

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* transId */
      case T_TS24007L3_L3HdrOptions_transId: {
         OSUINT8 transId = OSRTMIN (pvalue->u.transId.value, 7);
         RTXCTXTPUSHELEMNAME (pctxt, "transId");

         /* encode flag */

         RTXCTXTPUSHELEMNAME (pctxt, "flag");
         RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

         ret = rtxEncBit (pctxt, pvalue->u.transId.flag);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);
         RTXCTXTPOPELEMNAME (pctxt);

         /* encode value */

         RTXCTXTPUSHELEMNAME (pctxt, "value");
         RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

         ret = rtxEncBits (pctxt, transId, 3);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);
         RTXCTXTPOPELEMNAME (pctxt);

         RTXCTXTPOPELEMNAME (pctxt);
         break;
      }

      /* epsBearerIdent */
      case T_TS24007L3_L3HdrOptions_epsBearerIdent:
         RTXCTXTPUSHELEMNAME (pctxt, "epsBearerIdent");

         ret = NASEnc_TS24007L3_EPSBearerIdentity (pctxt, pvalue->
            u.epsBearerIdent);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* skipInd */
      case T_TS24007L3_L3HdrOptions_secHdr:
         RTXCTXTPUSHELEMNAME (pctxt, "secHdr");

         if (pvalue->u.skipInd <= 15) {
            RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

            ret = rtxEncBits (pctxt, pvalue->u.secHdr, 4);
            if (ret < 0) return LOG_RTERR (pctxt, ret);

            RTDIAG_SETBITFLDCOUNT (pctxt);
         }
         else {
            rtxErrAddElemNameParm (pctxt);
            rtxErrAddUIntParm (pctxt, pvalue->u.secHdr);
            return LOG_RTERR (pctxt, RTERR_CONSVIO);
         }

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      default:
         return LOG_RTERR (pctxt, RTERR_INVOPT);
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
