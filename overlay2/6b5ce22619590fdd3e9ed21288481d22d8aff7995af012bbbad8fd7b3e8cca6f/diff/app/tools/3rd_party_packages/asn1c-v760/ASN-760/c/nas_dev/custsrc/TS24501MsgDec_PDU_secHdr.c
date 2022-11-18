/* start custom code */
{
   OSRTBufSave savedBuf;

   rtxDiagSetBitFldDisabled (pctxt->pBitFldList, TRUE);

   /* Save context location (at begin of message, at extended protocol
      discriminator, and then restore below prior to decoding the security
      header, if present... */
   OSRTBUFSAVE2 (pctxt, &savedBuf);

   /* decode extended protocol discriminatory */
   ret = NASDec_TS24501Msg_NAS5GProtoDiscr (pctxt, &pvalue->secHdr.protoDiscr);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   /* only decode security header if this is not a plain message... */
   if (pvalue->secHdr.protoDiscr == TS24501Msg_NAS5GProtoDiscr_mobMgmt5G)
   {
      /* skip spare bits */
      ret = rtxSkipBits (pctxt, 4);
      if (0 != ret) return LOG_RTERR (pctxt, ret);

      /* decode security header type */
      ret = NASDec_TS24501Msg_NAS5GSecHdrType (pctxt, &pvalue->secHdr.secHdrType);
      if (0 != ret) return LOG_RTERR (pctxt, ret);
   }

   /* Restore context location to begin of message, at extended protocol
      discriminator, so that we can fully decode the security header... */
   OSRTBUFRESTORE2 (pctxt, &savedBuf);
   rtxDiagSetBitFldDisabled (pctxt->pBitFldList, FALSE);

   if ((pvalue->secHdr.secHdrType != TS24501Msg_NAS5GSecHdrType_noSec) && 
       (pvalue->secHdr.protoDiscr == TS24501Msg_NAS5GProtoDiscr_mobMgmt5G))
   {
      RTXCTXTPUSHELEMNAME (pctxt, "secHdr");

      ret = NASDec_TS24501Msg_NAS5GSecProtMsgHdr (pctxt, &pvalue->secHdr);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      pvalue->m.secHdrPresent = 1;

      RTXCTXTPOPELEMNAME (pctxt);
   }

   if (pvalue->m.secHdrPresent && 
       pvalue->secHdr.secHdrType != TS24501Msg_NAS5GSecHdrType_noSec)
   {
      OSOCTET* msg;
      OSSIZE   msgLen;
      OSUINT32 mac;
      
      /* Compute the MAC on the (possibly ciphered) plain message.
         Integrity protection applies to everything but the first 6 octets */
      msg = pctxt->buffer.data + savedBuf.byteIndex + 6;
      msgLen = pctxt->buffer.size - savedBuf.byteIndex - 6;

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
      
      if (pvalue->secHdr.secHdrType == 
             TS24501Msg_NAS5GSecHdrType_integProtAndCipher ||
          pvalue->secHdr.secHdrType == 
             TS24501Msg_NAS5GSecHdrType_integProtAndCipherAnd5GSecCtxt)
      {
         /* Decrypt the message in place.
            The first 7 bytes are the security protected message fields. 
            The plain message follows that. */
         msg = pctxt->buffer.data + savedBuf.byteIndex + 7;
         msgLen = pctxt->buffer.size - savedBuf.byteIndex - 7;

         ret = rtx3gppCipher(pctxt, msg, msgLen);
         
         if (ret < 0) return LOG_RTERR (pctxt, ret);   
      }            
   }
}
/* end custom code */
