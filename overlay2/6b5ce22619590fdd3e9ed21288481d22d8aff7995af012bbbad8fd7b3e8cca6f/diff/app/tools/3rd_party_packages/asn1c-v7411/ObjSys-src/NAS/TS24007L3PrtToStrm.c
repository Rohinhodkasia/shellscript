/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.4.1.1, Date: 02-Jun-2020.
 */
#include "TS24007L3.h"
#include "rtsrc/rtPrintToStream.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtsrc/rtBCD.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxDiagBitTrace.h"

int asn1PrtToStrm_TS24007L3_EPSBearerIdentity (OSCTXT *pctxt, 
   const char* name, const TS24007L3_EPSBearerIdentity* pvalue)
{
   rtPrintToStreamIndent (pctxt);
   rtxPrintToStream (pctxt, name);
   switch (*pvalue) {
      case 0:
         rtxPrintToStream (pctxt, " = noIdent\n");
         break;
      case 5:
         rtxPrintToStream (pctxt, " = id5\n");
         break;
      case 6:
         rtxPrintToStream (pctxt, " = id6\n");
         break;
      case 7:
         rtxPrintToStream (pctxt, " = id7\n");
         break;
      case 8:
         rtxPrintToStream (pctxt, " = id8\n");
         break;
      case 9:
         rtxPrintToStream (pctxt, " = id9\n");
         break;
      case 10:
         rtxPrintToStream (pctxt, " = id10\n");
         break;
      case 11:
         rtxPrintToStream (pctxt, " = id11\n");
         break;
      case 12:
         rtxPrintToStream (pctxt, " = id12\n");
         break;
      case 13:
         rtxPrintToStream (pctxt, " = id13\n");
         break;
      case 14:
         rtxPrintToStream (pctxt, " = id14\n");
         break;
      case 15:
         rtxPrintToStream (pctxt, " = id15\n");
         break;
      default:
         rtxPrintToStream (pctxt," = ???\n");
   }

   return 0;
}

int asn1PrtToStrm_TS24007L3_L3HdrOptions (OSCTXT *pctxt, 
   const char* name, const TS24007L3_L3HdrOptions* pvalue)
{
   rtPrintToStreamOpenBrace (pctxt, name);

   switch (pvalue->t)
   {
      /* skipInd */
      case 1:
      {
         rtPrintToStreamIndent (pctxt);
         rtPrintToStreamUnsigned (pctxt, "skipInd", pvalue->u.skipInd);
         break;
      }
      /* transId */
      case 2:
      {
         rtPrintToStreamOpenBrace (pctxt, "transId");

         rtPrintToStreamIndent (pctxt);
         rtPrintToStreamBoolean (pctxt, "flag", pvalue->u.transId.flag);

         rtPrintToStreamIndent (pctxt);
         rtPrintToStreamUnsigned (pctxt, "value", pvalue->u.transId.value);

         rtPrintToStreamCloseBrace (pctxt);
         break;
      }
      /* epsBearerIdent */
      case 3:
      {
         asn1PrtToStrm_TS24007L3_EPSBearerIdentity (pctxt, "epsBearerIdent", &pvalue->u.epsBearerIdent);
         break;
      }
      /* secHdr */
      case 4:
      {
         rtPrintToStreamIndent (pctxt);
         rtPrintToStreamUnsigned (pctxt, "secHdr", pvalue->u.secHdr);
         break;
      }
      default:;
   }

   rtPrintToStreamCloseBrace (pctxt);
   return 0;
}

