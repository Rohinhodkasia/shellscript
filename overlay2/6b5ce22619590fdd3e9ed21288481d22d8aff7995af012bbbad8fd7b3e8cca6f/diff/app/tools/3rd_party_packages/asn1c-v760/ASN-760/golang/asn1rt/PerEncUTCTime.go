// PerEncUTCTime encodes an ASN.1 UTCTime value.
// Each character is encoded in the given number of bits, which should be
// 7 for unaligned encoding and 8 for aligned encoding.
func (pctxt *OSRTContext) PerEncUTCTime(value string, nbits uint8) (err error) {

	dateTime, consVio, err := parseTime(value, true)
	if err != nil {
		err = fmt.Errorf("PerEncUTCTime: %w", err)
		return
	}

	if len(consVio) > 0 {
		/* There are canonical violations.
		If the time uses an offset, we can fix it to use UTC.  Any other canonical
		violations will be fixed by parsing and making the time.
		*/
		if dateTime.tzFlag && dateTime.tzo != 0 {
			/* Fix the timezone */
			normalizeTimeZone(&dateTime)
		}

		value, err = makeTime(&dateTime, true)
		if err != nil {
			err = fmt.Errorf("PerEncUTCTime: %w", err)
			return
		}
	}
	err = pctxt.perEncString(value, nil, nbits)
	return
}
