// EncGetIdentByteCount - Get number of bytes needed for specified ident
// parameter.
func EncGetIdentByteCount(ident uint64) uint64 {
	if ident < (1 << 7) {
		return 1
	} else if ident < (1 << 14) {
		return 2
	} else if ident < (1 << 21) {
		return 3
	} else if ident < (1 << 28) {
		return 4
	}
	return 5
}
