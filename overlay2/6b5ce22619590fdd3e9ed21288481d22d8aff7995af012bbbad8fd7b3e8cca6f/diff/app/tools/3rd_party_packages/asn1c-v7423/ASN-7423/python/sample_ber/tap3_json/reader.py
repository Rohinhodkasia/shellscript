#
# This file was generated by the Objective Systems ASN1C Compiler
# (https://obj-sys.com).  Version: 7.4.A, Date: 24-Dec-2019.
#


import argparse
import sys
import traceback
from osyspyrt.asn1json import Asn1JsonEncodeBuffer
from osyspyrt.asn1ber import Asn1BerDecodeBuffer
from TAP_0310 import *


class Reader:
    @staticmethod
    def main(in_filename, out_filename, trace):
        try:
            dataInterChange = DataInterChange()

            decbuf = Asn1BerDecodeBuffer.from_file(in_filename)
            dataInterChange.ber_decode(decbuf)

            if trace:
                dataInterChange.print_value("dataInterChange", 0)

            encbuf = Asn1JsonEncodeBuffer(filename=out_filename)
            dataInterChange.json_encode(encbuf)

        except Exception:
            print(traceback.format_exc())
            sys.exit(-1)


if __name__ == '__main__':
    my_in_filename = "message.dat"
    my_out_filename = "message2.json"
    mytrace = True

    # Process command line arguments
    parser = argparse.ArgumentParser()

    parser.add_argument('--notrace',
                        action='store_true',
                        help='Do not display trace info')

    parser.add_argument('-i', metavar='<filename>',
                        help='Read encoded msg from <in_filename>')

    args = parser.parse_args()

    if args.notrace:
        mytrace = False
    if args.i:
        my_in_filename = args.i

    Reader.main(my_in_filename, my_out_filename, mytrace)
