# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(RTSRCDIR) \
-I$(BERSRCDIR) $(XMLINC) $(XMLDEFS)
LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

HFILES = $(RTSRCDIR)/asn1type.h \
$(RTSRCDIR)/asn1CppTypes.h \
$(BERSRCDIR)/asn1BerCppTypes.h \



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

xml2der$(OBJ) : xml2der.cpp Employee.h $(HFILES)

writer$(OBJ) : writer.cpp Employee.h $(HFILES)

Employee$(OBJ) : Employee.cpp Employee.h $(HFILES)
EmployeeEnc$(OBJ) : EmployeeEnc.cpp Employee.h $(HFILES)
EmployeeDec$(OBJ) : EmployeeDec.cpp Employee.h $(HFILES)
EmployeePrint$(OBJ) : EmployeePrint.cpp Employee.h $(HFILES)

Employee.cpp EmployeeDec.cpp EmployeeEnc.cpp \
Employee.h EmployeePrint.cpp : employee.asn
	$(ASN1C) employee.asn -c++ -xer -der -trace -print

clean :
	$(RM) Employee*.cpp
	$(RM) Employee.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.xml
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) xml2der$(EXE)
	$(RM) rtkey.h


