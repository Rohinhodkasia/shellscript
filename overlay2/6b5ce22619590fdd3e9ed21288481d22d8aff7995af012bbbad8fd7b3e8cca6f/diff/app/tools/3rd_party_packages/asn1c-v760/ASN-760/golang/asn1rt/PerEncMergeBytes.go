// PerEncMergeBytes - Insert bytes into an existing location within the encode buffer.
// The new bytes will overwrite the existing content at the given location.
func (pctxt *OSRTContext) PerEncMergeBytes(buf []byte, bitidx uint64) error {
	buflen := uint64(len(buf))
	if buflen == 0 {
		return nil
	}
	byteIndex := uint64(bitidx / 8)
	bitOffset := uint64(8 - (bitidx % 8))
	if bitOffset == 8 {
		// Copy bytes directly into encode buffer
		copy(pctxt.buffer.data[byteIndex:byteIndex+buflen], buf[:buflen])
	} else {
		// Not on byte boundary
		// Merge first byte
		rshift := 8 - bitOffset
		tmp := byte((pctxt.buffer.data[byteIndex] >> bitOffset) << bitOffset)
		tmp2 := buf[0] >> rshift
		pctxt.buffer.data[byteIndex] = byte(tmp | tmp2)
		byteIndex++

		// Merge bytes in middle
		for i := 0; i < len(buf)-1; i++ {
			tmp = byte(buf[i] << bitOffset)
			tmp2 = byte(buf[i+1] >> rshift)
			pctxt.buffer.data[byteIndex] = byte(tmp | tmp2)
			byteIndex++
		}

		// Merge last byte
		tmp = byte(buf[len(buf)-1] << bitOffset)
		tmp2 = byte((pctxt.buffer.data[byteIndex] << rshift) >> rshift)
		pctxt.buffer.data[byteIndex] = byte(tmp | tmp2)
	}
	return nil
}
