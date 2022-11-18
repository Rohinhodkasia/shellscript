package main

import (
	"megaco/asn1gen"
	"megaco/asn1gen/asn1rt"
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
	var pdu asn1gen.MegacoMessage

	if writer {
		// TODO populate PDU type variable to be encoded

		// Encode

		pctxt.InitEncode()
		pctxt.NewBitFieldList()

		err := pdu.PerEncode(pctxt)

		pctxt.FlushBuffer()
		pctxt.PrintBitFieldList("pdu")

		if err == nil {
			fmt.Printf("MegacoMessage encoded successfully\n")
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
