/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.4.2.3, Date: 13-Jul-2020.
 */
#include ".h"
#include "rtsrc/rtPrintToString.h"
#include "rtsrc/rtBCD.h"
#include "rtxsrc/rtxCommon.h"

int asn1PrtToStr_InitiatingMessage (const char* name, 
   InitiatingMessage* pvalue, char* buffer, OSSIZE bufSize)
{
   char namebuf[512];

   rtxStrJoin (namebuf, 512, name, ".procedureCode", 0, 0, 0);
   if (asn1PrtToStr_ProcedureCode (namebuf, &pvalue->procedureCode, buffer, bufSize) < 0)
   {
      return -1;
   }

   rtxStrJoin (namebuf, 512, name, ".criticality", 0, 0, 0);
   if (asn1PrtToStr_Criticality (namebuf, &pvalue->criticality, buffer, bufSize) < 0)
   {
      return -1;
   }

   rtxStrJoin (namebuf, 512, name, ".value", 0, 0, 0);
   {
   char namebuf2[512], numbuf[32];

   rtxIntToCharStr (pvalue->value.t, numbuf, sizeof(numbuf), 0);
   rtxStrJoin (namebuf2, sizeof(namebuf2), namebuf, ".t = ", numbuf, "\n", 0);
   if (rtPrintToString (namebuf2, buffer, bufSize) < 0)
   {
      return -1;
   }

   switch (pvalue->value.t) {
      /* aMFConfigurationUpdate */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_aMFConfigurationUpdate:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.aMFConfigurationUpdate", 0, 0, 0);
         if (asn1PrtToStr_AMFConfigurationUpdate (namebuf2, pvalue->value.u.aMFConfigurationUpdate, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* handoverCancel */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverCancel:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.handoverCancel", 0, 0, 0);
         if (asn1PrtToStr_HandoverCancel (namebuf2, pvalue->value.u.handoverCancel, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* handoverPreparation */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverPreparation:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.handoverPreparation", 0, 0, 0);
         if (asn1PrtToStr_HandoverRequired (namebuf2, pvalue->value.u.handoverPreparation, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* handoverResourceAllocation */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverResourceAllocation:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.handoverResourceAllocation", 0, 0, 0);
         if (asn1PrtToStr_HandoverRequest (namebuf2, pvalue->value.u.handoverResourceAllocation, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* initialContextSetup */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_initialContextSetup:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.initialContextSetup", 0, 0, 0);
         if (asn1PrtToStr_InitialContextSetupRequest (namebuf2, pvalue->value.u.initialContextSetup, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* nGReset */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGReset:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.nGReset", 0, 0, 0);
         if (asn1PrtToStr_NGReset (namebuf2, pvalue->value.u.nGReset, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* nGSetup */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGSetup:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.nGSetup", 0, 0, 0);
         if (asn1PrtToStr_NGSetupRequest (namebuf2, pvalue->value.u.nGSetup, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* pathSwitchRequest */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pathSwitchRequest:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.pathSwitchRequest", 0, 0, 0);
         if (asn1PrtToStr_PathSwitchRequest (namebuf2, pvalue->value.u.pathSwitchRequest, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* pDUSessionResourceModify */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceModify:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.pDUSessionResourceModify", 0, 0, 0);
         if (asn1PrtToStr_PDUSessionResourceModifyRequest (namebuf2, pvalue->value.u.pDUSessionResourceModify, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* pDUSessionResourceModifyIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceModifyIndication:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.pDUSessionResourceModifyIndication", 0, 0, 0);
         if (asn1PrtToStr_PDUSessionResourceModifyIndication (namebuf2, pvalue->value.u.pDUSessionResourceModifyIndication, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* pDUSessionResourceRelease */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceRelease:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.pDUSessionResourceRelease", 0, 0, 0);
         if (asn1PrtToStr_PDUSessionResourceReleaseCommand (namebuf2, pvalue->value.u.pDUSessionResourceRelease, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* pDUSessionResourceSetup */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceSetup:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.pDUSessionResourceSetup", 0, 0, 0);
         if (asn1PrtToStr_PDUSessionResourceSetupRequest (namebuf2, pvalue->value.u.pDUSessionResourceSetup, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* pWSCancel */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pWSCancel:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.pWSCancel", 0, 0, 0);
         if (asn1PrtToStr_PWSCancelRequest (namebuf2, pvalue->value.u.pWSCancel, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* rANConfigurationUpdate */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rANConfigurationUpdate:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.rANConfigurationUpdate", 0, 0, 0);
         if (asn1PrtToStr_RANConfigurationUpdate (namebuf2, pvalue->value.u.rANConfigurationUpdate, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* uEContextModification */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextModification:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.uEContextModification", 0, 0, 0);
         if (asn1PrtToStr_UEContextModificationRequest (namebuf2, pvalue->value.u.uEContextModification, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* uEContextRelease */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextRelease:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.uEContextRelease", 0, 0, 0);
         if (asn1PrtToStr_UEContextReleaseCommand (namebuf2, pvalue->value.u.uEContextRelease, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* uERadioCapabilityCheck */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uERadioCapabilityCheck:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.uERadioCapabilityCheck", 0, 0, 0);
         if (asn1PrtToStr_UERadioCapabilityCheckRequest (namebuf2, pvalue->value.u.uERadioCapabilityCheck, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* writeReplaceWarning */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_writeReplaceWarning:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.writeReplaceWarning", 0, 0, 0);
         if (asn1PrtToStr_WriteReplaceWarningRequest (namebuf2, pvalue->value.u.writeReplaceWarning, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* aMFStatusIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_aMFStatusIndication:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.aMFStatusIndication", 0, 0, 0);
         if (asn1PrtToStr_AMFStatusIndication (namebuf2, pvalue->value.u.aMFStatusIndication, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* cellTrafficTrace */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_cellTrafficTrace:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.cellTrafficTrace", 0, 0, 0);
         if (asn1PrtToStr_CellTrafficTrace (namebuf2, pvalue->value.u.cellTrafficTrace, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* deactivateTrace */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_deactivateTrace:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.deactivateTrace", 0, 0, 0);
         if (asn1PrtToStr_DeactivateTrace (namebuf2, pvalue->value.u.deactivateTrace, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* downlinkNASTransport */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkNASTransport:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.downlinkNASTransport", 0, 0, 0);
         if (asn1PrtToStr_DownlinkNASTransport (namebuf2, pvalue->value.u.downlinkNASTransport, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* downlinkNonUEAssociatedNRPPaTransport */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkNonUEAssociatedNRPPaTransport:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.downlinkNonUEAssociatedNRPPaTransport", 0, 0, 0);
         if (asn1PrtToStr_DownlinkNonUEAssociatedNRPPaTransport (namebuf2, pvalue->value.u.downlinkNonUEAssociatedNRPPaTransport, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* downlinkRANConfigurationTransfer */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkRANConfigurationTransfer:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.downlinkRANConfigurationTransfer", 0, 0, 0);
         if (asn1PrtToStr_DownlinkRANConfigurationTransfer (namebuf2, pvalue->value.u.downlinkRANConfigurationTransfer, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* downlinkRANStatusTransfer */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkRANStatusTransfer:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.downlinkRANStatusTransfer", 0, 0, 0);
         if (asn1PrtToStr_DownlinkRANStatusTransfer (namebuf2, pvalue->value.u.downlinkRANStatusTransfer, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* downlinkUEAssociatedNRPPaTransport */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkUEAssociatedNRPPaTransport:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.downlinkUEAssociatedNRPPaTransport", 0, 0, 0);
         if (asn1PrtToStr_DownlinkUEAssociatedNRPPaTransport (namebuf2, pvalue->value.u.downlinkUEAssociatedNRPPaTransport, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* errorIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_errorIndication:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.errorIndication", 0, 0, 0);
         if (asn1PrtToStr_ErrorIndication (namebuf2, pvalue->value.u.errorIndication, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* handoverNotification */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverNotification:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.handoverNotification", 0, 0, 0);
         if (asn1PrtToStr_HandoverNotify (namebuf2, pvalue->value.u.handoverNotification, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* initialUEMessage */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_initialUEMessage:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.initialUEMessage", 0, 0, 0);
         if (asn1PrtToStr_InitialUEMessage (namebuf2, pvalue->value.u.initialUEMessage, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* locationReport */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_locationReport:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.locationReport", 0, 0, 0);
         if (asn1PrtToStr_LocationReport (namebuf2, pvalue->value.u.locationReport, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* locationReportingControl */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_locationReportingControl:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.locationReportingControl", 0, 0, 0);
         if (asn1PrtToStr_LocationReportingControl (namebuf2, pvalue->value.u.locationReportingControl, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* locationReportingFailureIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_locationReportingFailureIndication:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.locationReportingFailureIndication", 0, 0, 0);
         if (asn1PrtToStr_LocationReportingFailureIndication (namebuf2, pvalue->value.u.locationReportingFailureIndication, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* nASNonDeliveryIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nASNonDeliveryIndication:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.nASNonDeliveryIndication", 0, 0, 0);
         if (asn1PrtToStr_NASNonDeliveryIndication (namebuf2, pvalue->value.u.nASNonDeliveryIndication, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* overloadStart */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_overloadStart:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.overloadStart", 0, 0, 0);
         if (asn1PrtToStr_OverloadStart (namebuf2, pvalue->value.u.overloadStart, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* overloadStop */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_overloadStop:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.overloadStop", 0, 0, 0);
         if (asn1PrtToStr_OverloadStop (namebuf2, pvalue->value.u.overloadStop, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* paging */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_paging:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.paging", 0, 0, 0);
         if (asn1PrtToStr_Paging (namebuf2, pvalue->value.u.paging, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* pDUSessionResourceNotify */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceNotify:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.pDUSessionResourceNotify", 0, 0, 0);
         if (asn1PrtToStr_PDUSessionResourceNotify (namebuf2, pvalue->value.u.pDUSessionResourceNotify, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* privateMessage */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_privateMessage:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.privateMessage", 0, 0, 0);
         if (asn1PrtToStr_PrivateMessage (namebuf2, pvalue->value.u.privateMessage, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* pWSFailureIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pWSFailureIndication:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.pWSFailureIndication", 0, 0, 0);
         if (asn1PrtToStr_PWSFailureIndication (namebuf2, pvalue->value.u.pWSFailureIndication, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* pWSRestartIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pWSRestartIndication:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.pWSRestartIndication", 0, 0, 0);
         if (asn1PrtToStr_PWSRestartIndication (namebuf2, pvalue->value.u.pWSRestartIndication, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* rerouteNASRequest */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rerouteNASRequest:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.rerouteNASRequest", 0, 0, 0);
         if (asn1PrtToStr_RerouteNASRequest (namebuf2, pvalue->value.u.rerouteNASRequest, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* rRCInactiveTransitionReport */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rRCInactiveTransitionReport:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.rRCInactiveTransitionReport", 0, 0, 0);
         if (asn1PrtToStr_RRCInactiveTransitionReport (namebuf2, pvalue->value.u.rRCInactiveTransitionReport, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* secondaryRATDataUsageReport */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_secondaryRATDataUsageReport:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.secondaryRATDataUsageReport", 0, 0, 0);
         if (asn1PrtToStr_SecondaryRATDataUsageReport (namebuf2, pvalue->value.u.secondaryRATDataUsageReport, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* traceFailureIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_traceFailureIndication:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.traceFailureIndication", 0, 0, 0);
         if (asn1PrtToStr_TraceFailureIndication (namebuf2, pvalue->value.u.traceFailureIndication, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* traceStart */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_traceStart:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.traceStart", 0, 0, 0);
         if (asn1PrtToStr_TraceStart (namebuf2, pvalue->value.u.traceStart, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* uEContextReleaseRequest */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextReleaseRequest:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.uEContextReleaseRequest", 0, 0, 0);
         if (asn1PrtToStr_UEContextReleaseRequest (namebuf2, pvalue->value.u.uEContextReleaseRequest, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* uERadioCapabilityInfoIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uERadioCapabilityInfoIndication:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.uERadioCapabilityInfoIndication", 0, 0, 0);
         if (asn1PrtToStr_UERadioCapabilityInfoIndication (namebuf2, pvalue->value.u.uERadioCapabilityInfoIndication, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* uETNLABindingRelease */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uETNLABindingRelease:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.uETNLABindingRelease", 0, 0, 0);
         if (asn1PrtToStr_UETNLABindingReleaseRequest (namebuf2, pvalue->value.u.uETNLABindingRelease, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* uplinkNASTransport */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkNASTransport:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.uplinkNASTransport", 0, 0, 0);
         if (asn1PrtToStr_UplinkNASTransport (namebuf2, pvalue->value.u.uplinkNASTransport, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* uplinkNonUEAssociatedNRPPaTransport */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkNonUEAssociatedNRPPaTransport:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.uplinkNonUEAssociatedNRPPaTransport", 0, 0, 0);
         if (asn1PrtToStr_UplinkNonUEAssociatedNRPPaTransport (namebuf2, pvalue->value.u.uplinkNonUEAssociatedNRPPaTransport, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* uplinkRANConfigurationTransfer */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkRANConfigurationTransfer:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.uplinkRANConfigurationTransfer", 0, 0, 0);
         if (asn1PrtToStr_UplinkRANConfigurationTransfer (namebuf2, pvalue->value.u.uplinkRANConfigurationTransfer, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* uplinkRANStatusTransfer */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkRANStatusTransfer:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.uplinkRANStatusTransfer", 0, 0, 0);
         if (asn1PrtToStr_UplinkRANStatusTransfer (namebuf2, pvalue->value.u.uplinkRANStatusTransfer, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* uplinkUEAssociatedNRPPaTransport */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkUEAssociatedNRPPaTransport:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.uplinkUEAssociatedNRPPaTransport", 0, 0, 0);
         if (asn1PrtToStr_UplinkUEAssociatedNRPPaTransport (namebuf2, pvalue->value.u.uplinkUEAssociatedNRPPaTransport, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      default: {
         if (0 != pvalue->value.u.extElem1) {
            rtPrintToStringOpenType ("extElem1", pvalue->value.u.extElem1->numocts, pvalue->value.u.extElem1->data, ".", buffer, bufSize);
         }
      }
   }
   }

   return 0;
}

int asn1PrtToStr_SuccessfulOutcome (const char* name, 
   SuccessfulOutcome* pvalue, char* buffer, OSSIZE bufSize)
{
   char namebuf[512];

   rtxStrJoin (namebuf, 512, name, ".procedureCode", 0, 0, 0);
   if (asn1PrtToStr_ProcedureCode (namebuf, &pvalue->procedureCode, buffer, bufSize) < 0)
   {
      return -1;
   }

   rtxStrJoin (namebuf, 512, name, ".criticality", 0, 0, 0);
   if (asn1PrtToStr_Criticality (namebuf, &pvalue->criticality, buffer, bufSize) < 0)
   {
      return -1;
   }

   rtxStrJoin (namebuf, 512, name, ".value", 0, 0, 0);
   {
   char namebuf2[512], numbuf[32];

   rtxIntToCharStr (pvalue->value.t, numbuf, sizeof(numbuf), 0);
   rtxStrJoin (namebuf2, sizeof(namebuf2), namebuf, ".t = ", numbuf, "\n", 0);
   if (rtPrintToString (namebuf2, buffer, bufSize) < 0)
   {
      return -1;
   }

   switch (pvalue->value.t) {
      /* aMFConfigurationUpdate */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_aMFConfigurationUpdate:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.aMFConfigurationUpdate", 0, 0, 0);
         if (asn1PrtToStr_AMFConfigurationUpdateAcknowledge (namebuf2, pvalue->value.u.aMFConfigurationUpdate, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* handoverCancel */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverCancel:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.handoverCancel", 0, 0, 0);
         if (asn1PrtToStr_HandoverCancelAcknowledge (namebuf2, pvalue->value.u.handoverCancel, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* handoverPreparation */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverPreparation:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.handoverPreparation", 0, 0, 0);
         if (asn1PrtToStr_HandoverCommand (namebuf2, pvalue->value.u.handoverPreparation, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* handoverResourceAllocation */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverResourceAllocation:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.handoverResourceAllocation", 0, 0, 0);
         if (asn1PrtToStr_HandoverRequestAcknowledge (namebuf2, pvalue->value.u.handoverResourceAllocation, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* initialContextSetup */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_initialContextSetup:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.initialContextSetup", 0, 0, 0);
         if (asn1PrtToStr_InitialContextSetupResponse (namebuf2, pvalue->value.u.initialContextSetup, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* nGReset */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGReset:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.nGReset", 0, 0, 0);
         if (asn1PrtToStr_NGResetAcknowledge (namebuf2, pvalue->value.u.nGReset, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* nGSetup */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGSetup:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.nGSetup", 0, 0, 0);
         if (asn1PrtToStr_NGSetupResponse (namebuf2, pvalue->value.u.nGSetup, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* pathSwitchRequest */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pathSwitchRequest:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.pathSwitchRequest", 0, 0, 0);
         if (asn1PrtToStr_PathSwitchRequestAcknowledge (namebuf2, pvalue->value.u.pathSwitchRequest, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* pDUSessionResourceModify */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceModify:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.pDUSessionResourceModify", 0, 0, 0);
         if (asn1PrtToStr_PDUSessionResourceModifyResponse (namebuf2, pvalue->value.u.pDUSessionResourceModify, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* pDUSessionResourceModifyIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceModifyIndication:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.pDUSessionResourceModifyIndication", 0, 0, 0);
         if (asn1PrtToStr_PDUSessionResourceModifyConfirm (namebuf2, pvalue->value.u.pDUSessionResourceModifyIndication, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* pDUSessionResourceRelease */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceRelease:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.pDUSessionResourceRelease", 0, 0, 0);
         if (asn1PrtToStr_PDUSessionResourceReleaseResponse (namebuf2, pvalue->value.u.pDUSessionResourceRelease, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* pDUSessionResourceSetup */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceSetup:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.pDUSessionResourceSetup", 0, 0, 0);
         if (asn1PrtToStr_PDUSessionResourceSetupResponse (namebuf2, pvalue->value.u.pDUSessionResourceSetup, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* pWSCancel */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pWSCancel:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.pWSCancel", 0, 0, 0);
         if (asn1PrtToStr_PWSCancelResponse (namebuf2, pvalue->value.u.pWSCancel, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* rANConfigurationUpdate */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rANConfigurationUpdate:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.rANConfigurationUpdate", 0, 0, 0);
         if (asn1PrtToStr_RANConfigurationUpdateAcknowledge (namebuf2, pvalue->value.u.rANConfigurationUpdate, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* uEContextModification */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextModification:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.uEContextModification", 0, 0, 0);
         if (asn1PrtToStr_UEContextModificationResponse (namebuf2, pvalue->value.u.uEContextModification, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* uEContextRelease */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextRelease:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.uEContextRelease", 0, 0, 0);
         if (asn1PrtToStr_UEContextReleaseComplete (namebuf2, pvalue->value.u.uEContextRelease, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* uERadioCapabilityCheck */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uERadioCapabilityCheck:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.uERadioCapabilityCheck", 0, 0, 0);
         if (asn1PrtToStr_UERadioCapabilityCheckResponse (namebuf2, pvalue->value.u.uERadioCapabilityCheck, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* writeReplaceWarning */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_writeReplaceWarning:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.writeReplaceWarning", 0, 0, 0);
         if (asn1PrtToStr_WriteReplaceWarningResponse (namebuf2, pvalue->value.u.writeReplaceWarning, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      default: {
         if (0 != pvalue->value.u.extElem1) {
            rtPrintToStringOpenType ("extElem1", pvalue->value.u.extElem1->numocts, pvalue->value.u.extElem1->data, ".", buffer, bufSize);
         }
      }
   }
   }

   return 0;
}

int asn1PrtToStr_UnsuccessfulOutcome (const char* name, 
   UnsuccessfulOutcome* pvalue, char* buffer, OSSIZE bufSize)
{
   char namebuf[512];

   rtxStrJoin (namebuf, 512, name, ".procedureCode", 0, 0, 0);
   if (asn1PrtToStr_ProcedureCode (namebuf, &pvalue->procedureCode, buffer, bufSize) < 0)
   {
      return -1;
   }

   rtxStrJoin (namebuf, 512, name, ".criticality", 0, 0, 0);
   if (asn1PrtToStr_Criticality (namebuf, &pvalue->criticality, buffer, bufSize) < 0)
   {
      return -1;
   }

   rtxStrJoin (namebuf, 512, name, ".value", 0, 0, 0);
   {
   char namebuf2[512], numbuf[32];

   rtxIntToCharStr (pvalue->value.t, numbuf, sizeof(numbuf), 0);
   rtxStrJoin (namebuf2, sizeof(namebuf2), namebuf, ".t = ", numbuf, "\n", 0);
   if (rtPrintToString (namebuf2, buffer, bufSize) < 0)
   {
      return -1;
   }

   switch (pvalue->value.t) {
      /* aMFConfigurationUpdate */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_aMFConfigurationUpdate:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.aMFConfigurationUpdate", 0, 0, 0);
         if (asn1PrtToStr_AMFConfigurationUpdateFailure (namebuf2, pvalue->value.u.aMFConfigurationUpdate, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* handoverPreparation */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverPreparation:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.handoverPreparation", 0, 0, 0);
         if (asn1PrtToStr_HandoverPreparationFailure (namebuf2, pvalue->value.u.handoverPreparation, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* handoverResourceAllocation */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverResourceAllocation:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.handoverResourceAllocation", 0, 0, 0);
         if (asn1PrtToStr_HandoverFailure (namebuf2, pvalue->value.u.handoverResourceAllocation, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* initialContextSetup */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_initialContextSetup:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.initialContextSetup", 0, 0, 0);
         if (asn1PrtToStr_InitialContextSetupFailure (namebuf2, pvalue->value.u.initialContextSetup, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* nGSetup */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGSetup:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.nGSetup", 0, 0, 0);
         if (asn1PrtToStr_NGSetupFailure (namebuf2, pvalue->value.u.nGSetup, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* pathSwitchRequest */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pathSwitchRequest:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.pathSwitchRequest", 0, 0, 0);
         if (asn1PrtToStr_PathSwitchRequestFailure (namebuf2, pvalue->value.u.pathSwitchRequest, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* rANConfigurationUpdate */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rANConfigurationUpdate:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.rANConfigurationUpdate", 0, 0, 0);
         if (asn1PrtToStr_RANConfigurationUpdateFailure (namebuf2, pvalue->value.u.rANConfigurationUpdate, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* uEContextModification */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextModification:
      {
         rtxStrJoin (namebuf2, 512, namebuf, "->u.uEContextModification", 0, 0, 0);
         if (asn1PrtToStr_UEContextModificationFailure (namebuf2, pvalue->value.u.uEContextModification, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      default: {
         if (0 != pvalue->value.u.extElem1) {
            rtPrintToStringOpenType ("extElem1", pvalue->value.u.extElem1->numocts, pvalue->value.u.extElem1->data, ".", buffer, bufSize);
         }
      }
   }
   }

   return 0;
}

int asn1PrtToStr_NGAP_PDU (const char* name, NGAP_PDU* pvalue, char* buffer, 
   OSSIZE bufSize)
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
      /* initiatingMessage */
      case 1:
      {
         rtxStrJoin (namebuf2, 512, name, ".u.initiatingMessage", 0, 0, 0);
         if (asn1PrtToStr_InitiatingMessage (namebuf2, pvalue->u.initiatingMessage, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* successfulOutcome */
      case 2:
      {
         rtxStrJoin (namebuf2, 512, name, ".u.successfulOutcome", 0, 0, 0);
         if (asn1PrtToStr_SuccessfulOutcome (namebuf2, pvalue->u.successfulOutcome, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* unsuccessfulOutcome */
      case 3:
      {
         rtxStrJoin (namebuf2, 512, name, ".u.unsuccessfulOutcome", 0, 0, 0);
         if (asn1PrtToStr_UnsuccessfulOutcome (namebuf2, pvalue->u.unsuccessfulOutcome, buffer, bufSize) < 0)
         {
            return -1;
         }
         break;
      }
      /* extElem1 */
      case 4:
      {
         rtxStrJoin (namebuf2, 512, name, ".u.extElem1", 0, 0, 0);
         if(rtPrintToStringOpenType (namebuf2, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data, ".", buffer, bufSize) < 0)
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

