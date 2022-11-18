# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = nbapSample.asn

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)cpp$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
PERSRCDIR = $(OSROOTDIR)$(PS)rtpersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(RTSRCDIR)$(PS)asn1CppTypes.h  \
$(PERSRCDIR)$(PS)asn1per.h $(PERSRCDIR)$(PS)asn1PerCppTypes.h 
# compiler defs
CFLAGS = -c $(CVARSMTD_) $(CFLAGS_) $(CBLDTYPE_)
CCFLAGS = -c $(CVARSMTD_) $(CCFLAGS_) $(CBLDTYPE_)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(PERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1per$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A) $(LLSYS)
LLIBS = $(LLPER) $(LLRT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
NBAP-PDU-Descriptions$(OBJ) \
NBAP-PDU-Contents$(OBJ) \
NBAP-IEs$(OBJ) \
NBAP-CommonDataTypes$(OBJ) \
NBAP-CommonDataTypesDec$(OBJ) \
printHandler$(OBJ)

all : $(OBJECTS) reader$(EXE)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(LIBDEPENDS)
	$(LINK) reader$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(LLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .cpp .h rules
$(SRCDIR)/NBAP-PDU-Descriptions.cpp \
$(HFILESDIR)$(PS)NBAP-PDU-Descriptions.h \
$(SRCDIR)/NBAP-PDU-Contents.cpp \
$(HFILESDIR)$(PS)NBAP-PDU-Contents.h \
$(SRCDIR)/NBAP-IEs.cpp \
$(HFILESDIR)$(PS)NBAP-IEs.h \
$(SRCDIR)/NBAP-CommonDataTypesDec.cpp \
$(SRCDIR)/NBAP-CommonDataTypes.cpp \
$(HFILESDIR)$(PS)NBAP-CommonDataTypes.h \
$(HFILESDIR)$(PS)NBAP-Constants.h \
$(HFILESDIR)$(PS)NBAP-Containers.h \
$(HFILESDIR)$(PS)rtkey.h \
: $(ASN1FILE) $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -cpp -per -events -noInit -notypes -table-unions -x64

depends: NBAP-PDU-Descriptions.cpp NBAP-PDU-Contents.cpp NBAP-IEs.cpp \
NBAP-CommonDataTypes.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) NBAP-PDU-Descriptions.cpp
	$(RM) $(HFILESDIR)$(PS)NBAP-PDU-Descriptions.h 
	$(RM) NBAP-PDU-Contents.cpp
	$(RM) $(HFILESDIR)$(PS)NBAP-PDU-Contents.h 
	$(RM) NBAP-IEs.cpp
	$(RM) $(HFILESDIR)$(PS)NBAP-IEs.h 
	$(RM) NBAP-CommonDataTypesDec.cpp
	$(RM) NBAP-CommonDataTypes.cpp
	$(RM) $(HFILESDIR)$(PS)NBAP-CommonDataTypes.h 
	$(RM) $(HFILESDIR)$(PS)NBAP-Constants.h 
	$(RM) $(HFILESDIR)$(PS)NBAP-Containers.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM_MSVC_FILES)

