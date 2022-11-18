{
   OSUINT32 tmpval = pvalue->msgType;

   if ((pvalue->protoDiscr == TS24007L3_ProtoDiscr_callCtrl ||
        pvalue->protoDiscr == TS24007L3_ProtoDiscr_mobMgmt))
   {
      if (pvalue->l3HdrOpts.u.transId.value >= 7) {

         /* encode transId.value */

         RTXCTXTPUSHELEMNAME (pctxt, "transId.value");
         RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

         ret = rtxEncUInt32 (pctxt, pvalue->l3HdrOpts.u.transId.value, 1);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);
         RTXCTXTPOPELEMNAME (pctxt);
      }

      /* for MM and CC messages, sendSeqNum is encoded in first 2 bits of 
        message type */
      if (pvalue->m.sendSeqNumPresent) {
         tmpval |= (pvalue->sendSeqNum << 6);
      }
   }

   /* encode msgType */

   RTXCTXTPUSHELEMNAME (pctxt, "msgType");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncUInt32 (pctxt, tmpval, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);
}
