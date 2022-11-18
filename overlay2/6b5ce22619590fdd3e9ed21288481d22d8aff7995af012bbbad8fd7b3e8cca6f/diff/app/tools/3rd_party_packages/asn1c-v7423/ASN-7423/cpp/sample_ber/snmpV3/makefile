# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

OBJECTS = SNMPv3MessageSyntax$(OBJ) SNMPv2-PDU$(OBJ) \
SNMPv3MessageSyntaxEnc$(OBJ) SNMPv2-PDUEnc$(OBJ) \
SNMPv3MessageSyntaxDec$(OBJ) SNMPv2-PDUDec$(OBJ) 
PRINT_OBJECTS = SNMPv3MessageSyntaxPrint$(OBJ) SNMPv2-PDUPrint$(OBJ)

HFILES  = $(RTSRCDIR)/asn1type.h
SNMP_HFILES = SNMPv3MessageSyntax.h SNMPv2-PDU.h 

LIBS    = $(LLBER)

all : $(OBJECTS) writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(BSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(PRINT_OBJECTS) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) $(PRINT_OBJECTS) $(LINKOPT) \
	   $(LPATHS) $(BSLIBS)

writer$(OBJ) : writer.cpp $(SNMP_HFILES) $(HFILES)
reader$(OBJ) : reader.cpp $(SNMP_HFILES) $(HFILES)

SNMPv3MessageSyntax$(OBJ) : \
SNMPv3MessageSyntax.cpp SNMPv3MessageSyntax.h $(HFILES)
SNMPv3MessageSyntaxEnc$(OBJ) : \
SNMPv3MessageSyntaxEnc.cpp SNMPv3MessageSyntax.h $(HFILES)
SNMPv3MessageSyntaxDec$(OBJ) : \
SNMPv3MessageSyntaxDec.cpp SNMPv3MessageSyntax.h $(HFILES)
SNMPv3MessageSyntaxPrint$(OBJ) : \
SNMPv3MessageSyntaxPrint.cpp SNMPv3MessageSyntax.h $(HFILES)

SNMPv2-PDU$(OBJ) : SNMPv2-PDU.cpp SNMPv2-PDU.h $(HFILES)
SNMPv2-PDUEnc$(OBJ) : SNMPv2-PDUEnc.cpp SNMPv2-PDU.h $(HFILES)
SNMPv2-PDUDec$(OBJ) : SNMPv2-PDUDec.cpp SNMPv2-PDU.h $(HFILES)
SNMPv2-PDUPrint$(OBJ) : SNMPv2-PDUPrint.cpp SNMPv2-PDU.h $(HFILES)

SNMPv3MessageSyntax.cpp SNMPv3MessageSyntaxEnc.cpp SNMPv3MessageSyntaxDec.cpp \
SNMPv3MessageSyntax.h SNMPv3MessageSyntaxPrint.cpp \
SNMPv2-PDU.cpp SNMPv2-PDUEnc.cpp SNMPv2-PDUDec.cpp \
SNMPv2-PDUPrint.cpp SNMPv2-PDU.h : SNMPv3.asn
	$(ASN1C) SNMPv3.asn -asnstd x208 -c++ -ber -print -x64

clean:
	$(RM) SNMP*.cpp
	$(RM) SNMP*.h
	$(RM) *$(OBJ)
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM) *.log
	$(RM_MSVC_FILES)
	$(RM) *.dat
	$(RM) *~
	$(RM) rtkey.h
