# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = pkcs-1v2.asn
HFILESDIR = .
HFILES = $(RTSRCDIR)/asn1type.h $(BERSRCDIR)/asn1ber.h
LIBS = $(LIBDIR)/$(BERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
LLIBS = $(BSLIBS)

OBJECTS =  \
PKCS-1$(OBJ)

ENCOBJECTS =  \
PKCS-1Enc$(OBJ)

DECOBJECTS =  \
PKCS-1Dec$(OBJ)

PRTOBJECTS =  \
PKCS-1Print$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS) \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)/PKCS-1.h $(HFILESDIR)/rtkey.h $(HFILES)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
PKCS-1Enc.c \
PKCS-1Dec.c \
PKCS-1.c \
PKCS-1Print.c \
$(HFILESDIR)/PKCS-1.h \
$(HFILESDIR)/rtkey.h \
: pkcs1.cfg $(ASN1FILE) $(OSROOTDIR)/bin/asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -c -der -config pkcs1.cfg -events -noindeflen -print -table-unions

depends: PKCS-1.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) PKCS-1Enc.c
	$(RM) PKCS-1Dec.c
	$(RM) PKCS-1.c
	$(RM) PKCS-1Print.c
	$(RM) $(HFILESDIR)$(PS)PKCS-1.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) *.dat

