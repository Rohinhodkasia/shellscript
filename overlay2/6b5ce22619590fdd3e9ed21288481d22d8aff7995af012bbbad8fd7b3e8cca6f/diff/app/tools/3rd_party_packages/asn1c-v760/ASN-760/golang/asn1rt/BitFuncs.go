// Package asn1rt provides ASN.1 run-time encode/decode functions
package asn1rt

import (
	"encoding/asn1"
	"fmt"
)

type BitString asn1.BitString

// SetBit sets the bit at the given bit index in the bit string
func SetBit(bitidx uint64, pbitstr *BitString) {
	byteIndex := bitidx / 8
	bitMask := byte(0x80 >> (bitidx % 8))
	if uint64(cap(pbitstr.Bytes)) <= byteIndex {
		s := make([]byte, byteIndex+1)
		copy(s, pbitstr.Bytes)
		pbitstr.Bytes = s
	}
	pbitstr.Bytes[byteIndex] |= bitMask
	if bitidx >= uint64(pbitstr.BitLength) {
		pbitstr.BitLength = int(bitidx) + 1
	}
	return
}

// ClearBit clear the bit at the given bit index in the bit string
func ClearBit(bitidx uint64, pbitstr *BitString) error {
	byteIndex := bitidx / 8
	if uint64(cap(pbitstr.Bytes)) <= byteIndex {
		return fmt.Errorf("Bit index %d is out of range", bitidx)
	}
	bitMask := ^(0x80 >> (bitidx % 8))
	pbitstr.Bytes[byteIndex] &= byte(bitMask)
	return nil
}

// TestBit test if the bit at the given bit index is set in the bit string
func TestBit(bitidx uint64, pbitstr *BitString) (bool, error) {
	byteIndex := bitidx / 8
	if uint64(cap(pbitstr.Bytes)) <= byteIndex {
		return false, fmt.Errorf("Bit index %d is out of range", bitidx)
	}
	bitMask := 0x80 >> (bitidx % 8)
	res := bool((pbitstr.Bytes[byteIndex] & byte(bitMask)) != 0)

	return res, nil
}
