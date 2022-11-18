// DecInt decodes a 2's complement integer encoded in the given number
// of bytes, and returns the decoded value.
// If length == 0, 0 is returned.
func (pctxt *OSRTContext) DecInt(length uint8) (value int64, err error) {

	if length == 0 {
		return
	}

	uvalue, err := pctxt.PerDecBitsToUInt(uint64(length * 8))
	if err != nil {
		return 0, fmt.Errorf("DecInt: %w", err)
	}

	shift := bits.UintSize - length*8 // # of unused bits in the value

	if shift != 0 {
		/* Left shift highest decoded bit into high positiion.  This makes
		it so the sign will be converted correctly when we cast. */
		uvalue = uvalue << shift
	}

	value = int64(uvalue)

	if shift != 0 {
		/* Right shift bits back into place.  We'll give sign extension. */
		value = value >> shift
	}

	return
}
