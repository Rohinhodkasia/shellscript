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
	$(LINK) reader$(OBJ) $(OBJECTS) $(PRINT_OBJECTS) $(LINKOPT) $(LPATHS) $(BSLIBS)

writer$(OBJ) : writer.cpp AIN-Operation.h TCAPMessages.h $(HFILES)
reader$(OBJ) : reader.cpp AIN-Operation.h TCAPMessages.h $(HFILES)

AIN-Operation$(OBJ) : AIN-Operation.cpp AIN-Operation.h $(HFILES)
AIN-OperationEnc$(OBJ) : AIN-OperationEnc.cpp AIN-Operation.h $(HFILES)
AIN-OperationDec$(OBJ) : AIN-OperationDec.cpp AIN-Operation.h $(HFILES)
AIN-OperationPrint$(OBJ) : AIN-OperationPrint.cpp AIN-Operation.h $(HFILES)

AIN-Operation.cpp AIN-OperationEnc.cpp AIN-OperationDec.cpp \
AIN-Operation.h : ainop.asn $(ASN1C)
	$(ASN1C) ainop.asn -asnstd x208 -c++ -ber -print -x64

Asn1External$(OBJ) : Asn1External.cpp Asn1External.h $(HFILES)

TCAPMessages$(OBJ) : TCAPMessages.cpp TCAPMessages.h $(HFILES)
TCAPMessagesEnc$(OBJ) : TCAPMessagesEnc.cpp TCAPMessages.h $(HFILES)
TCAPMessagesDec$(OBJ) : TCAPMessagesDec.cpp TCAPMessages.h $(HFILES)
TCAPMessagesPrint$(OBJ) : TCAPMessagesPrint.cpp TCAPMessages.h $(HFILES)

TCAPMessages.cpp TCAPMessagesEnc.cpp TCAPMessagesDec.cpp TCAPMessages.h : \
tcap.asn $(ASN1C)
	$(ASN1C) tcap.asn -asnstd x208 -c++ -ber -print -x64

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
