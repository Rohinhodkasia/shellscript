// PerEnc2sCompBinInt encompasses the rules to encode a 2's complement binary
// integer as specified in the X.691 standard.
func (pctxt *OSRTContext) PerEnc2sCompBinInt(value int64) error {
	var lbuf [8]byte
	var lb byte
	var i int

	temp := value

	for i = len(lbuf) - 1; i >= 0; i-- {
		lb = byte(temp % 256)
		temp /= 256
		if temp < 0 && lb != 0 {
			temp-- /* two's complement adjustment */
		}
		lbuf[i] = lb
		if temp == 0 || temp == -1 {
			break
		}
	}

	/* If the value is positive and bit 8 of the leading byte is set,    */
	/* copy a zero byte to the contents to signal a positive number..    */

	if value > 0 && (lb&0x80) != 0 {
		i--

	} else if value < 0 && ((lb & 0x80) == 0) {
		/* If the value is negative and bit 8 of the leading byte is clear,  */
		/* copy a -1 byte (0xFF) to the contents to signal a negative        */
		/* number..                                                          */

		i--
		if i >= 0 && i < len(lbuf) {
			lbuf[i] = 0xff
		}
	}

	/* Add the data to the encode buffer */

	return pctxt.EncBytes(lbuf[i:])
}
