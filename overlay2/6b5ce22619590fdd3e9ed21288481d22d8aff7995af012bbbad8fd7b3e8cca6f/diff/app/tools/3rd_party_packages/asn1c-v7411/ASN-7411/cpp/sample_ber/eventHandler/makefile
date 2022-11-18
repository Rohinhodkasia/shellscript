# makefile to build the employee sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = $(BERCPPHFILES) $(RTSRCDIR)/asn1CppEvtHndlr.h

writer$(EXE) : writer$(OBJ) Employee$(OBJ) EmployeeEnc$(OBJ) EmployeeDec$(OBJ) \
$(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) Employee$(OBJ) EmployeeEnc$(OBJ) EmployeeDec$(OBJ) \
	$(LINKOPT) $(LPATHS) $(BSLIBS)

reader$(EXE) : reader$(OBJ) printHandler$(OBJ) Employee$(OBJ) \
EmployeeEnc$(OBJ) EmployeeDec$(OBJ) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) printHandler$(OBJ) Employee$(OBJ) \
	EmployeeEnc$(OBJ) EmployeeDec$(OBJ) $(LINKOPT) $(LPATHS) $(BSLIBS)

writer$(OBJ) : writer.cpp Employee.h $(HFILES)
reader$(OBJ) : reader.cpp Employee.h $(HFILES)
printHandler$(OBJ) : printHandler.cpp printHandler.h $(HFILES)
EmployeeEnc$(OBJ)  : EmployeeEnc.cpp Employee.h $(HFILES)
EmployeeDec$(OBJ)  : EmployeeDec.cpp Employee.h $(HFILES)
EmployeePrint$(OBJ)  : EmployeePrint.cpp Employee.h $(HFILES)

Employee.cpp EmployeeDec.cpp EmployeeEnc.cpp Employee.h : employee.asn
	$(ASN1C) employee.asn -c++ -ber -trace -print -events

clean :
	$(RM) Employee*.cpp
	$(RM) Employee.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
