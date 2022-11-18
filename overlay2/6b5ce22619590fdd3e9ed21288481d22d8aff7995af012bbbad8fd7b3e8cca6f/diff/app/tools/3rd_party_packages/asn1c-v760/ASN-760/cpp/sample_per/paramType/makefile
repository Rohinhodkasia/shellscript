# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = param.asn
HFILES = $(PERCPPHFILES)
OBJECTS = ParamType$(OBJ) ParamTypeEnc$(OBJ) ParamTypeDec$(OBJ)

writer$(EXE) : writer$(OBJ) print$(OBJ) $(OBJECTS) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) writer$(OBJ) print$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) print$(OBJ) $(OBJECTS) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) reader$(OBJ) print$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(PSLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

ParamType.cpp ParamTypeEnc.cpp ParamTypeDec.cpp ParamType.h \
print.cpp : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c++ -per -trace -print print.cpp

depends: ParamType.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

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


