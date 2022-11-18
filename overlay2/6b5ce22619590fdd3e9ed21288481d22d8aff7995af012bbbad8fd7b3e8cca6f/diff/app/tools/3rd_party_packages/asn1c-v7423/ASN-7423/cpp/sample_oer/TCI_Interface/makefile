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
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I../../../specs/TCI_Interface/1609dot3 -I../../../specs/TCI_Interface -I$(RTSRCDIR) -I$(OERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1oer$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1oer$(LLAEXT) $(LLPFX)asn1rt$(LLAEXT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
CITSapplMgmtIDs$(OBJ) \
IEEE-1609-3-WEE$(OBJ) \
IEEE-1609-3-WSA$(OBJ) \
IEEE-1609-3-WSM$(OBJ) \
TCI-16093$(OBJ) \
TCI-16094$(OBJ) \
TCI-29451$(OBJ) \
TCI-80211$(OBJ) \
TCI-CommonTypes$(OBJ) \
TCI-Dispatcher$(OBJ) \
TCI-eventHandling$(OBJ) \
TCI-SutControl$(OBJ) \
TCI-indication$(OBJ) \
TCI-ip$(OBJ) \
TCI-responseInfo$(OBJ) \
TCI-wsm$(OBJ)

ENCOBJECTS =  \
CITSapplMgmtIDsEnc$(OBJ) \
IEEE-1609-3-WEEEnc$(OBJ) \
IEEE-1609-3-WSAEnc$(OBJ) \
IEEE-1609-3-WSMEnc$(OBJ) \
TCI-16093Enc$(OBJ) \
TCI-16094Enc$(OBJ) \
TCI-29451Enc$(OBJ) \
TCI-80211Enc$(OBJ) \
TCI-CommonTypesEnc$(OBJ) \
TCI-DispatcherEnc$(OBJ) \
TCI-eventHandlingEnc$(OBJ) \
TCI-SutControlEnc$(OBJ) \
TCI-indicationEnc$(OBJ) \
TCI-ipEnc$(OBJ) \
TCI-responseInfoEnc$(OBJ) \
TCI-wsmEnc$(OBJ)

DECOBJECTS =  \
CITSapplMgmtIDsDec$(OBJ) \
IEEE-1609-3-WEEDec$(OBJ) \
IEEE-1609-3-WSADec$(OBJ) \
IEEE-1609-3-WSMDec$(OBJ) \
TCI-16093Dec$(OBJ) \
TCI-16094Dec$(OBJ) \
TCI-29451Dec$(OBJ) \
TCI-80211Dec$(OBJ) \
TCI-CommonTypesDec$(OBJ) \
TCI-DispatcherDec$(OBJ) \
TCI-eventHandlingDec$(OBJ) \
TCI-SutControlDec$(OBJ) \
TCI-indicationDec$(OBJ) \
TCI-ipDec$(OBJ) \
TCI-responseInfoDec$(OBJ) \
TCI-wsmDec$(OBJ)

PRTOBJECTS =  \
CITSapplMgmtIDsPrint$(OBJ) \
IEEE-1609-3-WEEPrint$(OBJ) \
IEEE-1609-3-WSAPrint$(OBJ) \
IEEE-1609-3-WSMPrint$(OBJ) \
TCI-16093Print$(OBJ) \
TCI-16094Print$(OBJ) \
TCI-29451Print$(OBJ) \
TCI-80211Print$(OBJ) \
TCI-CommonTypesPrint$(OBJ) \
TCI-DispatcherPrint$(OBJ) \
TCI-eventHandlingPrint$(OBJ) \
TCI-SutControlPrint$(OBJ) \
TCI-indicationPrint$(OBJ) \
TCI-ipPrint$(OBJ) \
TCI-responseInfoPrint$(OBJ) \
TCI-wsmPrint$(OBJ)

P2MOBJECTS =  \
CITSapplMgmtIDsPrtToStrm$(OBJ) \
IEEE-1609-3-WEEPrtToStrm$(OBJ) \
IEEE-1609-3-WSAPrtToStrm$(OBJ) \
IEEE-1609-3-WSMPrtToStrm$(OBJ) \
TCI-16093PrtToStrm$(OBJ) \
TCI-16094PrtToStrm$(OBJ) \
TCI-29451PrtToStrm$(OBJ) \
TCI-80211PrtToStrm$(OBJ) \
TCI-CommonTypesPrtToStrm$(OBJ) \
TCI-DispatcherPrtToStrm$(OBJ) \
TCI-eventHandlingPrtToStrm$(OBJ) \
TCI-SutControlPrtToStrm$(OBJ) \
TCI-indicationPrtToStrm$(OBJ) \
TCI-ipPrtToStrm$(OBJ) \
TCI-responseInfoPrtToStrm$(OBJ) \
TCI-wsmPrtToStrm$(OBJ)

TESTOBJECTS =  \
CITSapplMgmtIDsTest$(OBJ) \
IEEE-1609-3-WEETest$(OBJ) \
IEEE-1609-3-WSATest$(OBJ) \
IEEE-1609-3-WSMTest$(OBJ) \
TCI-16093Test$(OBJ) \
TCI-16094Test$(OBJ) \
TCI-29451Test$(OBJ) \
TCI-80211Test$(OBJ) \
TCI-CommonTypesTest$(OBJ) \
TCI-DispatcherTest$(OBJ) \
TCI-eventHandlingTest$(OBJ) \
TCI-SutControlTest$(OBJ) \
TCI-indicationTest$(OBJ) \
TCI-ipTest$(OBJ) \
TCI-responseInfoTest$(OBJ) \
TCI-wsmTest$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
$(P2MOBJECTS) $(TESTOBJECTS) writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
 $(TESTOBJECTS) $(PRTOBJECTS) $(P2MOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS) $(P2MOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)CITSapplMgmtIDs.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WSA.h $(HFILESDIR)$(PS)IEEE-1609-3-WSM.h $(HFILESDIR)$(PS)TCI-16093.h  \
$(HFILESDIR)$(PS)TCI-16094.h $(HFILESDIR)$(PS)TCI-29451.h $(HFILESDIR)$(PS)TCI-80211.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)TCI-Dispatcher.h  \
$(HFILESDIR)$(PS)TCI-eventHandling.h $(HFILESDIR)$(PS)TCI-SutControl.h $(HFILESDIR)$(PS)TCI-indication.h  \
$(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)TCI-responseInfo.h $(HFILESDIR)$(PS)TCI-wsm.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)

