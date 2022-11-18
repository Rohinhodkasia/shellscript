// Package asn1rt contains ASN.1 run-time functions. This source file 
// print functions.
package asn1rt

import (
	"encoding/asn1"
	"fmt"
)

const bitStringBytesInLine uint64 = 16

func bitStringDump (numbits uint64, data []byte) {
	if numbits == 0 || data == nil {
		return
	}

	numocts := numbits / 8

	if numocts > 8 {
		fmt.Println()
	}

	var i uint64
	var linebuf string
	var prevline string
	var repcount uint64
	for i = 0; i < numocts; i++ {
		if i != 0 && i % bitStringBytesInLine == 0 {
			if linebuf != prevline {
				if repcount > 0 {
					fmt.Printf("last line repeated %d times..\n", repcount)
					repcount = 0
				} else {
					fmt.Printf("%s\n", linebuf)
				}
				prevline = linebuf
			} else {
				repcount++
			}
			linebuf = ""
		} else if i % bitStringBytesInLine != 0 {
			linebuf += " "
		}

		linebuf += fmt.Sprintf ("0x%02X", data[i])
	}
	if repcount > 0 {
		fmt.Printf("last line repeated %d times..\n", repcount)
		repcount = 0
	}
	if len(linebuf) > 0 {
		fmt.Printf("%s", linebuf)
	}

	if i * 8 != numbits {
		// Print last partial byte as 1's and 0's
		buff := make([]byte, 8)
		tm := data[i]
		nmBits := numbits % 8

		var j uint64
		for j = 0; j < nmBits; j++ {
			buff[j] = byte(((tm >> 7) & 1) + '0')
			tm <<= 1
		}
		for ; j < 8; j++ {
			buff[j] = 'x'
		}

		if (len(linebuf) > 60) {
			fmt.Printf("\n%.8s", buff)
		} else if len(linebuf) > 0 {
			fmt.Printf(" %.8s", buff)
		} else {
			fmt.Printf("%.8s", buff)
		}
	}
	fmt.Println()
}

// PrintBitStr prints the content of a bit string to standard output
func PrintBitStr (name string, numbits uint64, data []byte) {
	fmt.Printf("%s.numbits = %d\n", name, numbits)
	fmt.Printf("%s.data = ", name)
	bitStringDump (numbits, data)
	fmt.Println()
}

// PrintAsn1BitString prints the contents of a value of type asn1.BitString
// to standard output
func PrintAsn1BitString(name string, pbitstr *asn1.BitString) {
	PrintBitStr(name, uint64(pbitstr.BitLength), pbitstr.Bytes)
}
