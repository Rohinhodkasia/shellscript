# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = test.asn
HFILES = $(RTSRCDIR)/ASN1CBitStr.h $(BERCPPHFILES)

LIBS = $(LLBER) $(LLRT) $(LLSYS)
OBJECTS =  BitString$(OBJ) BitStringEnc$(OBJ) BitStringDec$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(LIBS)

reader$(EXE) : reader$(OBJ) BitStringPrint$(OBJ) $(OBJECTS) \
$(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) BitStringPrint$(OBJ) $(OBJECTS) \
	   $(LINKOPT) $(LPATHS) $(LIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

BitString.cpp BitStringEnc.cpp BitStringDec.cpp BitStringPrint.cpp \
BitString.h : $(ASN1FILE) $(ASN1C)
	$(ASN1C) $(ASN1FILE) -c++ -ber -print -strict-size

depends: BitString.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) BitString*.cpp
	$(RM) BitString.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
