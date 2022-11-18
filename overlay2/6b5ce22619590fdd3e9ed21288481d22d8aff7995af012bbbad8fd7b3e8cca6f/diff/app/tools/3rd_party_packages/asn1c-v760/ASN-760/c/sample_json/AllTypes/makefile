# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = employee.asn

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)c$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)$(PS)$(LIBPFX)asn1json$(A) $(LIBDIR)$(PS)$(LIBPFX)asn1rt$(A)
LLIBS = $(LLJSON) $(LLRT)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
AllTypes$(OBJ)

ENCOBJECTS =  \
AllTypesEnc$(OBJ)

DECOBJECTS =  \
AllTypesDec$(OBJ)

PRTOBJECTS =  \
AllTypesPrint$(OBJ)

TESTOBJECTS =  \
AllTypesTest$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
$(TESTOBJECTS) writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(TESTOBJECTS) \
 $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(JSONLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(JSONLIBS)

RWHFILES = $(HFILESDIR)$(PS)AllTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
# We do not include AllTypesTest.c since that file is Perforce-controlled.
# Including it causes ASN1C to run twice since nmake/make sees it as a target
# that's supposed to be created but isn't.
$(SRCDIR)$(PS)AllTypesEnc.c \
$(SRCDIR)$(PS)AllTypesDec.c \
$(SRCDIR)$(PS)AllTypes.c \
$(SRCDIR)$(PS)AllTypesPrint.c \
$(HFILESDIR)$(PS)AllTypes.h \
$(HFILESDIR)$(PS)rtkey.h \
: $(ASN1FILE) $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -c -json -print -fqtvalue

depends: AllTypes.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) AllTypesEnc.c
	$(RM) AllTypesDec.c
	$(RM) AllTypes.c
	$(RM) AllTypesPrint.c
	$(RM) $(HFILESDIR)$(PS)AllTypes.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) .$(PS)rtkey.h
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.json

