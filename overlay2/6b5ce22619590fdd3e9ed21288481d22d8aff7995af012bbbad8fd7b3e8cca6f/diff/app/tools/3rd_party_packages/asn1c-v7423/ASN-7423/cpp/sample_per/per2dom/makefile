# makefile to build the employee sample program

include ../../platform.mk
include ../../../sample.mk

all : reader$(EXE)

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(PERSRCDIR) -I$(RTSRCDIR)
HFILES = $(PERCPPHFILES)

reader$(EXE) : reader$(OBJ) Employee$(OBJ) domHandler$(OBJ) \
$(LIBDIR)/$(PERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
	$(LINK) reader$(OBJ) Employee$(OBJ) \
	   domHandler$(OBJ) $(LINKOPT) $(LPATHS) $(PSLIBS) 

reader$(OBJ) : reader.cpp Employee.h $(HFILES)
domHandler$(OBJ) : domHandler.cpp domHandler.h $(HFILES)

Employee$(OBJ) : Employee.cpp Employee.h $(HFILES)

Employee.cpp Employee.h : employee.asn
	$(ASN1C) employee.asn -c++ -per -events -notypes -x64

clean :
	$(RM) Employee*.cpp
	$(RM) Employee.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.lib
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) rtkey.h
