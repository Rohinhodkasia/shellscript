/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.4.2.3, Date: 13-Jul-2020.
 */
#include ".h"
#include "rtxsrc/rtxCommon.h"

/* InitiatingMessage */

void asn1SetTC_InitiatingMessage_aMFConfigurationUpdate
   (OSCTXT* pctxt, InitiatingMessage* pElem, AMFConfigurationUpdate *pvalue)
{
   pElem->procedureCode = 0;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_aMFConfigurationUpdate;
   pElem->value.u.aMFConfigurationUpdate = pvalue;
}

void asn1SetTC_InitiatingMessage_handoverCancel
   (OSCTXT* pctxt, InitiatingMessage* pElem, HandoverCancel *pvalue)
{
   pElem->procedureCode = 10;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverCancel;
   pElem->value.u.handoverCancel = pvalue;
}

void asn1SetTC_InitiatingMessage_handoverPreparation
   (OSCTXT* pctxt, InitiatingMessage* pElem, HandoverRequired *pvalue)
{
   pElem->procedureCode = 12;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverPreparation;
   pElem->value.u.handoverPreparation = pvalue;
}

void asn1SetTC_InitiatingMessage_handoverResourceAllocation
   (OSCTXT* pctxt, InitiatingMessage* pElem, HandoverRequest *pvalue)
{
   pElem->procedureCode = 13;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverResourceAllocation;
   pElem->value.u.handoverResourceAllocation = pvalue;
}

void asn1SetTC_InitiatingMessage_initialContextSetup
   (OSCTXT* pctxt, InitiatingMessage* pElem, InitialContextSetupRequest *pvalue)
{
   pElem->procedureCode = 14;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_initialContextSetup;
   pElem->value.u.initialContextSetup = pvalue;
}

void asn1SetTC_InitiatingMessage_nGReset
   (OSCTXT* pctxt, InitiatingMessage* pElem, NGReset *pvalue)
{
   pElem->procedureCode = 20;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGReset;
   pElem->value.u.nGReset = pvalue;
}

void asn1SetTC_InitiatingMessage_nGSetup
   (OSCTXT* pctxt, InitiatingMessage* pElem, NGSetupRequest *pvalue)
{
   pElem->procedureCode = 21;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGSetup;
   pElem->value.u.nGSetup = pvalue;
}

void asn1SetTC_InitiatingMessage_pathSwitchRequest
   (OSCTXT* pctxt, InitiatingMessage* pElem, PathSwitchRequest *pvalue)
{
   pElem->procedureCode = 25;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pathSwitchRequest;
   pElem->value.u.pathSwitchRequest = pvalue;
}

void asn1SetTC_InitiatingMessage_pDUSessionResourceModify
   (OSCTXT* pctxt, InitiatingMessage* pElem, PDUSessionResourceModifyRequest *pvalue)
{
   pElem->procedureCode = 26;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceModify;
   pElem->value.u.pDUSessionResourceModify = pvalue;
}

void asn1SetTC_InitiatingMessage_pDUSessionResourceModifyIndication
   (OSCTXT* pctxt, InitiatingMessage* pElem, PDUSessionResourceModifyIndication *pvalue)
{
   pElem->procedureCode = 27;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceModifyIndication;
   pElem->value.u.pDUSessionResourceModifyIndication = pvalue;
}

void asn1SetTC_InitiatingMessage_pDUSessionResourceRelease
   (OSCTXT* pctxt, InitiatingMessage* pElem, PDUSessionResourceReleaseCommand *pvalue)
{
   pElem->procedureCode = 28;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceRelease;
   pElem->value.u.pDUSessionResourceRelease = pvalue;
}

void asn1SetTC_InitiatingMessage_pDUSessionResourceSetup
   (OSCTXT* pctxt, InitiatingMessage* pElem, PDUSessionResourceSetupRequest *pvalue)
{
   pElem->procedureCode = 29;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceSetup;
   pElem->value.u.pDUSessionResourceSetup = pvalue;
}

