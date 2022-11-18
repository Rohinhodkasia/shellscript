# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

XSDFILE = Employee.xsd
HFILES = $(BERCPPHFILES)

OBJECTS =  \
Employee$(OBJ)

ENCOBJECTS =  \
EmployeeEnc$(OBJ)

DECOBJECTS =  \
EmployeeDec$(OBJ)

PRTOBJECTS =  \
EmployeePrint$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS) \
writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
$(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
	   $(LINKOPT) $(LPATHS) $(BSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
$(PRTOBJECTS) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
	   $(PRTOBJECTS) $(LINKOPT) $(LPATHS) $(BSLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Employee.cpp EmployeeDec.cpp EmployeeEnc.cpp Employee.h : \
$(XSDFILE) $(ASN1C)
	$(ASN1C) $(XSDFILE) -c++ -ber -trace -print

depends: Employee.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) Employee*.cpp
	$(RM) Employee.h
	$(RM) Namespace.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
