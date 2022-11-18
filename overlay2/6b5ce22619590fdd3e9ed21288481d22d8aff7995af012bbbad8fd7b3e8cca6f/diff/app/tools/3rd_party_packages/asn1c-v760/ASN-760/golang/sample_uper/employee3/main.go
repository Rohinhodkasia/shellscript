package main

import (
	"employee3/asn1gen"
	"encoding/json"
	"encoding/hex"
	"fmt"
	"io/ioutil"
	"os"
)

func main() {
	msgfile := "message.uper"
	jsonfile := "message.json"
	writer := false
	if len(os.Args) > 1 {
		if os.Args[1] == "writer" {
			writer = true
		} else if os.Args[1] != "reader" {
			fmt.Println("first argument must be 'writer' or 'reader'")
			return
		}
	} else {
		fmt.Println("Usage: employee3 writer|reader ...")
		return
	}

	var pdu asn1gen.PersonnelRecord
	var err error
	var encoding []byte

	if writer {
		// Encode

		var jsonbuf []byte
		jsonbuf, err = ioutil.ReadFile(jsonfile)
		if err != nil {
			fmt.Printf("Read %s failed: %s\n", jsonfile, err)
			os.Exit(1)
		}

		err = json.Unmarshal(jsonbuf, &pdu)
		if err != nil {
			fmt.Printf("Unmarshal failed: %s\n", err)
			os.Exit(1)
		}

		encoding, err = asn1gen.Marshal(pdu)

		if err == nil {
			fmt.Printf("PersonnelRecord encoded successfully\n")
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
