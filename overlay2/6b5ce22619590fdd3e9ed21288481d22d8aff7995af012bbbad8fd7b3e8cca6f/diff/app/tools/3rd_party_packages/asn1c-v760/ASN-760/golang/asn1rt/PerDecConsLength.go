// PerDecConsLength decodes a constrained length value
func (pctxt *OSRTContext) PerDecConsLength(
	rangeBitCount uint64, lowerBound uint64) (uint64, error) {
	var err error
	var len uint64

	len, err = pctxt.PerDecBitsToUInt(rangeBitCount)
	if err != nil {
		return 0, err
	}

	return len + lowerBound, nil
}
