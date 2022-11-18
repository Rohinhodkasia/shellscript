# makefile to build generated files

include ../../platform.mk

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)c$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_) -D_TRACE
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I../../../specs/S1AP/rel15 -I$(RTSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1rt$(LLAEXT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

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
$(HFILESDIR)$(PS)S1AP-Constants.h $(HFILESDIR)$(PS)S1AP-Containers.h $(HFILESDIR)$(PS)S1AP-IEs.h  \
$(HFILESDIR)$(PS)S1AP-PDU-Contents.h $(HFILESDIR)$(PS)S1AP-PDU-Descriptions.h  \
$(HFILESDIR)$(PS)SonTransfer-IEs.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

writer$(OBJ) : $(SRCDIR)$(PS)writer.c $(RWHFILES)
	$(CC) -c $(CFLAGS) $(IPATHS) $(SRCDIR)$(PS)writer.c

reader$(OBJ) : $(SRCDIR)$(PS)reader.c $(RWHFILES)
	$(CC) -c $(CFLAGS) $(IPATHS) $(SRCDIR)$(PS)reader.c

# .c -> .obj rules
# common file rules
S1AP-CommonDataTypes$(OBJ) : $(SRCDIR)$(PS)S1AP-CommonDataTypes.c \
$(HFILESDIR)$(PS)S1AP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)S1AP-CommonDataTypes.c

# decode file rules
S1AP-CommonDataTypesDec$(OBJ) : $(SRCDIR)$(PS)S1AP-CommonDataTypesDec.c \
$(HFILESDIR)$(PS)S1AP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)S1AP-CommonDataTypesDec.c

# encode file rules
S1AP-CommonDataTypesEnc$(OBJ) : $(SRCDIR)$(PS)S1AP-CommonDataTypesEnc.c \
$(HFILESDIR)$(PS)S1AP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)S1AP-CommonDataTypesEnc.c

# print file rules
S1AP-CommonDataTypesPrint$(OBJ) : $(SRCDIR)$(PS)S1AP-CommonDataTypesPrint.c \
$(HFILESDIR)$(PS)S1AP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)S1AP-CommonDataTypesPrint.c

# common file rules
S1AP-IEs$(OBJ) : $(SRCDIR)$(PS)S1AP-IEs.c \
$(HFILESDIR)$(PS)S1AP-IEs.h $(HFILESDIR)$(PS)S1AP-Constants.h  \
$(HFILESDIR)$(PS)S1AP-CommonDataTypes.h $(HFILESDIR)$(PS)S1AP-Containers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)S1AP-IEs.c

# decode file rules
S1AP-IEsDec$(OBJ) : $(SRCDIR)$(PS)S1AP-IEsDec.c \
$(HFILESDIR)$(PS)S1AP-IEs.h $(HFILESDIR)$(PS)S1AP-Constants.h  \
$(HFILESDIR)$(PS)S1AP-CommonDataTypes.h $(HFILESDIR)$(PS)S1AP-Containers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)S1AP-IEsDec.c

# encode file rules
S1AP-IEsEnc$(OBJ) : $(SRCDIR)$(PS)S1AP-IEsEnc.c \
$(HFILESDIR)$(PS)S1AP-IEs.h $(HFILESDIR)$(PS)S1AP-Constants.h  \
$(HFILESDIR)$(PS)S1AP-CommonDataTypes.h $(HFILESDIR)$(PS)S1AP-Containers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)S1AP-IEsEnc.c

# print file rules
S1AP-IEsPrint$(OBJ) : $(SRCDIR)$(PS)S1AP-IEsPrint.c \
$(HFILESDIR)$(PS)S1AP-IEs.h $(HFILESDIR)$(PS)S1AP-Constants.h  \
$(HFILESDIR)$(PS)S1AP-CommonDataTypes.h $(HFILESDIR)$(PS)S1AP-Containers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)S1AP-IEsPrint.c

# common file rules
S1AP-PDU-Contents$(OBJ) : $(SRCDIR)$(PS)S1AP-PDU-Contents.c \
$(HFILESDIR)$(PS)S1AP-PDU-Contents.h $(HFILESDIR)$(PS)S1AP-IEs.h  \
$(HFILESDIR)$(PS)S1AP-Containers.h $(HFILESDIR)$(PS)S1AP-Constants.h  \
$(HFILESDIR)$(PS)S1AP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)S1AP-PDU-Contents.c

# decode file rules
S1AP-PDU-ContentsDec$(OBJ) : $(SRCDIR)$(PS)S1AP-PDU-ContentsDec.c \
$(HFILESDIR)$(PS)S1AP-PDU-Contents.h $(HFILESDIR)$(PS)S1AP-IEs.h  \
$(HFILESDIR)$(PS)S1AP-Containers.h $(HFILESDIR)$(PS)S1AP-Constants.h  \
$(HFILESDIR)$(PS)S1AP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)S1AP-PDU-ContentsDec.c

