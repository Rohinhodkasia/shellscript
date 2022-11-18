   RTXCTXTPUSHELEMNAME (pctxt, "protoDiscr");

   ret = NASDec_TS24007L3_ProtoDiscr (pctxt, &pvalue->protoDiscr);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* Use protocol descriptor to set L3 header option t value. */
   switch (  pvalue->protoDiscr ) {
      case TS24007L3_ProtoDiscr_sms: {
         OSUINT8 skipInd = pvalue->l3HdrOpts.u.skipInd;
         pvalue->l3HdrOpts.t = T_TS24007L3_L3HdrOptions_transId;
         /* lowest four bits of skipInd hold transId flag & value; flag is
            bit 4, bits 3-1 are value. The highest 4 bits of skipInd ought to
            be zero. */
         pvalue->l3HdrOpts.u.transId.flag = skipInd >> 3;
         pvalue->l3HdrOpts.u.transId.value = skipInd & 0x7;
         break;
      }
      case TS24007L3_ProtoDiscr_epsMobMgmt: {
         pvalue->l3HdrOpts.t = T_TS24007L3_L3HdrOptions_secHdr;
         pvalue->l3HdrOpts.u.secHdr = pvalue->l3HdrOpts.u.skipInd;
         break;
      }
      case TS24007L3_ProtoDiscr_epsSessMgmt: {
         pvalue->l3HdrOpts.t = T_TS24007L3_L3HdrOptions_epsBearerIdent;
         pvalue->l3HdrOpts.u.epsBearerIdent = pvalue->l3HdrOpts.u.skipInd;
         break;
      }
      default:
         break;
   }
