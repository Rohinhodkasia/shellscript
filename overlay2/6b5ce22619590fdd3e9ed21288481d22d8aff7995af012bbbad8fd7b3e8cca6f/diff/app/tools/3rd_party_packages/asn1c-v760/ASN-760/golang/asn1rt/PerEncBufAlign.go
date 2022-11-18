// PerEncBufAlign will align the PER encoding buffer on the next byte boundary.
func (pctxt *OSRTContext) PerEncBufAlign() {
	if pctxt.buffer.bitOffset != 8 {
		pctxt.DiagSetBitFieldCount()
		pctxt.buffer.bitOffset = 8
		pctxt.buffer.data = append(pctxt.buffer.data, pctxt.buffer.partial)
		pctxt.buffer.byteIndex++
		pctxt.buffer.partial = 0
	}
}
