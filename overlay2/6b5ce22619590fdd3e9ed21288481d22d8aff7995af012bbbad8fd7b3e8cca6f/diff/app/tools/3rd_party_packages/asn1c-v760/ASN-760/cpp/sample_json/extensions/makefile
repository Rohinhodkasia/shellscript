# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = extensions.asn

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)cpp$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(RTSRCDIR)$(PS)asn1CppTypes.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_)
CCFLAGS = -c $(CVARS_) $(CCFLAGS_) $(CBLDTYPE_)
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

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
 $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)Extensions.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .cpp .h rules
$(SRCDIR)/ExtensionsEnc.cpp \
$(SRCDIR)/ExtensionsDec.cpp \
$(SRCDIR)/Extensions.cpp \
$(SRCDIR)/ExtensionsPrint.cpp \
$(HFILESDIR)$(PS)Extensions.h \
$(HFILESDIR)$(PS)rtkey.h \
: $(ASN1FILE) $(ASN1C)
	$(ASN1C) $(ASN1FILE) -cpp -jer -print

depends: Extensions.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) ExtensionsEnc.cpp
	$(RM) ExtensionsDec.cpp
	$(RM) Extensions.cpp
	$(RM) ExtensionsPrint.cpp
	$(RM) $(HFILESDIR)$(PS)Extensions.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) message.json
	$(RM) *~
