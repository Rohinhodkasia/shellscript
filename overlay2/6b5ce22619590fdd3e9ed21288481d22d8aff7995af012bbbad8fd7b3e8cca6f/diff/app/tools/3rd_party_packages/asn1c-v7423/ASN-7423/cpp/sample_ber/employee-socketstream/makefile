# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

# include directories
OSROOTDIR = ../../..
RTSRCDIR = $(OSROOTDIR)/rtsrc
BERSRCDIR = $(OSROOTDIR)/rtbersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)/asn1type.h $(RTSRCDIR)/asn1CppTypes.h  \
$(BERSRCDIR)/asn1ber.h $(BERSRCDIR)/asn1BerCppTypes.h 
# compiler defs
CFLAGS = -c $(CVARSMTD_) $(CFLAGS_) $(CBLDTYPE_)
CCFLAGS = $(CFLAGS)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(BERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(BERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
LLIBS = $(LLBER) $(LLRT) $(LLSYS)
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
server$(EXE) client$(EXE)

SERVEROBJ = server$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
 $(PRTOBJECTS)

server$(EXE) : $(SERVEROBJ) $(LIBS)
	$(LINK) $(SERVEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

CLIENTOBJ = client$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

client$(EXE) : $(CLIENTOBJ) $(LIBS)
	$(LINK) $(CLIENTOBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)/Employee.h $(HFILESDIR)/rtkey.h $(HFILES)

server$(OBJ) : server.cpp $(RWHFILES)
client$(OBJ) : client.cpp $(RWHFILES)

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

# client file rules
client$(OBJ) : $(SRCDIR)/client.cpp \
$(HFILESDIR)/Employee.h $(HFILESDIR)/rtkey.h $(HFILES)

# server file rules
server$(OBJ) : $(SRCDIR)/server.cpp \
$(HFILESDIR)/Employee.h $(HFILESDIR)/rtkey.h $(HFILES)

# .asn -> .cpp .h rules
$(SRCDIR)/EmployeeEnc.cpp \
$(SRCDIR)/EmployeeDec.cpp \
$(SRCDIR)/Employee.cpp \
$(SRCDIR)/EmployeePrint.cpp \
$(HFILESDIR)/Employee.h \
$(HFILESDIR)/rtkey.h \
: employee.asn $(OSROOTDIR)/bin/asn1c$(EXE)
	..$(PS)..$(PS)..$(PS)bin$(PS)asn1c employee.asn -cpp -ber -stream -print -prtfmt bracetext -trace -uniqueNames

clean:
	$(RM) EmployeeEnc.cpp
	$(RM) EmployeeDec.cpp
	$(RM) Employee.cpp
	$(RM) EmployeePrint.cpp
	$(RM) $(HFILESDIR)$(PS)Employee.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) client$(EXE)
	$(RM) server$(EXE)
	$(RM_MSVC_FILES)

