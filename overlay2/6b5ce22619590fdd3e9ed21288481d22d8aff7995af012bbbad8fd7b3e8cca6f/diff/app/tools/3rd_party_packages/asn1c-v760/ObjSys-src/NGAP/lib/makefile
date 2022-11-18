# makefile to build generated files

include ../../../ASN-760/platform.mk

# include directories
OSROOTDIR = ../../../ASN-760
LIBDIR  = $(OSROOTDIR)$(PS)c$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
PERSRCDIR = $(OSROOTDIR)$(PS)rtpersrc
SRCDIR = ..
HFILESDIR = ..
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(PERSRCDIR)$(PS)asn1per.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_) -D_TRACE -std=gnu99
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(PERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1per$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1per$(LLAEXT) $(LLPFX)asn1rt$(LLAEXT)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
NGAP-CommonDataTypes$(OBJ) \
NGAP-IEs$(OBJ) \
NGAP-PDU-Contents$(OBJ) \
NGAP-PDU-Descriptions$(OBJ)

ENCOBJECTS =  \
NGAP-CommonDataTypesEnc$(OBJ) \
NGAP-IEsEnc$(OBJ) \
NGAP-PDU-ContentsEnc$(OBJ) \
NGAP-PDU-DescriptionsEnc$(OBJ)

DECOBJECTS =  \
NGAP-CommonDataTypesDec$(OBJ) \
NGAP-IEsDec$(OBJ) \
NGAP-PDU-ContentsDec$(OBJ) \
NGAP-PDU-DescriptionsDec$(OBJ)

PRTOBJECTS =  \
NGAP-CommonDataTypesPrint$(OBJ) \
NGAP-IEsPrint$(OBJ) \
NGAP-PDU-ContentsPrint$(OBJ) \
NGAP-PDU-DescriptionsPrint$(OBJ)

P2SOBJECTS =  \
NGAP-CommonDataTypesPrtToStr$(OBJ) \
NGAP-IEsPrtToStr$(OBJ) \
NGAP-PDU-ContentsPrtToStr$(OBJ) \
NGAP-PDU-DescriptionsPrtToStr$(OBJ)

P2MOBJECTS =  \
NGAP-CommonDataTypesPrtToStrm$(OBJ) \
NGAP-IEsPrtToStrm$(OBJ) \
NGAP-PDU-ContentsPrtToStrm$(OBJ) \
NGAP-PDU-DescriptionsPrtToStrm$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
$(P2SOBJECTS) $(P2MOBJECTS) $(LIBPFX)NGAP$(A)

# .c -> .obj rules
# common file rules
NGAP-CommonDataTypes$(OBJ) : $(SRCDIR)$(PS)NGAP-CommonDataTypes.c \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-CommonDataTypes.c

# decode file rules
NGAP-CommonDataTypesDec$(OBJ) : $(SRCDIR)$(PS)NGAP-CommonDataTypesDec.c \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-CommonDataTypesDec.c

# encode file rules
NGAP-CommonDataTypesEnc$(OBJ) : $(SRCDIR)$(PS)NGAP-CommonDataTypesEnc.c \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-CommonDataTypesEnc.c

# print file rules
NGAP-CommonDataTypesPrint$(OBJ) : $(SRCDIR)$(PS)NGAP-CommonDataTypesPrint.c \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-CommonDataTypesPrint.c

# print-to-string file rules
NGAP-CommonDataTypesPrtToStr$(OBJ) : $(SRCDIR)$(PS)NGAP-CommonDataTypesPrtToStr.c \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-CommonDataTypesPrtToStr.c

# print-to-stream file rules
NGAP-CommonDataTypesPrtToStrm$(OBJ) : $(SRCDIR)$(PS)NGAP-CommonDataTypesPrtToStrm.c \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-CommonDataTypesPrtToStrm.c

# common file rules
NGAP-IEs$(OBJ) : $(SRCDIR)$(PS)NGAP-IEs.c \
$(HFILESDIR)$(PS)NGAP-IEs.h $(HFILESDIR)$(PS)NGAP-Constants.h  \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)NGAP-Containers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-IEs.c

# decode file rules
NGAP-IEsDec$(OBJ) : $(SRCDIR)$(PS)NGAP-IEsDec.c \
$(HFILESDIR)$(PS)NGAP-IEs.h $(HFILESDIR)$(PS)NGAP-Constants.h  \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)NGAP-Containers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-IEsDec.c

# encode file rules
NGAP-IEsEnc$(OBJ) : $(SRCDIR)$(PS)NGAP-IEsEnc.c \
$(HFILESDIR)$(PS)NGAP-IEs.h $(HFILESDIR)$(PS)NGAP-Constants.h  \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)NGAP-Containers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-IEsEnc.c

# print file rules
NGAP-IEsPrint$(OBJ) : $(SRCDIR)$(PS)NGAP-IEsPrint.c \
$(HFILESDIR)$(PS)NGAP-IEs.h $(HFILESDIR)$(PS)NGAP-Constants.h  \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)NGAP-Containers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-IEsPrint.c

# print-to-string file rules
NGAP-IEsPrtToStr$(OBJ) : $(SRCDIR)$(PS)NGAP-IEsPrtToStr.c \
$(HFILESDIR)$(PS)NGAP-IEs.h $(HFILESDIR)$(PS)NGAP-Constants.h  \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)NGAP-Containers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-IEsPrtToStr.c

