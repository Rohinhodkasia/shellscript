package main

import (
	"supl-v21/asn1gen"
	"supl-v21/asn1gen/asn1rt"
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
		fmt.Println("Usage: supl-v21 writer|reader ...")
		return
	}

	var pdu asn1gen.ULPPDU
	var err error
	var encoding []byte

	if writer {
		// Populate PDU type variable to be encoded
		
		var suplInit asn1gen.SUPLINIT
		suplInit.PosMethod = asn1gen.PosMethodAgpsSETbasedpref
		suplInit.SLPAddress = new(asn1gen.SLPAddress)
		suplInit.SLPAddress.T = asn1gen.SLPAddressFQDNTAG
		fqdn := asn1gen.FQDN("obj-sys.com")
		suplInit.SLPAddress.U.FQDN = &fqdn
		suplInit.QoP = new(asn1gen.QoP)
		suplInit.QoP.Horacc = 29
		var maxLocAge uint64 = 0
		suplInit.QoP.MaxLocAge = &maxLocAge
		var delay uint64 = 5
		suplInit.QoP.Delay = &delay
		suplInit.SLPMode = asn1gen.SLPModeProxy
		
		pdu.Length = 42
		pdu.Version.Maj = 2
		pdu.Version.Min = 1
		pdu.Version.Servind = 0
		pdu.SessionID.SlpSessionID = new(asn1gen.SlpSessionID)
		pdu.SessionID.SlpSessionID.SessionID = 
			asn1rt.OctetString([]byte{0x32, 0x30, 0x30, 0x32})
		pdu.SessionID.SlpSessionID.SlpId.T = asn1gen.SLPAddressFQDNTAG
		pdu.SessionID.SlpSessionID.SlpId.U.FQDN = &fqdn
		pdu.Message.T = asn1gen.UlpMessageMsSUPLINITTAG
		pdu.Message.U.MsSUPLINIT = &suplInit;
   
		// Encode

		encoding, err = asn1gen.Marshal(pdu)

		if err == nil {
			fmt.Printf("ULPPDU encoded successfully\n")
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
