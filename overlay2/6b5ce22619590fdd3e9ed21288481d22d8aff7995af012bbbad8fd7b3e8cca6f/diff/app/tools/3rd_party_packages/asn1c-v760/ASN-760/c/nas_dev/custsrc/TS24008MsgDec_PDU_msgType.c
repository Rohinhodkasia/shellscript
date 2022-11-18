{
   if (pvalue->protoDiscr == TS24007L3_ProtoDiscr_callCtrl ||
       pvalue->protoDiscr == TS24007L3_ProtoDiscr_sessMgmt) 
   {
      OSUINT8 tmpval = pvalue->l3HdrOpts.u.skipInd;

      pvalue->l3HdrOpts.u.transId.flag = (OSBOOL)((tmpval & 0x08) != 0);

      if ((tmpval & 0x07) == 7) {
         RTXCTXTPUSHELEMNAME (pctxt, "transId");
         RTDIAG_NEWBITFIELD (pctxt, "flag");

         ret = rtxSkipBits (pctxt, 1);
         if (0 != ret) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);

         RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

         ret = rtxDecBitsToByte 
            (pctxt, &pvalue->l3HdrOpts.u.transId.value, 7);
         if (0 != ret) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);
         RTXCTXTPOPELEMNAME (pctxt);
      }
      else {
         pvalue->l3HdrOpts.u.transId.value = tmpval & 0x07;
      }
   }

   RTXCTXTPUSHELEMNAME (pctxt, "msgType");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->msgType, 8);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* for callCtrl or mobMgmt, sendSeqNum is stored in upper 2 bits 
      of msgType */

   if (pvalue->protoDiscr == TS24007L3_ProtoDiscr_callCtrl ||
       pvalue->protoDiscr == TS24007L3_ProtoDiscr_mobMgmt)
   {
      pvalue->sendSeqNum = (pvalue->msgType & 0xC0) >> 6;
      pvalue->m.sendSeqNumPresent = (pvalue->sendSeqNum != 0);

      pvalue->msgType &= 0x3F;
   }
}
