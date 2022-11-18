// PerEncEmbeddedLenEnd will complete a PER embedded length encoding which
// was initiated using PerEncEmbeddedLenStart. It will encode and fill in
// the length value. The buffer contents will be shifted if necessary.
func (pctxt *OSRTContext) PerEncEmbeddedLenEnd(bitidx uint64, bitlen bool) error {
	lenvalue := (pctxt.BitOffset() - bitidx - 8)
	if !bitlen {
		lenvalue /= 8 // length in bytes
	}
	savedByteIndex := pctxt.buffer.byteIndex

	// if length < 128, we can encode a single byte length into the area we
	// reserved and we are done
	if lenvalue < 128 {
		// Restore context bit offset to where length encoding started
		pctxt.SetBitOffset(bitidx)
		if pctxt.buffer.bitOffset == 8 {
			pctxt.buffer.data[pctxt.buffer.byteIndex] = byte(lenvalue)
		} else {
			// patch first byte
			tmp := pctxt.buffer.data[pctxt.buffer.byteIndex]
			mask := byte(0x80 >> (8 - pctxt.buffer.bitOffset))
			lenmask := byte(0x80)
			lenbyte := byte(lenvalue)
			for mask != 0 {
				if (lenbyte & lenmask) != 0 {
					tmp = tmp | mask
				}
				mask = mask >> 1
				lenmask = lenmask >> 1
			}
			pctxt.buffer.data[pctxt.buffer.byteIndex] = tmp
			pctxt.buffer.byteIndex++

			// patch 2nd byte
			tmp = pctxt.buffer.data[pctxt.buffer.byteIndex]
			mask = 0x80
			for lenmask != 0 {
				if (lenbyte & lenmask) != 0 {
					tmp = tmp | mask
				}
				mask = mask >> 1
				lenmask = lenmask >> 1
			}
			pctxt.buffer.data[pctxt.buffer.byteIndex] = tmp
		}
		pctxt.buffer.byteIndex = savedByteIndex
	} else {
		// Encode length at the end of the buffer
		endBitOffset := pctxt.buffer.bitOffset

		pctxt2 := new(OSRTContext)
		pctxt2.InitEncode()
		_, err := pctxt2.PerEncUnconsLen(lenvalue)
		if err != nil {
			return err
		}

		// Shift contents of the encode buffer to make space for the length
		pctxt.SetBitOffset(bitidx)
		idx := pctxt.buffer.byteIndex
		encbuf := &pctxt.buffer
		tmpbuf := pctxt2.buffer.data
		tmplen := pctxt2.buffer.byteIndex
		for i := uint64(0); i < tmplen-1; i++ {
			encbuf.data = append(encbuf.data, 0)
		}
		copy(encbuf.data[idx+tmplen:], encbuf.data[idx+1:savedByteIndex+tmplen-1])

		// Merge saved length into encode buffer
		err = pctxt.PerEncMergeBytes(tmpbuf, bitidx)
		if err != nil {
			return err
		}

		// Adjust bit offsets in diag bit trace records
		pctxt.DiagAdjustBitOffsets(bitidx, (tmplen-1)*8)

		pctxt.buffer.bitOffset = endBitOffset
		pctxt.buffer.byteIndex = uint64(len(encbuf.data))
	}
	// this is needed to cause the PenEncUnconsLen function to be included
	// pctxt.PerEncUnconsLen(lenvalue)

	return nil
}
