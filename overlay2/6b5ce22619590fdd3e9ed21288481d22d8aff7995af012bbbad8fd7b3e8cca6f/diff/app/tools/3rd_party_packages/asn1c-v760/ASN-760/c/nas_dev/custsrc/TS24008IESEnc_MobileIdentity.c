/* 10.5.1.4 - Mobile Identity */

EXTERN int NASEnc_TS24008IE_MobileIdentity (OSCTXT* pctxt
   , TS24008IE_MobileIdentity* pvalue)
{
   int ret = 0;
   RTXCTXTPUSHTYPENAME (pctxt, "MobileIdentity");

   /* Encode choice data value */

   switch (pvalue->t)
   {
      /* no identity */
      case T_TS24008IE_MobileIdentity_none:
      {
         int i;

         RTXCTXTPUSHELEMNAME (pctxt, "none");

         /* Encode length.  The "none" field gives us the length. */
         RTDIAG_NEWBITFIELD (pctxt, "length");

         ret = rtxEncBits (pctxt, pvalue->u.none, 8);
         if (0 != ret) return LOG_RTERR (pctxt, ret);

         /* encode identity digits of octet 3, 0 for even/odd and 0 for
            type of identity.*/
         RTDIAG_NEWBITFIELD (pctxt, "octet3");
         ret = rtxEncBits (pctxt, 0, 8);
         if (0 != ret) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);
         
         /* encode identity digits for remaining octets, if any */
         for(i = 1; i < pvalue->u.none; i++)
         {
            RTDIAG_NEWBITFIELD (pctxt, "octet4+");         
            ret = rtxEncBits (pctxt, 0, 8);
            if (0 != ret) return LOG_RTERR (pctxt, ret);            
            RTDIAG_SETBITFLDCOUNT (pctxt);
         }

         RTXCTXTPOPELEMNAME (pctxt);
         break;
      }

      /* imsi */
      case 1:
         RTXCTXTPUSHELEMNAME (pctxt, "imsi");

         ret = rtx3GPPEncMobileIdentityType1 
            (pctxt, (OSUINT8)pvalue->t, pvalue->u.imsi);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* imei */
      case 2:
         RTXCTXTPUSHELEMNAME (pctxt, "imei");

         ret = rtx3GPPEncMobileIdentityType1 
            (pctxt, (OSUINT8)pvalue->t, pvalue->u.imei);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* imeisv */
      case 3:
         RTXCTXTPUSHELEMNAME (pctxt, "imeisv");

         ret = rtx3GPPEncMobileIdentityType1 
            (pctxt, (OSUINT8)pvalue->t, pvalue->u.imeisv);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* tmsi */
      case 4:
         RTXCTXTPUSHELEMNAME (pctxt, "tmsi");

         /* Encode length */
         RTDIAG_NEWBITFIELD (pctxt, "length");

         ret = rtxEncBits (pctxt, 5, 8);
         if (0 != ret) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);

         /* Identity digit 1 is set to 0xF (1111) */
         RTDIAG_NEWBITFIELD (pctxt, "digit1");

         ret = rtxEncBits (pctxt, 0x0F, 4);
         if (0 != ret) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);

         /* Encode odd/even indicator */
         RTDIAG_NEWBITFIELD (pctxt, "odd");

         ret = rtxEncBit (pctxt, FALSE);
         if (0 != ret) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);

         /* Encode type of identity */
         RTDIAG_NEWBITFIELD (pctxt, "type");

         ret = rtxEncBits (pctxt, T_TS24008IE_MobileIdentity_tmsi, 3);
         if (0 != ret) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);

         /* Encode TMSI bytes */
         RTDIAG_NEWBITFIELD (pctxt, "OCTET STRING");

         ret = rtxWriteBytes (pctxt, pvalue->u.tmsi, 4);

         RTDIAG_SETBITFLDCOUNT (pctxt);
         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* tmgi */
      case 5: {
         OSUINT8 len = 4;
         RTXCTXTPUSHELEMNAME (pctxt, "tmgi");

         /* Encode length */

         if (pvalue->u.tmgi.mbmsSessIdInd) {
            len += 1;
         }
         if (pvalue->u.tmgi.mccMncInd) {
            len += 3;
         }
         /* Encode length */
         RTDIAG_NEWBITFIELD (pctxt, "length");

         ret = rtxWriteBytes (pctxt, &len, 1);
         if (0 != ret) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);

         /* Encode spare bits */

         RTDIAG_NEWBITFIELD (pctxt, "spare");

         ret = rtxEncBits (pctxt, 0, 2); /* spare */
         if (0 != ret) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);

         /* encode mbmsSessIdInd */

         RTXCTXTPUSHELEMNAME (pctxt, "mbmsSessIdInd");
         RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

         ret = rtxEncBit (pctxt, pvalue->u.tmgi.mbmsSessIdInd);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);
         RTXCTXTPOPELEMNAME (pctxt);

         /* encode mccMncInd */

         RTXCTXTPUSHELEMNAME (pctxt, "mccMncInd");
         RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

         ret = rtxEncBit (pctxt, pvalue->u.tmgi.mccMncInd);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);
         RTXCTXTPOPELEMNAME (pctxt);

         /* encode odd/even indicator */

         RTXCTXTPUSHELEMNAME (pctxt, "odd");
         RTDIAG_NEWBITFIELD (pctxt, "BOOLEAN");

         ret = rtxEncBit (pctxt, FALSE);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);
         RTXCTXTPOPELEMNAME (pctxt);

         /* Encode type of identity */
         RTDIAG_NEWBITFIELD (pctxt, "type");

         ret = rtxEncBits (pctxt, T_TS24008IE_MobileIdentity_tmgi, 3);
         if (0 != ret) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);

         /* encode mbmsServiceID */

         RTXCTXTPUSHELEMNAME (pctxt, "mbmsServiceID");
         RTDIAG_NEWBITFIELD (pctxt, "OCTET STRING");

         ret = rtxWriteBytes (pctxt, pvalue->u.tmgi.mbmsServiceID, 3);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);
         RTXCTXTPOPELEMNAME (pctxt);

         /* encode mcc-mnc */

         RTXCTXTPUSHELEMNAME (pctxt, "mcc-mnc");

         ret = NASEnc_TS24008IE_MCCMNCPair (pctxt, &pvalue->u.tmgi.mcc_mnc);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);

         /* encode mbmsSessionID */

         RTXCTXTPUSHELEMNAME (pctxt, "mbmsSessionID");
         RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

         ret = rtxEncBits (pctxt, pvalue->u.tmgi.mbmsSessionID, 8);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);
         RTXCTXTPOPELEMNAME (pctxt);

         RTXCTXTPOPELEMNAME (pctxt);
         break;
      }

      default:
         return LOG_RTERR (pctxt, RTERR_INVOPT);
   }

   rtxCtxtPopTypeName (pctxt);

   return (ret);
}