int asn1PrtToStrm_TS24007L3_ProtoDiscr (OSCTXT *pctxt, 
   const char* name, const TS24007L3_ProtoDiscr* pvalue)
{
   rtPrintToStreamIndent (pctxt);
   rtxPrintToStream (pctxt, name);
   switch (*pvalue) {
      case 0:
         rtxPrintToStream (pctxt, " = gcc\n");
         break;
      case 1:
         rtxPrintToStream (pctxt, " = bcc\n");
         break;
      case 2:
         rtxPrintToStream (pctxt, " = epsSessMgmt\n");
         break;
      case 3:
         rtxPrintToStream (pctxt, " = callCtrl\n");
         break;
      case 4:
         rtxPrintToStream (pctxt, " = gttp\n");
         break;
      case 5:
         rtxPrintToStream (pctxt, " = mobMgmt\n");
         break;
      case 6:
         rtxPrintToStream (pctxt, " = rrMgmt\n");
         break;
      case 7:
         rtxPrintToStream (pctxt, " = epsMobMgmt\n");
         break;
      case 8:
         rtxPrintToStream (pctxt, " = gprsMobMgmt\n");
         break;
      case 9:
         rtxPrintToStream (pctxt, " = sms\n");
         break;
      case 10:
         rtxPrintToStream (pctxt, " = sessMgmt\n");
         break;
      case 11:
         rtxPrintToStream (pctxt, " = nonCallSS\n");
         break;
      case 12:
         rtxPrintToStream (pctxt, " = locnSvcs\n");
         break;
      case 14:
         rtxPrintToStream (pctxt, " = extPduInd\n");
         break;
      case 15:
         rtxPrintToStream (pctxt, " = testProc\n");
         break;
      default:
         rtxPrintToStream (pctxt," = ???\n");
   }

   return 0;
}

int asn1PrtToStrm_TS24007L3_SecHdrType (OSCTXT *pctxt, 
   const char* name, const TS24007L3_SecHdrType* pvalue)
{
   rtPrintToStreamIndent (pctxt);
   rtxPrintToStream (pctxt, name);
   switch (*pvalue) {
      case 0:
         rtxPrintToStream (pctxt, " = noSec\n");
         break;
      case 1:
         rtxPrintToStream (pctxt, " = integProt\n");
         break;
      case 2:
         rtxPrintToStream (pctxt, " = integProtAndCipher\n");
         break;
      case 3:
         rtxPrintToStream (pctxt, " = integProtAndSecCtxt\n");
         break;
      case 4:
         rtxPrintToStream (pctxt, " = integProtAndCipherAndSecCtxt\n");
         break;
      case 5:
         rtxPrintToStream (pctxt, " = integProtAndPartCipher\n");
         break;
      case 12:
         rtxPrintToStream (pctxt, " = secHdrForSvcReq\n");
         break;
      default:
         rtxPrintToStream (pctxt," = ???\n");
   }

   return 0;
}

int asn1PrtToStrm_TS24007L3_Header (OSCTXT *pctxt, 
   const char* name, const TS24007L3_Header* pvalue)
{
   rtPrintToStreamOpenBrace (pctxt, name);

   asn1PrtToStrm_TS24007L3_L3HdrOptions (pctxt, "l3HdrOpts", &pvalue->l3HdrOpts);

   asn1PrtToStrm_TS24007L3_ProtoDiscr (pctxt, "protoDiscr", &pvalue->protoDiscr);

   rtPrintToStreamIndent (pctxt);
   rtPrintToStreamUnsigned (pctxt, "msgType", pvalue->msgType);

   rtPrintToStreamCloseBrace (pctxt);
   return 0;
}

int asn1PrtToStrm_TS24007L3_MsgType_MM_CC_SS (OSCTXT *pctxt, 
   const char* name, const TS24007L3_MsgType_MM_CC_SS* pvalue)
{
   rtPrintToStreamOpenBrace (pctxt, name);

   rtPrintToStreamIndent (pctxt);
   rtPrintToStreamUnsigned (pctxt, "sendSeqNum", pvalue->sendSeqNum);

   rtPrintToStreamIndent (pctxt);
   rtPrintToStreamUnsigned (pctxt, "value", pvalue->value);

   rtPrintToStreamCloseBrace (pctxt);
   return 0;
}

int asn1PrtToStrm_TS24007L3_SecProtMsgHeader (OSCTXT *pctxt, 
   const char* name, const TS24007L3_SecProtMsgHeader* pvalue)
{
   rtPrintToStreamOpenBrace (pctxt, name);

   asn1PrtToStrm_TS24007L3_SecHdrType (pctxt, "secHdrType", &pvalue->secHdrType);

   rtPrintToStreamIndent (pctxt);
   rtPrintToStreamUnsigned (pctxt, "protoDiscr", pvalue->protoDiscr);

   rtPrintToStreamIndent (pctxt);
   rtPrintToStreamUnsigned (pctxt, "msgAuthCode", pvalue->msgAuthCode);

   rtPrintToStreamIndent (pctxt);
   rtPrintToStreamUnsigned (pctxt, "seqNumber", pvalue->seqNumber);

   rtPrintToStreamCloseBrace (pctxt);
   return 0;
}

