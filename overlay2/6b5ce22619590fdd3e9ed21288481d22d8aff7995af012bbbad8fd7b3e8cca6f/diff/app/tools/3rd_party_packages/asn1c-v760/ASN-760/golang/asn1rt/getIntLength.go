func getIntLength(value int64) int {
	var tempValue uint64
	var shift int

	/* Calculate signed number value length */
	// note: in C, shift is calculated as follows:
	// int shift = (int)(((sizeof(value) - 1) * 8) - 1);
	// for a 64-bit integer, this produces a value of 55

	for shift = 55; shift > 0; shift -= 8 {
		tempValue = uint64((value >> shift) & 0x1ff)
		if tempValue == 0 || tempValue == 0x1ff {
			continue
		} else {
			break
		}
	}

	return (shift + 9) / 8
}
