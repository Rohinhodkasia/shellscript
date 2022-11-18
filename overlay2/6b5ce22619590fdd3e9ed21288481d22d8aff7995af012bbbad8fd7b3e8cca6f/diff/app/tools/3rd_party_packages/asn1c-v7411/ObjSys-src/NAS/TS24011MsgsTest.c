/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.4.1.1, Date: 02-Jun-2020.
 */
#include "TS24011Msgs.h"
#include "TS24007L3.h"
#include "TS24011IES.h"
#include "TS24008IES.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxDiagBitTrace.h"

/*
 * Randomly generated test file: seed = 1591119629
 */
TS24011Msg_CPDATA* asn1Test_TS24011Msg_CPDATA (OSCTXT* pctxt)
{
   TS24011Msg_CPDATA* pvalue = rtxMemAllocType (pctxt, TS24011Msg_CPDATA);
   asn1Init_TS24011Msg_CPDATA (pvalue);

   {
      pvalue->cpUserData.numocts = 0;
   }
   return (pvalue);
}

TS24011Msg_CPERROR* asn1Test_TS24011Msg_CPERROR (OSCTXT* pctxt)
{
   TS24011Msg_CPERROR* pvalue = rtxMemAllocType (pctxt, TS24011Msg_CPERROR);
   asn1Init_TS24011Msg_CPERROR (pvalue);

   pvalue->cpCause.ext = 1;

   pvalue->cpCause.value = 50;
   return (pvalue);
}

TS24011Msg_CP_PDU* asn1Test_TS24011Msg_CP_PDU (OSCTXT* pctxt)
{
   TS24011Msg_CP_PDU* pvalue = rtxMemAllocType (pctxt, TS24011Msg_CP_PDU);
   asn1Init_TS24011Msg_CP_PDU (pvalue);

   pvalue->l3HdrOpts.t =  2;

   pvalue->l3HdrOpts.u.transId.flag = 1;

   pvalue->l3HdrOpts.u.transId.value = 253;

   pvalue->protoDiscr = TS24007L3_ProtoDiscr_sms;

   pvalue->msgType = ASN1V_mt_CP_ERROR;

   pvalue->data.t = T_TS24011Msgs_TS24011_OBJECTSET_obj_CP_ERROR;
   pvalue->data.u.obj_CP_ERROR = rtxMemAllocTypeZ (pctxt, TS24011Msg_CPERROR);

   pvalue->data.u.obj_CP_ERROR->cpCause.ext = 0;

   pvalue->data.u.obj_CP_ERROR->cpCause.value = 65;
   return (pvalue);
}

TS24011Msg_RPHeader* asn1Test_TS24011Msg_RPHeader (OSCTXT* pctxt)
{
   TS24011Msg_RPHeader* pvalue = rtxMemAllocType (pctxt, TS24011Msg_RPHeader);
   asn1Init_TS24011Msg_RPHeader (pvalue);

   pvalue->spare = 14;

   pvalue->rpMsgType = 5;

   pvalue->rpMsgRef = 52;
   return (pvalue);
}

TS24011Msg_RPDataMSOriginating*
    asn1Test_TS24011Msg_RPDataMSOriginating (OSCTXT* pctxt)
{
   TS24011Msg_RPDataMSOriginating* pvalue = rtxMemAllocType (pctxt, TS24011Msg_RPDataMSOriginating);
   asn1Init_TS24011Msg_RPDataMSOriginating (pvalue);

   pvalue->origAddrLen = 250;

   pvalue->destAddress.length = 0; /* length will be calculated */

   pvalue->destAddress.octet3.typeOfNumber = 1;

   pvalue->destAddress.octet3.numberingPlanID = 12;

   pvalue->destAddress.number = "28*4";

   {
      pvalue->userData.numocts = 0;
   }
   return (pvalue);
}

TS24011Msg_RPDataMSTerminated*
    asn1Test_TS24011Msg_RPDataMSTerminated (OSCTXT* pctxt)
{
   TS24011Msg_RPDataMSTerminated* pvalue = rtxMemAllocType (pctxt, TS24011Msg_RPDataMSTerminated);
   asn1Init_TS24011Msg_RPDataMSTerminated (pvalue);

   pvalue->origAddress.length = 0; /* length will be calculated */

   pvalue->origAddress.octet3.typeOfNumber = 4;

   pvalue->origAddress.octet3.numberingPlanID = 14;

   pvalue->origAddress.number = "45a#";

   pvalue->destAddrLen = 46;

   {
      pvalue->userData.numocts = 0;
   }
   return (pvalue);
}