writer$(OBJ) : $(SRCDIR)$(PS)writer.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)$(PS)writer.cpp

reader$(OBJ) : $(SRCDIR)$(PS)reader.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)$(PS)reader.cpp

# .cpp -> .obj rules
# common file rules
CITSapplMgmtIDs$(OBJ) : $(SRCDIR)$(PS)CITSapplMgmtIDs.cpp \
$(HFILESDIR)$(PS)CITSapplMgmtIDs.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CITSapplMgmtIDs.cpp

# decode file rules
CITSapplMgmtIDsDec$(OBJ) : $(SRCDIR)$(PS)CITSapplMgmtIDsDec.cpp \
$(HFILESDIR)$(PS)CITSapplMgmtIDs.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CITSapplMgmtIDsDec.cpp

# encode file rules
CITSapplMgmtIDsEnc$(OBJ) : $(SRCDIR)$(PS)CITSapplMgmtIDsEnc.cpp \
$(HFILESDIR)$(PS)CITSapplMgmtIDs.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CITSapplMgmtIDsEnc.cpp

# print file rules
CITSapplMgmtIDsPrint$(OBJ) : $(SRCDIR)$(PS)CITSapplMgmtIDsPrint.cpp \
$(HFILESDIR)$(PS)CITSapplMgmtIDs.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CITSapplMgmtIDsPrint.cpp

# print-to-stream file rules
CITSapplMgmtIDsPrtToStrm$(OBJ) : $(SRCDIR)$(PS)CITSapplMgmtIDsPrtToStrm.cpp \
$(HFILESDIR)$(PS)CITSapplMgmtIDs.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CITSapplMgmtIDsPrtToStrm.cpp

# test file rules
CITSapplMgmtIDsTest$(OBJ) : $(SRCDIR)$(PS)CITSapplMgmtIDsTest.cpp \
$(HFILESDIR)$(PS)CITSapplMgmtIDs.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CITSapplMgmtIDsTest.cpp

# common file rules
IEEE-1609-3-WEE$(OBJ) : $(SRCDIR)$(PS)IEEE-1609-3-WEE.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE-1609-3-WEE.cpp

# decode file rules
IEEE-1609-3-WEEDec$(OBJ) : $(SRCDIR)$(PS)IEEE-1609-3-WEEDec.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE-1609-3-WEEDec.cpp

# encode file rules
IEEE-1609-3-WEEEnc$(OBJ) : $(SRCDIR)$(PS)IEEE-1609-3-WEEEnc.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE-1609-3-WEEEnc.cpp

# print file rules
IEEE-1609-3-WEEPrint$(OBJ) : $(SRCDIR)$(PS)IEEE-1609-3-WEEPrint.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE-1609-3-WEEPrint.cpp

# print-to-stream file rules
IEEE-1609-3-WEEPrtToStrm$(OBJ) : $(SRCDIR)$(PS)IEEE-1609-3-WEEPrtToStrm.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE-1609-3-WEEPrtToStrm.cpp

# test file rules
IEEE-1609-3-WEETest$(OBJ) : $(SRCDIR)$(PS)IEEE-1609-3-WEETest.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE-1609-3-WEETest.cpp

# common file rules
IEEE-1609-3-WSA$(OBJ) : $(SRCDIR)$(PS)IEEE-1609-3-WSA.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WSA.h $(HFILESDIR)$(PS)CITSapplMgmtIDs.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE-1609-3-WSA.cpp

# decode file rules
IEEE-1609-3-WSADec$(OBJ) : $(SRCDIR)$(PS)IEEE-1609-3-WSADec.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WSA.h $(HFILESDIR)$(PS)CITSapplMgmtIDs.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE-1609-3-WSADec.cpp

# encode file rules
IEEE-1609-3-WSAEnc$(OBJ) : $(SRCDIR)$(PS)IEEE-1609-3-WSAEnc.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WSA.h $(HFILESDIR)$(PS)CITSapplMgmtIDs.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE-1609-3-WSAEnc.cpp

# print file rules
IEEE-1609-3-WSAPrint$(OBJ) : $(SRCDIR)$(PS)IEEE-1609-3-WSAPrint.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WSA.h $(HFILESDIR)$(PS)CITSapplMgmtIDs.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE-1609-3-WSAPrint.cpp

# print-to-stream file rules
IEEE-1609-3-WSAPrtToStrm$(OBJ) : $(SRCDIR)$(PS)IEEE-1609-3-WSAPrtToStrm.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WSA.h $(HFILESDIR)$(PS)CITSapplMgmtIDs.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE-1609-3-WSAPrtToStrm.cpp

# test file rules
IEEE-1609-3-WSATest$(OBJ) : $(SRCDIR)$(PS)IEEE-1609-3-WSATest.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WSA.h $(HFILESDIR)$(PS)CITSapplMgmtIDs.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE-1609-3-WSATest.cpp

# common file rules
IEEE-1609-3-WSM$(OBJ) : $(SRCDIR)$(PS)IEEE-1609-3-WSM.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WSM.h $(HFILESDIR)$(PS)CITSapplMgmtIDs.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE-1609-3-WSM.cpp

# decode file rules
IEEE-1609-3-WSMDec$(OBJ) : $(SRCDIR)$(PS)IEEE-1609-3-WSMDec.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WSM.h $(HFILESDIR)$(PS)CITSapplMgmtIDs.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE-1609-3-WSMDec.cpp

# encode file rules
IEEE-1609-3-WSMEnc$(OBJ) : $(SRCDIR)$(PS)IEEE-1609-3-WSMEnc.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WSM.h $(HFILESDIR)$(PS)CITSapplMgmtIDs.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE-1609-3-WSMEnc.cpp

