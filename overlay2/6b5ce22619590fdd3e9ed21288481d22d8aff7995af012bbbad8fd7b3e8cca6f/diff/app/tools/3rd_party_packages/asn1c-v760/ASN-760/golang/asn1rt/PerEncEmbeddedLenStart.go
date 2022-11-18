// PerEncEmbeddedLenStart encodes the start of an embedded length in the
// encode buffer. This is a placeholder that will be filled in later with
// an actual length value by PerEncEmbeddedLenEnd. This is used for encoding
// open type and containing type lengths.
func (pctxt *OSRTContext) PerEncEmbeddedLenStart() (uint64, error) {
	pctxt.PerEncBufAlign()
	pctxt.DiagNewBitField("length")

	// Encode a zero length byte
	err := pctxt.EncBitsFromByte(0, 8)
	if err != nil {
		return pctxt.BitOffset(), err
	}
	pctxt.DiagSetBitFieldCount()

	bitidx := pctxt.BitOffset() - 8

	return bitidx, nil
}
