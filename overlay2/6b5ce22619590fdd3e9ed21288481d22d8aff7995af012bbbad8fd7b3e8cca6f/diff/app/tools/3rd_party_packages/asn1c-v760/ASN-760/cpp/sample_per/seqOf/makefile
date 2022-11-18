# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = seqOfTest.asn
HFILES = SeqOfTest.h $(PERCPPHFILES)

writer$(EXE) : writer$(OBJ) SeqOfTest$(OBJ) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) writer$(OBJ) SeqOfTest$(OBJ) $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) SeqOfTest$(OBJ) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) reader$(OBJ) SeqOfTest$(OBJ) $(LINKOPT) $(LPATHS) $(PSLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

SeqOfTest.cpp SeqOfTest.h : $(ASN1FILE) seqOf.cfg $(ASN1C)
	$(ASN1C) $(ASN1FILE) -c++ -per -trace -config seqOf.cfg \
	   -cfile SeqOfTest.cpp -strict-size

depends: SeqOfTest.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) SeqOfTest.cpp
	$(RM) SeqOfTest.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h


