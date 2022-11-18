// PerEncRelObjectIdentifier encodes an RELATIVE-OID value.
// This encode an unconstrained length as part of the encoding.
func (pctxt *OSRTContext) PerEncRelObjectIdentifier(subids []uint64) error {
	var i int
	var length uint64 = 0
	var numids = len(subids)

	/* Calculate length in bytes and encode */
	for i = 0; i < numids; i++ {
		length += EncGetIdentByteCount(subids[i])
	}

	_, stat := pctxt.PerEncUnconsLen(length)
	if stat != nil {
		return stat
	}

	pctxt.DiagNewBitField("RelObjectId")

	/* Encode each arc */
	for i = 0; i < numids; i++ {
		stat = pctxt.PerEncIdentifier(subids[i])
		if stat != nil {
			return stat
		}
	}

	pctxt.DiagSetBitFieldCount()
	return nil
}
