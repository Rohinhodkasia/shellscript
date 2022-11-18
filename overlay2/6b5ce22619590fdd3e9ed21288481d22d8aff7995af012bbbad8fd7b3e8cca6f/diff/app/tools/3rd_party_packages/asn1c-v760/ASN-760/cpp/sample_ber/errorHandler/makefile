# makefile to build the employee sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = $(BERCPPHFILES) $(RTSRCDIR)/asn1CppEvtHndlr.h

OBJECTS = Employee$(OBJ) EmployeeEnc$(OBJ) EmployeeDec$(OBJ)
OBJECTS2 = Employee2$(OBJ) Employee2Enc$(OBJ) Employee2Dec$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS2) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS2) $(LINKOPT) $(LPATHS) $(BSLIBS)

reader$(EXE) : reader$(OBJ) errorHandler$(OBJ) $(OBJECTS) \
EmployeePrint$(OBJ) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) errorHandler$(OBJ) $(OBJECTS) \
	   EmployeePrint$(OBJ) $(LINKOPT) $(LPATHS) $(BSLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Employee.cpp EmployeeDec.cpp EmployeeEnc.cpp EmployeePrint.cpp \
Employee.h : employee.asn
	$(ASN1C) employee.asn -c++ -ber -events -print

Employee2.cpp Employee2Dec.cpp Employee2Enc.cpp Employee2.h : employee2.asn
	$(ASN1C) employee2.asn -c++ -ber -events

depends: Employee.cpp Employee2.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) Employee*.cpp
	$(RM) Employee*.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
