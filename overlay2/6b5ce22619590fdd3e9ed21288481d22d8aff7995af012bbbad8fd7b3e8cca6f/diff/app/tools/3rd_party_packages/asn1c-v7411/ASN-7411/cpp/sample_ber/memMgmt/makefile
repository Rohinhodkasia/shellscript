# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = $(BERCPPHFILES)

OBJECTS = Employee$(OBJ) EmployeeEnc$(OBJ) EmployeeDec$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) EmployeeCopy$(OBJ) \
$(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) EmployeeCopy$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(BSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) EmployeePrint$(OBJ) \
EmployeeCopy$(OBJ) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) EmployeePrint$(OBJ) \
	   EmployeeCopy$(OBJ) $(LINKOPT) $(LPATHS) $(BSLIBS)

writer$(OBJ) : writer.cpp Employee.h $(HFILES)
reader$(OBJ) : reader.cpp Employee.h $(HFILES)

Employee$(OBJ)  : Employee.cpp Employee.h $(HFILES)
EmployeeDec$(OBJ)  : EmployeeDec.cpp Employee.h $(HFILES)
EmployeeEnc$(OBJ)  : EmployeeEnc.cpp Employee.h $(HFILES)
EmployeePrint$(OBJ)  : EmployeePrint.cpp Employee.h $(HFILES)
EmployeeCopy$(OBJ)  : EmployeeCopy.cpp Employee.h $(HFILES)

Employee.cpp EmployeeDec.cpp EmployeeEnc.cpp Employee.h : employee.asn
	$(ASN1C) employee.asn -c++ -ber -trace -print -genCopy

clean :
	$(RM) Employee*.cpp
	$(RM) Employee.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) *.dat
	$(RM) rtkey.h
