/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.4.1.1, Date: 02-Jun-2020.
 */
#include "TS24011Msgs.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxBitDecode.h"
#include "rtxsrc/rtxIntDecode.h"
#include "rt3gppsrc/rtx3GPP.h"
#include "rt3gppsrc/rt3gppNasSec.h"
#include "rtxsrc/rtxDiagBitTrace.h"

EXTERN int NASDec_TS24011Msg_CPDATA (OSCTXT* pctxt, TS24011Msg_CPDATA* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "CPDATA");

   /* decode cpUserData */

   RTXCTXTPUSHELEMNAME (pctxt, "cpUserData");

   ret = NASDec_TS24011IE_CPUserData (pctxt, &pvalue->cpUserData);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   ret = rtx3GPPDecL3NonImperative (pctxt, FALSE);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

EXTERN int NASDec_TS24011Msg_CPERROR (OSCTXT* pctxt, TS24011Msg_CPERROR* pvalue
   )
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "CPERROR");

   /* decode cpCause */

   RTXCTXTPUSHELEMNAME (pctxt, "cpCause");

   ret = NASDec_TS24011IE_CPCauseValue (pctxt, &pvalue->cpCause);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   ret = rtx3GPPDecL3NonImperative (pctxt, FALSE);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

EXTERN int NASDec_TS24011Msg_CP_PDU (OSCTXT* pctxt, TS24011Msg_CP_PDU* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "CP_PDU");

   /* decode l3HdrOpts */

   RTXCTXTPUSHELEMNAME (pctxt, "l3HdrOpts");

   ret = NASDec_TS24007L3_L3HdrOptions (pctxt, &pvalue->l3HdrOpts);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode protoDiscr */

   /* begin custom source file PDU_protoDiscr.c */

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
      }

   /* end custom source file PDU_protoDiscr.c */

   /* decode msgType */

   RTXCTXTPUSHELEMNAME (pctxt, "msgType");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->msgType, 8);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode data */

   RTXCTXTPUSHELEMNAME (pctxt, "data");

   switch (pvalue->protoDiscr) {
   /* obj_CP_DATA */
   case TS24007L3_ProtoDiscr_sms:
      switch (pvalue->msgType) {
      /* obj_CP_DATA */
      case ASN1V_mt_CP_DATA:
         pvalue->data.t = T_TS24011Msgs_TS24011_OBJECTSET_obj_CP_DATA;

         pvalue->data.u.obj_CP_DATA = rtxMemAllocType (pctxt, 
            TS24011Msg_CPDATA);

         if (pvalue->data.u.obj_CP_DATA == NULL)
            return LOG_RTERR (pctxt, RTERR_NOMEM);

         asn1Init_TS24011Msg_CPDATA (pvalue->data.u.obj_CP_DATA);

         RTXCTXTPUSHELEMNAME (pctxt, "u.obj_CP_DATA");

         ret = NASDec_TS24011Msg_CPDATA (pctxt, pvalue->data.u.obj_CP_DATA);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);

         break;

      /* obj_CP_ACK */
      case ASN1V_mt_CP_ACK:
         pvalue->data.t = T_TS24011Msgs_TS24011_OBJECTSET_obj_CP_ACK;

         RTXCTXTPUSHELEMNAME (pctxt, "u.obj_CP_ACK");

         RTXCTXTPOPELEMNAME (pctxt);

         break;

      /* obj_CP_ERROR */
      case ASN1V_mt_CP_ERROR:
         pvalue->data.t = T_TS24011Msgs_TS24011_OBJECTSET_obj_CP_ERROR;

         pvalue->data.u.obj_CP_ERROR = rtxMemAllocType (pctxt, 
            TS24011Msg_CPERROR);

         if (pvalue->data.u.obj_CP_ERROR == NULL)
            return LOG_RTERR (pctxt, RTERR_NOMEM);

         asn1Init_TS24011Msg_CPERROR (pvalue->data.u.obj_CP_ERROR);

         RTXCTXTPUSHELEMNAME (pctxt, "u.obj_CP_ERROR");

         ret = NASDec_TS24011Msg_CPERROR (pctxt, pvalue->data.u.obj_CP_ERROR);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);

         break;

      default:
         return LOG_RTERRNEW (pctxt,
            rtxErrInvUIntOpt (pctxt, pvalue->msgType));
         break;
      }

      break;

   /* obj_CP_ACK */
   /* obj_CP_ERROR */
   default:
      return LOG_RTERRNEW (pctxt,
         rtxErrInvUIntOpt (pctxt, pvalue->protoDiscr));
      break;
   }

   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

