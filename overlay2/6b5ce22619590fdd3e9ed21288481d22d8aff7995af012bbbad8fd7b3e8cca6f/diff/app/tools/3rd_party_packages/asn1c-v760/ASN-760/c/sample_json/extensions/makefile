# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = extensions.asn

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
LIBS = $(LIBDIR)/$(LIBPFX)asn1json$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1json$(LLAEXT) $(LLPFX)asn1rt$(LLAEXT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
Extensions$(OBJ)

ENCOBJECTS =  \
ExtensionsEnc$(OBJ)

DECOBJECTS =  \
ExtensionsDec$(OBJ)

PRTOBJECTS =  \
ExtensionsPrint$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)Extensions.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
$(SRCDIR)/ExtensionsEnc.c \
$(SRCDIR)/ExtensionsDec.c \
$(SRCDIR)/Extensions.c \
$(SRCDIR)/ExtensionsPrint.c \
$(HFILESDIR)$(PS)Extensions.h \
$(HFILESDIR)$(PS)rtkey.h \
: $(ASN1FILE) $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -c -jer -print -fqtvalue

depends: Extensions.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) ExtensionsEnc.c
	$(RM) ExtensionsDec.c
	$(RM) Extensions.c
	$(RM) ExtensionsPrint.c
	$(RM) $(HFILESDIR)$(PS)Extensions.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) message.json
	$(RM) *~
