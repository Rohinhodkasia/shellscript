// PerDecByteAlign aligns the decode buffer on the next byte boundary
func (pctxt *OSRTContext) PerDecByteAlign() {
	if pctxt.buffer.bitOffset != 8 {
		pctxt.buffer.bitOffset = 8
		pctxt.buffer.byteIndex++
		pctxt.DiagSetBitFieldOffset()
	}
}