EXTERN int NASDec_TS24011Msg_RPHeader (OSCTXT* pctxt
   , TS24011Msg_RPHeader* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "RPHeader");

   /* decode spare */

   RTXCTXTPUSHELEMNAME (pctxt, "spare");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->spare, 5);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode rpMsgType */

   RTXCTXTPUSHELEMNAME (pctxt, "rpMsgType");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->rpMsgType, 3);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode rpMsgRef */

   RTXCTXTPUSHELEMNAME (pctxt, "rpMsgRef");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->rpMsgRef, 8);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

EXTERN int NASDec_TS24011Msg_RPDataMSOriginating (OSCTXT* pctxt
   , TS24011Msg_RPDataMSOriginating* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "RPDataMSOriginating");

   /* decode origAddrLen */

   RTXCTXTPUSHELEMNAME (pctxt, "origAddrLen");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->origAddrLen, 8);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode destAddress */

   RTXCTXTPUSHELEMNAME (pctxt, "destAddress");

   ret = NASDec_TS24011IE_RPDestinationAddress (pctxt, &pvalue->destAddress);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode userData */

   RTXCTXTPUSHELEMNAME (pctxt, "userData");

   ret = NASDec_TS24011IE_RPUserData (pctxt, &pvalue->userData);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   ret = rtx3GPPDecL3NonImperative (pctxt, FALSE);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

EXTERN int NASDec_TS24011Msg_RPDataMSTerminated (OSCTXT* pctxt
   , TS24011Msg_RPDataMSTerminated* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "RPDataMSTerminated");

   /* decode origAddress */

   RTXCTXTPUSHELEMNAME (pctxt, "origAddress");

   ret = NASDec_TS24011IE_RPOriginatorAddress (pctxt, &pvalue->origAddress);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode destAddrLen */

   RTXCTXTPUSHELEMNAME (pctxt, "destAddrLen");

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxDecBitsToByte (pctxt, &pvalue->destAddrLen, 8);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode userData */

   RTXCTXTPUSHELEMNAME (pctxt, "userData");

   ret = NASDec_TS24011IE_RPUserData (pctxt, &pvalue->userData);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   ret = rtx3GPPDecL3NonImperative (pctxt, FALSE);
   if (0 != ret) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