void asn1SetTC_InitiatingMessage_pWSCancel
   (OSCTXT* pctxt, InitiatingMessage* pElem, PWSCancelRequest *pvalue)
{
   pElem->procedureCode = 32;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pWSCancel;
   pElem->value.u.pWSCancel = pvalue;
}

void asn1SetTC_InitiatingMessage_rANConfigurationUpdate
   (OSCTXT* pctxt, InitiatingMessage* pElem, RANConfigurationUpdate *pvalue)
{
   pElem->procedureCode = 35;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rANConfigurationUpdate;
   pElem->value.u.rANConfigurationUpdate = pvalue;
}

void asn1SetTC_InitiatingMessage_uEContextModification
   (OSCTXT* pctxt, InitiatingMessage* pElem, UEContextModificationRequest *pvalue)
{
   pElem->procedureCode = 40;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextModification;
   pElem->value.u.uEContextModification = pvalue;
}

void asn1SetTC_InitiatingMessage_uEContextRelease
   (OSCTXT* pctxt, InitiatingMessage* pElem, UEContextReleaseCommand *pvalue)
{
   pElem->procedureCode = 41;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextRelease;
   pElem->value.u.uEContextRelease = pvalue;
}

void asn1SetTC_InitiatingMessage_uERadioCapabilityCheck
   (OSCTXT* pctxt, InitiatingMessage* pElem, UERadioCapabilityCheckRequest *pvalue)
{
   pElem->procedureCode = 43;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uERadioCapabilityCheck;
   pElem->value.u.uERadioCapabilityCheck = pvalue;
}

void asn1SetTC_InitiatingMessage_writeReplaceWarning
   (OSCTXT* pctxt, InitiatingMessage* pElem, WriteReplaceWarningRequest *pvalue)
{
   pElem->procedureCode = 51;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_writeReplaceWarning;
   pElem->value.u.writeReplaceWarning = pvalue;
}

void asn1SetTC_InitiatingMessage_aMFStatusIndication
   (OSCTXT* pctxt, InitiatingMessage* pElem, AMFStatusIndication *pvalue)
{
   pElem->procedureCode = 1;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_aMFStatusIndication;
   pElem->value.u.aMFStatusIndication = pvalue;
}

void asn1SetTC_InitiatingMessage_cellTrafficTrace
   (OSCTXT* pctxt, InitiatingMessage* pElem, CellTrafficTrace *pvalue)
{
   pElem->procedureCode = 2;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_cellTrafficTrace;
   pElem->value.u.cellTrafficTrace = pvalue;
}

void asn1SetTC_InitiatingMessage_deactivateTrace
   (OSCTXT* pctxt, InitiatingMessage* pElem, DeactivateTrace *pvalue)
{
   pElem->procedureCode = 3;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_deactivateTrace;
   pElem->value.u.deactivateTrace = pvalue;
}

void asn1SetTC_InitiatingMessage_downlinkNASTransport
   (OSCTXT* pctxt, InitiatingMessage* pElem, DownlinkNASTransport *pvalue)
{
   pElem->procedureCode = 4;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkNASTransport;
   pElem->value.u.downlinkNASTransport = pvalue;
}

void asn1SetTC_InitiatingMessage_downlinkNonUEAssociatedNRPPaTransport
   (OSCTXT* pctxt, InitiatingMessage* pElem, DownlinkNonUEAssociatedNRPPaTransport *pvalue)
{
   pElem->procedureCode = 5;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkNonUEAssociatedNRPPaTransport;
   pElem->value.u.downlinkNonUEAssociatedNRPPaTransport = pvalue;
}

void asn1SetTC_InitiatingMessage_downlinkRANConfigurationTransfer
   (OSCTXT* pctxt, InitiatingMessage* pElem, DownlinkRANConfigurationTransfer *pvalue)
{
   pElem->procedureCode = 6;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkRANConfigurationTransfer;
   pElem->value.u.downlinkRANConfigurationTransfer = pvalue;
}

