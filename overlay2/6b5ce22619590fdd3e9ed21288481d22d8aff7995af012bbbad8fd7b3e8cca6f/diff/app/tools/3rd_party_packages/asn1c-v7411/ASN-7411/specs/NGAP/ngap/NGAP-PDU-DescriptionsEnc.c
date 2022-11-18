/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.4.1.1, Date: 02-Jun-2020.
 */
#include ".h"
#include "rtxsrc/rtxCommon.h"

EXTERN int asn1PE_InitiatingMessage (OSCTXT* pctxt, InitiatingMessage* pvalue)
{
   int stat = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "InitiatingMessage");

   RTDIAGSTRM2 (pctxt, "asn1PE_InitiatingMessage: start\n");

   /* encode procedureCode */

   RTXCTXTPUSHELEMNAME (pctxt, "procedureCode");

   stat = asn1PE_ProcedureCode (pctxt, pvalue->procedureCode);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode criticality */

   RTXCTXTPUSHELEMNAME (pctxt, "criticality");

   stat = asn1PE_Criticality (pctxt, pvalue->criticality);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode value */

   RTXCTXTPUSHELEMNAME (pctxt, "value");

   { OSCTXT lctxt;
   OSOCTET* pDynamicEncodeBuffer;
   ASN1OpenType openType;
   OSBOOL encoded = TRUE;
   OSRTDiagBitFieldList* pFieldList;
   OSINT16 savedBitOffset = pctxt->buffer.bitOffset;

   openType.numocts = 0;
   openType.data = 0;

   rtxCopyContext (&lctxt, pctxt);
   pctxt->pStream = 0;

   pFieldList = pctxt->pBitFldList;
   if (0 != pFieldList) {
      pu_initRtxDiagBitFieldList (pctxt, savedBitOffset);
   }
   stat = rtxInitContextBuffer (pctxt, 0, 0);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   switch (pvalue->value.t) {
   /* aMFConfigurationUpdate */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_aMFConfigurationUpdate:
      RTXCTXTPUSHELEMNAME (pctxt, "aMFConfigurationUpdate");

      stat = asn1PE_AMFConfigurationUpdate (pctxt, pvalue->value.u.aMFConfigurationUpdate);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* handoverCancel */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverCancel:
      RTXCTXTPUSHELEMNAME (pctxt, "handoverCancel");

      stat = asn1PE_HandoverCancel (pctxt, pvalue->value.u.handoverCancel);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* handoverPreparation */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverPreparation:
      RTXCTXTPUSHELEMNAME (pctxt, "handoverPreparation");

      stat = asn1PE_HandoverRequired (pctxt, pvalue->value.u.handoverPreparation);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* handoverResourceAllocation */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverResourceAllocation:
      RTXCTXTPUSHELEMNAME (pctxt, "handoverResourceAllocation");

      stat = asn1PE_HandoverRequest (pctxt, pvalue->value.u.handoverResourceAllocation);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* initialContextSetup */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_initialContextSetup:
      RTXCTXTPUSHELEMNAME (pctxt, "initialContextSetup");

      stat = asn1PE_InitialContextSetupRequest (pctxt, pvalue->value.u.initialContextSetup);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* nGReset */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGReset:
      RTXCTXTPUSHELEMNAME (pctxt, "nGReset");

      stat = asn1PE_NGReset (pctxt, pvalue->value.u.nGReset);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* nGSetup */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGSetup:
      RTXCTXTPUSHELEMNAME (pctxt, "nGSetup");

      stat = asn1PE_NGSetupRequest (pctxt, pvalue->value.u.nGSetup);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* pathSwitchRequest */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pathSwitchRequest:
      RTXCTXTPUSHELEMNAME (pctxt, "pathSwitchRequest");

      stat = asn1PE_PathSwitchRequest (pctxt, pvalue->value.u.pathSwitchRequest);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* pDUSessionResourceModify */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceModify:
      RTXCTXTPUSHELEMNAME (pctxt, "pDUSessionResourceModify");

      stat = asn1PE_PDUSessionResourceModifyRequest (pctxt, pvalue->value.u.pDUSessionResourceModify);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* pDUSessionResourceModifyIndication */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceModifyIndication:
      RTXCTXTPUSHELEMNAME (pctxt, "pDUSessionResourceModifyIndication");

      stat = asn1PE_PDUSessionResourceModifyIndication (pctxt, pvalue->value.u.pDUSessionResourceModifyIndication);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* pDUSessionResourceRelease */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceRelease:
      RTXCTXTPUSHELEMNAME (pctxt, "pDUSessionResourceRelease");

      stat = asn1PE_PDUSessionResourceReleaseCommand (pctxt, pvalue->value.u.pDUSessionResourceRelease);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* pDUSessionResourceSetup */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceSetup:
      RTXCTXTPUSHELEMNAME (pctxt, "pDUSessionResourceSetup");

      stat = asn1PE_PDUSessionResourceSetupRequest (pctxt, pvalue->value.u.pDUSessionResourceSetup);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* pWSCancel */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pWSCancel:
      RTXCTXTPUSHELEMNAME (pctxt, "pWSCancel");

      stat = asn1PE_PWSCancelRequest (pctxt, pvalue->value.u.pWSCancel);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* rANConfigurationUpdate */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rANConfigurationUpdate:
      RTXCTXTPUSHELEMNAME (pctxt, "rANConfigurationUpdate");

      stat = asn1PE_RANConfigurationUpdate (pctxt, pvalue->value.u.rANConfigurationUpdate);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* uEContextModification */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextModification:
      RTXCTXTPUSHELEMNAME (pctxt, "uEContextModification");

      stat = asn1PE_UEContextModificationRequest (pctxt, pvalue->value.u.uEContextModification);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* uEContextRelease */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextRelease:
      RTXCTXTPUSHELEMNAME (pctxt, "uEContextRelease");

      stat = asn1PE_UEContextReleaseCommand (pctxt, pvalue->value.u.uEContextRelease);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* uERadioCapabilityCheck */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uERadioCapabilityCheck:
      RTXCTXTPUSHELEMNAME (pctxt, "uERadioCapabilityCheck");

      stat = asn1PE_UERadioCapabilityCheckRequest (pctxt, pvalue->value.u.uERadioCapabilityCheck);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* writeReplaceWarning */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_writeReplaceWarning:
      RTXCTXTPUSHELEMNAME (pctxt, "writeReplaceWarning");

      stat = asn1PE_WriteReplaceWarningRequest (pctxt, pvalue->value.u.writeReplaceWarning);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* aMFStatusIndication */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_aMFStatusIndication:
      RTXCTXTPUSHELEMNAME (pctxt, "aMFStatusIndication");

      stat = asn1PE_AMFStatusIndication (pctxt, pvalue->value.u.aMFStatusIndication);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* cellTrafficTrace */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_cellTrafficTrace:
      RTXCTXTPUSHELEMNAME (pctxt, "cellTrafficTrace");

      stat = asn1PE_CellTrafficTrace (pctxt, pvalue->value.u.cellTrafficTrace);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* deactivateTrace */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_deactivateTrace:
      RTXCTXTPUSHELEMNAME (pctxt, "deactivateTrace");

      stat = asn1PE_DeactivateTrace (pctxt, pvalue->value.u.deactivateTrace);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* downlinkNASTransport */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkNASTransport:
      RTXCTXTPUSHELEMNAME (pctxt, "downlinkNASTransport");

      stat = asn1PE_DownlinkNASTransport (pctxt, pvalue->value.u.downlinkNASTransport);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* downlinkNonUEAssociatedNRPPaTransport */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkNonUEAssociatedNRPPaTransport:
      RTXCTXTPUSHELEMNAME (pctxt, "downlinkNonUEAssociatedNRPPaTransport");

      stat = asn1PE_DownlinkNonUEAssociatedNRPPaTransport (pctxt, pvalue->value.u.downlinkNonUEAssociatedNRPPaTransport);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* downlinkRANConfigurationTransfer */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkRANConfigurationTransfer:
      RTXCTXTPUSHELEMNAME (pctxt, "downlinkRANConfigurationTransfer");

      stat = asn1PE_DownlinkRANConfigurationTransfer (pctxt, pvalue->value.u.downlinkRANConfigurationTransfer);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* downlinkRANStatusTransfer */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkRANStatusTransfer:
      RTXCTXTPUSHELEMNAME (pctxt, "downlinkRANStatusTransfer");

      stat = asn1PE_DownlinkRANStatusTransfer (pctxt, pvalue->value.u.downlinkRANStatusTransfer);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* downlinkUEAssociatedNRPPaTransport */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkUEAssociatedNRPPaTransport:
      RTXCTXTPUSHELEMNAME (pctxt, "downlinkUEAssociatedNRPPaTransport");

      stat = asn1PE_DownlinkUEAssociatedNRPPaTransport (pctxt, pvalue->value.u.downlinkUEAssociatedNRPPaTransport);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* errorIndication */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_errorIndication:
      RTXCTXTPUSHELEMNAME (pctxt, "errorIndication");

      stat = asn1PE_ErrorIndication (pctxt, pvalue->value.u.errorIndication);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* handoverNotification */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverNotification:
      RTXCTXTPUSHELEMNAME (pctxt, "handoverNotification");

      stat = asn1PE_HandoverNotify (pctxt, pvalue->value.u.handoverNotification);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* initialUEMessage */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_initialUEMessage:
      RTXCTXTPUSHELEMNAME (pctxt, "initialUEMessage");

      stat = asn1PE_InitialUEMessage (pctxt, pvalue->value.u.initialUEMessage);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* locationReport */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_locationReport:
      RTXCTXTPUSHELEMNAME (pctxt, "locationReport");

      stat = asn1PE_LocationReport (pctxt, pvalue->value.u.locationReport);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* locationReportingControl */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_locationReportingControl:
      RTXCTXTPUSHELEMNAME (pctxt, "locationReportingControl");

      stat = asn1PE_LocationReportingControl (pctxt, pvalue->value.u.locationReportingControl);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* locationReportingFailureIndication */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_locationReportingFailureIndication:
      RTXCTXTPUSHELEMNAME (pctxt, "locationReportingFailureIndication");

      stat = asn1PE_LocationReportingFailureIndication (pctxt, pvalue->value.u.locationReportingFailureIndication);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* nASNonDeliveryIndication */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nASNonDeliveryIndication:
      RTXCTXTPUSHELEMNAME (pctxt, "nASNonDeliveryIndication");

      stat = asn1PE_NASNonDeliveryIndication (pctxt, pvalue->value.u.nASNonDeliveryIndication);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* overloadStart */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_overloadStart:
      RTXCTXTPUSHELEMNAME (pctxt, "overloadStart");

      stat = asn1PE_OverloadStart (pctxt, pvalue->value.u.overloadStart);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* overloadStop */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_overloadStop:
      RTXCTXTPUSHELEMNAME (pctxt, "overloadStop");

      stat = asn1PE_OverloadStop (pctxt, pvalue->value.u.overloadStop);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* paging */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_paging:
      RTXCTXTPUSHELEMNAME (pctxt, "paging");

      stat = asn1PE_Paging (pctxt, pvalue->value.u.paging);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* pDUSessionResourceNotify */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceNotify:
      RTXCTXTPUSHELEMNAME (pctxt, "pDUSessionResourceNotify");

      stat = asn1PE_PDUSessionResourceNotify (pctxt, pvalue->value.u.pDUSessionResourceNotify);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* privateMessage */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_privateMessage:
      RTXCTXTPUSHELEMNAME (pctxt, "privateMessage");

      stat = asn1PE_PrivateMessage (pctxt, pvalue->value.u.privateMessage);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* pWSFailureIndication */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pWSFailureIndication:
      RTXCTXTPUSHELEMNAME (pctxt, "pWSFailureIndication");

      stat = asn1PE_PWSFailureIndication (pctxt, pvalue->value.u.pWSFailureIndication);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* pWSRestartIndication */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pWSRestartIndication:
      RTXCTXTPUSHELEMNAME (pctxt, "pWSRestartIndication");

      stat = asn1PE_PWSRestartIndication (pctxt, pvalue->value.u.pWSRestartIndication);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* rerouteNASRequest */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rerouteNASRequest:
      RTXCTXTPUSHELEMNAME (pctxt, "rerouteNASRequest");

      stat = asn1PE_RerouteNASRequest (pctxt, pvalue->value.u.rerouteNASRequest);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* rRCInactiveTransitionReport */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rRCInactiveTransitionReport:
      RTXCTXTPUSHELEMNAME (pctxt, "rRCInactiveTransitionReport");

      stat = asn1PE_RRCInactiveTransitionReport (pctxt, pvalue->value.u.rRCInactiveTransitionReport);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* secondaryRATDataUsageReport */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_secondaryRATDataUsageReport:
      RTXCTXTPUSHELEMNAME (pctxt, "secondaryRATDataUsageReport");

      stat = asn1PE_SecondaryRATDataUsageReport (pctxt, pvalue->value.u.secondaryRATDataUsageReport);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* traceFailureIndication */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_traceFailureIndication:
      RTXCTXTPUSHELEMNAME (pctxt, "traceFailureIndication");

      stat = asn1PE_TraceFailureIndication (pctxt, pvalue->value.u.traceFailureIndication);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* traceStart */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_traceStart:
      RTXCTXTPUSHELEMNAME (pctxt, "traceStart");

      stat = asn1PE_TraceStart (pctxt, pvalue->value.u.traceStart);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* uEContextReleaseRequest */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextReleaseRequest:
      RTXCTXTPUSHELEMNAME (pctxt, "uEContextReleaseRequest");

      stat = asn1PE_UEContextReleaseRequest (pctxt, pvalue->value.u.uEContextReleaseRequest);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* uERadioCapabilityInfoIndication */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uERadioCapabilityInfoIndication:
      RTXCTXTPUSHELEMNAME (pctxt, "uERadioCapabilityInfoIndication");

      stat = asn1PE_UERadioCapabilityInfoIndication (pctxt, pvalue->value.u.uERadioCapabilityInfoIndication);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* uETNLABindingRelease */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uETNLABindingRelease:
      RTXCTXTPUSHELEMNAME (pctxt, "uETNLABindingRelease");

      stat = asn1PE_UETNLABindingReleaseRequest (pctxt, pvalue->value.u.uETNLABindingRelease);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* uplinkNASTransport */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkNASTransport:
      RTXCTXTPUSHELEMNAME (pctxt, "uplinkNASTransport");

      stat = asn1PE_UplinkNASTransport (pctxt, pvalue->value.u.uplinkNASTransport);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* uplinkNonUEAssociatedNRPPaTransport */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkNonUEAssociatedNRPPaTransport:
      RTXCTXTPUSHELEMNAME (pctxt, "uplinkNonUEAssociatedNRPPaTransport");

      stat = asn1PE_UplinkNonUEAssociatedNRPPaTransport (pctxt, pvalue->value.u.uplinkNonUEAssociatedNRPPaTransport);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* uplinkRANConfigurationTransfer */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkRANConfigurationTransfer:
      RTXCTXTPUSHELEMNAME (pctxt, "uplinkRANConfigurationTransfer");

      stat = asn1PE_UplinkRANConfigurationTransfer (pctxt, pvalue->value.u.uplinkRANConfigurationTransfer);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* uplinkRANStatusTransfer */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkRANStatusTransfer:
      RTXCTXTPUSHELEMNAME (pctxt, "uplinkRANStatusTransfer");

      stat = asn1PE_UplinkRANStatusTransfer (pctxt, pvalue->value.u.uplinkRANStatusTransfer);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* uplinkUEAssociatedNRPPaTransport */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkUEAssociatedNRPPaTransport:
      RTXCTXTPUSHELEMNAME (pctxt, "uplinkUEAssociatedNRPPaTransport");

      stat = asn1PE_UplinkUEAssociatedNRPPaTransport (pctxt, pvalue->value.u.uplinkUEAssociatedNRPPaTransport);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_UNDEF_:
      if (0 != pvalue->value.u.extElem1) {
         openType.numocts = pvalue->value.u.extElem1->numocts;
         openType.data = pvalue->value.u.extElem1->data;
      }
      encoded = FALSE;
      break;

   default:
      encoded = FALSE;
      stat = RTERR_INVOPT;
   }

   if (encoded) {
      openType.numocts = (OSUINT32) pe_GetMsgLen (pctxt);
      openType.data = pDynamicEncodeBuffer = pctxt->buffer.data;
   }

   rtxCopyContext (pctxt, &lctxt);

   if (0 == stat) {
      OSRTDiagBitFieldList* pOTFieldList = pctxt->pBitFldList;
      pctxt->pBitFldList = pFieldList;

      stat = pe_OpenType (pctxt, openType.numocts, openType.data);

      PU_SETOPENTYPEFLDLIST (pctxt->pBitFldList, pOTFieldList);
   }

   /* Free dynamic encode buffer */
   if (encoded) {
      rtxMemFreePtr (pctxt, pDynamicEncodeBuffer);
   }}

   if (stat != 0) return LOG_RTERR (pctxt, stat);

   RTXCTXTPOPELEMNAME (pctxt);

   RTDIAGSTRM2 (pctxt, "asn1PE_InitiatingMessage: end\n");

   RTXCTXTPOPTYPENAME (pctxt);

   return (stat);
}

