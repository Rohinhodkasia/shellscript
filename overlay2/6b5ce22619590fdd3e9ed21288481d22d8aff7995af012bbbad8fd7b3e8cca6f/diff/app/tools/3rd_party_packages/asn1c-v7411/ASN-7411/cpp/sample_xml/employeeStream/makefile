# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(XERSRCDIR) -I$(XMLSRCDIR) \
-I$(RTSRCDIR) $(XMLINC) 

LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

HFILES = $(RTSRCDIR)/asn1type.h \
$(RTSRCDIR)/asn1CppTypes.h \
$(XMLSRCDIR)/asn1xml.h \
$(RTXSRCDIR)/rtxCommon.h

HFILESDIR = .
SRCDIR = .

OBJECTS =  \
Employee$(OBJ)

ENCOBJECTS =  \
EmployeeEnc$(OBJ)

DECOBJECTS =  \
EmployeeDec$(OBJ)

PRTOBJECTS =  \
EmployeePrint$(OBJ)

LIBS = $(LIBDIR)/$(RTLIBNAME)
all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
 $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(XMLLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(XMLLIBS)

RWHFILES = $(HFILESDIR)/Employee.h $(HFILESDIR)/rtkey.h $(HFILES)

writer$(OBJ) : writer.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) writer.cpp

reader$(OBJ) : reader.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) reader.cpp

# .cpp -> .obj rules
# common file rules
Employee$(OBJ) : $(SRCDIR)/Employee.cpp \
$(HFILESDIR)/Employee.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/Employee.cpp

# decode file rules
EmployeeDec$(OBJ) : $(SRCDIR)/EmployeeDec.cpp \
$(HFILESDIR)/Employee.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/EmployeeDec.cpp

# encode file rules
EmployeeEnc$(OBJ) : $(SRCDIR)/EmployeeEnc.cpp \
$(HFILESDIR)/Employee.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/EmployeeEnc.cpp

# print file rules
EmployeePrint$(OBJ) : $(SRCDIR)/EmployeePrint.cpp \
$(HFILESDIR)/Employee.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/EmployeePrint.cpp

# .asn -> .cpp .h rules
$(SRCDIR)/EmployeeEnc.cpp \
$(SRCDIR)/EmployeeDec.cpp \
$(SRCDIR)/Employee.cpp \
$(SRCDIR)/EmployeePrint.cpp \
$(HFILESDIR)/Employee.h \
$(HFILESDIR)/rtkey.h \
: ../employee/employee.asn $(OSROOTDIR)/bin/asn1c$(EXE)
	$(ASN1C) ../employee/employee.asn -cpp -xml -print -stream

clean:
	$(RM) EmployeeEnc.cpp
	$(RM) EmployeeDec.cpp
	$(RM) Employee.cpp
	$(RM) EmployeePrint.cpp
	$(RM) $(HFILESDIR)$(PS)Employee.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.xml

