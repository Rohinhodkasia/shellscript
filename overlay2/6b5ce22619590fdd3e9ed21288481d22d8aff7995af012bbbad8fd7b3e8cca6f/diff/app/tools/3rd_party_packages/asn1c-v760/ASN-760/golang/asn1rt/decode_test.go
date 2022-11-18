package asn1rt

import (
	"fmt"
	"math"
	"testing"
)

func TestDecBit(t *testing.T) {
	pctxt := new(OSRTContext)

	// Test decoding 1 bit
	b := []byte{0x80}
	pctxt.InitDecodeBytes(b)

	res, err := pctxt.DecBit()
	if err != nil {
		fmt.Println(err)
		t.Fail()
	}

	buf := &pctxt.buffer
	if buf.bitOffset != 7 {
		t.Errorf("buf.bitOffset = %d, should be 7", buf.bitOffset)
	}
	if res != true {
		t.Errorf("result = false, should be true")
	}
}

func TestPerDecBitsToUInt(t *testing.T) {
	pctxt := new(OSRTContext)

	// Test decoding 9 bit value
	b := []byte{0x80, 0xC0}
	pctxt.InitDecodeBytes(b)

	res, err := pctxt.PerDecBitsToUInt(9)
	if err != nil {
		fmt.Println(err)
		return
	}

	buf := &pctxt.buffer
	if buf.bitOffset != 7 {
		t.Errorf("buf.bitOffset = %d, should be 7", buf.bitOffset)
	}
	if res != 257 {
		t.Errorf("result = %d, should be 257", res)
	}

	// Decode final 7 bits
	res, err = pctxt.PerDecBitsToUInt(7)
	if err != nil {
		fmt.Println(err)
		return
	}

	if buf.bitOffset != 8 {
		t.Errorf("buf.bitOffset = %d, should be 8", buf.bitOffset)
	}
	if res != 64 {
		t.Errorf("result = %d, should be 64", res)
	}

	// Test decode unaligned at each end: 12 bits = 2 8 2
	encoding := []byte{0x02, 0x2b, 0x80}
	pctxt.InitDecodeBytes(encoding)

	res, err = pctxt.PerDecBitsToUInt(6)
	if err != nil {
		fmt.Println(err)
		t.Fail()
	}
	if buf.bitOffset != 2 {
		t.Errorf("buf.bitOffset = %d, should be 2", buf.bitOffset)
	}
	if res != 0 {
		t.Errorf("result = %d, should be 0", res)
	}

	res, err = pctxt.PerDecBitsToUInt(12)
	if err != nil {
		fmt.Println(err)
		t.Fail()
	}
	if buf.bitOffset != 6 {
		t.Errorf("buf.bitOffset = %d, should be 6", buf.bitOffset)
	}
	if res != 2222 {
		t.Errorf("result = %d, should be 2222", res)
	}
}

func TestPerDecUnconsInt(t *testing.T) {
	pctxt := new(OSRTContext)
	type IntTestData struct {
		value    int
		encoding []byte
	}
	intTestData := []IntTestData{
		IntTestData{
			value:    -1,
			encoding: []byte{0x01, 0xff},
		},
		IntTestData{
			value:    -2222,
			encoding: []byte{0x02, 0xf7, 0x52},
		},
	}

	// Test decoding each test data record
	for _, x := range intTestData {
		pctxt.InitDecodeBytes(x.encoding)

		ivalue, err := pctxt.PerDecUnconsInt()
		if err != nil {
			t.Error(err)
		}
		if ivalue != x.value {
			t.Errorf("result = %d, should be %d", ivalue, x.value)
		}
	}
}

func TestPerDecUnconsLen(t *testing.T) {
	pctxt := new(OSRTContext)

	// Test decoding 1 byte length
	b := []byte{0x07f}
	pctxt.InitDecodeBytes(b)

	res, frag, err := pctxt.PerDecUnconsLen()
	if err != nil {
		t.Error(err)
	}

	buf := &pctxt.buffer
	if buf.bitOffset != 8 {
		t.Errorf("buf.bitOffset = %d, should be 8", buf.bitOffset)
	}
	if res != 127 {
		t.Errorf("result = %d, should be 127", res)
	}
	if frag {
		t.Error("fragmented = true, expected false")
	}
}

// Test OBJECT IDENTIFIER decoding
func TestPerDecObjectIdentifier(t *testing.T) {
	pctxt := new(OSRTContext)
	var expectedVals = []uint64{1, 2, 840, 10005, 0, 9}

	b := []byte{7 /*length*/, 0x2a, 0x86, 0x48, 0xce, 0x15, 0x00, 0x09}
	pctxt.InitDecodeBytes(b)

	// Test decoding subid values
	subids := make([]uint64, 8)
	subids, err := pctxt.PerDecObjectIdentifier()
	if err != nil {
		t.Fatalf("OID encoding failed: %v", err)
		return
	}

	if len(subids) != 6 {
		t.Errorf("subids length = %d, should be 6", len(subids))
	}

	for i := range expectedVals {
		if subids[i] != expectedVals[i] {
			t.Errorf("subid[%d] result = %d, should be %d",
				i, subids[i], expectedVals[i])
		}
	}
}

//Test REAL decoding

/* realBase10Tests consists of encodings we will not produce from float64 values, but
must be able to decode.
*/
var realBase10Tests []RealTestVal = []RealTestVal{
	{1, []byte{0x06, 0x03, 0x31, 0x2E, 0x45, 0x2B, 0x30}},
	{-1, []byte{0x07, 0x03, 0x2D, 0x31, 0x2E, 0x45, 0x2B, 0x30}},
	{.1, []byte{0x06, 0x03, 0x31, 0x2E, 0x45, 0x2D, 0x31}},
	{14.7E67, []byte{0x08, 0x03, 0x31, 0x34, 0x37, 0x2E, 0x45, 0x36, 0x36}},
	{-14.7E-67, []byte{0x0A, 0x03, 0x2D, 0x31, 0x34, 0x37, 0x2E, 0x45, 0x2D, 0x36, 0x38}},
}

func TestPerDecReal(t *testing.T) {
	pctxt := new(OSRTContext)

	fulltests := make([]RealTestVal, len(realBase2Tests), len(realBase2Tests)+len(realBase10Tests))
	copy(fulltests, realBase2Tests)
	fulltests = append(fulltests, realBase10Tests...)

	for _, x := range fulltests {
		t.Run(fmt.Sprintf("value=%g", x.testval), func(t *testing.T) {
			pctxt.InitDecodeBytes(x.encoding)
			value, err := pctxt.PerDecReal()
			if err != nil {
				t.Fatalf("decoding failed: %v", err)
			}
			if x.testval != value && !(math.IsNaN(x.testval) && math.IsNaN(value)) {
				/* Values don't match and it is not the case that both are NaN */
				t.Errorf("result = %g, should be %g", value, x.testval)
			}
		})
	}
}

func TestPerDecReal10(t *testing.T) {
	pctxt := new(OSRTContext)

	for _, x := range real10Tests {
		t.Run(fmt.Sprintf("value=%s", x.nr3), func(t *testing.T) {
			pctxt.InitDecodeBytes(x.encoding)
			value, err := pctxt.PerDecReal10()
			if err != nil {
				t.Fatalf("decoding failed: %v", err)
			}
			if x.nr3 != value {
				/* Values don't match. */
				t.Errorf("result = %s, should be %s", value, x.nr3)
			}
		})
	}
}
