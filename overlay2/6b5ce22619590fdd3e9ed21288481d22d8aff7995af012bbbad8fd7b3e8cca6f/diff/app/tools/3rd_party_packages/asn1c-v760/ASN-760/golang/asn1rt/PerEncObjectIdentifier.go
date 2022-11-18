// PerEncObjectIdentifier - Encode an OBJECT IDENTIFIER type.
func (pctxt *OSRTContext) PerEncObjectIdentifier(subids []uint64) error {
	var i int
	var length uint64 = 1 /* 1st 2 arcs require 1 byte */
	var numids = len(subids)
	var temp uint64

	/* Calculate length in bytes and encode */
	for i = 2; i < numids; i++ {
		length += EncGetIdentByteCount(subids[i])
	}

	_, stat := pctxt.PerEncUnconsLen(length)
	if stat != nil {
		return stat
	}

	pctxt.DiagNewBitField("ObjectId")

	/* Validate given object ID by applying ASN.1 rules */
	if (numids < 2) || (subids[0] > 2) {
		return fmt.Errorf("OID too short or has invalid first subid")
	}
	if (subids[0] != 2) && (subids[1] > 39) {
		return fmt.Errorf("OID has invalid 2nd subid (must be less than 40)")
	}

	/* Munge first two sub ID's and encode */
	temp = (subids[0] * 40) + subids[1]
	stat = pctxt.PerEncIdentifier(temp)
	if stat != nil {
		return stat
	}

	/* Encode the remainder of the OID value */
	for i = 2; i < numids; i++ {
		stat = pctxt.PerEncIdentifier(subids[i])
		if stat != nil {
			return stat
		}
	}

	pctxt.DiagSetBitFieldCount()
	return nil
}
