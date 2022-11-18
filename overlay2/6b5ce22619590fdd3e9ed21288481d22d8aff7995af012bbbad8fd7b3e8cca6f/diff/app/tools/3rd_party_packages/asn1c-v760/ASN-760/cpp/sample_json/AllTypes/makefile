# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = employee.asn

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)cpp$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(RTSRCDIR)$(PS)asn1CppTypes.h 
# compiler defs
CFLAGS = -c $(CVARSMTD_) $(CFLAGS_) $(CBLDTYPE_)
CCFLAGS = $(CFLAGS)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)$(PS)$(LIBPFX)asn1json$(A) $(LIBDIR)$(PS)$(LIBPFX)asn1rt$(A)
LLIBS = $(LLJSON) $(LLRT) $(LLSYS)
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

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
 $(TESTOBJECTS) $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)AllTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .cpp .h rules
$(SRCDIR)$(PS)AllTypesEnc.cpp \
$(SRCDIR)$(PS)AllTypesDec.cpp \
$(SRCDIR)$(PS)AllTypes.cpp \
$(SRCDIR)$(PS)AllTypesPrint.cpp \
$(SRCDIR)$(PS)AllTypesTest.cpp \
$(HFILESDIR)$(PS)AllTypes.h \
$(HFILESDIR)$(PS)rtkey.h \
: $(ASN1FILE) $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -cpp -json -print -test

depends: AllTypes.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) AllTypesEnc.cpp
	$(RM) AllTypesDec.cpp
	$(RM) AllTypes.cpp
	$(RM) AllTypesPrint.cpp
	$(RM) AllTypesTest.cpp
	$(RM) $(HFILESDIR)$(PS)AllTypes.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) .$(PS)rtkey.h
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.json