# print file rules
IEEE-1609-3-WSMPrint$(OBJ) : $(SRCDIR)$(PS)IEEE-1609-3-WSMPrint.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WSM.h $(HFILESDIR)$(PS)CITSapplMgmtIDs.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE-1609-3-WSMPrint.cpp

# print-to-stream file rules
IEEE-1609-3-WSMPrtToStrm$(OBJ) : $(SRCDIR)$(PS)IEEE-1609-3-WSMPrtToStrm.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WSM.h $(HFILESDIR)$(PS)CITSapplMgmtIDs.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE-1609-3-WSMPrtToStrm.cpp

# test file rules
IEEE-1609-3-WSMTest$(OBJ) : $(SRCDIR)$(PS)IEEE-1609-3-WSMTest.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WSM.h $(HFILESDIR)$(PS)CITSapplMgmtIDs.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IEEE-1609-3-WSMTest.cpp

# common file rules
TCI-16093$(OBJ) : $(SRCDIR)$(PS)TCI-16093.cpp \
$(HFILESDIR)$(PS)TCI-16093.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)TCI-responseInfo.h  \
$(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-16093.cpp

# decode file rules
TCI-16093Dec$(OBJ) : $(SRCDIR)$(PS)TCI-16093Dec.cpp \
$(HFILESDIR)$(PS)TCI-16093.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)TCI-responseInfo.h  \
$(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-16093Dec.cpp

# encode file rules
TCI-16093Enc$(OBJ) : $(SRCDIR)$(PS)TCI-16093Enc.cpp \
$(HFILESDIR)$(PS)TCI-16093.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)TCI-responseInfo.h  \
$(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-16093Enc.cpp

# print file rules
TCI-16093Print$(OBJ) : $(SRCDIR)$(PS)TCI-16093Print.cpp \
$(HFILESDIR)$(PS)TCI-16093.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)TCI-responseInfo.h  \
$(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-16093Print.cpp

# print-to-stream file rules
TCI-16093PrtToStrm$(OBJ) : $(SRCDIR)$(PS)TCI-16093PrtToStrm.cpp \
$(HFILESDIR)$(PS)TCI-16093.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)TCI-responseInfo.h  \
$(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-16093PrtToStrm.cpp

# test file rules
TCI-16093Test$(OBJ) : $(SRCDIR)$(PS)TCI-16093Test.cpp \
$(HFILESDIR)$(PS)TCI-16093.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)TCI-responseInfo.h  \
$(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-16093Test.cpp

# common file rules
TCI-16094$(OBJ) : $(SRCDIR)$(PS)TCI-16094.cpp \
$(HFILESDIR)$(PS)TCI-16094.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)TCI-responseInfo.h  \
$(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-16094.cpp

# decode file rules
TCI-16094Dec$(OBJ) : $(SRCDIR)$(PS)TCI-16094Dec.cpp \
$(HFILESDIR)$(PS)TCI-16094.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)TCI-responseInfo.h  \
$(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-16094Dec.cpp

# encode file rules
TCI-16094Enc$(OBJ) : $(SRCDIR)$(PS)TCI-16094Enc.cpp \
$(HFILESDIR)$(PS)TCI-16094.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)TCI-responseInfo.h  \
$(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-16094Enc.cpp

# print file rules
TCI-16094Print$(OBJ) : $(SRCDIR)$(PS)TCI-16094Print.cpp \
$(HFILESDIR)$(PS)TCI-16094.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)TCI-responseInfo.h  \
$(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-16094Print.cpp

# print-to-stream file rules
TCI-16094PrtToStrm$(OBJ) : $(SRCDIR)$(PS)TCI-16094PrtToStrm.cpp \
$(HFILESDIR)$(PS)TCI-16094.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)TCI-responseInfo.h  \
$(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-16094PrtToStrm.cpp

# test file rules
TCI-16094Test$(OBJ) : $(SRCDIR)$(PS)TCI-16094Test.cpp \
$(HFILESDIR)$(PS)TCI-16094.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)TCI-responseInfo.h  \
$(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-16094Test.cpp

# common file rules
TCI-29451$(OBJ) : $(SRCDIR)$(PS)TCI-29451.cpp \
$(HFILESDIR)$(PS)TCI-29451.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-indication.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-29451.cpp

# decode file rules
TCI-29451Dec$(OBJ) : $(SRCDIR)$(PS)TCI-29451Dec.cpp \
$(HFILESDIR)$(PS)TCI-29451.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-indication.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-29451Dec.cpp

# encode file rules
TCI-29451Enc$(OBJ) : $(SRCDIR)$(PS)TCI-29451Enc.cpp \
$(HFILESDIR)$(PS)TCI-29451.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-indication.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-29451Enc.cpp

# print file rules
TCI-29451Print$(OBJ) : $(SRCDIR)$(PS)TCI-29451Print.cpp \
$(HFILESDIR)$(PS)TCI-29451.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-indication.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-29451Print.cpp

# print-to-stream file rules
TCI-29451PrtToStrm$(OBJ) : $(SRCDIR)$(PS)TCI-29451PrtToStrm.cpp \
$(HFILESDIR)$(PS)TCI-29451.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-indication.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-29451PrtToStrm.cpp

# test file rules
TCI-29451Test$(OBJ) : $(SRCDIR)$(PS)TCI-29451Test.cpp \
$(HFILESDIR)$(PS)TCI-29451.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-indication.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-29451Test.cpp

# common file rules
TCI-80211$(OBJ) : $(SRCDIR)$(PS)TCI-80211.cpp \
$(HFILESDIR)$(PS)TCI-80211.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-80211.cpp

# decode file rules
TCI-80211Dec$(OBJ) : $(SRCDIR)$(PS)TCI-80211Dec.cpp \
$(HFILESDIR)$(PS)TCI-80211.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-80211Dec.cpp

# encode file rules
TCI-80211Enc$(OBJ) : $(SRCDIR)$(PS)TCI-80211Enc.cpp \
$(HFILESDIR)$(PS)TCI-80211.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-80211Enc.cpp

# print file rules
TCI-80211Print$(OBJ) : $(SRCDIR)$(PS)TCI-80211Print.cpp \
$(HFILESDIR)$(PS)TCI-80211.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-80211Print.cpp

# print-to-stream file rules
TCI-80211PrtToStrm$(OBJ) : $(SRCDIR)$(PS)TCI-80211PrtToStrm.cpp \
$(HFILESDIR)$(PS)TCI-80211.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-80211PrtToStrm.cpp

# test file rules
TCI-80211Test$(OBJ) : $(SRCDIR)$(PS)TCI-80211Test.cpp \
$(HFILESDIR)$(PS)TCI-80211.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-80211Test.cpp

# common file rules
TCI-CommonTypes$(OBJ) : $(SRCDIR)$(PS)TCI-CommonTypes.cpp \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)CITSapplMgmtIDs.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-CommonTypes.cpp

