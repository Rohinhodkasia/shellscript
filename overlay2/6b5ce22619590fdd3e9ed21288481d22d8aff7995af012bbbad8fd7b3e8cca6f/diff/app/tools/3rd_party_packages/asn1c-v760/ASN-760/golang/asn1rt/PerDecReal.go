// perDecRealInternal decodes an ASN.1 REAL value.  It requires the encoded base
// to be base 2, if base2Only is true.
func (pctxt *OSRTContext) perDecRealInternal(base2Only bool) (value Real, err error) {

	/* Decode unconstrained length */
	len, fragmented, err := pctxt.PerDecUnconsLen()
	if err != nil {
		err = fmt.Errorf("perDecRealInternal: %w", err)
		return
	}
	if fragmented {
		err = fmt.Errorf("Unexpected fragmetation: REAL")
		return
	}

	if len == 0 {
		value = 0
		return
	}

	pctxt.DiagNewBitField("Real")

	/* Fetch first octet */
	firstOctet, err := pctxt.PerDecBitsToUInt(8)
	if err != nil {
		err = fmt.Errorf("perDecRealInternal: %w", err)
		return
	}

	/* Check for special real values (plus/minus infinity) */
	if len == 1 {
		switch firstOctet {
		case asn1KPlusInfinity:
			value = Real(math.Inf(1))
			return
		case asn1KMinusInfinity:
			value = Real(math.Inf(-1))
			return
		case asn1KNaN:
			value = Real(math.NaN())
			return
		case asn1KMinusZero:
			value = Real(math.Copysign(0, -1))
			return
		default:
			err = fmt.Errorf("perDecRealInternal: invalid real")
			return
		}
	}

	len--

	/* Decode normal ASN.1 real value */
	var expLen uint8

	if firstOctet&realBinary > 0 {
		switch firstOctet & realExpLenMask {
		case (realExpLen1):
			expLen = 1
		case (realExpLen2):
			expLen = 2
		case (realExpLen3):
			expLen = 3

		default:
			{
				/* Long form.  Second octet encodes number of octets used for exponent. */
				var b uint64
				b, err = pctxt.PerDecBitsToUInt(8)
				if err != nil {
					err = fmt.Errorf("perDecRealInternal: %w", err)
					return
				}
				expLen = uint8(b)
				len--
			}
		}

		/* Decode exponent integer */
		var exponent int64
		exponent, err = pctxt.DecInt(expLen)
		if err != nil {
			err = fmt.Errorf("perDecRealInternal: %w", err)
			return
		}

		len -= uint64(expLen)

		/* Now get the mantissa */

		mantissa := Real(0.0)

		for i := uint64(0); i < len; i++ {
			var b uint64
			b, err = pctxt.PerDecBitsToUInt(8)
			if err != nil {
				err = fmt.Errorf("perDecRealInternal: %w", err)
				return
			}

			mantissa *= 1 << 8
			mantissa += Real(b)
		}

		/* adjust N by scaling factor */

		mantissa *= Real(uint64(1) << ((firstOctet & realFactorMask) >> 2))

		var base uint64
		switch firstOctet & realBaseMask {
		case realBase2:
			base = 2
		default:
			err = fmt.Errorf("perDecRealInternal: invalid real")
			return
		}

		value = mantissa * Real(math.Pow(float64(base), float64(exponent)))

		if firstOctet&realSign > 0 {
			value = -value
		}
	} else {
		/* Decimal version, process decoding according to ISO 6093 */
		//    char         mark, sbuf[256], *buf, *pb;

		if base2Only {
			err = fmt.Errorf("perDecRealInternal: base 2 encoding required")
			return
		}

		/* C code formats 0.0 to determine floating point character for the
		current locale.  This does not seem to work for Go.
		*/

		var buf []byte
		buf, err = pctxt.decBytes(len)
		if err == nil {
			/* PER REAL in decimal form must be encoded only in NR3 form */
			if (firstOctet & realIso6093Mask) != 3 {
				err = fmt.Errorf("perDecRealInternal: invalid real.  NR3 form required")
			} else {
				/* Make sure string contains only expected characters.  ParseFloat would
				allow some invalid strings, such as "Infinity" */
				for _, pb := range buf {
					if !((pb >= '0' && pb <= '9') ||
						pb == '.' || pb == ',' ||
						pb == '+' || pb == '-' ||
						pb == 'E' || pb == 'e') {
						err = fmt.Errorf("perDecRealInternal: invalid char(%c)", pb)
						break
					}
				}
				if err == nil {
					var floatvalue, err = strconv.ParseFloat(string(buf), 64)
					value = Real(floatvalue)
					if err != nil {
						err = fmt.Errorf("perDecRealInternal: %w", err)
					}
				}
			}
		}

		if err != nil {
			err = fmt.Errorf("perDecRealInternal: %w", err)
		}

	}
	pctxt.DiagSetBitFieldCount()

	return
}

// PerDecReal decodes an ASN.1 REAL value from pctxt.
// This function allows the value to have been encoded using base 2 or base 10,
// which is appropriate for unconstrained REAL.
// Special values (e.g. plus-infinity) are supported.
func (pctxt *OSRTContext) PerDecReal() (value Real, e error) {
	return pctxt.perDecRealInternal(false)
}

// PerDecReal2 decodes an ASN.1 REAL value from pctxt.
// This function allows the value to have been encoded using base 2 only,
// which is appropriate for type REAL constrained to base 2 values.
// Special values (e.g. plus-infinity) are supported.
func (pctxt *OSRTContext) PerDecReal2() (value Real, e error) {
	return pctxt.perDecRealInternal(true)
}
