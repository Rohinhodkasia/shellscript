// PerEncUnconsOctStr will encode an unconstrained octet string value.
// The string is assumed to not have a size constraint.
func (pctxt *OSRTContext) PerEncUnconsOctStr(value []byte) error {
	var err error
	nitems := uint64(len(value))
	var enclen uint64
	var fraglen uint64

	if nitems == 0 {
		fraglen, err = pctxt.PerEncUnconsLen(0)
		return err
	}

	for enclen < nitems {
		// Encode length
		fraglen, err = pctxt.PerEncUnconsLen(nitems - enclen)
		if err != nil {
			return err
		}
		// Encode bytes
		pctxt.DiagNewBitField("data")
		if enclen+fraglen < nitems {
			err = pctxt.PerEncBytes(value[enclen : enclen+fraglen])
		} else {
			err = pctxt.PerEncBytes(value[enclen:])
		}
		if err != nil {
			return err
		}
		pctxt.DiagSetBitFieldCount()
		enclen += fraglen
	}
	return nil
}