# decode file rules
TCI-CommonTypesDec$(OBJ) : $(SRCDIR)$(PS)TCI-CommonTypesDec.cpp \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)CITSapplMgmtIDs.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-CommonTypesDec.cpp

# encode file rules
TCI-CommonTypesEnc$(OBJ) : $(SRCDIR)$(PS)TCI-CommonTypesEnc.cpp \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)CITSapplMgmtIDs.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-CommonTypesEnc.cpp

# print file rules
TCI-CommonTypesPrint$(OBJ) : $(SRCDIR)$(PS)TCI-CommonTypesPrint.cpp \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)CITSapplMgmtIDs.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-CommonTypesPrint.cpp

# print-to-stream file rules
TCI-CommonTypesPrtToStrm$(OBJ) : $(SRCDIR)$(PS)TCI-CommonTypesPrtToStrm.cpp \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)CITSapplMgmtIDs.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-CommonTypesPrtToStrm.cpp

# test file rules
TCI-CommonTypesTest$(OBJ) : $(SRCDIR)$(PS)TCI-CommonTypesTest.cpp \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)CITSapplMgmtIDs.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-CommonTypesTest.cpp

# common file rules
TCI-Dispatcher$(OBJ) : $(SRCDIR)$(PS)TCI-Dispatcher.cpp \
$(HFILESDIR)$(PS)TCI-Dispatcher.h $(HFILESDIR)$(PS)TCI-16093.h  \
$(HFILESDIR)$(PS)TCI-16094.h $(HFILESDIR)$(PS)TCI-80211.h $(HFILESDIR)$(PS)TCI-29451.h  \
$(HFILESDIR)$(PS)TCI-SutControl.h $(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-Dispatcher.cpp

# decode file rules
TCI-DispatcherDec$(OBJ) : $(SRCDIR)$(PS)TCI-DispatcherDec.cpp \
$(HFILESDIR)$(PS)TCI-Dispatcher.h $(HFILESDIR)$(PS)TCI-16093.h  \
$(HFILESDIR)$(PS)TCI-16094.h $(HFILESDIR)$(PS)TCI-80211.h $(HFILESDIR)$(PS)TCI-29451.h  \
$(HFILESDIR)$(PS)TCI-SutControl.h $(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-DispatcherDec.cpp

# encode file rules
TCI-DispatcherEnc$(OBJ) : $(SRCDIR)$(PS)TCI-DispatcherEnc.cpp \
$(HFILESDIR)$(PS)TCI-Dispatcher.h $(HFILESDIR)$(PS)TCI-16093.h  \
$(HFILESDIR)$(PS)TCI-16094.h $(HFILESDIR)$(PS)TCI-80211.h $(HFILESDIR)$(PS)TCI-29451.h  \
$(HFILESDIR)$(PS)TCI-SutControl.h $(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-DispatcherEnc.cpp

# print file rules
TCI-DispatcherPrint$(OBJ) : $(SRCDIR)$(PS)TCI-DispatcherPrint.cpp \
$(HFILESDIR)$(PS)TCI-Dispatcher.h $(HFILESDIR)$(PS)TCI-16093.h  \
$(HFILESDIR)$(PS)TCI-16094.h $(HFILESDIR)$(PS)TCI-80211.h $(HFILESDIR)$(PS)TCI-29451.h  \
$(HFILESDIR)$(PS)TCI-SutControl.h $(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-DispatcherPrint.cpp

# print-to-stream file rules
TCI-DispatcherPrtToStrm$(OBJ) : $(SRCDIR)$(PS)TCI-DispatcherPrtToStrm.cpp \
$(HFILESDIR)$(PS)TCI-Dispatcher.h $(HFILESDIR)$(PS)TCI-16093.h  \
$(HFILESDIR)$(PS)TCI-16094.h $(HFILESDIR)$(PS)TCI-80211.h $(HFILESDIR)$(PS)TCI-29451.h  \
$(HFILESDIR)$(PS)TCI-SutControl.h $(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-DispatcherPrtToStrm.cpp

# test file rules
TCI-DispatcherTest$(OBJ) : $(SRCDIR)$(PS)TCI-DispatcherTest.cpp \
$(HFILESDIR)$(PS)TCI-Dispatcher.h $(HFILESDIR)$(PS)TCI-16093.h  \
$(HFILESDIR)$(PS)TCI-16094.h $(HFILESDIR)$(PS)TCI-80211.h $(HFILESDIR)$(PS)TCI-29451.h  \
$(HFILESDIR)$(PS)TCI-SutControl.h $(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-DispatcherTest.cpp

# common file rules
TCI-eventHandling$(OBJ) : $(SRCDIR)$(PS)TCI-eventHandling.cpp \
$(HFILESDIR)$(PS)TCI-eventHandling.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-eventHandling.cpp

# decode file rules
TCI-eventHandlingDec$(OBJ) : $(SRCDIR)$(PS)TCI-eventHandlingDec.cpp \
$(HFILESDIR)$(PS)TCI-eventHandling.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-eventHandlingDec.cpp

# encode file rules
TCI-eventHandlingEnc$(OBJ) : $(SRCDIR)$(PS)TCI-eventHandlingEnc.cpp \
$(HFILESDIR)$(PS)TCI-eventHandling.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-eventHandlingEnc.cpp

# print file rules
TCI-eventHandlingPrint$(OBJ) : $(SRCDIR)$(PS)TCI-eventHandlingPrint.cpp \
$(HFILESDIR)$(PS)TCI-eventHandling.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-eventHandlingPrint.cpp

# print-to-stream file rules
TCI-eventHandlingPrtToStrm$(OBJ) : $(SRCDIR)$(PS)TCI-eventHandlingPrtToStrm.cpp \
$(HFILESDIR)$(PS)TCI-eventHandling.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-eventHandlingPrtToStrm.cpp

# test file rules
TCI-eventHandlingTest$(OBJ) : $(SRCDIR)$(PS)TCI-eventHandlingTest.cpp \
$(HFILESDIR)$(PS)TCI-eventHandling.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-eventHandlingTest.cpp

# common file rules
TCI-SutControl$(OBJ) : $(SRCDIR)$(PS)TCI-SutControl.cpp \
$(HFILESDIR)$(PS)TCI-SutControl.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-responseInfo.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-SutControl.cpp

# decode file rules
TCI-SutControlDec$(OBJ) : $(SRCDIR)$(PS)TCI-SutControlDec.cpp \
$(HFILESDIR)$(PS)TCI-SutControl.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-responseInfo.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-SutControlDec.cpp

# encode file rules
TCI-SutControlEnc$(OBJ) : $(SRCDIR)$(PS)TCI-SutControlEnc.cpp \
$(HFILESDIR)$(PS)TCI-SutControl.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-responseInfo.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-SutControlEnc.cpp

# print file rules
TCI-SutControlPrint$(OBJ) : $(SRCDIR)$(PS)TCI-SutControlPrint.cpp \
$(HFILESDIR)$(PS)TCI-SutControl.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-responseInfo.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-SutControlPrint.cpp

# print-to-stream file rules
TCI-SutControlPrtToStrm$(OBJ) : $(SRCDIR)$(PS)TCI-SutControlPrtToStrm.cpp \
$(HFILESDIR)$(PS)TCI-SutControl.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-responseInfo.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-SutControlPrtToStrm.cpp

# test file rules
TCI-SutControlTest$(OBJ) : $(SRCDIR)$(PS)TCI-SutControlTest.cpp \
$(HFILESDIR)$(PS)TCI-SutControl.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-responseInfo.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-SutControlTest.cpp

# common file rules
TCI-indication$(OBJ) : $(SRCDIR)$(PS)TCI-indication.cpp \
$(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-indication.cpp

# decode file rules
TCI-indicationDec$(OBJ) : $(SRCDIR)$(PS)TCI-indicationDec.cpp \
$(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-indicationDec.cpp

# encode file rules
TCI-indicationEnc$(OBJ) : $(SRCDIR)$(PS)TCI-indicationEnc.cpp \
$(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-indicationEnc.cpp

# print file rules
TCI-indicationPrint$(OBJ) : $(SRCDIR)$(PS)TCI-indicationPrint.cpp \
$(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-indicationPrint.cpp

# print-to-stream file rules
TCI-indicationPrtToStrm$(OBJ) : $(SRCDIR)$(PS)TCI-indicationPrtToStrm.cpp \
$(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-indicationPrtToStrm.cpp

# test file rules
TCI-indicationTest$(OBJ) : $(SRCDIR)$(PS)TCI-indicationTest.cpp \
$(HFILESDIR)$(PS)TCI-indication.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-indicationTest.cpp

# common file rules
TCI-ip$(OBJ) : $(SRCDIR)$(PS)TCI-ip.cpp \
$(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)TCI-eventHandling.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-ip.cpp

# decode file rules
TCI-ipDec$(OBJ) : $(SRCDIR)$(PS)TCI-ipDec.cpp \
$(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)TCI-eventHandling.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-ipDec.cpp

# encode file rules
TCI-ipEnc$(OBJ) : $(SRCDIR)$(PS)TCI-ipEnc.cpp \
$(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)TCI-eventHandling.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-ipEnc.cpp

# print file rules
TCI-ipPrint$(OBJ) : $(SRCDIR)$(PS)TCI-ipPrint.cpp \
$(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)TCI-eventHandling.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-ipPrint.cpp

# print-to-stream file rules
TCI-ipPrtToStrm$(OBJ) : $(SRCDIR)$(PS)TCI-ipPrtToStrm.cpp \
$(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)TCI-eventHandling.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-ipPrtToStrm.cpp

# test file rules
TCI-ipTest$(OBJ) : $(SRCDIR)$(PS)TCI-ipTest.cpp \
$(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)TCI-eventHandling.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-ipTest.cpp

# common file rules
TCI-responseInfo$(OBJ) : $(SRCDIR)$(PS)TCI-responseInfo.cpp \
$(HFILESDIR)$(PS)TCI-responseInfo.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-responseInfo.cpp

# decode file rules
TCI-responseInfoDec$(OBJ) : $(SRCDIR)$(PS)TCI-responseInfoDec.cpp \
$(HFILESDIR)$(PS)TCI-responseInfo.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-responseInfoDec.cpp

# encode file rules
TCI-responseInfoEnc$(OBJ) : $(SRCDIR)$(PS)TCI-responseInfoEnc.cpp \
$(HFILESDIR)$(PS)TCI-responseInfo.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-responseInfoEnc.cpp

# print file rules
TCI-responseInfoPrint$(OBJ) : $(SRCDIR)$(PS)TCI-responseInfoPrint.cpp \
$(HFILESDIR)$(PS)TCI-responseInfo.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-responseInfoPrint.cpp

# print-to-stream file rules
TCI-responseInfoPrtToStrm$(OBJ) : $(SRCDIR)$(PS)TCI-responseInfoPrtToStrm.cpp \
$(HFILESDIR)$(PS)TCI-responseInfo.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-responseInfoPrtToStrm.cpp

# test file rules
TCI-responseInfoTest$(OBJ) : $(SRCDIR)$(PS)TCI-responseInfoTest.cpp \
$(HFILESDIR)$(PS)TCI-responseInfo.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)TCI-CommonTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-responseInfoTest.cpp

# common file rules
TCI-wsm$(OBJ) : $(SRCDIR)$(PS)TCI-wsm.cpp \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WSA.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-eventHandling.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-wsm.cpp

# decode file rules
TCI-wsmDec$(OBJ) : $(SRCDIR)$(PS)TCI-wsmDec.cpp \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WSA.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-eventHandling.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-wsmDec.cpp

# encode file rules
TCI-wsmEnc$(OBJ) : $(SRCDIR)$(PS)TCI-wsmEnc.cpp \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WSA.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-eventHandling.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-wsmEnc.cpp

# print file rules
TCI-wsmPrint$(OBJ) : $(SRCDIR)$(PS)TCI-wsmPrint.cpp \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WSA.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-eventHandling.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-wsmPrint.cpp

# print-to-stream file rules
TCI-wsmPrtToStrm$(OBJ) : $(SRCDIR)$(PS)TCI-wsmPrtToStrm.cpp \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WSA.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-eventHandling.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-wsmPrtToStrm.cpp

# test file rules
TCI-wsmTest$(OBJ) : $(SRCDIR)$(PS)TCI-wsmTest.cpp \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h  \
$(HFILESDIR)$(PS)IEEE-1609-3-WSA.h $(HFILESDIR)$(PS)TCI-CommonTypes.h  \
$(HFILESDIR)$(PS)TCI-eventHandling.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TCI-wsmTest.cpp

# .asn -> .cpp .h rules
$(SRCDIR)/CITSapplMgmtIDsEnc.cpp \
$(SRCDIR)/CITSapplMgmtIDsDec.cpp \
$(SRCDIR)/CITSapplMgmtIDs.cpp \
$(SRCDIR)/CITSapplMgmtIDsPrint.cpp \
$(SRCDIR)/CITSapplMgmtIDsPrtToStrm.cpp \
$(SRCDIR)/CITSapplMgmtIDsTest.cpp \
$(HFILESDIR)$(PS)CITSapplMgmtIDs.h \
$(SRCDIR)/IEEE-1609-3-WEEEnc.cpp \
$(SRCDIR)/IEEE-1609-3-WEEDec.cpp \
$(SRCDIR)/IEEE-1609-3-WEE.cpp \
$(SRCDIR)/IEEE-1609-3-WEEPrint.cpp \
$(SRCDIR)/IEEE-1609-3-WEEPrtToStrm.cpp \
$(SRCDIR)/IEEE-1609-3-WEETest.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h \
$(SRCDIR)/IEEE-1609-3-WSAEnc.cpp \
$(SRCDIR)/IEEE-1609-3-WSADec.cpp \
$(SRCDIR)/IEEE-1609-3-WSA.cpp \
$(SRCDIR)/IEEE-1609-3-WSAPrint.cpp \
$(SRCDIR)/IEEE-1609-3-WSAPrtToStrm.cpp \
$(SRCDIR)/IEEE-1609-3-WSATest.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WSA.h \
$(SRCDIR)/IEEE-1609-3-WSMEnc.cpp \
$(SRCDIR)/IEEE-1609-3-WSMDec.cpp \
$(SRCDIR)/IEEE-1609-3-WSM.cpp \
$(SRCDIR)/IEEE-1609-3-WSMPrint.cpp \
$(SRCDIR)/IEEE-1609-3-WSMPrtToStrm.cpp \
$(SRCDIR)/IEEE-1609-3-WSMTest.cpp \
$(HFILESDIR)$(PS)IEEE-1609-3-WSM.h \
$(SRCDIR)/TCI-16093Enc.cpp \
$(SRCDIR)/TCI-16093Dec.cpp \
$(SRCDIR)/TCI-16093.cpp \
$(SRCDIR)/TCI-16093Print.cpp \
$(SRCDIR)/TCI-16093PrtToStrm.cpp \
$(SRCDIR)/TCI-16093Test.cpp \
$(HFILESDIR)$(PS)TCI-16093.h \
$(SRCDIR)/TCI-16094Enc.cpp \
$(SRCDIR)/TCI-16094Dec.cpp \
$(SRCDIR)/TCI-16094.cpp \
$(SRCDIR)/TCI-16094Print.cpp \
$(SRCDIR)/TCI-16094PrtToStrm.cpp \
$(SRCDIR)/TCI-16094Test.cpp \
$(HFILESDIR)$(PS)TCI-16094.h \
$(SRCDIR)/TCI-29451Enc.cpp \
$(SRCDIR)/TCI-29451Dec.cpp \
$(SRCDIR)/TCI-29451.cpp \
$(SRCDIR)/TCI-29451Print.cpp \
$(SRCDIR)/TCI-29451PrtToStrm.cpp \
$(SRCDIR)/TCI-29451Test.cpp \
$(HFILESDIR)$(PS)TCI-29451.h \
$(SRCDIR)/TCI-80211Enc.cpp \
$(SRCDIR)/TCI-80211Dec.cpp \
$(SRCDIR)/TCI-80211.cpp \
$(SRCDIR)/TCI-80211Print.cpp \
$(SRCDIR)/TCI-80211PrtToStrm.cpp \
$(SRCDIR)/TCI-80211Test.cpp \
$(HFILESDIR)$(PS)TCI-80211.h \
$(SRCDIR)/TCI-CommonTypesEnc.cpp \
$(SRCDIR)/TCI-CommonTypesDec.cpp \
$(SRCDIR)/TCI-CommonTypes.cpp \
$(SRCDIR)/TCI-CommonTypesPrint.cpp \
$(SRCDIR)/TCI-CommonTypesPrtToStrm.cpp \
$(SRCDIR)/TCI-CommonTypesTest.cpp \
$(HFILESDIR)$(PS)TCI-CommonTypes.h \
$(SRCDIR)/TCI-DispatcherEnc.cpp \
$(SRCDIR)/TCI-DispatcherDec.cpp \
$(SRCDIR)/TCI-Dispatcher.cpp \
$(SRCDIR)/TCI-DispatcherPrint.cpp \
$(SRCDIR)/TCI-DispatcherPrtToStrm.cpp \
$(SRCDIR)/TCI-DispatcherTest.cpp \
$(HFILESDIR)$(PS)TCI-Dispatcher.h \
$(SRCDIR)/TCI-eventHandlingEnc.cpp \
$(SRCDIR)/TCI-eventHandlingDec.cpp \
$(SRCDIR)/TCI-eventHandling.cpp \
$(SRCDIR)/TCI-eventHandlingPrint.cpp \
$(SRCDIR)/TCI-eventHandlingPrtToStrm.cpp \
$(SRCDIR)/TCI-eventHandlingTest.cpp \
$(HFILESDIR)$(PS)TCI-eventHandling.h \
$(SRCDIR)/TCI-SutControlEnc.cpp \
$(SRCDIR)/TCI-SutControlDec.cpp \
$(SRCDIR)/TCI-SutControl.cpp \
$(SRCDIR)/TCI-SutControlPrint.cpp \
$(SRCDIR)/TCI-SutControlPrtToStrm.cpp \
$(SRCDIR)/TCI-SutControlTest.cpp \
$(HFILESDIR)$(PS)TCI-SutControl.h \
$(SRCDIR)/TCI-indicationEnc.cpp \
$(SRCDIR)/TCI-indicationDec.cpp \
$(SRCDIR)/TCI-indication.cpp \
$(SRCDIR)/TCI-indicationPrint.cpp \
$(SRCDIR)/TCI-indicationPrtToStrm.cpp \
$(SRCDIR)/TCI-indicationTest.cpp \
$(HFILESDIR)$(PS)TCI-indication.h \
$(SRCDIR)/TCI-ipEnc.cpp \
$(SRCDIR)/TCI-ipDec.cpp \
$(SRCDIR)/TCI-ip.cpp \
$(SRCDIR)/TCI-ipPrint.cpp \
$(SRCDIR)/TCI-ipPrtToStrm.cpp \
$(SRCDIR)/TCI-ipTest.cpp \
$(HFILESDIR)$(PS)TCI-ip.h \
$(SRCDIR)/TCI-responseInfoEnc.cpp \
$(SRCDIR)/TCI-responseInfoDec.cpp \
$(SRCDIR)/TCI-responseInfo.cpp \
$(SRCDIR)/TCI-responseInfoPrint.cpp \
$(SRCDIR)/TCI-responseInfoPrtToStrm.cpp \
$(SRCDIR)/TCI-responseInfoTest.cpp \
$(HFILESDIR)$(PS)TCI-responseInfo.h \
$(SRCDIR)/TCI-wsmEnc.cpp \
$(SRCDIR)/TCI-wsmDec.cpp \
$(SRCDIR)/TCI-wsm.cpp \
$(SRCDIR)/TCI-wsmPrint.cpp \
$(SRCDIR)/TCI-wsmPrtToStrm.cpp \
$(SRCDIR)/TCI-wsmTest.cpp \
$(HFILESDIR)$(PS)TCI-wsm.h \
$(HFILESDIR)$(PS)rtkey.h \
: ../../../specs/TCI_Interface/1609dot3/17419_CITSapplMgmtIDs_v1.asn ../../../specs/TCI_Interface/1609dot3/wee.asn ../../../specs/TCI_Interface/1609dot3/wsa.asn ../../../specs/TCI_Interface/1609dot3/wsm.asn ../../../specs/TCI_Interface/TCI16093.asn ../../../specs/TCI_Interface/TCI16094.asn ../../../specs/TCI_Interface/TCI29451.asn ../../../specs/TCI_Interface/TCI80211.asn ../../../specs/TCI_Interface/TCICommonTypes.asn ../../../specs/TCI_Interface/TCIDispatcher.asn ../../../specs/TCI_Interface/TCIEventHandling.asn ../../../specs/TCI_Interface/TCISutControl.asn ../../../specs/TCI_Interface/TCIindication.asn ../../../specs/TCI_Interface/TCIip.asn ../../../specs/TCI_Interface/TCIresponseInfo.asn ../../../specs/TCI_Interface/TCIwsm.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(OSROOTDIR)$(PS)bin$(PS)asn1c ../../../specs/TCI_Interface/1609dot3/17419_CITSapplMgmtIDs_v1.asn ../../../specs/TCI_Interface/1609dot3/wee.asn ../../../specs/TCI_Interface/1609dot3/wsa.asn ../../../specs/TCI_Interface/1609dot3/wsm.asn ../../../specs/TCI_Interface/TCI16093.asn ../../../specs/TCI_Interface/TCI16094.asn ../../../specs/TCI_Interface/TCI29451.asn ../../../specs/TCI_Interface/TCI80211.asn ../../../specs/TCI_Interface/TCICommonTypes.asn ../../../specs/TCI_Interface/TCIDispatcher.asn ../../../specs/TCI_Interface/TCIEventHandling.asn ../../../specs/TCI_Interface/TCISutControl.asn ../../../specs/TCI_Interface/TCIindication.asn ../../../specs/TCI_Interface/TCIip.asn ../../../specs/TCI_Interface/TCIresponseInfo.asn ../../../specs/TCI_Interface/TCIwsm.asn -cpp -oer -I ../../../specs/TCI_Interface/1609dot3 -I ../../../specs/TCI_Interface -pdu TCIMsg -print -prttostrm -strict-size -table-unions -test -trace -x64

clean:
	$(RM) CITSapplMgmtIDsEnc.cpp
	$(RM) CITSapplMgmtIDsDec.cpp
	$(RM) CITSapplMgmtIDs.cpp
	$(RM) CITSapplMgmtIDsPrint.cpp
	$(RM) CITSapplMgmtIDsPrtToStrm.cpp
	$(RM) CITSapplMgmtIDsTest.cpp
	$(RM) $(HFILESDIR)$(PS)CITSapplMgmtIDs.h 
	$(RM) IEEE-1609-3-WEEEnc.cpp
	$(RM) IEEE-1609-3-WEEDec.cpp
	$(RM) IEEE-1609-3-WEE.cpp
	$(RM) IEEE-1609-3-WEEPrint.cpp
	$(RM) IEEE-1609-3-WEEPrtToStrm.cpp
	$(RM) IEEE-1609-3-WEETest.cpp
	$(RM) $(HFILESDIR)$(PS)IEEE-1609-3-WEE.h 
	$(RM) IEEE-1609-3-WSAEnc.cpp
	$(RM) IEEE-1609-3-WSADec.cpp
	$(RM) IEEE-1609-3-WSA.cpp
	$(RM) IEEE-1609-3-WSAPrint.cpp
	$(RM) IEEE-1609-3-WSAPrtToStrm.cpp
	$(RM) IEEE-1609-3-WSATest.cpp
	$(RM) $(HFILESDIR)$(PS)IEEE-1609-3-WSA.h 
	$(RM) IEEE-1609-3-WSMEnc.cpp
	$(RM) IEEE-1609-3-WSMDec.cpp
	$(RM) IEEE-1609-3-WSM.cpp
	$(RM) IEEE-1609-3-WSMPrint.cpp
	$(RM) IEEE-1609-3-WSMPrtToStrm.cpp
	$(RM) IEEE-1609-3-WSMTest.cpp
	$(RM) $(HFILESDIR)$(PS)IEEE-1609-3-WSM.h 
	$(RM) TCI-16093Enc.cpp
	$(RM) TCI-16093Dec.cpp
	$(RM) TCI-16093.cpp
	$(RM) TCI-16093Print.cpp
	$(RM) TCI-16093PrtToStrm.cpp
	$(RM) TCI-16093Test.cpp
	$(RM) $(HFILESDIR)$(PS)TCI-16093.h 
	$(RM) TCI-16094Enc.cpp
	$(RM) TCI-16094Dec.cpp
	$(RM) TCI-16094.cpp
	$(RM) TCI-16094Print.cpp
	$(RM) TCI-16094PrtToStrm.cpp
	$(RM) TCI-16094Test.cpp
	$(RM) $(HFILESDIR)$(PS)TCI-16094.h 
	$(RM) TCI-29451Enc.cpp
	$(RM) TCI-29451Dec.cpp
	$(RM) TCI-29451.cpp
	$(RM) TCI-29451Print.cpp
	$(RM) TCI-29451PrtToStrm.cpp
	$(RM) TCI-29451Test.cpp
	$(RM) $(HFILESDIR)$(PS)TCI-29451.h 
	$(RM) TCI-80211Enc.cpp
	$(RM) TCI-80211Dec.cpp
	$(RM) TCI-80211.cpp
	$(RM) TCI-80211Print.cpp
	$(RM) TCI-80211PrtToStrm.cpp
	$(RM) TCI-80211Test.cpp
	$(RM) $(HFILESDIR)$(PS)TCI-80211.h 
	$(RM) TCI-CommonTypesEnc.cpp
	$(RM) TCI-CommonTypesDec.cpp
	$(RM) TCI-CommonTypes.cpp
	$(RM) TCI-CommonTypesPrint.cpp
	$(RM) TCI-CommonTypesPrtToStrm.cpp
	$(RM) TCI-CommonTypesTest.cpp
	$(RM) $(HFILESDIR)$(PS)TCI-CommonTypes.h 
	$(RM) TCI-DispatcherEnc.cpp
	$(RM) TCI-DispatcherDec.cpp
	$(RM) TCI-Dispatcher.cpp
	$(RM) TCI-DispatcherPrint.cpp
	$(RM) TCI-DispatcherPrtToStrm.cpp
	$(RM) TCI-DispatcherTest.cpp
	$(RM) $(HFILESDIR)$(PS)TCI-Dispatcher.h 
	$(RM) TCI-eventHandlingEnc.cpp
	$(RM) TCI-eventHandlingDec.cpp
	$(RM) TCI-eventHandling.cpp
	$(RM) TCI-eventHandlingPrint.cpp
	$(RM) TCI-eventHandlingPrtToStrm.cpp
	$(RM) TCI-eventHandlingTest.cpp
	$(RM) $(HFILESDIR)$(PS)TCI-eventHandling.h 
	$(RM) TCI-SutControlEnc.cpp
	$(RM) TCI-SutControlDec.cpp
	$(RM) TCI-SutControl.cpp
	$(RM) TCI-SutControlPrint.cpp
	$(RM) TCI-SutControlPrtToStrm.cpp
	$(RM) TCI-SutControlTest.cpp
	$(RM) $(HFILESDIR)$(PS)TCI-SutControl.h 
	$(RM) TCI-indicationEnc.cpp
	$(RM) TCI-indicationDec.cpp
	$(RM) TCI-indication.cpp
	$(RM) TCI-indicationPrint.cpp
	$(RM) TCI-indicationPrtToStrm.cpp
	$(RM) TCI-indicationTest.cpp
	$(RM) $(HFILESDIR)$(PS)TCI-indication.h 
	$(RM) TCI-ipEnc.cpp
	$(RM) TCI-ipDec.cpp
	$(RM) TCI-ip.cpp
	$(RM) TCI-ipPrint.cpp
	$(RM) TCI-ipPrtToStrm.cpp
	$(RM) TCI-ipTest.cpp
	$(RM) $(HFILESDIR)$(PS)TCI-ip.h 
	$(RM) TCI-responseInfoEnc.cpp
	$(RM) TCI-responseInfoDec.cpp
	$(RM) TCI-responseInfo.cpp
	$(RM) TCI-responseInfoPrint.cpp
	$(RM) TCI-responseInfoPrtToStrm.cpp
	$(RM) TCI-responseInfoTest.cpp
	$(RM) $(HFILESDIR)$(PS)TCI-responseInfo.h 
	$(RM) TCI-wsmEnc.cpp
	$(RM) TCI-wsmDec.cpp
	$(RM) TCI-wsm.cpp
	$(RM) TCI-wsmPrint.cpp
	$(RM) TCI-wsmPrtToStrm.cpp
	$(RM) TCI-wsmTest.cpp
	$(RM) $(HFILESDIR)$(PS)TCI-wsm.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) *.exe
	$(RM_MSVC_FILES)