# encode file rules
S1AP-PDU-ContentsEnc$(OBJ) : $(SRCDIR)$(PS)S1AP-PDU-ContentsEnc.c \
$(HFILESDIR)$(PS)S1AP-PDU-Contents.h $(HFILESDIR)$(PS)S1AP-IEs.h  \
$(HFILESDIR)$(PS)S1AP-Containers.h $(HFILESDIR)$(PS)S1AP-Constants.h  \
$(HFILESDIR)$(PS)S1AP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)S1AP-PDU-ContentsEnc.c

# print file rules
S1AP-PDU-ContentsPrint$(OBJ) : $(SRCDIR)$(PS)S1AP-PDU-ContentsPrint.c \
$(HFILESDIR)$(PS)S1AP-PDU-Contents.h $(HFILESDIR)$(PS)S1AP-IEs.h  \
$(HFILESDIR)$(PS)S1AP-Containers.h $(HFILESDIR)$(PS)S1AP-Constants.h  \
$(HFILESDIR)$(PS)S1AP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)S1AP-PDU-ContentsPrint.c

# common file rules
S1AP-PDU-Descriptions$(OBJ) : $(SRCDIR)$(PS)S1AP-PDU-Descriptions.c \
$(HFILESDIR)$(PS)S1AP-PDU-Descriptions.h  \
$(HFILESDIR)$(PS)S1AP-CommonDataTypes.h $(HFILESDIR)$(PS)S1AP-PDU-Contents.h  \
$(HFILESDIR)$(PS)S1AP-Constants.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)S1AP-PDU-Descriptions.c

# decode file rules
S1AP-PDU-DescriptionsDec$(OBJ) : $(SRCDIR)$(PS)S1AP-PDU-DescriptionsDec.c \
$(HFILESDIR)$(PS)S1AP-PDU-Descriptions.h  \
$(HFILESDIR)$(PS)S1AP-CommonDataTypes.h $(HFILESDIR)$(PS)S1AP-PDU-Contents.h  \
$(HFILESDIR)$(PS)S1AP-Constants.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)S1AP-PDU-DescriptionsDec.c

# encode file rules
S1AP-PDU-DescriptionsEnc$(OBJ) : $(SRCDIR)$(PS)S1AP-PDU-DescriptionsEnc.c \
$(HFILESDIR)$(PS)S1AP-PDU-Descriptions.h  \
$(HFILESDIR)$(PS)S1AP-CommonDataTypes.h $(HFILESDIR)$(PS)S1AP-PDU-Contents.h  \
$(HFILESDIR)$(PS)S1AP-Constants.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)S1AP-PDU-DescriptionsEnc.c

# print file rules
S1AP-PDU-DescriptionsPrint$(OBJ) : $(SRCDIR)$(PS)S1AP-PDU-DescriptionsPrint.c \
$(HFILESDIR)$(PS)S1AP-PDU-Descriptions.h  \
$(HFILESDIR)$(PS)S1AP-CommonDataTypes.h $(HFILESDIR)$(PS)S1AP-PDU-Contents.h  \
$(HFILESDIR)$(PS)S1AP-Constants.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)S1AP-PDU-DescriptionsPrint.c

# common file rules
SonTransfer-IEs$(OBJ) : $(SRCDIR)$(PS)SonTransfer-IEs.c \
$(HFILESDIR)$(PS)SonTransfer-IEs.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)SonTransfer-IEs.c

# decode file rules
SonTransfer-IEsDec$(OBJ) : $(SRCDIR)$(PS)SonTransfer-IEsDec.c \
$(HFILESDIR)$(PS)SonTransfer-IEs.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)SonTransfer-IEsDec.c

# encode file rules
SonTransfer-IEsEnc$(OBJ) : $(SRCDIR)$(PS)SonTransfer-IEsEnc.c \
$(HFILESDIR)$(PS)SonTransfer-IEs.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)SonTransfer-IEsEnc.c

# print file rules
SonTransfer-IEsPrint$(OBJ) : $(SRCDIR)$(PS)SonTransfer-IEsPrint.c \
$(HFILESDIR)$(PS)SonTransfer-IEs.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)SonTransfer-IEsPrint.c

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
: ../../../specs/S1AP/rel15/S1AP-CommonDataTypes.asn ../../../specs/S1AP/rel15/S1AP-Constants.asn ../../../specs/S1AP/rel15/S1AP-Containers.asn ../../../specs/S1AP/rel15/S1AP-IEs.asn ../../../specs/S1AP/rel15/S1AP-PDU-Contents.asn ../../../specs/S1AP/rel15/S1AP-PDU-Descriptions.asn ../../../specs/S1AP/rel15/SonTransfer-IEs.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(OSROOTDIR)$(PS)bin$(PS)asn1c ../../../specs/S1AP/rel15/S1AP-CommonDataTypes.asn ../../../specs/S1AP/rel15/S1AP-Constants.asn ../../../specs/S1AP/rel15/S1AP-Containers.asn ../../../specs/S1AP/rel15/S1AP-IEs.asn ../../../specs/S1AP/rel15/S1AP-PDU-Contents.asn ../../../specs/S1AP/rel15/S1AP-PDU-Descriptions.asn ../../../specs/S1AP/rel15/SonTransfer-IEs.asn -c -avn -I ../../../specs/S1AP/rel15 -pdu S1AP_PDU -print -strict-size -table-unions -trace -fqtvalue -x64

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
