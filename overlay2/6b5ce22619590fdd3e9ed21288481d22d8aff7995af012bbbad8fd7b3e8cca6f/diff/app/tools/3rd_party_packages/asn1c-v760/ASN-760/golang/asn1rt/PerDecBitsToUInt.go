// PerDecBitsToUInt decodes the given number of bits and returns the result
// in an unsigned integer variable
func (pctxt *OSRTContext) PerDecBitsToUInt(nbits uint64) (uint64, error) {
	if nbits == 0 {
		return uint64(0), nil
	} else if nbits > 64 {
		return 0,
			fmt.Errorf("Result will not fit in 64-bit unsigned int")
	}
	buf := pctxt.buffer.data
	idx := pctxt.buffer.byteIndex

	// If the number of bits is less than the current bit offset, mask
	// off the required number of bits and return..

	var ui uint64
	if nbits <= pctxt.buffer.bitOffset {
		if idx >= uint64(len(pctxt.buffer.data)) {
			return uint64(0), fmt.Errorf("Attempt to read past end-of-buffer")
		}
		pctxt.buffer.bitOffset -= nbits

		ui = uint64((buf[idx] >> pctxt.buffer.bitOffset) &
			((1 << nbits) - 1))

		if pctxt.buffer.bitOffset == 0 {
			pctxt.buffer.bitOffset = 8
			pctxt.buffer.byteIndex++
		}
	} else {
		nbytes := uint64((nbits - pctxt.buffer.bitOffset + 15) / 8)
		var i uint64
		if pctxt.buffer.bitOffset == 8 {
			if nbits%8 == 0 {
				for i = 0; i < nbytes; i++ {
					ui = ui*256 + uint64(buf[idx+i])
				}
			} else {
				for i = 0; i < nbytes-1; i++ {
					ui = ui*256 + uint64(buf[idx+i])
				}
				pctxt.buffer.bitOffset = 8 - (nbits % 8)
				ui = ui<<(8-pctxt.buffer.bitOffset) +
					uint64(buf[idx+i]>>pctxt.buffer.bitOffset)

			}
		} else {
			// handle case of non-byte boundary
			// first read current byte remaining bits
			mask := byte(0xff >> (8 - pctxt.buffer.bitOffset))
			ui = uint64(buf[idx] & mask)

			nbits -= pctxt.buffer.bitOffset
			pctxt.buffer.bitOffset = 8

			// second add full bytes from buf
			for i = 1; nbits >= 8; i++ {
				ui <<= 8
				ui |= uint64(buf[idx+i])
				nbits -= 8
			}

			// third process last partial byte
			if nbits > 0 {
				pctxt.buffer.bitOffset = uint64(8 - nbits)
				ui <<= nbits
				ui |= uint64(buf[idx+i]) >> pctxt.buffer.bitOffset
			}
		}
		pctxt.buffer.byteIndex += nbytes
		if pctxt.buffer.bitOffset != 8 {
			pctxt.buffer.byteIndex--
		}
	}

	return ui, nil
}
