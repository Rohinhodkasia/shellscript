// PerEncIRIString encodes an ASN.1 OID-IRI or RELATIVE-OID-IRI value.
// The Go value must use the XML value notation. Whitespace will be omitted
// from the encoding, as required.
func (pctxt *OSRTContext) PerEncIRIString(value string) (err error) {

	var data []byte /* If not nil, data to encode (value without whitespace) */

	/* Once data is not nil, dest is the index in data to copy the next bytes to
	and src is the index in string to copy the next bytes from.
	*/
	var dest int
	var src int

	for i := 0; i < len(value); {
		/* The definition of whitespace, which is to be omitted, is the characters with
		unicode code points 9-13, 32, and 160.  The UTF-8 encoding for the last
		of these is 0xC2 0xA0.
		*/
		whitesp := (value[i] >= 9 && value[i] <= 13) ||
			value[i] == 32 ||
			(value[i] == 0xC2 && i+1 < len(value) && value[i+1] == 0xA0)
		if whitesp {
			if data == nil {
				data = make([]byte, len(value)-1) /* -1 : we know at least one byte will be omitted */
				copy(data, value[0:i])
				dest = i
			} else {
				/* Copy previously uncopied data, excluding the current byte. */
				copy(data[dest:], value[src:i])
				dest = dest + i - src
			}

			if value[i] == 0xC2 {
				/* Two bytes being skipped */
				i += 2
			} else {
				/* Single byte being skipped */
				i++
			}
			src = i
		} else if value[i] >= 0xF0 {
			// 4 byte UTF-8 sequence
			i += 4
		} else if value[i] >= 0xE0 {
			// 3 byte UTF-8 sequence
			i += 3
		} else if value[i] >= 0xC0 {
			// 2 byte UTF-8 sequence
			i += 2
		} else {
			i++
		}
	}

	if data != nil {
		if src < len(value) {
			copy(data[dest:], value[src:]) // copy remaining bytes from value to data
			dest = dest + len(value) - src
		}
		data = data[0:dest] //trim unused portion of data

		return pctxt.PerEncUnconsOctStr(data)
	}

	return pctxt.PerEncUnconsOctStr([]byte(value))
}
