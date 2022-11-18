// PerEncOpenTypeExt encodes an open type extension value. These are unknown,
// already encoded components that are preserved after decoding.
func (pctxt *OSRTContext) PerEncOpenTypeExt(extElems [][]byte) error {
	if len(extElems) > 0 {
		for i := 0; i < len(extElems); i++ {
			err := pctxt.PerEncOpenType(extElems[i])
			if err != nil {
				return err
			}
		}
	}
	return nil
}
