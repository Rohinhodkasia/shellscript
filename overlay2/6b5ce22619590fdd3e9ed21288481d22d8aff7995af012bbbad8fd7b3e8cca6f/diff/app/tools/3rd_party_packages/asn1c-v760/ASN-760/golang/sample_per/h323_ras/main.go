package main

import (
	"h323_ras/asn1gen"
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
		fmt.Println("Usage: h323_ras writer|reader ...")
		return
	}

	var pdu asn1gen.RasMessage
	var err error
	var encoding []byte

	if writer {
		// Populate PDU type variable to be encoded
		var registrationConfirm asn1gen.RegistrationConfirm
		registrationConfirm.RequestSeqNum = 1
		registrationConfirm.ProtocolIdentifier = []uint64{ 0, 0, 8, 2250, 0, 2 }

		var ipAddress asn1gen.TransportAddressIpAddress
		ipAddress.Ip = []byte{ 0xc0, 0xa8, 0x00, 0x01 }
		ipAddress.Port = 1720

		var transportAddress asn1gen.TransportAddress
		transportAddress.T = asn1gen.TransportAddressIpAddressTAG
		transportAddress.U.IpAddress = &ipAddress
		registrationConfirm.CallSignalAddress = append(registrationConfirm.CallSignalAddress, transportAddress)

		var aliasAddress asn1gen.AliasAddress
		aliasAddress.T = asn1gen.AliasAddressH323IDTAG
		var h323ID string = "anH323ID"
		aliasAddress.U.H323ID = &h323ID
		registrationConfirm.TerminalAlias = append(registrationConfirm.TerminalAlias, aliasAddress)

		var gkid asn1gen.GatekeeperIdentifier = "aGatekeeperID"
		registrationConfirm.GatekeeperIdentifier = &gkid
		registrationConfirm.EndpointIdentifier = "anEndpointID"

		pdu.T = asn1gen.RasMessageRegistrationConfirmTAG
		pdu.U.RegistrationConfirm = &registrationConfirm;

		// Encode

		encoding, err = asn1gen.Marshal(pdu)

		if err == nil {
			fmt.Printf("RasMessage encoded successfully\n")
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
