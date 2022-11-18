# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = $(PERCPPHFILES)
OBJECTS = T38$(OBJ) T38Enc$(OBJ) T38Dec$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) print$(OBJ) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) print$(OBJ) $(LINKOPT) $(LPATHS) $(PSLIBS)

writer$(OBJ) : writer.cpp T38.h $(HFILES)
reader$(OBJ) : reader.cpp T38.h $(HFILES)
print$(OBJ)  : print.cpp T38.h $(HFILES)

T38$(OBJ) : T38.cpp T38.h $(HFILES)
T38Enc$(OBJ) : T38Enc.cpp T38.h $(HFILES)
T38Dec$(OBJ) : T38Dec.cpp T38.h $(HFILES)

T38.cpp T38Enc.cpp T38Dec.cpp T38.h print.cpp : t38.asn $(ASN1C)
	$(ASN1C) t38.asn -c++ -per -trace -print print.cpp -strict-size -use-enum-types

clean :
	$(RM) T38*.cpp
	$(RM) T38.h
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


