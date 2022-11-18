// PerDecRelObjectIdentifier decodes a RELATIVE-OID value, including decoding of the unconstrained length.
func (pctxt *OSRTContext) PerDecRelObjectIdentifier() ([]uint64, error) {
	var b uint64
	var i int

	/* Decode unconstrained length */
	length, frag, stat := pctxt.PerDecUnconsLen()
	if stat != nil {
		return nil, stat
	}
	if frag {
		return nil, fmt.Errorf(
			"Object identifier with fragmented length not supported")
	}

	pctxt.DiagNewBitField("RelObjectID")
	subids := make([]uint64, length)

	/* Copy contents to a byte-aligned local buffer */
	for (length > 0) && (stat == nil) {
		if i < 128 { /* ASN_K_MAXSUBIDS */
			/* Parse a subidentifier out of the contents field */
			subids[i] = 0
			for stat == nil {
				b, stat = pctxt.PerDecBitsToUInt(8)
				if stat == nil {
					subids[i] = (subids[i] * 128) + (b & 0x7F)
					length--
				}

				if (b & 0x80) == 0 {
					break
				}
			}

			i++
		} else {
			stat = fmt.Errorf("Invalid object identifier value")
		}
	}

	pctxt.DiagSetBitFieldCount()
	if (stat == nil) && (length != 0) {
		return nil, fmt.Errorf("Invalid object identifier length")
	}

	if stat != nil {
		return nil, stat
	}

	if i < len(subids) {
		subids = subids[0:i]
	}
	return subids, nil
}
