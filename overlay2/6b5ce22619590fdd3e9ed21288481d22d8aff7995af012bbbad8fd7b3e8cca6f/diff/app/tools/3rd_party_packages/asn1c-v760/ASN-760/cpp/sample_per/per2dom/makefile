# makefile to build the employee sample program

include ../../platform.mk
include ../../../sample.mk

all : reader$(EXE)

ASN1FILE = employee.asn
IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(PERSRCDIR) -I$(RTSRCDIR)
HFILES = $(PERCPPHFILES)

reader$(EXE) : reader$(OBJ) Employee$(OBJ) domHandler$(OBJ) \
$(LIBDIR)/$(PERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
	$(LINK) reader$(OBJ) Employee$(OBJ) \
	   domHandler$(OBJ) $(LINKOPT) $(LPATHS) $(PSLIBS) 

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Employee.cpp Employee.h : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c++ -per -events -notypes -x64

depends: Employee.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

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
