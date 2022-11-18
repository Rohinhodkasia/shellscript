# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : reader$(EXE)

HFILES = $(PERCPPHFILES) printHandler.h
LIBFILES = $(LIBDIR)/$(PERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
LINKLIBS = $(PSLIBS)

OBJECTS = \
H323-MESSAGES$(OBJ) \
H235-SECURITY-MESSAGES$(OBJ) \
printHandler$(OBJ)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(LIBFILES)
	$(LINK) reader$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(LINKLIBS)

reader$(OBJ) : reader.cpp H323-MESSAGES.h H235-SECURITY-MESSAGES.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) reader.cpp

printHandler$(OBJ) : printHandler.cpp $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) printHandler.cpp

H323-MESSAGES$(OBJ) : H323-MESSAGES.cpp H323-MESSAGES.h \
H235-SECURITY-MESSAGES.h $(HFILES)

H235-SECURITY-MESSAGES$(OBJ) : \
H235-SECURITY-MESSAGES.cpp H235-SECURITY-MESSAGES.h $(HFILES)

H323-MESSAGES.cpp H323-MESSAGES.h : h225.asn h323.cfg $(ASN1C)
	$(ASN1C) h225.asn -c++ -per -events -notypes -config h323.cfg -strict-size -x64

H235-SECURITY-MESSAGES.cpp H235-SECURITY-MESSAGES.h : h235.asn h323.cfg $(ASN1C)
	$(ASN1C) h235.asn -c++ -per -events -notypes -config h323.cfg -strict-size -x64

clean :
	$(RM) H*-MESSAGES*.cpp
	$(RM) H*-MESSAGES.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.lib
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) rtkey.h
