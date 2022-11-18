// DiagBitField describes a bit field within a message
type DiagBitField struct {
	elemName           string
	nameSuffix         string
	bitOffset          uint64
	numbits            uint64
	pOpenTypeFieldList *list.List
	closed             bool /* If true, closed; otherwise open. */
}

type diagBinDumpBuffer struct {
	lb            uint8
	lbm           uint8
	fmtBitBuffer  string
	fmtHexBuffer  string
	fmtAscBuffer  string
	lastBitBuffer string
	repeatCount   uint64
}

// NewBitFieldList creates a new bit field list for bit tracing
func (pctxt *OSRTContext) NewBitFieldList() {
	pctxt.pBitFieldList = new(list.List)
}

// PrintBitFieldList prints the contents of the bit field list in the context
func (pctxt *OSRTContext) PrintBitFieldList(varName string) {
	if pctxt.pBitFieldList != nil {
		var binDumpBuffer diagBinDumpBuffer
		dumpFields(pctxt.pBitFieldList, varName, 0,
			pctxt.buffer.data, nil, &binDumpBuffer)
	}
}

// DiagAdjustBitOffsets finds the first record in the bit field list with 
// the given start offset and then adds the delta value to all subsequent 
// records. Its primary use is to adjust bit field records after an embedded
// length encoding is done.
func (pctxt *OSRTContext)DiagAdjustBitOffsets(startOffset uint64, delta uint64) {
	if pctxt.pBitFieldList == nil {
		return
	}
	var found bool
	for pNode := pctxt.pBitFieldList.Front(); pNode != nil; pNode = pNode.Next() {
		pField := pNode.Value.(*DiagBitField)
		if found {
			pField.bitOffset += delta
		} else if pField.bitOffset == startOffset {
			found = true
			pField.numbits += delta
		}
	}
}

// DiagNewBitField creates a new bit field and adds it at the end of the
// context bit field list.
// A call to this function is a redundant call if the previous field is at the
// same location and is not closed.  Redundant calls are allowed and ignored;
// calls from within the runtime might in some cases be redundant but not
// in others.
// This function will automatically call DiagSetBitFieldCount for the previous field
// (if there is one), if the previous field is not at the same location. Generally,
// this means explicit calls to DiagSetBitFieldCount are not required.  However,
// calling DiagSetBitFieldCount is required for zero-length bit fields.
func (pctxt *OSRTContext) DiagNewBitField(nameSuffix string) *DiagBitField {
	var pBitField *DiagBitField

	if pctxt.pBitFieldList != nil {
		var pPrevField *DiagBitField
		var collocated = false
		var redundant = false
		if pctxt.pBitFieldList.Len() > 0 {
			pPrevField = pctxt.pBitFieldList.Back().Value.(*DiagBitField)
			collocated = pctxt.BitOffset() == pPrevField.bitOffset
			redundant = collocated && !pPrevField.closed
			if redundant {
				return pPrevField
			} else if !collocated && !pPrevField.closed {
				// Automatically call DiagSetBitFieldCount.  If the previous
				// field was zero-length, the fact that the new field is not
				// collocated implies there were alignment bits added and
				// calling DiagSetBitFieldCount would incorrectly set the
				// bit field size, which is why DiagSetBitFieldCount must be
				// called explicitly for zero-length fields.
				pctxt.DiagSetBitFieldCount()
			}
			//else: !redundant and (collocated || pPrevField.closed) implies field is already closed
		}

		// Not a redundant call.
		pBitField = new(DiagBitField)
		pBitField.elemName = pctxt.ElemName()
		pBitField.nameSuffix = nameSuffix
		pBitField.bitOffset = pctxt.BitOffset()
		//fmt.Printf("DiagNewBitField: bitOffset = %d\n",
		//	pBitField.bitOffset)
		pctxt.pBitFieldList.PushBack(pBitField)
	}
	return pBitField
}

// DiagSetBitFieldOffset set the bit offset within the last bit field
// structure to be the current bit field offset in the context
func (pctxt *OSRTContext) DiagSetBitFieldOffset() {
	if pctxt.pBitFieldList != nil && pctxt.pBitFieldList.Len() > 0 {
		var pField = pctxt.pBitFieldList.Back()
		if pField != nil && pField.Value.(*DiagBitField).numbits == 0 {
			pBitField := pField.Value.(*DiagBitField)
			pBitField.bitOffset = pctxt.BitOffset()
			//fmt.Printf("DiagSetBitFieldOffset: bitOffset = %d\n",
			//	pBitField.bitOffset)
			//pField.Value = DiagBitField
		}
	}
}

