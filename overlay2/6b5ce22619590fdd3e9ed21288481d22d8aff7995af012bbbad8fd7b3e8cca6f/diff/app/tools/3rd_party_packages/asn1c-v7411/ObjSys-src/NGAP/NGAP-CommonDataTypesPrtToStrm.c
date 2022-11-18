/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.4.1.1, Date: 07-Aug-2020.
 */
#include "NGAP-CommonDataTypes.h"
#include "rtsrc/rtPrintToStream.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtsrc/rtBCD.h"
#include "rtxsrc/rtxCommon.h"

int asn1PrtToStrm_Criticality (OSCTXT *pctxt, 
   const char* name, const Criticality* pvalue)
{
   rtxPrintToStream (pctxt, name);
   switch (*pvalue) {
      case 0:
         rtxPrintToStream (pctxt, " = reject\n");
         break;
      case 1:
         rtxPrintToStream (pctxt, " = ignore\n");
         break;
      case 2:
         rtxPrintToStream (pctxt, " = notify\n");
         break;
      default:
         rtxPrintToStream (pctxt," = ???\n");
   }

   return 0;
}

int asn1PrtToStrm_Presence (OSCTXT *pctxt, 
   const char* name, const Presence* pvalue)
{
   rtxPrintToStream (pctxt, name);
   switch (*pvalue) {
      case 0:
         rtxPrintToStream (pctxt, " = optional\n");
         break;
      case 1:
         rtxPrintToStream (pctxt, " = conditional\n");
         break;
      case 2:
         rtxPrintToStream (pctxt, " = mandatory\n");
         break;
      default:
         rtxPrintToStream (pctxt," = ???\n");
   }

   return 0;
}

int asn1PrtToStrm_ProcedureCode (OSCTXT *pctxt, 
   const char* name, const ProcedureCode* pvalue)
{
   rtPrintToStreamUnsigned (pctxt, name, *pvalue);
   return 0;
}

int asn1PrtToStrm_ProtocolExtensionID (OSCTXT *pctxt, 
   const char* name, const ProtocolExtensionID* pvalue)
{
   rtPrintToStreamUnsigned (pctxt, name, *pvalue);
   return 0;
}

int asn1PrtToStrm_ProtocolIE_ID (OSCTXT *pctxt, 
   const char* name, const ProtocolIE_ID* pvalue)
{
   rtPrintToStreamUnsigned (pctxt, name, *pvalue);
   return 0;
}

int asn1PrtToStrm_TriggeringMessage (OSCTXT *pctxt, 
   const char* name, const TriggeringMessage* pvalue)
{
   rtxPrintToStream (pctxt, name);
   switch (*pvalue) {
      case 0:
         rtxPrintToStream (pctxt, " = initiating-message\n");
         break;
      case 1:
         rtxPrintToStream (pctxt, " = successful-outcome\n");
         break;
      case 2:
         rtxPrintToStream (pctxt, " = unsuccessfull-outcome\n");
         break;
      default:
         rtxPrintToStream (pctxt," = ???\n");
   }

   return 0;
}

int asn1PrtToStrm_PrivateIE_ID (OSCTXT *pctxt, 
   const char* name, const PrivateIE_ID* pvalue)
{
   {
      char namebuf[512], numbuf[32];

      rtxIntToCharStr (pvalue->t, numbuf, sizeof(numbuf), 0);
      rtxStrJoin (namebuf, sizeof(namebuf), name, ".t = ", numbuf, "\n", 0);
      rtxPrintToStream (pctxt, namebuf);

      switch (pvalue->t)
      {
         /* local */
         case 1:
         {
            rtxStrJoin (namebuf, 512, name, ".u.local", 0, 0, 0);
            rtPrintToStreamUnsigned (pctxt, namebuf, pvalue->u.local);
            break;
         }
         /* global */
         case 2:
         {
            rtxStrJoin (namebuf, 512, name, ".u.global", 0, 0, 0);
            rtPrintToStreamOID (pctxt, namebuf, pvalue->u.global);
            break;
         }
         default:;
      }
   }
   return 0;
}
