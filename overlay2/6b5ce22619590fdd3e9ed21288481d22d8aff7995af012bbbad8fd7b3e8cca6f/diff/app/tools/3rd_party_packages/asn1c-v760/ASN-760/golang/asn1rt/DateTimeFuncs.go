var daysInMonth []byte = []byte{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}

// isLeapYear returns whether the given year is a leap year or not.
func isLeapYear(year uint16) bool {
	return ((year%4 == 0) && (year%100 != 0)) || (year%400 == 0)
}

// maxDaysInMonth returns the number of days in the given month of the given year.
func maxDaysInMonth(year uint16, month uint8) (days uint8) {
	if isLeapYear(year) && month == 2 {
		days = daysInMonth[month-1] + 1
	} else {
		days = daysInMonth[month-1]
	}
	return
}

/* datetime represents a parsed GeneralizedTime or UTCTime value.
Shallow copies are unsafe.
*/
type datetime struct {
	year    uint16
	month   uint8 /* 1 <=  mon <= 12   */
	day     uint8 /* 1 <=  day <= 31   */
	hour    uint8 /* 0 <=  hour <= 23   */
	minute  uint8 /* 0 <=  min <= 59	*/
	second  uint8 /* 0 <= sec <= 59 */
	secFrac struct {
		num   uint64 /* num is 0 or evenly divisible by 10 */
		denom uint64 /* denom is a power of 10, >= 1, and num < denom */
	}
	tzFlag bool  /* is tzo explicitely set? */
	tzo    int16 /* -840 <= tzo <= 840 */
}

// makeTime creates an ASN.1 GeneralizedTime or ASN.1 UTCTime string from the given datetime object.
func makeTime(dateTime *datetime, utc bool) (value string, err error) {
	var sb strings.Builder

	if !rtxDateTimeIsValid(dateTime) {
		err = fmt.Errorf("makeTime: invalid datetime")
		return
	}

	if utc {
		/* Year is more restricted in UTC time */
		if dateTime.year < 1950 || dateTime.year > 2049 {
			err = fmt.Errorf("makeTime: UTCTime year (%d) is out of range", dateTime.year)
			return
		}

		sb.WriteString(
			fmt.Sprintf("%02d%02d%02d%02d%02d%02d",
				dateTime.year%100, dateTime.month, dateTime.day,
				dateTime.hour, dateTime.minute, dateTime.second))
	} else {

		/* YYYYMMDDHH[MM[SS[(.|,)SSSS]]][TZD] */
		sb.WriteString(
			fmt.Sprintf("%04d%02d%02d%02d%02d%02d",
				dateTime.year, dateTime.month, dateTime.day,
				dateTime.hour, dateTime.minute, dateTime.second))

		if dateTime.secFrac.num > 0 {
			/* There is a fraction part. */
			sb.WriteByte('.')
			fracDigits := uint64(math.Log10(float64(dateTime.secFrac.denom)))
			sb.WriteString(
				fmt.Sprintf("%*d", fracDigits, dateTime.secFrac.num))
		}
	}

	if utc && !dateTime.tzFlag {
		err = fmt.Errorf("makeTime: UTCTime requires UTC designation or timezone offset")
		return
	}

	if dateTime.tzFlag && dateTime.tzo == 0 {
		sb.WriteByte('Z')
	} else if dateTime.tzFlag {
		var tz int16

		if dateTime.tzo < 0 {
			tz = -dateTime.tzo
			sb.WriteByte('-')
		} else {
			tz = dateTime.tzo
			sb.WriteByte('+')
		}
		sb.WriteString(fmt.Sprintf("%02d%02d", tz/60, tz%60))
	}

	value = sb.String()
	return
}

