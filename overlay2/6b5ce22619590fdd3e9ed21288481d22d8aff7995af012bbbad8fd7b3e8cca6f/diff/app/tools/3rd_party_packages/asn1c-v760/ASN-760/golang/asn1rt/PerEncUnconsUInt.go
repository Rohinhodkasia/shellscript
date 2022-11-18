// PerEncUnconsUInt will encode an unconstrained unsigned integer value.
func (pctxt *OSRTContext) PerEncUnconsUInt(value uint64) error {
	/* Encode value as an unconstrained whole number. */

	var mask uint64 = 1 << (bits.UintSize - 1)

	if (value & mask) == 0 {
		/* The most significant bit is 0, we can simply cast to int */
		/* and use PerEncUnconsInt */
		return pctxt.PerEncUnconsInt(int64(value))
	}
	/* The most significant bit is 1.  We can encode this as a 2's
	complement binary integer by encoding the length, a zero byte,
	and then the value. */

	nbytes := uint64(unsafe.Sizeof(value) + 1) /*  + 1 for the leading zero byte */

	/* Encode length */
	pctxt.DiagNewBitField("length")

	err := pctxt.PerEncBitsFromUInt(nbytes, 8)
	if err != nil {
		return err
	}

	pctxt.DiagSetBitFieldCount()

	/* Encode unsigned value */

	pctxt.DiagNewBitField("data")

	err = pctxt.PerEncBitsFromUInt(0, 8)
	if err != nil {
		return err
	}

	/* Encode the value */
	err = pctxt.PerEncBitsFromUInt(value, bits.UintSize)
	if err != nil {
		return err
	}

	pctxt.DiagSetBitFieldCount()

	return nil
}