void asn1SetTC_InitiatingMessage_downlinkRANStatusTransfer
   (OSCTXT* pctxt, InitiatingMessage* pElem, DownlinkRANStatusTransfer *pvalue)
{
   pElem->procedureCode = 7;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkRANStatusTransfer;
   pElem->value.u.downlinkRANStatusTransfer = pvalue;
}

void asn1SetTC_InitiatingMessage_downlinkUEAssociatedNRPPaTransport
   (OSCTXT* pctxt, InitiatingMessage* pElem, DownlinkUEAssociatedNRPPaTransport *pvalue)
{
   pElem->procedureCode = 8;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_downlinkUEAssociatedNRPPaTransport;
   pElem->value.u.downlinkUEAssociatedNRPPaTransport = pvalue;
}

void asn1SetTC_InitiatingMessage_errorIndication
   (OSCTXT* pctxt, InitiatingMessage* pElem, ErrorIndication *pvalue)
{
   pElem->procedureCode = 9;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_errorIndication;
   pElem->value.u.errorIndication = pvalue;
}

void asn1SetTC_InitiatingMessage_handoverNotification
   (OSCTXT* pctxt, InitiatingMessage* pElem, HandoverNotify *pvalue)
{
   pElem->procedureCode = 11;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverNotification;
   pElem->value.u.handoverNotification = pvalue;
}

void asn1SetTC_InitiatingMessage_initialUEMessage
   (OSCTXT* pctxt, InitiatingMessage* pElem, InitialUEMessage *pvalue)
{
   pElem->procedureCode = 15;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_initialUEMessage;
   pElem->value.u.initialUEMessage = pvalue;
}

void asn1SetTC_InitiatingMessage_locationReport
   (OSCTXT* pctxt, InitiatingMessage* pElem, LocationReport *pvalue)
{
   pElem->procedureCode = 18;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_locationReport;
   pElem->value.u.locationReport = pvalue;
}

void asn1SetTC_InitiatingMessage_locationReportingControl
   (OSCTXT* pctxt, InitiatingMessage* pElem, LocationReportingControl *pvalue)
{
   pElem->procedureCode = 16;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_locationReportingControl;
   pElem->value.u.locationReportingControl = pvalue;
}

void asn1SetTC_InitiatingMessage_locationReportingFailureIndication
   (OSCTXT* pctxt, InitiatingMessage* pElem, LocationReportingFailureIndication *pvalue)
{
   pElem->procedureCode = 17;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_locationReportingFailureIndication;
   pElem->value.u.locationReportingFailureIndication = pvalue;
}

void asn1SetTC_InitiatingMessage_nASNonDeliveryIndication
   (OSCTXT* pctxt, InitiatingMessage* pElem, NASNonDeliveryIndication *pvalue)
{
   pElem->procedureCode = 19;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nASNonDeliveryIndication;
   pElem->value.u.nASNonDeliveryIndication = pvalue;
}

void asn1SetTC_InitiatingMessage_overloadStart
   (OSCTXT* pctxt, InitiatingMessage* pElem, OverloadStart *pvalue)
{
   pElem->procedureCode = 22;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_overloadStart;
   pElem->value.u.overloadStart = pvalue;
}

void asn1SetTC_InitiatingMessage_overloadStop
   (OSCTXT* pctxt, InitiatingMessage* pElem, OverloadStop *pvalue)
{
   pElem->procedureCode = 23;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_overloadStop;
   pElem->value.u.overloadStop = pvalue;
}

void asn1SetTC_InitiatingMessage_paging
   (OSCTXT* pctxt, InitiatingMessage* pElem, Paging *pvalue)
{
   pElem->procedureCode = 24;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_paging;
   pElem->value.u.paging = pvalue;
}

