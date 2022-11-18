# makefile to build generated files

include ../../platform.mk

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
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I../../../specs/IEEE_1609_2 -I$(RTSRCDIR) -I$(OERSRCDIR) $(IPATHS_)
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

RWHFILES = $(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h  \
$(HFILESDIR)$(PS)IEEE1609dot2-Peer2Peer.h $(HFILESDIR)$(PS)IEEE1609dot2.h  \
$(HFILESDIR)$(PS)IEEE1609dot2CrlBaseTypes.h $(HFILESDIR)$(PS)IEEE1609dot2Crl.h  \
$(HFILESDIR)$(PS)IEEE1609dot2CrlSsp.h $(HFILESDIR)$(PS)IEEE1609dot2WsaProtocol.h  \
$(HFILESDIR)$(PS)IEEE1609dot2WsaSsp.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

writer$(OBJ) : $(SRCDIR)$(PS)writer.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)/writer.cpp

reader$(OBJ) : $(SRCDIR)$(PS)reader.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)/reader.cpp

# .cpp -> .obj rules
# common file rules
IEEE1609dot2BaseTypes$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2BaseTypes.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2BaseTypes.cpp

# decode file rules
IEEE1609dot2BaseTypesDec$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2BaseTypesDec.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2BaseTypesDec.cpp

# encode file rules
IEEE1609dot2BaseTypesEnc$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2BaseTypesEnc.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2BaseTypesEnc.cpp

# print file rules
IEEE1609dot2BaseTypesPrint$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2BaseTypesPrint.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2BaseTypesPrint.cpp

# common file rules
IEEE1609dot2-Peer2Peer$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2-Peer2Peer.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2-Peer2Peer.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)IEEE1609dot2.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2-Peer2Peer.cpp

# decode file rules
IEEE1609dot2-Peer2PeerDec$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2-Peer2PeerDec.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2-Peer2Peer.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)IEEE1609dot2.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2-Peer2PeerDec.cpp

# encode file rules
IEEE1609dot2-Peer2PeerEnc$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2-Peer2PeerEnc.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2-Peer2Peer.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)IEEE1609dot2.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2-Peer2PeerEnc.cpp

# print file rules
IEEE1609dot2-Peer2PeerPrint$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2-Peer2PeerPrint.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2-Peer2Peer.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)IEEE1609dot2.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2-Peer2PeerPrint.cpp

# common file rules
IEEE1609dot2$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2.cpp

# decode file rules
IEEE1609dot2Dec$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2Dec.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2Dec.cpp

# encode file rules
IEEE1609dot2Enc$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2Enc.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2Enc.cpp

# print file rules
IEEE1609dot2Print$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2Print.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2Print.cpp

# common file rules
IEEE1609dot2CrlBaseTypes$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2CrlBaseTypes.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2CrlBaseTypes.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2CrlBaseTypes.cpp

# decode file rules
IEEE1609dot2CrlBaseTypesDec$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2CrlBaseTypesDec.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2CrlBaseTypes.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2CrlBaseTypesDec.cpp

# encode file rules
IEEE1609dot2CrlBaseTypesEnc$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2CrlBaseTypesEnc.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2CrlBaseTypes.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2CrlBaseTypesEnc.cpp

# print file rules
IEEE1609dot2CrlBaseTypesPrint$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2CrlBaseTypesPrint.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2CrlBaseTypes.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2CrlBaseTypesPrint.cpp

# common file rules
IEEE1609dot2Crl$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2Crl.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2Crl.h $(HFILESDIR)$(PS)IEEE1609dot2.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)IEEE1609dot2CrlBaseTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2Crl.cpp

# decode file rules
IEEE1609dot2CrlDec$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2CrlDec.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2Crl.h $(HFILESDIR)$(PS)IEEE1609dot2.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)IEEE1609dot2CrlBaseTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2CrlDec.cpp

# encode file rules
IEEE1609dot2CrlEnc$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2CrlEnc.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2Crl.h $(HFILESDIR)$(PS)IEEE1609dot2.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)IEEE1609dot2CrlBaseTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2CrlEnc.cpp

# print file rules
IEEE1609dot2CrlPrint$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2CrlPrint.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2Crl.h $(HFILESDIR)$(PS)IEEE1609dot2.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)IEEE1609dot2CrlBaseTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2CrlPrint.cpp

# common file rules
IEEE1609dot2CrlSsp$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2CrlSsp.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2CrlSsp.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2CrlSsp.cpp

# decode file rules
IEEE1609dot2CrlSspDec$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2CrlSspDec.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2CrlSsp.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2CrlSspDec.cpp

# encode file rules
IEEE1609dot2CrlSspEnc$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2CrlSspEnc.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2CrlSsp.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2CrlSspEnc.cpp

# print file rules
IEEE1609dot2CrlSspPrint$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2CrlSspPrint.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2CrlSsp.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2CrlSspPrint.cpp

# common file rules
IEEE1609dot2WsaProtocol$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2WsaProtocol.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2WsaProtocol.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2WsaProtocol.cpp

# decode file rules
IEEE1609dot2WsaProtocolDec$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2WsaProtocolDec.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2WsaProtocol.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2WsaProtocolDec.cpp

# encode file rules
IEEE1609dot2WsaProtocolEnc$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2WsaProtocolEnc.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2WsaProtocol.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2WsaProtocolEnc.cpp

# print file rules
IEEE1609dot2WsaProtocolPrint$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2WsaProtocolPrint.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2WsaProtocol.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2WsaProtocolPrint.cpp

# common file rules
IEEE1609dot2WsaSsp$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2WsaSsp.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2WsaSsp.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2WsaSsp.cpp

# decode file rules
IEEE1609dot2WsaSspDec$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2WsaSspDec.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2WsaSsp.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2WsaSspDec.cpp

# encode file rules
IEEE1609dot2WsaSspEnc$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2WsaSspEnc.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2WsaSsp.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2WsaSspEnc.cpp

# print file rules
IEEE1609dot2WsaSspPrint$(OBJ) : $(SRCDIR)$(PS)IEEE1609dot2WsaSspPrint.cpp \
$(HFILESDIR)$(PS)IEEE1609dot2WsaSsp.h  \
$(HFILESDIR)$(PS)IEEE1609dot2BaseTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE1609dot2WsaSspPrint.cpp

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
: ../../../specs/IEEE_1609_2/1609dot2-base-types.asn ../../../specs/IEEE_1609_2/1609dot2-P2P.asn ../../../specs/IEEE_1609_2/1609dot2-schema.asn ../../../specs/IEEE_1609_2/crl-base-types.asn ../../../specs/IEEE_1609_2/crl-protocol.asn ../../../specs/IEEE_1609_2/crl-ssp.asn ../../../specs/IEEE_1609_2/wsa-protocol.asn ../../../specs/IEEE_1609_2/wsa-ssp.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(OSROOTDIR)$(PS)bin$(PS)asn1c ../../../specs/IEEE_1609_2/1609dot2-base-types.asn ../../../specs/IEEE_1609_2/1609dot2-P2P.asn ../../../specs/IEEE_1609_2/1609dot2-schema.asn ../../../specs/IEEE_1609_2/crl-base-types.asn ../../../specs/IEEE_1609_2/crl-protocol.asn ../../../specs/IEEE_1609_2/crl-ssp.asn ../../../specs/IEEE_1609_2/wsa-protocol.asn ../../../specs/IEEE_1609_2/wsa-ssp.asn -cpp -oer -I ../../../specs/IEEE_1609_2 -pdu Certificate -print -table-unions -trace

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

