// PerEncBitsFromUInt will encode bits from an unsigned integer value.
// The least significant bits in the value will be encoded.
func (pctxt *OSRTContext) PerEncBitsFromUInt(value uint64, nbits uint64) error {
	if nbits == 0 {
		return nil
	} else if nbits > bits.UintSize {
		return fmt.Errorf("nbits %d greater than max %d", nbits, bits.UintSize)
	}

	/* Encode value to temp buffer */
	const uintSizeBytes = bits.UintSize / 8
	var ba [uintSizeBytes]byte
	tmpidx := uint64(uintSizeBytes)
	temp := value
	for {
		lb := temp % 256
		temp /= 256
		tmpidx--
		ba[tmpidx] = byte(lb)

		if temp == 0 {
			break
		}
	}

	/* Encode bytes from temp buffer to output stream */
	var err error
	nbytes := nbits / 8
	b0bits := nbits % 8
	startx := uintSizeBytes - nbytes
	if b0bits != 0 {
		err = pctxt.EncBitsFromByte(ba[startx-1], b0bits)
		if err != nil {
			return err
		}
	}
	for i := startx; i < uintSizeBytes; i++ {
		err = pctxt.EncBitsFromByte(ba[i], 8)
	}

	return nil
}
