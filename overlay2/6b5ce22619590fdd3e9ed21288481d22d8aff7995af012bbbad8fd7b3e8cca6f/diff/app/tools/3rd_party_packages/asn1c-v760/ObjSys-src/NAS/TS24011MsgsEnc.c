/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.6.0, Date: 15-Feb-2022.
 */
#include "TS24011Msgs.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxBitEncode.h"
#include "rtxsrc/rtxIntEncode.h"
#include "rt3gppsrc/rtx3GPP.h"
#include "rt3gppsrc/rt3gppNasSec.h"
#include "rtxsrc/rtxDiagBitTrace.h"

EXTERN int NASEnc_TS24011Msg_CPDATA (OSCTXT* pctxt, TS24011Msg_CPDATA* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "CPDATA");

   /* encode cpUserData */

   RTXCTXTPUSHELEMNAME (pctxt, "cpUserData");

   ret = NASEnc_TS24011IE_CPUserData (pctxt, &pvalue->cpUserData);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

EXTERN int NASEnc_TS24011Msg_CPERROR (OSCTXT* pctxt, TS24011Msg_CPERROR* pvalue
   )
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "CPERROR");

   /* encode cpCause */

   RTXCTXTPUSHELEMNAME (pctxt, "cpCause");

   ret = NASEnc_TS24011IE_CPCauseValue (pctxt, &pvalue->cpCause);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