EXTERN int asn1PE_SuccessfulOutcome (OSCTXT* pctxt, SuccessfulOutcome* pvalue)
{
   int stat = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "SuccessfulOutcome");

   RTDIAGSTRM2 (pctxt, "asn1PE_SuccessfulOutcome: start\n");

   /* encode procedureCode */

   RTXCTXTPUSHELEMNAME (pctxt, "procedureCode");

   stat = asn1PE_ProcedureCode (pctxt, pvalue->procedureCode);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode criticality */

   RTXCTXTPUSHELEMNAME (pctxt, "criticality");

   stat = asn1PE_Criticality (pctxt, pvalue->criticality);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode value */

   RTXCTXTPUSHELEMNAME (pctxt, "value");

   { OSCTXT lctxt;
   OSOCTET* pDynamicEncodeBuffer;
   ASN1OpenType openType;
   OSBOOL encoded = TRUE;
   OSRTDiagBitFieldList* pFieldList;
   OSINT16 savedBitOffset = pctxt->buffer.bitOffset;

   openType.numocts = 0;
   openType.data = 0;

   rtxCopyContext (&lctxt, pctxt);
   pctxt->pStream = 0;

   pFieldList = pctxt->pBitFldList;
   if (0 != pFieldList) {
      pu_initRtxDiagBitFieldList (pctxt, savedBitOffset);
   }
   stat = rtxInitContextBuffer (pctxt, 0, 0);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   switch (pvalue->value.t) {
   /* aMFConfigurationUpdate */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_aMFConfigurationUpdate:
      RTXCTXTPUSHELEMNAME (pctxt, "aMFConfigurationUpdate");

      stat = asn1PE_AMFConfigurationUpdateAcknowledge (pctxt, pvalue->value.u.aMFConfigurationUpdate);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* handoverCancel */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverCancel:
      RTXCTXTPUSHELEMNAME (pctxt, "handoverCancel");

      stat = asn1PE_HandoverCancelAcknowledge (pctxt, pvalue->value.u.handoverCancel);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* handoverPreparation */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverPreparation:
      RTXCTXTPUSHELEMNAME (pctxt, "handoverPreparation");

      stat = asn1PE_HandoverCommand (pctxt, pvalue->value.u.handoverPreparation);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* handoverResourceAllocation */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverResourceAllocation:
      RTXCTXTPUSHELEMNAME (pctxt, "handoverResourceAllocation");

      stat = asn1PE_HandoverRequestAcknowledge (pctxt, pvalue->value.u.handoverResourceAllocation);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* initialContextSetup */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_initialContextSetup:
      RTXCTXTPUSHELEMNAME (pctxt, "initialContextSetup");

      stat = asn1PE_InitialContextSetupResponse (pctxt, pvalue->value.u.initialContextSetup);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* nGReset */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGReset:
      RTXCTXTPUSHELEMNAME (pctxt, "nGReset");

      stat = asn1PE_NGResetAcknowledge (pctxt, pvalue->value.u.nGReset);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* nGSetup */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGSetup:
      RTXCTXTPUSHELEMNAME (pctxt, "nGSetup");

      stat = asn1PE_NGSetupResponse (pctxt, pvalue->value.u.nGSetup);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* pathSwitchRequest */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pathSwitchRequest:
      RTXCTXTPUSHELEMNAME (pctxt, "pathSwitchRequest");

      stat = asn1PE_PathSwitchRequestAcknowledge (pctxt, pvalue->value.u.pathSwitchRequest);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* pDUSessionResourceModify */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceModify:
      RTXCTXTPUSHELEMNAME (pctxt, "pDUSessionResourceModify");

      stat = asn1PE_PDUSessionResourceModifyResponse (pctxt, pvalue->value.u.pDUSessionResourceModify);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* pDUSessionResourceModifyIndication */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceModifyIndication:
      RTXCTXTPUSHELEMNAME (pctxt, "pDUSessionResourceModifyIndication");

      stat = asn1PE_PDUSessionResourceModifyConfirm (pctxt, pvalue->value.u.pDUSessionResourceModifyIndication);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* pDUSessionResourceRelease */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceRelease:
      RTXCTXTPUSHELEMNAME (pctxt, "pDUSessionResourceRelease");

      stat = asn1PE_PDUSessionResourceReleaseResponse (pctxt, pvalue->value.u.pDUSessionResourceRelease);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* pDUSessionResourceSetup */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceSetup:
      RTXCTXTPUSHELEMNAME (pctxt, "pDUSessionResourceSetup");

      stat = asn1PE_PDUSessionResourceSetupResponse (pctxt, pvalue->value.u.pDUSessionResourceSetup);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* pWSCancel */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pWSCancel:
      RTXCTXTPUSHELEMNAME (pctxt, "pWSCancel");

      stat = asn1PE_PWSCancelResponse (pctxt, pvalue->value.u.pWSCancel);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* rANConfigurationUpdate */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rANConfigurationUpdate:
      RTXCTXTPUSHELEMNAME (pctxt, "rANConfigurationUpdate");

      stat = asn1PE_RANConfigurationUpdateAcknowledge (pctxt, pvalue->value.u.rANConfigurationUpdate);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* uEContextModification */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextModification:
      RTXCTXTPUSHELEMNAME (pctxt, "uEContextModification");

      stat = asn1PE_UEContextModificationResponse (pctxt, pvalue->value.u.uEContextModification);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* uEContextRelease */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextRelease:
      RTXCTXTPUSHELEMNAME (pctxt, "uEContextRelease");

      stat = asn1PE_UEContextReleaseComplete (pctxt, pvalue->value.u.uEContextRelease);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* uERadioCapabilityCheck */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uERadioCapabilityCheck:
      RTXCTXTPUSHELEMNAME (pctxt, "uERadioCapabilityCheck");

      stat = asn1PE_UERadioCapabilityCheckResponse (pctxt, pvalue->value.u.uERadioCapabilityCheck);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* writeReplaceWarning */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_writeReplaceWarning:
      RTXCTXTPUSHELEMNAME (pctxt, "writeReplaceWarning");

      stat = asn1PE_WriteReplaceWarningResponse (pctxt, pvalue->value.u.writeReplaceWarning);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_UNDEF_:
      if (0 != pvalue->value.u.extElem1) {
         openType.numocts = pvalue->value.u.extElem1->numocts;
         openType.data = pvalue->value.u.extElem1->data;
      }
      encoded = FALSE;
      break;

   default:
      encoded = FALSE;
      stat = RTERR_INVOPT;
   }

   if (encoded) {
      openType.numocts = (OSUINT32) pe_GetMsgLen (pctxt);
      openType.data = pDynamicEncodeBuffer = pctxt->buffer.data;
   }

   rtxCopyContext (pctxt, &lctxt);

   if (0 == stat) {
      OSRTDiagBitFieldList* pOTFieldList = pctxt->pBitFldList;
      pctxt->pBitFldList = pFieldList;

      stat = pe_OpenType (pctxt, openType.numocts, openType.data);

      PU_SETOPENTYPEFLDLIST (pctxt->pBitFldList, pOTFieldList);
   }

   /* Free dynamic encode buffer */
   if (encoded) {
      rtxMemFreePtr (pctxt, pDynamicEncodeBuffer);
   }}

   if (stat != 0) return LOG_RTERR (pctxt, stat);

   RTXCTXTPOPELEMNAME (pctxt);

   RTDIAGSTRM2 (pctxt, "asn1PE_SuccessfulOutcome: end\n");

   RTXCTXTPOPTYPENAME (pctxt);

   return (stat);
}

