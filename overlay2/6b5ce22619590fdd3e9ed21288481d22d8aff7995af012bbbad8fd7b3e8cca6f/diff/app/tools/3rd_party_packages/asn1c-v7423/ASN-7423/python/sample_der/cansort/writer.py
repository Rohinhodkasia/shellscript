#
# This file was generated by the Objective Systems ASN1C Compiler
# (https://obj-sys.com).  Version: 7.4.A, Date: 21-Nov-2019.
#
import argparse
import os
import traceback
from osyspyrt.asn1ber import Asn1BerEncodeBuffer
from osyspyrt.util import hexdump
from SetOfInt import *


class Writer:
    @staticmethod
    def main(filename, trace):
        try:
            encbuf = Asn1BerEncodeBuffer()

            # populate setOfInt with test data
            setOfInt = [None]*5
            setOfInt[0] = 425
            setOfInt[1] = 2
            setOfInt[2] = 89327645
            setOfInt[3] = -24523
            setOfInt[4] = 0

            if trace:
                print("The following record will be encoded:")
                print("setOfInt = %r" % setOfInt)

            # Encode data and write to file
            SetOfInt.ber_encode(setOfInt, encbuf)
            f = open(filename, 'wb')
            f.write(encbuf.buffer())
            f.close()

            # Write hex dump to file
            hexfile = os.path.splitext(filename)[0] + '.hex'
            f = open(hexfile, 'w')
            f.write(hexdump(encbuf.buffer()))
            f.close()

            if trace:
                print(encbuf.bin_dump())

        except Exception:
            print(traceback.format_exc())


if __name__ == '__main__':
    myfilename = "message.dat"
    mytrace = True

    # Process command line arguments
    parser = argparse.ArgumentParser()

    parser.add_argument('--notrace',
                        action='store_true',
                        help='Do not display trace info')

    parser.add_argument('-o', metavar='<filename>',
                        help='Write encoded msg to <filename>')

    args = parser.parse_args()

    if args.notrace:
        mytrace = False
    if args.o:
        myfilename = args.o

    Writer.main(myfilename, mytrace)