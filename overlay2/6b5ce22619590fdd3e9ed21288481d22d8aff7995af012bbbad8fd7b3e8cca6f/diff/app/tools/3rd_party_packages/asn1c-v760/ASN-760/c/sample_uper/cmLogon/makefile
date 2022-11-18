# makefile to build the employee sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = CMMessageSetVersion1.h ACSE-1.h Asn1External.h $(PERHFILES)

OBJS = ACSE-1$(OBJ) Asn1External$(OBJ) ACSE-1Print$(OBJ) \
CMMessageSetVersion1Print$(OBJ) CMMessageSetVersion1$(OBJ)
ENCOBJS = CMMessageSetVersion1Enc$(OBJ) ACSE-1Enc$(OBJ)
DECOBJS = CMMessageSetVersion1Dec$(OBJ) ACSE-1Dec$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJS) $(ENCOBJS) $(PERLIBNAMES)
	$(LINK) writer$(OBJ) $(OBJS) $(ENCOBJS) $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJS) $(DECOBJS) $(PERLIBNAMES)
	$(LINK) reader$(OBJ) $(OBJS) $(DECOBJS) $(LINKOPT) $(LPATHS) $(PSLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

CMMessageSetVersion1.c \
CMMessageSetVersion1Enc.c CMMessageSetVersion1Dec.c \
CMMessageSetVersion1Print.c CMMessageSetVersion1.h : cm-v1.asn $(ASN1C)
	$(ASN1C) cm-v1.asn -c -uper -trace -print -strict-size -x64

ACSE-1.c ACSE-1Enc.c ACSE-1Dec.c ACSE-1Print.c ACSE-1.h : acse-1.asn $(ASN1C)
	$(ASN1C) acse-1.asn -c -uper -trace -print -strict-size -x64

depends: CMMessageSetVersion1.c ACSE-1.c Asn1External.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) A*.c
	$(RM) A*.h
	$(RM) CMMessageSetVersion1*.*
	$(RM) rtkey.h
	$(RM) message.dat
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.lib
	$(RM) *.ilk
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)

