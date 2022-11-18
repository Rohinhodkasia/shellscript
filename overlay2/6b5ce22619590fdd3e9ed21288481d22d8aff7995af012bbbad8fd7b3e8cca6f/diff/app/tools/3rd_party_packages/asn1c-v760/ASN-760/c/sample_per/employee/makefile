# makefile to build the employee sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = employee.asn
HFILES = Employee.h $(PERHFILES)

writer$(EXE) : writer$(OBJ) Employee$(OBJ) EmployeeEnc$(OBJ) \
EmployeePrint$(OBJ) $(PERLIBNAMES)
	$(LINK) writer$(OBJ) Employee$(OBJ) EmployeeEnc$(OBJ) \
	   EmployeePrint$(OBJ) $(LINKOPT) $(LPATHS) $(LLPER) \
	   $(LLRT) $(LLSYS)

reader$(EXE) : reader$(OBJ) Employee$(OBJ) EmployeeDec$(OBJ) \
EmployeePrint$(OBJ) $(PERLIBNAMES)
	$(LINK) reader$(OBJ) Employee$(OBJ) EmployeeDec$(OBJ) \
	   EmployeePrint$(OBJ) $(LINKOPT) $(LPATHS) $(LLPER) \
	   $(LLRT) $(LLSYS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Employee.c EmployeeEnc.c EmployeeDec.c EmployeePrint.c Employee.h : \
$(ASN1FILE) ../../../bin/asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -c -per -trace -print -prtfmt bracetext -geninit

depends: Employee.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) Employee.h
	$(RM) Employee*.c
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
