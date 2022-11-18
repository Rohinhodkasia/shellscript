// Package asn1rt provides ASN.1 run-time encode/decode functions
package asn1rt

import (
	"encoding/asn1"
	"encoding/hex"
	"strconv"
)

func JerEncBitString(value asn1.BitString) ([]byte, error) {
	return []byte(`{"data":"` + hex.EncodeToString(value.Bytes) +
		`","length":` + strconv.Itoa(value.BitLength) + "}"), nil
}