// normalizeTimeZone takes a datetime with an offset from UTC and
// converts it to using UTC (0 offset).
func normalizeTimeZone(pvalue *datetime) {
	if !pvalue.tzFlag {
		panic("Cannot normalize local time")
	}

	if pvalue.tzo == 0 {
		return // already normalized.
	}

	/* Adjust time by subtracting the tzo offset from the minutes field.
	Then, normalize the minutes, hours, day, month, and year as needed.
	*/
	tmp := int16(pvalue.minute) - pvalue.tzo //raw adjusted value of field being updated (minutes, then hours, etc.)
	roll := tmp / 60                         // value to add (or subtract if negative) to (from) the next field to bring
	// the current field into range.

	tmp = tmp - roll*60 // result after adding/borrowing from next field
	if tmp < 0 {
		/* roll <= 0, meaning we're borrowing hours to add to minutes.  We need to borrow 1 hour more to get
		0 < min < 60, which means decrementing roll. */
		tmp += 60
		roll--
	} //else: 0<= tmp < 60

	pvalue.minute = uint8(tmp)
	pvalue.tzo = 0

	if roll == 0 {
		return
	}

	/* Adjust hours */
	tmp = int16(pvalue.hour) + roll /* raw hours */
	roll = tmp / 24                 /* days to add/subtract to/from days field */
	tmp = tmp - roll*24
	if tmp < 0 {
		/* Borrwing days; borrow one more */
		tmp += 24
		roll--
	}
	pvalue.hour = uint8(tmp)

	if roll == 0 {
		return
	}

	/* Adjus days */
	tmp = int16(pvalue.day) + roll /* raw adjusted day */

	if tmp <= 0 {
		/* Borrow # of prev month's days */
		if pvalue.month == 1 {
			tmp += 31
		} else {
			tmp += int16(maxDaysInMonth(pvalue.year, pvalue.month-1))
		}
		roll = -1
	} else {
		maxday := maxDaysInMonth(pvalue.year, pvalue.month)
		if tmp > int16(maxday) {
			tmp -= int16(maxday)
			roll = 1
		} else {
			//tmp is valid day value
			pvalue.day = uint8(tmp)
			return
		}
	}
	pvalue.day = uint8(tmp)

	tmp = int16(pvalue.month) + roll
	if tmp <= 0 {
		pvalue.month = uint8(tmp + 12)
		pvalue.year--
	} else if tmp > 12 {
		pvalue.month = uint8(tmp - 12)
		pvalue.year++
	} else {
		pvalue.month = uint8(tmp)
	}

	return
}

