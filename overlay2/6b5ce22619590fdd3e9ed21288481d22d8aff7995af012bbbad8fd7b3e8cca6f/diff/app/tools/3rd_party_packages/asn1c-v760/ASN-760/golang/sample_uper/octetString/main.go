package main

import (
	"fmt"
	"io/ioutil"
	"octetString/asn1gen"
	"octetString/asn1gen/asn1rt"
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
		fmt.Println("Usage: octetString writer|reader ...")
		return
	}

	var pdu asn1gen.MySeq
	var err error
	var encoding []byte

	if writer {
		// populate PDU type variable to be encoded
		// note: this forces a fragmented length encoding
		pdu.Os1 = make([]byte, 70000)
		for i := range pdu.Os1 {
			pdu.Os1[i] = 0xed
		}
		pdu.Os2 = []byte{0x01, 0x02, 0x03}
		pdu.Os3 = []byte{0x04, 0x05, 0x06}
		os4 := asn1rt.OctetString([]byte{0x07})
		pdu.Os4 = &os4

		os5 := asn1gen.OctStr3([]byte{0x0a, 0x0b, 0x0c})
		pdu.Os5 = &os5

		pdu.Os6 = make([]byte, 10)
		for i := range pdu.Os6 {
			pdu.Os6[i] = byte(i)
		}

		// Encode

		encoding, err = asn1gen.Marshal(pdu)

		if err == nil {
			fmt.Printf("MySeq encoded successfully\n")
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
