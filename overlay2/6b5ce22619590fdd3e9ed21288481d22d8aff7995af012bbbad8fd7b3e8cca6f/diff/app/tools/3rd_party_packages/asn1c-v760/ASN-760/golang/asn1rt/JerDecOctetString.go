// Package asn1rt provides ASN.1 run-time encode/decode functions
package asn1rt

import (
	"encoding/hex"
)

func (pvalue *OctetString) UnmarshalJSON(b []byte) error {
	s := string(b)
	s = s[1 : len(s)-1]
	data, err := hex.DecodeString(s)
	if err == nil {
		*pvalue = data
	}
	return err
}
