package main

import (
	"bytes"
	"extChoiceOpen/asn1gen"
	"extChoiceOpen/asn1gen/asn1rt"
	"encoding/hex"
	"fmt"
	"io/ioutil"
	"log"
   "os"
)

func main() {
	msgfile := "message.per"

	// Decode message with open extension
	pctxt := new(asn1rt.OSRTContext)
	var pdu asn1gen.AliasAddress

	encoding, err := ioutil.ReadFile(msgfile)
	if err != nil {
		fmt.Printf("Read %s failed: %s\n", msgfile, err)
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
	}

	// Encode

	pctxt.InitEncode()
	pctxt.NewBitFieldList()

	err = pdu.PerEncode(pctxt)

	pctxt.FlushBuffer()
	pctxt.PrintBitFieldList("pdu")

	if err == nil {
		fmt.Printf("AliasAddress encoded successfully\n")
		fmt.Printf("%s\n", hex.Dump(pctxt.BufferData()))
		err = ioutil.WriteFile("message2.per", pctxt.BufferData(), 0777)

		// Input and output byte arrays should be equal
		if !bytes.Equal(encoding, pctxt.BufferData()) {
			log.Fatal("Input and output byte arrays not equal")
		}
	} else {
		fmt.Printf("Encoding failed: %s\n", err)
		os.Exit(1)
	}
}