EXTERN int asn1PE_UnsuccessfulOutcome (OSCTXT* pctxt, UnsuccessfulOutcome* pvalue)
{
   int stat = 0;

   RTXCTXTPUSHTYPENAME (pctxt, "UnsuccessfulOutcome");

   RTDIAGSTRM2 (pctxt, "asn1PE_UnsuccessfulOutcome: start\n");

   /* encode procedureCode */

   RTXCTXTPUSHELEMNAME (pctxt, "procedureCode");

   stat = asn1PE_ProcedureCode (pctxt, pvalue->procedureCode);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode criticality */

   RTXCTXTPUSHELEMNAME (pctxt, "criticality");

   stat = asn1PE_Criticality (pctxt, pvalue->criticality);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   RTXCTXTPOPELEMNAME (pctxt);

   /* encode value */

   RTXCTXTPUSHELEMNAME (pctxt, "value");

   { OSCTXT lctxt;
   OSOCTET* pDynamicEncodeBuffer;
   ASN1OpenType openType;
   OSBOOL encoded = TRUE;
   OSRTDiagBitFieldList* pFieldList;
   OSINT16 savedBitOffset = pctxt->buffer.bitOffset;

   openType.numocts = 0;
   openType.data = 0;

   rtxCopyContext (&lctxt, pctxt);
   pctxt->pStream = 0;

   pFieldList = pctxt->pBitFldList;
   if (0 != pFieldList) {
      pu_initRtxDiagBitFieldList (pctxt, savedBitOffset);
   }
   stat = rtxInitContextBuffer (pctxt, 0, 0);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   switch (pvalue->value.t) {
   /* aMFConfigurationUpdate */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_aMFConfigurationUpdate:
      RTXCTXTPUSHELEMNAME (pctxt, "aMFConfigurationUpdate");

      stat = asn1PE_AMFConfigurationUpdateFailure (pctxt, pvalue->value.u.aMFConfigurationUpdate);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* handoverPreparation */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverPreparation:
      RTXCTXTPUSHELEMNAME (pctxt, "handoverPreparation");

      stat = asn1PE_HandoverPreparationFailure (pctxt, pvalue->value.u.handoverPreparation);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* handoverResourceAllocation */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverResourceAllocation:
      RTXCTXTPUSHELEMNAME (pctxt, "handoverResourceAllocation");

      stat = asn1PE_HandoverFailure (pctxt, pvalue->value.u.handoverResourceAllocation);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* initialContextSetup */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_initialContextSetup:
      RTXCTXTPUSHELEMNAME (pctxt, "initialContextSetup");

      stat = asn1PE_InitialContextSetupFailure (pctxt, pvalue->value.u.initialContextSetup);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* nGSetup */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGSetup:
      RTXCTXTPUSHELEMNAME (pctxt, "nGSetup");

      stat = asn1PE_NGSetupFailure (pctxt, pvalue->value.u.nGSetup);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* pathSwitchRequest */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pathSwitchRequest:
      RTXCTXTPUSHELEMNAME (pctxt, "pathSwitchRequest");

      stat = asn1PE_PathSwitchRequestFailure (pctxt, pvalue->value.u.pathSwitchRequest);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* rANConfigurationUpdate */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rANConfigurationUpdate:
      RTXCTXTPUSHELEMNAME (pctxt, "rANConfigurationUpdate");

      stat = asn1PE_RANConfigurationUpdateFailure (pctxt, pvalue->value.u.rANConfigurationUpdate);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   /* uEContextModification */
   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextModification:
      RTXCTXTPUSHELEMNAME (pctxt, "uEContextModification");

      stat = asn1PE_UEContextModificationFailure (pctxt, pvalue->value.u.uEContextModification);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
      break;

   case T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_UNDEF_:
      if (0 != pvalue->value.u.extElem1) {
         openType.numocts = pvalue->value.u.extElem1->numocts;
         openType.data = pvalue->value.u.extElem1->data;
      }
      encoded = FALSE;
      break;

   default:
      encoded = FALSE;
      stat = RTERR_INVOPT;
   }

   if (encoded) {
      openType.numocts = (OSUINT32) pe_GetMsgLen (pctxt);
      openType.data = pDynamicEncodeBuffer = pctxt->buffer.data;
   }

   rtxCopyContext (pctxt, &lctxt);

   if (0 == stat) {
      OSRTDiagBitFieldList* pOTFieldList = pctxt->pBitFldList;
      pctxt->pBitFldList = pFieldList;

      stat = pe_OpenType (pctxt, openType.numocts, openType.data);

      PU_SETOPENTYPEFLDLIST (pctxt->pBitFldList, pOTFieldList);
   }

   /* Free dynamic encode buffer */
   if (encoded) {
      rtxMemFreePtr (pctxt, pDynamicEncodeBuffer);
   }}

   if (stat != 0) return LOG_RTERR (pctxt, stat);

   RTXCTXTPOPELEMNAME (pctxt);

   RTDIAGSTRM2 (pctxt, "asn1PE_UnsuccessfulOutcome: end\n");

   RTXCTXTPOPTYPENAME (pctxt);

   return (stat);
}

