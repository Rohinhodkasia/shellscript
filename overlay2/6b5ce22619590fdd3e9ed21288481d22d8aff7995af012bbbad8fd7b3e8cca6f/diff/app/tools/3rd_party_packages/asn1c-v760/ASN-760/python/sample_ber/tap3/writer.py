#
# This file was generated by the Objective Systems ASN1C Compiler
# (https://obj-sys.com).  Version: 7.4.A, Date: 15-Nov-2019.
#


import argparse
import traceback
from osyspyrt.asn1ber import Asn1BerEncodeBuffer
from osyspyrt.util import hexdump
from TAP_0312 import *


class Writer:
    @staticmethod
    def main(filename, trace):
        try:
            encbuf = Asn1BerEncodeBuffer()

            dataInterChange = DataInterChange()

            # populate dataInterChange with test data

            dataInterChange.notification = Notification()
            dataInterChange.notification.sender = "00101"
            dataInterChange.notification.recipient = "00101"
            dataInterChange.notification.fileSequenceNumber = "77223"
            dataInterChange.notification.fileCreationTimeStamp = \
                FileCreationTimeStamp()
            dataInterChange.notification.fileCreationTimeStamp.localTimeStamp \
                = "19032200153000"
            dataInterChange.notification.fileCreationTimeStamp.utcTimeOffset \
                = "+0400"
            
            dataInterChange.notification.fileAvailableTimeStamp = \
                FileAvailableTimeStamp()
            dataInterChange.notification.fileAvailableTimeStamp.\
                localTimeStamp = "19041500222500"
            dataInterChange.notification.fileAvailableTimeStamp.\
                utcTimeOffset = "+0400"
            
            dataInterChange.notification.specificationVersionNumber = 3
            dataInterChange.notification.releaseVersionNumber = 12
            dataInterChange.notification.operatorSpecInformation = []
            dataInterChange.notification.operatorSpecInformation.append(
                "OperatorSpecInformation")

            if trace:
                print("The following record will be encoded:")
                dataInterChange.print_value("dataInterChange", 0)

            # Encode data and write to file
            dataInterChange.ber_encode(encbuf)
            f = open(filename, 'wb')
            f.write(encbuf.buffer())
            f.close()

            # write hex dump of encoded data to a file
            f = open('message.hex', 'w')
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
