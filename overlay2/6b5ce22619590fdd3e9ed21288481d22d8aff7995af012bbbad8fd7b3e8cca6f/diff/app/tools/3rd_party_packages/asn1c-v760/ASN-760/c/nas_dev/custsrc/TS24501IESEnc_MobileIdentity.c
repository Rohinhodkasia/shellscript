/* Start custom code.
Handle first octet holding data for some of the cases, and use of nested
choice type.
*/
EXTERN int NASEnc_TS24501IE_MobileIdentity (OSCTXT* pctxt,
   TS24501IE_MobileIdentity* pvalue)
{
   int ret = 0;
   OSSIZE startIndex;
   OSUINT8 len = 0;          /* non-zero if known upfront. */
   OSUINT8 firstOctet = 0;   /* firstOctet for certain cases */

   RTXCTXTPUSHTYPENAME (pctxt, "MobileIdentity");

   /* We encode a length and the first octet for all cases except
      IMEI and IMEISV, for which we'll call separate functions.
   */   
   switch (pvalue->t) {
      case T_TS24501IE_MobileIdentity_none:
         len = 1; firstOctet = 0; break;
      case T_TS24501IE_MobileIdentity_suci: {
         /* SUCI */
         len = 0;    /* we'll fill in length afterward */
         firstOctet = 1;
         if ( pvalue->u.suci.t == T_TS24501IE_MobileIdentity_suci_supiNetSpecificId)
            firstOctet += 0x10;
         break;
      }
      case T_TS24501IE_MobileIdentity_guti:
         len = 11; firstOctet = 0xF2; break;
      case T_TS24501IE_MobileIdentity_stmsi:
         len = 7; firstOctet = 0xF4; break;
      case T_TS24501IE_MobileIdentity_mac: {
         len = 7; firstOctet = 6;
         if ( pvalue->u.mac.mauri ) firstOctet += 0x08;
         break;
      }
      case T_TS24501IE_MobileIdentity_eui_64:
         len = 9; firstOctet = 0x07; break;
      default:
         break;
   }
   
   if ( pvalue->t == T_TS24501IE_MobileIdentity_imei ||
         pvalue->t == T_TS24501IE_MobileIdentity_imeisv )
   {
      /* Encode 0 for the first octet of the two-octet length. */
      RTDIAG_NEWBITFIELD (pctxt, "length-1st-octet");

      ret = rtxEncUInt32 (pctxt, 0, 1);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);
   }         
   else {
      /* Encode zero or expected length.  We'll correct it after encoding,
         if necessary. */

      RTXCTXTPUSHELEMNAME (pctxt, "length");

      RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

      ret = rtxEncUInt32 (pctxt, len, 2);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);
      RTXCTXTPOPELEMNAME (pctxt);
      
      startIndex = rtxCtxtGetBitOffset (pctxt);

      /* encode first octet */
      RTXCTXTPUSHELEMNAME (pctxt, "bits+type");

      RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

      ret = rtxEncBits (pctxt, firstOctet, 8);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);
      RTXCTXTPOPELEMNAME (pctxt);
   }

   /* Encode whatever remains for each type. */
   switch (pvalue->t)
   {
      case T_TS24501IE_MobileIdentity_none:
         break;    /* None.  Nothing remains */
      case T_TS24501IE_MobileIdentity_suci: {       
         RTXCTXTPUSHELEMNAME (pctxt, "suci");

         switch (pvalue->u.suci.t) {
            case T_TS24501IE_MobileIdentity_suci_supiImsi:
               ret = NASEnc_TS24501IE_MobileIdentity_SUCI_IMSI(pctxt,
                  &pvalue->u.suci.u.supiImsi);
               break;
            case T_TS24501IE_MobileIdentity_suci_supiNetSpecificId:
               ret = NASEnc_TS24501IE_MobileIdentity_SUCI_NetId (pctxt,
                  &pvalue->u.suci.u.supiNetSpecificId);
               break;
            default:
               return LOG_RTERR (pctxt, RTERR_INVOPT);
         }       
         if (ret < 0) return LOG_RTERR (pctxt, ret);     

         RTXCTXTPOPELEMNAME (pctxt);        
         break;
      }
      case T_TS24501IE_MobileIdentity_guti: {
         RTXCTXTPUSHELEMNAME (pctxt, "guti");
         ret = NASEnc_TS24501IE_MobileIdentity_GUTI(pctxt, &pvalue->u.guti);
         if (ret < 0) return LOG_RTERR (pctxt, ret);
         RTXCTXTPOPELEMNAME (pctxt);        
         break;
      }
      case T_TS24501IE_MobileIdentity_imei: {
         /* IMEI */
         RTXCTXTPUSHELEMNAME (pctxt, "imei");

         ret = rtx3GPPEncMobileIdentityType1 
            (pctxt, 3, pvalue->u.imei);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);        
         break;
      }
      case T_TS24501IE_MobileIdentity_stmsi: {
         /* stmsi */
         RTXCTXTPUSHELEMNAME (pctxt, "stmsi");
         ret = NASEnc_TS24501IE_MobileIdentity_STMSI(pctxt, &pvalue->u.stmsi);
         if (ret < 0) return LOG_RTERR (pctxt, ret);
         RTXCTXTPOPELEMNAME (pctxt);        
         break;
      }
      case T_TS24501IE_MobileIdentity_imeisv: {
         /* IMEISV */
         RTXCTXTPUSHELEMNAME (pctxt, "imeisv");

         ret = rtx3GPPEncMobileIdentityType1 
            (pctxt, 5, pvalue->u.imeisv);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);        
         break;
      }
      case T_TS24501IE_MobileIdentity_mac: {
         /* mac */
         RTXCTXTPUSHELEMNAME (pctxt, "macaddr");
         RTDIAG_NEWBITFIELD (pctxt, "OCTET STRING");

         ret = rtxEncBitsFromByteArray (pctxt, pvalue->u.mac.macaddr, 48);
         if (ret < 0) return LOG_RTERR (pctxt, ret);
         
         RTDIAG_SETBITFLDCOUNT (pctxt);
         RTXCTXTPOPELEMNAME (pctxt);
         break;
      }
      case T_TS24501IE_MobileIdentity_eui_64: {
         /* eui64 */
         RTXCTXTPUSHELEMNAME (pctxt, "eui-64");

         RTDIAG_NEWBITFIELD (pctxt, "OCTET STRING");

         ret = rtxEncBitsFromByteArray (pctxt, pvalue->u.eui_64, 64);

         RTDIAG_SETBITFLDCOUNT (pctxt);

         RTXCTXTPOPELEMNAME (pctxt);
         break;
      }
      default:
         return LOG_RTERR (pctxt, RTERR_INVOPT);
   }
   
   if(rtxCtxtTestFlag(pctxt, OSCONTCLOSED)) {
      if(!OSRTBYTEALIGNED(pctxt)) return LOG_RTERRNEW(pctxt, ASN_E_BAD_ALIGN);
      rtxCtxtClearFlag(pctxt, OSCONTCLOSED);
   }
   else  {
      rtxByteAlign (pctxt);
   }

   if ( pvalue->t != T_TS24501IE_MobileIdentity_imei &&
         pvalue->t != T_TS24501IE_MobileIdentity_imeisv ) 
   {
      /* Go back and encode the correct length, if the previously encoded
         length is different than the actual length.
      */
      OSSIZE endIndex = rtxCtxtGetBitOffset (pctxt);
      OSUINT32 actualLen = (OSUINT32)((endIndex - startIndex)/8);
      if (len != actualLen) {
         rtxCtxtSetBitOffset (pctxt, startIndex - 16);
         ret = rtxMergeBits (pctxt, actualLen, 16);
         if (ret < 0) return LOG_RTERR (pctxt, ret);
         rtxCtxtSetBitOffset (pctxt, endIndex);
      }
   }
   
   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

/* End custom code */
