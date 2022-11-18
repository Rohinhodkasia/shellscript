# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = test.asn

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
TimeString$(OBJ)

ENCOBJECTS = 

DECOBJECTS = 

PRTOBJECTS =  \
print$(OBJ)

TESTOBJECTS = 

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
$(TESTOBJECTS) writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(TESTOBJECTS) \
 $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS) $(LLSYS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS) $(LLSYS)

RWHFILES = $(HFILESDIR)$(PS)TimeString.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
$(SRCDIR)$(PS)TimeString.c \
$(SRCDIR)$(PS)print.c \
$(HFILESDIR)$(PS)TimeString.h \
$(HFILESDIR)$(PS)rtkey.h \
: $(ASN1FILE) $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -c -json -cfile TimeString.c -pdu all -print print.c -test -fqtvalue

depends: TimeString.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) TimeString.c
	$(RM) print.c
	$(RM) $(HFILESDIR)$(PS)TimeString.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) .$(PS)rtkey.h
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.json

