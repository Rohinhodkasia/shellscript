# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = nbapSample.asn

# include directories
OSROOTDIR = ../../..
LIBDIR  = $(OSROOTDIR)/cpp$(RTDIRSFX)/lib
RTSRCDIR = $(OSROOTDIR)/rtsrc
PERSRCDIR = $(OSROOTDIR)/rtpersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)/asn1type.h $(RTSRCDIR)/asn1CppTypes.h  \
$(PERSRCDIR)/asn1per.h $(PERSRCDIR)/asn1PerCppTypes.h 
# compiler defs
CFLAGS = -c $(CVARSMTD_) $(CFLAGS_) $(CBLDTYPE_) -D_TRACE
CCFLAGS = $(CFLAGS)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(PERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(PERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
LLIBS = $(LLPER) $(LLRT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
NBAP-PDU-Descriptions$(OBJ) \
NBAP-PDU-Contents$(OBJ) \
NBAP-IEs$(OBJ) \
NBAP-CommonDataTypes$(OBJ) 

ENCOBJECTS =  \
NBAP-PDU-DescriptionsEnc$(OBJ) \
NBAP-PDU-ContentsEnc$(OBJ) \
NBAP-IEsEnc$(OBJ) \
NBAP-CommonDataTypesEnc$(OBJ)

DECOBJECTS =  \
NBAP-PDU-DescriptionsDec$(OBJ) \
NBAP-PDU-ContentsDec$(OBJ) \
NBAP-IEsDec$(OBJ) \
NBAP-CommonDataTypesDec$(OBJ)

PRTOBJECTS =  \
NBAP-PDU-DescriptionsPrint$(OBJ) \
NBAP-PDU-ContentsPrint$(OBJ) \
NBAP-IEsPrint$(OBJ) \
NBAP-CommonDataTypesPrint$(OBJ)

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

RWHFILES = $(HFILESDIR)/NBAP-PDU-Descriptions.h \
$(HFILESDIR)/NBAP-PDU-Contents.h $(HFILESDIR)/NBAP-IEs.h \
$(HFILESDIR)/NBAP-CommonDataTypes.h $(HFILESDIR)/NBAP-Constants.h \
$(HFILESDIR)/NBAP-Containers.h $(HFILESDIR)/rtkey.h $(HFILES)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .cpp .h rules
$(SRCDIR)/NBAP-PDU-DescriptionsEnc.cpp \
$(SRCDIR)/NBAP-PDU-DescriptionsDec.cpp \
$(SRCDIR)/NBAP-PDU-Descriptions.cpp \
$(SRCDIR)/NBAP-PDU-DescriptionsPrint.cpp \
$(HFILESDIR)/NBAP-PDU-Descriptions.h \
$(SRCDIR)/NBAP-PDU-ContentsEnc.cpp \
$(SRCDIR)/NBAP-PDU-ContentsDec.cpp \
$(SRCDIR)/NBAP-PDU-Contents.cpp \
$(SRCDIR)/NBAP-PDU-ContentsPrint.cpp \
$(HFILESDIR)/NBAP-PDU-Contents.h \
$(SRCDIR)/NBAP-IEsEnc.cpp \
$(SRCDIR)/NBAP-IEsDec.cpp \
$(SRCDIR)/NBAP-IEs.cpp \
$(SRCDIR)/NBAP-IEsPrint.cpp \
$(HFILESDIR)/NBAP-IEs.h \
$(SRCDIR)/NBAP-CommonDataTypesEnc.cpp \
$(SRCDIR)/NBAP-CommonDataTypesDec.cpp \
$(SRCDIR)/NBAP-CommonDataTypes.cpp \
$(SRCDIR)/NBAP-CommonDataTypesPrint.cpp \
$(HFILESDIR)/NBAP-CommonDataTypes.h \
$(HFILESDIR)/NBAP-Constants.h \
$(HFILESDIR)/NBAP-Containers.h \
$(HFILESDIR)/rtkey.h \
: $(ASN1FILE) $(OSROOTDIR)/bin/asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -cpp -per -print -table-unions -trace

depends: NBAP-PDU-Descriptions.cpp NBAP-PDU-Contents.cpp NBAP-IEs.cpp \
NBAP-CommonDataTypes.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) NBAP-PDU-DescriptionsEnc.cpp
	$(RM) NBAP-PDU-DescriptionsDec.cpp
	$(RM) NBAP-PDU-Descriptions.cpp
	$(RM) NBAP-PDU-DescriptionsPrint.cpp
	$(RM) NBAP-PDU-Descriptions.h 
	$(RM) NBAP-PDU-ContentsEnc.cpp
	$(RM) NBAP-PDU-ContentsDec.cpp
	$(RM) NBAP-PDU-Contents.cpp
	$(RM) NBAP-PDU-ContentsPrint.cpp
	$(RM) NBAP-PDU-Contents.h 
	$(RM) NBAP-IEsEnc.cpp
	$(RM) NBAP-IEsDec.cpp
	$(RM) NBAP-IEs.cpp
	$(RM) NBAP-IEsPrint.cpp
	$(RM) NBAP-IEs.h 
	$(RM) NBAP-CommonDataTypesEnc.cpp
	$(RM) NBAP-CommonDataTypesDec.cpp
	$(RM) NBAP-CommonDataTypes.cpp
	$(RM) NBAP-CommonDataTypesPrint.cpp
	$(RM) NBAP-CommonDataTypes.h 
	$(RM) NBAP-Constants.h 
	$(RM) NBAP-Containers.h 
	$(RM) rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.dat

