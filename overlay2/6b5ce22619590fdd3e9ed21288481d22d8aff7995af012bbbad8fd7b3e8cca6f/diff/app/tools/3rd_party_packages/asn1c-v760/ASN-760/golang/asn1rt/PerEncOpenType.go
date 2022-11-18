// PerEncOpenType encodes an open type value
func (pctxt *OSRTContext) PerEncOpenType(buf []byte) error {
	return pctxt.PerEncUnconsOctStr(buf)
}