void asn1SetTC_InitiatingMessage_pDUSessionResourceNotify
   (OSCTXT* pctxt, InitiatingMessage* pElem, PDUSessionResourceNotify *pvalue)
{
   pElem->procedureCode = 30;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceNotify;
   pElem->value.u.pDUSessionResourceNotify = pvalue;
}

void asn1SetTC_InitiatingMessage_privateMessage
   (OSCTXT* pctxt, InitiatingMessage* pElem, PrivateMessage *pvalue)
{
   pElem->procedureCode = 31;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_privateMessage;
   pElem->value.u.privateMessage = pvalue;
}

void asn1SetTC_InitiatingMessage_pWSFailureIndication
   (OSCTXT* pctxt, InitiatingMessage* pElem, PWSFailureIndication *pvalue)
{
   pElem->procedureCode = 33;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pWSFailureIndication;
   pElem->value.u.pWSFailureIndication = pvalue;
}

void asn1SetTC_InitiatingMessage_pWSRestartIndication
   (OSCTXT* pctxt, InitiatingMessage* pElem, PWSRestartIndication *pvalue)
{
   pElem->procedureCode = 34;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pWSRestartIndication;
   pElem->value.u.pWSRestartIndication = pvalue;
}

void asn1SetTC_InitiatingMessage_rerouteNASRequest
   (OSCTXT* pctxt, InitiatingMessage* pElem, RerouteNASRequest *pvalue)
{
   pElem->procedureCode = 36;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rerouteNASRequest;
   pElem->value.u.rerouteNASRequest = pvalue;
}

void asn1SetTC_InitiatingMessage_rRCInactiveTransitionReport
   (OSCTXT* pctxt, InitiatingMessage* pElem, RRCInactiveTransitionReport *pvalue)
{
   pElem->procedureCode = 37;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rRCInactiveTransitionReport;
   pElem->value.u.rRCInactiveTransitionReport = pvalue;
}

void asn1SetTC_InitiatingMessage_secondaryRATDataUsageReport
   (OSCTXT* pctxt, InitiatingMessage* pElem, SecondaryRATDataUsageReport *pvalue)
{
   pElem->procedureCode = 52;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_secondaryRATDataUsageReport;
   pElem->value.u.secondaryRATDataUsageReport = pvalue;
}

void asn1SetTC_InitiatingMessage_traceFailureIndication
   (OSCTXT* pctxt, InitiatingMessage* pElem, TraceFailureIndication *pvalue)
{
   pElem->procedureCode = 38;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_traceFailureIndication;
   pElem->value.u.traceFailureIndication = pvalue;
}

void asn1SetTC_InitiatingMessage_traceStart
   (OSCTXT* pctxt, InitiatingMessage* pElem, TraceStart *pvalue)
{
   pElem->procedureCode = 39;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_traceStart;
   pElem->value.u.traceStart = pvalue;
}

void asn1SetTC_InitiatingMessage_uEContextReleaseRequest
   (OSCTXT* pctxt, InitiatingMessage* pElem, UEContextReleaseRequest *pvalue)
{
   pElem->procedureCode = 42;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextReleaseRequest;
   pElem->value.u.uEContextReleaseRequest = pvalue;
}

void asn1SetTC_InitiatingMessage_uERadioCapabilityInfoIndication
   (OSCTXT* pctxt, InitiatingMessage* pElem, UERadioCapabilityInfoIndication *pvalue)
{
   pElem->procedureCode = 44;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uERadioCapabilityInfoIndication;
   pElem->value.u.uERadioCapabilityInfoIndication = pvalue;
}

void asn1SetTC_InitiatingMessage_uETNLABindingRelease
   (OSCTXT* pctxt, InitiatingMessage* pElem, UETNLABindingReleaseRequest *pvalue)
{
   pElem->procedureCode = 45;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uETNLABindingRelease;
   pElem->value.u.uETNLABindingRelease = pvalue;
}

