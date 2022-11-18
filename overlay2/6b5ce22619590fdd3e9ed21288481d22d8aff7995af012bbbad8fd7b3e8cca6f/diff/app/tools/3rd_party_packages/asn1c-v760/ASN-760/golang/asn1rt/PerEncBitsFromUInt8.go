// PerEncBitsFromUInt8 is the 8-bit version of PerEncBitsFromUInt.
func (pctxt *OSRTContext) PerEncBitsFromUInt8(value uint8, nbits uint64) error {
	if nbits > 8 {
		return fmt.Errorf("PerEncBitsFromUInt8: nbits (%d) > 8", nbits)
	}

	return pctxt.PerEncBitsFromUInt(uint64(value), nbits)
}