// DiagSetBitFieldCount sets the bit field count in the last bit field
// structure to be the difference between the current bit offset and
// the bit offset in the previous bit field structure.
func (pctxt *OSRTContext) DiagSetBitFieldCount() {
	if pctxt.pBitFieldList != nil && pctxt.pBitFieldList.Len() > 0 {
		var pField = pctxt.pBitFieldList.Back().Value.(*DiagBitField)
		pField.closed = true
		if pField.numbits == 0 {
			pField.numbits = pctxt.BitOffset() - pField.bitOffset
		}
	}
}

func (buf *diagBinDumpBuffer) init(currBitOffset uint64) {
	buf.fmtBitBuffer = ""
	buf.fmtHexBuffer = ""
	buf.fmtAscBuffer = ""
	buf.lastBitBuffer = ""
	buf.repeatCount = 0

	//fmt.Printf("currBitOffset = %d\n", currBitOffset)
	fillerLen := currBitOffset % 32
	if fillerLen > 0 {
		for i := uint64(0); i < fillerLen; i++ {
			if i > 0 && i%8 == 0 {
				buf.fmtBitBuffer += " -"
				buf.fmtHexBuffer += "--"
				buf.fmtAscBuffer += "-"
			} else {
				buf.fmtBitBuffer += "-"
			}
		}
		if fillerLen%8 == 0 {
			buf.fmtBitBuffer += " "
			buf.fmtHexBuffer += "--"
			buf.fmtAscBuffer += "-"
		}
	}
}

func printLine(pbuf *diagBinDumpBuffer) {
	// If repeat count > 0, print a line indicating how many times
	// last line repeated
	if pbuf.repeatCount > 0 {
		fmt.Printf("last line repeated %d times..\n", pbuf.repeatCount)
	}
	fmt.Printf("%-35.35s    %-8.8s    %-4.4s\n",
		pbuf.fmtBitBuffer, pbuf.fmtHexBuffer, pbuf.fmtAscBuffer)
}

func fmtAndPrintBit(value int, pbuf *diagBinDumpBuffer) {
	if value > 0 {
		pbuf.fmtBitBuffer += "1"
		pbuf.lb |= pbuf.lbm
	} else if value < 0 {
		pbuf.fmtBitBuffer += "x"
	} else {
		pbuf.fmtBitBuffer += "0"
	}

	pbuf.lbm >>= 1

	if pbuf.lbm == 0 {
		if len(pbuf.fmtAscBuffer) < 4 {
			pbuf.fmtBitBuffer += " "
		}

		pbuf.fmtHexBuffer += fmt.Sprintf("%02x", pbuf.lb)

		if pbuf.lb >= ' ' && pbuf.lb <= '~' {
			pbuf.fmtAscBuffer += string(pbuf.lb)
		} else {
			pbuf.fmtAscBuffer += "."
		}

		pbuf.lb = 0
		pbuf.lbm = 0x80

		// If buffer is full, print to stdout

		if len(pbuf.fmtAscBuffer) >= 4 {
			// Check if this line if the same as the last. If it is, do not
			// print, incrent repeat count
			if pbuf.fmtBitBuffer == pbuf.lastBitBuffer {
				pbuf.repeatCount++
				pbuf.fmtBitBuffer = ""
				pbuf.fmtHexBuffer = ""
				pbuf.fmtAscBuffer = ""
			} else {
				printLine(pbuf)

				lastBitBuf := pbuf.fmtBitBuffer
				pbuf.init(0)
				pbuf.lastBitBuffer = lastBitBuf
			}
		}
	}
}

func getMaskAndIndex(bitOffset uint64) (uint64, uint8) {
	var relBitOffset uint64 = 7 - (bitOffset % 8)
	var mask uint8 = uint8(1 << relBitOffset)
	return uint64(bitOffset / 8), mask /* byte index, bit mask */
}

