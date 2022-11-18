// PerEncSmallNonNegWholeNumber encompasses the rules to encode a small
// non-negative whole number as specified in section 10.6 of the X.691
// standard.
func (pctxt *OSRTContext) PerEncSmallNonNegWholeNumber(value uint64) error {
	var err error
	if value < 64 {
		err = pctxt.PerEncBitsFromUInt(value, 7)
	} else {
		/* Encode extension bit */
		err = pctxt.EncBit(true)
		if err != nil {
			return err
		}
		pctxt.PerEncBufAlign()

		/* Encode a one-byte length determinant value */
		var llen uint64
		if value < 256 {
			llen = 1
		} else if value < 65536 {
			llen = 2
		} else if value < 0x1000000 {
			llen = 3
		} else {
			return fmt.Errorf("Very large SmallNonNegWholeNumber not supported")
		}

		err = pctxt.PerEncBitsFromUInt(llen, 8)

		/* Encode the value */
		if err == nil {
			err = pctxt.PerEncBitsFromUInt(value, llen*8)
		}
	}

	return err
}
