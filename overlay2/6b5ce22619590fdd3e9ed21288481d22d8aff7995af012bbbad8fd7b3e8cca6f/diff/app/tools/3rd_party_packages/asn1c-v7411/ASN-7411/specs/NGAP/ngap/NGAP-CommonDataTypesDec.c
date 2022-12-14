/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.4.1.1, Date: 02-Jun-2020.
 */
#include ".h"
#include "rtxsrc/rtxCommon.h"

EXTERN int asn1PD_Criticality (OSCTXT* pctxt, Criticality* pvalue)
{
   int stat = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "Criticality");

   RTDIAGSTRM2 (pctxt,"asn1PD_Criticality: start\n");

   stat = pd_ConsUnsigned (pctxt, pvalue, 0, OSUINTCONST(2));
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   RTDIAGSTRM2 (pctxt,"asn1PD_Criticality: end\n");

   RTXCTXTPOPTYPENAME (pctxt);

   return (stat);
}

EXTERN int asn1PD_Presence (OSCTXT* pctxt, Presence* pvalue)
{
   int stat = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "Presence");

   RTDIAGSTRM2 (pctxt,"asn1PD_Presence: start\n");

   stat = pd_ConsUnsigned (pctxt, pvalue, 0, OSUINTCONST(2));
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   RTDIAGSTRM2 (pctxt,"asn1PD_Presence: end\n");

   RTXCTXTPOPTYPENAME (pctxt);

   return (stat);
}

EXTERN int asn1PD_ProcedureCode (OSCTXT* pctxt, ProcedureCode* pvalue)
{
   int stat = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "ProcedureCode");

   RTDIAGSTRM2 (pctxt,"asn1PD_ProcedureCode: start\n");

   if (pctxt->buffer.aligned) {
      int stat2 = PD_BYTE_ALIGN (pctxt);
      if (stat2 != 0) return LOG_RTERR (pctxt, stat2);
   }
   PU_NEWFIELD (pctxt, "constrainted int");

   stat = rtxDecBitsToByte (pctxt, pvalue, 8);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   PU_SETBITCOUNT (pctxt);

   RTDIAGSTRM2 (pctxt,"asn1PD_ProcedureCode: end\n");

   RTXCTXTPOPTYPENAME (pctxt);

   return (stat);
}

EXTERN int asn1PD_ProtocolExtensionID (OSCTXT* pctxt, ProtocolExtensionID* pvalue)
{
   int stat = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "ProtocolExtensionID");

   RTDIAGSTRM2 (pctxt,"asn1PD_ProtocolExtensionID: start\n");

   if (pctxt->buffer.aligned) {
      int stat2 = PD_BYTE_ALIGN (pctxt);
      if (stat2 != 0) return LOG_RTERR (pctxt, stat2);
   }
   PU_NEWFIELD (pctxt, "constrainted int");

   stat = rtxDecBitsToUInt16 (pctxt, pvalue, pctxt->buffer.aligned ? 16 : 16);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   PU_SETBITCOUNT (pctxt);

   RTDIAGSTRM2 (pctxt,"asn1PD_ProtocolExtensionID: end\n");

   RTXCTXTPOPTYPENAME (pctxt);

   return (stat);
}

EXTERN int asn1PD_ProtocolIE_ID (OSCTXT* pctxt, ProtocolIE_ID* pvalue)
{
   int stat = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "ProtocolIE-ID");

   RTDIAGSTRM2 (pctxt,"asn1PD_ProtocolIE_ID: start\n");

   if (pctxt->buffer.aligned) {
      int stat2 = PD_BYTE_ALIGN (pctxt);
      if (stat2 != 0) return LOG_RTERR (pctxt, stat2);
   }
   PU_NEWFIELD (pctxt, "constrainted int");

   stat = rtxDecBitsToUInt16 (pctxt, pvalue, pctxt->buffer.aligned ? 16 : 16);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   PU_SETBITCOUNT (pctxt);

   RTDIAGSTRM2 (pctxt,"asn1PD_ProtocolIE_ID: end\n");

   RTXCTXTPOPTYPENAME (pctxt);

   return (stat);
}

EXTERN int asn1PD_TriggeringMessage (OSCTXT* pctxt, TriggeringMessage* pvalue)
{
   int stat = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "TriggeringMessage");

   RTDIAGSTRM2 (pctxt,"asn1PD_TriggeringMessage: start\n");

   stat = pd_ConsUnsigned (pctxt, pvalue, 0, OSUINTCONST(2));
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   RTDIAGSTRM2 (pctxt,"asn1PD_TriggeringMessage: end\n");

   RTXCTXTPOPTYPENAME (pctxt);

   return (stat);
}

EXTERN int asn1PD_PrivateIE_ID (OSCTXT* pctxt, PrivateIE_ID* pvalue)
{
   int stat = 0;
   OSUINT32 ui;

   RTXCTXTPUSHTYPENAME (pctxt, "PrivateIE-ID");

   RTDIAGSTRM2 (pctxt,"asn1PD_PrivateIE_ID: start\n");

   RTXCTXTPUSHELEMNAME (pctxt, "t");
   PU_NEWFIELD (pctxt, "<choice-index>");

   {
      OSBOOL b = 0;
      DEC_BIT (pctxt, &b);
      ui = b;
   }
   pvalue->t = ui + 1;

   PU_SETBITCOUNT (pctxt);
   RTXCTXTPOPELEMNAME (pctxt);

   switch (ui) {
      /* local */
      case 0:
         RTXCTXTPUSHELEMNAME (pctxt, "local");

         if (pctxt->buffer.aligned) {
            int stat2 = PD_BYTE_ALIGN (pctxt);
            if (stat2 != 0) return LOG_RTERR (pctxt, stat2);
         }
         PU_NEWFIELD (pctxt, "constrainted int");

         stat = rtxDecBitsToUInt16 (pctxt, &pvalue->u.local, pctxt->buffer.aligned ? 16 : 16);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         PU_SETBITCOUNT (pctxt);

         RTXCTXTPOPELEMNAME (pctxt);

         break;

      /* global */
      case 1:
         RTXCTXTPUSHELEMNAME (pctxt, "global");

         pvalue->u.global = rtxMemAllocType (pctxt, ASN1OBJID);

         if (pvalue->u.global == NULL)
            return LOG_RTERR (pctxt, RTERR_NOMEM);

         pvalue->u.global->numids = 0;

         stat = pd_ObjectIdentifier (pctxt, pvalue->u.global);
         if (stat != 0) return LOG_RTERR (pctxt, stat);

         RTXCTXTPOPELEMNAME (pctxt);

         break;

      default:
         return LOG_RTERR (pctxt, RTERR_INVOPT);
   }

   RTDIAGSTRM2 (pctxt,"asn1PD_PrivateIE_ID: end\n");

   RTXCTXTPOPTYPENAME (pctxt);

   return (stat);
}

