# makefile to build the employee sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = $(PERCPPHFILES)
OBJECTS = Employee$(OBJ) EmployeeDec$(OBJ) EmployeeEnc$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) EmployeePrint$(OBJ) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) EmployeePrint$(OBJ) $(LINKOPT) $(LPATHS) $(PSLIBS)

writer$(OBJ) : writer.cpp Employee.h $(HFILES)

reader$(OBJ) : reader.cpp Employee.h $(HFILES)

Employee$(OBJ) : Employee.cpp Employee.h $(HFILES)
EmployeeDec$(OBJ) : EmployeeDec.cpp Employee.h $(HFILES)
EmployeeEnc$(OBJ) : EmployeeEnc.cpp Employee.h $(HFILES)
EmployeePrint$(OBJ)  : EmployeePrint.cpp Employee.h $(HFILES)

Employee.cpp EmployeeDec.cpp EmployeeEnc.cpp \
EmployeePrint.cpp Employee.h : employee.asn
	$(ASN1C) employee.asn -c++ -per -trace -print

clean :
	$(RM) Employee*.cpp
	$(RM) Employee.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h


