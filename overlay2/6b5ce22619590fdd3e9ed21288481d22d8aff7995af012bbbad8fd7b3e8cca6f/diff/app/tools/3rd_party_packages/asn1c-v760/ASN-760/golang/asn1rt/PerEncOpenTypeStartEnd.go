// PerEncOpenTypeStart prepares the encode buffer for encoding an open type
// in place. The assumption is made that the length of encoding in most cases
// will fit into one byte. If this is true, then encoding is more efficient
// then encoding to a temporary buffer and copying the contents to the main
// encode buffer. If not true, encoding should be roughly the same in terms
// of time because the encoded bytes will need to be shifted forward. It will,
// however, be more efficient in terms of memory consumption.
func (pctxt *OSRTContext) PerEncOpenTypeStart() (uint64, error) {
	return pctxt.PerEncEmbeddedLenStart()
}

// PerEncOpenTypeEnd will complete a PER open type encoding which was initiated
// using PerEncOpenTypeStart. It will encode and fill in the length value. The
// buffer contents will be shifted if necessary
func (pctxt *OSRTContext) PerEncOpenTypeEnd(bitidx uint64) error {
	// The encoded open type value must first be padded out to a byte boundary
	for (pctxt.BitOffset()-bitidx)%8 != 0 {
		err := pctxt.EncBit(false)
		if err != nil {
			return err
		}
	}
	return pctxt.PerEncEmbeddedLenEnd(bitidx, false)
}
