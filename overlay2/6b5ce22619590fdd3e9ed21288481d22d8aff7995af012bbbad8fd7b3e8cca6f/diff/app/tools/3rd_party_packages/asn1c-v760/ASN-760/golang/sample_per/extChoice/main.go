package main

import (
	"extChoice/asn1gen"
	"extChoice/asn1gen/asn1rt"
	"encoding/hex"
	"fmt"
	"io/ioutil"
	"os"
	"strconv"
)

func main() {
	var tvalue int = 1
	var err error
	msgfile := "message.per"
	writer := false
	if len(os.Args) > 1 {
		if os.Args[1] == "writer" {
			writer = true
		} else if os.Args[1] != "reader" {
			fmt.Println("first argument must be 'writer' or 'reader'")
			return
		}

		for i := 2; i < len(os.Args); i++ {
			if os.Args[i] == "-t" {
				i++
				tvalue, err = strconv.Atoi(os.Args[i])
				if err != nil {
					fmt.Println(err)
					return
				}
			}
		}
	} else {
		fmt.Println("Usage: employee writer|reader ...")
		return
	}

	pctxt := new(asn1rt.OSRTContext)
	var pdu asn1gen.AliasAddress

	if writer {
		// Populate PDU type variable to be encoded
		var choiceExt asn1rt.Asn1ChoiceExt
		var strval string
		pdu.T = uint64(tvalue)
		switch tvalue {
		case asn1gen.AliasAddressE164TAG:
			strval = "#12345"
			pdu.U.E164 = &strval
		case asn1gen.AliasAddressUrlIDTAG:
			strval = "http://www.obj-sys.com"
			pdu.U.UrlID = &strval
		case asn1gen.AliasAddressTransportIDTAG:
			pdu.U.TransportID = new(asn1gen.TransportAddress)
			*pdu.U.TransportID = "Truck"
		case asn1gen.AliasAddressEmailIDTAG:
			strval = "objective@obj-sys.com"
			pdu.U.EmailID = &strval
		case asn1gen.AliasAddressPartyNumberTAG:
			pdu.U.PartyNumber = new(asn1gen.PartyNumber)
			*pdu.U.PartyNumber = 555
		default:
			// test open extension
			choiceExt.Index = 7
			choiceExt.Data = []byte{0x03, 'a', 'b', 'c'}
			pdu.U.ExtElem1 = &choiceExt
		}

		// Encode

		pctxt.InitEncode()
		pctxt.NewBitFieldList()

		err := pdu.PerEncode(pctxt)

		pctxt.FlushBuffer()
		pctxt.PrintBitFieldList("pdu")

		if err == nil {
			fmt.Printf("AliasAddress encoded successfully\n")
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
		}
	}
}
