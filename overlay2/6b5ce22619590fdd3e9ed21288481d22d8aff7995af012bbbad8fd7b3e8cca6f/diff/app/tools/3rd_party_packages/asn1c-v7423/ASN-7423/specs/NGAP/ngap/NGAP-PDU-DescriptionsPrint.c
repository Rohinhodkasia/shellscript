/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.4.2.3, Date: 13-Jul-2020.
 */
#include ".h"
#include "rtsrc/rtPrint.h"
#include "rtsrc/rtBCD.h"
#include "rtxsrc/rtxCommon.h"

void asn1Print_InitiatingMessage 
   (const char* name, const InitiatingMessage* pvalue)
{
   char namebuf[512];

   rtxStrJoin (namebuf, 512, name, ".procedureCode", 0, 0, 0);
   asn1Print_ProcedureCode (namebuf, &pvalue->procedureCode);

   rtxStrJoin (namebuf, 512, name, ".criticality", 0, 0, 0);
   asn1Print_Criticality (namebuf, &pvalue->criticality);

   rtxStrJoin (namebuf, 512, name, ".value", 0, 0, 0);
   printf ("%s.t = %d\n", namebuf, pvalue->value.t);
   switch (pvalue->value.t)
   {
      /* aMFConfigurationUpdate */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_aMFConfigurationUpdate:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.aMFConfigurationUpdate", 0, 0, 0);
         asn1Print_AMFConfigurationUpdate (namebuf, pvalue->value.
            u.aMFConfigurationUpdate);
         break;
      }
      /* handoverCancel */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverCancel:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.handoverCancel", 0, 0, 0);
         asn1Print_HandoverCancel (namebuf, pvalue->value.u.handoverCancel);
         break;
      }
      /* handoverPreparation */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverPreparation:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.handoverPreparation", 0, 0, 0);
         asn1Print_HandoverRequired (namebuf, pvalue->value.
            u.handoverPreparation);
         break;
      }
      /* handoverResourceAllocation */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverResourceAllocation:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.handoverResourceAllocation", 0, 0, 0);
         asn1Print_HandoverRequest (namebuf, pvalue->value.
            u.handoverResourceAllocation);
         break;
      }
      /* initialContextSetup */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_initialContextSetup:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.initialContextSetup", 0, 0, 0);
         asn1Print_InitialContextSetupRequest (namebuf, pvalue->value.
            u.initialContextSetup);
         break;
      }
      /* nGReset */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGReset:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.nGReset", 0, 0, 0);
         asn1Print_NGReset (namebuf, pvalue->value.u.nGReset);
         break;
      }
      /* nGSetup */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGSetup:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.nGSetup", 0, 0, 0);
         asn1Print_NGSetupRequest (namebuf, pvalue->value.u.nGSetup);
         break;
      }
      /* pathSwitchRequest */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pathSwitchRequest:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.pathSwitchRequest", 0, 0, 0);
         asn1Print_PathSwitchRequest (namebuf, pvalue->value.
            u.pathSwitchRequest);
         break;
      }
      /* pDUSessionResourceModify */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceModify:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.pDUSessionResourceModify", 0, 0, 0);
         asn1Print_PDUSessionResourceModifyRequest (namebuf, pvalue->value.
            u.pDUSessionResourceModify);
         break;
      }
      /* pDUSessionResourceModifyIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceModifyIndication:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.pDUSessionResourceModifyIndication", 0, 0, 0);
         asn1Print_PDUSessionResourceModifyIndication (namebuf, pvalue->value.
            u.pDUSessionResourceModifyIndication);
         break;
      }
      /* pDUSessionResourceRelease */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceRelease:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.pDUSessionResourceRelease", 0, 0, 0);
         asn1Print_PDUSessionResourceReleaseCommand (namebuf, pvalue->value.
            u.pDUSessionResourceRelease);
         break;
      }
      /* pDUSessionResourceSetup */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceSetup:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.pDUSessionResourceSetup", 0, 0, 0);
         asn1Print_PDUSessionResourceSetupRequest (namebuf, pvalue->value.
            u.pDUSessionResourceSetup);
         break;
      }
      /* pWSCancel */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pWSCancel:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.pWSCancel", 0, 0, 0);
         asn1Print_PWSCancelRequest (namebuf, pvalue->value.u.pWSCancel);
         break;
      }
      /* rANConfigurationUpdate */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rANConfigurationUpdate:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.rANConfigurationUpdate", 0, 0, 0);
         asn1Print_RANConfigurationUpdate (namebuf, pvalue->value.
            u.rANConfigurationUpdate);
         break;
      }
      /* uEContextModification */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextModification:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.uEContextModification", 0, 0, 0);
         asn1Print_UEContextModificationRequest (namebuf, pvalue->value.
            u.uEContextModification);
         break;
      }
      /* uEContextRelease */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextRelease:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.uEContextRelease", 0, 0, 0);
         asn1Print_UEContextReleaseCommand (namebuf, pvalue->value.
            u.uEContextRelease);
         break;
      }
      /* uERadioCapabilityCheck */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uERadioCapabilityCheck:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.uERadioCapabilityCheck", 0, 0, 0);
         asn1Print_UERadioCapabilityCheckRequest (namebuf, pvalue->value.
            u.uERadioCapabilityCheck);
         break;
      }
      /* writeReplaceWarning */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_writeReplaceWarning:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.writeReplaceWarning", 0, 0, 0);
         asn1Print_WriteReplaceWarningRequest (namebuf, pvalue->value.
            u.writeReplaceWarning);
         break;
      }
      /* aMFStatusIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_aMFStatusIndication:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.aMFStatusIndication", 0, 0, 0);
         asn1Print_AMFStatusIndication (namebuf, pvalue->value.
            u.aMFStatusIndication);
         break;
      }
      /* cellTrafficTrace */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_cellTrafficTrace:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.cellTrafficTrace", 0, 0, 0);
         asn1Print_CellTrafficTrace (namebuf, pvalue->value.u.cellTrafficTrace
            );
         break;
      }
      /* deactivateTrace */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_deactivateTrace:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.deactivateTrace", 0, 0, 0);
         asn1Print_DeactivateTrace (namebuf, pvalue->value.u.deactivateTrace);
         break;
      }
      /* downlinkNASTransport */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkNASTransport:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.downlinkNASTransport", 0, 0, 0);
         asn1Print_DownlinkNASTransport (namebuf, pvalue->value.
            u.downlinkNASTransport);
         break;
      }
      /* downlinkNonUEAssociatedNRPPaTransport */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkNonUEAssociatedNRPPaTransport:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.downlinkNonUEAssociatedNRPPaTransport", 0, 0, 0);
         asn1Print_DownlinkNonUEAssociatedNRPPaTransport (namebuf, pvalue->
            value.u.downlinkNonUEAssociatedNRPPaTransport);
         break;
      }
      /* downlinkRANConfigurationTransfer */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkRANConfigurationTransfer:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.downlinkRANConfigurationTransfer", 0, 0, 0);
         asn1Print_DownlinkRANConfigurationTransfer (namebuf, pvalue->value.
            u.downlinkRANConfigurationTransfer);
         break;
      }
      /* downlinkRANStatusTransfer */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkRANStatusTransfer:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.downlinkRANStatusTransfer", 0, 0, 0);
         asn1Print_DownlinkRANStatusTransfer (namebuf, pvalue->value.
            u.downlinkRANStatusTransfer);
         break;
      }
      /* downlinkUEAssociatedNRPPaTransport */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkUEAssociatedNRPPaTransport:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.downlinkUEAssociatedNRPPaTransport", 0, 0, 0);
         asn1Print_DownlinkUEAssociatedNRPPaTransport (namebuf, pvalue->value.
            u.downlinkUEAssociatedNRPPaTransport);
         break;
      }
      /* errorIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_errorIndication:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.errorIndication", 0, 0, 0);
         asn1Print_ErrorIndication (namebuf, pvalue->value.u.errorIndication);
         break;
      }
      /* handoverNotification */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverNotification:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.handoverNotification", 0, 0, 0);
         asn1Print_HandoverNotify (namebuf, pvalue->value.
            u.handoverNotification);
         break;
      }
      /* initialUEMessage */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_initialUEMessage:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.initialUEMessage", 0, 0, 0);
         asn1Print_InitialUEMessage (namebuf, pvalue->value.u.initialUEMessage
            );
         break;
      }
      /* locationReport */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_locationReport:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.locationReport", 0, 0, 0);
         asn1Print_LocationReport (namebuf, pvalue->value.u.locationReport);
         break;
      }
      /* locationReportingControl */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_locationReportingControl:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.locationReportingControl", 0, 0, 0);
         asn1Print_LocationReportingControl (namebuf, pvalue->value.
            u.locationReportingControl);
         break;
      }
      /* locationReportingFailureIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_locationReportingFailureIndication:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.locationReportingFailureIndication", 0, 0, 0);
         asn1Print_LocationReportingFailureIndication (namebuf, pvalue->value.
            u.locationReportingFailureIndication);
         break;
      }
      /* nASNonDeliveryIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nASNonDeliveryIndication:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.nASNonDeliveryIndication", 0, 0, 0);
         asn1Print_NASNonDeliveryIndication (namebuf, pvalue->value.
            u.nASNonDeliveryIndication);
         break;
      }
      /* overloadStart */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_overloadStart:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.overloadStart", 0, 0, 0);
         asn1Print_OverloadStart (namebuf, pvalue->value.u.overloadStart);
         break;
      }
      /* overloadStop */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_overloadStop:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.overloadStop", 0, 0, 0);
         asn1Print_OverloadStop (namebuf, pvalue->value.u.overloadStop);
         break;
      }
      /* paging */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_paging:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.paging", 0, 0, 0);
         asn1Print_Paging (namebuf, pvalue->value.u.paging);
         break;
      }
      /* pDUSessionResourceNotify */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceNotify:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.pDUSessionResourceNotify", 0, 0, 0);
         asn1Print_PDUSessionResourceNotify (namebuf, pvalue->value.
            u.pDUSessionResourceNotify);
         break;
      }
      /* privateMessage */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_privateMessage:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.privateMessage", 0, 0, 0);
         asn1Print_PrivateMessage (namebuf, pvalue->value.u.privateMessage);
         break;
      }
      /* pWSFailureIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pWSFailureIndication:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.pWSFailureIndication", 0, 0, 0);
         asn1Print_PWSFailureIndication (namebuf, pvalue->value.
            u.pWSFailureIndication);
         break;
      }
      /* pWSRestartIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pWSRestartIndication:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.pWSRestartIndication", 0, 0, 0);
         asn1Print_PWSRestartIndication (namebuf, pvalue->value.
            u.pWSRestartIndication);
         break;
      }
      /* rerouteNASRequest */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rerouteNASRequest:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.rerouteNASRequest", 0, 0, 0);
         asn1Print_RerouteNASRequest (namebuf, pvalue->value.
            u.rerouteNASRequest);
         break;
      }
      /* rRCInactiveTransitionReport */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rRCInactiveTransitionReport:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.rRCInactiveTransitionReport", 0, 0, 0);
         asn1Print_RRCInactiveTransitionReport (namebuf, pvalue->value.
            u.rRCInactiveTransitionReport);
         break;
      }
      /* secondaryRATDataUsageReport */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_secondaryRATDataUsageReport:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.secondaryRATDataUsageReport", 0, 0, 0);
         asn1Print_SecondaryRATDataUsageReport (namebuf, pvalue->value.
            u.secondaryRATDataUsageReport);
         break;
      }
      /* traceFailureIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_traceFailureIndication:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.traceFailureIndication", 0, 0, 0);
         asn1Print_TraceFailureIndication (namebuf, pvalue->value.
            u.traceFailureIndication);
         break;
      }
      /* traceStart */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_traceStart:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.traceStart", 0, 0, 0);
         asn1Print_TraceStart (namebuf, pvalue->value.u.traceStart);
         break;
      }
      /* uEContextReleaseRequest */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextReleaseRequest:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.uEContextReleaseRequest", 0, 0, 0);
         asn1Print_UEContextReleaseRequest (namebuf, pvalue->value.
            u.uEContextReleaseRequest);
         break;
      }
      /* uERadioCapabilityInfoIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uERadioCapabilityInfoIndication:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.uERadioCapabilityInfoIndication", 0, 0, 0);
         asn1Print_UERadioCapabilityInfoIndication (namebuf, pvalue->value.
            u.uERadioCapabilityInfoIndication);
         break;
      }
      /* uETNLABindingRelease */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uETNLABindingRelease:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.uETNLABindingRelease", 0, 0, 0);
         asn1Print_UETNLABindingReleaseRequest (namebuf, pvalue->value.
            u.uETNLABindingRelease);
         break;
      }
      /* uplinkNASTransport */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkNASTransport:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.uplinkNASTransport", 0, 0, 0);
         asn1Print_UplinkNASTransport (namebuf, pvalue->value.
            u.uplinkNASTransport);
         break;
      }
      /* uplinkNonUEAssociatedNRPPaTransport */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkNonUEAssociatedNRPPaTransport:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.uplinkNonUEAssociatedNRPPaTransport", 0, 0, 0);
         asn1Print_UplinkNonUEAssociatedNRPPaTransport (namebuf, pvalue->value.
            u.uplinkNonUEAssociatedNRPPaTransport);
         break;
      }
      /* uplinkRANConfigurationTransfer */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkRANConfigurationTransfer:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.uplinkRANConfigurationTransfer", 0, 0, 0);
         asn1Print_UplinkRANConfigurationTransfer (namebuf, pvalue->value.
            u.uplinkRANConfigurationTransfer);
         break;
      }
      /* uplinkRANStatusTransfer */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkRANStatusTransfer:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.uplinkRANStatusTransfer", 0, 0, 0);
         asn1Print_UplinkRANStatusTransfer (namebuf, pvalue->value.
            u.uplinkRANStatusTransfer);
         break;
      }
      /* uplinkUEAssociatedNRPPaTransport */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkUEAssociatedNRPPaTransport:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.uplinkUEAssociatedNRPPaTransport", 0, 0, 0);
         asn1Print_UplinkUEAssociatedNRPPaTransport (namebuf, pvalue->value.
            u.uplinkUEAssociatedNRPPaTransport);
         break;
      }
      default: {
         if (0 != pvalue->value.u.extElem1) {
            rtPrintOpenType ("extElem1", pvalue->value.u.extElem1->numocts, pvalue->value.u.extElem1->data, ".");
         }
      }
   }

}

