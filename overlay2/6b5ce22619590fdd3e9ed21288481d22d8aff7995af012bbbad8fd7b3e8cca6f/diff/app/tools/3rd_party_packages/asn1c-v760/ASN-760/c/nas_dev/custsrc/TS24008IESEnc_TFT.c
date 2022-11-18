EXTERN int NASEnc_TS24008IE_TFT (OSCTXT* pctxt, TS24008IE_TFT* pvalue)
{
   OSSIZE startIndex;
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "TFT");

   /* encode length */

   RTXCTXTPUSHELEMNAME (pctxt, "length");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncUInt32 (pctxt, 0, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);
   startIndex = pctxt->buffer.byteIndex;

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode octet1 */

   RTXCTXTPUSHELEMNAME (pctxt, "octet1");

   ret = NASEnc_TS24008IE_TFTOctet1 (pctxt, &pvalue->octet1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode packetFilterList */

   RTXCTXTPUSHELEMNAME (pctxt, "packetFilterList");

   switch (pvalue->octet1.tftOperationCode)
   {
      /* identifiers */
      case 5:
         RTXCTXTPUSHELEMNAME (pctxt, "identifiers");
         RTDIAG_NEWBITFIELD (pctxt, "OCTET STRING");

         /* set numocts to packet filter count */
         pvalue->packetFilterList.u.identifiers.numocts =
            pvalue->octet1.numPacketFilters;

         ret = rtxWriteBytes (pctxt, 
            pvalue->packetFilterList.u.identifiers.data, 
            pvalue->octet1.numPacketFilters);

         RTDIAG_SETBITFLDCOUNT (pctxt);
         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* filterItems */
      default:
         RTXCTXTPUSHELEMNAME (pctxt, "filterItems");
         pvalue->packetFilterList.u.filterItems.n = 
            pvalue->octet1.numPacketFilters;

         if (pvalue->octet1.numPacketFilters > 0) {
            OSUINT8 i;
            if (0 == pvalue->packetFilterList.u.filterItems.elem) {
               RTXCTXTPUSHELEMNAME (pctxt, "elem");
               rtxErrAddElemNameParm (pctxt);
               return LOG_RTERR(pctxt, RTERR_NULLPTR);
            }
            for (i = 0; i < pvalue->packetFilterList.u.filterItems.n; i++) {
               RTXCTXTPUSHARRAYELEMNAME (pctxt, "elem", i);

               ret = NASEnc_TS24008IE_TFTPacketFilterItem (pctxt, &pvalue->
                  packetFilterList.u.filterItems.elem[i]);
               if (ret < 0) return LOG_RTERR (pctxt, ret);

               RTXCTXTPOPARRAYELEMNAME (pctxt);
            }
         }

         RTXCTXTPOPELEMNAME (pctxt);
         break;

   }
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode paramList */

   RTXCTXTPUSHELEMNAME (pctxt, "paramList");
   {
      OSUINT8 i;
      for (i = 0; i < pvalue->paramList.n; i++) {
         RTXCTXTPUSHARRAYELEMNAME (pctxt, "elem", i);

         ret = NASEnc_TS24008IE_TFTParam (pctxt, &pvalue->paramList.elem[i]);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPARRAYELEMNAME (pctxt);
      }
   }

   RTXCTXTPOPELEMNAME (pctxt);

   pvalue->length = (OSUINT8) (pctxt->buffer.byteIndex - startIndex);
   pctxt->buffer.data[startIndex-1] = (OSUINT8) pvalue->length;
   if (0 == pvalue->length) {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddUIntParm (pctxt, pvalue->length);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
