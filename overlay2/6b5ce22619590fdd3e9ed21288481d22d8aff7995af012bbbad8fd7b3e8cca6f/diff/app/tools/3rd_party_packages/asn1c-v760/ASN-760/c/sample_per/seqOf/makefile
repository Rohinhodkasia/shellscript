# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = seqOfTest.asn
HFILES = SeqOfTest.h $(PERHFILES)

writer$(EXE) : writer$(OBJ) SeqOfTest$(OBJ) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) writer$(OBJ) SeqOfTest$(OBJ) $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) SeqOfTest$(OBJ) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) reader$(OBJ) SeqOfTest$(OBJ) $(LINKOPT) $(LPATHS) $(PSLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

SeqOfTest.c SeqOfTest.h print.c : $(ASN1FILE) seqOf.cfg $(ASN1C)
	$(ASN1C) $(ASN1FILE) -c -per -trace -config seqOf.cfg \
	   -cfile SeqOfTest.c -strict-size

depends: SeqOfTest.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) SeqOfTest.c
	$(RM) SeqOfTest.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) rtkey.h


