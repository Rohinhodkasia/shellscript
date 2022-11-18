static int NASDec_TS24301IE_IMSI_IMEI
(OSCTXT* pctxt, char* buffer, OSSIZE bufsize, OSOCTET digit1, OSSIZE numocts)
{
   OSOCTET ub, b;
   OSSIZE  i, j = 0;
   int ret;

   if (bufsize < (numocts * 2) + 1) {
      return LOG_RTERR (pctxt, RTERR_BUFOVFLW);
   }
   /* first digit is upper nibble decoded earlier */
   ret = rtxTBCDBinToChar (digit1, &buffer[j++]);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   for (i = 0; i < numocts; i++) {
      ret = rtxReadBytes (pctxt, &ub, 1);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      /* 1st digit is in lower nibble */
      b = ub & 0xF;
      ret = rtxTBCDBinToChar (b, &buffer[j++]);
      if (0 != ret) return LOG_RTERR (pctxt, ret);

      /* 2nd digit is in upper nibble */
      b = ub >> 4;
      ret = rtxTBCDBinToChar (b, &buffer[j++]);
      if (0 != ret) return LOG_RTERR (pctxt, ret);
   }

   buffer[j] = '\0';

   return 0;
}

EXTERN int NASDec_TS24301IE_EPSMobileIdentity (OSCTXT* pctxt
   , TS24301IE_EPSMobileIdentity* pvalue)
{
   OSSIZE endIndex;
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "EPSMobileIdentity");

   /* decode length */

   RTXCTXTPUSHELEMNAME (pctxt, "length");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->length, 8);
   if (0 != ret) return LOG_RTERR (pctxt, ret);
   endIndex = rtxCtxtGetBitOffset (pctxt) + (pvalue->length) * 8;

   ret = rtxCtxtPushContainerBytes(pctxt, pvalue->length);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* decode filler or identity digit 1 */

   if ( rtxCtxtContainerHasRemBits(pctxt) )  {
      RTXCTXTPUSHELEMNAME (pctxt, "filler");

      RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

      ret = rtxDecBitsToByte (pctxt, &pvalue->filler, 4);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);

      RTXCTXTPOPELEMNAME (pctxt);

   }
   if (rtxCtxtGetBitOffset(pctxt) > endIndex)
      return LOG_RTERR (pctxt, RTERR_INVLEN);

   /* decode oddEvenInd */

   RTXCTXTPUSHELEMNAME (pctxt, "oddEvenInd");

   RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

   ret = rtxDecBit (pctxt, &pvalue->oddEvenInd);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   if (rtxCtxtGetBitOffset(pctxt) > endIndex)
      return LOG_RTERR (pctxt, RTERR_INVLEN);

   /* decode typeOfIdent */

   RTXCTXTPUSHELEMNAME (pctxt, "typeOfIdent");

   ret = NASDec_TS24301IE_EPSMobileIdentity_typeOfIdent (pctxt, &pvalue->
      typeOfIdent);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   if (rtxCtxtGetBitOffset(pctxt) > endIndex)
      return LOG_RTERR (pctxt, RTERR_INVLEN);

   /* decode content */

   RTXCTXTPUSHELEMNAME (pctxt, "content");

   /* Decode choice data value */

   switch (pvalue->typeOfIdent)
   {
      /* guti */
      case 6:
         RTXCTXTPUSHELEMNAME (pctxt, "guti");

         ret = NASDec_TS24301IE_EPSMobileIdentity_GUTI (pctxt, &pvalue->content
            .u.guti);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* imsi */
      case 1:
         RTXCTXTPUSHELEMNAME (pctxt, "imsi");

         ret = NASDec_TS24301IE_IMSI_IMEI 
            (pctxt, pvalue->content.u.imsi, sizeof(pvalue->content.u.imsi), 
             pvalue->filler, pvalue->length-1);

         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* imei */
      case 3:
         RTXCTXTPUSHELEMNAME (pctxt, "imei");

         ret = NASDec_TS24301IE_IMSI_IMEI 
            (pctxt, pvalue->content.u.imei, sizeof(pvalue->content.u.imei), 
             pvalue->filler, pvalue->length-1);

         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      default:
         return LOG_RTERR (pctxt, RTERR_INVOPT);
   }

   RTXCTXTPOPELEMNAME (pctxt);

   if (rtxCtxtGetBitOffset(pctxt) > endIndex)
      return LOG_RTERR (pctxt, RTERR_INVLEN);

   rtxCtxtSetBitOffset(pctxt, endIndex);
   rtxCtxtPopContainer(pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
