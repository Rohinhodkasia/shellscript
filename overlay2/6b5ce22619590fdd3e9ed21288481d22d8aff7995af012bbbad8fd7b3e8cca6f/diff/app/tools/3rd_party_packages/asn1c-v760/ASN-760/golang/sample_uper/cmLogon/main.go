package main

import (
	"cmLogon/asn1gen"
	"cmLogon/asn1gen/asn1rt"
	"encoding/hex"
	"fmt"
	"io/ioutil"
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
		fmt.Println("Usage: cmLogon writer|reader ...")
		return
	}

	var acse asn1gen.ACSEApdu
	var pdu asn1gen.CMAircraftMessage
	var err error
	var encoding []byte

	if writer {
		// Populate CMLogonRequest structure */

		var cmLogonRequest asn1gen.CMLogonRequest
		cmLogonRequest.AircraftFlightIdentification = "UA901"

		cmLogonRequest.CMLongTSAP.RDP = asn1rt.OctetString("AB901")

		cmLogonRequest.CMLongTSAP.ShortTsap.LocSysNselTsel = []byte("4440900901")

		cmLogonRequest.FacilityDesignation = new(asn1gen.FacilityDesignation)
		*cmLogonRequest.FacilityDesignation = "KIADIZDS"

		// Plug structure into CMAircraftMessage variable

		pdu.T = asn1gen.CMAircraftMessageCmLogonRequestTAG
		pdu.U.CmLogonRequest = &cmLogonRequest

		// Encode - note that we cannot use the Marshal function for this as we
		// will need the bit count to populate the External arbitrary data bit
		// string in the AARQ APDU

		pctxt := new(asn1rt.OSRTContext)
		pctxt.InitEncode()
		pctxt.NewBitFieldList()

		err = pdu.PerEncode(pctxt)

		bitcnt := pctxt.BitOffset()
		pctxt.FlushBuffer()
		pctxt.PrintBitFieldList("pdu")

		if err == nil {
			fmt.Printf("CMAircraftMessage encoded successfully\n")
			fmt.Printf("%s\n", hex.Dump(pctxt.BufferData()))
		} else {
			fmt.Printf("Encoding failed: %s\n", err)
			os.Exit(1)
		}

		// Populate AARQ PDU structure

		var aarq asn1gen.AARQApdu
		aarq.ProtocolVersion.BitLength = 1
		aarq.ProtocolVersion.Bytes = []byte{0x80}
		aarq.ApplicationContextName = []uint64{1, 3, 27, 3, 1}

		var callingAPTitleOID = asn1gen.APTitleForm2([]uint64{1, 3, 27, 1, 500, 0})
		aarq.CallingAPTitle = new(asn1gen.APTitle)
		aarq.CallingAPTitle.T = asn1gen.APTitleApTitleForm2TAG
		aarq.CallingAPTitle.U.ApTitleForm2 = &callingAPTitleOID

		aarq.CallingAEQualifier = new(asn1gen.AEQualifier)
		aarq.CallingAEQualifier.T = asn1gen.AEQualifierAeQualifierForm2TAG
		aarq.CallingAEQualifier.U.AeQualifierForm2 = new(asn1gen.AEQualifierForm2)
		*aarq.CallingAEQualifier.U.AeQualifierForm2 = 1

		// Populate external type with info in the encoded request and plug
		// into the structure..

		aarq.UserInformation = make([]asn1gen.External, 1)
		aarq.UserInformation[0].Encoding.T = asn1gen.ExternalEncodingArbitraryTAG
		aarq.UserInformation[0].Encoding.U.Arbitrary = new(asn1rt.BitString)
		aarq.UserInformation[0].Encoding.U.Arbitrary.BitLength = int(bitcnt)
		aarq.UserInformation[0].Encoding.U.Arbitrary.Bytes = pctxt.BufferData()

		acse.T = asn1gen.ACSEApduAarqTAG
		acse.U.Aarq = &aarq

		// Encode

		encoding, err = asn1gen.Marshal(acse)

		if err == nil {
			fmt.Printf("ACSE encoded successfully\n")
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

		// Decode ACSE APDU

		_, err = asn1gen.Unmarshal(encoding, &acse)
		if err == nil {
			fmt.Printf("Decoding was successful:\n")
			asn1gen.Print(acse)
		} else {
			fmt.Printf("Decoding failed: %s\n", err)
			os.Exit(1)
		}

		// Check fields for expected values

		if acse.T != asn1gen.ACSEApduAarqTAG {
			fmt.Printf("ERROR: expecting %d, got %d\n",
				asn1gen.ACSEApduAarqTAG, acse.T)
			os.Exit(1)
		}

		if acse.U.Aarq.UserInformation == nil {
			fmt.Printf("ERROR: encoded aircraft message is not present.\n")
			os.Exit(1)
		}

		if len(acse.U.Aarq.UserInformation) != 1 {
			fmt.Printf("ERROR: expecting only 1 external element, got %d\n",
				len(acse.U.Aarq.UserInformation))
			os.Exit(1)
		}

		if acse.U.Aarq.UserInformation[0].Encoding.T !=
			asn1gen.ExternalEncodingArbitraryTAG {
			fmt.Printf("ERROR: expecting arbitray encoding, got %d\n",
				acse.U.Aarq.UserInformation[0].Encoding.T)
			os.Exit(1)
		}

		// Decode CMAircraftMessage

		_, err = asn1gen.Unmarshal(
			acse.U.Aarq.UserInformation[0].Encoding.U.Arbitrary.Bytes, &pdu)
		if err == nil {
			fmt.Printf("Decoding was successful:\n")
			asn1gen.Print(pdu)
		} else {
			fmt.Printf("Decoding failed: %s\n", err)
			os.Exit(1)
		}
	}
}
