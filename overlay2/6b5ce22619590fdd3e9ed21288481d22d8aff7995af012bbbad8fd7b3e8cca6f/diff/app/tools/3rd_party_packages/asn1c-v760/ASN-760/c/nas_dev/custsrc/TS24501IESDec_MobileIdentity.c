/* Start custom code.

Handle first octet of IE having type plus some bits to be interpreted
variously, and nested CHOICE.
 */
EXTERN int NASDec_TS24501IE_MobileIdentity (OSCTXT* pctxt,
   TS24501IE_MobileIdentity* pvalue)
{
   OSSIZE endIndex;
   OSUINT16 len;
   OSUINT8 leadingBits;    /* first 5 bits of first octet */
   TS24501IE_TypeOfIdentity typeOfIdent;
   
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "MobileIdentity");

   /* decode length */

   RTXCTXTPUSHELEMNAME (pctxt, "length");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecUInt16 (pctxt, &len, 2);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   endIndex = rtxCtxtGetBitOffset (pctxt) + len * 8;
   
   ret = rtxCtxtPushContainerBytes(pctxt, len);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   /* decode leading bits */

   RTXCTXTPUSHELEMNAME (pctxt, "leading bits");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &leadingBits, 5);
   if (ret < 0) return LOG_RTERR (pctxt, ret);
   
   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode typeOfIdent */

   RTXCTXTPUSHELEMNAME (pctxt, "typeOfIdent");

   ret = NASDec_TS24501IE_TypeOfIdentity (pctxt, &typeOfIdent);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* Decode chosen alternative */
   pvalue->t = (int)typeOfIdent + 1;

   switch (typeOfIdent)
   {
      case TS24501IE_TypeOfIdentity_none:
         break;

      case TS24501IE_TypeOfIdentity_suci: {
         OSUINT8 supiFormat = ( leadingBits >> 1 ) & 0x07;
         
         RTXCTXTPUSHELEMNAME (pctxt, "suci");

         /* Decode choice data value */

         switch (supiFormat)
         {
            /* supiImsi */
            case 0: {
               RTXCTXTPUSHELEMNAME (pctxt, "supiImsi");

               pvalue->u.suci.t = T_TS24501IE_MobileIdentity_suci_supiImsi;
               
               ret = NASDec_TS24501IE_MobileIdentity_SUCI_IMSI (pctxt,
                            &pvalue->u.suci.u.supiImsi);
               if (ret < 0) return LOG_RTERR (pctxt, ret);

               RTXCTXTPOPELEMNAME (pctxt);
               break;
            }
            /* supiNetSpecificId */
            case 1: {
               RTXCTXTPUSHELEMNAME (pctxt, "supiNetSpecificId");

               pvalue->u.suci.t = T_TS24501IE_MobileIdentity_suci_supiNetSpecificId;
               
               ret = NASDec_TS24501IE_MobileIdentity_SUCI_NetId (pctxt,
                            &pvalue->u.suci.u.supiNetSpecificId);
               if (ret < 0) return LOG_RTERR (pctxt, ret);

               RTXCTXTPOPELEMNAME (pctxt);
               break;
            }
            default:
               return LOG_RTERR (pctxt, RTERR_INVOPT);
         }

         RTXCTXTPOPELEMNAME (pctxt);
         break;
      }
      case TS24501IE_TypeOfIdentity_guti: {
         RTXCTXTPUSHELEMNAME (pctxt, "guti");

         /* Ensure highest 4 bits are set. */
         if (leadingBits < 0x1E) {
            rtxErrAddStrParm (pctxt, "MobileIdentity leading bits for GUTI");
            rtxErrAddUIntParm (pctxt, leadingBits);
            return LOG_RTERR (pctxt, RTERR_CONSVIO);
         }
         ret = NASDec_TS24501IE_MobileIdentity_GUTI (pctxt,
                      &pvalue->u.guti);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;
      }
      case TS24501IE_TypeOfIdentity_imei: {
         OSUINT8 firstDigit = leadingBits >> 1;
         OSUINT8 odd = firstDigit & 1;
         
         RTXCTXTPUSHELEMNAME (pctxt, "imei");

         if (len > 255) {
            rtxErrAddElemNameParm (pctxt);
            rtxErrAddStrParm (pctxt, "length");
            rtxErrAddIntParm (pctxt, (int)len);
            return LOG_RTERR (pctxt, RTERR_CONSVIO);            
         }
         
         ret = rtx3GPPDecMobileIdentityType1 
            (pctxt, (OSUINT8)len, odd, firstDigit, pvalue->u.imei, sizeof(TS24008IE_IMEI));
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;
      }
      case TS24501IE_TypeOfIdentity_stmsi: {
         RTXCTXTPUSHELEMNAME (pctxt, "stmsi");

         /* Ensure leading 4 bits are set */
         if (leadingBits < 0x1E) {
            rtxErrAddStrParm (pctxt, "MobileIdentity leading bits for 5G-S-TMSI");
            rtxErrAddUIntParm (pctxt, leadingBits);
            return LOG_RTERR (pctxt, RTERR_CONSVIO);
         }

         ret = NASDec_TS24501IE_MobileIdentity_STMSI (pctxt,
                      &pvalue->u.stmsi);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;
      }
      case TS24501IE_TypeOfIdentity_imeisv: {
         OSUINT8 firstDigit = leadingBits >> 1;
         OSUINT8 odd = leadingBits & 1;
         
         RTXCTXTPUSHELEMNAME (pctxt, "imeisv");

         if (len > 255) {
            rtxErrAddElemNameParm (pctxt);
            rtxErrAddStrParm (pctxt, "length");
            rtxErrAddIntParm (pctxt, (int)len);
            return LOG_RTERR (pctxt, RTERR_CONSVIO);            
         }
         
         ret = rtx3GPPDecMobileIdentityType1 
            (pctxt, (OSUINT8)len, odd, firstDigit, pvalue->u.imeisv, sizeof(TS24008IE_IMEISV));
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;
      }
      case TS24501IE_TypeOfIdentity_macAddr: {
         RTXCTXTPUSHELEMNAME (pctxt, "mac");
         pvalue->u.mac.mauri = leadingBits & 1;

         RTDIAG_NEWBITFIELD (pctxt, "OCTET STRING");

         ret = rtxDecBitsToByteArray (pctxt, pvalue->u.mac.macaddr, 6, 48);
         if (ret < 0) return LOG_RTERR (pctxt, ret);
         
         RTDIAG_SETBITFLDCOUNT (pctxt);

         RTXCTXTPOPELEMNAME (pctxt);
         break;         
      }
      case TS24501IE_TypeOfIdentity_eui64: {
         RTXCTXTPUSHELEMNAME (pctxt, "eui-64");

         RTDIAG_NEWBITFIELD (pctxt, "OCTET STRING");

         ret = rtxDecBitsToByteArray (pctxt, pvalue->u.eui_64, 8, 64);

         RTDIAG_SETBITFLDCOUNT (pctxt);

         RTXCTXTPOPELEMNAME (pctxt);
         break;
      }
      default:
         return LOG_RTERR (pctxt, RTERR_INVOPT);
   }
  
   if (rtxCtxtGetBitOffset(pctxt) > endIndex)
      return LOG_RTERR (pctxt, RTERR_INVLEN);

   rtxCtxtSetBitOffset(pctxt, endIndex);
   rtxCtxtPopContainer(pctxt);
   
   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

/* End custom code */
