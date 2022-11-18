package main

import (
	"bitString/asn1gen"
	"bitString/asn1gen/asn1rt"
	"encoding/hex"
	"fmt"
	"io/ioutil"
	"os"
)

func setBitStr(pbitstr *asn1rt.BitString, nbits uint64, repbyte byte) {
	pbitstr.BitLength = int(nbits)
	pbitstr.Bytes = make([]byte, (nbits+7)/8)
	for i := range pbitstr.Bytes {
		pbitstr.Bytes[i] = repbyte
	}
	return
}

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
		fmt.Println("Usage: bitString writer|reader ...")
		return
	}

	var pdu asn1gen.BitStrSeq
	var err error
	var encoding []byte

	if writer {
		// populate PDU type variable to be encoded
		var tmpval asn1rt.BitString
		setBitStr(&tmpval, 122, 0xed)
		pdu.SimpleBitStr = asn1gen.BitStr(tmpval)
		setBitStr(&tmpval, 100, 0xed)
		pdu.SizedBitStr = asn1gen.SizedBitStr(tmpval)
		setBitStr(&pdu.InSz1to10, 50, 0xed)
		setBitStr(&pdu.InFxdSz, 100, 0xed)
		setBitStr(&tmpval, 100, 0xed)
		pdu.DefFixed = asn1gen.FixedSizeBitStr(tmpval)

		var tmpval2 asn1rt.BitString
		asn1rt.SetBit(asn1gen.NamedBitsA, &tmpval2)
		asn1rt.SetBit(asn1gen.NamedBitsB, &tmpval2)
		asn1rt.SetBit(asn1gen.NamedBitsC, &tmpval2)
		asn1rt.ClearBit(asn1gen.NamedBitsB, &tmpval2)
		pdu.NamedBits = asn1gen.NamedBits(tmpval2)

		// Encode
		encoding, err = asn1gen.Marshal(pdu)

		if err == nil {
			fmt.Printf("BitStrSeq encoded successfully\n")
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
