// EncBitsFromByte will encode bits from a byte value.
// The least significant bits in the value will be encoded.
func (pctxt *OSRTContext) EncBitsFromByte(value byte, nbits uint64) error {
	encbuf := &pctxt.buffer
	bitOff := encbuf.bitOffset

	if nbits == 0 {
		return nil
	} else if nbits > 8 {
		return fmt.Errorf("nbits %d greater than max 8", nbits)
	}

	if bitOff == 8 {
		/* field aligned */
		if nbits == 8 {
			encbuf.data = append(encbuf.data, value)
			encbuf.byteIndex++
		} else {
			encbuf.partial = value << (8 - nbits) // clear unused bits
			encbuf.bitOffset = (8 - (nbits & 7))
		}
	} else {
		/* field unaligned */
		usedBits := 8 - bitOff
		nextOff := nbits + usedBits

		encbuf.bitOffset = (8 - (nextOff & 0x7))

		value <<= 8 - nbits /* clear unused bits */
		encbuf.partial |= value >> usedBits

		if nextOff > 7 {
			encbuf.data = append(encbuf.data, encbuf.partial)
			encbuf.byteIndex++
			encbuf.partial = value << bitOff
		}
	}

	return nil
}
