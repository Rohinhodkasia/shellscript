// PerEncBitsFromByteArray will encode bits from a byte array/slice
func (pctxt *OSRTContext) PerEncBitsFromByteArray(
	value []byte, nbits uint64) (err error) {
	encbuf := &pctxt.buffer
	bitOff := encbuf.bitOffset

	if nbits == 0 {
		return
	} else if nbits > uint64(len(value)*8) {
		err = fmt.Errorf("nbits %d greater than length of buffer", nbits)
		return
	}

	nbytes := nbits / 8
	if bitOff == 8 {
		// field aligned
		encbuf.data = append(encbuf.data, value[:nbytes]...)
		encbuf.byteIndex += nbytes
	} else {
		// not aligned
		for i := uint64(0); i < nbytes; i++ {
			err = pctxt.EncBitsFromByte(value[i], 8)
		}
	}
	rembits := nbits % 8
	if rembits != 0 {
		// encode remaining bits in last byte
		b := byte(value[nbytes] >> (8 - rembits))
		err = pctxt.EncBitsFromByte(b, rembits)
	}

	return
}
