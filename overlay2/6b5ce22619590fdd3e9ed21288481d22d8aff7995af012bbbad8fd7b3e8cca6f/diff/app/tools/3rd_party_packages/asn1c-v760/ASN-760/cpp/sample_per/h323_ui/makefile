# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = $(PERCPPHFILES)
LIBFILES = $(LIBDIR)/$(PERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
LINKLIBS = $(PSLIBS)

OBJECTS = \
H323-MESSAGES$(OBJ) \
H235-SECURITY-MESSAGES$(OBJ) \
H323-MESSAGESEnc$(OBJ) \
H235-SECURITY-MESSAGESEnc$(OBJ) \
H323-MESSAGESDec$(OBJ) \
H235-SECURITY-MESSAGESDec$(OBJ)

PRINT_OBJECTS = \
H323-MESSAGESPrint$(OBJ) \
H235-SECURITY-MESSAGESPrint$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBFILES)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(LINKLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(PRINT_OBJECTS) $(LIBFILES)
	$(LINK) reader$(OBJ) $(OBJECTS) $(PRINT_OBJECTS) $(LINKOPT) \
	   $(LPATHS) $(LINKLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

H323-MESSAGES.cpp H323-MESSAGESDec.cpp H323-MESSAGESEnc.cpp \
H323-MESSAGESPrint.cpp H323-MESSAGES.h : h225.asn h323.cfg $(ASN1C)
	$(ASN1C) h225.asn -c++ -per -trace -print -config h323.cfg -strict-size

H235-SECURITY-MESSAGES.cpp H235-SECURITY-MESSAGESEnc.cpp \
H235-SECURITY-MESSAGESDec.cpp H235-SECURITY-MESSAGESPrint.cpp \
H235-SECURITY-MESSAGES.h : h235.asn h323.cfg $(ASN1C)
	$(ASN1C) h235.asn -c++ -per -trace -print -config h323.cfg -strict-size

depends: H323-MESSAGES.cpp H235-SECURITY-MESSAGES.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) H*-MESSAGES*.cpp
	$(RM) H*-MESSAGES.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
