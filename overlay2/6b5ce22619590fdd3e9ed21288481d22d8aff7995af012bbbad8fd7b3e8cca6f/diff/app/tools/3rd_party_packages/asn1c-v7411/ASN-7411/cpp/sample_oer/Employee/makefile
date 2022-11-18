# makefile to build generated files

include ../../platform.mk

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)cpp$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
OERSRCDIR = $(OSROOTDIR)$(PS)rtoersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(RTSRCDIR)$(PS)asn1CppTypes.h  \
$(OERSRCDIR)$(PS)asn1oer.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_) -D_TRACE
CCFLAGS = -c $(CVARS_) $(CCFLAGS_) $(CBLDTYPE_) -D_TRACE
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(OERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1oer$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1oer$(LLAEXT) $(LLPFX)asn1rt$(LLAEXT) $(LLSYS)
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

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
 $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)Employee.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

writer$(OBJ) : $(SRCDIR)$(PS)writer.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)/writer.cpp

reader$(OBJ) : $(SRCDIR)$(PS)reader.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)/reader.cpp

# .cpp -> .obj rules
# common file rules
Employee$(OBJ) : $(SRCDIR)$(PS)Employee.cpp \
$(HFILESDIR)$(PS)Employee.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Employee.cpp

# decode file rules
EmployeeDec$(OBJ) : $(SRCDIR)$(PS)EmployeeDec.cpp \
$(HFILESDIR)$(PS)Employee.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)EmployeeDec.cpp

# encode file rules
EmployeeEnc$(OBJ) : $(SRCDIR)$(PS)EmployeeEnc.cpp \
$(HFILESDIR)$(PS)Employee.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)EmployeeEnc.cpp

# print file rules
EmployeePrint$(OBJ) : $(SRCDIR)$(PS)EmployeePrint.cpp \
$(HFILESDIR)$(PS)Employee.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)EmployeePrint.cpp

# .asn -> .cpp .h rules
$(SRCDIR)/EmployeeEnc.cpp \
$(SRCDIR)/EmployeeDec.cpp \
$(SRCDIR)/Employee.cpp \
$(SRCDIR)/EmployeePrint.cpp \
$(HFILESDIR)$(PS)Employee.h \
$(HFILESDIR)$(PS)rtkey.h \
: employee.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(OSROOTDIR)$(PS)bin$(PS)asn1c employee.asn -cpp -oer -fqenum -print -trace -fqtvalue

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
	$(RM) message.dat

