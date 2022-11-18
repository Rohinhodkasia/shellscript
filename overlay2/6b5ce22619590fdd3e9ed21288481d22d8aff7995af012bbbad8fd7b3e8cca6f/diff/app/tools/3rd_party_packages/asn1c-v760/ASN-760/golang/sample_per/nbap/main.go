package main

import (
	"encoding/hex"
	"fmt"
	"io/ioutil"
	"nbap/asn1gen"
	"nbap/asn1gen/asn1rt"
	"os"
)

func main() {
	msgfile := "message.per"
	writer := false
	if len(os.Args) > 1 {
		if os.Args[1] == "writer" {
			writer = true
		} else if os.Args[1] != "reader" {
			fmt.Println("first argument must be 'writer' or 'reader'")
			return
		}
	} else {
		fmt.Println("Usage: employee writer|reader ...")
		return
	}

	pctxt := new(asn1rt.OSRTContext)
	var pdu asn1gen.NBAPPDU

	if writer {
		/* Populate RL_InformationList_RL_setupRqstFDDElem */
		var setupRqstFDDElem asn1gen.RLInformationListRLSetupRqstFDDElement
		setupRqstFDDElem.Id = 211 // id-RL-InformationItem-RL-SetupRqstFDD
		setupRqstFDDElem.Criticality = asn1gen.CriticalityNotify
		setupRqstFDDElem.Value.RLID = 25  /*  INTEGER (0..31) */
		setupRqstFDDElem.Value.CID = 1000 /*  INTEGER (0..65535) */
		setupRqstFDDElem.Value.FirstRLSIndicator = asn1gen.FirstRLSIndicatorFirstRLS
		setupRqstFDDElem.Value.FrameOffset = 99          /*  INTEGER (0..255) */
		setupRqstFDDElem.Value.ChipOffset = 224          /*  INTEGER (0..38399) */
		propagationDelay := asn1gen.PropagationDelay(22) /* INTEGER (0..255) */
		setupRqstFDDElem.Value.PropagationDelay = &propagationDelay
		diversityControlField :=
			asn1gen.DiversityControlField(asn1gen.DiversityControlFieldMustNot)
		setupRqstFDDElem.Value.DiversityControlField = &diversityControlField

		var dlCodeInformationItem asn1gen.DLCodeInformationItemRLSetupRqstFDD
		dlCodeInformationItem.DlScramblingCode = 0
		dlCodeInformationItem.FddDLChannelisationCodeNumber = 255
		dlCodeInformationItem.TransmissionGapPatternSequenceCodeInformation =
			new(asn1gen.TransmissionGapPatternSequenceCodeInformation)
		*dlCodeInformationItem.TransmissionGapPatternSequenceCodeInformation =
			asn1gen.TransmissionGapPatternSequenceCodeInformationNocodeChange

		setupRqstFDDElem.Value.DlCodeInformationList = append(
			setupRqstFDDElem.Value.DlCodeInformationList, dlCodeInformationItem)

		setupRqstFDDElem.Value.InitialDLTransmissionPower = -22
		setupRqstFDDElem.Value.MaximumDLPower = 100
		setupRqstFDDElem.Value.MinimumDLPower = -100

		/* Populate RadioLinkSetupRequestFDD structure */

		var setupRqstFDD asn1gen.RLInformationListRLSetupRqstFDD
		setupRqstFDD = append(setupRqstFDD, setupRqstFDDElem)

		var protocolIE asn1gen.RadioLinkSetupRequestFDDProtocolIEsElement
		protocolIE.Id = 216 // id-RL-InformationList-RL-SetupRqstFDD
		protocolIE.Criticality = asn1gen.CriticalityNotify
		protocolIE.Value.T =
			asn1gen.NBAPPDUContentsRadioLinkSetupRequestFDDIEsIdRLInformationListRLSetupRqstFDDTAG
		protocolIE.Value.U.RadioLinkSetupRequestFDDIEsIdRLInformationListRLSetupRqstFDD = &setupRqstFDD

		var radioLinkSetupFDD asn1gen.RadioLinkSetupRequestFDD
		radioLinkSetupFDD.ProtocolIEs = append(radioLinkSetupFDD.ProtocolIEs, protocolIE)

		/* Populate NBAP-PDU structure */

		var initMsg asn1gen.InitiatingMessage
		initMsg.ProcedureID.ProcedureCode = 27 // id-radioLinkSetup;
		initMsg.ProcedureID.DdMode = asn1gen.ProcedureIDDdModeFdd
		initMsg.Criticality = asn1gen.CriticalityReject
		initMsg.MessageDiscriminator = asn1gen.MessageDiscriminatorCommon
		initMsg.TransactionID.T = asn1gen.TransactionIDShortTransActionIdTAG
		shortTransActionID := uint64(1)
		initMsg.TransactionID.U.ShortTransActionId = &shortTransActionID
		initMsg.Value.T = asn1gen.NBAPPDUDescriptionsNBAPELEMENTARYPROCEDURESRadioLinkSetupFDDTAG
		initMsg.Value.U.RadioLinkSetupFDD = &radioLinkSetupFDD

		var pdu asn1gen.NBAPPDU
		pdu.T = asn1gen.NBAPPDUInitiatingMessageTAG
		pdu.U.InitiatingMessage = &initMsg

		// Encode

		pctxt.InitEncode()
		pctxt.NewBitFieldList()

		err := pdu.PerEncode(pctxt)

		pctxt.FlushBuffer()
		pctxt.PrintBitFieldList("pdu")

		if err == nil {
			fmt.Printf("NBAPPDU encoded successfully\n")
			fmt.Printf("%s\n", hex.Dump(pctxt.BufferData()))
			err = ioutil.WriteFile(msgfile, pctxt.BufferData(), 0777)
		} else {
			fmt.Printf("Encoding failed: %s\n", err)
			os.Exit(1)
		}
	} else {
		encoding, err := ioutil.ReadFile(msgfile)
		if err != nil {
			fmt.Printf("Read %s failed: %s\n", msgfile, err)
			os.Exit(1)
			return
		}

		pctxt.InitDecodeBytes(encoding)
		pctxt.NewBitFieldList()

		err = pdu.PerDecode(pctxt)

		pctxt.PrintBitFieldList("pdu")

		if err == nil {
			fmt.Printf("Decoding was successful:\n")
			asn1gen.Print(pdu)
		} else {
			fmt.Printf("Decoding failed: %s\n", err)
			os.Exit(1)
		}
	}
}
