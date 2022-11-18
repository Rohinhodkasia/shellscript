# makefile to build generated files

include ../../platform.mk

# include directories
OSROOTDIR = ..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)c$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
PERSRCDIR = $(OSROOTDIR)$(PS)rtpersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(PERSRCDIR)$(PS)asn1per.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_) -D_TRACE
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(PERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1per$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1per$(LLAEXT) $(LLPFX)asn1rt$(LLAEXT) $(LLSYS)
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
$(P2SOBJECTS) $(P2MOBJECTS) $(LIBPFX)NGAP-CommonDataTypes$(A)

# .c -> .obj rules
# common file rules
NGAP-CommonDataTypes$(OBJ) : $(SRCDIR)$(PS)NGAP-CommonDataTypes.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-CommonDataTypes.c

# decode file rules
NGAP-CommonDataTypesDec$(OBJ) : $(SRCDIR)$(PS)NGAP-CommonDataTypesDec.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-CommonDataTypesDec.c

# encode file rules
NGAP-CommonDataTypesEnc$(OBJ) : $(SRCDIR)$(PS)NGAP-CommonDataTypesEnc.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-CommonDataTypesEnc.c

# print file rules
NGAP-CommonDataTypesPrint$(OBJ) : $(SRCDIR)$(PS)NGAP-CommonDataTypesPrint.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-CommonDataTypesPrint.c

# print-to-string file rules
NGAP-CommonDataTypesPrtToStr$(OBJ) : $(SRCDIR)$(PS)NGAP-CommonDataTypesPrtToStr.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-CommonDataTypesPrtToStr.c

# print-to-stream file rules
NGAP-CommonDataTypesPrtToStrm$(OBJ) : $(SRCDIR)$(PS)NGAP-CommonDataTypesPrtToStrm.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-CommonDataTypesPrtToStrm.c

# common file rules
NGAP-IEs$(OBJ) : $(SRCDIR)$(PS)NGAP-IEs.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-IEs.c

# decode file rules
NGAP-IEsDec$(OBJ) : $(SRCDIR)$(PS)NGAP-IEsDec.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-IEsDec.c

# encode file rules
NGAP-IEsEnc$(OBJ) : $(SRCDIR)$(PS)NGAP-IEsEnc.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-IEsEnc.c

# print file rules
NGAP-IEsPrint$(OBJ) : $(SRCDIR)$(PS)NGAP-IEsPrint.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-IEsPrint.c

# print-to-string file rules
NGAP-IEsPrtToStr$(OBJ) : $(SRCDIR)$(PS)NGAP-IEsPrtToStr.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-IEsPrtToStr.c

# print-to-stream file rules
NGAP-IEsPrtToStrm$(OBJ) : $(SRCDIR)$(PS)NGAP-IEsPrtToStrm.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-IEsPrtToStrm.c

# common file rules
NGAP-PDU-Contents$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-Contents.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-Contents.c

# decode file rules
NGAP-PDU-ContentsDec$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-ContentsDec.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-ContentsDec.c

# encode file rules
NGAP-PDU-ContentsEnc$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-ContentsEnc.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-ContentsEnc.c

# print file rules
NGAP-PDU-ContentsPrint$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-ContentsPrint.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-ContentsPrint.c

# print-to-string file rules
NGAP-PDU-ContentsPrtToStr$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-ContentsPrtToStr.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-ContentsPrtToStr.c

# print-to-stream file rules
NGAP-PDU-ContentsPrtToStrm$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-ContentsPrtToStrm.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-ContentsPrtToStrm.c

# common file rules
NGAP-PDU-Descriptions$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-Descriptions.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-Descriptions.c

# decode file rules
NGAP-PDU-DescriptionsDec$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-DescriptionsDec.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-DescriptionsDec.c

# encode file rules
NGAP-PDU-DescriptionsEnc$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-DescriptionsEnc.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-DescriptionsEnc.c

# print file rules
NGAP-PDU-DescriptionsPrint$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-DescriptionsPrint.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-DescriptionsPrint.c

# print-to-string file rules
NGAP-PDU-DescriptionsPrtToStr$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-DescriptionsPrtToStr.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-DescriptionsPrtToStr.c

# print-to-stream file rules
NGAP-PDU-DescriptionsPrtToStrm$(OBJ) : $(SRCDIR)$(PS)NGAP-PDU-DescriptionsPrtToStrm.c \
$(HFILESDIR)$(PS)rtkey.h $(HFILESDIR)$(PS).h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NGAP-PDU-DescriptionsPrtToStrm.c

# .obj -> .lib rules
$(LIBPFX)NGAP-CommonDataTypes$(A) : $(OBJECTS) $(ENCOBJECTS)  \
$(DECOBJECTS) $(PRTOBJECTS) $(P2SOBJECTS) $(P2MOBJECTS)
	$(LIBCMD) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
$(P2SOBJECTS) $(P2MOBJECTS)

# .asn -> .c .h rules
$(SRCDIR)/NGAP-CommonDataTypesEnc.c \
$(SRCDIR)/NGAP-CommonDataTypesDec.c \
$(SRCDIR)/NGAP-CommonDataTypes.c \
$(SRCDIR)/NGAP-CommonDataTypesPrint.c \
$(SRCDIR)/NGAP-CommonDataTypesPrtToStr.c \
$(SRCDIR)/NGAP-CommonDataTypesPrtToStrm.c \
$(SRCDIR)/NGAP-IEsEnc.c \
$(SRCDIR)/NGAP-IEsDec.c \
$(SRCDIR)/NGAP-IEs.c \
$(SRCDIR)/NGAP-IEsPrint.c \
$(SRCDIR)/NGAP-IEsPrtToStr.c \
$(SRCDIR)/NGAP-IEsPrtToStrm.c \
$(SRCDIR)/NGAP-PDU-ContentsEnc.c \
$(SRCDIR)/NGAP-PDU-ContentsDec.c \
$(SRCDIR)/NGAP-PDU-Contents.c \
$(SRCDIR)/NGAP-PDU-ContentsPrint.c \
$(SRCDIR)/NGAP-PDU-ContentsPrtToStr.c \
$(SRCDIR)/NGAP-PDU-ContentsPrtToStrm.c \
$(SRCDIR)/NGAP-PDU-DescriptionsEnc.c \
$(SRCDIR)/NGAP-PDU-DescriptionsDec.c \
$(SRCDIR)/NGAP-PDU-Descriptions.c \
$(SRCDIR)/NGAP-PDU-DescriptionsPrint.c \
$(SRCDIR)/NGAP-PDU-DescriptionsPrtToStr.c \
$(SRCDIR)/NGAP-PDU-DescriptionsPrtToStrm.c \
$(HFILESDIR)$(PS)rtkey.h \
$(HFILESDIR)$(PS).h \
: ./NGAP-CommonDataTypes.asn1 ./NGAP-Constants.asn1 ./NGAP-Containers.asn1 ./NGAP-IEs.asn1 ./NGAP-PDU-Contents.asn1 ./NGAP-PDU-Descriptions.asn1 $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(OSROOTDIR)$(PS)bin$(PS)asn1c ./NGAP-CommonDataTypes.asn1 ./NGAP-Constants.asn1 ./NGAP-Containers.asn1 ./NGAP-IEs.asn1 ./NGAP-PDU-Contents.asn1 ./NGAP-PDU-Descriptions.asn1 -c -per -hfile .h -print -prtfmt details -prttostr -prtfmt details -prttostrm -prtfmt details -strict-size -table-unions -trace -fqtvalue

clean:
	$(RM) NGAP-CommonDataTypesEnc.c
	$(RM) NGAP-CommonDataTypesDec.c
	$(RM) NGAP-CommonDataTypes.c
	$(RM) NGAP-CommonDataTypesPrint.c
	$(RM) NGAP-CommonDataTypesPrtToStr.c
	$(RM) NGAP-CommonDataTypesPrtToStrm.c
	$(RM) NGAP-IEsEnc.c
	$(RM) NGAP-IEsDec.c
	$(RM) NGAP-IEs.c
	$(RM) NGAP-IEsPrint.c
	$(RM) NGAP-IEsPrtToStr.c
	$(RM) NGAP-IEsPrtToStrm.c
	$(RM) NGAP-PDU-ContentsEnc.c
	$(RM) NGAP-PDU-ContentsDec.c
	$(RM) NGAP-PDU-Contents.c
	$(RM) NGAP-PDU-ContentsPrint.c
	$(RM) NGAP-PDU-ContentsPrtToStr.c
	$(RM) NGAP-PDU-ContentsPrtToStrm.c
	$(RM) NGAP-PDU-DescriptionsEnc.c
	$(RM) NGAP-PDU-DescriptionsDec.c
	$(RM) NGAP-PDU-Descriptions.c
	$(RM) NGAP-PDU-DescriptionsPrint.c
	$(RM) NGAP-PDU-DescriptionsPrtToStr.c
	$(RM) NGAP-PDU-DescriptionsPrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) $(HFILESDIR)$(PS).h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) $(LIBPFX)NGAP-CommonDataTypes$(A)