void asn1SetTC_InitiatingMessage_uplinkNASTransport
   (OSCTXT* pctxt, InitiatingMessage* pElem, UplinkNASTransport *pvalue)
{
   pElem->procedureCode = 46;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkNASTransport;
   pElem->value.u.uplinkNASTransport = pvalue;
}

void asn1SetTC_InitiatingMessage_uplinkNonUEAssociatedNRPPaTransport
   (OSCTXT* pctxt, InitiatingMessage* pElem, UplinkNonUEAssociatedNRPPaTransport *pvalue)
{
   pElem->procedureCode = 47;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkNonUEAssociatedNRPPaTransport;
   pElem->value.u.uplinkNonUEAssociatedNRPPaTransport = pvalue;
}

void asn1SetTC_InitiatingMessage_uplinkRANConfigurationTransfer
   (OSCTXT* pctxt, InitiatingMessage* pElem, UplinkRANConfigurationTransfer *pvalue)
{
   pElem->procedureCode = 48;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkRANConfigurationTransfer;
   pElem->value.u.uplinkRANConfigurationTransfer = pvalue;
}

void asn1SetTC_InitiatingMessage_uplinkRANStatusTransfer
   (OSCTXT* pctxt, InitiatingMessage* pElem, UplinkRANStatusTransfer *pvalue)
{
   pElem->procedureCode = 49;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkRANStatusTransfer;
   pElem->value.u.uplinkRANStatusTransfer = pvalue;
}

void asn1SetTC_InitiatingMessage_uplinkUEAssociatedNRPPaTransport
   (OSCTXT* pctxt, InitiatingMessage* pElem, UplinkUEAssociatedNRPPaTransport *pvalue)
{
   pElem->procedureCode = 50;
   pElem->criticality = ignore;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uplinkUEAssociatedNRPPaTransport;
   pElem->value.u.uplinkUEAssociatedNRPPaTransport = pvalue;
}

int asn1Init_InitiatingMessage (InitiatingMessage* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->value, 0, sizeof(pvalue->value));
   return 0;
}

/* SuccessfulOutcome */

void asn1SetTC_SuccessfulOutcome_aMFConfigurationUpdate
   (OSCTXT* pctxt, SuccessfulOutcome* pElem, AMFConfigurationUpdateAcknowledge *pvalue)
{
   pElem->procedureCode = 0;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_aMFConfigurationUpdate;
   pElem->value.u.aMFConfigurationUpdate = pvalue;
}

void asn1SetTC_SuccessfulOutcome_handoverCancel
   (OSCTXT* pctxt, SuccessfulOutcome* pElem, HandoverCancelAcknowledge *pvalue)
{
   pElem->procedureCode = 10;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverCancel;
   pElem->value.u.handoverCancel = pvalue;
}

void asn1SetTC_SuccessfulOutcome_handoverPreparation
   (OSCTXT* pctxt, SuccessfulOutcome* pElem, HandoverCommand *pvalue)
{
   pElem->procedureCode = 12;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverPreparation;
   pElem->value.u.handoverPreparation = pvalue;
}

void asn1SetTC_SuccessfulOutcome_handoverResourceAllocation
   (OSCTXT* pctxt, SuccessfulOutcome* pElem, HandoverRequestAcknowledge *pvalue)
{
   pElem->procedureCode = 13;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverResourceAllocation;
   pElem->value.u.handoverResourceAllocation = pvalue;
}

void asn1SetTC_SuccessfulOutcome_initialContextSetup
   (OSCTXT* pctxt, SuccessfulOutcome* pElem, InitialContextSetupResponse *pvalue)
{
   pElem->procedureCode = 14;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_initialContextSetup;
   pElem->value.u.initialContextSetup = pvalue;
}