TS24011Msg_RP_ACK* asn1Test_TS24011Msg_RP_ACK (OSCTXT* pctxt)
{
   TS24011Msg_RP_ACK* pvalue = rtxMemAllocType (pctxt, TS24011Msg_RP_ACK);
   asn1Init_TS24011Msg_RP_ACK (pvalue);

   pvalue->m.userDataPresent = 1;
   {
      pvalue->userData.numocts = 0;
   }
   return (pvalue);
}

TS24011Msg_RP_ERROR* asn1Test_TS24011Msg_RP_ERROR (OSCTXT* pctxt)
{
   TS24011Msg_RP_ERROR* pvalue = rtxMemAllocType (pctxt, TS24011Msg_RP_ERROR);
   asn1Init_TS24011Msg_RP_ERROR (pvalue);

   pvalue->rpCause.length = 0; /* length will be calculated */

   pvalue->rpCause.ext = 0;

   pvalue->rpCause.causeValue = 63;

   /* zero elements */

   pvalue->m.userDataPresent = 1;
   {
      pvalue->userData.numocts = 0;
   }
   return (pvalue);
}

TS24011Msg_RP_PDU* asn1Test_TS24011Msg_RP_PDU (OSCTXT* pctxt)
{
   TS24011Msg_RP_PDU* pvalue = rtxMemAllocType (pctxt, TS24011Msg_RP_PDU);
   asn1Init_TS24011Msg_RP_PDU (pvalue);

   pvalue->header.spare = 22;

   pvalue->header.rpMsgType = 2;

   pvalue->header.rpMsgRef = 40;

   switch (pvalue->header.rpMsgType) {
      /* dataToNet */
      case 0:

         pvalue->infoElem.u.dataToNet.origAddrLen = 246;

         pvalue->infoElem.u.dataToNet.destAddress.length = 0; /* length will be calculated */

         pvalue->infoElem.u.dataToNet.destAddress.octet3.typeOfNumber = 3;

         pvalue->infoElem.u.dataToNet.destAddress.octet3.numberingPlanID = 8;

         pvalue->infoElem.u.dataToNet.destAddress.number = "4c##b07";

         {
            pvalue->infoElem.u.dataToNet.userData.numocts = 0;
         }
         break;

      /* dataToMS */
      case 1:

         pvalue->infoElem.u.dataToMS.origAddress.length = 0; /* length will be calculated */

         pvalue->infoElem.u.dataToMS.origAddress.octet3.typeOfNumber = 4;

         pvalue->infoElem.u.dataToMS.origAddress.octet3.numberingPlanID = 10;

         pvalue->infoElem.u.dataToMS.origAddress.number = "b924";

         pvalue->infoElem.u.dataToMS.destAddrLen = 63;

         {
            pvalue->infoElem.u.dataToMS.userData.numocts = 0;
         }
         break;

      /* ackToNet */
      case 2:

         pvalue->infoElem.u.ackToNet.m.userDataPresent = 1;
         {
            pvalue->infoElem.u.ackToNet.userData.numocts = 0;
         }
         break;

      /* ackToMS */
      case 3:

         pvalue->infoElem.u.ackToMS.m.userDataPresent = 1;
         {
            pvalue->infoElem.u.ackToMS.userData.numocts = 0;
         }
         break;

      /* errorToNet */
      case 4:

         pvalue->infoElem.u.errorToNet.rpCause.length = 0; /* length will be calculated */

         pvalue->infoElem.u.errorToNet.rpCause.ext = 0;

         pvalue->infoElem.u.errorToNet.rpCause.causeValue = 107;

         /* zero elements */

         pvalue->infoElem.u.errorToNet.m.userDataPresent = 1;
         {
            pvalue->infoElem.u.errorToNet.userData.numocts = 0;
         }
         break;

      /* errorToMS */
      case 5:

         pvalue->infoElem.u.errorToMS.rpCause.length = 0; /* length will be calculated */

         pvalue->infoElem.u.errorToMS.rpCause.ext = 1;

         pvalue->infoElem.u.errorToMS.rpCause.causeValue = 44;

         /* zero elements */

         pvalue->infoElem.u.errorToMS.m.userDataPresent = 1;
         {
            pvalue->infoElem.u.errorToMS.userData.numocts = 0;
         }
         break;

      /* smma */
      case 6:
         break;

      default: break;
   }
   return (pvalue);
}
