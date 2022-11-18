// PerDecConsWholeNumRangeGT64K encodes a constrained whole number whose
// range is greater than 64K
func (pctxt *OSRTContext) PerDecConsWholeNumRangeGT64K(
	lenBits uint64) (uint64, error) {
	/* range > 64k, indefinite-length case (10.5.7d)               */
	/* Encode length determinant as a constrained whole number.    */
	/* Constraint is 1 to max number of bytes needed to hold       */
	/* the target integer value..                                  */
	pctxt.DiagNewBitField("length")

	nocts, err := pctxt.PerDecBitsToUInt(lenBits)
	if err != nil {
		return 0, err
	}
	pctxt.PerDecByteAlign()

	pctxt.DiagSetBitFieldCount()
	pctxt.DiagNewBitField("data")

	rangeBitCount := (nocts + 1) * 8

	return pctxt.PerDecBitsToUInt(rangeBitCount)
}
