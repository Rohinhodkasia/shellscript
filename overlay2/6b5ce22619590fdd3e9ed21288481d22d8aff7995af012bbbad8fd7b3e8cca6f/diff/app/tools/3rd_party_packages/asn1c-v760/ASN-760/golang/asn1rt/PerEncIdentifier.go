// PerEncIdentifier - Encode an OID subid.
func (pctxt *OSRTContext) PerEncIdentifier(ident uint64) error {
	var lv uint64
	var mask, nshifts uint64
	var stat error

	if ident != 0 {
		nshifts = EncGetIdentByteCount(ident)
		for nshifts > 0 {
			/* avoid mask overflow */
			mask = 0x7f << (7 * (nshifts - 1))
			nshifts--
			lv = (ident & mask) >> (nshifts * 7)
			if nshifts != 0 {
				lv |= 0x80
			}
			stat = pctxt.EncBitsFromByte(byte(lv), 8)
			if stat != nil {
				return stat
			}
		}
	} else {
		/* encode a single zero byte */
		stat = pctxt.EncBitsFromByte(0, 8)
		if stat != nil {
			return stat
		}
	}

	return nil
}
