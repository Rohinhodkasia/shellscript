// PerEncGeneralizedTime encodes an ASN.1 GeneralizedTime value.
// Each character is encoded in the given number of bits, which should be
// 7 for unaligned encoding and 8 for aligned encoding.
func (pctxt *OSRTContext) PerEncGeneralizedTime(value string, nbits uint8) (err error) {

	dateTime, consVio, err := parseTime(value, false)
	if err != nil {
		err = fmt.Errorf("PerEncGeneralizedTime: %w", err)
		return
	}

	if len(consVio) > 0 {
		/* There are canonical violations.  The only one we cannot fix is
		if the time uses local time (we would have to assume the timezone).
		If the time uses an offset, we can fix it to use UTC.  Any other canonical
		violations will be fixed by parsing and making the time.
		*/
		if dateTime.tzFlag && dateTime.tzo != 0 {
			/* Fix the timezone */
			normalizeTimeZone(&dateTime)
		} else if !dateTime.tzFlag {
			err = fmt.Errorf("PerEncGeneralizedTime: Cannot encode value with local time")
			return
		}
		value, err = makeTime(&dateTime, false)
		if err != nil {
			err = fmt.Errorf("PerEncGeneralizedTime: %w", err)
			return
		}
	}
	err = pctxt.perEncString(value, nil, nbits)
	return
}
