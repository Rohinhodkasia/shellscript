# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES  = $(BERCPPHFILES)
OBJECTS = AIN-Operation$(OBJ) TCAPMessages$(OBJ) Asn1External$(OBJ) \
AIN-OperationEnc$(OBJ) TCAPMessagesEnc$(OBJ) \
AIN-OperationDec$(OBJ) TCAPMessagesDec$(OBJ)
PRINT_OBJECTS = AIN-OperationPrint$(OBJ) TCAPMessagesPrint$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(BSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(PRINT_OBJECTS) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) $(PRINT_OBJECTS) $(LINKOPT) $(LPATHS) \
	    $(BSLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

AIN-Operation.cpp AIN-OperationEnc.cpp AIN-OperationDec.cpp \
AIN-Operation.h : ainop.asn $(ASN1C)
	$(ASN1C) ainop.asn -asnstd x208 -c++ -ber -print -x64

TCAPMessages.cpp TCAPMessagesEnc.cpp TCAPMessagesDec.cpp TCAPMessages.h : \
tcap.asn $(ASN1C)
	$(ASN1C) tcap.asn -asnstd x208 -c++ -ber -print -x64

depends: TCAPMessages.cpp AIN-Operation.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) AIN-Operation*
	$(RM) TCAPMessages*
	$(RM) Asn1Ext*
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) *.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) rtkey.h
