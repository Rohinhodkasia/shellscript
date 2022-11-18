# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

SPECSDIR = ..$(PS)..$(PS)..$(PS)specs$(PS)IEEE_1609_2

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)cpp$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
OERSRCDIR = $(OSROOTDIR)$(PS)rtoersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(RTSRCDIR)$(PS)asn1CppTypes.h  \
$(OERSRCDIR)$(PS)asn1oer.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_) -D_TRACE
CCFLAGS = -c $(CVARS_) $(CCFLAGS_) $(CBLDTYPE_) -D_TRACE
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(SPECSDIR) -I$(RTSRCDIR) \
-I$(OERSRCDIR) $(IPATHS_)
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

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
 $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h \
$(HFILESDIR)$(PS)IEEE1609dot2-Peer2Peer.h $(HFILESDIR)$(PS)IEEE1609dot2.h \
$(HFILESDIR)$(PS)IEEE1609dot2CrlBaseTypes.h \
$(HFILESDIR)$(PS)IEEE1609dot2Crl.h $(HFILESDIR)$(PS)IEEE1609dot2CrlSsp.h \
$(HFILESDIR)$(PS)IEEE1609dot2WsaProtocol.h \
$(HFILESDIR)$(PS)IEEE1609dot2WsaSsp.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .cpp .h rules
$(SRCDIR)/IEEE1609dot2BaseTypesEnc.cpp \
$(SRCDIR)/IEEE1609dot2BaseTypesDec.cpp \
$(SRCDIR)/IEEE1609dot2BaseTypes.cpp \
$(SRCDIR)/IEEE1609dot2BaseTypesPrint.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h \
$(SRCDIR)/IEEE1609dot2-Peer2PeerEnc.cpp \
$(SRCDIR)/IEEE1609dot2-Peer2PeerDec.cpp \
$(SRCDIR)/IEEE1609dot2-Peer2Peer.cpp \
$(SRCDIR)/IEEE1609dot2-Peer2PeerPrint.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2-Peer2Peer.h \
$(SRCDIR)/IEEE1609dot2Enc.cpp \
$(SRCDIR)/IEEE1609dot2Dec.cpp \
$(SRCDIR)/IEEE1609dot2.cpp \
$(SRCDIR)/IEEE1609dot2Print.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2.h \
$(SRCDIR)/IEEE1609dot2CrlBaseTypesEnc.cpp \
$(SRCDIR)/IEEE1609dot2CrlBaseTypesDec.cpp \
$(SRCDIR)/IEEE1609dot2CrlBaseTypes.cpp \
$(SRCDIR)/IEEE1609dot2CrlBaseTypesPrint.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2CrlBaseTypes.h \
$(SRCDIR)/IEEE1609dot2CrlEnc.cpp \
$(SRCDIR)/IEEE1609dot2CrlDec.cpp \
$(SRCDIR)/IEEE1609dot2Crl.cpp \
$(SRCDIR)/IEEE1609dot2CrlPrint.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2Crl.h \
$(SRCDIR)/IEEE1609dot2CrlSspEnc.cpp \
$(SRCDIR)/IEEE1609dot2CrlSspDec.cpp \
$(SRCDIR)/IEEE1609dot2CrlSsp.cpp \
$(SRCDIR)/IEEE1609dot2CrlSspPrint.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2CrlSsp.h \
$(SRCDIR)/IEEE1609dot2WsaProtocolEnc.cpp \
$(SRCDIR)/IEEE1609dot2WsaProtocolDec.cpp \
$(SRCDIR)/IEEE1609dot2WsaProtocol.cpp \
$(SRCDIR)/IEEE1609dot2WsaProtocolPrint.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2WsaProtocol.h \
$(SRCDIR)/IEEE1609dot2WsaSspEnc.cpp \
$(SRCDIR)/IEEE1609dot2WsaSspDec.cpp \
$(SRCDIR)/IEEE1609dot2WsaSsp.cpp \
$(SRCDIR)/IEEE1609dot2WsaSspPrint.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2WsaSsp.h \
$(HFILESDIR)$(PS)rtkey.h \
: $(SPECSDIR)$(PS)1609dot2-base-types.asn $(SPECSDIR)$(PS)1609dot2-P2P.asn $(SPECSDIR)$(PS)1609dot2-schema.asn $(SPECSDIR)$(PS)crl-base-types.asn $(SPECSDIR)$(PS)crl-protocol.asn $(SPECSDIR)$(PS)crl-ssp.asn $(SPECSDIR)$(PS)wsa-protocol.asn $(SPECSDIR)$(PS)wsa-ssp.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(ASN1C) $(SPECSDIR)$(PS)1609dot2-base-types.asn $(SPECSDIR)$(PS)1609dot2-P2P.asn $(SPECSDIR)$(PS)1609dot2-schema.asn $(SPECSDIR)$(PS)crl-base-types.asn $(SPECSDIR)$(PS)crl-protocol.asn $(SPECSDIR)$(PS)crl-ssp.asn $(SPECSDIR)$(PS)wsa-protocol.asn $(SPECSDIR)$(PS)wsa-ssp.asn -cpp -oer -I $(SPECSDIR) -pdu Certificate -print -table-unions -trace

