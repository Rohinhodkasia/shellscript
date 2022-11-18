EXTERN int NASEnc_TS24011IE_RPAddress (OSCTXT* pctxt
   , TS24011IE_RPAddress* pvalue)
{
   OSUINT8 length = 1;
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "RPAddress");

   /* Calculate length */
   if (0 != pvalue->number) {
      OSSIZE slen = OSCRTLSTRLEN (pvalue->number);
      length += slen / 2;
      if (0 != (slen % 2)) length++;
   }

   if (1 == length || length > 11) return LOG_RTERR (pctxt, RTERR_INVLEN);

   /* Encode length */
   RTDIAG_NEWBITFIELD (pctxt, "length");

   ret = rtxWriteBytes (pctxt, &length, 1);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   if (0 == length) return 0;

   /* Encode octet 3 */
   /* encode ext */

   RTXCTXTPUSHELEMNAME (pctxt, "ext");
   RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

   ret = rtxEncBit (pctxt, pvalue->ext);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode typeOfNumber */

   RTXCTXTPUSHELEMNAME (pctxt, "typeOfNumber");
   if (pvalue->typeOfNumber <= 7) {
      RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

      ret = rtxEncBits (pctxt, pvalue->typeOfNumber, 3);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);
   }
   else {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddUIntParm (pctxt, pvalue->typeOfNumber);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode numberingPlanID */

   RTXCTXTPUSHELEMNAME (pctxt, "numberingPlanID");
   if (pvalue->numberingPlanID <= 15) {
      RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

      ret = rtxEncBits (pctxt, pvalue->numberingPlanID, 4);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);
   }
   else {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddUIntParm (pctxt, pvalue->numberingPlanID);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode number */

   RTXCTXTPUSHELEMNAME (pctxt, "number");

   ret = NASEnc_TS24011IE_TBCDString (pctxt, pvalue->number);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
