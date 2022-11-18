// decBytes reads the given number of bytes from input and returns an array
// containing the data read.
// The returned slice may be backed by the input data, so that modifications
// to it will modify the input data and also the input data will not be garbage
// collected until the slice is garbarge collected.  If this is undesirable,
// use DecBytesCopy instead.
func (pctxt *OSRTContext) decBytes(nbytes uint64) (value []byte, err error) {
	if pctxt.buffer.bitOffset == 8 {
		if nbytes > uint64(len(pctxt.buffer.data))-pctxt.buffer.byteIndex {
			err = fmt.Errorf("decBytes: buffer overflow")
			return
		}

		value = pctxt.buffer.data[pctxt.buffer.byteIndex : pctxt.buffer.byteIndex+nbytes]
		pctxt.buffer.byteIndex += nbytes
	} else {
		/* Data is not byte-aligned.  We'll have to copy the data. */
		value = make([]byte, nbytes)
		err = pctxt.DecBytesIntoSlice(value)
	}
	return
}
