#
# This file was generated by the Objective Systems ASN1C Compiler
# (https://obj-sys.com).  Version: 7.4.A, Date: 03-Nov-2019.
#


import argparse
import os
import traceback
from osyspyrt.asn1ber import Asn1BerEncodeBuffer
from osyspyrt.asn1univtype import Asn1BitString
from osyspyrt.ts32297 import *
from GPRSChargingDataTypes import *


class Writer:
    @staticmethod
    def set_ipv4address(value):
        ipaddr = IPAddress()
        ipaddr.iPTextRepresentedAddress = IPTextRepresentedAddress()
        ipaddr.iPTextRepresentedAddress.iPTextV4Address = value
        return ipaddr

    @staticmethod
    def main(filename, trace):
        try:
            encbuf = Asn1BerEncodeBuffer()

            # populate gPRSRecord with test data
            gPRSRecord = GPRSRecord()
            gPRSRecord.sGWRecord = SGWRecord()
            gPRSRecord.sGWRecord.recordType = 84
            gPRSRecord.sGWRecord.servedIMSI = "712345678901234"
            gPRSRecord.sGWRecord.s_GWAddress = Writer.set_ipv4address("1.2.3.4")
            gPRSRecord.sGWRecord.chargingID = 0
            gPRSRecord.sGWRecord.servingNodeAddress = []
            gPRSRecord.sGWRecord.servingNodeAddress.append(
                Writer.set_ipv4address("1.2.3.4"))
            gPRSRecord.sGWRecord.accessPointNameNI = "internet"
            gPRSRecord.sGWRecord.servedPDPPDNAddress = PDPAddress()
            gPRSRecord.sGWRecord.servedPDPPDNAddress.iPAddress = \
                Writer.set_ipv4address("1.2.3.4")
            gPRSRecord.sGWRecord.listOfTrafficVolumes = []
            cOfCC = ChangeOfCharCondition()
            cOfCC.dataVolumeGPRSUplink = 436019
            cOfCC.dataVolumeGPRSDownlink = 22620553
            cOfCC.changeCondition = "recordClosure"
            cOfCC.changeTime = bytes(
                [0x18, 0x05, 0x18, 0x00, 0x06, 0x07, 0x2B, 0x00, 0x00])
            cOfCC.ePCQoSInformation = EPCQoSInformation()
            cOfCC.ePCQoSInformation.qCI = 9
            gPRSRecord.sGWRecord.listOfTrafficVolumes.append(cOfCC)
            gPRSRecord.sGWRecord.recordOpeningTime = bytes(
                [0x18, 0x05, 0x18, 0x00, 0x02, 0x13, 0x2B, 0x00, 0x00])
            gPRSRecord.sGWRecord.duration = 234
            gPRSRecord.sGWRecord.causeForRecClosing = 0
            gPRSRecord.sGWRecord.servedMSISDN = bytes(
                [0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00])
            gPRSRecord.sGWRecord.chargingCharacteristics = bytes([0x00, 0x00])
            gPRSRecord.sGWRecord.servingNodePLMNIdentifier = bytes(
                [0x17, 0xF6, 0x91])
            gPRSRecord.sGWRecord.servedIMEISV = "8655920341303285"
            gPRSRecord.sGWRecord.rATType = 6
            gPRSRecord.sGWRecord.userLocationInformation = bytes([
                0x18, 0x17, 0xF6, 0xDD, 0xDD, 0xEE, 0xEE, 0xFF,
                0xFF, 0x00, 0x00, 0x00, 0x00])
            gPRSRecord.sGWRecord.servingNodeType = ['mME']

            # Encode record
            total_len = cdrlen = gPRSRecord.ber_encode(encbuf)

            # Populate CDR header and encode
            cdrhdr = TS32297CDRHeader()
            cdrhdr.cdr_length = cdrlen
            cdrhdr.rel_vers_id = TS32297RelVersId()
            cdrhdr.rel_vers_id.rel_id = 11
            cdrhdr.rel_vers_id.vers_id = 6
            cdrhdr.data_record_format = 1
            cdrhdr.ts_number = 7

            total_len += cdrhdr.encode(encbuf)

            # Populate 2nd GPRSRecord with test data.  Since encoding is done
            # back-to-front, this will appear as the first record in the
            # file.
            gPRSRecord = GPRSRecord()
            gPRSRecord.sGWRecord = SGWRecord()
            gPRSRecord.sGWRecord.recordType = 84
            gPRSRecord.sGWRecord.servedIMSI = "712345678900000"
            gPRSRecord.sGWRecord.s_GWAddress = Writer.set_ipv4address("1.2.3.4")
            gPRSRecord.sGWRecord.chargingID = 0
            gPRSRecord.sGWRecord.servingNodeAddress = []
            gPRSRecord.sGWRecord.servingNodeAddress.append(
                Writer.set_ipv4address("1.2.3.4"))
            gPRSRecord.sGWRecord.accessPointNameNI = "ims"
            gPRSRecord.sGWRecord.servedPDPPDNAddress = PDPAddress()
            gPRSRecord.sGWRecord.servedPDPPDNAddress.iPAddress = \
                Writer.set_ipv4address("1.2.3.4")
            gPRSRecord.sGWRecord.listOfTrafficVolumes = []
            cOfCC = ChangeOfCharCondition()
            cOfCC.dataVolumeGPRSUplink = 6403
            cOfCC.dataVolumeGPRSDownlink = 6402
            cOfCC.changeCondition = "recordClosure"
            cOfCC.changeTime = bytes(
                [0x18, 0x05, 0x18, 0x00, 0x06, 0x07, 0x2B, 0x00, 0x00])
            cOfCC.ePCQoSInformation = EPCQoSInformation()
            cOfCC.ePCQoSInformation.qCI = 5
            gPRSRecord.sGWRecord.listOfTrafficVolumes.append(cOfCC)
            gPRSRecord.sGWRecord.recordOpeningTime = bytes(
                [0x18, 0x05, 0x18, 0x00, 0x02, 0x13, 0x2B, 0x00, 0x00])
            gPRSRecord.sGWRecord.duration = 234
            gPRSRecord.sGWRecord.causeForRecClosing = 0
            gPRSRecord.sGWRecord.servedMSISDN = bytes(
                [0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00])
            gPRSRecord.sGWRecord.chargingCharacteristics = bytes([0x00, 0x00])
            gPRSRecord.sGWRecord.servingNodePLMNIdentifier = bytes(
                [0x11, 0x22, 0x33])
            gPRSRecord.sGWRecord.servedIMEISV = "8600000000000000"
            gPRSRecord.sGWRecord.rATType = 6
            gPRSRecord.sGWRecord.userLocationInformation = bytes([
                0x18, 0x1A, 0xAB, 0xBC, 0xCD, 0xDE, 0xEF, 0xF0,
                0x00, 0x00, 0x00, 0x00, 0x00])
            gPRSRecord.sGWRecord.servingNodeType = ['mME']

            # Encode record
            cdrlen = gPRSRecord.ber_encode(encbuf)
            total_len += cdrlen

            # Populate CDR header and encode
            cdrhdr = TS32297CDRHeader()
            cdrhdr.cdr_length = cdrlen
            cdrhdr.rel_vers_id = TS32297RelVersId()
            cdrhdr.rel_vers_id.rel_id = 11
            cdrhdr.rel_vers_id.vers_id = 6
            cdrhdr.data_record_format = 1
            cdrhdr.ts_number = 7

            total_len += cdrhdr.encode(encbuf)

            # Populate CDR file header and encode
            # File and header length will be computed on encode
            cdrfilehdr = TS32297CDRFileHeader()
            cdrfilehdr.header_length = 0
            cdrfilehdr.high_rel_vers_id = TS32297RelVersId()
            cdrfilehdr.high_rel_vers_id.rel_id = 11
            cdrfilehdr.high_rel_vers_id.vers_id = 6
            cdrfilehdr.low_rel_vers_id = TS32297RelVersId()
            cdrfilehdr.low_rel_vers_id.rel_id = 11
            cdrfilehdr.low_rel_vers_id.vers_id = 6
            cdrfilehdr.open_timestamp = \
                TS32297Timestamp(5, 18, 0, 0, 0, 0, True)
            cdrfilehdr.last_append_timestamp = \
                TS32297Timestamp(5, 18, 0, 0, 0, 0, True)
            cdrfilehdr.cdr_count = 2
            cdrfilehdr.file_sequence_number = 1321
            cdrfilehdr.file_closure_reason = "normal"
            cdrfilehdr.ip_address = TS32297IpAddress()
            cdrfilehdr.ip_address.parse(
                "0000:0000:0000:0000:0000:0000:7f00:0001")
            cdrfilehdr.lost_cdr_indicator = 0

            cdrfilehdr.encode(encbuf, total_len)

            # write encoded data out to a file
            f = open(filename, 'wb')
            f.write(encbuf.buffer())
            f.close()

            # Write hex dump to file
            hexfile = os.path.splitext(filename)[0] + '.hex'
            f = open(hexfile, 'w')
            f.write(hexdump(encbuf.buffer()))
            f.close()

        except Exception:
            print(traceback.format_exc())


if __name__ == '__main__':
    myfilename = "test2.cdr"
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