// parseTime parses an ASN.1 GeneralizedTime or ASN.1 UTCTime into a datetime object.
// If utc is true, a UTCTime is parsed; otherwise a GeneralizedTime is parsed.
//
// If there are any violations of the canonical rules in X.690 (and shared by X.691),
// these are reported in canonVio, not in err.
//
// If midnight is represented using hour 24, the returned datetime is adjusted (as many
// fields as necessary) to use hour 00.  This canonical violation will also be noted in
// canonVio.
func parseTime(value string, utc bool) (dt datetime, canonVio []string, err error) {
	var diffHour, diffMin uint8
	var fracNum uint64 = 0   /* fraction numerator */
	var fracDenom uint64 = 1 /* fraction denominator */
	var p string = value
	var fixMidnight bool = false
	var n uint
	var tzd byte

	if utc {
		dt.year, dt.month, dt.day, err = parseYYMMDD(p)
		if dt.year >= 50 {
			dt.year += 1900
		} else {
			dt.year += 2000
		}

		if err == nil {
			p = p[6:]
		}
	} else {
		dt.year, dt.month, dt.day, err = parseYYYYMMDD(p)
		if err == nil {
			p = p[8:]
		}
	}

	if err == nil {
		n = 0

		// Decode hour (required)
		dt.hour, err = digitCharsToUint8(p, 2)

		if err == nil {
			p = p[2:]
			n++

			// Decode minutes if present
			if len(p) > 0 && unicode.IsDigit(rune(p[0])) {
				dt.minute, err = digitCharsToUint8(p, 2)
				if err == nil {
					p = p[2:]
					n++
				}

				//Decond seconds if present
				if len(p) > 0 && unicode.IsDigit(rune(p[0])) {
					dt.second, err = digitCharsToUint8(p, 2)
					if err == nil {
						p = p[2:]
						n++
					}
				}
			}
		}
	}

	if n < 3 {
		canonVio = append(canonVio, "seconds missing")
	}

	if err == nil && !utc && len(p) > 0 && (p[0] == byte('.') || p[0] == ',') {
		/* fraction of hour, minute, or second */
		var j int /* count of fractional digits */

		if p[0] == ',' {
			canonVio = append(canonVio, "Use of ',' separator")
		}

		p = p[1:]

		/* parse fraction digits.  It is legal (but not canonical) for there to be no fraction
		digits after the decimal separator. */
		for j = 0; len(p) > 0 && unicode.IsDigit(rune(p[0])); j, p = j+1, p[1:] {
			fracNum = fracNum*10 + (uint64(p[0]) - uint64('0'))
			fracDenom *= 10
		}

		if j == 0 {
			canonVio = append(canonVio, "Use of decimal separator without fraction digits")
		} else if fracNum%10 == 0 {
			canonVio = append(canonVio, "trailing zeros in fraction")
		}

		/* convert frational hours/mins to frac seconds */
		if n == 1 {
			fracNum *= 60 /* was hours; now is minutes */
			if fracNum >= fracDenom {
				/* Fraction of hour gives a whole number of minutes.  Reduce. */
				dt.minute = uint8(fracNum / fracDenom) // < 60
				fracNum -= uint64(dt.minute) * fracDenom
			}
		}

		if n < 3 {
			fracNum *= 60 /* was minutes; now is seconds */
			if fracNum >= fracDenom {
				/* Fraction of minutes gives a whole number of seconds.  Reduce. */
				dt.second = uint8(fracNum / fracDenom) // < 60
				fracNum -= uint64(dt.second) * fracDenom
			}
		}

		/* Adjust fraction to be in reduced form */
		for fracNum > 0 && fracNum%10 == 0 {
			fracNum = fracNum / 10
			fracDenom /= 10
		}
	}

	dt.tzFlag = false
	if err == nil && len(p) > 0 {
		tzd = p[0]
		if tzd == 'Z' && len(p) == 1 {
			/* utc */
			dt.tzFlag = true
			p = p[1:]
		} else if tzd == '-' || tzd == '+' {
			canonVio = append(canonVio, "Timezone offset used; UTC required")

			dt.tzFlag = true
			p = p[1:]
			diffHour, err = digitCharsToUint8(p, 2)

			if err == nil {
				p = p[2:]
				if diffHour > 13 {
					err = fmt.Errorf("parseTime: invalid hour offset in \"%s\"", value)
					return
				}

				if len(p) > 0 {
					diffMin, err = digitCharsToUint8(p, 2)

					if err == nil && diffMin > 59 {
						err = fmt.Errorf("parseTime: invalid minute offset in \"%s\"", value)
						return
					}
				}
				//else: no minutes in offset
			}
		} else {
			/* string does not end with just Z */
			err = fmt.Errorf("parseTime: extraneous characters in \"%s\"", value)
			return
		}
	} else if utc {
		err = fmt.Errorf("parseTime: missing UTC designation or timezone offset in \"%s\"", value)
		return
	} else {
		canonVio = append(canonVio, "Local time used; UTC required")
	}

	dt.secFrac.num = fracNum
	dt.secFrac.denom = fracDenom
	dt.tzo = int16(diffHour)*60 + int16(diffMin)
	if tzd == '-' {
		dt.tzo *= -1
	}

	if dt.hour == 24 && dt.minute == 0 && dt.second == 0 {
		/* 240000 is valid for midnight.  Change it to 00, make sure fields
		are otherwise valid, then add a day. */
		fixMidnight = true
		dt.hour = 0

		/* Using 24 for midnight is a canonical violation */
		canonVio = append(canonVio, "Midnight must use 00 hour")
	}

	if err == nil && !rtxDateTimeIsValid(&dt) {
		err = fmt.Errorf("parseTime: invalid value \"%s\"", value)
		return
	}

	if fixMidnight {
		if dt.day == maxDaysInMonth(dt.year, dt.month) {
			dt.day = 1
			if dt.month == 12 {
				dt.month = 1
				dt.year++
			} else {
				dt.month++
			}
		} else {
			dt.day++
		}
	}

	if err != nil {
		err = fmt.Errorf("parseTime: failed on \"%s\":\n%w", value, err)
	}

	return
}

