// intByteCount returns the smallest number of bytes needed to
// represent the given value in 2's complement form
// Examples:
// 	intByteCount(0) == 1
//  intByteCount(255) == 2
func intByteCount(val int) uint8 {
	var retVal uint8

	var mask int = 0x7f80 << (bits.UintSize - 16)
	retVal = bits.UintSize / 8

	if val < 0 {
		/* Take bit-wise complement of val.  However many
		octets are needed to represent that positive
		value, the same will be needed to represent
		the original value.
		*/
		val = ^val
	}

	for (retVal > 1) && ((val & mask) == 0) {
		mask >>= 8
		retVal--
	}

	return retVal
}

// octetBitLen returns the size of the binary number held in the
// highest bits of w.  It is equal to 8 minus the number of trailing
// zero bits in the low bits of w.
// For example:
//		octetBitLen(0) == 0.
// 		octetBitLen(1) == 8.
// 		octetBitLen(0x80) == 1.
func octetBitLen(w uint8) (len uint8) {
	/* binary search */

	if w&0xF > 0 {
		if w&3 > 0 {
			if w&1 > 0 {
				len = 8
			} else {
				len = 7
			}
		} else {
			if w&4 > 0 {
				len = 6
			} else {
				len = 5
			}
		}
	} else {
		if w&0x30 > 0 {
			if w&0x10 > 0 {
				len = 4
			} else {
				len = 3
			}
		} else {
			if w&0x40 > 0 {
				len = 2
			} else {
				if w > 0 {
					len = 1
				} else {
					len = 0
				}
			}
		}
	}
	return
}

