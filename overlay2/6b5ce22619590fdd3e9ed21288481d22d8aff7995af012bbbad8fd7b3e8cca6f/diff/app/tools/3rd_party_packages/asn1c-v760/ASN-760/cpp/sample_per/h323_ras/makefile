# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = H323RAS.asn
HFILES = $(PERCPPHFILES)
LIBFILES = $(LIBDIR)/$(PERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
LINKLIBS = $(PSLIBS)
OBJECTS = H323RAS$(OBJ) H323RASDec$(OBJ) H323RASEnc$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBFILES)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(LINKLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) H323RASPrint$(OBJ) $(LIBFILES)
	$(LINK) reader$(OBJ) $(OBJECTS) H323RASPrint$(OBJ) $(LINKOPT) $(LPATHS) \
	    $(LINKLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

H323RAS.cpp H323RASEnc.cpp H323RASDec.cpp \
H323RAS.h H323RASPrint.cpp : $(ASN1FILE) $(ASN1C)
	$(ASN1C) $(ASN1FILE) -per -c++ -print -trace -strict-size

depends: H323RAS.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) H323RAS*.cpp
	$(RM) H323RAS.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
