# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(XERSRCDIR) -I$(XMLSRCDIR) \
-I$(RTSRCDIR) $(XMLINC) 

LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

HFILES = $(RTSRCDIR)/asn1type.h \
$(RTSRCDIR)/asn1intl.h \
$(RTSRCDIR)/asn1CppTypes.h \
$(XMLSRCDIR)/asn1xml.h \
$(RTXSRCDIR)/rtxCommon.h

OBJECTS = Employee$(OBJ) EmployeeEnc$(OBJ) EmployeeDec$(OBJ)

all : writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(OBJECTS) \
$(LIBDIR)/$(RTLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(XMLLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) EmployeePrint$(OBJ) \
$(LIBDIR)/$(RTLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) EmployeePrint$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(XMLLIBS)

writer$(OBJ) : writer.cpp Employee.h $(HFILES)
reader$(OBJ) : reader.cpp Employee.h $(HFILES)

Employee$(OBJ) : Employee.cpp Employee.h $(HFILES)
EmployeeEnc$(OBJ) : EmployeeEnc.cpp Employee.h $(HFILES)
EmployeeDec$(OBJ) : EmployeeDec.cpp Employee.h $(HFILES)
EmployeePrint$(OBJ) : EmployeePrint.cpp Employee.h $(HFILES)

Employee.cpp EmployeeEnc.cpp EmployeeDec.cpp Employee.xsd \
Employee.h EmployeePrint.cpp : employee.asn
	$(ASN1C) employee.asn -c++ -xml -xsd -trace -print

clean :
	$(RM) Employee*.cpp
	$(RM) Employee.h
	$(RM) Employee.xsd
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.xml
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h


