# makefile to build the employee sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = employee.asn
HFILES = Employee.h $(BERHFILES)

writer$(EXE) : writer$(OBJ) Employee$(OBJ) EmployeeEnc$(OBJ) \
EmployeePrint$(OBJ) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) Employee$(OBJ) EmployeeEnc$(OBJ) \
	   EmployeePrint$(OBJ) $(LINKOPT) $(LPATHS) $(BSLIBS)

reader$(EXE) : reader$(OBJ) Employee$(OBJ) EmployeeDec$(OBJ) \
EmployeePrint$(OBJ) printHandler$(OBJ) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) Employee$(OBJ) EmployeeDec$(OBJ) EmployeePrint$(OBJ) \
	   printHandler$(OBJ) $(LINKOPT) $(LPATHS) $(BSLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Employee.c EmployeeEnc.c EmployeeDec.c EmployeePrint.c Employee.h : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c -ber -trace -print -events -geninit 

depends: Employee.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) Employee*.c
	$(RM) Employee.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
	$(RM) message.dat
	$(RM) messagei.dat
