// PerEncSmallLength encodes a normally small length as specified in
// section 11.9 of the X.691 standard.
func (pctxt *OSRTContext) PerEncSmallLength(value uint64) error {
	var err error
	if value == 0 {
		return fmt.Errorf(
			"Normally small length value must be greater than zero")
	} else if value <= 64 {
		err = pctxt.EncBit(false) /*  indicate <= 64 */
		if err == nil {
			/* encode n-1 */
			err = pctxt.PerEncBitsFromUInt(value-1, 6)
		}
	} else {
		err = pctxt.EncBit(true) /* indicate value > 64 */
		if err == nil {
			_, err = pctxt.PerEncUnconsLen(value)
		}
	}

	return err
}