depends: IEEE1609dot2BaseTypes.cpp IEEE1609dot2-Peer2Peer.cpp \
IEEE1609dot2.cpp IEEE1609dot2CrlBaseTypes.cpp IEEE1609dot2Crl.cpp \
IEEE1609dot2CrlSsp.cpp IEEE1609dot2WsaProtocol.cpp IEEE1609dot2WsaSsp.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) IEEE1609dot2BaseTypesEnc.cpp
	$(RM) IEEE1609dot2BaseTypesDec.cpp
	$(RM) IEEE1609dot2BaseTypes.cpp
	$(RM) IEEE1609dot2BaseTypesPrint.cpp
	$(RM) $(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h 
	$(RM) IEEE1609dot2-Peer2PeerEnc.cpp
	$(RM) IEEE1609dot2-Peer2PeerDec.cpp
	$(RM) IEEE1609dot2-Peer2Peer.cpp
	$(RM) IEEE1609dot2-Peer2PeerPrint.cpp
	$(RM) $(HFILESDIR)$(PS)IEEE1609dot2-Peer2Peer.h 
	$(RM) IEEE1609dot2Enc.cpp
	$(RM) IEEE1609dot2Dec.cpp
	$(RM) IEEE1609dot2.cpp
	$(RM) IEEE1609dot2Print.cpp
	$(RM) $(HFILESDIR)$(PS)IEEE1609dot2.h 
	$(RM) IEEE1609dot2CrlBaseTypesEnc.cpp
	$(RM) IEEE1609dot2CrlBaseTypesDec.cpp
	$(RM) IEEE1609dot2CrlBaseTypes.cpp
	$(RM) IEEE1609dot2CrlBaseTypesPrint.cpp
	$(RM) $(HFILESDIR)$(PS)IEEE1609dot2CrlBaseTypes.h 
	$(RM) IEEE1609dot2CrlEnc.cpp
	$(RM) IEEE1609dot2CrlDec.cpp
	$(RM) IEEE1609dot2Crl.cpp
	$(RM) IEEE1609dot2CrlPrint.cpp
	$(RM) $(HFILESDIR)$(PS)IEEE1609dot2Crl.h 
	$(RM) IEEE1609dot2CrlSspEnc.cpp
	$(RM) IEEE1609dot2CrlSspDec.cpp
	$(RM) IEEE1609dot2CrlSsp.cpp
	$(RM) IEEE1609dot2CrlSspPrint.cpp
	$(RM) $(HFILESDIR)$(PS)IEEE1609dot2CrlSsp.h 
	$(RM) IEEE1609dot2WsaProtocolEnc.cpp
	$(RM) IEEE1609dot2WsaProtocolDec.cpp
	$(RM) IEEE1609dot2WsaProtocol.cpp
	$(RM) IEEE1609dot2WsaProtocolPrint.cpp
	$(RM) $(HFILESDIR)$(PS)IEEE1609dot2WsaProtocol.h 
	$(RM) IEEE1609dot2WsaSspEnc.cpp
	$(RM) IEEE1609dot2WsaSspDec.cpp
	$(RM) IEEE1609dot2WsaSsp.cpp
	$(RM) IEEE1609dot2WsaSspPrint.cpp
	$(RM) $(HFILESDIR)$(PS)IEEE1609dot2WsaSsp.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.dat

