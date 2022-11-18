package main

import (
	"encoding/hex"
	"fmt"
	"io/ioutil"
	"os"
	"paramType/asn1gen"
	"paramType/asn1gen/asn1rt"
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
	var pdu asn1gen.SignedName

	if writer {
		// Populate PDU type variable to be encoded

		pdu.ToBeSigned.GivenName = "John"
		pdu.ToBeSigned.Initial = "P"
		pdu.ToBeSigned.FamilyName = "Smith"
		pdu.AlgorithmOID = []uint64{0, 0, 8, 2250, 0, 1}
		ranInt := int64(222)
		pdu.ParamS.RanInt = &ranInt
		var iv8 asn1gen.IV8 = make([]byte, 8)
		for i := byte(0); i < 8; i++ {
			iv8[i] = i + 0x7d
		}
		pdu.ParamS.Iv8 = &iv8

		pdu.Signature.Bytes = []byte{0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff}
		pdu.Signature.BitLength = len(pdu.Signature.Bytes) * 8

		// Encode

		pctxt.InitEncode()
		pctxt.NewBitFieldList()

		err := pdu.PerEncode(pctxt)

		pctxt.FlushBuffer()
		pctxt.PrintBitFieldList("pdu")

		if err == nil {
			fmt.Printf("SignedName encoded successfully\n")
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
