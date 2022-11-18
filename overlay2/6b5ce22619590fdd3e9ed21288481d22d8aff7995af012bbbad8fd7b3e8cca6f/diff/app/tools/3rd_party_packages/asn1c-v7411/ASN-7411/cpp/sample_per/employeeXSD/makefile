# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

HFILES = $(PERCPPHFILES)

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
$(LIBDIR)/$(PERLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
	   $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
$(PRTOBJECTS) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
	   $(PRTOBJECTS) $(LINKOPT) $(LPATHS) $(PSLIBS)

writer$(OBJ) : writer.cpp Employee.h $(HFILES)
reader$(OBJ) : reader.cpp Employee.h $(HFILES)

# .cpp -> .obj rules
# common file rules
Employee$(OBJ) : Employee.cpp Employee.h rtkey.h $(HFILES)
	$(CCC) $(CFLAGS) -c $(IPATHS) Employee.cpp

# decode file rules
EmployeeDec$(OBJ) : EmployeeDec.cpp Employee.h rtkey.h $(HFILES)
	$(CCC) $(CFLAGS) -c $(IPATHS) EmployeeDec.cpp

# encode file rules
EmployeeEnc$(OBJ) : EmployeeEnc.cpp Employee.h rtkey.h $(HFILES)
	$(CCC) $(CFLAGS) -c $(IPATHS) EmployeeEnc.cpp

# print file rules
EmployeePrint$(OBJ) : EmployeePrint.cpp Employee.h rtkey.h $(HFILES)
	$(CCC) $(CFLAGS) -c $(IPATHS) EmployeePrint.cpp

Employee.cpp EmployeeDec.cpp EmployeeEnc.cpp Employee.h : \
Employee.xsd $(ASN1C)
	$(ASN1C) Employee.xsd -c++ -per -trace -print

clean :
	$(RM) Employee*.cpp
	$(RM) Employee.h
	$(RM) Namespace.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
