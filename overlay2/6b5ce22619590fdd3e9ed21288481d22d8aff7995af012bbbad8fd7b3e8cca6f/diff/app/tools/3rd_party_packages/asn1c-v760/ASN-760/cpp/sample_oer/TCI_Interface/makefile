# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

SPECSDIR = ..$(PS)..$(PS)..$(PS)specs$(PS)TCI_Interface

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
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(SPECSDIR)$(PS)1609dot3 -I$(SPECSDIR) \
-I$(RTSRCDIR) -I$(OERSRCDIR) $(IPATHS_)
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

RWHFILES = $(HFILESDIR)$(PS)CITSapplMgmtIDs.h \
$(HFILESDIR)$(PS)IEEE-1609-3-WEE.h $(HFILESDIR)$(PS)IEEE-1609-3-WSA.h \
$(HFILESDIR)$(PS)IEEE-1609-3-WSM.h $(HFILESDIR)$(PS)TCI-16093.h \
$(HFILESDIR)$(PS)TCI-16094.h $(HFILESDIR)$(PS)TCI-29451.h \
$(HFILESDIR)$(PS)TCI-80211.h $(HFILESDIR)$(PS)TCI-CommonTypes.h \
$(HFILESDIR)$(PS)TCI-Dispatcher.h $(HFILESDIR)$(PS)TCI-eventHandling.h \
$(HFILESDIR)$(PS)TCI-SutControl.h $(HFILESDIR)$(PS)TCI-indication.h \
$(HFILESDIR)$(PS)TCI-ip.h $(HFILESDIR)$(PS)TCI-responseInfo.h \
$(HFILESDIR)$(PS)TCI-wsm.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

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
: $(SPECSDIR)$(PS)1609dot3/17419_CITSapplMgmtIDs_v1.asn $(SPECSDIR)$(PS)1609dot3$(PS)wee.asn $(SPECSDIR)$(PS)1609dot3$(PS)wsa.asn $(SPECSDIR)$(PS)1609dot3$(PS)wsm.asn $(SPECSDIR)$(PS)TCI16093.asn $(SPECSDIR)$(PS)TCI16094.asn $(SPECSDIR)$(PS)TCI29451.asn $(SPECSDIR)$(PS)TCI80211.asn $(SPECSDIR)$(PS)TCICommonTypes.asn $(SPECSDIR)$(PS)TCIDispatcher.asn $(SPECSDIR)$(PS)TCIEventHandling.asn $(SPECSDIR)$(PS)TCISutControl.asn $(SPECSDIR)$(PS)TCIindication.asn $(SPECSDIR)$(PS)TCIip.asn $(SPECSDIR)$(PS)TCIresponseInfo.asn $(SPECSDIR)$(PS)TCIwsm.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(ASN1C) $(SPECSDIR)$(PS)1609dot3$(PS)17419_CITSapplMgmtIDs_v1.asn $(SPECSDIR)$(PS)1609dot3$(PS)wee.asn $(SPECSDIR)$(PS)1609dot3$(PS)wsa.asn $(SPECSDIR)$(PS)1609dot3$(PS)wsm.asn $(SPECSDIR)$(PS)TCI16093.asn $(SPECSDIR)$(PS)TCI16094.asn $(SPECSDIR)$(PS)TCI29451.asn $(SPECSDIR)$(PS)TCI80211.asn $(SPECSDIR)$(PS)TCICommonTypes.asn $(SPECSDIR)$(PS)TCIDispatcher.asn $(SPECSDIR)$(PS)TCIEventHandling.asn $(SPECSDIR)$(PS)TCISutControl.asn $(SPECSDIR)$(PS)TCIindication.asn $(SPECSDIR)$(PS)TCIip.asn $(SPECSDIR)$(PS)TCIresponseInfo.asn $(SPECSDIR)$(PS)TCIwsm.asn -cpp -oer -I $(SPECSDIR)$(PS)1609dot3 -I $(SPECSDIR) -pdu TCIMsg -print -prttostrm -strict-size -table-unions -test -trace -x64

depends: CITSapplMgmtIDs.cpp IEEE-1609-3-WEE.cpp IEEE-1609-3-WSA.cpp \
IEEE-1609-3-WSM.cpp TCI-16093.cpp TCI-16094.cpp TCI-29451.cpp TCI-80211.cpp \
TCI-CommonTypes.cpp TCI-Dispatcher.cpp TCI-eventHandling.cpp \
TCI-SutControl.cpp TCI-indication.cpp TCI-ip.cpp TCI-responseInfo.cpp \
TCI-wsm.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

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
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM) message.dat
	$(RM_MSVC_FILES)
