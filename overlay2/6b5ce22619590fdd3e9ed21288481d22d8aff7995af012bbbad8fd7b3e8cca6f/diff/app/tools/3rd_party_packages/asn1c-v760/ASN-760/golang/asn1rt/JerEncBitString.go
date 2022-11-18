// Package asn1rt provides ASN.1 run-time encode/decode functions
package asn1rt

import (
	"encoding/asn1"
	"encoding/hex"
	"strconv"
)

func (value BitString) MarshalJSON() ([]byte, error) {
	return []byte(`{"value":"` + hex.EncodeToString(value.Bytes) +
		`","length":` + strconv.Itoa(value.BitLength) + "}"), nil
}