EXTERN int NASDec_TS24011Msg_RP_ACK (OSCTXT* pctxt, TS24011Msg_RP_ACK* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "RP_ACK");

   OSCRTLMEMSET (&pvalue->m, 0, sizeof(pvalue->m));

   {
      int lastRow = 0;
      OSUINT8 iei, lastIEI = 0;

      while (rtxCtxtContainerHasRemBits(pctxt)) {
         OSUINT8 skipBytes = 0;
         OSBOOL comprReqd = FALSE;

         /* Decode IEI */
         RTDIAG_NEWBITFIELD (pctxt, "IEI");

         ret = rtxDecBitsToByte (pctxt, &iei, 8);
         if (ret == RTERR_ENDOFBUF) break;
         else if (0 != ret) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);

         switch (iei) {
            case 65: {
               if (lastRow == 0) {
                  /* decode userData */
                  RTXCTXTPUSHELEMNAME (pctxt, "userData");

                  ret = NASDec_TS24011IE_RPUserData (pctxt, &pvalue->userData
                     );
                  if (ret < 0) return LOG_RTERR (pctxt, ret);
                  pvalue->m.userDataPresent = 1;

                  lastRow = 1;

                  RTXCTXTPOPELEMNAME (pctxt);
               }
               else {
                  ret = rtxDecBitsToByte (pctxt, &skipBytes, 8);
                  if (0 != ret) return LOG_RTERR (pctxt, ret);
               }
               break;
            }
            default: {
               if (!(iei & 0x80)) {
                  ret = rtxDecBitsToByte (pctxt, &skipBytes, 8);
                  if (0 != ret) return LOG_RTERR (pctxt, ret);

                  comprReqd = (OSBOOL)((iei & 0x0F) == 0);
               }
            }
         }

         if (skipBytes != 0) {
            ret = rtxSkipBits (pctxt, skipBytes * 8);
            if (0 != ret) return LOG_RTERR (pctxt, ret);
         }

         if (comprReqd && iei != lastIEI) {
            rtxErrAddIntParm (pctxt, iei);
            LOG_RTERRNEW (pctxt, RTERR_UNKNOWNIE);
         }

         lastIEI = iei;
      }
   }
   ret = rtxErrGetStatus (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

EXTERN int NASDec_TS24011Msg_RP_ERROR (OSCTXT* pctxt
   , TS24011Msg_RP_ERROR* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "RP_ERROR");

   OSCRTLMEMSET (&pvalue->m, 0, sizeof(pvalue->m));

   /* decode rpCause */

   RTXCTXTPUSHELEMNAME (pctxt, "rpCause");

   ret = NASDec_TS24011IE_RPCauseElem (pctxt, &pvalue->rpCause);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   {
      int lastRow = 0;
      OSUINT8 iei, lastIEI = 0;

      while (rtxCtxtContainerHasRemBits(pctxt)) {
         OSUINT8 skipBytes = 0;
         OSBOOL comprReqd = FALSE;

         /* Decode IEI */
         RTDIAG_NEWBITFIELD (pctxt, "IEI");

         ret = rtxDecBitsToByte (pctxt, &iei, 8);
         if (ret == RTERR_ENDOFBUF) break;
         else if (0 != ret) return LOG_RTERR (pctxt, ret);

         RTDIAG_SETBITFLDCOUNT (pctxt);

         switch (iei) {
            case 65: {
               if (lastRow == 0) {
                  /* decode userData */
                  RTXCTXTPUSHELEMNAME (pctxt, "userData");

                  ret = NASDec_TS24011IE_RPUserData (pctxt, &pvalue->userData
                     );
                  if (ret < 0) return LOG_RTERR (pctxt, ret);
                  pvalue->m.userDataPresent = 1;

                  lastRow = 1;

                  RTXCTXTPOPELEMNAME (pctxt);
               }
               else {
                  ret = rtxDecBitsToByte (pctxt, &skipBytes, 8);
                  if (0 != ret) return LOG_RTERR (pctxt, ret);
               }
               break;
            }
            default: {
               if (!(iei & 0x80)) {
                  ret = rtxDecBitsToByte (pctxt, &skipBytes, 8);
                  if (0 != ret) return LOG_RTERR (pctxt, ret);

                  comprReqd = (OSBOOL)((iei & 0x0F) == 0);
               }
            }
         }

         if (skipBytes != 0) {
            ret = rtxSkipBits (pctxt, skipBytes * 8);
            if (0 != ret) return LOG_RTERR (pctxt, ret);
         }

         if (comprReqd && iei != lastIEI) {
            rtxErrAddIntParm (pctxt, iei);
            LOG_RTERRNEW (pctxt, RTERR_UNKNOWNIE);
         }

         lastIEI = iei;
      }
   }
   ret = rtxErrGetStatus (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

EXTERN int NASDec_TS24011Msg_RP_PDU (OSCTXT* pctxt, TS24011Msg_RP_PDU* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "RP_PDU");

   /* decode header */

   RTXCTXTPUSHELEMNAME (pctxt, "header");

   ret = NASDec_TS24011Msg_RPHeader (pctxt, &pvalue->header);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* decode infoElem */

   RTXCTXTPUSHELEMNAME (pctxt, "infoElem");

   /* Decode choice data value */

   switch (pvalue->header.rpMsgType)
   {
      /* dataToNet */
      case 0:
         RTXCTXTPUSHELEMNAME (pctxt, "dataToNet");

         ret = NASDec_TS24011Msg_RPDataMSOriginating (pctxt, &pvalue->infoElem.
            u.dataToNet);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* dataToMS */
      case 1:
         RTXCTXTPUSHELEMNAME (pctxt, "dataToMS");

         ret = NASDec_TS24011Msg_RPDataMSTerminated (pctxt, &pvalue->infoElem.
            u.dataToMS);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* ackToNet */
      case 2:
         RTXCTXTPUSHELEMNAME (pctxt, "ackToNet");

         ret = NASDec_TS24011Msg_RP_ACK (pctxt, &pvalue->infoElem.u.ackToNet);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* ackToMS */
      case 3:
         RTXCTXTPUSHELEMNAME (pctxt, "ackToMS");

         ret = NASDec_TS24011Msg_RP_ACK (pctxt, &pvalue->infoElem.u.ackToMS);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* errorToNet */
      case 4:
         RTXCTXTPUSHELEMNAME (pctxt, "errorToNet");

         ret = NASDec_TS24011Msg_RP_ERROR (pctxt, &pvalue->infoElem.
            u.errorToNet);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* errorToMS */
      case 5:
         RTXCTXTPUSHELEMNAME (pctxt, "errorToMS");

         ret = NASDec_TS24011Msg_RP_ERROR (pctxt, &pvalue->infoElem.u.errorToMS
            );
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* smma */
      case 6:
         RTXCTXTPUSHELEMNAME (pctxt, "smma");

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      default:
         return LOG_RTERR (pctxt, RTERR_INVOPT);
   }

   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

