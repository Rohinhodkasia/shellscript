# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

OBJECTS = RFC1155-SMI$(OBJ) RFC1157-SNMP$(OBJ) RFC1213-MIB$(OBJ)
PRINT_OBJECTS = RFC1155-SMIPrint$(OBJ) RFC1157-SNMPPrint$(OBJ) \
RFC1213-MIBPrint$(OBJ)

HFILES  = $(BERCPPHFILES)

all : $(OBJECTS) writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(BSLIBS) 

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(PRINT_OBJECTS) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) $(PRINT_OBJECTS) $(LINKOPT) \
	   $(LPATHS) $(BSLIBS) 

writer$(OBJ) : writer.cpp RFC1155-SMI.h RFC1157-SNMP.h RFC1213-MIB.h $(HFILES)
reader$(OBJ) : reader.cpp RFC1155-SMI.h RFC1157-SNMP.h RFC1213-MIB.h $(HFILES)

RFC1155-SMI$(OBJ)  : RFC1155-SMI.cpp RFC1155-SMI.h $(HFILES) $(SYSTEM_INCLUDE)
RFC1155-SMIPrint$(OBJ) : RFC1155-SMIPrint.cpp RFC1155-SMI.h $(HFILES)

RFC1155-SMI.cpp RFC1155-SMIPrint.cpp RFC1155-SMI.h : RFC1155-SMI.asn
	$(ASN1C) RFC1155-SMI.asn -asnstd x208 -c++ -ber -print RFC1155-SMIPrint.cpp -cfile RFC1155-SMI.cpp -x64

RFC1157-SNMP$(OBJ) : RFC1157-SNMP.cpp RFC1157-SNMP.h $(HFILES)
RFC1157-SNMPPrint$(OBJ) : RFC1157-SNMPPrint.cpp RFC1157-SNMP.h $(HFILES)

RFC1157-SNMP.cpp RFC1157-SNMPPrint.cpp RFC1157-SNMP.h : RFC1157-SNMP.asn
	$(ASN1C) RFC1157-SNMP.asn -asnstd x208 -c++ -ber -print RFC1157-SNMPPrint.cpp -cfile RFC1157-SNMP.cpp -x64

RFC1213-MIB$(OBJ)  : RFC1213-MIB.cpp RFC1213-MIB.h $(HFILES)
RFC1213-MIBPrint$(OBJ) : RFC1213-MIBPrint.cpp RFC1213-MIB.h $(HFILES)

RFC1213-MIB.cpp RFC1213-MIBPrint.cpp RFC1213-MIB.h : RFC1213-MIB2.asn
	$(ASN1C) RFC1213-MIB2.asn -asnstd x208 -c++ -ber -print RFC1213-MIBPrint.cpp -cfile RFC1213-MIB.cpp -x64

clean:
	$(RM) RFC*.cpp
	$(RM) RFC*.h
	$(RM) *$(OBJ)
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM) *.log
	$(RM_MSVC_FILES)
	$(RM) *.dat
	$(RM) *~
	$(RM) rtkey.h
