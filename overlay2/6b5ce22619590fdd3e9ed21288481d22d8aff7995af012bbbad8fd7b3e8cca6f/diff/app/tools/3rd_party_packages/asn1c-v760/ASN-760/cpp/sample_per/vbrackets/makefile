# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = vbrackets.asn

# include directories
OSROOTDIR = ../../..
LIBDIR  = $(OSROOTDIR)/cpp$(RTDIRSFX)/lib
RTSRCDIR = $(OSROOTDIR)/rtsrc
PERSRCDIR = $(OSROOTDIR)/rtpersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)/asn1type.h $(RTSRCDIR)/asn1CppTypes.h  \
$(PERSRCDIR)/asn1per.h $(PERSRCDIR)/asn1PerCppTypes.h 
# compiler defs
CFLAGS = -c $(CVARSMTD_) $(CFLAGS_) $(CBLDTYPE_) -D_TRACE
CCFLAGS = $(CFLAGS)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(PERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(PERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
LLIBS = $(LLPER) $(LLRT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
VersionBrackets$(OBJ)

ENCOBJECTS =  \
VersionBracketsEnc$(OBJ)

DECOBJECTS =  \
VersionBracketsDec$(OBJ)

PRTOBJECTS =  \
VersionBracketsPrint$(OBJ)

CPYOBJECTS =  \
VersionBracketsCopy$(OBJ)

CMPOBJECTS =  \
VersionBracketsCompare$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
$(CPYOBJECTS) $(CMPOBJECTS) writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
 $(PRTOBJECTS) $(CPYOBJECTS) $(CMPOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS) $(CPYOBJECTS) $(CMPOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)/VersionBrackets.h $(HFILESDIR)/rtkey.h $(HFILES)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .cpp .h rules
$(SRCDIR)/VersionBracketsEnc.cpp \
$(SRCDIR)/VersionBracketsDec.cpp \
$(SRCDIR)/VersionBrackets.cpp \
$(SRCDIR)/VersionBracketsPrint.cpp \
$(SRCDIR)/VersionBracketsCopy.cpp \
$(SRCDIR)/VersionBracketsCompare.cpp \
$(HFILESDIR)/VersionBrackets.h \
$(HFILESDIR)/rtkey.h \
: $(ASN1FILE) $(OSROOTDIR)/bin/asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -cpp -per -compare -copy -print -trace

depends: VersionBrackets.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) VersionBracketsEnc.cpp
	$(RM) VersionBracketsDec.cpp
	$(RM) VersionBrackets.cpp
	$(RM) VersionBracketsPrint.cpp
	$(RM) VersionBracketsCopy.cpp
	$(RM) VersionBracketsCompare.cpp
	$(RM) VersionBrackets.h 
	$(RM) rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.dat

