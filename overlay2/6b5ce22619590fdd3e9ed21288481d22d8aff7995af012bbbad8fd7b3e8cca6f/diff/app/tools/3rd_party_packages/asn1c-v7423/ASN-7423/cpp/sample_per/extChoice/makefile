# makefile to build the extChoice sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = $(PERCPPHFILES)
OBJECTS =  ExtChoice$(OBJ) ExtChoiceEnc$(OBJ) ExtChoiceDec$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) print$(OBJ) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) print$(OBJ) $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) print$(OBJ) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) print$(OBJ) $(LINKOPT) $(LPATHS) $(PSLIBS)

writer$(OBJ) : writer.cpp ExtChoice.h $(HFILES)
reader$(OBJ) : reader.cpp ExtChoice.h $(HFILES)
print$(OBJ)  : print.cpp  $(HFILES)
ExtChoice$(OBJ) : ExtChoice.cpp $(HFILES)
ExtChoiceDec$(OBJ) : ExtChoiceDec.cpp $(HFILES)
ExtChoiceEnc$(OBJ) : ExtChoiceEnc.cpp $(HFILES)

ExtChoice.cpp ExtChoiceEnc.cpp ExtChoiceDec.cpp \
ExtChoice.h print.cpp : extChoice.asn
	$(ASN1C) extChoice.asn -c++ -per -trace -print print.cpp

clean :
	$(RM) ExtChoice*.cpp
	$(RM) ExtChoice.h
	$(RM) print.cpp
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
