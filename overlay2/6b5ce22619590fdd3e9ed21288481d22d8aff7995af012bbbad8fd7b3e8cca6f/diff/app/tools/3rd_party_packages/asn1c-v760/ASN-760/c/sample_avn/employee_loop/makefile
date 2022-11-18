# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

# include directories
# OSROOTDIR = ..$(PS)..$(PS)..
# LIBDIR  = $(OSROOTDIR)$(PS)c$(RTDIRSFX)$(PS)lib
# RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
# PERSRCDIR = $(OSROOTDIR)$(PS)rtpersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(PERSRCDIR)$(PS)asn1per.h 
# compiler defs
# CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_) -D_TRACE
# IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(PERSRCDIR) $(IPATHS_)
# LINKOPT = $(LINKOPT_)

# run-time libraries
# LIBS = $(LIBDIR)/$(LIBPFX)asn1per$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPER) $(LLRT) $(LLSYS)
# LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
Employee$(OBJ)

ENCOBJECTS =  \
EmployeeEnc$(OBJ)

DECOBJECTS =  \
EmployeeDec$(OBJ)

PRTOBJECTS =  \
EmployeePrint$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
reader$(EXE)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)Employee.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

reader$(OBJ) : $(SRCDIR)$(PS)reader.c $(RWHFILES)
	$(CC) -c $(CFLAGS) $(IPATHS) $(SRCDIR)$(PS)reader.c

# .c -> .obj rules
# common file rules
Employee$(OBJ) : $(SRCDIR)$(PS)Employee.c \
$(HFILESDIR)$(PS)Employee.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Employee.c

# decode file rules
EmployeeDec$(OBJ) : $(SRCDIR)$(PS)EmployeeDec.c \
$(HFILESDIR)$(PS)Employee.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)EmployeeDec.c

# encode file rules
EmployeeEnc$(OBJ) : $(SRCDIR)$(PS)EmployeeEnc.c \
$(HFILESDIR)$(PS)Employee.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)EmployeeEnc.c

# print file rules
EmployeePrint$(OBJ) : $(SRCDIR)$(PS)EmployeePrint.c \
$(HFILESDIR)$(PS)Employee.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)EmployeePrint.c

# .asn -> .c .h rules
$(SRCDIR)/EmployeeEnc.c \
$(SRCDIR)/EmployeeDec.c \
$(SRCDIR)/Employee.c \
$(SRCDIR)/EmployeePrint.c \
$(HFILESDIR)$(PS)Employee.h \
$(HFILESDIR)$(PS)rtkey.h \
: employee.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(ASN1C) employee.asn -c -avn -per -print -trace -fqtvalue

clean:
	$(RM) EmployeeEnc.c
	$(RM) EmployeeDec.c
	$(RM) Employee.c
	$(RM) EmployeePrint.c
	$(RM) $(HFILESDIR)$(PS)Employee.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
