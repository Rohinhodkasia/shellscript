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

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

H323-MESSAGES.cpp H323-MESSAGES.h : h225.asn h323.cfg $(ASN1C)
	$(ASN1C) h225.asn -c++ -per -events -notypes -config h323.cfg -strict-size -x64

H235-SECURITY-MESSAGES.cpp H235-SECURITY-MESSAGES.h : h235.asn h323.cfg $(ASN1C)
	$(ASN1C) h235.asn -c++ -per -events -notypes -config h323.cfg -strict-size -x64

depends: H323-MESSAGES.cpp H235-SECURITY-MESSAGES.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

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
