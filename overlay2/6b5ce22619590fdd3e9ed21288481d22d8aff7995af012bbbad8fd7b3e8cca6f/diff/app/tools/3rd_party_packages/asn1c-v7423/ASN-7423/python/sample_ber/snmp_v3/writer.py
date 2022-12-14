#
# This file was generated by the Objective Systems ASN1C Compiler
# (https://obj-sys.com).  Version: 7.4.A, Date: 28-Dec-2019.
#


import argparse
import os
import sys
import traceback
from osyspyrt.asn1ber import Asn1BerEncodeBuffer
from osyspyrt.asn1univtype import null_value
from osyspyrt.util import hexdump
from SNMPv3MessageSyntax import *
from SNMPv2_PDU import VarBind, VarBind_aChoice, PDU, PDUs


class Writer:
    @staticmethod
    def main(filename, trace):
        # Dummy security data
        secdata = bytes([ 
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09])

        try:
            encbuf = Asn1BerEncodeBuffer()

            # populate PDU object
            varBind = VarBind()
            varBind.name = [1, 3, 6, 1, 2, 1, 1, 1, 0] # sysDescr + index 0
            varBind.aChoice = VarBind_aChoice()
            varBind.aChoice.unSpecified = null_value

            getReqPDU = PDU()
            getReqPDU.request_id = 1
            getReqPDU.error_status = "noError"
            getReqPDU.error_index = 0
            getReqPDU.variable_bindings = [varBind]

            pdu = PDUs()
            pdu.get_request = getReqPDU

            # Need to encode PDU separately to include as a scoped PDU in the
            # v3 message..
            enclen = pdu.ber_encode(encbuf)

            # Populate main message structure
            snmpMessage = SNMPv3Message()

            snmpMessage.msgVersion = 3
            snmpMessage.msgGlobalData = HeaderData()
            snmpMessage.msgGlobalData.msgID = 1
            snmpMessage.msgGlobalData.msgMaxSize = 1024
            snmpMessage.msgGlobalData.msgFlags = bytes([0xaa])
            snmpMessage.msgGlobalData.msgSecurityModel = 1
            snmpMessage.msgSecurityParameters = secdata

            scopedPDU = ScopedPDU()
            scopedPDU.contextEngineID = "aContextEngineID"
            scopedPDU.contextName = "aContextName"
            scopedPDU.data = encbuf.buffer()

            snmpMessage.msgData = ScopedPduData()
            snmpMessage.msgData.plaintext = scopedPDU

            if trace:
                print("The following record will be encoded:")
                snmpMessage.print_value("snmpMessage", 0)

            # Encode data and write to file
            snmpMessage.ber_encode(encbuf)
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
            sys.exit(-1)


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
