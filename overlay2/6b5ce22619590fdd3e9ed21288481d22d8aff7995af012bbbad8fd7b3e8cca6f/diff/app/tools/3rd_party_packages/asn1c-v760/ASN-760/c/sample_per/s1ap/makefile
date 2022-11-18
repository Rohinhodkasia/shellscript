# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

SRCDIR = .
HFILESDIR = .

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1per$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(PSLIBS)

OBJECTS =  \
S1AP-CommonDataTypes$(OBJ) \
S1AP-IEs$(OBJ) \
S1AP-PDU-Contents$(OBJ) \
S1AP-PDU-Descriptions$(OBJ) \
SonTransfer-IEs$(OBJ)

ENCOBJECTS =  \
S1AP-CommonDataTypesEnc$(OBJ) \
S1AP-IEsEnc$(OBJ) \
S1AP-PDU-ContentsEnc$(OBJ) \
S1AP-PDU-DescriptionsEnc$(OBJ) \
SonTransfer-IEsEnc$(OBJ)

DECOBJECTS =  \
S1AP-CommonDataTypesDec$(OBJ) \
S1AP-IEsDec$(OBJ) \
S1AP-PDU-ContentsDec$(OBJ) \
S1AP-PDU-DescriptionsDec$(OBJ) \
SonTransfer-IEsDec$(OBJ)

PRTOBJECTS =  \
S1AP-CommonDataTypesPrint$(OBJ) \
S1AP-IEsPrint$(OBJ) \
S1AP-PDU-ContentsPrint$(OBJ) \
S1AP-PDU-DescriptionsPrint$(OBJ) \
SonTransfer-IEsPrint$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)S1AP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)S1AP-Constants.h $(HFILESDIR)$(PS)S1AP-Containers.h \
$(HFILESDIR)$(PS)S1AP-IEs.h $(HFILESDIR)$(PS)S1AP-PDU-Contents.h \
$(HFILESDIR)$(PS)S1AP-PDU-Descriptions.h $(HFILESDIR)$(PS)SonTransfer-IEs.h \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
$(SRCDIR)/S1AP-CommonDataTypesEnc.c \
$(SRCDIR)/S1AP-CommonDataTypesDec.c \
$(SRCDIR)/S1AP-CommonDataTypes.c \
$(SRCDIR)/S1AP-CommonDataTypesPrint.c \
$(HFILESDIR)$(PS)S1AP-CommonDataTypes.h \
$(HFILESDIR)$(PS)S1AP-Constants.h \
$(HFILESDIR)$(PS)S1AP-Containers.h \
$(SRCDIR)/S1AP-IEsEnc.c \
$(SRCDIR)/S1AP-IEsDec.c \
$(SRCDIR)/S1AP-IEs.c \
$(SRCDIR)/S1AP-IEsPrint.c \
$(HFILESDIR)$(PS)S1AP-IEs.h \
$(SRCDIR)/S1AP-PDU-ContentsEnc.c \
$(SRCDIR)/S1AP-PDU-ContentsDec.c \
$(SRCDIR)/S1AP-PDU-Contents.c \
$(SRCDIR)/S1AP-PDU-ContentsPrint.c \
$(HFILESDIR)$(PS)S1AP-PDU-Contents.h \
$(SRCDIR)/S1AP-PDU-DescriptionsEnc.c \
$(SRCDIR)/S1AP-PDU-DescriptionsDec.c \
$(SRCDIR)/S1AP-PDU-Descriptions.c \
$(SRCDIR)/S1AP-PDU-DescriptionsPrint.c \
$(HFILESDIR)$(PS)S1AP-PDU-Descriptions.h \
$(SRCDIR)/SonTransfer-IEsEnc.c \
$(SRCDIR)/SonTransfer-IEsDec.c \
$(SRCDIR)/SonTransfer-IEs.c \
$(SRCDIR)/SonTransfer-IEsPrint.c \
$(HFILESDIR)$(PS)SonTransfer-IEs.h \
$(HFILESDIR)$(PS)rtkey.h \
: ../../../specs/S1AP/rel15/S1AP-CommonDataTypes.asn ../../../specs/S1AP/rel15/S1AP-Constants.asn ../../../specs/S1AP/rel15/S1AP-Containers.asn ../../../specs/S1AP/rel15/S1AP-IEs.asn ../../../specs/S1AP/rel15/S1AP-PDU-Contents.asn ../../../specs/S1AP/rel15/S1AP-PDU-Descriptions.asn ../../../specs/S1AP/rel15/SonTransfer-IEs.asn $(ASN1C)
	$(ASN1C) ../../../specs/S1AP/rel15/S1AP-CommonDataTypes.asn ../../../specs/S1AP/rel15/S1AP-Constants.asn ../../../specs/S1AP/rel15/S1AP-Containers.asn ../../../specs/S1AP/rel15/S1AP-IEs.asn ../../../specs/S1AP/rel15/S1AP-PDU-Contents.asn ../../../specs/S1AP/rel15/S1AP-PDU-Descriptions.asn ../../../specs/S1AP/rel15/SonTransfer-IEs.asn -c -per -I ../../../specs/S1AP/rel15 -pdu S1AP_PDU -pdu S1AP-PDU -print -strict-size -table-unions -trace -fqtvalue -x64

depends: S1AP-CommonDataTypes.c S1AP-IEs.c S1AP-PDU-Contents.c \
S1AP-PDU-Descriptions.c SonTransfer-IEs.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) S1AP-CommonDataTypesEnc.c
	$(RM) S1AP-CommonDataTypesDec.c
	$(RM) S1AP-CommonDataTypes.c
	$(RM) S1AP-CommonDataTypesPrint.c
	$(RM) $(HFILESDIR)$(PS)S1AP-CommonDataTypes.h 
	$(RM) $(HFILESDIR)$(PS)S1AP-Constants.h 
	$(RM) $(HFILESDIR)$(PS)S1AP-Containers.h 
	$(RM) S1AP-IEsEnc.c
	$(RM) S1AP-IEsDec.c
	$(RM) S1AP-IEs.c
	$(RM) S1AP-IEsPrint.c
	$(RM) $(HFILESDIR)$(PS)S1AP-IEs.h 
	$(RM) S1AP-PDU-ContentsEnc.c
	$(RM) S1AP-PDU-ContentsDec.c
	$(RM) S1AP-PDU-Contents.c
	$(RM) S1AP-PDU-ContentsPrint.c
	$(RM) $(HFILESDIR)$(PS)S1AP-PDU-Contents.h 
	$(RM) S1AP-PDU-DescriptionsEnc.c
	$(RM) S1AP-PDU-DescriptionsDec.c
	$(RM) S1AP-PDU-Descriptions.c
	$(RM) S1AP-PDU-DescriptionsPrint.c
	$(RM) $(HFILESDIR)$(PS)S1AP-PDU-Descriptions.h 
	$(RM) SonTransfer-IEsEnc.c
	$(RM) SonTransfer-IEsDec.c
	$(RM) SonTransfer-IEs.c
	$(RM) SonTransfer-IEsPrint.c
	$(RM) $(HFILESDIR)$(PS)SonTransfer-IEs.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) message.dat
	$(RM_MSVC_FILES)
