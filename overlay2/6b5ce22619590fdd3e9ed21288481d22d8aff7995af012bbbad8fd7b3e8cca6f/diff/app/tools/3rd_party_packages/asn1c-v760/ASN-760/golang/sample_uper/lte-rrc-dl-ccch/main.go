package main

import (
	"encoding/hex"
	"fmt"
	"io/ioutil"
	"lte-rrc-dl-ccch/asn1gen"
	"os"
)

func main() {
	msgfile := "message.uper"
	writer := false
	if len(os.Args) > 1 {
		if os.Args[1] == "writer" {
			writer = true
		} else if os.Args[1] != "reader" {
			fmt.Println("first argument must be 'writer' or 'reader'")
			return
		}
	} else {
		fmt.Println("Usage: lte-rrc-dl-ccch writer|reader ...")
		return
	}

	var pdu asn1gen.DLCCCHMessage
	var err error
	var encoding []byte

	if writer {
		// Populate PDU type variable to be encoded
		pdu.Message.T = asn1gen.DLCCCHMessageTypeC1TAG
		pdu.Message.U.C1 = new(asn1gen.DLCCCHMessageTypeC1)
		pdu.Message.U.C1.T = asn1gen.DLCCCHMessageTypeC1RrcConnectionSetupTAG
		pdu.Message.U.C1.U.RrcConnectionSetup = new(asn1gen.RRCConnectionSetup)
		pdu.Message.U.C1.U.RrcConnectionSetup.RrcTransactionIdentifier = 0

		pdu.Message.U.C1.U.RrcConnectionSetup.CriticalExtensions.T =
			asn1gen.RRCConnectionSetupCriticalExtensionsC1TAG

		pdu.Message.U.C1.U.RrcConnectionSetup.CriticalExtensions.U.C1 =
			new(asn1gen.RRCConnectionSetupCriticalExtensionsC1)

		pdu.Message.U.C1.U.RrcConnectionSetup.CriticalExtensions.U.C1.T =
			asn1gen.RRCConnectionSetupCriticalExtensionsC1RrcConnectionSetupR8TAG

		pdu.Message.U.C1.U.RrcConnectionSetup.
			CriticalExtensions.U.C1.U.RrcConnectionSetupR8 =
			new(asn1gen.RRCConnectionSetupR8IEs)

		pdu.Message.U.C1.U.RrcConnectionSetup.
			CriticalExtensions.U.C1.U.RrcConnectionSetupR8.
			RadioResourceConfigDedicated.PhysicalConfigDedicated =
			new(asn1gen.PhysicalConfigDedicated)

		pdu.Message.U.C1.U.RrcConnectionSetup.
			CriticalExtensions.U.C1.U.RrcConnectionSetupR8.
			RadioResourceConfigDedicated.PhysicalConfigDedicated.
			CqiReportConfig = new(asn1gen.CQIReportConfig)

		pdu.Message.U.C1.U.RrcConnectionSetup.
			CriticalExtensions.U.C1.U.RrcConnectionSetupR8.
			RadioResourceConfigDedicated.PhysicalConfigDedicated.
			CqiReportConfig.CqiReportModeAperiodic = new(asn1gen.CQIReportModeAperiodic)

		*pdu.Message.U.C1.U.RrcConnectionSetup.
			CriticalExtensions.U.C1.U.RrcConnectionSetupR8.
			RadioResourceConfigDedicated.PhysicalConfigDedicated.
			CqiReportConfig.CqiReportModeAperiodic = asn1gen.CQIReportModeAperiodicRm22

		pdu.Message.U.C1.U.RrcConnectionSetup.
			CriticalExtensions.U.C1.U.RrcConnectionSetupR8.
			RadioResourceConfigDedicated.PhysicalConfigDedicated.
			CqiReportConfig.NomPDSCHRSEPREOffset = -1

		pdu.Message.U.C1.U.RrcConnectionSetup.
			CriticalExtensions.U.C1.U.RrcConnectionSetupR8.
			RadioResourceConfigDedicated.PhysicalConfigDedicated.
			ExtGrpV3 = new(asn1gen.PhysicalConfigDedicatedExtGrpV3)

		pdu.Message.U.C1.U.RrcConnectionSetup.
			CriticalExtensions.U.C1.U.RrcConnectionSetupR8.
			RadioResourceConfigDedicated.PhysicalConfigDedicated.ExtGrpV3.
			AntennaInfoR10 = new(asn1gen.PhysicalConfigDedicatedAntennaInfoR10)

		pdu.Message.U.C1.U.RrcConnectionSetup.
			CriticalExtensions.U.C1.U.RrcConnectionSetupR8.
			RadioResourceConfigDedicated.PhysicalConfigDedicated.ExtGrpV3.
			AntennaInfoR10.T = asn1gen.PhysicalConfigDedicatedAntennaInfoR10ExplicitValueR10TAG

		pdu.Message.U.C1.U.RrcConnectionSetup.
			CriticalExtensions.U.C1.U.RrcConnectionSetupR8.
			RadioResourceConfigDedicated.PhysicalConfigDedicated.ExtGrpV3.
			AntennaInfoR10.U.ExplicitValueR10 = new(asn1gen.AntennaInfoDedicatedR10)

		pdu.Message.U.C1.U.RrcConnectionSetup.
			CriticalExtensions.U.C1.U.RrcConnectionSetupR8.
			RadioResourceConfigDedicated.PhysicalConfigDedicated.ExtGrpV3.
			AntennaInfoR10.U.ExplicitValueR10.TransmissionModeR10 =
			asn1gen.AntennaInfoDedicatedR10TransmissionModeR10Tm3

		pdu.Message.U.C1.U.RrcConnectionSetup.
			CriticalExtensions.U.C1.U.RrcConnectionSetupR8.
			RadioResourceConfigDedicated.PhysicalConfigDedicated.ExtGrpV3.
			AntennaInfoR10.U.ExplicitValueR10.UeTransmitAntennaSelection.T =
			asn1gen.AntennaInfoDedicatedUeTransmitAntennaSelectionSetupTAG

		pdu.Message.U.C1.U.RrcConnectionSetup.
			CriticalExtensions.U.C1.U.RrcConnectionSetupR8.
			RadioResourceConfigDedicated.PhysicalConfigDedicated.ExtGrpV3.
			AntennaInfoR10.U.ExplicitValueR10.UeTransmitAntennaSelection.U.Setup =
			new(asn1gen.AntennaInfoDedicatedR10UeTransmitAntennaSelectionSetup)

		*pdu.Message.U.C1.U.RrcConnectionSetup.
			CriticalExtensions.U.C1.U.RrcConnectionSetupR8.
			RadioResourceConfigDedicated.PhysicalConfigDedicated.ExtGrpV3.
			AntennaInfoR10.U.ExplicitValueR10.UeTransmitAntennaSelection.U.Setup =
			asn1gen.AntennaInfoDedicatedUeTransmitAntennaSelectionSetupOpenLoop

		// Encode

		encoding, err = asn1gen.Marshal(pdu)

		if err == nil {
			fmt.Printf("DL-CCCH-Message encoded successfully\n")
			fmt.Printf("%s\n", hex.Dump(encoding))
			err = ioutil.WriteFile(msgfile, encoding, 0777)
		} else {
			fmt.Printf("Encoding failed: %s\n", err)
			os.Exit(1)
		}
	} else {
		encoding, err := ioutil.ReadFile(msgfile)
		if err != nil {
			fmt.Printf("Read %s failed: %s\n", msgfile, err)
			os.Exit(1)
		}

		_, err = asn1gen.Unmarshal(encoding, &pdu)
		if err == nil {
			fmt.Printf("Decoding was successful:\n")
			asn1gen.Print(pdu)
		} else {
			fmt.Printf("Decoding failed: %s\n", err)
			os.Exit(1)
		}
	}
}