void asn1SetTC_SuccessfulOutcome_nGReset
   (OSCTXT* pctxt, SuccessfulOutcome* pElem, NGResetAcknowledge *pvalue)
{
   pElem->procedureCode = 20;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGReset;
   pElem->value.u.nGReset = pvalue;
}

void asn1SetTC_SuccessfulOutcome_nGSetup
   (OSCTXT* pctxt, SuccessfulOutcome* pElem, NGSetupResponse *pvalue)
{
   pElem->procedureCode = 21;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGSetup;
   pElem->value.u.nGSetup = pvalue;
}

void asn1SetTC_SuccessfulOutcome_pathSwitchRequest
   (OSCTXT* pctxt, SuccessfulOutcome* pElem, PathSwitchRequestAcknowledge *pvalue)
{
   pElem->procedureCode = 25;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pathSwitchRequest;
   pElem->value.u.pathSwitchRequest = pvalue;
}

void asn1SetTC_SuccessfulOutcome_pDUSessionResourceModify
   (OSCTXT* pctxt, SuccessfulOutcome* pElem, PDUSessionResourceModifyResponse *pvalue)
{
   pElem->procedureCode = 26;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceModify;
   pElem->value.u.pDUSessionResourceModify = pvalue;
}

void asn1SetTC_SuccessfulOutcome_pDUSessionResourceModifyIndication
   (OSCTXT* pctxt, SuccessfulOutcome* pElem, PDUSessionResourceModifyConfirm *pvalue)
{
   pElem->procedureCode = 27;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceModifyIndication;
   pElem->value.u.pDUSessionResourceModifyIndication = pvalue;
}

void asn1SetTC_SuccessfulOutcome_pDUSessionResourceRelease
   (OSCTXT* pctxt, SuccessfulOutcome* pElem, PDUSessionResourceReleaseResponse *pvalue)
{
   pElem->procedureCode = 28;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceRelease;
   pElem->value.u.pDUSessionResourceRelease = pvalue;
}

void asn1SetTC_SuccessfulOutcome_pDUSessionResourceSetup
   (OSCTXT* pctxt, SuccessfulOutcome* pElem, PDUSessionResourceSetupResponse *pvalue)
{
   pElem->procedureCode = 29;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pDUSessionResourceSetup;
   pElem->value.u.pDUSessionResourceSetup = pvalue;
}

void asn1SetTC_SuccessfulOutcome_pWSCancel
   (OSCTXT* pctxt, SuccessfulOutcome* pElem, PWSCancelResponse *pvalue)
{
   pElem->procedureCode = 32;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pWSCancel;
   pElem->value.u.pWSCancel = pvalue;
}

void asn1SetTC_SuccessfulOutcome_rANConfigurationUpdate
   (OSCTXT* pctxt, SuccessfulOutcome* pElem, RANConfigurationUpdateAcknowledge *pvalue)
{
   pElem->procedureCode = 35;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rANConfigurationUpdate;
   pElem->value.u.rANConfigurationUpdate = pvalue;
}

void asn1SetTC_SuccessfulOutcome_uEContextModification
   (OSCTXT* pctxt, SuccessfulOutcome* pElem, UEContextModificationResponse *pvalue)
{
   pElem->procedureCode = 40;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextModification;
   pElem->value.u.uEContextModification = pvalue;
}

void asn1SetTC_SuccessfulOutcome_uEContextRelease
   (OSCTXT* pctxt, SuccessfulOutcome* pElem, UEContextReleaseComplete *pvalue)
{
   pElem->procedureCode = 41;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextRelease;
   pElem->value.u.uEContextRelease = pvalue;
}

void asn1SetTC_SuccessfulOutcome_uERadioCapabilityCheck
   (OSCTXT* pctxt, SuccessfulOutcome* pElem, UERadioCapabilityCheckResponse *pvalue)
{
   pElem->procedureCode = 43;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uERadioCapabilityCheck;
   pElem->value.u.uERadioCapabilityCheck = pvalue;
}

