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

	var pdu asn1gen.AliasAddress
	var encoding []byte
	
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
			*pdu.U.TransportID = asn1gen.TransportAddress("Truck")
		case asn1gen.AliasAddressEmailIDTAG:
			strval = "objective@obj-sys.com"
			pdu.U.EmailID = &strval
		case asn1gen.AliasAddressPartyNumberTAG:
			ival := asn1gen.PartyNumber(555)
			pdu.U.PartyNumber = &ival
		default:
			// test open extension
			choiceExt.Index = 7
			choiceExt.Data = []byte{0x03, 'a', 'b', 'c'}
			pdu.U.ExtElem1 = &choiceExt
		}

		// Encode

		encoding, err := asn1gen.Marshal(pdu)

		if err == nil {
			fmt.Printf("AliasAddress encoded successfully\n")
			fmt.Printf("%s\n", hex.Dump(encoding))
			err = ioutil.WriteFile(msgfile, encoding, 0777)
		} else {
			fmt.Printf("Encoding failed: %s\n", err)
			os.Exit(1)
		}
	} else {
		encoding, err = ioutil.ReadFile(msgfile)
		if err != nil {
			fmt.Printf("Read %s failed: %s\n", msgfile, err)
			os.Exit(1)
			return
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
