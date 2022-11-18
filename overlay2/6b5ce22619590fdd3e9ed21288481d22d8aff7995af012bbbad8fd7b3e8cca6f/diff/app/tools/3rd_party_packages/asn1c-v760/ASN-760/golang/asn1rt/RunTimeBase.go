// OSRTBuffer holds encoded message data.  For an encode operation,
// it is where the message being built is stored.  For decode, it
// holds a copy of the message that is being decoded.
type OSRTBuffer struct {
	data      []byte
	bitOffset uint64
	byteIndex uint64
	partial   byte
}

// OSRTContext is a container structure that holds all working
// variables involved in encoding or decoding a message.
type OSRTContext struct {
	buffer        OSRTBuffer
	elemNameStack list.List
	pBitFieldList *list.List
}

func (pctxt *OSRTContext) init() {
	pctxt.buffer.bitOffset = 8
	pctxt.buffer.byteIndex = 0
	pctxt.buffer.partial = 0
}

// AlignBuffer aligns the buffer on the next byte boundary
func (pctxt *OSRTContext) AlignBuffer() bool {
	if pctxt.buffer.bitOffset != 8 {
		pctxt.buffer.bitOffset = 8
		pctxt.buffer.byteIndex++
                return true
	}
        return false
}

// FlushBuffer writes the last partially encoded byte to the output stream.
func (pctxt *OSRTContext) FlushBuffer() {
	if pctxt.buffer.bitOffset != 8 {
		pctxt.buffer.bitOffset = 8
		pctxt.buffer.data =
			append(pctxt.buffer.data, pctxt.buffer.partial)
		pctxt.buffer.byteIndex++
		pctxt.buffer.partial = 0
	}
}

// InitEncode initializes the context buffer for encoding
func (pctxt *OSRTContext) InitEncode() {
	pctxt.init()
	pctxt.buffer.data = make([]byte, 0, 1024)
}

// InitDecodeBytes initializes the context buffer for decoding from a byte
// buffer
func (pctxt *OSRTContext) InitDecodeBytes(b []byte) {
	pctxt.init()
	pctxt.buffer.data = b
}

// ElemName returns the full dotted element name of the current element
func (pctxt *OSRTContext) ElemName() string {
	elemName := ""
	if pctxt.elemNameStack.Len() > 0 {
		for e := pctxt.elemNameStack.Front(); e != nil; e = e.Next() {
			elemName += e.Value.(string)
			if e != pctxt.elemNameStack.Back() {
				elemName += "."
			}
		}
	}
	return elemName
}

// BitOffset return the current bit offset
func (pctxt *OSRTContext) BitOffset() uint64 {
	return uint64((pctxt.buffer.byteIndex * 8) +
		(8 - pctxt.buffer.bitOffset))
}

// Buffer returns a copy of the context buffer
func (pctxt *OSRTContext) Buffer() OSRTBuffer {
	return pctxt.buffer
}

// BufferData returns a pointer to the message data buffer
func (pctxt *OSRTContext) BufferData() []byte {
	return pctxt.buffer.data
}

// BufferRemBytes returns a slice representing the number of bytes remaining
// in the message data buffer after a decode operation
func (pctxt *OSRTContext) BufferRemBytes() []byte {
	return pctxt.buffer.data[pctxt.buffer.byteIndex:]
}

// ErrInvalidEnum returns an invalid enumerated identifier error oject
func (pctxt *OSRTContext) ErrInvalidEnum(value uint64) error {
	return fmt.Errorf("Invalid enumerated identifier: field %s, value %d",
		pctxt.ElemName(), value)
}

// ErrNotPDUType returns an error indicating value passed into Marshal or
// Unmarshal function is not a known PDU type
func (pctxt *OSRTContext) ErrNotPDUType(value interface{}) error {
	switch v := value.(type) {
	default:
		return fmt.Errorf("Type %T is not a known PDU type", v)
	}
}

// ErrNotSupported returns a feature not supported error
func (pctxt *OSRTContext) ErrNotSupported(descr string) error {
	return fmt.Errorf("Feature not supported: %s, field %s",
		descr, pctxt.ElemName())
}

// ErrSizeConsVio returns a size constraint violation error oject
func (pctxt *OSRTContext) ErrSizeConsVio(len uint64) error {
	return pctxt.ErrWithParam("Size constraint violation", len)
}

// ErrValueConsVio return a value constraint violation error object
func (pctxt *OSRTContext) ErrValueConsVio(value interface{}) error {
	return pctxt.ErrWithParam("Value constraint violation", value)
}

// ErrWithNoParam returns an error object with the string description and 
// current element.
func (pctxt *OSRTContext) ErrWithNoParam(descr string) error {
	return fmt.Errorf("%s: field %s", descr,  pctxt.ElemName())
}

// ErrWithParam returns an error object with a single parameter of any type
func (pctxt *OSRTContext) ErrWithParam(descr string, value interface{}) error {
	var valstr string
	switch value.(type) {
	case string:
		valstr = value.(string)
		break
	case int:
		valstr = strconv.Itoa(value.(int))
		break
	case uint:
		valstr = strconv.FormatUint(uint64(value.(uint)), 10)
		break
	case uint64:
		valstr = strconv.FormatUint(value.(uint64), 10)
		break
	}
	return fmt.Errorf("%s: field %s, value %s", descr,  pctxt.ElemName(), valstr)
}

// PushArrayElemName is used to push an element name with array subscript 
// onto the eleent name stack
func (pctxt *OSRTContext) PushArrayElemName(elemName string, idx uint64) {
	name := fmt.Sprintf("%s[%d]", elemName, idx)
	pctxt.elemNameStack.PushBack(name)
}

// PushElemName is used to push an element name onto the eleent name stack
func (pctxt *OSRTContext) PushElemName(elemName string) {
	pctxt.elemNameStack.PushBack(elemName)
}

// PopElemName returns the top element name on the stack and removes the 
// top record
func (pctxt *OSRTContext) PopElemName() string {
	if pctxt.elemNameStack.Len() > 0 {
		element := pctxt.elemNameStack.Back()
		pctxt.elemNameStack.Remove(element)
		return element.Value.(string)
	}
	return ""
}

// PeekElemName returns the top name element name on the stack but leaves the 
// stack intact
func (pctxt *OSRTContext) PeekElemName() string {
	if pctxt.elemNameStack.Len() > 0 {
		element := pctxt.elemNameStack.Back()
		return element.Value.(string)
	}
	return ""
}

// ReplaceTopElemName replace the top element name on the stack with a new name
func (pctxt *OSRTContext) ReplaceTopElemName(elemName string) {
	pctxt.PopElemName()
	pctxt.elemNameStack.PushBack(elemName)
}

// SetBitOffset sets the context buffer byteIndex and bitOffset parameters to the
// given aggregate bit offset
func (pctxt *OSRTContext) SetBitOffset(offset uint64) error {
	pctxt.buffer.byteIndex = uint64(offset / 8)
	pctxt.buffer.bitOffset = uint64(8 - (offset % 8))
	byteIndex := pctxt.buffer.byteIndex
	if pctxt.buffer.bitOffset != 8 {
		byteIndex++
	}
	if byteIndex >= uint64(len(pctxt.buffer.data)) {
		return fmt.Errorf("Attempt made to set byte index past end of buffer")
	}
	return nil
}

// SetBuffer sets the context buffer to the given value
func (pctxt *OSRTContext) SetBuffer(buf OSRTBuffer) {
	pctxt.buffer = buf
}
