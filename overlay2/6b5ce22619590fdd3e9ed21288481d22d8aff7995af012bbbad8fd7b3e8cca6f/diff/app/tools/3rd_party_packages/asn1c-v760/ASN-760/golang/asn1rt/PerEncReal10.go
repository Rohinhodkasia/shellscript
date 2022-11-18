// PerEncReal10 encodes value as an ASN.1 REAL.
// The value will be encoded as base 10, NR3 form.  The value may be represented in integer,
// floating-point decimal, and exponent formats.  Special values (e.g. plus-infinity)
// are NOT allowed.
func (pctxt *OSRTContext) PerEncReal10(value RealBase10) (err error) {

	/* The input string might not be in NR3 form, so we have to parse it and
	normalize it to NR3 form. */

	mantMinus := uint64(0) // # of characters to encode for mantissa minus sign.

	/* Skip ws and leading zeros and plus */
	p := int(0) // Index to current character in string.
	for ; p < len(value); p++ {
		c := value[p]
		if c == '-' {
			mantMinus = 1
		} else if c != ' ' && c != '0' && c != '+' {
			break
		}
	}

	var mantBeg, mantEnd = p, p // Indices for start and end of mantissa
	trailZeros := uint64(0)     // Number of trailing zeros in mantissa
	digits := uint64(0)
	flFrac := false       // Fraction present
	expMinus := uint64(0) // # of characters to encode for exponent minus sign.
	mantExpVal := 0       // Exponent value based on mantisaa (fractional digits)
	expVal := 0           // Exponent value

	/* Count mantissa digits */
	for ; p < len(value); p++ {
		c := value[p]
		if c == '0' {
			trailZeros++
		} else if c > '0' && c <= '9' {
			if digits == 0 && flFrac {
				mantExpVal = -int(trailZeros)
				digits = 1
				mantBeg = p
			} else {
				digits += trailZeros + 1
			}
			trailZeros = 0
			mantEnd = p + 1
		} else if c == '.' {
			mantExpVal = int(digits + trailZeros)
			flFrac = true
		} else if c == 'e' || c == 'E' {
			p++
			break
		} else if c != ' ' {
			break
		}
	}

	var ll0 uint64 //Length of encoding.

	if ll0 = digits; digits > 0 {
		if !flFrac {
			mantExpVal = int(digits + trailZeros)
		}
		/* Skip ws and leading zeros and plus */
		for ; p < len(value); p++ {
			c := value[p]
			if c == '-' {
				expMinus = 1
			} else if c != ' ' && c != '0' && c != '+' {
				break
			}
		}

		/* Get exponent */
		for ; p < len(value); p++ {
			c := value[p]
			if c >= '0' && c <= '9' {
				expVal = expVal*10 + int((c - '0'))
			} else if c != ' ' {
				break
			}
		}

		if expMinus == 1 {
			expVal = -expVal
		}

		expVal += mantExpVal

		expVal -= int(digits)

		if expVal < 0 {
			expMinus = 1
			expVal = -expVal
		} else {
			expMinus = 0
		}

		var pExp int
		var expBuf [8]byte
		/* Count exponent length */
		if expVal != 0 {
			tm := expVal
			pExp = len(expBuf)

			for tm > 0 {
				pExp--
				expBuf[pExp] = byte(tm%10) + '0'
				tm /= 10
				ll0++
			}
		} else {
			ll0 += 2
		}

		ll0 += 3 + expMinus + mantMinus

		var enclen uint64
		enclen, err = pctxt.PerEncUnconsLen(ll0)
		if err != nil {
			err = fmt.Errorf("PerEncReal10: %w", err)
			return
		}
		if enclen != ll0 {
			err = fmt.Errorf("PerEncReal10: unexpected fragmentation")
			return
		}

		/* If an unconstrained length must be aligned and must use a multiple of 8 bits,
		then alignment is not required here. */
		pctxt.PerEncBufAlign()

		pctxt.DiagNewBitField("Real10")

		/* real10 NR3 marker */
		err = pctxt.PerEncBitsFromUInt(3, 8)
		if err != nil {
			err = fmt.Errorf("PerEncReal10: %w", err)
			return
		}

		/* Put mantissa */
		if mantMinus == 1 {
			err = pctxt.PerEncBitsFromUInt('-', 8)
			if err != nil {
				err = fmt.Errorf("PerEncReal10: %w", err)
				return
			}

		}

		for mantBeg != mantEnd {
			c := value[mantBeg]
			mantBeg++
			if c >= '0' && c <= '9' {
				err = pctxt.PerEncBitsFromUInt8(c, 8)
				if err != nil {
					err = fmt.Errorf("PerEncReal10: %w", err)
					return
				}

			}
		}

		err = pctxt.PerEncBitsFromUInt('.', 8)
		if err != nil {
			err = fmt.Errorf("PerEncReal10: %w", err)
			return
		}

		err = pctxt.PerEncBitsFromUInt('E', 8)
		if err != nil {
			err = fmt.Errorf("PerEncReal10: %w", err)
			return
		}

		/* Put exponent */
		if expVal != 0 {
			if expMinus == 1 {
				err = pctxt.PerEncBitsFromUInt('-', 8)
				if err != nil {
					err = fmt.Errorf("PerEncReal10: %w", err)
					return
				}
			}
			pctxt.EncBytes(expBuf[pExp:])
			if err != nil {
				err = fmt.Errorf("PerEncReal10: %w", err)
				return
			}
		} else {
			err = pctxt.PerEncBitsFromUInt('+', 8)
			if err != nil {
				err = fmt.Errorf("PerEncReal10: %w", err)
				return
			}
			err = pctxt.PerEncBitsFromUInt('0', 8)
			if err != nil {
				err = fmt.Errorf("PerEncReal10: %w", err)
				return
			}
		}
	} else {
		/* Encode 0 */
		_, err = pctxt.PerEncUnconsLen(0)
		if err != nil {
			err = fmt.Errorf("PerEncReal10: %w", err)
			return
		}

		pctxt.DiagNewBitField("Real10")
	}

	pctxt.DiagSetBitFieldCount()
	return nil
}
