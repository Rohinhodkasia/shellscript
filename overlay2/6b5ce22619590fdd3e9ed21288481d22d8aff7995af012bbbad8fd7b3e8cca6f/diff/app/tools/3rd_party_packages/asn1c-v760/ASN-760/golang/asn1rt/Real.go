// Constants for REAL encoding and decoding
const (
	asn1KPlusInfinity  = 0x40
	asn1KMinusInfinity = 0x41
	asn1KNaN           = 0x42
	asn1KMinusZero     = 0x43
	realBinary         = 0x80
	realSign           = 0x40
	realExpLenMask     = 0x03
	realExpLen1        = 0x00
	realExpLen2        = 0x01
	realExpLen3        = 0x02
	realExpLenLong     = 0x03
	realFactorMask     = 0x0c
	realBaseMask       = 0x30
	realBase2          = 0x00
	realBase8          = 0x10
	realBase16         = 0x20
	realIso6093Mask    = 0x3f
)

// Type for REAL values
type Real float64

// Type for REAL values constrained to base 10
type RealBase10 string