void asn1Print_SuccessfulOutcome 
   (const char* name, const SuccessfulOutcome* pvalue)
{
   char namebuf[512];

   rtxStrJoin (namebuf, 512, name, ".procedureCode", 0, 0, 0);
   asn1Print_ProcedureCode (namebuf, &pvalue->procedureCode);

   rtxStrJoin (namebuf, 512, name, ".criticality", 0, 0, 0);
   asn1Print_Criticality (namebuf, &pvalue->criticality);

   rtxStrJoin (namebuf, 512, name, ".value", 0, 0, 0);
   printf ("%s.t = %d\n", namebuf, pvalue->value.t);
   switch (pvalue->value.t)
   {
      /* aMFConfigurationUpdate */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_aMFConfigurationUpdate:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.aMFConfigurationUpdate", 0, 0, 0);
         asn1Print_AMFConfigurationUpdateAcknowledge (namebuf, pvalue->value.
            u.aMFConfigurationUpdate);
         break;
      }
      /* handoverCancel */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverCancel:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.handoverCancel", 0, 0, 0);
         asn1Print_HandoverCancelAcknowledge (namebuf, pvalue->value.
            u.handoverCancel);
         break;
      }
      /* handoverPreparation */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverPreparation:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.handoverPreparation", 0, 0, 0);
         asn1Print_HandoverCommand (namebuf, pvalue->value.
            u.handoverPreparation);
         break;
      }
      /* handoverResourceAllocation */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverResourceAllocation:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.handoverResourceAllocation", 0, 0, 0);
         asn1Print_HandoverRequestAcknowledge (namebuf, pvalue->value.
            u.handoverResourceAllocation);
         break;
      }
      /* initialContextSetup */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_initialContextSetup:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.initialContextSetup", 0, 0, 0);
         asn1Print_InitialContextSetupResponse (namebuf, pvalue->value.
            u.initialContextSetup);
         break;
      }
      /* nGReset */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGReset:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.nGReset", 0, 0, 0);
         asn1Print_NGResetAcknowledge (namebuf, pvalue->value.u.nGReset);
         break;
      }
      /* nGSetup */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGSetup:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.nGSetup", 0, 0, 0);
         asn1Print_NGSetupResponse (namebuf, pvalue->value.u.nGSetup);
         break;
      }
      /* pathSwitchRequest */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pathSwitchRequest:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.pathSwitchRequest", 0, 0, 0);
         asn1Print_PathSwitchRequestAcknowledge (namebuf, pvalue->value.
            u.pathSwitchRequest);
         break;
      }
      /* pDUSessionResourceModify */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceModify:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.pDUSessionResourceModify", 0, 0, 0);
         asn1Print_PDUSessionResourceModifyResponse (namebuf, pvalue->value.
            u.pDUSessionResourceModify);
         break;
      }
      /* pDUSessionResourceModifyIndication */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceModifyIndication:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.pDUSessionResourceModifyIndication", 0, 0, 0);
         asn1Print_PDUSessionResourceModifyConfirm (namebuf, pvalue->value.
            u.pDUSessionResourceModifyIndication);
         break;
      }
      /* pDUSessionResourceRelease */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceRelease:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.pDUSessionResourceRelease", 0, 0, 0);
         asn1Print_PDUSessionResourceReleaseResponse (namebuf, pvalue->value.
            u.pDUSessionResourceRelease);
         break;
      }
      /* pDUSessionResourceSetup */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceSetup:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.pDUSessionResourceSetup", 0, 0, 0);
         asn1Print_PDUSessionResourceSetupResponse (namebuf, pvalue->value.
            u.pDUSessionResourceSetup);
         break;
      }
      /* pWSCancel */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pWSCancel:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.pWSCancel", 0, 0, 0);
         asn1Print_PWSCancelResponse (namebuf, pvalue->value.u.pWSCancel);
         break;
      }
      /* rANConfigurationUpdate */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rANConfigurationUpdate:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.rANConfigurationUpdate", 0, 0, 0);
         asn1Print_RANConfigurationUpdateAcknowledge (namebuf, pvalue->value.
            u.rANConfigurationUpdate);
         break;
      }
      /* uEContextModification */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextModification:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.uEContextModification", 0, 0, 0);
         asn1Print_UEContextModificationResponse (namebuf, pvalue->value.
            u.uEContextModification);
         break;
      }
      /* uEContextRelease */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextRelease:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.uEContextRelease", 0, 0, 0);
         asn1Print_UEContextReleaseComplete (namebuf, pvalue->value.
            u.uEContextRelease);
         break;
      }
      /* uERadioCapabilityCheck */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uERadioCapabilityCheck:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.uERadioCapabilityCheck", 0, 0, 0);
         asn1Print_UERadioCapabilityCheckResponse (namebuf, pvalue->value.
            u.uERadioCapabilityCheck);
         break;
      }
      /* writeReplaceWarning */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_writeReplaceWarning:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.writeReplaceWarning", 0, 0, 0);
         asn1Print_WriteReplaceWarningResponse (namebuf, pvalue->value.
            u.writeReplaceWarning);
         break;
      }
      default: {
         if (0 != pvalue->value.u.extElem1) {
            rtPrintOpenType ("extElem1", pvalue->value.u.extElem1->numocts, pvalue->value.u.extElem1->data, ".");
         }
      }
   }

}

