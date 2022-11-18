# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

SPECSDIR = ..$(PS)..$(PS)..$(PS)specs$(PS)IEEE_1609_2

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)c$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
OERSRCDIR = $(OSROOTDIR)$(PS)rtoersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(OERSRCDIR)$(PS)asn1oer.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_) -D_TRACE
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(OERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1oer$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1oer$(LLAEXT) $(LLPFX)asn1rt$(LLAEXT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
IEEE1609dot2BaseTypes$(OBJ) \
IEEE1609dot2-Peer2Peer$(OBJ) \
IEEE1609dot2$(OBJ) \
IEEE1609dot2CrlBaseTypes$(OBJ) \
IEEE1609dot2Crl$(OBJ) \
IEEE1609dot2CrlSsp$(OBJ) \
IEEE1609dot2WsaProtocol$(OBJ) \
IEEE1609dot2WsaSsp$(OBJ)

ENCOBJECTS =  \
IEEE1609dot2BaseTypesEnc$(OBJ) \
IEEE1609dot2-Peer2PeerEnc$(OBJ) \
IEEE1609dot2Enc$(OBJ) \
IEEE1609dot2CrlBaseTypesEnc$(OBJ) \
IEEE1609dot2CrlEnc$(OBJ) \
IEEE1609dot2CrlSspEnc$(OBJ) \
IEEE1609dot2WsaProtocolEnc$(OBJ) \
IEEE1609dot2WsaSspEnc$(OBJ)

DECOBJECTS =  \
IEEE1609dot2BaseTypesDec$(OBJ) \
IEEE1609dot2-Peer2PeerDec$(OBJ) \
IEEE1609dot2Dec$(OBJ) \
IEEE1609dot2CrlBaseTypesDec$(OBJ) \
IEEE1609dot2CrlDec$(OBJ) \
IEEE1609dot2CrlSspDec$(OBJ) \
IEEE1609dot2WsaProtocolDec$(OBJ) \
IEEE1609dot2WsaSspDec$(OBJ)

PRTOBJECTS =  \
IEEE1609dot2BaseTypesPrint$(OBJ) \
IEEE1609dot2-Peer2PeerPrint$(OBJ) \
IEEE1609dot2Print$(OBJ) \
IEEE1609dot2CrlBaseTypesPrint$(OBJ) \
IEEE1609dot2CrlPrint$(OBJ) \
IEEE1609dot2CrlSspPrint$(OBJ) \
IEEE1609dot2WsaProtocolPrint$(OBJ) \
IEEE1609dot2WsaSspPrint$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h  \
$(HFILESDIR)$(PS)IEEE1609dot2-Peer2Peer.h $(HFILESDIR)$(PS)IEEE1609dot2.h \
$(HFILESDIR)$(PS)IEEE1609dot2CrlBaseTypes.h \
$(HFILESDIR)$(PS)IEEE1609dot2Crl.h $(HFILESDIR)$(PS)IEEE1609dot2CrlSsp.h \
$(HFILESDIR)$(PS)IEEE1609dot2WsaProtocol.h \
$(HFILESDIR)$(PS)IEEE1609dot2WsaSsp.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
$(SRCDIR)/IEEE1609dot2BaseTypesEnc.c \
$(SRCDIR)/IEEE1609dot2BaseTypesDec.c \
$(SRCDIR)/IEEE1609dot2BaseTypes.c \
$(SRCDIR)/IEEE1609dot2BaseTypesPrint.c \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h \
$(SRCDIR)/IEEE1609dot2-Peer2PeerEnc.c \
$(SRCDIR)/IEEE1609dot2-Peer2PeerDec.c \
$(SRCDIR)/IEEE1609dot2-Peer2Peer.c \
$(SRCDIR)/IEEE1609dot2-Peer2PeerPrint.c \
$(HFILESDIR)$(PS)IEEE1609dot2-Peer2Peer.h \
$(SRCDIR)/IEEE1609dot2Enc.c \
$(SRCDIR)/IEEE1609dot2Dec.c \
$(SRCDIR)/IEEE1609dot2.c \
$(SRCDIR)/IEEE1609dot2Print.c \
$(HFILESDIR)$(PS)IEEE1609dot2.h \
$(SRCDIR)/IEEE1609dot2CrlBaseTypesEnc.c \
$(SRCDIR)/IEEE1609dot2CrlBaseTypesDec.c \
$(SRCDIR)/IEEE1609dot2CrlBaseTypes.c \
$(SRCDIR)/IEEE1609dot2CrlBaseTypesPrint.c \
$(HFILESDIR)$(PS)IEEE1609dot2CrlBaseTypes.h \
$(SRCDIR)/IEEE1609dot2CrlEnc.c \
$(SRCDIR)/IEEE1609dot2CrlDec.c \
$(SRCDIR)/IEEE1609dot2Crl.c \
$(SRCDIR)/IEEE1609dot2CrlPrint.c \
$(HFILESDIR)$(PS)IEEE1609dot2Crl.h \
$(SRCDIR)/IEEE1609dot2CrlSspEnc.c \
$(SRCDIR)/IEEE1609dot2CrlSspDec.c \
$(SRCDIR)/IEEE1609dot2CrlSsp.c \
$(SRCDIR)/IEEE1609dot2CrlSspPrint.c \
$(HFILESDIR)$(PS)IEEE1609dot2CrlSsp.h \
$(SRCDIR)/IEEE1609dot2WsaProtocolEnc.c \
$(SRCDIR)/IEEE1609dot2WsaProtocolDec.c \
$(SRCDIR)/IEEE1609dot2WsaProtocol.c \
$(SRCDIR)/IEEE1609dot2WsaProtocolPrint.c \
$(HFILESDIR)$(PS)IEEE1609dot2WsaProtocol.h \
$(SRCDIR)/IEEE1609dot2WsaSspEnc.c \
$(SRCDIR)/IEEE1609dot2WsaSspDec.c \
$(SRCDIR)/IEEE1609dot2WsaSsp.c \
$(SRCDIR)/IEEE1609dot2WsaSspPrint.c \
$(HFILESDIR)$(PS)IEEE1609dot2WsaSsp.h \
$(HFILESDIR)$(PS)rtkey.h \
: $(SPECSDIR)/1609dot2-base-types.asn $(SPECSDIR)/1609dot2-P2P.asn $(SPECSDIR)/1609dot2-schema.asn $(SPECSDIR)/crl-base-types.asn $(SPECSDIR)/crl-protocol.asn $(SPECSDIR)/crl-ssp.asn $(SPECSDIR)/wsa-protocol.asn $(SPECSDIR)/wsa-ssp.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(ASN1C) $(SPECSDIR)/1609dot2-base-types.asn $(SPECSDIR)/1609dot2-P2P.asn $(SPECSDIR)/1609dot2-schema.asn $(SPECSDIR)/crl-base-types.asn $(SPECSDIR)/crl-protocol.asn $(SPECSDIR)/crl-ssp.asn $(SPECSDIR)/wsa-protocol.asn $(SPECSDIR)/wsa-ssp.asn -c -oer -I $(SPECSDIR) -pdu Certificate -print -strict-size -table-unions -trace -fqtvalue

depends: IEEE1609dot2BaseTypes.c IEEE1609dot2-Peer2Peer.c IEEE1609dot2.c \
IEEE1609dot2CrlBaseTypes.c IEEE1609dot2Crl.c IEEE1609dot2CrlSsp.c \
IEEE1609dot2WsaProtocol.c IEEE1609dot2WsaSsp.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) IEEE1609dot2BaseTypesEnc.c
	$(RM) IEEE1609dot2BaseTypesDec.c
	$(RM) IEEE1609dot2BaseTypes.c
	$(RM) IEEE1609dot2BaseTypesPrint.c
	$(RM) $(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h 
	$(RM) IEEE1609dot2-Peer2PeerEnc.c
	$(RM) IEEE1609dot2-Peer2PeerDec.c
	$(RM) IEEE1609dot2-Peer2Peer.c
	$(RM) IEEE1609dot2-Peer2PeerPrint.c
	$(RM) $(HFILESDIR)$(PS)IEEE1609dot2-Peer2Peer.h 
	$(RM) IEEE1609dot2Enc.c
	$(RM) IEEE1609dot2Dec.c
	$(RM) IEEE1609dot2.c
	$(RM) IEEE1609dot2Print.c
	$(RM) $(HFILESDIR)$(PS)IEEE1609dot2.h 
	$(RM) IEEE1609dot2CrlBaseTypesEnc.c
	$(RM) IEEE1609dot2CrlBaseTypesDec.c
	$(RM) IEEE1609dot2CrlBaseTypes.c
	$(RM) IEEE1609dot2CrlBaseTypesPrint.c
	$(RM) $(HFILESDIR)$(PS)IEEE1609dot2CrlBaseTypes.h 
	$(RM) IEEE1609dot2CrlEnc.c
	$(RM) IEEE1609dot2CrlDec.c
	$(RM) IEEE1609dot2Crl.c
	$(RM) IEEE1609dot2CrlPrint.c
	$(RM) $(HFILESDIR)$(PS)IEEE1609dot2Crl.h 
	$(RM) IEEE1609dot2CrlSspEnc.c
	$(RM) IEEE1609dot2CrlSspDec.c
	$(RM) IEEE1609dot2CrlSsp.c
	$(RM) IEEE1609dot2CrlSspPrint.c
	$(RM) $(HFILESDIR)$(PS)IEEE1609dot2CrlSsp.h 
	$(RM) IEEE1609dot2WsaProtocolEnc.c
	$(RM) IEEE1609dot2WsaProtocolDec.c
	$(RM) IEEE1609dot2WsaProtocol.c
	$(RM) IEEE1609dot2WsaProtocolPrint.c
	$(RM) $(HFILESDIR)$(PS)IEEE1609dot2WsaProtocol.h 
	$(RM) IEEE1609dot2WsaSspEnc.c
	$(RM) IEEE1609dot2WsaSspDec.c
	$(RM) IEEE1609dot2WsaSsp.c
	$(RM) IEEE1609dot2WsaSspPrint.c
	$(RM) $(HFILESDIR)$(PS)IEEE1609dot2WsaSsp.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.dat

