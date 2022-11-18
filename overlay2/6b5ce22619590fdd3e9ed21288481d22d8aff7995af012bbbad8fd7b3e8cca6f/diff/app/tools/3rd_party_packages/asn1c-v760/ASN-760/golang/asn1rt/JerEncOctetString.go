// Package asn1rt provides ASN.1 run-time encode/decode functions
package asn1rt

import (
	"encoding/hex"
	"strconv"
)

func (value OctetString) MarshalJSON() ([]byte, error) {
	return ([]byte(strconv.Quote(hex.EncodeToString(value)))), nil
}
