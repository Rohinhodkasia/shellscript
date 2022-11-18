/* start custom code */
/* only set MAC and encrypt if requried */
if (pvalue->m.secHdrPresent && 
    pvalue->secHdr.protoDiscr == TS24007L3_ProtoDiscr_epsMobMgmt &&
    pvalue->secHdr.secHdrType != TS24007L3_SecHdrType_noSec &&
    pvalue->secHdr.secHdrType != TS24007L3_SecHdrType_secHdrForSvcReq) 
{
   OSOCTET* msg;
   OSSIZE msgLen;
   OSRTBufSave positionAfterMsg;
   
   OSRTBUFSAVE2(pctxt, &positionAfterMsg);

   if (pvalue->secHdr.secHdrType == TS24007L3_SecHdrType_integProtAndCipher
      || pvalue->secHdr.secHdrType == TS24007L3_SecHdrType_integProtAndCipherAndSecCtxt)
   {    
      //We need to encrypt the message, which we can do in place.
      //The first 6 bytes are the security protected message fields. The plain
      //message follows that.
      msg = pctxt->buffer.data + saveinfo.byteIndex + 6;
      msgLen = pctxt->buffer.byteIndex - saveinfo.byteIndex - 6;

      ret = rtx3gppCipher(pctxt, msg, msgLen);

      if (ret < 0) return LOG_RTERR (pctxt, ret);     
   }
      
   //Next, we need to compute the mac on the (possibly ciphered) plain
   //message.
   //integrity protection applies to everything but the first 5 octets
   msg = pctxt->buffer.data + saveinfo.byteIndex + 5;
   msgLen = pctxt->buffer.byteIndex - saveinfo.byteIndex - 5;

   ret = rtx3gppComputeMAC(pctxt, msg, msgLen, &pvalue->secHdr.msgAuthCode);
   if (ret < 0) return LOG_RTERR (pctxt, ret);            

   //Move back to the mac field and encode it; the mac follows the first octet.
   pctxt->buffer.byteIndex = saveinfo.byteIndex + 1;
   ret = rtxEncBits(pctxt, pvalue->secHdr.msgAuthCode, 32);
   if (ret < 0) return LOG_RTERR (pctxt, ret);            
   
   OSRTBUFRESTORE2(pctxt, &positionAfterMsg);
}

}  //close brace opened by TS24301MsgEnc_PDUE_secHdr.c custom code

/* end custom code */
