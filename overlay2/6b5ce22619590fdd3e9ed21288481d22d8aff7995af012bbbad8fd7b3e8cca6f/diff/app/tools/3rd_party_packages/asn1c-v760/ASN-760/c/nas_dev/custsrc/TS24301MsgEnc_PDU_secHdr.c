/* start custom code */
//open scope for declaration of saveinfo. This block is closed in fragment
//TS24301MsgEnc_PDU_eom.c
{
   OSRTBufSave saveinfo;

   OSRTBUFSAVE2(pctxt, &saveinfo);

   /* only encode header if optional bit set and header type != noSec */
   if (pvalue->m.secHdrPresent && 
    pvalue->secHdr.protoDiscr == TS24007L3_ProtoDiscr_epsMobMgmt &&
    pvalue->secHdr.secHdrType != TS24007L3_SecHdrType_noSec) {
      

   /* if security header type is SERVICE REQUEST, directly encode
      service request message */
   if (pvalue->secHdr.secHdrType == TS24007L3_SecHdrType_secHdrForSvcReq) {
         /*
         secure message not used in this case.
         calc short mac on first two octets of message
         */
         OSUINT32 mac;
      
      if (pvalue->data.t != 
          T_TS24301Msgs_TS24301_IE_OBJECTSET_obj_ServiceRequest) {
         return LOG_RTERR (pctxt, RTERR_INVOPT);
      }
      ret = NASEnc_TS24301Msg_ServiceRequest 
         (pctxt, pvalue->data.u.obj_ServiceRequest);

         if (ret < 0) return LOG_RTERR (pctxt, ret);            

         ret = rtx3gppComputeMAC(pctxt, pctxt->buffer.data + saveinfo.byteIndex,
            2 /*length*/, &mac);
         if (ret < 0) return LOG_RTERR (pctxt, ret);            

         pvalue->data.u.obj_ServiceRequest->shortMAC.data[0] = mac >> 8;
         pvalue->data.u.obj_ServiceRequest->shortMAC.data[1] = mac & 0xFF;
         
         pctxt->buffer.byteIndex -= 2; //backup to start of mac
         ret = rtxEncBits(pctxt, mac, 16);   //least significant 16 bits only
         
         //no need to restore location, we are back to end of the serv req msg.

      return (ret < 0) ? LOG_RTERR (pctxt, ret) : 0;
   }
   else {
      RTXCTXTPUSHELEMNAME (pctxt, "secHdr");

         /* This is going to encode the header, but we'll later go back
         and fill in the msgAuthCode, which starts at 2nd octet and takes 4 
         octets.         
         */
         
      ret = NASEnc_TS24007L3_SecProtMsgHeader (pctxt, &pvalue->secHdr);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTXCTXTPOPELEMNAME (pctxt);
   }
   }
/* end custom code */
