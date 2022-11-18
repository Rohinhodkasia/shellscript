# makefile to build the employee sample program

include ../../platform.mk
include ../../../sample.mk

all : reader$(EXE)

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(PERSRCDIR) \
-I$(RTSRCDIR) $(XMLINC) $(XMLDEFS)

LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

HFILES = $(PERCPPHFILES)

reader$(EXE) : reader$(OBJ) Employee$(OBJ) EmployeePrint$(OBJ) \
$(LIBDIR)/$(PERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
	$(LINK) reader$(OBJ) Employee$(OBJ) EmployeePrint$(OBJ) \
	   $(LINKOPT) $(LPATHS) \
	   $(LLPER) $(LLXML) $(LLRT) $(LLSYS)

reader$(OBJ) : reader.cpp Employee.h $(HFILES)

Employee$(OBJ) : Employee.cpp Employee.h $(HFILES)
EmployeePrint$(OBJ)  : EmployeePrint.cpp Employee.h $(HFILES)

Employee.cpp EmployeePrint.cpp Employee.h : employee.asn
	$(ASN1C) employee.asn -c++ -per -xml -trace -print EmployeePrint.cpp \
	-cfile Employee.cpp

clean :
	$(RM) Employee*.cpp
	$(RM) Employee.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.xml
	$(RM) *.lib
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) rtkey.h
