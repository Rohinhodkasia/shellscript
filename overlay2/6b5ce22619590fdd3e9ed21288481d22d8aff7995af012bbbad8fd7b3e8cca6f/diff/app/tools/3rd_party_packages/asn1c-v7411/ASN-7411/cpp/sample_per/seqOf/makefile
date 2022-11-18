# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = SeqOfTest.h $(PERCPPHFILES)

writer$(EXE) : writer$(OBJ) SeqOfTest$(OBJ) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) writer$(OBJ) SeqOfTest$(OBJ) $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) SeqOfTest$(OBJ) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) reader$(OBJ) SeqOfTest$(OBJ) $(LINKOPT) $(LPATHS) $(PSLIBS)

writer$(OBJ) : writer.cpp $(HFILES)
reader$(OBJ) : reader.cpp $(HFILES)
SeqOfTest$(OBJ) : SeqOfTest.cpp $(HFILES)

SeqOfTest.cpp SeqOfTest.h : seqOfTest.asn seqOf.cfg $(ASN1C)
	$(ASN1C) seqOfTest.asn -c++ -per -trace -config seqOf.cfg \
	   -cfile SeqOfTest.cpp -strict-size

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


