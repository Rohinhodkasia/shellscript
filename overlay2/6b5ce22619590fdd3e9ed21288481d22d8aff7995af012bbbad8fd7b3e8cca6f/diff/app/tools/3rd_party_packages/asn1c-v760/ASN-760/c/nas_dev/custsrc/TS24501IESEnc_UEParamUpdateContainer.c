/* Start custom code.
Handle first octet holding data for some of the cases, and use of nested
choice type.
*/
EXTERN int NASEnc_TS24501IE_UEParamUpdateContainer (OSCTXT* pctxt,
   TS24501IE_UEParamUpdateContainer* pvalue)
{
   OSSIZE startIndex;
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "UEParamUpdateContainer");

   /* encode length */

   RTXCTXTPUSHELEMNAME (pctxt, "length");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, 0, 16);
   if (ret < 0) return LOG_RTERR (pctxt, ret);
   startIndex = rtxCtxtGetBitOffset (pctxt);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);
   
   /* encode updateOrAck */
   RTXCTXTPUSHELEMNAME (pctxt, "updateOrAck");
   
   if (pvalue->updateOrAck.t == T_UEParamUpdateContainer_updateOrAck_update)
   {
      ret = NASEnc_TS24501IE_UEParamUpdate (pctxt, &pvalue->updateOrAck.u.update);
      if (ret < 0) return LOG_RTERR (pctxt, ret);
   }
   else if (pvalue->updateOrAck.t == T_UEParamUpdateContainer_updateOrAck_ack)
   {
      ret = NASEnc_TS24501IE_UEParamUpdateAck (pctxt, &pvalue->updateOrAck.u.ack);
      if (ret < 0) return LOG_RTERR (pctxt, ret);
   }
   else return LOG_RTERR (pctxt, RTERR_INVOPT);

   RTXCTXTPOPELEMNAME (pctxt);

   if(rtxCtxtTestFlag(pctxt, OSCONTCLOSED)){
      if(!OSRTBYTEALIGNED(pctxt)) return LOG_RTERRNEW(pctxt, ASN_E_BAD_ALIGN);
      rtxCtxtClearFlag(pctxt, OSCONTCLOSED);
   }
   else  {
      rtxByteAlign (pctxt);
   }
   {
      OSSIZE endIndex = rtxCtxtGetBitOffset (pctxt);
      pvalue->length = (OSUINT8)((endIndex - startIndex)/8);
      rtxCtxtSetBitOffset (pctxt, startIndex - 16);
      ret = rtxMergeBits (pctxt, pvalue->length, 16);
      if (ret < 0) return LOG_RTERR (pctxt, ret);
      rtxCtxtSetBitOffset (pctxt, endIndex);
   }

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

/* End custom code */
