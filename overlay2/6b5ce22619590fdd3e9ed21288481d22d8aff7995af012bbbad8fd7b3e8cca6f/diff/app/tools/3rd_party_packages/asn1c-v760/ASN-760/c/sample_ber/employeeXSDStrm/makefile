# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

XSDFILE = Employee.xsd

# include directories
OSROOTDIR = ../../..
RTSRCDIR = $(OSROOTDIR)/rtsrc
BERSRCDIR = $(OSROOTDIR)/rtbersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)/asn1type.h $(BERSRCDIR)/asn1ber.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_) -D_TRACE
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(BERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(BERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
LLIBS = $(LLBER) $(LLRT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR) $(XMLLPATHS)

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

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(LIBS)
	$(LINK) writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) \
	  $(LINKOPT) $(LPATHS) $(LLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRTOBJECTS) $(LIBS)
	$(LINK) reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRTOBJECTS) \
	  $(LINKOPT) $(LPATHS) $(LLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
$(SRCDIR)/EmployeeEnc.c \
$(SRCDIR)/EmployeeDec.c \
$(SRCDIR)/Employee.c \
$(SRCDIR)/EmployeePrint.c \
$(HFILESDIR)/Employee.h \
$(HFILESDIR)/rtkey.h \
: $(XSDFILE) $(OSROOTDIR)/bin/asn1c$(EXE)
	$(ASN1C) $(XSDFILE) -c -ber -stream -print -trace

depends: Employee.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) EmployeeEnc.c
	$(RM) EmployeeDec.c
	$(RM) Employee.c
	$(RM) EmployeePrint.c
	$(RM) $(HFILESDIR)$(PS)Employee.h 
	$(RM) $(HFILESDIR)$(PS)Namespace.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.dat
	$(RM) messagei.dat
