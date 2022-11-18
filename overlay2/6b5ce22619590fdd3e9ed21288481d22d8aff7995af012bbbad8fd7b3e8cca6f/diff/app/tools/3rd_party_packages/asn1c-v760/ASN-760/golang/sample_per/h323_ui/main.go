package main

import (
	"h323_ui/asn1gen"
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
		fmt.Println("Usage: h323_ui writer|reader ...")
		return
	}

	var pdu asn1gen.H225H323UserInformation
	var err error
	var encoding []byte

	if writer {
		// Populate PDU type variable to be encoded
		var setup asn1gen.H225SetupUUIE
		setup.ProtocolIdentifier = []uint64{ 0, 0, 8, 2250, 0, 2 }
		setup.ConferenceID = make([]byte, 16)
		for i := 0; i < 16; i++ {
			setup.ConferenceID[i] = byte(i + 1)
		}
		setup.ConferenceGoal.T = asn1gen.H225SetupUUIEConferenceGoalCreateTAG
		setup.CallType.T = asn1gen.H225CallTypePointToPointTAG
		setup.CallIdentifier = new(asn1gen.H225CallIdentifier)
		setup.CallIdentifier.Guid = make([]byte, 16)
		for i := 0; i < 16; i++ {
			setup.CallIdentifier.Guid[i] = byte(i + 1)
		}
		var mediaWaitForConnect bool = false
		setup.MediaWaitForConnect = &mediaWaitForConnect
		var canOverlapSend bool = false
		setup.CanOverlapSend = &canOverlapSend
	 
		pdu.H323UuPdu.H323MessageBody.T = asn1gen.H225H323UUPDUH323MessageBodySetupTAG
		pdu.H323UuPdu.H323MessageBody.U.Setup = &setup;
	
		// Encode

		encoding, err = asn1gen.Marshal(pdu)

		if err == nil {
			fmt.Printf("H225H323UserInformation encoded successfully\n")
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
