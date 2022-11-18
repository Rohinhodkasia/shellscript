   /* decode receiveNPDUNumber */

   RTXCTXTPUSHELEMNAME (pctxt, "receiveNPDUNumber");

    {
      OSRTDList tmplist;
      TS24008IE_ReceiveNPDUNumber* pdata;

      tmplist.head = tmplist.tail = (OSRTDListNode*) 0;
      tmplist.count = 0;

      while ( rtxCtxtContainerHasRemBits(pctxt) ) {
         OSUINT8 sapi;
      
         ret = rtxDecBitsToByte(pctxt, &sapi, 4);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         if ( sapi == 0 ) break;    /* no more occurrences */
         else {
            /* backup 4 bits to re-read the sapi */
            ret = rtxMoveBitCursor(pctxt, -4);
            if (ret < 0) return LOG_RTERR (pctxt, ret);
         }

         pdata = rtxMemAllocTypeZ (pctxt, TS24008IE_ReceiveNPDUNumber);

         if (pdata == NULL)
            return LOG_RTERR (pctxt, RTERR_NOMEM);

         RTXCTXTPUSHARRAYELEMNAME (pctxt, "elem", (OSUINT8)tmplist.count);

         ret = NASDec_TS24008IE_ReceiveNPDUNumber (pctxt, pdata);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         if (0 == rtxDListAppend (pctxt, &tmplist, (void*)pdata)) {
            return LOG_RTERR (pctxt, RTERR_NOMEM);
         }

         RTXCTXTPOPARRAYELEMNAME (pctxt);

      }

      pvalue->receiveNPDUNumber.n = (OSUINT8) tmplist.count;

      ret = rtxDListToArray (pctxt, &tmplist,
         (void**)&pvalue->receiveNPDUNumber.elem, 0,
         sizeof(TS24008IE_ReceiveNPDUNumber));

      rtxDListFreeAll (pctxt, &tmplist);

      if (ret < 0) return LOG_RTERR (pctxt, ret);
      else ret = 0;
   }

   RTXCTXTPOPELEMNAME (pctxt);