void asn1Print_UnsuccessfulOutcome 
   (const char* name, const UnsuccessfulOutcome* pvalue)
{
   char namebuf[512];

   rtxStrJoin (namebuf, 512, name, ".procedureCode", 0, 0, 0);
   asn1Print_ProcedureCode (namebuf, &pvalue->procedureCode);

   rtxStrJoin (namebuf, 512, name, ".criticality", 0, 0, 0);
   asn1Print_Criticality (namebuf, &pvalue->criticality);

   rtxStrJoin (namebuf, 512, name, ".value", 0, 0, 0);
   printf ("%s.t = %d\n", namebuf, pvalue->value.t);
   switch (pvalue->value.t)
   {
      /* aMFConfigurationUpdate */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_aMFConfigurationUpdate:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.aMFConfigurationUpdate", 0, 0, 0);
         asn1Print_AMFConfigurationUpdateFailure (namebuf, pvalue->value.
            u.aMFConfigurationUpdate);
         break;
      }
      /* handoverPreparation */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverPreparation:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.handoverPreparation", 0, 0, 0);
         asn1Print_HandoverPreparationFailure (namebuf, pvalue->value.
            u.handoverPreparation);
         break;
      }
      /* handoverResourceAllocation */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverResourceAllocation:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.handoverResourceAllocation", 0, 0, 0);
         asn1Print_HandoverFailure (namebuf, pvalue->value.
            u.handoverResourceAllocation);
         break;
      }
      /* initialContextSetup */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_initialContextSetup:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.initialContextSetup", 0, 0, 0);
         asn1Print_InitialContextSetupFailure (namebuf, pvalue->value.
            u.initialContextSetup);
         break;
      }
      /* nGSetup */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGSetup:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.nGSetup", 0, 0, 0);
         asn1Print_NGSetupFailure (namebuf, pvalue->value.u.nGSetup);
         break;
      }
      /* pathSwitchRequest */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pathSwitchRequest:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.pathSwitchRequest", 0, 0, 0);
         asn1Print_PathSwitchRequestFailure (namebuf, pvalue->value.
            u.pathSwitchRequest);
         break;
      }
      /* rANConfigurationUpdate */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rANConfigurationUpdate:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.rANConfigurationUpdate", 0, 0, 0);
         asn1Print_RANConfigurationUpdateFailure (namebuf, pvalue->value.
            u.rANConfigurationUpdate);
         break;
      }
      /* uEContextModification */
      case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextModification:
      {
         rtxStrJoin (namebuf, 512, namebuf, "->u.uEContextModification", 0, 0, 0);
         asn1Print_UEContextModificationFailure (namebuf, pvalue->value.
            u.uEContextModification);
         break;
      }
      default: {
         if (0 != pvalue->value.u.extElem1) {
            rtPrintOpenType ("extElem1", pvalue->value.u.extElem1->numocts, pvalue->value.u.extElem1->data, ".");
         }
      }
   }

}

