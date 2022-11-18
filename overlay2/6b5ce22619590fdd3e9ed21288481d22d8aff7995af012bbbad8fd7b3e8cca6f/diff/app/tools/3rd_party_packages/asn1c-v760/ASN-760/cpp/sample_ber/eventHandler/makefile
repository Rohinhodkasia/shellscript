# makefile to build the employee sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = employee.asn
HFILES = $(BERCPPHFILES) $(RTSRCDIR)/asn1CppEvtHndlr.h

writer$(EXE) : writer$(OBJ) Employee$(OBJ) EmployeeEnc$(OBJ) \
EmployeeDec$(OBJ) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) Employee$(OBJ) EmployeeEnc$(OBJ) EmployeeDec$(OBJ) \
	$(LINKOPT) $(LPATHS) $(BSLIBS)

reader$(EXE) : reader$(OBJ) printHandler$(OBJ) Employee$(OBJ) \
EmployeeEnc$(OBJ) EmployeeDec$(OBJ) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) printHandler$(OBJ) Employee$(OBJ) \
	EmployeeEnc$(OBJ) EmployeeDec$(OBJ) $(LINKOPT) $(LPATHS) $(BSLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Employee.cpp EmployeeDec.cpp EmployeeEnc.cpp Employee.h : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c++ -ber -trace -print -events

depends: Employee.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

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