// digitCharsToUint8 is the same as digitCharsToUint64 except it will panic
// if the result does not fit into a uint8.
func digitCharsToUint8(digits string, ndigits int) (value uint8, err error) {
	var v uint64
	v, err = digitCharsToUint64(digits, ndigits)
	if v > math.MaxUint8 {
		panic("Integer overflow")
	}
	value = uint8(v)
	return
}

// digitCharsToUint16 is the same as digitCharsToUint64 except it will panic
// if the result does not fit into a uint16.
func digitCharsToUint16(digits string, ndigits int) (value uint16, err error) {
	var v uint64
	v, err = digitCharsToUint64(digits, ndigits)
	if v > math.MaxUint16 {
		panic("Integer overflow")
	}
	value = uint16(v)
	return
}

// digitCharsToUInt64 reads the given number of digits from the given string,
// returning the digits as an integer value or an error.
// If the string is too short, this returns an error rather than panicking.
func digitCharsToUint64(digits string, ndigits int) (value uint64, err error) {
	value = 0
	if len(digits) < ndigits {
		err = fmt.Errorf("digitCharsToUint64: unexpected end of string")
		return
	}

	for i := 0; i < ndigits; i++ {
		if unicode.IsDigit(rune(digits[i])) {
			oldvalue := value
			value = value*10 + (uint64(digits[i]) - uint64('0'))
			if value < oldvalue {
				panic("integer overflow")
			}
		} else {
			err = fmt.Errorf("digitCharsToUint64: '%c' is not a digit", digits[i])
			return
		}
	}
	return
}

// parseYYMMDD parses a 2 digit year, month, and day from the given string.
// It will return an error if the input does not match the expected input.
func parseYYMMDD(str string) (year uint16, month, day uint8, err error) {

	year, err = digitCharsToUint16(str, 2)
	if err == nil {
		str = str[2:]
		month, err = digitCharsToUint8(str, 2)
	}

	if err == nil {
		str = str[2:]
		day, err = digitCharsToUint8(str, 2)
	}

	return
}

// parseYYMMDD parses a 4 digit year, and 2 digit month and day from the given string.
// It will return an error if the input does not match the expected input.
func parseYYYYMMDD(str string) (year uint16, month, day uint8, err error) {

	year, err = digitCharsToUint16(str, 4)
	if err == nil {
		str = str[4:]
		month, err = digitCharsToUint8(str, 2)
	}

	if err == nil {
		str = str[2:]
		day, err = digitCharsToUint8(str, 2)
	}

	return
}

func rtxDateIsValid(dateTime *datetime) bool {
	//int dim;
	if dateTime.year < 0 || dateTime.year > 9999 ||
		dateTime.month < 1 || dateTime.month > 12 ||
		(dateTime.tzFlag && (dateTime.tzo < -840 || dateTime.tzo > 840)) {
		return false
	}

	dim := maxDaysInMonth(dateTime.year, dateTime.month)

	if dateTime.day < 1 || dateTime.day > dim {
		return false
	}
	return true
}

func rtxTimeIsValid(dateTime *datetime) bool {

	if dateTime.hour > 23 ||
		dateTime.minute > 59 ||
		dateTime.second < 0 || dateTime.second >= 60 ||
		(dateTime.tzFlag && (dateTime.tzo < -840 || dateTime.tzo > 840)) {
		return false
	}
	return true
}

func rtxDateTimeIsValid(dateTime *datetime) bool {
	return rtxDateIsValid(dateTime) && rtxTimeIsValid(dateTime)
}
