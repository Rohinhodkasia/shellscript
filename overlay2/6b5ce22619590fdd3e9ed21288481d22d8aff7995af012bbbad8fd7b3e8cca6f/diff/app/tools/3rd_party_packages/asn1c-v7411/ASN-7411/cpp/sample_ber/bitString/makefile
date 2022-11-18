# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = $(RTSRCDIR)/ASN1CBitStr.h $(BERCPPHFILES)

LIBS = $(LLBER) $(LLRT) $(LLSYS)
OBJECTS =  BitString$(OBJ) BitStringEnc$(OBJ) BitStringDec$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(LIBS)

reader$(EXE) : reader$(OBJ) BitStringPrint$(OBJ) $(OBJECTS) \
$(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) BitStringPrint$(OBJ) $(OBJECTS) \
	   $(LINKOPT) $(LPATHS) $(LIBS)

writer$(OBJ) : writer.cpp BitString.h $(HFILES)
reader$(OBJ) : reader.cpp BitString.h $(HFILES)
BitStringPrint$(OBJ)  : BitStringPrint.cpp BitString.h $(HFILES)

BitString$(OBJ)  : BitString.cpp BitString.h $(HFILES)
BitStringEnc$(OBJ)  : BitStringEnc.cpp BitString.h $(HFILES)
BitStringDec$(OBJ)  : BitStringDec.cpp BitString.h $(HFILES)

BitString.cpp BitStringEnc.cpp BitStringDec.cpp BitStringPrint.cpp \
BitString.h : test.asn $(ASN1C)
	$(ASN1C) test.asn -c++ -ber -print -strict-size

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
