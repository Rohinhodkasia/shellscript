package main

import (
	"employee/asn1gen"
	"encoding/hex"
	"fmt"
	"io/ioutil"
	"os"
)

func main() {
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

	var pdu asn1gen.PersonnelRecord

	if writer {
		// populate PDU type variable to be encoded
		fillName(&pdu.Name, "John", "P", "Smith")

		pdu.Title = "Director"
		pdu.Number = 51
		pdu.DateOfHire = "19710917"

		fillName(&pdu.NameOfSpouse, "Mary", "T", "Smith")

		// fill first child record

		var childInfo asn1gen.ChildInformation
		fillName(&childInfo.Name, "Ralph", "T", "Smith")
		childInfo.DateOfBirth = "19571111"
		pdu.Children = append(pdu.Children, childInfo)

		// fill second child record

		fillName(&childInfo.Name, "Susan", "B", "Jones")
		childInfo.DateOfBirth = "19590717"
		pdu.Children = append(pdu.Children, childInfo)

		// Marshal

		encodedData, err := asn1gen.Marshal(pdu)

		if err == nil {
			fmt.Printf("PersonnelRecord encoded successfully\n")
			fmt.Printf("%s\n", hex.Dump(encodedData))
			err = ioutil.WriteFile("message.per", encodedData, 0777)
		} else {
			fmt.Printf("Encoding failed: %s\n", err)
			os.Exit(1)
		}
	} else {
		encoding, err := ioutil.ReadFile("message.per")
		if err != nil {
			fmt.Printf("Read message.per failed: %s\n", err)
			return
		}

		_, err = asn1gen.Unmarshal(encoding, &pdu)

		if err == nil {
			fmt.Printf("Decoding was successful:\n")
			asn1gen.Print(pdu)
		} else {
			fmt.Printf("Decoding failed: %s\n", err)
		}
	}
}

func fillName(name *asn1gen.Name, givenName string, initial string, familyName string) {
	name.GivenName = givenName
	name.Initial = initial
	name.FamilyName = familyName
}
