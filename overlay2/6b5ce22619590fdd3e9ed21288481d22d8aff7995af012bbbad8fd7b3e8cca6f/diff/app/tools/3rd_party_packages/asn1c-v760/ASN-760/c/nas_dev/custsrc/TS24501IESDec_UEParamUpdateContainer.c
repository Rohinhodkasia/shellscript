/* Start custom code.

Handle first octet of IE having type plus some bits to be interpreted
variously, and nested CHOICE.
 */
EXTERN int NASDec_TS24501IE_UEParamUpdateContainer (OSCTXT* pctxt,
   TS24501IE_UEParamUpdateContainer* pvalue)
{
   OSUINT8 firstOctet;
   
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "UEParamUpdateContainer");

   /* decode length */

   RTXCTXTPUSHELEMNAME (pctxt, "length");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecUInt16 (pctxt, &pvalue->length, 2);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   ret = rtxCtxtPushContainerBytes(pctxt, pvalue->length);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   /* decode first octet */
   ret = rtxDecBitsToByte (pctxt, &firstOctet, 8);
   if (ret < 0) return LOG_RTERR (pctxt, ret);
   
   /* Backup so we can re-read that first octet.*/
   pctxt->buffer.byteIndex--;
   
   /* Decode according to data type. */
   if ((firstOctet & 1) == 0) {
      pvalue->updateOrAck.t = T_UEParamUpdateContainer_updateOrAck_update;
      ret = NASDec_TS24501IE_UEParamUpdate (pctxt, &pvalue->updateOrAck.u.update);
      if (ret < 0) return LOG_RTERR (pctxt, ret);
   }
   else {
      pvalue->updateOrAck.t = T_UEParamUpdateContainer_updateOrAck_ack;
      ret = NASDec_TS24501IE_UEParamUpdateAck (pctxt, &pvalue->updateOrAck.u.ack);
      if (ret < 0) return LOG_RTERR (pctxt, ret);
   }
   
   return 0;
}

/* End custom code */
