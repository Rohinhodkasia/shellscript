# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

# include directories
OSROOTDIR = ../../..
RTSRCDIR = $(OSROOTDIR)/rtsrc
XMLSRCDIR = $(OSROOTDIR)/rtxmlsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)/asn1type.h $(RTSRCDIR)/asn1CppTypes.h  \
$(XMLSRCDIR)/osrtxml.h 
# compiler defs
CFLAGS = -c $(CVARSMTD_) $(CFLAGS_) $(CBLDTYPE_)
CCFLAGS = $(CFLAGS)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(XMLSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(RTLIBNAME)
LLIBS = $(LLXML) $(LLRT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
Employee$(OBJ)

ENCOBJECTS =  \
EmployeeEnc$(OBJ)

DECOBJECTS =  \
EmployeeDec$(OBJ)

PRTOBJECTS =  \
EmployeePrint$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(PRTOBJECTS) $(DECOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)/Employee.h $(HFILESDIR)/rtkey.h $(HFILES)

writer$(OBJ) : writer.cpp $(RWHFILES)
reader$(OBJ) : reader.cpp $(RWHFILES)

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

# reader file rules
reader$(OBJ) : $(SRCDIR)/reader.cpp \
$(HFILESDIR)/Employee.h $(HFILESDIR)/rtkey.h $(HFILES)

# writer file rules
writer$(OBJ) : $(SRCDIR)/writer.cpp \
$(HFILESDIR)/Employee.h $(HFILESDIR)/rtkey.h $(HFILES)

# .asn -> .cpp .h rules
$(SRCDIR)/EmployeeEnc.cpp \
$(SRCDIR)/EmployeeDec.cpp \
$(SRCDIR)/Employee.cpp \
$(SRCDIR)/EmployeePrint.cpp \
$(HFILESDIR)/Employee.h \
$(HFILESDIR)/rtkey.h \
: Employee.xsd $(OSROOTDIR)/bin/asn1c$(EXE)
	..$(PS)..$(PS)..$(PS)bin$(PS)asn1c Employee.xsd -cpp -xml -print -prtfmt bracetext -trace -uniqueNames

clean:
	$(RM) EmployeeEnc.cpp
	$(RM) EmployeeDec.cpp
	$(RM) Employee.cpp
	$(RM) EmployeePrint.cpp
	$(RM) $(HFILESDIR)$(PS)Employee.h 
	$(RM) $(HFILESDIR)$(PS)Namespace.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.xml