func dumpBits(dataBuffer []byte, currBitOffset uint64, numbits uint64,
	nextBitOffset uint64, pbuf *diagBinDumpBuffer) {

	// Get byte index and mask from field relative bit offset

	byteIndex, bitMask := getMaskAndIndex(currBitOffset)

	// Initialize output strings by setting characters to filler values
	// (hyphens) until we reach current bit offset

	pbuf.init(currBitOffset)

	// Loop to dump all bits in the field

	for i := uint64(0); i < numbits; i++ {
		bitValue := 0
		if (dataBuffer[byteIndex] & bitMask) != 0 {
			bitValue = 1
		}
		fmtAndPrintBit(bitValue, pbuf)

		bitMask >>= 1
		if bitMask == 0 {
			byteIndex++
			bitMask = 0x80
		}

		currBitOffset++
	}

	// Print unused bits between this and the next field

	for currBitOffset < nextBitOffset {
		fmtAndPrintBit(-1, pbuf)
		currBitOffset++
	}

	// Print anything that remains in the format buffer

	if len(pbuf.fmtBitBuffer) > 0 {

		// Calculate bit index

		bitBufLen := len(pbuf.fmtBitBuffer)

		// Fill to end of bit dump buffer with hyphens

		for i := bitBufLen; i < 35; i++ {
			if i == 8 || i == 17 || i == 26 {
				pbuf.fmtBitBuffer += " "
			} else {
				pbuf.fmtBitBuffer += "-"
			}
		}
		for i := len(pbuf.fmtHexBuffer); i < 8; i++ {
			pbuf.fmtHexBuffer += "-"
		}
		for i := len(pbuf.fmtAscBuffer); i < 4; i++ {
			pbuf.fmtAscBuffer += "-"
		}

		printLine(pbuf)
	}
}

func dumpField(dataBuffer []byte, pField *DiagBitField,
	varname string, nextBitOffset uint64, pBinDumpBuffer *diagBinDumpBuffer) {
	if pField.numbits == 0 {
		return
	}

	// Print field name

	fieldName := varname
	if pField.elemName != "" {
		fieldName += "."
		fieldName += pField.elemName
	}
	if pField.nameSuffix != "" {
		fieldName += " "
		fieldName += pField.nameSuffix
	}
	fmt.Printf("%s\n", fieldName)

	// Print bit offsets and counts

	fmt.Printf("bit offset: %d\tbit count: %d\tnext bit offset: %d\n",
		pField.bitOffset, pField.numbits, nextBitOffset)

	// Print bits

	dumpBits(dataBuffer, pField.bitOffset, pField.numbits,
		nextBitOffset, pBinDumpBuffer)

	fmt.Printf("\n")
}

func dumpFields(pBFList *list.List, varname string, level int,
	dataBuffer []byte, pLastPrinted *list.Element,
	pBinDumpBuffer *diagBinDumpBuffer) {

	pNode := pLastPrinted
	if pNode == nil {
		pNode = pBFList.Front()
	} else {
		pNode = pNode.Next()
	}
	pBinDumpBuffer.lb = 0
	pBinDumpBuffer.lbm = 0x80

	// If first field is a bit adjustment record, set value to use to
	// adjust bit offsets in all subsequent records

	var bitAdjustment uint64 = 0
	if pNode != nil {
		bitField := pNode.Value.(*DiagBitField)
		if bitField.elemName == "" && 0 == bitField.numbits {
			bitAdjustment = bitField.bitOffset
			pNode = pNode.Next()
		}
	}

	// Loop through the field list and dump fields

	for pNode != nil {
		var nextBitOffset uint64

		/* Determine the bit offset of the next field.  This is
		used in outputting 'x' bits for alignment bits.
		Since we skip zero-length fields in the dump, look past
		any such fields.
		*/
		for pNext := pNode.Next(); pNext != nil; pNext = pNext.Next() {
			pNextField := pNext.Value.(*DiagBitField)
			if pNextField.numbits != 0 {
				nextBitOffset = pNextField.bitOffset + bitAdjustment
				break
			}
		}
		pBitField := pNode.Value.(*DiagBitField)
		pBitField.bitOffset += bitAdjustment
		//fmt.Printf("bitField: %v\n", pBitField)

		dumpField(dataBuffer, pBitField, varname,
			nextBitOffset, pBinDumpBuffer)

		if pBitField.pOpenTypeFieldList != nil {
			byteIndex := pBitField.bitOffset / 8
			fmt.Printf("*** Open Type Data ***\n")

			// Make recursive call
			var binDumpBuffer2 diagBinDumpBuffer

			dumpFields(pBitField.pOpenTypeFieldList, varname,
				level+1, dataBuffer[byteIndex:], pNode,
				&binDumpBuffer2)

			fmt.Printf("***\n")
		}

		pNode = pNode.Next()
	}
}
