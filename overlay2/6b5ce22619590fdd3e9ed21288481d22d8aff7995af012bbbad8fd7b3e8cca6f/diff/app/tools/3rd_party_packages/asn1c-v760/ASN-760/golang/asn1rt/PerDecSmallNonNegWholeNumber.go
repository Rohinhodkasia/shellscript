// PerDecSmallNonNegWholeNumber encompasses the rules to decode a small
// non-negative whole number as specified in section 10.6 of the X.691
// standard.
func (pctxt *OSRTContext) PerDecSmallNonNegWholeNumber() (uint64, error) {
	bitValue, err := pctxt.DecBit()
	if err != nil {
		return 0, err
	}

	var value uint64
	if !bitValue {
		/* n <= 64. Encoded value is n-1. */
		return pctxt.PerDecBitsToUInt(6)
	}
	/*  n > 64. Encoded value is n. */
	var llen uint64
	llen, _, err = pctxt.PerDecUnconsLen()
	if err == nil {
		pctxt.PerDecByteAlign()
		value, err = pctxt.PerDecBitsToUInt(llen * 8)
	}

	return value, err
}
