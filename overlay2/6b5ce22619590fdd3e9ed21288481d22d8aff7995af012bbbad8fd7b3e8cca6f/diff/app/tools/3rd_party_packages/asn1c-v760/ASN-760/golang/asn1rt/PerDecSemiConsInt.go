// PerDecSemiConsInt is used to decode a PER semi-constrained
// integer into a signed integer variable.
func (pctxt *OSRTContext) PerDecSemiConsInt(lower int64) (int64, error) {
	var ivalue int64
	ui, err := pctxt.PerDecSemiConsUInt(0)
	if err == nil {
		ivalue = int64(ui) + lower
	}
	return ivalue, err
}
