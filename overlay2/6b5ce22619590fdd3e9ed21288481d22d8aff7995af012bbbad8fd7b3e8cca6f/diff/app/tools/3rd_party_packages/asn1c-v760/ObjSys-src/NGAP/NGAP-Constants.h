/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.6.0, Date: 21-Feb-2022.
 */
#ifndef NGAP_CONSTANTS_H
#define NGAP_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "rtkey.h"
#include "rtxsrc/rtxCommon.h"
#include "rtpersrc/asn1per.h"

#include "NGAP-CommonDataTypes.h"

/**
 * Header file for ASN.1 module NGAP-Constants
 */
/* Value definitions */

#define ASN1V_id_AMFConfigurationUpdate 0
#define ASN1V_id_AMFStatusIndication 1
#define ASN1V_id_CellTrafficTrace 2
#define ASN1V_id_DeactivateTrace 3
#define ASN1V_id_DownlinkNASTransport 4
#define ASN1V_id_DownlinkNonUEAssociatedNRPPaTransport 5
#define ASN1V_id_DownlinkRANConfigurationTransfer 6
#define ASN1V_id_DownlinkRANStatusTransfer 7
#define ASN1V_id_DownlinkUEAssociatedNRPPaTransport 8
#define ASN1V_id_ErrorIndication 9
#define ASN1V_id_HandoverCancel 10
#define ASN1V_id_HandoverNotification 11
#define ASN1V_id_HandoverPreparation 12
#define ASN1V_id_HandoverResourceAllocation 13
#define ASN1V_id_InitialContextSetup 14
#define ASN1V_id_InitialUEMessage 15
#define ASN1V_id_LocationReportingControl 16
#define ASN1V_id_LocationReportingFailureIndication 17
#define ASN1V_id_LocationReport 18
#define ASN1V_id_NASNonDeliveryIndication 19
#define ASN1V_id_NGReset 20
#define ASN1V_id_NGSetup 21
#define ASN1V_id_OverloadStart 22
#define ASN1V_id_OverloadStop 23
#define ASN1V_id_Paging 24
#define ASN1V_id_PathSwitchRequest 25
#define ASN1V_id_PDUSessionResourceModify 26
#define ASN1V_id_PDUSessionResourceModifyIndication 27
#define ASN1V_id_PDUSessionResourceRelease 28
#define ASN1V_id_PDUSessionResourceSetup 29
#define ASN1V_id_PDUSessionResourceNotify 30
#define ASN1V_id_PrivateMessage 31
#define ASN1V_id_PWSCancel 32
#define ASN1V_id_PWSFailureIndication 33
#define ASN1V_id_PWSRestartIndication 34
#define ASN1V_id_RANConfigurationUpdate 35
#define ASN1V_id_RerouteNASRequest 36
#define ASN1V_id_RRCInactiveTransitionReport 37
#define ASN1V_id_TraceFailureIndication 38
#define ASN1V_id_TraceStart 39
#define ASN1V_id_UEContextModification 40
#define ASN1V_id_UEContextRelease 41
#define ASN1V_id_UEContextReleaseRequest 42
#define ASN1V_id_UERadioCapabilityCheck 43
#define ASN1V_id_UERadioCapabilityInfoIndication 44
#define ASN1V_id_UETNLABindingRelease 45
#define ASN1V_id_UplinkNASTransport 46
#define ASN1V_id_UplinkNonUEAssociatedNRPPaTransport 47
#define ASN1V_id_UplinkRANConfigurationTransfer 48
#define ASN1V_id_UplinkRANStatusTransfer 49
#define ASN1V_id_UplinkUEAssociatedNRPPaTransport 50
#define ASN1V_id_WriteReplaceWarning 51
#define ASN1V_id_SecondaryRATDataUsageReport 52
#define ASN1V_id_UplinkRIMInformationTransfer 53
#define ASN1V_id_DownlinkRIMInformationTransfer 54
#define ASN1V_id_RetrieveUEInformation 55
#define ASN1V_id_UEInformationTransfer 56
#define ASN1V_id_RANCPRelocationIndication 57
#define ASN1V_id_UEContextResume 58
#define ASN1V_id_UEContextSuspend 59
#define ASN1V_id_UERadioCapabilityIDMapping 60
#define ASN1V_id_HandoverSuccess 61
#define ASN1V_id_UplinkRANEarlyStatusTransfer 62
#define ASN1V_id_DownlinkRANEarlyStatusTransfer 63
#define ASN1V_id_AMFCPRelocationIndication 64
#define ASN1V_id_ConnectionEstablishmentIndication 65
#define ASN1V_maxPrivateIEs 65535
#define ASN1V_maxProtocolExtensions 65535
#define ASN1V_maxProtocolIEs 65535
#define ASN1V_maxnoofAllowedAreas 16
#define ASN1V_maxnoofAllowedCAGsperPLMN 256
#define ASN1V_maxnoofAllowedS_NSSAIs 8
#define ASN1V_maxnoofBluetoothName 4
#define ASN1V_maxnoofBPLMNs 12
#define ASN1V_maxnoofCAGSperCell 64
#define ASN1V_maxnoofCellIDforMDT 32
#define ASN1V_maxnoofCellIDforWarning 65535
#define ASN1V_maxnoofCellinAoI 256
#define ASN1V_maxnoofCellinEAI 65535
#define ASN1V_maxnoofCellinTAI 65535
#define ASN1V_maxnoofCellsingNB 16384
#define ASN1V_maxnoofCellsinngeNB 256
#define ASN1V_maxnoofCellsinUEHistoryInfo 16
#define ASN1V_maxnoofCellsUEMovingTrajectory 16
#define ASN1V_maxnoofDRBs 32
#define ASN1V_maxnoofEmergencyAreaID 65535
#define ASN1V_maxnoofEAIforRestart 256
#define ASN1V_maxnoofEPLMNs 15
#define ASN1V_maxnoofEPLMNsPlusOne 16
#define ASN1V_maxnoofE_RABs 256
#define ASN1V_maxnoofErrors 256
#define ASN1V_maxnoofExtSliceItems 65535
#define ASN1V_maxnoofForbTACs 4096
#define ASN1V_maxnoofFreqforMDT 8
#define ASN1V_maxnoofMDTPLMNs 16
#define ASN1V_maxnoofMultiConnectivity 4
#define ASN1V_maxnoofMultiConnectivityMinusOne 3
#define ASN1V_maxnoofNeighPCIforMDT 32
#define ASN1V_maxnoofNGConnectionsToReset 65536
#define ASN1V_maxnoofNRCellBands 32
#define ASN1V_maxnoofPC5QoSFlows 2048
#define ASN1V_maxnoofPDUSessions 256
#define ASN1V_maxnoofPLMNs 12
#define ASN1V_maxnoofQosFlows 64
#define ASN1V_maxnoofQosParaSets 8
#define ASN1V_maxnoofRANNodeinAoI 64
#define ASN1V_maxnoofRecommendedCells 16
#define ASN1V_maxnoofRecommendedRANNodes 16
#define ASN1V_maxnoofAoI 64
#define ASN1V_maxnoofSensorName 3
#define ASN1V_maxnoofServedGUAMIs 256
#define ASN1V_maxnoofSliceItems 1024
#define ASN1V_maxnoofTACs 256
#define ASN1V_maxnoofTAforMDT 8
#define ASN1V_maxnoofTAIforInactive 16
#define ASN1V_maxnoofTAIforPaging 16
#define ASN1V_maxnoofTAIforRestart 2048
#define ASN1V_maxnoofTAIforWarning 65535
#define ASN1V_maxnoofTAIinAoI 16
#define ASN1V_maxnoofTimePeriods 2
#define ASN1V_maxnoofTNLAssociations 32
#define ASN1V_maxnoofWLANName 4
#define ASN1V_maxnoofXnExtTLAs 16
#define ASN1V_maxnoofXnGTP_TLAs 16
#define ASN1V_maxnoofXnTLAs 2
#define ASN1V_maxnoofCandidateCells 32
#define ASN1V_maxNRARFCN 3279165
#define ASN1V_id_AllowedNSSAI 0
#define ASN1V_id_AMFName 1
#define ASN1V_id_AMFOverloadResponse 2
#define ASN1V_id_AMFSetID 3
#define ASN1V_id_AMF_TNLAssociationFailedToSetupList 4
#define ASN1V_id_AMF_TNLAssociationSetupList 5
#define ASN1V_id_AMF_TNLAssociationToAddList 6
#define ASN1V_id_AMF_TNLAssociationToRemoveList 7
#define ASN1V_id_AMF_TNLAssociationToUpdateList 8
#define ASN1V_id_AMFTrafficLoadReductionIndication 9
#define ASN1V_id_AMF_UE_NGAP_ID 10
#define ASN1V_id_AssistanceDataForPaging 11
#define ASN1V_id_BroadcastCancelledAreaList 12
#define ASN1V_id_BroadcastCompletedAreaList 13
#define ASN1V_id_CancelAllWarningMessages 14
#define ASN1V_id_Cause 15
#define ASN1V_id_CellIDListForRestart 16
#define ASN1V_id_ConcurrentWarningMessageInd 17
#define ASN1V_id_CoreNetworkAssistanceInformationForInactive 18
#define ASN1V_id_CriticalityDiagnostics 19
#define ASN1V_id_DataCodingScheme 20
#define ASN1V_id_DefaultPagingDRX 21
#define ASN1V_id_DirectForwardingPathAvailability 22
#define ASN1V_id_EmergencyAreaIDListForRestart 23
#define ASN1V_id_EmergencyFallbackIndicator 24
#define ASN1V_id_EUTRA_CGI 25
#define ASN1V_id_FiveG_S_TMSI 26
#define ASN1V_id_GlobalRANNodeID 27
#define ASN1V_id_GUAMI 28
#define ASN1V_id_HandoverType 29
#define ASN1V_id_IMSVoiceSupportIndicator 30
#define ASN1V_id_IndexToRFSP 31
#define ASN1V_id_InfoOnRecommendedCellsAndRANNodesForPaging 32
#define ASN1V_id_LocationReportingRequestType 33
#define ASN1V_id_MaskedIMEISV 34
#define ASN1V_id_MessageIdentifier 35
#define ASN1V_id_MobilityRestrictionList 36
#define ASN1V_id_NASC 37
#define ASN1V_id_NAS_PDU 38
#define ASN1V_id_NASSecurityParametersFromNGRAN 39
#define ASN1V_id_NewAMF_UE_NGAP_ID 40
#define ASN1V_id_NewSecurityContextInd 41
#define ASN1V_id_NGAP_Message 42
#define ASN1V_id_NGRAN_CGI 43
#define ASN1V_id_NGRANTraceID 44
#define ASN1V_id_NR_CGI 45
#define ASN1V_id_NRPPa_PDU 46
#define ASN1V_id_NumberOfBroadcastsRequested 47
#define ASN1V_id_OldAMF 48
#define ASN1V_id_OverloadStartNSSAIList 49
#define ASN1V_id_PagingDRX 50
#define ASN1V_id_PagingOrigin 51
#define ASN1V_id_PagingPriority 52
#define ASN1V_id_PDUSessionResourceAdmittedList 53
#define ASN1V_id_PDUSessionResourceFailedToModifyListModRes 54
#define ASN1V_id_PDUSessionResourceFailedToSetupListCxtRes 55
#define ASN1V_id_PDUSessionResourceFailedToSetupListHOAck 56
#define ASN1V_id_PDUSessionResourceFailedToSetupListPSReq 57
#define ASN1V_id_PDUSessionResourceFailedToSetupListSURes 58
#define ASN1V_id_PDUSessionResourceHandoverList 59
#define ASN1V_id_PDUSessionResourceListCxtRelCpl 60
#define ASN1V_id_PDUSessionResourceListHORqd 61
#define ASN1V_id_PDUSessionResourceModifyListModCfm 62
#define ASN1V_id_PDUSessionResourceModifyListModInd 63
#define ASN1V_id_PDUSessionResourceModifyListModReq 64
#define ASN1V_id_PDUSessionResourceModifyListModRes 65
#define ASN1V_id_PDUSessionResourceNotifyList 66
#define ASN1V_id_PDUSessionResourceReleasedListNot 67
#define ASN1V_id_PDUSessionResourceReleasedListPSAck 68
#define ASN1V_id_PDUSessionResourceReleasedListPSFail 69
#define ASN1V_id_PDUSessionResourceReleasedListRelRes 70
#define ASN1V_id_PDUSessionResourceSetupListCxtReq 71
#define ASN1V_id_PDUSessionResourceSetupListCxtRes 72
#define ASN1V_id_PDUSessionResourceSetupListHOReq 73
#define ASN1V_id_PDUSessionResourceSetupListSUReq 74
#define ASN1V_id_PDUSessionResourceSetupListSURes 75
#define ASN1V_id_PDUSessionResourceToBeSwitchedDLList 76
#define ASN1V_id_PDUSessionResourceSwitchedList 77
#define ASN1V_id_PDUSessionResourceToReleaseListHOCmd 78
#define ASN1V_id_PDUSessionResourceToReleaseListRelCmd 79
#define ASN1V_id_PLMNSupportList 80
#define ASN1V_id_PWSFailedCellIDList 81
#define ASN1V_id_RANNodeName 82
#define ASN1V_id_RANPagingPriority 83
#define ASN1V_id_RANStatusTransfer_TransparentContainer 84
#define ASN1V_id_RAN_UE_NGAP_ID 85
#define ASN1V_id_RelativeAMFCapacity 86
#define ASN1V_id_RepetitionPeriod 87
#define ASN1V_id_ResetType 88
#define ASN1V_id_RoutingID 89
#define ASN1V_id_RRCEstablishmentCause 90
#define ASN1V_id_RRCInactiveTransitionReportRequest 91
#define ASN1V_id_RRCState 92
#define ASN1V_id_SecurityContext 93
#define ASN1V_id_SecurityKey 94
#define ASN1V_id_SerialNumber 95
#define ASN1V_id_ServedGUAMIList 96
#define ASN1V_id_SliceSupportList 97
#define ASN1V_id_SONConfigurationTransferDL 98
#define ASN1V_id_SONConfigurationTransferUL 99
#define ASN1V_id_SourceAMF_UE_NGAP_ID 100
#define ASN1V_id_SourceToTarget_TransparentContainer 101
#define ASN1V_id_SupportedTAList 102
#define ASN1V_id_TAIListForPaging 103
#define ASN1V_id_TAIListForRestart 104
#define ASN1V_id_TargetID 105
#define ASN1V_id_TargetToSource_TransparentContainer 106
#define ASN1V_id_TimeToWait 107
#define ASN1V_id_TraceActivation 108
#define ASN1V_id_TraceCollectionEntityIPAddress 109
#define ASN1V_id_UEAggregateMaximumBitRate 110
#define ASN1V_id_UE_associatedLogicalNG_connectionList 111
#define ASN1V_id_UEContextRequest 112
#define ASN1V_id_UE_NGAP_IDs 114
#define ASN1V_id_UEPagingIdentity 115
#define ASN1V_id_UEPresenceInAreaOfInterestList 116
#define ASN1V_id_UERadioCapability 117
#define ASN1V_id_UERadioCapabilityForPaging 118
#define ASN1V_id_UESecurityCapabilities 119
#define ASN1V_id_UnavailableGUAMIList 120
#define ASN1V_id_UserLocationInformation 121
#define ASN1V_id_WarningAreaList 122
#define ASN1V_id_WarningMessageContents 123
#define ASN1V_id_WarningSecurityInfo 124
#define ASN1V_id_WarningType 125
#define ASN1V_id_AdditionalUL_NGU_UP_TNLInformation 126
#define ASN1V_id_DataForwardingNotPossible 127
#define ASN1V_id_DL_NGU_UP_TNLInformation 128
#define ASN1V_id_NetworkInstance 129
#define ASN1V_id_PDUSessionAggregateMaximumBitRate 130
#define ASN1V_id_PDUSessionResourceFailedToModifyListModCfm 131
#define ASN1V_id_PDUSessionResourceFailedToSetupListCxtFail 132
#define ASN1V_id_PDUSessionResourceListCxtRelReq 133
#define ASN1V_id_PDUSessionType 134
#define ASN1V_id_QosFlowAddOrModifyRequestList 135
#define ASN1V_id_QosFlowSetupRequestList 136
#define ASN1V_id_QosFlowToReleaseList 137
#define ASN1V_id_SecurityIndication 138
#define ASN1V_id_UL_NGU_UP_TNLInformation 139
#define ASN1V_id_UL_NGU_UP_TNLModifyList 140
#define ASN1V_id_WarningAreaCoordinates 141
#define ASN1V_id_PDUSessionResourceSecondaryRATUsageList 142
#define ASN1V_id_HandoverFlag 143
#define ASN1V_id_SecondaryRATUsageInformation 144
#define ASN1V_id_PDUSessionResourceReleaseResponseTransfer 145
#define ASN1V_id_RedirectionVoiceFallback 146
#define ASN1V_id_UERetentionInformation 147
#define ASN1V_id_S_NSSAI 148
#define ASN1V_id_PSCellInformation 149
#define ASN1V_id_LastEUTRAN_PLMNIdentity 150
#define ASN1V_id_MaximumIntegrityProtectedDataRate_DL 151
#define ASN1V_id_AdditionalDLForwardingUPTNLInformation 152
#define ASN1V_id_AdditionalDLUPTNLInformationForHOList 153
#define ASN1V_id_AdditionalNGU_UP_TNLInformation 154
#define ASN1V_id_AdditionalDLQosFlowPerTNLInformation 155
#define ASN1V_id_SecurityResult 156
#define ASN1V_id_ENDC_SONConfigurationTransferDL 157
#define ASN1V_id_ENDC_SONConfigurationTransferUL 158
#define ASN1V_id_OldAssociatedQosFlowList_ULendmarkerexpected 159
#define ASN1V_id_CNTypeRestrictionsForEquivalent 160
#define ASN1V_id_CNTypeRestrictionsForServing 161
#define ASN1V_id_NewGUAMI 162
#define ASN1V_id_ULForwarding 163
#define ASN1V_id_ULForwardingUP_TNLInformation 164
#define ASN1V_id_CNAssistedRANTuning 165
#define ASN1V_id_CommonNetworkInstance 166
#define ASN1V_id_NGRAN_TNLAssociationToRemoveList 167
#define ASN1V_id_TNLAssociationTransportLayerAddressNGRAN 168
#define ASN1V_id_EndpointIPAddressAndPort 169
#define ASN1V_id_LocationReportingAdditionalInfo 170
#define ASN1V_id_SourceToTarget_AMFInformationReroute 171
#define ASN1V_id_AdditionalULForwardingUPTNLInformation 172
#define ASN1V_id_SCTP_TLAs 173
#define ASN1V_id_SelectedPLMNIdentity 174
#define ASN1V_id_RIMInformationTransfer 175
#define ASN1V_id_GUAMIType 176
#define ASN1V_id_SRVCCOperationPossible 177
#define ASN1V_id_TargetRNC_ID 178
#define ASN1V_id_RAT_Information 179
#define ASN1V_id_ExtendedRATRestrictionInformation 180
#define ASN1V_id_QosMonitoringRequest 181
#define ASN1V_id_SgNB_UE_X2AP_ID 182
#define ASN1V_id_AdditionalRedundantDL_NGU_UP_TNLInformation 183
#define ASN1V_id_AdditionalRedundantDLQosFlowPerTNLInformation 184
#define ASN1V_id_AdditionalRedundantNGU_UP_TNLInformation 185
#define ASN1V_id_AdditionalRedundantUL_NGU_UP_TNLInformation 186
#define ASN1V_id_CNPacketDelayBudgetDL 187
#define ASN1V_id_CNPacketDelayBudgetUL 188
#define ASN1V_id_ExtendedPacketDelayBudget 189
#define ASN1V_id_RedundantCommonNetworkInstance 190
#define ASN1V_id_RedundantDL_NGU_TNLInformationReused 191
#define ASN1V_id_RedundantDL_NGU_UP_TNLInformation 192
#define ASN1V_id_RedundantDLQosFlowPerTNLInformation 193
#define ASN1V_id_RedundantQosFlowIndicator 194
#define ASN1V_id_RedundantUL_NGU_UP_TNLInformation 195
#define ASN1V_id_TSCTrafficCharacteristics 196
#define ASN1V_id_RedundantPDUSessionInformation 197
#define ASN1V_id_UsedRSNInformation 198
#define ASN1V_id_IAB_Authorized 199
#define ASN1V_id_IAB_Supported 200
#define ASN1V_id_IABNodeIndication 201
#define ASN1V_id_NB_IoT_PagingDRX 202
#define ASN1V_id_NB_IoT_Paging_eDRXInfo 203
#define ASN1V_id_NB_IoT_DefaultPagingDRX 204
#define ASN1V_id_Enhanced_CoverageRestriction 205
#define ASN1V_id_Extended_ConnectedTime 206
#define ASN1V_id_PagingAssisDataforCEcapabUE 207
#define ASN1V_id_WUS_Assistance_Information 208
#define ASN1V_id_UE_DifferentiationInfo 209
#define ASN1V_id_NB_IoT_UEPriority 210
#define ASN1V_id_UL_CP_SecurityInformation 211
#define ASN1V_id_DL_CP_SecurityInformation 212
#define ASN1V_id_TAI 213
#define ASN1V_id_UERadioCapabilityForPagingOfNB_IoT 214
#define ASN1V_id_LTEV2XServicesAuthorized 215
#define ASN1V_id_NRV2XServicesAuthorized 216
#define ASN1V_id_LTEUESidelinkAggregateMaximumBitrate 217
#define ASN1V_id_NRUESidelinkAggregateMaximumBitrate 218
#define ASN1V_id_PC5QoSParameters 219
#define ASN1V_id_AlternativeQoSParaSetList 220
#define ASN1V_id_CurrentQoSParaSetIndex 221
#define ASN1V_id_CEmodeBrestricted 222
#define ASN1V_id_PagingeDRXInformation 223
#define ASN1V_id_CEmodeBSupport_Indicator 224
#define ASN1V_id_LTEM_Indication 225
#define ASN1V_id_EndIndication 226
#define ASN1V_id_EDT_Session 227
#define ASN1V_id_UECapabilityInfoRequest 228
#define ASN1V_id_PDUSessionResourceFailedToResumeListRESReq 229
#define ASN1V_id_PDUSessionResourceFailedToResumeListRESRes 230
#define ASN1V_id_PDUSessionResourceSuspendListSUSReq 231
#define ASN1V_id_PDUSessionResourceResumeListRESReq 232
#define ASN1V_id_PDUSessionResourceResumeListRESRes 233
#define ASN1V_id_UE_UP_CIoT_Support 234
#define ASN1V_id_Suspend_Request_Indication 235
#define ASN1V_id_Suspend_Response_Indication 236
#define ASN1V_id_RRC_Resume_Cause 237
#define ASN1V_id_RGLevelWirelineAccessCharacteristics 238
#define ASN1V_id_W_AGFIdentityInformation 239
#define ASN1V_id_GlobalTNGF_ID 240
#define ASN1V_id_GlobalTWIF_ID 241
#define ASN1V_id_GlobalW_AGF_ID 242
#define ASN1V_id_UserLocationInformationW_AGF 243
#define ASN1V_id_UserLocationInformationTNGF 244
#define ASN1V_id_AuthenticatedIndication 245
#define ASN1V_id_TNGFIdentityInformation 246
#define ASN1V_id_TWIFIdentityInformation 247
#define ASN1V_id_UserLocationInformationTWIF 248
#define ASN1V_id_DataForwardingResponseERABList 249
#define ASN1V_id_IntersystemSONConfigurationTransferDL 250
#define ASN1V_id_IntersystemSONConfigurationTransferUL 251
#define ASN1V_id_SONInformationReport 252
#define ASN1V_id_UEHistoryInformationFromTheUE 253
#define ASN1V_id_ManagementBasedMDTPLMNList 254
#define ASN1V_id_MDTConfiguration 255
#define ASN1V_id_PrivacyIndicator 256
#define ASN1V_id_TraceCollectionEntityURI 257
#define ASN1V_id_NPN_Support 258
#define ASN1V_id_NPN_AccessInformation 259
#define ASN1V_id_NPN_PagingAssistanceInformation 260
#define ASN1V_id_NPN_MobilityInformation 261
#define ASN1V_id_TargettoSource_Failure_TransparentContainer 262
#define ASN1V_id_NID 263
#define ASN1V_id_UERadioCapabilityID 264
#define ASN1V_id_UERadioCapability_EUTRA_Format 265
#define ASN1V_id_DAPSRequestInfo 266
#define ASN1V_id_DAPSResponseInfoList 267
#define ASN1V_id_EarlyStatusTransfer_TransparentContainer 268
#define ASN1V_id_NotifySourceNGRANNode 269
#define ASN1V_id_ExtendedSliceSupportList 270
#define ASN1V_id_ExtendedTAISliceSupportList 271
#define ASN1V_id_ConfiguredTACIndication 272
#define ASN1V_id_Extended_RANNodeName 273
#define ASN1V_id_Extended_AMFName 274
#define ASN1V_id_GlobalCable_ID 275
#define ASN1V_id_QosMonitoringReportingFrequency 276
#define ASN1V_id_QosFlowParametersList 277
#define ASN1V_id_QosFlowFeedbackList 278
#define ASN1V_id_BurstArrivalTimeDownlink 279
#define ASN1V_id_ExtendedUEIdentityIndexValue 280
#define ASN1V_id_PduSessionExpectedUEActivityBehaviour 281
#define ASN1V_id_MicoAllPLMN 282
#define ASN1V_id_QosFlowFailedToSetupList 283

#ifdef __cplusplus
}
#endif

#endif
