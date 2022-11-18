# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = $(PERCPPHFILES)
OBJECTS = ParamType$(OBJ) ParamTypeEnc$(OBJ) ParamTypeDec$(OBJ)

writer$(EXE) : writer$(OBJ) print$(OBJ) $(OBJECTS) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) writer$(OBJ) print$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) print$(OBJ) $(OBJECTS) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) reader$(OBJ) print$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(PSLIBS)

writer$(OBJ) : writer.cpp ParamType.h $(HFILES)
reader$(OBJ) : reader.cpp ParamType.h $(HFILES)
print$(OBJ)  : print.cpp  ParamType.h $(HFILES)
ParamType$(OBJ) : ParamType.cpp ParamType.h $(HFILES)
ParamTypeEnc$(OBJ) : ParamTypeEnc.cpp ParamType.h $(HFILES)
ParamTypeDec$(OBJ) : ParamTypeDec.cpp ParamType.h $(HFILES)

ParamType.cpp ParamTypeEnc.cpp ParamTypeDec.cpp ParamType.h print.cpp : param.asn
	$(ASN1C) param.asn -c++ -per -trace -print print.cpp

clean:
	$(RM) ParamType*.cpp
	$(RM) ParamType.h
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


