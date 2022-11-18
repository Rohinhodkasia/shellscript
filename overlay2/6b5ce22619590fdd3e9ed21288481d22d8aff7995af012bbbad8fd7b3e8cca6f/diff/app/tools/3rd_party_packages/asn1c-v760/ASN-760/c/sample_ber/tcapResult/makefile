# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES  = $(RTSRCDIR)/asn1type.h

OBJECTS = \
AIN-Operation$(OBJ) \
TCAPMessages$(OBJ) \
Asn1External$(OBJ)

ENCOBJECTS = AIN-OperationEnc$(OBJ) \
TCAPMessagesEnc$(OBJ)

DECOBJECTS = AIN-OperationDec$(OBJ) \
TCAPMessagesDec$(OBJ)

PRINT_OBJECTS = AIN-OperationPrint$(OBJ) \
TCAPMessagesPrint$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(LINKOPT) $(LPATHS) $(BSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRINT_OBJECTS) \
$(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRINT_OBJECTS) $(LINKOPT) $(LPATHS) $(BSLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

AIN-Operation.c AIN-OperationEnc.c AIN-OperationDec.c AIN-Operation.h : \
ainop.asn $(ASN1C)
	$(ASN1C) ainop.asn -asnstd x208 -c -ber -print -x64

TCAPMessages.c TCAPMessagesEnc.c TCAPMessagesDec.c TCAPMessages.h : \
tcap.asn $(ASN1C)
	$(ASN1C) tcap.asn -asnstd x208 -c -ber -print -config tcap.cfg -x64

depends: AIN-Operation.c TCAPMessages.c Asn1External.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) AIN-Operation*
	$(RM) TCAPMessages*
	$(RM) Asn1Ext*
	$(RM) *$(OBJ)
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM_MSVC_FILES)
	$(RM) *~
	$(RM) rtkey.h
	$(RM) message.dat
	$(RM) messagei.dat
