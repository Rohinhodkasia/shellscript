// RestrCharEncoding wraps the functions required to encode restricted
// character strings in PER when the encoding involves character translation
// into a smaller number of bits than the base type would be encoded in.
type RestrCharEncoding interface {
	//NumBits returns the number of bits each character is encoded into.
	//The values returned by Translate must be representable in this
        //number of bits.
	NumBits() uint8

	//Actual2Encoded returns the value that should be encoded for the given value.
	//actual >= 0 and encodeAs <= actual
	Actual2Encoded(actual rune) (encodeAs rune, err error)

	//Encoded2Actual returns the value that is encoded using the given value.
	//encodeAs >= 0 and actual >= rune
	Encoded2Actual(encodeAs rune) (actual rune, err error)
}

// PermittedAlphabetRange implements the RestrCharEncoding interface.
// It is used in the case where the permitted alphabet is specified by
// a range of contiguous characters.
type PermittedAlphabetRange struct {
	//Bits is the number of bits each character is encoded into.
	Bits uint8

	//LowerBound is the smallest character in the range.
	LowerBound rune
}

//NumCanSet is the effective permitted alphabet for NumericString
const NumCanSet = " 0123456789"

// NumBits implements RestrCharEncoding.NumBits
func (x PermittedAlphabetRange) NumBits() uint8 {
	return x.Bits
}

// Actual2Encoded implements RestrCharEncoding.Actual2Encoded
func (x PermittedAlphabetRange) Actual2Encoded(actual rune) (encodedAs rune, err error) {
	if actual < x.LowerBound {
		err = fmt.Errorf("Character out of bounds: %v", actual)
	}
	encodedAs = actual - x.LowerBound

	return
}

// Encoded2Actual implements RestrCharEncoding.EncodedToActual
func (x PermittedAlphabetRange) Encoded2Actual(encodedAs rune) (actual rune, err error) {
	actual = x.LowerBound + encodedAs
	return
}

// PermittedAlphabetList implements the RestrCharEncoding interface.
// It is used in the case where the permitted alphabet is specifed by
// listing all of the characters of the alphabet, in sorted order.
type PermittedAlphabetList struct {
	// Bits is the number of bits each character is encoded into.
	Bits uint8

	// Characters is the sorted list of characters in the permitted
	// alphabet.  It is a UTF-8 string.
	Characters string

	// runes consists of the runes corresponding to Characters.
	// It is initialized by the initRunes function.
	runes []rune
}

// NumBits implements RestrCharEncoding.NumBits
func (x PermittedAlphabetList) NumBits() uint8 {
	return x.Bits
}

// initRunes initializes runes based on Characters.
func (x *PermittedAlphabetList) initRunes() (err error) {
	if x.runes != nil {
		return /* already initialized */
	}

	var reader *strings.Reader = strings.NewReader(x.Characters)

	for {
		var ch rune
		ch, _, err = reader.ReadRune()
		if err == io.EOF {
			/* End of string */
			err = nil
			return
		} else if err != nil {
			err = fmt.Errorf("initRunes: %w", err)
			return
		} else {
			x.runes = append(x.runes, ch)
		}
	}
}

// Actual2Encoded implements RestrCharEncoding.Actual2Encoded
func (x *PermittedAlphabetList) Actual2Encoded(actual rune) (encodedAs rune, err error) {

	if x.runes == nil {
		err = x.initRunes()
		if err != nil {
			return
		}
	}

	for idx := 0; idx < len(x.runes); idx++ {
		if x.runes[idx] == actual {
			encodedAs = rune(idx)
			return
		}
	}

	err = fmt.Errorf("Character not in alphabet: %v", actual)
	return
}

// Encoded2Actual implements RestrCharEncoding.Encoded2Actual
func (x *PermittedAlphabetList) Encoded2Actual(encodedAs rune) (actual rune, err error) {

	if x.runes == nil {
		err = x.initRunes()
		if err != nil {
			return
		}
	}

	if encodedAs >= rune(len(x.runes)) {
		err = fmt.Errorf("Invalid encoded value: %v", encodedAs)
		return
	}

	actual = x.runes[encodedAs]
	return
}

// UTF8Len returns the number of characters in a string, interpreted as UTF-8
// data. This function is for use by generated code.  It exists because Go
// reports
// errors on unused packages, making it simpler to avoid a direct import
// of unicode/utf8 in the generated code.
func UTF8Len(value string) uint64 {
	return uint64(utf8.RuneCountInString(value))
}
