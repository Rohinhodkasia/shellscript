/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.4.2.3, Date: 13-Jul-2020.
 */
#include ".h"
#include "rtsrc/rtPrintToString.h"
#include "rtsrc/rtBCD.h"
#include "rtxsrc/rtxCommon.h"

int asn1PrtToStr_Criticality (const char* name, Criticality* pvalue, 
   char* buffer, OSSIZE bufSize)
{
   int stat;
   if(rtPrintToString (name, buffer, bufSize) < 0)
   {
      return -1;
   }
   switch (*pvalue) {
      case 0:
         stat = rtPrintToString (" = reject\n", buffer, bufSize);
         break;

      case 1:
         stat = rtPrintToString (" = ignore\n", buffer, bufSize);
         break;

      case 2:
         stat = rtPrintToString (" = notify\n", buffer, bufSize);
         break;

      default:
      stat = rtPrintToString (" = ???\n", buffer, bufSize);
   }

   if(stat < 0) return -1;
   return 0;
}

int asn1PrtToStr_Presence (const char* name, Presence* pvalue, char* buffer, 
   OSSIZE bufSize)
{
   int stat;
   if(rtPrintToString (name, buffer, bufSize) < 0)
   {
      return -1;
   }
   switch (*pvalue) {
      case 0:
         stat = rtPrintToString (" = optional\n", buffer, bufSize);
         break;

      case 1:
         stat = rtPrintToString (" = conditional\n", buffer, bufSize);
         break;

      case 2:
         stat = rtPrintToString (" = mandatory\n", buffer, bufSize);
         break;

      default:
      stat = rtPrintToString (" = ???\n", buffer, bufSize);
   }

   if(stat < 0) return -1;
   return 0;
}

int asn1PrtToStr_ProcedureCode (const char* name, ProcedureCode* pvalue, 
   char* buffer, OSSIZE bufSize)
{
   if (rtPrintToStringUnsigned (name, *pvalue, buffer, bufSize) < 0)
   {
      return -1;
   }
   return 0;
}

int asn1PrtToStr_ProtocolExtensionID (const char* name, 
   ProtocolExtensionID* pvalue, char* buffer, OSSIZE bufSize)
{
   if (rtPrintToStringUnsigned (name, *pvalue, buffer, bufSize) < 0)
   {
      return -1;
   }
   return 0;
}

int asn1PrtToStr_ProtocolIE_ID (const char* name, ProtocolIE_ID* pvalue, 
   char* buffer, OSSIZE bufSize)
{
   if (rtPrintToStringUnsigned (name, *pvalue, buffer, bufSize) < 0)
   {
      return -1;
   }
   return 0;
}

int asn1PrtToStr_TriggeringMessage (const char* name, 
   TriggeringMessage* pvalue, char* buffer, OSSIZE bufSize)
{
   int stat;
   if(rtPrintToString (name, buffer, bufSize) < 0)
   {
      return -1;
   }
   switch (*pvalue) {
      case 0:
         stat = rtPrintToString (" = initiating-message\n", buffer, bufSize);
         break;

      case 1:
         stat = rtPrintToString (" = successful-outcome\n", buffer, bufSize);
         break;

      case 2:
         stat = rtPrintToString (" = unsuccessfull-outcome\n", buffer, bufSize);
         break;

      default:
      stat = rtPrintToString (" = ???\n", buffer, bufSize);
   }

   if(stat < 0) return -1;
   return 0;
}

int asn1PrtToStr_PrivateIE_ID (const char* name, PrivateIE_ID* pvalue, 
   char* buffer, OSSIZE bufSize)
{
   {
   char namebuf2[512], numbuf[32];

   rtxIntToCharStr (pvalue->t, numbuf, sizeof(numbuf), 0);
   rtxStrJoin (namebuf2, sizeof(namebuf2), name, ".t = ", numbuf, "\n", 0);
   if (rtPrintToString (namebuf2, buffer, bufSize) < 0)
   {
      return -1;
   }

   switch (pvalue->t) {
      /* local */
      case 1:
      {
         rtxStrJoin (namebuf2, 512, name, ".u.local", 0, 0, 0);
         if (rtPrintToStringUnsigned (namebuf2, pvalue->u.local, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* global */
      case 2:
      {
         rtxStrJoin (namebuf2, 512, name, ".u.global", 0, 0, 0);
         if(rtPrintToStringOID (namebuf2, pvalue->u.global, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      default:;
   }
   }
   return 0;
}

