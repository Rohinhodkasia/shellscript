// DecBit decodes one bit
func (pctxt *OSRTContext) DecBit() (result bool, err error) {
	err = nil
	result = false

	if pctxt.buffer.byteIndex >= uint64(len(pctxt.buffer.data)) {
		err = fmt.Errorf("Attempt to read past end-of-buffer")
		return
	}
	pctxt.buffer.bitOffset--

	buf := pctxt.buffer.data
	idx := pctxt.buffer.byteIndex
	if ((buf[idx] >> pctxt.buffer.bitOffset) & 1) == 1 {
		result = true
	}

	if pctxt.buffer.bitOffset == 0 {
		pctxt.buffer.bitOffset = 8
		pctxt.buffer.byteIndex++
	}

	return
}
