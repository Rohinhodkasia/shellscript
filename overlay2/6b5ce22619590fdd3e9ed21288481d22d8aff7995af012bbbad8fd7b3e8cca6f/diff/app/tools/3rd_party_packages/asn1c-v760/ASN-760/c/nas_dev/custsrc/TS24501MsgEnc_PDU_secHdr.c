/* start custom code */
/* open scope for declaration of saveinfo. This block is closed in fragment
   TS24501MsgEnc_PDU_eom.c */
{
   OSRTBufSave saveinfo;
   OSRTBUFSAVE2(pctxt, &saveinfo);

   /* only encode header if optional bit set and header type != noSec */
   if (pvalue->m.secHdrPresent && 
       pvalue->secHdr.protoDiscr == TS24501Msg_NAS5GProtoDiscr_mobMgmt5G &&
       pvalue->secHdr.secHdrType != TS24501Msg_NAS5GSecHdrType_noSec) {
      
      RTXCTXTPUSHELEMNAME (pctxt, "secHdr");

      /* This is going to encode the header, but we'll later go back
         and fill in the msgAuthCode, which starts at 2nd octet and takes 4 
         octets. */
         
      ret = NASEnc_TS24501Msg_NAS5GSecProtMsgHdr (pctxt, &pvalue->secHdr);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTXCTXTPOPELEMNAME (pctxt);
   }
   /* end custom code */
