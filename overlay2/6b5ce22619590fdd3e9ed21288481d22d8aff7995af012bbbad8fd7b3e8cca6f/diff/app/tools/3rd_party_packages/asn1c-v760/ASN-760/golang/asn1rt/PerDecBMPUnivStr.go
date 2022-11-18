// perDecString decodes an ASN.1 character string, first decoding an
// unconstrained length and then decoding the data.
//
// The decoded string is returned as a UTF-8 string.
//
// Pass nil for encoding if no translation is required.  Otherwise, pass a
// RestrCharEncoding object.  If encoding == nil, nbits must be passed, the
// number of bits to encode each character in; otherwise nbits is ignored.
func (pctxt *OSRTContext) perDecString(encoding RestrCharEncoding, nbits uint8) (string, error) {
	nchars, frag, err := pctxt.PerDecUnconsLen()
	if err != nil {
		return "", err
	}
	if frag {
		return "", pctxt.ErrNotSupported("String with fragmented length")
	}
	pctxt.DiagNewBitField("data")

	strbuf, err := pctxt.perDecStringData(nchars, encoding, nbits)

	pctxt.DiagSetBitFieldCount()

	return strbuf, err
}

// perDecStringData decodes the data (no length determinant) for an ASN.1
// character string, decoding slen characters.  This method supports decoding
// with and without character translation.
//
// The decoded string is returned as a UTF-8 string.
//
// Pass nil for encoding if no translation is required.  Otherwise, pass a
// RestrCharEncoding object.  If encoding == nil, nbits must be passed, the
// number of bits to encode each character in; otherwise nbits is ignored.
func (pctxt *OSRTContext) perDecStringData(slen uint64,
	encoding RestrCharEncoding, nbits uint8) (str string, err error) {
	var builder = new(strings.Builder)

	translate := encoding != nil
	if translate {
		nbits = encoding.NumBits()
	}

	/* Read each character and write it as UTF-8 to the builder. */
	for i := uint64(0); i < slen; i++ {
		var ch uint64
		ch, err = pctxt.PerDecBitsToUInt(uint64(nbits))
		if err != nil {
			err = fmt.Errorf("PerDecBMPStringData: %w", err)
			return
		}

		var r = rune(ch)
		if translate {
			r, err = encoding.Encoded2Actual(r)
			if err != nil {
				return
			}
		}

		builder.WriteRune(r)
	}

	str = builder.String()
	return
}

// PerDecBMPStringData decodes the data (no length determinant) for an ASN.1
// BMPString, decoding slen characters.  This method supports decoding with
// and without character translation.
//
// The decoded string is returned as a UTF-8 string.
//
// Pass nil for encoding if no translation is required.  Otherwise, pass a
// RestrCharEncoding object.
func (pctxt *OSRTContext) PerDecBMPStringData(slen uint64,
	encoding RestrCharEncoding) (str string, err error) {
	return pctxt.perDecStringData(slen, encoding, 16)
}

// PerDecBMPString decodes an ASN.1 BMPString, first decoding an
// unconstrained length and then decoding the data.
//
// The decoded string is returned as a UTF-8 string.
//
// Pass nil for encoding if no translation is required.  Otherwise, pass a
// RestrCharEncoding object.
func (pctxt *OSRTContext) PerDecBMPString(encoding RestrCharEncoding) (string, error) {
	return pctxt.perDecString(encoding, 16)
}


// PerDecUnivStringData decodes the data (no length determinant) for an ASN.1
// UniversalString, decoding slen characters.  This method supports decoding
// with and without character translation.
//
// The decoded string is returned as a UTF-8 string.
//
// Pass nil for encoding if no translation is required.  Otherwise, pass a
// RestrCharEncoding object.
func (pctxt *OSRTContext) PerDecUnivStringData(slen uint64,
	encoding RestrCharEncoding) (str string, err error) {
	return pctxt.perDecStringData(slen, encoding, 32)
}

// PerDecUnivString decodes an ASN.1 UniversalString, first decoding an
// unconstrained length and then decoding the data.
//
// The decoded string is returned as a UTF-8 string.
//
// Pass nil for encoding if no translation is required.  Otherwise, pass a
// RestrCharEncoding object.
func (pctxt *OSRTContext) PerDecUnivString(encoding RestrCharEncoding) (string, error) {
	return pctxt.perDecString(encoding, 32)
}
