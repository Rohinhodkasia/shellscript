// PerEncRestrStringData encodes the data (no length determinant) for an ASN.1
// restricted charactcer string value, encoding each character in nbits bits.
// If charSet is not empty, it is used to translate character values.
//
// This function can be used for string types where each character is
// represented in the Go string by 1 byte (NumericString, PrintableString,
// VisibleString (ISO646String), and IA5String).
//
// charSet, if not empty, is the set of characters, in sorted order, which
// form the effective permitted alphabet for the string type being encoded.
func (pctxt *OSRTContext) PerEncRestrStringData(value string,
	charSet string, nbits uint64) error {

	if len(charSet) == 0 {
		// Encode as-is, w/o translation.
		if pctxt.buffer.bitOffset == 8 && nbits == 8 {
			strbytes := []byte(value)
			pctxt.buffer.data = append(pctxt.buffer.data, strbytes...)
			pctxt.buffer.byteIndex += uint64(len(strbytes))
		} else {
			for i := 0; i < len(value); i++ {
				err := pctxt.EncBitsFromByte(value[i], nbits)
				if err != nil {
					return err
				}
			}
		}
	} else {
		//Encode with translation.
		for i := 0; i < len(value); i++ {
			idx := strings.Index(charSet, value[i:i+1])
			if idx < 0 {
				return fmt.Errorf("Character %s not found in character set %s",
					value[i:i+1], charSet)
			}

			err := pctxt.PerEncBitsFromUInt(uint64(idx), nbits)
			if err != nil {
				return err
			}
		}
	}

	return nil
}
