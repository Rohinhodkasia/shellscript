// PerDecBytesToString decodes an ASN.1 character string type that is not
// a known multiplier string type.
// This decodes an unconstrained length.  The octet data is decoded as the
// bytes of the string.
func (pctxt *OSRTContext) PerDecBytesToString() (string, error) {
	b, err := pctxt.PerDecUnconsOctStr()
	if err != nil {
		return "", err
	}
	return string(b), nil
}
