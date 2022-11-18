// PerDecRestrStringData decodes the data of a restricted character string,
// decoding slen characters, each of which was encoded in nbits bits.
// If charSet is not empty, it is used to translate character values.
//
// This function can be used for string types where each character is
// represented in the Go string by 1 byte (NumericString, PrintableString,
// VisibleString (ISO646String), and IA5String).
//
// charSet, if not empty, is the set of characters, in sorted order, which
// form the effective permitted alphabet for the string type being decoded.
func (pctxt *OSRTContext) PerDecRestrStringData(slen uint64,
	charSet string, nbits uint64) (string, error) {
	var strbuf string

	if len(charSet) == 0 {
		// Decode without translation.
		if pctxt.buffer.bitOffset == 8 && nbits == 8 {
			idx := pctxt.buffer.byteIndex
			endx := idx + slen
			if endx > uint64(len(pctxt.buffer.data)) {
				return "", fmt.Errorf("Attempt to read past end-of-buffer")
			}
			strbuf = string(pctxt.buffer.data[idx:endx])
			pctxt.buffer.byteIndex = endx
		} else {
			var sb strings.Builder
			for i := uint64(0); i < slen; i++ {
				idx, err := pctxt.PerDecBitsToUInt(nbits)
				if err != nil {
					return "", err
				}
				sb.WriteRune(rune(idx))
			}
			strbuf = sb.String()
		}
	} else {
		// Decode with translation.
		nchars := uint64(len(charSet))
		for i := uint64(0); i < slen; i++ {
			idx, err := pctxt.PerDecBitsToUInt(nbits)
			if err != nil {
				return "", err
			}
			if idx < nchars {
				strbuf += charSet[idx : idx+1]
			} else {
				return "",
					fmt.Errorf("Decoded index %d not in character set", idx)
			}
		}
	}

	return strbuf, nil
}
