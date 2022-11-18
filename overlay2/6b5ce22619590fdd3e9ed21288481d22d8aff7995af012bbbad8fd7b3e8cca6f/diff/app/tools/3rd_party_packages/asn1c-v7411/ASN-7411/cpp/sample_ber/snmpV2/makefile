# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

OBJECTS = SNMPv2-SMI$(OBJ) SNMPv2-PDU$(OBJ) UDP-MIB$(OBJ)
PRINT_OBJECTS = SNMPv2-SMIPrint$(OBJ) SNMPv2-PDUPrint$(OBJ)

HFILES  = $(RTSRCDIR)/asn1type.h
LIBS    = $(LLBER)

all : $(OBJECTS) writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(BSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(PRINT_OBJECTS) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) $(PRINT_OBJECTS) $(LINKOPT) $(LPATHS) $(BSLIBS)

writer$(OBJ) : writer.cpp SNMPv2-SMI.h SNMPv2-PDU.h UDP-MIB.h $(HFILES)
reader$(OBJ) : reader.cpp SNMPv2-SMI.h SNMPv2-PDU.h UDP-MIB.h $(HFILES)

SNMPv2-SMI$(OBJ) : SNMPv2-SMI.cpp SNMPv2-SMI.h $(HFILES)

SNMPv2-SMIPrint$(OBJ) : SNMPv2-SMIPrint.cpp SNMPv2-SMI.h $(HFILES)

SNMPv2-SMI.cpp SNMPv2-SMIPrint.cpp SNMPv2-SMI.h : rfc2578-smiv2.asn
	$(ASN1C) rfc2578-smiv2.asn -asnstd x208 -c++ -ber \
	-print SNMPv2-SMIPrint.cpp -cfile SNMPv2-SMI.cpp -x64

SNMPv2-PDU$(OBJ) : SNMPv2-PDU.cpp SNMPv2-PDU.h $(HFILES)

SNMPv2-PDUPrint$(OBJ) : SNMPv2-PDUPrint.cpp SNMPv2-PDU.h $(HFILES)

SNMPv2-PDU.cpp SNMPv2-PDUPrint.cpp SNMPv2-PDU.h : rfc1905-snmpv2.asn
	$(ASN1C) rfc1905-snmpv2.asn -asnstd x208 -c++ -ber -config snmpV2.cfg \
	-print SNMPv2-PDUPrint.cpp -cfile SNMPv2-PDU.cpp -x64

UDP-MIB$(OBJ) : UDP-MIB.cpp UDP-MIB.h $(HFILES)

UDP-MIB.cpp UDP-MIB.h : udpMib.asn
	$(ASN1C) udpMib.asn -asnstd x208 -c++ -ber -config snmpV2.cfg \
	   -noencode -nodecode -x64

clean:
	$(RM) SNMPv2*.cpp
	$(RM) SNMPv2*.h
	$(RM) UDP*.cpp
	$(RM) UDP*.h
	$(RM) *$(OBJ)
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM) *.log
	$(RM_MSVC_FILES)
	$(RM) *.dat
	$(RM) *~
	$(RM) rtkey.h
