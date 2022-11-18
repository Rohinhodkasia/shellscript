// DecBits decodes the given number of bits and returns a slice containing
// the decoded bits
func (pctxt *OSRTContext) DecBits(nbits uint64) (value []byte, err error) {
	nbytes := nbits / 8
	rembits := nbits % 8

	value = make([]byte, nbytes)
	err = pctxt.DecBytesIntoSlice(value)
	if rembits > 0 {
		var b bool
		var lastByte byte
		var mask byte = 0x80
		for i := uint64(0); i < rembits; i++ {
			b, err = pctxt.DecBit()
			if err != nil {
				return
			}
			if b {
				lastByte |= mask
			}
			mask >>= 1
		}
		value = append(value, lastByte)
	}

	return
}
