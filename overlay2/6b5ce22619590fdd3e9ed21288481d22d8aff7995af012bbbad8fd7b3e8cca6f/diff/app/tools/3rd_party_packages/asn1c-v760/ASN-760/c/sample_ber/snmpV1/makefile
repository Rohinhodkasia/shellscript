# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

OBJECTS = RFC1155-SMI$(OBJ) RFC1157-SNMP$(OBJ) RFC1213-MIB$(OBJ)
ENCOBJECTS = RFC1155-SMIEnc$(OBJ) RFC1157-SNMPEnc$(OBJ) RFC1213-MIBEnc$(OBJ)
DECOBJECTS = RFC1155-SMIDec$(OBJ) RFC1157-SNMPDec$(OBJ) RFC1213-MIBDec$(OBJ)
PRINT_OBJECTS = RFC1155Print$(OBJ) RFC1157Print$(OBJ) RFC1213Print$(OBJ)

HFILES  = $(RTSRCDIR)/asn1type.h
LIBS    = $(LLBER)

all : $(OBJECTS) writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(LINKOPT) $(LPATHS) $(BSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRINT_OBJECTS) \
$(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRINT_OBJECTS) $(LINKOPT) $(LPATHS) $(BSLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

RFC1155-SMI.c RFC1155-SMIEnc.c RFC1155-SMIDec.c RFC1155Print.c \
RFC1155-SMI.h : RFC1155-SMI.asn $(ASN1C)
	$(ASN1C) RFC1155-SMI.asn -asnstd x208 -c -ber -print RFC1155Print.c -x64

RFC1157-SNMP.c RFC1157-SNMPEnc.c RFC1157-SNMPDec.c RFC1157Print.c \
RFC1157-SNMP.h : RFC1157-SNMP.asn $(ASN1C)
	$(ASN1C) RFC1157-SNMP.asn -asnstd x208 -c -ber -print RFC1157Print.c -x64

RFC1213-MIB.c RFC1213-MIBEnc.c RFC1213-MIBDec.c RFC1213Print.c \
RFC1213-MIB.h : RFC1213-MIB2.asn $(ASN1C)
	$(ASN1C) RFC1213-MIB2.asn -asnstd x208 -c -ber -print RFC1213Print.c -x64

depends: RFC1155-SMI.c RFC1157-SNMP.c RFC1213-MIB.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) RFC*.c
	$(RM) RFC*.h
	$(RM) *$(OBJ)
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM) *.log
	$(RM_MSVC_FILES)
	$(RM) *~
	$(RM) rtkey.h
	$(RM) message.dat
	$(RM) messagei.dat
