EXTERN int NASEnc_TS24008IE_PartySubaddress (OSCTXT* pctxt
   , TS24008IE_PartySubaddress* pvalue)
{
   int ret = 0;
   OSUINT8 length = pvalue->subaddrInfo.numocts + 1;

   RTXCTXTPUSHTYPENAME (pctxt, "PartySubaddress");

   /* encode length */

   RTDIAG_NEWBITFIELD (pctxt, "length");

   ret = rtxWriteBytes (pctxt, &length, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   /* encode ext */

   RTXCTXTPUSHELEMNAME (pctxt, "ext");
   RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

   ret = rtxEncBit (pctxt, pvalue->ext);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode typeOfSubaddr */

   RTXCTXTPUSHELEMNAME (pctxt, "typeOfSubaddr");
   if (pvalue->typeOfSubaddr <= 7) {
      RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

      ret = rtxEncBits (pctxt, pvalue->typeOfSubaddr, 3);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);
   }
   else {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddUIntParm (pctxt, pvalue->typeOfSubaddr);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode oddEvenIndicator */

   RTXCTXTPUSHELEMNAME (pctxt, "oddEvenIndicator");
   RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

   ret = rtxEncBit (pctxt, pvalue->oddEvenIndicator);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode spare */

   RTXCTXTPUSHELEMNAME (pctxt, "spare");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, pvalue->spare, 3);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode subaddrInfo */

   RTXCTXTPUSHELEMNAME (pctxt, "subaddrInfo");
   RTDIAG_NEWBITFIELD (pctxt, "OCTET STRING");

   if (pvalue->subaddrInfo.numocts > 20) {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddIntParm (pctxt, (int)pvalue->subaddrInfo.numocts);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }

   ret = rtxWriteBytes 
      (pctxt, pvalue->subaddrInfo.data, pvalue->subaddrInfo.numocts);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
