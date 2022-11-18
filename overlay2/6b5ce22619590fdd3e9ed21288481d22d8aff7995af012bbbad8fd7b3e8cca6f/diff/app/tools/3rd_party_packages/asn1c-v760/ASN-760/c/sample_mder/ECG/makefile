# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = IEEE_20601_d20_defs.asn1

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
LIBS = $(LIBDIR)$(PS)$(LIBPFX)asn1mder$(A) $(LIBDIR)$(PS)$(LIBPFX)asn1rt$(A)
LLIBS = $(LIBS) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
IEEE-11073-20601-ASN1$(OBJ)

ENCOBJECTS =  \
IEEE-11073-20601-ASN1Enc$(OBJ)

DECOBJECTS =  \
IEEE-11073-20601-ASN1Dec$(OBJ)

PRTOBJECTS =  \
IEEE-11073-20601-ASN1Print$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)IEEE-11073-20601-ASN1.h $(HFILESDIR)$(PS)rtkey.h \
$(HFILES)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
$(SRCDIR)$(PS)IEEE-11073-20601-ASN1Enc.c \
$(SRCDIR)$(PS)IEEE-11073-20601-ASN1Dec.c \
$(SRCDIR)$(PS)IEEE-11073-20601-ASN1.c \
$(SRCDIR)$(PS)IEEE-11073-20601-ASN1Print.c \
$(HFILESDIR)$(PS)IEEE-11073-20601-ASN1.h \
$(HFILESDIR)$(PS)rtkey.h \
: $(ASN1FILE) $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -c -mder -print -fqtvalue

depends: IEEE-11073-20601-ASN1.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) IEEE-11073-20601-ASN1Enc.c
	$(RM) IEEE-11073-20601-ASN1Dec.c
	$(RM) IEEE-11073-20601-ASN1.c
	$(RM) IEEE-11073-20601-ASN1Print.c
	$(RM) $(HFILESDIR)$(PS)IEEE-11073-20601-ASN1.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.dat

