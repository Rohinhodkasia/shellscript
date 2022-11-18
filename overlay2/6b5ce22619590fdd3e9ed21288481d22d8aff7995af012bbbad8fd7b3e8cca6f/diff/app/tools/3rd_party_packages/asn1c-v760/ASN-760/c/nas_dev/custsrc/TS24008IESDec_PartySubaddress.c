EXTERN int NASDec_TS24008IE_PartySubaddress (OSCTXT* pctxt
   , TS24008IE_PartySubaddress* pvalue)
{
   int ret = 0;
   OSUINT8 length;

   RTXCTXTPUSHTYPENAME (pctxt, "PartySubaddress");

   /* decode length */

   RTDIAG_NEWBITFIELD (pctxt, "length");

   ret = rtxReadBytes (pctxt, &length, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   if (0 == length) return 0;

   /* decode ext */

   RTXCTXTPUSHELEMNAME (pctxt, "ext");
   RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

   ret = rtxDecBit (pctxt, &pvalue->ext);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* decode typeOfSubaddr */

   RTXCTXTPUSHELEMNAME (pctxt, "typeOfSubaddr");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->typeOfSubaddr, 3);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* decode oddEvenIndicator */

   RTXCTXTPUSHELEMNAME (pctxt, "oddEvenIndicator");
   RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

   ret = rtxDecBit (pctxt, &pvalue->oddEvenIndicator);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* decode spare */

   RTXCTXTPUSHELEMNAME (pctxt, "spare");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->spare, 3);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   if (1 == length) return 0;

   /* decode subaddrInfo */

   RTXCTXTPUSHELEMNAME (pctxt, "subaddrInfo");
   RTDIAG_NEWBITFIELD (pctxt, "OCTET STRING");

   pvalue->subaddrInfo.numocts = length - 1;

   if (pvalue->subaddrInfo.numocts > 20) {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddIntParm (pctxt, (int)pvalue->subaddrInfo.numocts);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }

   ret = rtxReadBytes 
      (pctxt, pvalue->subaddrInfo.data, pvalue->subaddrInfo.numocts);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
