# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = t38.asn
HFILES = $(PERCPPHFILES)
OBJECTS = T38$(OBJ) T38Enc$(OBJ) T38Dec$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) print$(OBJ) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) print$(OBJ) $(LINKOPT) $(LPATHS) $(PSLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

T38.cpp T38Enc.cpp T38Dec.cpp T38.h print.cpp : $(ASN1FILE) $(ASN1C)
	$(ASN1C) $(ASN1FILE) -c++ -per -trace -print print.cpp -strict-size -use-enum-types

depends: T38.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

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


