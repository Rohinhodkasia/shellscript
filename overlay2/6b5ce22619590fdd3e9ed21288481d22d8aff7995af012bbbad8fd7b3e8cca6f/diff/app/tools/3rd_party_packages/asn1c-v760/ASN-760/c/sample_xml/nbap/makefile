# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = nbapSample.asn

# include directories
OSROOTDIR = ../../..
LIBDIR  = $(OSROOTDIR)/c$(RTDIRSFX)/lib
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

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(PRTOBJECTS)

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

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
$(SRCDIR)/NBAP-PDU-DescriptionsEnc.c \
$(SRCDIR)/NBAP-PDU-DescriptionsDec.c \
$(SRCDIR)/NBAP-PDU-Descriptions.c \
$(SRCDIR)/NBAP-PDU-DescriptionsPrint.c \
$(HFILESDIR)/NBAP-PDU-Descriptions.h \
$(SRCDIR)/NBAP-PDU-ContentsEnc.c \
$(SRCDIR)/NBAP-PDU-ContentsDec.c \
$(SRCDIR)/NBAP-PDU-Contents.c \
$(SRCDIR)/NBAP-PDU-ContentsPrint.c \
$(HFILESDIR)/NBAP-PDU-Contents.h \
$(SRCDIR)/NBAP-IEsEnc.c \
$(SRCDIR)/NBAP-IEsDec.c \
$(SRCDIR)/NBAP-IEs.c \
$(SRCDIR)/NBAP-IEsPrint.c \
$(HFILESDIR)/NBAP-IEs.h \
$(SRCDIR)/NBAP-CommonDataTypesEnc.c \
$(SRCDIR)/NBAP-CommonDataTypesDec.c \
$(SRCDIR)/NBAP-CommonDataTypes.c \
$(SRCDIR)/NBAP-CommonDataTypesPrint.c \
$(HFILESDIR)/NBAP-CommonDataTypes.h \
$(HFILESDIR)/NBAP-Constants.h \
$(HFILESDIR)/NBAP-Containers.h \
$(HFILESDIR)/rtkey.h \
: $(ASN1FILE) $(OSROOTDIR)/bin/asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -c -xml -print -table-unions -trace -fqtvalue

depends: NBAP-PDU-Descriptions.c NBAP-PDU-Contents.c NBAP-IEs.c \
NBAP-CommonDataTypes.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) NBAP-PDU-DescriptionsEnc.c
	$(RM) NBAP-PDU-DescriptionsDec.c
	$(RM) NBAP-PDU-Descriptions.c
	$(RM) NBAP-PDU-DescriptionsPrint.c
	$(RM) NBAP-PDU-Descriptions.h 
	$(RM) NBAP-PDU-ContentsEnc.c
	$(RM) NBAP-PDU-ContentsDec.c
	$(RM) NBAP-PDU-Contents.c
	$(RM) NBAP-PDU-ContentsPrint.c
	$(RM) NBAP-PDU-Contents.h 
	$(RM) NBAP-IEsEnc.c
	$(RM) NBAP-IEsDec.c
	$(RM) NBAP-IEs.c
	$(RM) NBAP-IEsPrint.c
	$(RM) NBAP-IEs.h 
	$(RM) NBAP-CommonDataTypesEnc.c
	$(RM) NBAP-CommonDataTypesDec.c
	$(RM) NBAP-CommonDataTypes.c
	$(RM) NBAP-CommonDataTypesPrint.c
	$(RM) NBAP-CommonDataTypes.h 
	$(RM) NBAP-Constants.h 
	$(RM) NBAP-Containers.h 
	$(RM) rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.xml

