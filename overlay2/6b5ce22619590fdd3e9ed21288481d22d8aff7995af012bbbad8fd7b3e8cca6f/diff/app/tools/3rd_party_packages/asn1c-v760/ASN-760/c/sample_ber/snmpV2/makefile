# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

OBJECTS = SNMPv2-SMI$(OBJ) UDP-MIB$(OBJ) SNMPv2-PDU$(OBJ)
ENCOBJECTS = SNMPv2-SMIEnc$(OBJ) SNMPv2-PDUEnc$(OBJ)
DECOBJECTS = SNMPv2-SMIDec$(OBJ) SNMPv2-PDUDec$(OBJ)
PRINT_OBJECTS = SNMPv2-SMIPrint$(OBJ) SNMPv2-PDUPrint$(OBJ)

HFILES  = $(RTSRCDIR)/asn1type.h
LIBS    = $(LLBER)

all : $(OBJECTS) writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(OBJECTS)  $(ENCOBJECTS) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(ENCOBJECTS)  $(LINKOPT) $(LPATHS) $(BSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRINT_OBJECTS) \
$(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRINT_OBJECTS) $(LINKOPT) $(LPATHS) $(BSLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

SNMPv2-SMI.c SNMPv2-SMIEnc.c SNMPv2-SMIDec.c SNMPv2-SMIPrint.c \
SNMPv2-SMI.h : rfc2578-smiv2.asn $(ASN1C)
	$(ASN1C) rfc2578-smiv2.asn -asnstd x208 -c -ber -print -x64

SNMPv2-PDU.c SNMPv2-PDUEnc.c SNMPv2-PDUDec.c SNMPv2-PDUPrint.c \
SNMPv2-PDU.h : rfc1905-snmpv2.asn $(ASN1C)
	$(ASN1C) rfc1905-snmpv2.asn -asnstd x208 -c -ber -config snmpV2.cfg -print -x64

UDP-MIB.c UDP-MIB.h : udpMib.asn $(ASN1C)
	$(ASN1C) udpMib.asn -asnstd x208 -c -ber -config snmpV2.cfg -noencode -nodecode -x64

depends: SNMPv2-SMI.c SNMPv2-PDU.c UDP-MIB.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) SNMPv2*.c
	$(RM) SNMPv2*.h
	$(RM) UDP*.c
	$(RM) UDP*.h
	$(RM) *$(OBJ)
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM) *.log
	$(RM_MSVC_FILES)
	$(RM) *~
	$(RM) rtkey.h
	$(RM) message.dat
	$(RM) messagei.dat
