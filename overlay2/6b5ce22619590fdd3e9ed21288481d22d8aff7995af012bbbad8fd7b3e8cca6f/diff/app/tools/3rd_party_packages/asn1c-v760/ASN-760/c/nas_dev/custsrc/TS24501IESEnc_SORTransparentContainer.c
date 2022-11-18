/* Start custom code.
Handle first octet holding data for some of the cases, and use of nested
choice type.
*/
EXTERN int NASEnc_TS24501IE_SORTransparentContainer (OSCTXT* pctxt,
   TS24501IE_SORTransparentContainer* pvalue)
{
   OSSIZE startIndex;
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "SORTransparentContainer");

   /* encode length */

   RTXCTXTPUSHELEMNAME (pctxt, "length");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, 0, 16);
   if (ret < 0) return LOG_RTERR (pctxt, ret);
   startIndex = rtxCtxtGetBitOffset (pctxt);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);
   
   /* encode steeringOrAck */
   RTXCTXTPUSHELEMNAME (pctxt, "steeringOrAck");
   
   if (pvalue->steeringOrAck.t == T_SORTransparentContainer_steeringOrAck_steering)
   {
      ret = NASEnc_TS24501IE_SORSteering (pctxt, &pvalue->steeringOrAck.u.steering);
      if (ret < 0) return LOG_RTERR (pctxt, ret);
   }
   else if (pvalue->steeringOrAck.t == T_SORTransparentContainer_steeringOrAck_ack)
   {
      ret = NASEnc_TS24501IE_SORAck (pctxt, &pvalue->steeringOrAck.u.ack);
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
