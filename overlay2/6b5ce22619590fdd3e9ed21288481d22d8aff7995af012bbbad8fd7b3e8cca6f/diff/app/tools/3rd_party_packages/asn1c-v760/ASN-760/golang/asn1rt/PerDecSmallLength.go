// PerDecSmallLength encompasses the rules to decode a normally small length
// as specified in section 11.9 of the X.691 standard.
func (pctxt *OSRTContext) PerDecSmallLength() (uint64, error) {
	bitValue, err := pctxt.DecBit()
	if err != nil {
		return 0, err
	}

	var value uint64
	if !bitValue {
		/* n <= 64. Encoded value is n-1. */
		value, err = pctxt.PerDecBitsToUInt(6)
		value = value + 1
	} else {
		/*  n > 64. Encoded value is n. */
		value, _, err = pctxt.PerDecUnconsLen()
	}
	return value, err
}
