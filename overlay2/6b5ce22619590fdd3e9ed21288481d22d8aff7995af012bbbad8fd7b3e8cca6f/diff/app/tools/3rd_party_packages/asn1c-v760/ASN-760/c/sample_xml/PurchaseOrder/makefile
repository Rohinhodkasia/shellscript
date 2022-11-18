# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

XSDFILE = po.xsd

# include directories
OSROOTDIR = ../../..
RTSRCDIR = $(OSROOTDIR)/rtsrc
XMLSRCDIR = $(OSROOTDIR)/rtxmlsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)/asn1type.h $(XMLSRCDIR)/osrtxml.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_) -D_TRACE
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(XMLSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(RTLIBNAME)
LLIBS = $(LLXML) $(LLRT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR) $(XMLLPATHS)

OBJECTS =  \
Po$(OBJ) \
XSD$(OBJ)

ENCOBJECTS =  \
PoEnc$(OBJ) \
XSDEnc$(OBJ)

DECOBJECTS =  \
PoDec$(OBJ) \
XSDDec$(OBJ)

PRTOBJECTS =  \
PoPrint$(OBJ) \
XSDPrint$(OBJ)

TESTOBJECTS =  \
PoTest$(OBJ) \
XSDTest$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
$(TESTOBJECTS) writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(TESTOBJECTS) $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS) $(LLSYS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRTOBJECTS) 

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS) $(LLSYS)

RWHFILES = $(HFILESDIR)/Po.h $(HFILESDIR)/rtkey.h $(HFILES)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
$(SRCDIR)/PoEnc.c \
$(SRCDIR)/PoDec.c \
$(SRCDIR)/Po.c \
$(SRCDIR)/PoPrint.c \
$(SRCDIR)/PoTest.c \
$(HFILESDIR)/Po.h \
$(SRCDIR)/XSDEnc.c \
$(SRCDIR)/XSDDec.c \
$(SRCDIR)/XSD.c \
$(SRCDIR)/XSDPrint.c \
$(SRCDIR)/XSDTest.c \
$(HFILESDIR)/XSD.h \
$(HFILESDIR)/Namespace.h \
$(HFILESDIR)/rtkey.h \
: $(XSDFILE) $(OSROOTDIR)/bin/asn1c$(EXE)
	$(ASN1C) $(XSDFILE) -c -xml -geninit -print -prtfmt bracetext -test -trace -uniqueNames

depends: Po.c XSD.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) PoEnc.c
	$(RM) PoDec.c
	$(RM) Po.c
	$(RM) PoPrint.c
	$(RM) PoTest.c
	$(RM) $(HFILESDIR)$(PS)Po.h 
	$(RM) XSDEnc.c
	$(RM) XSDDec.c
	$(RM) XSD.c
	$(RM) XSDPrint.c
	$(RM) XSDTest.c
	$(RM) $(HFILESDIR)$(PS)XSD.h 
	$(RM) $(HFILESDIR)$(PS)Namespace.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.xml

