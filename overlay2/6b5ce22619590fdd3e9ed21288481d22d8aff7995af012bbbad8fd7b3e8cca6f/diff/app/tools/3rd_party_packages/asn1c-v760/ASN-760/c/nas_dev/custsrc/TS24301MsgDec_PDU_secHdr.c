/* start custom code */
{
   OSRTBufSave savedBuf;
   OSOCTET ub, pd;

   rtxDiagSetBitFldDisabled (pctxt->pBitFldList, TRUE);
   OSRTBUFSAVE2 (pctxt, &savedBuf);

   /* decode security header type */
   ret = rtxDecBitsToByte (pctxt, &ub, 4);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   /* check for SERVICE REQUEST message */
   if (ub >= 12) {
      /* service request message usess short mac, calculated on the first
         two octets of the message */
      OSUINT32 mac;
      int computeMACRet;
   
      ret = computeMACRet = rtx3gppComputeMAC(pctxt, pctxt->buffer.data + savedBuf.byteIndex,
         2 /*length*/, &mac);
      if (ret < 0) LOG_RTERR (pctxt, ret);
   
      pvalue->m.secHdrPresent = 1;
      pvalue->l3HdrOpts.t = T_TS24007L3_L3HdrOptions_skipInd;
      pvalue->l3HdrOpts.u.skipInd = 0;   
      pvalue->secHdr.secHdrType = TS24007L3_SecHdrType_secHdrForSvcReq;
      pvalue->secHdr.protoDiscr = TS24007L3_ProtoDiscr_epsMobMgmt;
      pvalue->secHdr.msgAuthCode = 0;
      pvalue->secHdr.seqNumber  = 0;
      pvalue->protoDiscr = TS24007L3_ProtoDiscr_epsMobMgmt;
      pvalue->msgType = 0;

      OSRTBUFRESTORE2 (pctxt, &savedBuf);

      pvalue->data.t = T_TS24301Msgs_TS24301_IE_OBJECTSET_obj_ServiceRequest;

      pvalue->data.u.obj_ServiceRequest = 
         rtxMemAllocType (pctxt, TS24301Msg_ServiceRequest);

      if (pvalue->data.u.obj_ServiceRequest == NULL)
         return LOG_RTERR (pctxt, RTERR_NOMEM);

      ret = NASDec_TS24301Msg_ServiceRequest 
         (pctxt, pvalue->data.u.obj_ServiceRequest);

      if (ret < 0) return LOG_RTERR (pctxt, ret);
      
      if ( computeMACRet == 0 ) {
         //check computed mac and expected mac agree
         mac = mac & 0x0FFFF;  //it is a short mac; ignore high two octets
         if ( mac != (OSUINT32) ( pvalue->data.u.obj_ServiceRequest->shortMAC.data[0] << 8 | 
                        pvalue->data.u.obj_ServiceRequest->shortMAC.data[1]) )
         {
            rtxErrAddUIntParm(pctxt, mac); 
            rtxErrAddUIntParm(pctxt,
                        (OSUINT32)(pvalue->data.u.obj_ServiceRequest->shortMAC.data[0] << 8 | 
                        pvalue->data.u.obj_ServiceRequest->shortMAC.data[1]));
            LOG_RTERRNEW(pctxt, RTERR_INVMAC);
         }
      }

      return rtxErrGetStatus(pctxt);
   }

   /* decode protocol discriminator */
   ret = rtxDecBitsToByte (pctxt, &pd, 4);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   OSRTBUFRESTORE2 (pctxt, &savedBuf);
   rtxDiagSetBitFldDisabled (pctxt->pBitFldList, FALSE);

   if (ub != 0 && pd == TS24007L3_ProtoDiscr_epsMobMgmt) {
      RTXCTXTPUSHELEMNAME (pctxt, "secHdr");

      ret = NASDec_TS24007L3_SecProtMsgHeader (pctxt, &pvalue->secHdr);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      pvalue->m.secHdrPresent = 1;

      RTXCTXTPOPELEMNAME (pctxt);
   }

   if (pvalue->m.secHdrPresent && (
       pvalue->secHdr.secHdrType == TS24007L3_SecHdrType_integProtAndCipher ||
       pvalue->secHdr.secHdrType == TS24007L3_SecHdrType_integProtAndCipherAndSecCtxt ||
       pvalue->secHdr.secHdrType == TS24007L3_SecHdrType_integProt ||
       pvalue->secHdr.secHdrType == TS24007L3_SecHdrType_integProtAndSecCtxt ) )
   {
       
      OSOCTET* msg;
      size_t   msgLen;
      OSUINT32 mac;
      
      //Compute the MAC on the (possibly ciphered) plain message.
      //Integrity protection applies to everything but the first 5 octets
      msg = pctxt->buffer.data + savedBuf.byteIndex + 5;
      msgLen = pctxt->buffer.size - savedBuf.byteIndex - 5;

      ret = rtx3gppComputeMAC(pctxt, msg, msgLen, &mac);
      if (ret < 0) LOG_RTERR (pctxt, ret);            
      else {
         //check computed mac and expected mac agree
         if ( mac != pvalue->secHdr.msgAuthCode ) {
            rtxErrAddUIntParm(pctxt, pvalue->secHdr.msgAuthCode);
            rtxErrAddUIntParm(pctxt, mac); 
            LOG_RTERRNEW(pctxt, RTERR_INVMAC);
         }
      }
      
      if (pvalue->secHdr.secHdrType == TS24007L3_SecHdrType_integProtAndCipher ||
          pvalue->secHdr.secHdrType == TS24007L3_SecHdrType_integProtAndCipherAndSecCtxt )
      {
         //We need to decrypt the message, which we can do in place.
         //The first 6 bytes are the security protected message fields. The plain
         //message follows that.
         msg = pctxt->buffer.data + savedBuf.byteIndex + 6;
         msgLen = pctxt->buffer.size - savedBuf.byteIndex - 6;

         ret = rtx3gppCipher(pctxt, msg, msgLen);
         
         if (ret < 0) return LOG_RTERR (pctxt, ret);   
      }            
   }
}
/* end custom code */
