EXTERN int NASEnc_TS24301IE_EPSMobileIdentity (OSCTXT* pctxt
   , TS24301IE_EPSMobileIdentity* pvalue)
{
   OSSIZE startIndex;
   OSOCTET filler;
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "EPSMobileIdentity");

   /* encode length */

   RTXCTXTPUSHELEMNAME (pctxt, "length");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, 0, 8);
   if (ret < 0) return LOG_RTERR (pctxt, ret);
   startIndex = rtxCtxtGetBitOffset (pctxt);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode filler or first digit of IMSI/IMEI */

   switch (pvalue->typeOfIdent)
   {
      /* guti */
      case 6:
         RTXCTXTPUSHELEMNAME (pctxt, "filler");
         filler = 0x0f;
         break;

      /* imsi */
      case 1:
         RTXCTXTPUSHELEMNAME (pctxt, "imsi[0]");
         ret = rtxTBCDCharToBin (pvalue->content.u.imsi[0], &filler);
         if (ret < 0) return LOG_RTERR (pctxt, ret);
         break;

      /* imei */
      case 3:
         RTXCTXTPUSHELEMNAME (pctxt, "imei[0]");
         ret = rtxTBCDCharToBin (pvalue->content.u.imei[0], &filler);
         if (ret < 0) return LOG_RTERR (pctxt, ret);
         break;

      default:
         return LOG_RTERR (pctxt, RTERR_INVOPT);
   }
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, filler, 4);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode oddEvenInd */

   RTXCTXTPUSHELEMNAME (pctxt, "oddEvenInd");
   RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

   ret = rtxEncBit (pctxt, pvalue->oddEvenInd);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode typeOfIdent */

   RTXCTXTPUSHELEMNAME (pctxt, "typeOfIdent");

   ret = NASEnc_TS24301IE_EPSMobileIdentity_typeOfIdent (pctxt, pvalue->
      typeOfIdent);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode content */

   RTXCTXTPUSHELEMNAME (pctxt, "content");
   /* Encode choice data value */

   switch (pvalue->typeOfIdent)
   {
      /* guti */
      case 6:
         RTXCTXTPUSHELEMNAME (pctxt, "guti");

         ret = NASEnc_TS24301IE_EPSMobileIdentity_GUTI 
            (pctxt, &pvalue->content.u.guti);

         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* imsi */
      case 1:
         RTXCTXTPUSHELEMNAME (pctxt, "imsi");

         ret = NASEnc_TS24008IE_IMSI (pctxt, &pvalue->content.u.imsi[1]);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* imei */
      case 3:
         RTXCTXTPUSHELEMNAME (pctxt, "imei");

         ret = NASEnc_TS24008IE_IMEI (pctxt, &pvalue->content.u.imei[1]);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      default:
         return LOG_RTERR (pctxt, RTERR_INVOPT);
   }
   RTXCTXTPOPELEMNAME (pctxt);

   if(rtxCtxtTestFlag(pctxt, OSCONTCLOSED)){
      if(!OSRTBYTEALIGNED(pctxt)) return LOG_RTERRNEW(pctxt, ASN_E_BAD_ALIGN);
      rtxCtxtClearFlag(pctxt, OSCONTCLOSED);
   }
   else  {
      rtxByteAlign (pctxt);
   }
   {
      OSSIZE endIndex = rtxCtxtGetBitOffset (pctxt);
      pvalue->length = (OSUINT8)((endIndex - startIndex)/8);
      rtxCtxtSetBitOffset (pctxt, startIndex - 8);
      ret = rtxMergeBits (pctxt, pvalue->length, 8);
      if (ret < 0) return LOG_RTERR (pctxt, ret);
      rtxCtxtSetBitOffset (pctxt, endIndex);
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
