// EncBit will encode a single bit value
func (pctxt *OSRTContext) EncBit(value bool) error {
	encbuf := &pctxt.buffer
	var bitOffset uint64 = encbuf.bitOffset - 1
	var mask byte
	if value {
		mask = 1 << bitOffset
	}
	encbuf.partial |= mask

	if bitOffset == 0 {
		encbuf.data = append(encbuf.data, encbuf.partial)
		encbuf.partial = 0
		encbuf.bitOffset = 8
		encbuf.byteIndex++
	} else {
		encbuf.bitOffset = bitOffset
	}

	return nil
}
