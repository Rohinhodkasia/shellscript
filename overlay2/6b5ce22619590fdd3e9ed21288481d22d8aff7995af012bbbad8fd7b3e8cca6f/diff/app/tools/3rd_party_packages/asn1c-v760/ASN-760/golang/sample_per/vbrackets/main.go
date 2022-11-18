package main

import (
	"vbrackets/asn1gen"
	"vbrackets/asn1gen/asn1rt"
	"encoding/hex"
	"fmt"
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
	var pdu asn1gen.TestSequence

	if writer {
		// Populate PDU type variable to be encoded
		pdu.ItemCode = 29
		itemName := "SHERRY"
		pdu.ItemName = &itemName
		pdu.Urgency = new(asn1gen.TestSequenceUrgency)
		*pdu.Urgency = asn1gen.TestSequenceUrgencyHigh
		pdu.ExtGrpV3 = new(asn1gen.TestSequenceExtGrpV3)
		pdu.ExtGrpV3.AlternateItemCode = 45
		altItemName := "PORT"
		pdu.ExtGrpV3.AlternateItemName = &altItemName

		// Encode
		pctxt.InitEncode()
		pctxt.NewBitFieldList()

		err := pdu.PerEncode(pctxt)

		pctxt.FlushBuffer()
		pctxt.PrintBitFieldList("pdu")

		if err == nil {
			fmt.Printf("TestSequence encoded successfully\n")
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
