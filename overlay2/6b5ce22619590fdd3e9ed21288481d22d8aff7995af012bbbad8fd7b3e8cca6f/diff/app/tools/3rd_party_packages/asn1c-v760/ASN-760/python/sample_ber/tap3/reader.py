#
# This file was generated by the Objective Systems ASN1C Compiler
# (https://obj-sys.com).  Version: 7.4.A, Date: 15-Nov-2019.
#


import argparse
import traceback
from osyspyrt.asn1ber import Asn1BerDecodeBuffer
from TAP_0312 import *


class Reader:
    @staticmethod
    def main(filename, trace):
        try:
            decbuf = Asn1BerDecodeBuffer.from_file(filename)
            dataInterChange = DataInterChange()

            dataInterChange.ber_decode(decbuf)

            if trace:
                dataInterChange.print_value("dataInterChange", 0)

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

    parser.add_argument('-i', metavar='<filename>',
                        help='Read encoded msg from <filename>')

    args = parser.parse_args()

    if args.notrace:
        mytrace = False
    if args.i:
        myfilename = args.i

    Reader.main(myfilename, mytrace)