void asn1Print_NGAP_PDU (const char* name, const NGAP_PDU* pvalue)
{
   char namebuf[512];

   printf ("%s.t = %d\n", name, pvalue->t);
   switch (pvalue->t)
   {
      /* initiatingMessage */
      case 1:
      {
         rtxStrJoin (namebuf, 512, name, ".u.initiatingMessage", 0, 0, 0);
         asn1Print_InitiatingMessage (namebuf, pvalue->u.initiatingMessage);
         break;
      }
      /* successfulOutcome */
      case 2:
      {
         rtxStrJoin (namebuf, 512, name, ".u.successfulOutcome", 0, 0, 0);
         asn1Print_SuccessfulOutcome (namebuf, pvalue->u.successfulOutcome);
         break;
      }
      /* unsuccessfulOutcome */
      case 3:
      {
         rtxStrJoin (namebuf, 512, name, ".u.unsuccessfulOutcome", 0, 0, 0);
         asn1Print_UnsuccessfulOutcome (namebuf, pvalue->u.unsuccessfulOutcome
            );
         break;
      }
      /* extElem1 */
      case 4:
      {
         rtxStrJoin (namebuf, 512, name, ".u.extElem1", 0, 0, 0);
         rtPrintOpenType (namebuf, pvalue->u.extElem1->numocts,
         pvalue->u.extElem1->data, ".");
         break;
      }
      default:;
   }
}

