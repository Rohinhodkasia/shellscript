// perEncString encodes an ASN.1 character string value. It encodes an unconstrained length,
// and then encodes the character data.
//
// The value is given as a UTF-8 string.
//
// Pass nil for encoding if no translation is required.  Otherwise, pass a RestrCharEncoding
// object.  If encoding == nil, you must pass nbits, the number of bits to
// encode each character in; otherwise nbits is ignored.
func (pctxt *OSRTContext) perEncString(value string, encoding RestrCharEncoding, nbits uint8) (err error) {

	// Get and encode the length (# of characters = # of runes)
	var len int
	len = utf8.RuneCountInString(value)
	_, err = pctxt.PerEncUnconsLen(uint64(len))
	if err != nil {
		return fmt.Errorf("perEncString: %w", err)
	}

	// Encode the data.
	pctxt.DiagNewBitField("data")
	err = pctxt.perEncStringData(value, encoding, nbits)
	pctxt.DiagSetBitFieldCount()

	return
}

// perEncStringData encodes the data (no length determinant) for an ASN.1
// character string.  This method supports encoding with and without character translation.
//
// The value is given as a UTF-8 string.
//
// Pass nil for encoding if no translation is required.  Otherwise, pass a RestrCharEncoding
// object.  If encoding == nil, you must pass nbits, the number of bits to
// encode each character in; otherwise nbits is ignored.
func (pctxt *OSRTContext) perEncStringData(value string, encoding RestrCharEncoding, nbits uint8) (err error) {

	var max rune //maximum value we can encode

	translate := encoding != nil
	if translate {
		nbits = encoding.NumBits()
	}

	if nbits == 32 {
		max = math.MaxInt32 /* rune is signed! */
	} else if nbits < 32 {
		max = (1 << nbits) - 1
	} else {
		panic("Unexpected number of bits per character.")
	}

	/* Read the runes from the string, writing each char to pctxt. */
	reader := strings.NewReader(value)
	for {
		var orig rune
		var encodeAs rune
		orig, _, err = reader.ReadRune()
		if err == io.EOF {
			/* Done */
			err = nil
			break
		} else if err != nil {
			return
		} else {
			if translate {
				/* Translate ch */
				encodeAs, err = encoding.Actual2Encoded(orig)
				if err != nil {
					return
				}
			} else {
				encodeAs = orig
			}

			if encodeAs > max {
				err = fmt.Errorf("Invalid character: %c (max is %c)", orig, max)
				return
			}

			/* Write encodeAs to pctxt in nbits bits */
			pctxt.PerEncBitsFromUInt(uint64(encodeAs), uint64(nbits))
		}
	}
	return
}

// PerEncBMPStringData encodes the data (no length determinant) for an ASN.1
// BMPString.  This method supports encoding with and without character translation.
//
// The value is given as a UTF-8 string.
//
// Pass nil for encoding if no translation is required.  Otherwise, pass a RestrCharEncoding
// object.
func (pctxt *OSRTContext) PerEncBMPStringData(value string, encoding RestrCharEncoding) (err error) {
	return pctxt.perEncStringData(value, encoding, 16)
}

// PerEncUnivString encodes an ASN.1 UniversalString value. It encodes an unconstrained length,
// and then encodes the character data.  If the UniversalString is length-constrained, encode
// the length yourself, and then use PerEncUniversalStringData to encode the data.
//
// The value is given as a UTF-8 string.
//
// Pass nil for encoding if no translation is required.  Otherwise, pass a RestrCharEncoding
// object.
func (pctxt *OSRTContext) PerEncUnivString(value string, encoding RestrCharEncoding) (err error) {
	return pctxt.perEncString(value, encoding, 32)
}

// PerEncUnivStringData encodes the data (no length determinant) for an ASN.1
// UniversalString.  This method supports encoding with and without character translation.
//
// The value is given as a UTF-8 string.
//
// Pass nil for encoding if no translation is required.  Otherwise, pass a RestrCharEncoding
// object.
func (pctxt *OSRTContext) PerEncUnivStringData(value string, encoding RestrCharEncoding) (err error) {
	return pctxt.perEncStringData(value, encoding, 32)
}

// PerEncBMPString encodes an ASN.1 BMPString value. It encodes an unconstrained length,
// and then encodes the character data.  If the BMPString is length-constrained, encode
// the length yourself, and then use PerEncBMPStringData to encode the data.
//
// The value is given as a UTF-8 string.
//
// Pass nil for encoding if no translation is required.  Otherwise, pass a RestrCharEncoding
// object.
func (pctxt *OSRTContext) PerEncBMPString(value string, encoding RestrCharEncoding) (err error) {
	return pctxt.perEncString(value, encoding, 16)
}
