// Package asn1rt provides ASN.1 run-time encode/decode functions
package asn1rt

import (
	"encoding/asn1"
	"encoding/hex"
	"regexp"
	"strconv"
)

func (pvalue *BitString) UnmarshalJSON(data []byte) error {
	var err error
	bitstrrx, _ := regexp.Compile(`{"value":"([0-9a-fA-F]+)","length":([0-9]+)}`)
	if bitstrrx.Match(data) {
		submatch := bitstrrx.FindSubmatch(data)
		pvalue.Bytes, err = hex.DecodeString(string(submatch[1]))
		if err != nil {
			return err
		}
		pvalue.BitLength, err = strconv.Atoi(string(submatch[2]))
	} else {
		err = asn1.SyntaxError{Msg: "invalid BitString JSON"}
	}
	return err
}
