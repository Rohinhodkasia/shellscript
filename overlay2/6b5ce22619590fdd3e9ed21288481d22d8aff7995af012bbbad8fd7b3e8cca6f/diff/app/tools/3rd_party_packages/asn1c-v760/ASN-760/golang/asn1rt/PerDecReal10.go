// PerDecReal10 decodes an ASN.1 REAL value from pctxt.
// This function allows the value to have been encoded using base 10 only,
// which is appropriate for type REAL constrained to base 10 values.
// Special values (e.g. plus-infinity) are NOT supported.
func (pctxt *OSRTContext) PerDecReal10() (value RealBase10, err error) {
	length, fragmented, e := pctxt.PerDecUnconsLen()
	if e != nil {
		err = fmt.Errorf("PerDecReal10: %w", e)
		return
	}
	if fragmented {
		err = fmt.Errorf("PerDecReal10: fragmented REAL")
		return
	}

	if length == 0 {
		/* zero */
		value = RealBase10("0")
		pctxt.DiagNewBitField("Real10")
	} else {
		/* If the length must be aligned and must be a multiple of 8 bits,
		alignment would not be required here. */
		pctxt.PerDecByteAlign()
		pctxt.DiagNewBitField("Real10")

		flags, e := pctxt.PerDecBitsToUInt(8)
		if e != nil {
			err = fmt.Errorf("PerDecReal10: %w", e)
			return
		}

		if (flags & 0xC0) == 0 {
			/* base 10 */
			tm := flags & 0x3F
			if tm >= 1 && tm <= 3 {
				length--
				strbytes := make([]byte, length)
				for i := uint64(0); i < length; i++ {
					tm, e = pctxt.PerDecBitsToUInt(8)
					if e != nil {
						err = fmt.Errorf("PerDecReal10: %w", e)
						return
					}
					strbytes[i] = byte(tm)
				}
				value = RealBase10(strbytes)
			} else {
				err = fmt.Errorf("PerDecReal10: invalid NR form")
				return
			}
		} else if flags&0x80 > 0 {
			/* base 2 */
			err = fmt.Errorf("PerDecReal10: base 10 encoding required")
			return
		} else {
			/* +- INF */
			err = fmt.Errorf("PerDecReal10: special value not allowed")
			return
		}
	}

	pctxt.DiagSetBitFieldCount()

	return
}