# print-to-stream file rules
NGAP-IEsPrtToStrm$(OBJ) : $(SRCDIR)$(PS)NGAP-IEsPrtToStrm.c \
$(HFILESDIR)$(PS)NGAP-IEs.h $(HFILESDIR)$(PS)NGAP-Constants.h  \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)NGAP-Containers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-IEsPrtToStrm.c

# common file rules
NGAP-PDU-Contents$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-Contents.c \
$(HFILESDIR)$(PS)NGAP-PDU-Contents.h $(HFILESDIR)$(PS)NGAP-IEs.h  \
$(HFILESDIR)$(PS)NGAP-Containers.h $(HFILESDIR)$(PS)NGAP-Constants.h  \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-Contents.c

# decode file rules
NGAP-PDU-ContentsDec$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-ContentsDec.c \
$(HFILESDIR)$(PS)NGAP-PDU-Contents.h $(HFILESDIR)$(PS)NGAP-IEs.h  \
$(HFILESDIR)$(PS)NGAP-Containers.h $(HFILESDIR)$(PS)NGAP-Constants.h  \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-ContentsDec.c

# encode file rules
NGAP-PDU-ContentsEnc$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-ContentsEnc.c \
$(HFILESDIR)$(PS)NGAP-PDU-Contents.h $(HFILESDIR)$(PS)NGAP-IEs.h  \
$(HFILESDIR)$(PS)NGAP-Containers.h $(HFILESDIR)$(PS)NGAP-Constants.h  \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-ContentsEnc.c

# print file rules
NGAP-PDU-ContentsPrint$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-ContentsPrint.c \
$(HFILESDIR)$(PS)NGAP-PDU-Contents.h $(HFILESDIR)$(PS)NGAP-IEs.h  \
$(HFILESDIR)$(PS)NGAP-Containers.h $(HFILESDIR)$(PS)NGAP-Constants.h  \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-ContentsPrint.c

# print-to-string file rules
NGAP-PDU-ContentsPrtToStr$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-ContentsPrtToStr.c \
$(HFILESDIR)$(PS)NGAP-PDU-Contents.h $(HFILESDIR)$(PS)NGAP-IEs.h  \
$(HFILESDIR)$(PS)NGAP-Containers.h $(HFILESDIR)$(PS)NGAP-Constants.h  \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-ContentsPrtToStr.c

# print-to-stream file rules
NGAP-PDU-ContentsPrtToStrm$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-ContentsPrtToStrm.c \
$(HFILESDIR)$(PS)NGAP-PDU-Contents.h $(HFILESDIR)$(PS)NGAP-IEs.h  \
$(HFILESDIR)$(PS)NGAP-Containers.h $(HFILESDIR)$(PS)NGAP-Constants.h  \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-ContentsPrtToStrm.c

# common file rules
NGAP-PDU-Descriptions$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-Descriptions.c \
$(HFILESDIR)$(PS)NGAP-PDU-Descriptions.h  \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)NGAP-PDU-Contents.h  \
$(HFILESDIR)$(PS)NGAP-Constants.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-Descriptions.c

# decode file rules
NGAP-PDU-DescriptionsDec$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-DescriptionsDec.c \
$(HFILESDIR)$(PS)NGAP-PDU-Descriptions.h  \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)NGAP-PDU-Contents.h  \
$(HFILESDIR)$(PS)NGAP-Constants.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-DescriptionsDec.c

# encode file rules
NGAP-PDU-DescriptionsEnc$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-DescriptionsEnc.c \
$(HFILESDIR)$(PS)NGAP-PDU-Descriptions.h  \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)NGAP-PDU-Contents.h  \
$(HFILESDIR)$(PS)NGAP-Constants.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-DescriptionsEnc.c

# print file rules
NGAP-PDU-DescriptionsPrint$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-DescriptionsPrint.c \
$(HFILESDIR)$(PS)NGAP-PDU-Descriptions.h  \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)NGAP-PDU-Contents.h  \
$(HFILESDIR)$(PS)NGAP-Constants.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-DescriptionsPrint.c

# print-to-string file rules
NGAP-PDU-DescriptionsPrtToStr$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-DescriptionsPrtToStr.c \
$(HFILESDIR)$(PS)NGAP-PDU-Descriptions.h  \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)NGAP-PDU-Contents.h  \
$(HFILESDIR)$(PS)NGAP-Constants.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-DescriptionsPrtToStr.c

# print-to-stream file rules
NGAP-PDU-DescriptionsPrtToStrm$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-DescriptionsPrtToStrm.c \
$(HFILESDIR)$(PS)NGAP-PDU-Descriptions.h  \
$(HFILESDIR)$(PS)NGAP-CommonDataTypes.h $(HFILESDIR)$(PS)NGAP-PDU-Contents.h  \
$(HFILESDIR)$(PS)NGAP-Constants.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-DescriptionsPrtToStrm.c

# .obj -> .lib rules
$(LIBPFX)NGAP$(A) : $(OBJECTS) $(ENCOBJECTS)  \
$(DECOBJECTS) $(PRTOBJECTS) $(P2SOBJECTS) $(P2MOBJECTS)
	$(LIBCMD) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
$(P2SOBJECTS) $(P2MOBJECTS)

clean:
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) $(LIBPFX)NGAP$(A)
