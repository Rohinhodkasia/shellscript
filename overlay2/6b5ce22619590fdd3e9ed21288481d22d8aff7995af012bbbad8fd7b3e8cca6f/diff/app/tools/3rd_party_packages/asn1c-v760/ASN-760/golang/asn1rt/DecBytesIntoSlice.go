// DecBytesCopy read the given number of bytes from input and returns an array
// containing the data read.
// This will always make a copy of the input data. See also DecBytes for a
// possible alternative.
func (pctxt *OSRTContext) DecBytesCopy(nbytes uint64) (value []byte, err error) {
	value = make([]byte, nbytes)
	err = pctxt.DecBytesIntoSlice(value)
	return
}

// DecBytesIntoSlice reads len(value) bytes from input into value.
func (pctxt *OSRTContext) DecBytesIntoSlice(value []byte) (err error) {
	nbytes := uint64(len(value))

	if pctxt.buffer.bitOffset == 8 {
		if nbytes > uint64(len(pctxt.buffer.data))-pctxt.buffer.byteIndex {
			err = fmt.Errorf("DecBytesIntoSlice: buffer overflow")
			return
		}

		copy(value, pctxt.buffer.data[pctxt.buffer.byteIndex:pctxt.buffer.byteIndex+nbytes])
		pctxt.buffer.byteIndex += nbytes
	} else {
		for i := uint64(0); i < nbytes; i++ {
			var ub uint64
			ub, err = pctxt.PerDecBitsToUInt(8)
			if err != nil {
				err = fmt.Errorf("DecBytesIntoSlice: %w", err)
				return
			}
			value[i] = byte(ub)
		}
	}
	return
}