// PerEncReal encodes value as an ASN.1 REAL.
// The value will be encoded as base 2.  Special values (e.g. plus-infinity)
// are allowed.
func (pctxt *OSRTContext) PerEncReal(value Real) error {

	var err error

	/* special real values for +/- oo, NAN, -0 */
	if math.IsInf(float64(value), -1) {
		_, err = pctxt.PerEncUnconsLen(1)
		if err != nil {
			return fmt.Errorf("PerEncReal: %w", err)
		}

		pctxt.DiagNewBitField("Real")

		err = pctxt.PerEncBitsFromUInt(asn1KMinusInfinity, 8)
		if err != nil {
			return fmt.Errorf("PerEncReal: %w", err)
		}
	} else if math.IsInf(float64(value), 1) {
		_, err = pctxt.PerEncUnconsLen(1)
		if err != nil {
			return fmt.Errorf("PerEncReal: %w", err)
		}

		pctxt.DiagNewBitField("Real")

		err = pctxt.PerEncBitsFromUInt(asn1KPlusInfinity, 8)
		if err != nil {
			return fmt.Errorf("PerEncReal: %w", err)
		}
	} else if math.IsNaN(float64(value)) {
		_, err = pctxt.PerEncUnconsLen(1)
		if err != nil {
			return fmt.Errorf("PerEncReal: %w", err)
		}

		pctxt.DiagNewBitField("Real")

		err = pctxt.PerEncBitsFromUInt(asn1KNaN, 8)
		if err != nil {
			return fmt.Errorf("PerEncReal: %w", err)
		}

	} else if value == 0.0 && math.Signbit(float64(value)) {
		/* -0.0 */
		_, err = pctxt.PerEncUnconsLen(1)
		if err != nil {
			return fmt.Errorf("PerEncReal: %w", err)
		}

		pctxt.DiagNewBitField("Real")

		err = pctxt.PerEncBitsFromUInt(asn1KMinusZero, 8)
		if err != nil {
			return fmt.Errorf("PerEncReal: %w", err)
		}
	} else if value != 0.0 {
		/* encode a binary real value */
		const float64Bytes = 8
		var len uint8 = 1
		var sign int
		var buf [float64Bytes]byte

		/* Frexp gives mant, e such that:
		 * value == mant * 2 ^ e
		 * 0.5 <= |mant| < 1.0  */
		var e int
		mant, e := math.Frexp(float64(value))

		/* set sign and make mantissa = | mantissa | */
		if mant < 0.0 {
			sign = -1
			mant *= -1
		} else {
			sign = 1
		}

		tmp := mant

		/* Calculate multiplier to produce normalized REAL.
		Normalized REAL is necessary for PER encoding as it uses DER/CER
		encoding rules for REAL type.
		REAL is normalized, if mantissa is either zero or odd.

		Shift the mantissa bits left 16 bits at a time until we find
		the last word to have some bits set.
		*/
		var last uint16 = 0 // The lowest 16 bits of mantissa having bits set.

		for i := 0; i < float64Bytes; i++ {
			/* shift 16 bits worth to the left of the decimal */
			tmp *= 1 << 16

			/* grab only the integer part */
			imant := uint16(tmp)

			/* remove part to left of decimal now for next iteration */
			tmp -= float64(imant)

			if imant > 0 {
				last = imant
			} else if tmp == 0 {
				// No more bits remain.
				break
			}
		}

		/* Use the last word from the mantissa with bits set to determine
		how much to shift left so that the lowest bit set will be the lowest bit
		of a byte (making the mantissa odd).
		We may get mult == 8.  A shift would not be necessary for alignment,
		but it is still necessary for the logic below, which is going to assume
		we end up with mant > 0. */
		var mult uint8
		if last&0xFF > 0 {
			mult = octetBitLen(uint8(last & 0xFF))
		} else {
			mult = octetBitLen(uint8(last >> 8))
		}

		/* Shift 'mult' bits worth to the left of the decimal. Since mant != 0,
		last != 0, we know mult != 0. */
		tmp = mant * float64(uint8(1)<<mult)
		e -= int(mult) /* correct exponent */

		/* Convert mantissa into an unsigned integer.
		The first byte has already been shifted into the integer part.
		*/
		var mantLen uint8 = 1
		for i := 0; i < float64Bytes; i++ {
			/* grab only the integer part */
			imant := uint32(tmp)

			/* remove part to left of decimal now for next iteration */
			tmp -= float64(imant)

			/* write into tmp buffer */
			buf[i] = byte(imant)

			if tmp == 0.0 {
				break
			}

			/* Shift 8 bits worth to the left of the decimal (for the next iteration)*/
			tmp *= 1 << 8
			mantLen++
			e -= 8 /* correct exponent */
		}
		len += mantLen

		/*
		* write format octet  (first octet of content)
		*  field  1 S bb ff ee
		*  bit#   8 7 65 43 21
		*
		* 1 in bit#1 means binary rep
		* 1 in bit#2 means the mantissa is neg, 0 pos
		* bb is the base:    65  base
		*                    00    2
		*                    01    8
		*                    10    16
		*                    11    future ext.
		*
		* ff is the Value of F where  Mantissa = sign x N x 2^F
		*    FF can be one of 0 to 3 inclusive. (used to save re-alignment)
		*
		* ee is the length of the exponent:  21   length
		*                                    00     1
		*                                    01     2
		*                                    10     3
		*                                    11     long form
		*
		*
		* encoded binary real value looks like
		*
		*     fmt oct
		*   --------------------------------------------------------
		*   |1Sbbffee|  exponent (2's comp)  |   N (unsigned int)  |
		*   --------------------------------------------------------
		*    87654321
		 */

		var firstOctet uint8 = realBinary
		if sign == -1 {
			firstOctet |= realSign
		}

		/* bb is 00 since base is 2 so do nothing */
		/* ff is 00 since no other shifting is nec */
		var ll uint8 = intByteCount(e) /* calc length of exponent (in bytes) */

		len += ll
		switch ll {
		case (1):
			firstOctet |= realExpLen1
		case (2):
			firstOctet |= realExpLen2
		case (3):
			firstOctet |= realExpLen3
		default:
			firstOctet |= realExpLenLong
			len++
		}

		_, err = pctxt.PerEncUnconsLen(uint64(len))
		if err != nil {
			return fmt.Errorf("PerEncReal: %w", err)
		}

		pctxt.DiagNewBitField("Real")

		/* write the format octet */

		err = pctxt.EncBitsFromByte(firstOctet, 8)
		if err != nil {
			return fmt.Errorf("PerEncReal: %w", err)
		}

		if (firstOctet & realExpLenMask) == realExpLenLong {
			/* write exponent length */

			err = pctxt.PerEncBitsFromUInt8(ll, 8)
			if err != nil {
				return fmt.Errorf("PerEncReal: %w", err)
			}
		}

		/* write the exponent */

		err = pctxt.PerEncBitsFromUInt(uint64(e), uint64(ll)*8)
		if err != nil {
			return fmt.Errorf("PerEncReal: %w", err)
		}

		/* write the mantissa (N value) */

		err = pctxt.EncBytes(buf[0:mantLen])
		if err != nil {
			return fmt.Errorf("PerEncReal: %w", err)
		}
	} else {
		/* no contents for 0.0 reals */
		_, err = pctxt.PerEncUnconsLen(0)
		if err != nil {
			return fmt.Errorf("PerEncReal: %w", err)
		}

		pctxt.DiagNewBitField("Real")

	}

	pctxt.DiagSetBitFieldCount()

	return nil
}
