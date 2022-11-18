# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = $(PERCPPHFILES)
OBJECTS = InfoObject$(OBJ) InfoObjectEnc$(OBJ) InfoObjectDec$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) print$(OBJ) \
$(LIBDIR)/$(PERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) print$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) print$(OBJ) \
$(LIBDIR)/$(PERLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) print$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(PSLIBS)

writer$(OBJ) : writer.cpp InfoObject.h $(HFILES)
reader$(OBJ) : reader.cpp InfoObject.h $(HFILES)
print$(OBJ)  : print.cpp  $(HFILES)
InfoObject$(OBJ) : InfoObject.cpp $(HFILES)
InfoObjectEnc$(OBJ) : InfoObjectEnc.cpp $(HFILES)
InfoObjectDec$(OBJ) : InfoObjectDec.cpp $(HFILES)

InfoObject.cpp InfoObjectDec.cpp InfoObjectEnc.cpp \
InfoObject.h print.cpp : infoObject.asn
	$(ASN1C) infoObject.asn -c++ -per -trace -print print.cpp

clean :
	$(RM) InfoObject*.cpp
	$(RM) InfoObject.h
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
