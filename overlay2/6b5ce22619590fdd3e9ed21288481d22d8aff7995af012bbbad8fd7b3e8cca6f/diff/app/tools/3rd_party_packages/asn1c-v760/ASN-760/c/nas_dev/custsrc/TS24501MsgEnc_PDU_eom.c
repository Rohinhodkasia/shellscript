/* start custom code */
/* only set MAC and encrypt if required */
if (pvalue->m.secHdrPresent) {
   OSOCTET* msg;
   OSSIZE msgLen;
   OSRTBufSave positionAfterMsg;
   
   OSRTBUFSAVE2(pctxt, &positionAfterMsg);

   switch (pvalue->secHdr.secHdrType) {
   case TS24501Msg_NAS5GSecHdrType_integProtAndCipher:
   case TS24501Msg_NAS5GSecHdrType_integProtAndCipherAnd5GSecCtxt:
      /* Encrypt the message in place.
         The first 7 bytes are the security protected message fields. 
         The plain message follows that. */
      msg = pctxt->buffer.data + saveinfo.byteIndex + 7;
      msgLen = pctxt->buffer.byteIndex - saveinfo.byteIndex - 7;

      ret = rtx3gppCipher(pctxt, msg, msgLen);
      if (ret < 0) return LOG_RTERR (pctxt, ret);     

      break;

   default:; /* no action */
   }

   /* Next, compute the mac on the (possibly ciphered) plain
      message.  Integrity protection applies to everything but the first 
      6 octets. */
   msg = pctxt->buffer.data + saveinfo.byteIndex + 6;
   msgLen = pctxt->buffer.byteIndex - saveinfo.byteIndex - 6;

   ret = rtx3gppComputeMAC(pctxt, msg, msgLen, &pvalue->secHdr.msgAuthCode);
   if (ret < 0) return LOG_RTERR (pctxt, ret);            

   /* Move back to the mac field and encode it; the mac follows the 2nd 
      octet. */
   pctxt->buffer.byteIndex = saveinfo.byteIndex + 2;
   ret = rtxEncBits(pctxt, pvalue->secHdr.msgAuthCode, 32);
   if (ret < 0) return LOG_RTERR (pctxt, ret);            
   
   OSRTBUFRESTORE2(pctxt, &positionAfterMsg);
}

}  /* close brace opened by TS24301MsgEnc_PDUE_secHdr.c custom code */

/* end custom code */
