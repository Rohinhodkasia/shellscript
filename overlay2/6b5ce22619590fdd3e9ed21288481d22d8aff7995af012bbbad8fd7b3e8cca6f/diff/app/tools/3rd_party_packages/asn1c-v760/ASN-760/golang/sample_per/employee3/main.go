package main

import (
	"employee3/asn1gen"
	"employee3/asn1gen/asn1rt"
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
		fmt.Println("Usage: employee writer|reader ...")
		return
	}

	pctxt := new(asn1rt.OSRTContext)
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
		childInfo.Sex = new(asn1gen.ChildInformationSex)
		*childInfo.Sex = asn1gen.ChildInformationSexFemale
		pdu.Children = append(pdu.Children, childInfo)

		// Encode

		pctxt.InitEncode()
		pctxt.NewBitFieldList()

		err := pdu.PerEncode(pctxt)

		pctxt.FlushBuffer()
		pctxt.PrintBitFieldList("pdu")

		if err == nil {
			fmt.Printf("PersonnelRecord encoded successfully\n")
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

func fillName(name *asn1gen.Name, givenName asn1gen.NameString,
	initial string, familyName asn1gen.NameString) {
	name.GivenName = givenName
	name.Initial = initial
	name.FamilyName = familyName
}
