# makefile to build the employee sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = $(RTSRCDIR)/asn1CEvtHndlr.h

OBJECTS = Employee$(OBJ) EmployeeEnc$(OBJ) EmployeeDec$(OBJ)
OBJECTS2 = Employee2$(OBJ) Employee2Enc$(OBJ) Employee2Dec$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS2) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS2) $(LINKOPT) $(LPATHS) $(BSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) \
EmployeePrint$(OBJ) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) \
	   EmployeePrint$(OBJ) $(LINKOPT) $(LPATHS) $(BSLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Employee.c EmployeeDec.c EmployeeEnc.c EmployeePrint.c \
Employee.h : employee.asn
	$(ASN1C) employee.asn -c -ber -events -print

Employee2.c Employee2Dec.c Employee2Enc.c Employee2.h : employee2.asn
	$(ASN1C) employee2.asn -c -ber -events

depends: Employee.c Employee2.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) Employee*.c
	$(RM) Employee*.h
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
