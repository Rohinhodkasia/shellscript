# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

XSDFILE = cap.xsd

# include directories
OSROOTDIR = ../../..
RTSRCDIR = $(OSROOTDIR)/rtsrc
XMLSRCDIR = $(OSROOTDIR)/rtxmlsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)/asn1type.h $(RTSRCDIR)/asn1CppTypes.h  \
$(XMLSRCDIR)/osrtxml.h 
# compiler defs
CFLAGS = -c $(CVARSMTD_) $(CFLAGS_) $(CBLDTYPE_)
CCFLAGS = $(CFLAGS)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(XMLSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(RTLIBNAME)
LLIBS = $(LLXML) $(LLRT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
Cap$(OBJ) \
XSD$(OBJ)

ENCOBJECTS =  \
CapEnc$(OBJ) \
XSDEnc$(OBJ)

DECOBJECTS =  \
CapDec$(OBJ) \
XSDDec$(OBJ)

PRTOBJECTS =  \
CapPrint$(OBJ) \
XSDPrint$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(PRTOBJECTS) $(DECOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)/Cap.h $(HFILESDIR)/rtkey.h $(HFILES)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .cpp .h rules
$(SRCDIR)/CapEnc.cpp \
$(SRCDIR)/CapDec.cpp \
$(SRCDIR)/Cap.cpp \
$(SRCDIR)/CapPrint.cpp \
$(HFILESDIR)/Cap.h \
$(SRCDIR)/XSDEnc.cpp \
$(SRCDIR)/XSDDec.cpp \
$(SRCDIR)/XSD.cpp \
$(SRCDIR)/XSDPrint.cpp \
$(HFILESDIR)/XSD.h \
$(HFILESDIR)/Namespace.h \
$(HFILESDIR)/rtkey.h \
: $(XSDFILE) $(OSROOTDIR)/bin/asn1c$(EXE)
	$(ASN1C) $(XSDFILE) -cpp -xml -print -trace

depends: Cap.cpp XSD.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) CapEnc.cpp
	$(RM) CapDec.cpp
	$(RM) Cap.cpp
	$(RM) CapPrint.cpp
	$(RM) $(HFILESDIR)$(PS)Cap.h 
	$(RM) XSDEnc.cpp
	$(RM) XSDDec.cpp
	$(RM) XSD.cpp
	$(RM) XSDPrint.cpp
	$(RM) $(HFILESDIR)$(PS)XSD.h 
	$(RM) $(HFILESDIR)$(PS)Namespace.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.xml

