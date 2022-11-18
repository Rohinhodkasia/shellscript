# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = employee.asn
IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(XMLSRCDIR) -I$(RTSRCDIR) -I$(BERSRCDIR)
LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

HFILES = $(RTSRCDIR)/asn1type.h \
$(RTSRCDIR)/asn1CppTypes.h \
$(BERSRCDIR)/asn1BerCppTypes.h \
$(XMLSRCDIR)/asn1xml.h

OBJECTS = Employee$(OBJ) EmployeeEnc$(OBJ) EmployeeDec$(OBJ)

all : xml2der$(EXE) writer$(EXE)

xml2der$(EXE) : xml2der$(OBJ) $(OBJECTS) EmployeePrint$(OBJ) \
$(LIBDIR)/$(BERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
	$(LINK) xml2der$(OBJ) $(OBJECTS) EmployeePrint$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(LLBER) $(LLXML) $(LLRT) $(LLSYS)

writer$(EXE) : writer$(OBJ) $(OBJECTS) \
$(LIBDIR)/$(BERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) \
	   $(LINKOPT) $(LPATHS) $(LLBER) $(LLXML) $(LLRT) $(LLSYS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Employee.cpp EmployeeDec.cpp EmployeeEnc.cpp \
Employee.h Employee.xsd EmployeePrint.cpp : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c++ -xml -xsd -der -trace -print

depends: Employee.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) Employee*.cpp
	$(RM) Employee.h
	$(RM) Employee.xsd
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.*
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) xml2der$(EXE)
	$(RM) rtkey.h


