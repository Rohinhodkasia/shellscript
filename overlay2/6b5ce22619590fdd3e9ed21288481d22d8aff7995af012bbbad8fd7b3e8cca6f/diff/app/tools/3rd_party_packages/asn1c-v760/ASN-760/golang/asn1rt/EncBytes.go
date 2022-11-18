// EncBytes encodes the given array of bytes
func (pctxt *OSRTContext) EncBytes(value []byte) error {
	if pctxt.buffer.bitOffset == 8 {
		pctxt.buffer.data = append(pctxt.buffer.data, value...)
		pctxt.buffer.byteIndex = uint64(len(pctxt.buffer.data))
	} else {
		// write to not byte-aligned boundary
		for i := 0; i < len(value); i++ {
			err := pctxt.EncBitsFromByte(value[i], 8)
			if err != nil {
				return err
			}
		}
	}

	return nil
}
