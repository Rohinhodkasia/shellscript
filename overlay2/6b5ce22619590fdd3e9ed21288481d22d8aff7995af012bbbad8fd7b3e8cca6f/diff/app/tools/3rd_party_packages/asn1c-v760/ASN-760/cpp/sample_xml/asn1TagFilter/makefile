# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = asn1TagFilter.asn

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)cpp$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
XMLSRCDIR = $(OSROOTDIR)$(PS)rtxmlsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(RTSRCDIR)$(PS)asn1CppTypes.h  \
$(XMLSRCDIR)$(PS)osrtxml.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_)
CCFLAGS = -c $(CVARS_) $(CCFLAGS_) $(CBLDTYPE_)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(XMLSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1xml$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1xml$(LLAEXT) $(LLPFX)asn1rt$(LLAEXT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
Asn1TagFilter$(OBJ)

ENCOBJECTS =  \
Asn1TagFilterEnc$(OBJ)

DECOBJECTS =  \
Asn1TagFilterDec$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) writer$(EXE)  \
reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)Asn1TagFilter.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .cpp .h rules
$(SRCDIR)/Asn1TagFilterEnc.cpp \
$(SRCDIR)/Asn1TagFilterDec.cpp \
$(SRCDIR)/Asn1TagFilter.cpp \
$(HFILESDIR)$(PS)Asn1TagFilter.h \
$(HFILESDIR)$(PS)rtkey.h \
: $(ASN1FILE) $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -cpp -xml -noxmlns

depends: Asn1TagFilter.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) Asn1TagFilterEnc.cpp
	$(RM) Asn1TagFilterDec.cpp
	$(RM) Asn1TagFilter.cpp
	$(RM) $(HFILESDIR)$(PS)Asn1TagFilter.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.xml