EXTERN int NASEnc_TS24011Msg_CP_PDU (OSCTXT* pctxt, TS24011Msg_CP_PDU* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "CP-PDU");

   /* encode l3HdrOpts */

   RTXCTXTPUSHELEMNAME (pctxt, "l3HdrOpts");

   ret = NASEnc_TS24007L3_L3HdrOptions (pctxt, &pvalue->l3HdrOpts);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode protoDiscr */

   RTXCTXTPUSHELEMNAME (pctxt, "protoDiscr");

   ret = NASEnc_TS24007L3_ProtoDiscr (pctxt, pvalue->protoDiscr);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode msgType */

   RTXCTXTPUSHELEMNAME (pctxt, "msgType");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncUInt32 (pctxt, pvalue->msgType, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode data */

   RTXCTXTPUSHELEMNAME (pctxt, "data");
   switch (pvalue->data.t) {
   /* obj_CP_DATA */
   case T_TS24011Msgs_TS24011_OBJECTSET_obj_CP_DATA:
      RTXCTXTPUSHELEMNAME (pctxt, "u.obj_CP_DATA");

      ret = NASEnc_TS24011Msg_CPDATA (pctxt, pvalue->data.u.obj_CP_DATA);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* obj_CP_ACK */
   case T_TS24011Msgs_TS24011_OBJECTSET_obj_CP_ACK:
      RTXCTXTPUSHELEMNAME (pctxt, "u.obj_CP_ACK");

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* obj_CP_ERROR */
   case T_TS24011Msgs_TS24011_OBJECTSET_obj_CP_ERROR:
      RTXCTXTPUSHELEMNAME (pctxt, "u.obj_CP_ERROR");

      ret = NASEnc_TS24011Msg_CPERROR (pctxt, pvalue->data.u.obj_CP_ERROR);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   default:
      ret = RTERR_INVOPT;
   }
   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

EXTERN int NASEnc_TS24011Msg_RPHeader (OSCTXT* pctxt
   , TS24011Msg_RPHeader* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "RPHeader");

   /* encode spare */

   RTXCTXTPUSHELEMNAME (pctxt, "spare");
   if (!(pvalue->spare <= 31)) {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddIntParm (pctxt, (int)pvalue->spare);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, pvalue->spare, 5);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode rpMsgType */

   RTXCTXTPUSHELEMNAME (pctxt, "rpMsgType");
   if (!(pvalue->rpMsgType <= 7)) {
      rtxErrAddElemNameParm (pctxt);
      rtxErrAddIntParm (pctxt, (int)pvalue->rpMsgType);
      return LOG_RTERR (pctxt, RTERR_CONSVIO);
   }

   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncBits (pctxt, pvalue->rpMsgType, 3);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode rpMsgRef */

   RTXCTXTPUSHELEMNAME (pctxt, "rpMsgRef");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncUInt32 (pctxt, pvalue->rpMsgRef, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

EXTERN int NASEnc_TS24011Msg_RPDataMSOriginating (OSCTXT* pctxt
   , TS24011Msg_RPDataMSOriginating* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "RPDataMSOriginating");

   /* encode origAddrLen */

   RTXCTXTPUSHELEMNAME (pctxt, "origAddrLen");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncUInt32 (pctxt, pvalue->origAddrLen, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode destAddress */

   RTXCTXTPUSHELEMNAME (pctxt, "destAddress");

   ret = NASEnc_TS24011IE_RPDestinationAddress (pctxt, &pvalue->destAddress);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode userData */

   RTXCTXTPUSHELEMNAME (pctxt, "userData");

   ret = NASEnc_TS24011IE_RPUserData (pctxt, &pvalue->userData);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

EXTERN int NASEnc_TS24011Msg_RPDataMSTerminated (OSCTXT* pctxt
   , TS24011Msg_RPDataMSTerminated* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "RPDataMSTerminated");

   /* encode origAddress */

   RTXCTXTPUSHELEMNAME (pctxt, "origAddress");

   ret = NASEnc_TS24011IE_RPOriginatorAddress (pctxt, &pvalue->origAddress);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode destAddrLen */

   RTXCTXTPUSHELEMNAME (pctxt, "destAddrLen");
   RTDIAG_NEWBITFIELD (pctxt, "INTEGER");

   ret = rtxEncUInt32 (pctxt, pvalue->destAddrLen, 1);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTDIAG_SETBITFLDCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   /* encode userData */

   RTXCTXTPUSHELEMNAME (pctxt, "userData");

   ret = NASEnc_TS24011IE_RPUserData (pctxt, &pvalue->userData);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

EXTERN int NASEnc_TS24011Msg_RP_ACK (OSCTXT* pctxt, TS24011Msg_RP_ACK* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "RP-ACK");

   /* encode userData */

   RTXCTXTPUSHELEMNAME (pctxt, "userData");
   if (pvalue->m.userDataPresent) {
      if (!OSRTBYTEALIGNED(pctxt)) {
         return LOG_RTERR (pctxt, RTERR_NOTALIGNED);
      }
      RTDIAG_NEWBITFIELD (pctxt, "iei");

      ret = rtxEncBits (pctxt, 0x41, 8);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);

      ret = NASEnc_TS24011IE_RPUserData (pctxt, &pvalue->userData);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

   }
   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

EXTERN int NASEnc_TS24011Msg_RP_ERROR (OSCTXT* pctxt
   , TS24011Msg_RP_ERROR* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "RP-ERROR");

   /* encode rpCause */

   RTXCTXTPUSHELEMNAME (pctxt, "rpCause");

   ret = NASEnc_TS24011IE_RPCauseElem (pctxt, &pvalue->rpCause);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode userData */

   RTXCTXTPUSHELEMNAME (pctxt, "userData");
   if (pvalue->m.userDataPresent) {
      if (!OSRTBYTEALIGNED(pctxt)) {
         return LOG_RTERR (pctxt, RTERR_NOTALIGNED);
      }
      RTDIAG_NEWBITFIELD (pctxt, "iei");

      ret = rtxEncBits (pctxt, 0x41, 8);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

      RTDIAG_SETBITFLDCOUNT (pctxt);

      ret = NASEnc_TS24011IE_RPUserData (pctxt, &pvalue->userData);
      if (ret < 0) return LOG_RTERR (pctxt, ret);

   }
   RTXCTXTPOPELEMNAME (pctxt);

   RTXCTXTPOPTYPENAME (pctxt);

   return (ret);
}

EXTERN int NASEnc_TS24011Msg_RP_PDU (OSCTXT* pctxt, TS24011Msg_RP_PDU* pvalue)
{
   int ret = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "RP-PDU");

   /* encode header */

   RTXCTXTPUSHELEMNAME (pctxt, "header");

   ret = NASEnc_TS24011Msg_RPHeader (pctxt, &pvalue->header);
   if (ret < 0) return LOG_RTERR (pctxt, ret);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode infoElem */

   RTXCTXTPUSHELEMNAME (pctxt, "infoElem");
   /* Encode choice data value */

   switch (pvalue->header.rpMsgType)
   {
      /* dataToNet */
      case 0:
         RTXCTXTPUSHELEMNAME (pctxt, "dataToNet");

         ret = NASEnc_TS24011Msg_RPDataMSOriginating (pctxt, &pvalue->infoElem.
            u.dataToNet);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* dataToMS */
      case 1:
         RTXCTXTPUSHELEMNAME (pctxt, "dataToMS");

         ret = NASEnc_TS24011Msg_RPDataMSTerminated (pctxt, &pvalue->infoElem.
            u.dataToMS);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* ackToNet */
      case 2:
         RTXCTXTPUSHELEMNAME (pctxt, "ackToNet");

         ret = NASEnc_TS24011Msg_RP_ACK (pctxt, &pvalue->infoElem.u.ackToNet);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* ackToMS */
      case 3:
         RTXCTXTPUSHELEMNAME (pctxt, "ackToMS");

         ret = NASEnc_TS24011Msg_RP_ACK (pctxt, &pvalue->infoElem.u.ackToMS);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* errorToNet */
      case 4:
         RTXCTXTPUSHELEMNAME (pctxt, "errorToNet");

         ret = NASEnc_TS24011Msg_RP_ERROR (pctxt, &pvalue->infoElem.
            u.errorToNet);
         if (ret < 0) return LOG_RTERR (pctxt, ret);

         RTXCTXTPOPELEMNAME (pctxt);
         break;

      /* errorToMS */
      case 5:
         RTXCTXTPUSHELEMNAME (pctxt, "errorToMS");

         ret = NASEnc_TS24011Msg_RP_ERROR (pctxt, &pvalue->infoElem.u.errorToMS
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

