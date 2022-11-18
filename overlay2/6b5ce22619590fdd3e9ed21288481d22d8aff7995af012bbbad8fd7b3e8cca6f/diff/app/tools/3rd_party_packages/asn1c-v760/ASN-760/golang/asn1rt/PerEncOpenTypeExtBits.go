// PerEncOpenTypeExtBits encodes open type extension optional bit values
func (pctxt *OSRTContext) PerEncOpenTypeExtBits(extElems [][]byte) error {
	if len(extElems) > 0 {
		for i := 0; i < len(extElems); i++ {
			err := pctxt.EncBit(bool(len(extElems[i]) > 0))
			if err != nil {
				return err
			}
		}
	}
	return nil
}
