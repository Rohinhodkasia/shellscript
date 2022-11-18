// DecByte decodes a single byte value
func (pctxt *OSRTContext) DecByte() (value byte, err error) {

	if pctxt.buffer.bitOffset == 8 {
		if pctxt.buffer.byteIndex >= uint64(len(pctxt.buffer.data)) {
			err = fmt.Errorf("DecByte: buffer overflow")
			return
		}

		value = pctxt.buffer.data[pctxt.buffer.byteIndex]
		pctxt.buffer.byteIndex++
	} else {
		var ub uint64
		ub, err = pctxt.PerDecBitsToUInt(8)
		if err != nil {
			err = fmt.Errorf("DecByte: %w", err)
			return
		}
		value = byte(ub)
	}
	return
}
