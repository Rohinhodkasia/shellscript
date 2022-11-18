# makefile to build the extChoice sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = extChoice.asn
HFILES = $(PERCPPHFILES)
OBJECTS =  ExtChoice$(OBJ) ExtChoiceEnc$(OBJ) ExtChoiceDec$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) print$(OBJ) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) print$(OBJ) $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) print$(OBJ) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) print$(OBJ) $(LINKOPT) $(LPATHS) $(PSLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

ExtChoice.cpp ExtChoiceEnc.cpp ExtChoiceDec.cpp \
ExtChoice.h print.cpp : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c++ -per -trace -print print.cpp

depends: ExtChoice.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

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
