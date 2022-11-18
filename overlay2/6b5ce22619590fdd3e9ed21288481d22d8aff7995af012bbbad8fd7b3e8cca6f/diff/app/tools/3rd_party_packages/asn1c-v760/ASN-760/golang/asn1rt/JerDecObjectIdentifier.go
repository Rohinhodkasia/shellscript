// Package asn1rt provides ASN.1 run-time encode/decode functions
package asn1rt

import (
	"fmt"
	"strconv"
	"unicode"
)

// UnmarshalJSON - Decode an OBJECT IDENTIFIER type.
func (pvalue *ObjectIdentifier) UnmarshalJSON(data []byte) error {
	var numstr string
	*pvalue = []uint64{}
	if data[0] != '"' {
		return fmt.Errorf(
			"Unexpected start character %c in JSON OID\n", data[0])
	}
	var i int
	for i = 1; i < len(data)-1; i++ {
		if unicode.IsDigit(rune(data[i])) {
			numstr += string(data[i])
		} else if data[i] == '.' {
			val, err := strconv.ParseUint(numstr, 10, 64)
			if err != nil {
				return fmt.Errorf("Invalid OID arc value %s\n", numstr)
			}
			*pvalue = append(*pvalue, val)
			numstr = ""
		}
	}
	if data[i] != '"' {
		return fmt.Errorf(
			"Unexpected end character %c in JSON OID\n", data[i])
	}
	val, err := strconv.ParseUint(numstr, 10, 64)
	if err != nil {
		return fmt.Errorf("Invalid OID arc value %s\n", numstr)
	}
	*pvalue = append(*pvalue, val)
	
	return nil
}
