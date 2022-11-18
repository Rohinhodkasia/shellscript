package main

import (
	"encoding/hex"
	"fmt"
	"infoObject/asn1gen"
	"infoObject/asn1gen/asn1rt"
	"io/ioutil"
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
	var pdu asn1gen.IuReleaseCommand
	var err error

	if writer {
		// Populate PDU type variable to be encoded

		var protocolIE asn1gen.ProtocolIEField
		protocolIE.Id = 12345
		protocolIE.Criticality = asn1gen.CriticalityNotify
		protocolIE.Value, err = encodeCause(true) /* from encoded open type */

		if err != nil {
			fmt.Println(err)
		}

		pdu.ProtocolIEs = append(pdu.ProtocolIEs, protocolIE)

		// Encode

		pctxt.InitEncode()
		pctxt.NewBitFieldList()

		err := pdu.PerEncode(pctxt)

		pctxt.FlushBuffer()
		pctxt.PrintBitFieldList("pdu")

		if err == nil {
			fmt.Printf("PDU encoded successfully\n")
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

		// Decode Cause

		fmt.Println("***")
		fmt.Println("Decode open type value..")

		var value asn1gen.Cause
		pctxt.InitDecodeBytes(pdu.ProtocolIEs[0].Value)
		pctxt.NewBitFieldList()

		err = value.PerDecode(pctxt)

		pctxt.PrintBitFieldList("value")

		if err == nil {
			fmt.Printf("Decoding was successful:\n")
			asn1gen.Print(pdu)
		} else {
			fmt.Printf("Decoding failed: %s\n", err)
			os.Exit(1)
		}
	}
}

/* Encode message for use in open type field */

func encodeCause(verbose bool) ([]byte, error) {
	var err error

	pctxt := new(asn1rt.OSRTContext)
	var pdu asn1gen.Cause

	pdu.T = asn1gen.CauseRadioNetworkTAG
	var enumval asn1gen.CauseRadioNetwork = 
		asn1gen.CauseRadioNetwork(asn1gen.CauseRadioNetworkRelocationTriggered)
	pdu.U.RadioNetwork = &enumval

	pctxt.InitEncode()
	if verbose {
		pctxt.NewBitFieldList()
	}

	err = pdu.PerEncode(pctxt)

	pctxt.FlushBuffer()

	if err == nil {
		if verbose {
			fmt.Println("Encoding was successful")
			fmt.Println("")
			fmt.Println("Hex dump of encoded record:")
			fmt.Printf("%s\n", hex.Dump(pctxt.BufferData()))
			fmt.Println("Binary dump:")
			pctxt.PrintBitFieldList("pdu")
		}
	}

	return pctxt.BufferData(), err
}
