/* Start custom code.

Handle first octet of IE having type plus some bits to be interpreted
variously, and nested CHOICE.
 */
EXTERN int NASDec_TS24501IE_SORTransparentContainer (OSCTXT* pctxt,
   TS24501IE_SORTransparentContainer* pvalue)
{
   OSUINT8 firstOctet;
   
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "SORTransparentContainer");

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
      pvalue->steeringOrAck.t = T_SORTransparentContainer_steeringOrAck_steering;
      ret = NASDec_TS24501IE_SORSteering (pctxt, &pvalue->steeringOrAck.u.steering);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

   }
   else {
      pvalue->steeringOrAck.t = T_SORTransparentContainer_steeringOrAck_ack;
      ret = NASDec_TS24501IE_SORAck (pctxt, &pvalue->steeringOrAck.u.ack);
      if (ret < 0) return LOG_RTERR (pctxt, ret);
   }
   
   return 0;
}

/* End custom code */
