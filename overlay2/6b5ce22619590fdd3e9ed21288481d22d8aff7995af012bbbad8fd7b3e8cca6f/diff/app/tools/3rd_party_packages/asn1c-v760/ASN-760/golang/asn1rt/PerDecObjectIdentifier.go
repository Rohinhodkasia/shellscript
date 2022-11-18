// PerDecObjectIdentifier - Decode an OBJECT IDENTIFIER type.
func (pctxt *OSRTContext) PerDecObjectIdentifier() ([]uint64, error) {
	var b, subid uint64
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

	pctxt.DiagNewBitField("ObjectID")
	subids := make([]uint64, length+1)

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

			/* Handle the first subidentifier special case: the first two
			   sub-id's are encoded into one using the formula (x * 40) + y */
			if i == 0 {
				subid = subids[0]
				if (subid / 40) >= 2 {
					subids[0] = 2
				} else {
					subids[0] = subid / 40
				}

				if subids[0] == 2 {
					subids[1] = subid - 80
				} else {
					subids[1] = subid % 40
				}

				i = 2
			} else {
				i++
			}
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
