# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

OBJECTS = SNMPv3MessageSyntax$(OBJ) SNMPv2-PDU$(OBJ) 
ENCOBJECTS = SNMPv3MessageSyntaxEnc$(OBJ) SNMPv2-PDUEnc$(OBJ) 
DECOBJECTS = SNMPv3MessageSyntaxDec$(OBJ) SNMPv2-PDUDec$(OBJ) 
PRINT_OBJECTS = SNMPv3MessageSyntaxPrint$(OBJ) SNMPv2-PDUPrint$(OBJ)

HFILES  = $(RTSRCDIR)/asn1type.h
SNMP_HFILES = SNMPv3MessageSyntax.h SNMPv2-PDU.h 

LIBS    = $(LLBER)

all : writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(LINKOPT) $(LPATHS) $(BSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRINT_OBJECTS) \
$(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRINT_OBJECTS) $(LINKOPT) $(LPATHS) $(BSLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

SNMPv3MessageSyntax.c \
SNMPv3MessageSyntaxEnc.c SNMPv3MessageSyntaxDec.c \
SNMPv3MessageSyntax.h SNMPv3MessageSyntaxPrint.c \
SNMPv2-PDU.c SNMPv2-PDUEnc.c SNMPv2-PDUDec.c \
SNMPv2-PDUPrint.c SNMPv2-PDU.h : SNMPv3.asn $(ASN1C)
	$(ASN1C) SNMPv3.asn -asnstd x208 -c -ber -print -x64

depends: SNMPv3MessageSyntax.c SNMPv2-PDU.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) SNMP*.c
	$(RM) SNMP*.h
	$(RM) *$(OBJ)
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM) *.log
	$(RM_MSVC_FILES)
	$(RM) *~
	$(RM) rtkey.h
	$(RM) message.dat
	$(RM) messagei.dat
