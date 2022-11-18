# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = PKCS15TokenInfo.asn

# include directories
OSROOTDIR = ../../..
RTSRCDIR = $(OSROOTDIR)/rtsrc
XMLSRCDIR = $(OSROOTDIR)/rtxmlsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)/asn1type.h $(XMLSRCDIR)/osrtxml.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(XMLSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(RTLIBNAME)
LLIBS = $(LLXML) $(LLRT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
PKCS15TokenInfo$(OBJ)

ENCOBJECTS =  \
PKCS15TokenInfoEnc$(OBJ)

DECOBJECTS =  \
PKCS15TokenInfoDec$(OBJ)

PRTOBJECTS =  \
PKCS15TokenInfoPrint$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS) $(LLSYS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS) $(LLSYS)

RWHFILES = $(HFILESDIR)/PKCS15TokenInfo.h $(HFILESDIR)/rtkey.h $(HFILES)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
$(SRCDIR)/PKCS15TokenInfoEnc.c \
$(SRCDIR)/PKCS15TokenInfoDec.c \
$(SRCDIR)/PKCS15TokenInfo.c \
$(SRCDIR)/PKCS15TokenInfoPrint.c \
$(HFILESDIR)/PKCS15TokenInfo.h \
$(HFILESDIR)/rtkey.h \
: $(ASN1FILE) $(OSROOTDIR)/bin/asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -c -xml -xsd -print -strict-size

runtest : writer$(EXE) reader$(EXE)
	.$(PS)writer
	java -cp ../../../java/util/Val Val message.xml *.xsd
	.$(PS)reader

depends: PKCS15TokenInfo.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) PKCS15TokenInfoEnc.c
	$(RM) PKCS15TokenInfoDec.c
	$(RM) PKCS15TokenInfo.c
	$(RM) PKCS15TokenInfo.xsd
	$(RM) PKCS15TokenInfoPrint.c
	$(RM) $(HFILESDIR)$(PS)PKCS15TokenInfo.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) RtClass.xsd
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.xml

