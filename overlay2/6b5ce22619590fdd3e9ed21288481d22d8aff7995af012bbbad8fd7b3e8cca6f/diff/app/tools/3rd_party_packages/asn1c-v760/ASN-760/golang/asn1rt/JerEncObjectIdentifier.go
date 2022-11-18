// Package asn1rt provides ASN.1 run-time encode/decode functions
package asn1rt

import (
	"strconv"
)

// MarshalJSON - Encode (marshal) an OBJECT IDENTIFIER type.
func (value ObjectIdentifier) MarshalJSON() ([]byte, error) {
	var s string
	for i := range value {
		if i > 0 {
			s += "."
		}
		s += strconv.FormatUint(value[i], 10)
	}
	return ([]byte(strconv.Quote(s))), nil
}