EXTERN int asn1PE_NGAP_PDU (OSCTXT* pctxt, NGAP_PDU* pvalue)
{
   int stat = 0;
   OSBOOL extbit = FALSE;

   RTXCTXTPUSHTYPENAME (pctxt, "NGAP-PDU");

   RTDIAGSTRM2 (pctxt, "asn1PE_NGAP_PDU: start\n");

   /* extension bit */

   PU_NEWFIELD (pctxt, "extension marker");

   extbit = (OSBOOL)(pvalue->t > 3);

   stat = rtxEncBit (pctxt, extbit);
   if (stat != 0) return LOG_RTERR (pctxt, stat);

   PU_SETBITCOUNT (pctxt);

   if (!extbit) {

      /* Encode choice index value */

      RTXCTXTPUSHELEMNAME (pctxt, "t");
      PU_NEWFIELD (pctxt, "<choice-index>");

      stat = rtxEncBits (pctxt, pvalue->t - 1, 2);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      PU_SETBITCOUNT (pctxt);
      RTXCTXTPOPELEMNAME (pctxt);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* initiatingMessage */
         case 1:
            RTXCTXTPUSHELEMNAME (pctxt, "initiatingMessage");

            stat = asn1PE_InitiatingMessage (pctxt, pvalue->u.initiatingMessage);
            if (stat != 0) return LOG_RTERR (pctxt, stat);

            RTXCTXTPOPELEMNAME (pctxt);
            break;

         /* successfulOutcome */
         case 2:
            RTXCTXTPUSHELEMNAME (pctxt, "successfulOutcome");

            stat = asn1PE_SuccessfulOutcome (pctxt, pvalue->u.successfulOutcome);
            if (stat != 0) return LOG_RTERR (pctxt, stat);

            RTXCTXTPOPELEMNAME (pctxt);
            break;

         /* unsuccessfulOutcome */
         case 3:
            RTXCTXTPUSHELEMNAME (pctxt, "unsuccessfulOutcome");

            stat = asn1PE_UnsuccessfulOutcome (pctxt, pvalue->u.unsuccessfulOutcome);
            if (stat != 0) return LOG_RTERR (pctxt, stat);

            RTXCTXTPOPELEMNAME (pctxt);
            break;

         default:
            return LOG_RTERR (pctxt, RTERR_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      PU_NEWFIELD (pctxt, "choice index");

      stat = pe_SmallNonNegWholeNumber (pctxt, pvalue->t - 4);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      PU_SETBITCOUNT (pctxt);

      /* Encode extension element data value */

      RTXCTXTPUSHELEMNAME (pctxt, "...");

      stat = pe_OpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != 0) return LOG_RTERR (pctxt, stat);

      RTXCTXTPOPELEMNAME (pctxt);
   }

   RTDIAGSTRM2 (pctxt, "asn1PE_NGAP_PDU: end\n");

   RTXCTXTPOPTYPENAME (pctxt);

   return (stat);
}