void asn1SetTC_SuccessfulOutcome_writeReplaceWarning
   (OSCTXT* pctxt, SuccessfulOutcome* pElem, WriteReplaceWarningResponse *pvalue)
{
   pElem->procedureCode = 51;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_writeReplaceWarning;
   pElem->value.u.writeReplaceWarning = pvalue;
}

int asn1Init_SuccessfulOutcome (SuccessfulOutcome* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->value, 0, sizeof(pvalue->value));
   return 0;
}

/* UnsuccessfulOutcome */

void asn1SetTC_UnsuccessfulOutcome_aMFConfigurationUpdate
   (OSCTXT* pctxt, UnsuccessfulOutcome* pElem, AMFConfigurationUpdateFailure *pvalue)
{
   pElem->procedureCode = 0;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_aMFConfigurationUpdate;
   pElem->value.u.aMFConfigurationUpdate = pvalue;
}

void asn1SetTC_UnsuccessfulOutcome_handoverPreparation
   (OSCTXT* pctxt, UnsuccessfulOutcome* pElem, HandoverPreparationFailure *pvalue)
{
   pElem->procedureCode = 12;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverPreparation;
   pElem->value.u.handoverPreparation = pvalue;
}

void asn1SetTC_UnsuccessfulOutcome_handoverResourceAllocation
   (OSCTXT* pctxt, UnsuccessfulOutcome* pElem, HandoverFailure *pvalue)
{
   pElem->procedureCode = 13;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_handoverResourceAllocation;
   pElem->value.u.handoverResourceAllocation = pvalue;
}

void asn1SetTC_UnsuccessfulOutcome_initialContextSetup
   (OSCTXT* pctxt, UnsuccessfulOutcome* pElem, InitialContextSetupFailure *pvalue)
{
   pElem->procedureCode = 14;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_initialContextSetup;
   pElem->value.u.initialContextSetup = pvalue;
}

void asn1SetTC_UnsuccessfulOutcome_nGSetup
   (OSCTXT* pctxt, UnsuccessfulOutcome* pElem, NGSetupFailure *pvalue)
{
   pElem->procedureCode = 21;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_nGSetup;
   pElem->value.u.nGSetup = pvalue;
}

void asn1SetTC_UnsuccessfulOutcome_pathSwitchRequest
   (OSCTXT* pctxt, UnsuccessfulOutcome* pElem, PathSwitchRequestFailure *pvalue)
{
   pElem->procedureCode = 25;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_pathSwitchRequest;
   pElem->value.u.pathSwitchRequest = pvalue;
}

void asn1SetTC_UnsuccessfulOutcome_rANConfigurationUpdate
   (OSCTXT* pctxt, UnsuccessfulOutcome* pElem, RANConfigurationUpdateFailure *pvalue)
{
   pElem->procedureCode = 35;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_rANConfigurationUpdate;
   pElem->value.u.rANConfigurationUpdate = pvalue;
}

void asn1SetTC_UnsuccessfulOutcome_uEContextModification
   (OSCTXT* pctxt, UnsuccessfulOutcome* pElem, UEContextModificationFailure *pvalue)
{
   pElem->procedureCode = 40;
   pElem->criticality = reject;
   pElem->value.t = T_NGAP_PDU_Descriptions_NGAP_ELEMENTARY_PROCEDURES_uEContextModification;
   pElem->value.u.uEContextModification = pvalue;
}

int asn1Init_UnsuccessfulOutcome (UnsuccessfulOutcome* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   OSCRTLMEMSET (&pvalue->value, 0, sizeof(pvalue->value));
   return 0;
}

/* NGAP_PDU */

int asn1Init_NGAP_PDU (NGAP_PDU* pvalue)
{
   if (0 == pvalue) return RTERR_NULLPTR;
   pvalue->t = 0;
   OSCRTLMEMSET (&pvalue->u, 0, sizeof(pvalue->u));
   return 0;
}

