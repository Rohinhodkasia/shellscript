EXTERN int NASDec_TS24008IE_TFT (OSCTXT* pctxt, TS24008IE_TFT* pvalue)
{
   OSSIZE endIndex;
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "TFT");

   /* decode length */

   RTXCTXTPUSHELEMNAME (pctxt, "length");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxReadBytes (pctxt, &pvalue->length, 1);
   if (0 != ret) return LOG_RTERR (pctxt, ret);
   endIndex = pctxt->buffer.byteIndex + pvalue->length;

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   if (pctxt->buffer.byteIndex >= endIndex) return 0;

   /* decode octet1 */

   RTXCTXTPUSHELEMNAME (pctxt, "octet1");

   ret = NASDec_TS24008IE_TFTOctet1 (pctxt, &pvalue->octet1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   if (pctxt->buffer.byteIndex >= endIndex) return 0;

   /* decode packetFilterList */

   RTXCTXTPUSHELEMNAME (pctxt, "packetFilterList");

   /* Decode choice data value */

   switch (pvalue->octet1.tftOperationCode)
   {
      /* identifiers */
      case 5:
         RTXCTXTPUSHELEMNAME (pctxt, "identifiers");
         RTDIAG_NEWBITFIELD (pctxt, "OCTET STRING");

         pvalue->packetFilterList.u.identifiers.numocts = 
            pvalue->octet1.numPacketFilters;
         {
            OSOCTET *tmpdata = (OSOCTET*) rtxMemAlloc 
               (pctxt, pvalue->packetFilterList.u.identifiers.numocts);
           if (0 == tmpdata) return LOG_RTERR (pctxt, RTERR_NOMEM);

           ret = rtxReadBytes 
              (pctxt, tmpdata, pvalue->packetFilterList.u.identifiers.numocts);
           if (ret < 0) return LOG_RTERR (pctxt, ret);

           pvalue->packetFilterList.u.identifiers.data = tmpdata;
         }

         RTDIAG_SETBITFLDCOUNT (pctxt);
         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* filterItems */
      default: {
         OSUINT8 i;
         TS24008IE_TFTPacketFilterItem* pdata;

         RTXCTXTPUSHELEMNAME (pctxt, "filterItems");

         pvalue->packetFilterList.u.filterItems.n = 0;
         pvalue->packetFilterList.u.filterItems.elem =
            rtxMemAllocArray (pctxt, pvalue->octet1.numPacketFilters, 
                              TS24008IE_TFTPacketFilterItem);

         if (pvalue->packetFilterList.u.filterItems.elem == NULL)
            return LOG_RTERR (pctxt, RTERR_NOMEM);

         for (i = 0; i < pvalue->octet1.numPacketFilters; i++) {
            pdata = &pvalue->packetFilterList.u.filterItems.elem[i];
            asn1Init_TS24008IE_TFTPacketFilterItem (pdata);

            RTXCTXTPUSHARRAYELEMNAME (pctxt, "elem", i);

            ret = NASDec_TS24008IE_TFTPacketFilterItem (pctxt, pdata);
            if (ret < 0) return LOG_RTERR (pctxt, ret);

            RTXCTXTPOPARRAYELEMNAME (pctxt);

            pvalue->packetFilterList.u.filterItems.n++;
         }

         RTXCTXTPOPELEMNAME (pctxt);
         break;
      }
   }

   RTXCTXTPOPELEMNAME (pctxt);

   if (pctxt->buffer.byteIndex >= endIndex) return 0;

   /* decode paramList */

   RTXCTXTPUSHELEMNAME (pctxt, "paramList");
   {
      OSRTDList tmplist;
      TS24008IE_TFTParam* pdata;

      tmplist.head = tmplist.tail = (OSRTDListNode*) 0;
      tmplist.count = 0;

      while (pctxt->buffer.byteIndex < endIndex) {
         pdata = rtxMemAllocType (pctxt, TS24008IE_TFTParam);

         if (pdata == NULL)
            return LOG_RTERR (pctxt, RTERR_NOMEM);

         asn1Init_TS24008IE_TFTParam (pdata);

         RTXCTXTPUSHARRAYELEMNAME (pctxt, "elem", (OSUINT8)tmplist.count);

         ret = NASDec_TS24008IE_TFTParam (pctxt, pdata);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         if (0 == rtxDListAppend (pctxt, &tmplist, (void*)pdata)) {
            return LOG_RTERR (pctxt, RTERR_NOMEM);
         }

         RTXCTXTPOPARRAYELEMNAME (pctxt);

      }

      pvalue->paramList.n = (OSUINT8) tmplist.count;

      ret = rtxDListToArray (pctxt, &tmplist,
         (void**)&pvalue->paramList.elem, 0, sizeof(TS24008IE_TFTParam));

      rtxDListFreeAll (pctxt, &tmplist);

      if (ret < 0) return LOG_RTERR (pctxt, ret);
      else ret = 0;
   }

   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}
