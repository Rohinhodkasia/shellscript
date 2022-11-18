# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

# include directories
OSROOTDIR = ../../..
LIBDIR  = $(OSROOTDIR)$(PS)cpp$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)/rtsrc
BERSRCDIR = $(OSROOTDIR)/rtbersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)/asn1type.h $(RTSRCDIR)/asn1CppTypes.h  \
$(BERSRCDIR)/asn1ber.h $(BERSRCDIR)/asn1BerCppTypes.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_)
CCFLAGS = $(CFLAGS)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I../rose -I$(RTSRCDIR) -I$(BERSRCDIR) \
$(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(BERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
LLIBS = $(LLBER) $(LLRT)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
CSTA-make-call$(OBJ) \
CSTA-ROSE-PDU-types$(OBJ) \
CSTA-device-identifiers$(OBJ) \
CSTA-extension-types$(OBJ) \
CSTA-security$(OBJ) \
CSTA-call-connection-identifiers$(OBJ) \
Remote-Operations-Information-Objects$(OBJ) \
Remote-Operations-Generic-ROS-PDUs$(OBJ) \
CSTA-error-definition$(OBJ)

ENCOBJECTS =  \
CSTA-make-callEnc$(OBJ) \
CSTA-ROSE-PDU-typesEnc$(OBJ) \
CSTA-device-identifiersEnc$(OBJ) \
CSTA-extension-typesEnc$(OBJ) \
CSTA-securityEnc$(OBJ) \
CSTA-call-connection-identifiersEnc$(OBJ) \
Remote-Operations-Information-ObjectsEnc$(OBJ) \
Remote-Operations-Generic-ROS-PDUsEnc$(OBJ) \
CSTA-error-definitionEnc$(OBJ)

DECOBJECTS =  \
CSTA-make-callDec$(OBJ) \
CSTA-ROSE-PDU-typesDec$(OBJ) \
CSTA-device-identifiersDec$(OBJ) \
CSTA-extension-typesDec$(OBJ) \
CSTA-securityDec$(OBJ) \
CSTA-call-connection-identifiersDec$(OBJ) \
Remote-Operations-Information-ObjectsDec$(OBJ) \
Remote-Operations-Generic-ROS-PDUsDec$(OBJ) \
CSTA-error-definitionDec$(OBJ)

PRTOBJECTS =  \
CSTA-make-callPrint$(OBJ) \
CSTA-ROSE-PDU-typesPrint$(OBJ) \
CSTA-device-identifiersPrint$(OBJ) \
CSTA-extension-typesPrint$(OBJ) \
CSTA-securityPrint$(OBJ) \
CSTA-call-connection-identifiersPrint$(OBJ) \
Remote-Operations-Information-ObjectsPrint$(OBJ) \
Remote-Operations-Generic-ROS-PDUsPrint$(OBJ) \
CSTA-error-definitionPrint$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
 $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS) $(LLSYS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS) $(LLSYS)

RWHFILES = $(HFILESDIR)/CSTA-make-call.h $(HFILESDIR)/CSTA-ROSE-PDU-types.h \
$(HFILESDIR)/CSTA-device-identifiers.h $(HFILESDIR)/CSTA-extension-types.h \
$(HFILESDIR)/CSTA-security.h $(HFILESDIR)/CSTA-call-connection-identifiers.h \
$(HFILESDIR)/Remote-Operations-Information-Objects.h \
$(HFILESDIR)/Remote-Operations-Generic-ROS-PDUs.h \
$(HFILESDIR)/CSTA-error-definition.h $(HFILESDIR)/rtkey.h $(HFILES)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .cpp .h rules
$(SRCDIR)/CSTA-make-callEnc.cpp \
$(SRCDIR)/CSTA-make-callDec.cpp \
$(SRCDIR)/CSTA-make-call.cpp \
$(SRCDIR)/CSTA-make-callPrint.cpp \
$(HFILESDIR)/CSTA-make-call.h \
$(SRCDIR)/CSTA-ROSE-PDU-typesEnc.cpp \
$(SRCDIR)/CSTA-ROSE-PDU-typesDec.cpp \
$(SRCDIR)/CSTA-ROSE-PDU-types.cpp \
$(SRCDIR)/CSTA-ROSE-PDU-typesPrint.cpp \
$(HFILESDIR)/CSTA-ROSE-PDU-types.h \
$(SRCDIR)/CSTA-device-identifiersEnc.cpp \
$(SRCDIR)/CSTA-device-identifiersDec.cpp \
$(SRCDIR)/CSTA-device-identifiers.cpp \
$(SRCDIR)/CSTA-device-identifiersPrint.cpp \
$(HFILESDIR)/CSTA-device-identifiers.h \
$(SRCDIR)/CSTA-extension-typesEnc.cpp \
$(SRCDIR)/CSTA-extension-typesDec.cpp \
$(SRCDIR)/CSTA-extension-types.cpp \
$(SRCDIR)/CSTA-extension-typesPrint.cpp \
$(HFILESDIR)/CSTA-extension-types.h \
$(SRCDIR)/CSTA-securityEnc.cpp \
$(SRCDIR)/CSTA-securityDec.cpp \
$(SRCDIR)/CSTA-security.cpp \
$(SRCDIR)/CSTA-securityPrint.cpp \
$(HFILESDIR)/CSTA-security.h \
$(SRCDIR)/CSTA-call-connection-identifiersEnc.cpp \
$(SRCDIR)/CSTA-call-connection-identifiersDec.cpp \
$(SRCDIR)/CSTA-call-connection-identifiers.cpp \
$(SRCDIR)/CSTA-call-connection-identifiersPrint.cpp \
$(HFILESDIR)/CSTA-call-connection-identifiers.h \
$(SRCDIR)/Remote-Operations-Information-ObjectsEnc.cpp \
$(SRCDIR)/Remote-Operations-Information-ObjectsDec.cpp \
$(SRCDIR)/Remote-Operations-Information-Objects.cpp \
$(SRCDIR)/Remote-Operations-Information-ObjectsPrint.cpp \
$(HFILESDIR)/Remote-Operations-Information-Objects.h \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUsEnc.cpp \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUsDec.cpp \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUs.cpp \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUsPrint.cpp \
$(HFILESDIR)/Remote-Operations-Generic-ROS-PDUs.h \
$(SRCDIR)/CSTA-error-definitionEnc.cpp \
$(SRCDIR)/CSTA-error-definitionDec.cpp \
$(SRCDIR)/CSTA-error-definition.cpp \
$(SRCDIR)/CSTA-error-definitionPrint.cpp \
$(HFILESDIR)/CSTA-error-definition.h \
$(HFILESDIR)/rtkey.h \
: CSTA-make-call.asn CSTA-ROSE-PDU-types.asn $(OSROOTDIR)/bin/asn1c$(EXE)
	$(ASN1C) CSTA-make-call.asn CSTA-ROSE-PDU-types.asn -cpp -ber -depends -I ..$(PS)rose -print -table-unions

depends: CSTA-make-call.cpp CSTA-ROSE-PDU-types.cpp \
CSTA-device-identifiers.cpp CSTA-extension-types.cpp CSTA-security.cpp \
CSTA-call-connection-identifiers.cpp \
Remote-Operations-Information-Objects.cpp \
Remote-Operations-Generic-ROS-PDUs.cpp CSTA-error-definition.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) CSTA-make-callEnc.cpp
	$(RM) CSTA-make-callDec.cpp
	$(RM) CSTA-make-call.cpp
	$(RM) CSTA-make-callPrint.cpp
	$(RM) $(HFILESDIR)$(PS)CSTA-make-call.h 
	$(RM) CSTA-ROSE-PDU-typesEnc.cpp
	$(RM) CSTA-ROSE-PDU-typesDec.cpp
	$(RM) CSTA-ROSE-PDU-types.cpp
	$(RM) CSTA-ROSE-PDU-typesPrint.cpp
	$(RM) $(HFILESDIR)$(PS)CSTA-ROSE-PDU-types.h 
	$(RM) CSTA-device-identifiersEnc.cpp
	$(RM) CSTA-device-identifiersDec.cpp
	$(RM) CSTA-device-identifiers.cpp
	$(RM) CSTA-device-identifiersPrint.cpp
	$(RM) $(HFILESDIR)$(PS)CSTA-device-identifiers.h 
	$(RM) CSTA-extension-typesEnc.cpp
	$(RM) CSTA-extension-typesDec.cpp
	$(RM) CSTA-extension-types.cpp
	$(RM) CSTA-extension-typesPrint.cpp
	$(RM) $(HFILESDIR)$(PS)CSTA-extension-types.h 
	$(RM) CSTA-securityEnc.cpp
	$(RM) CSTA-securityDec.cpp
	$(RM) CSTA-security.cpp
	$(RM) CSTA-securityPrint.cpp
	$(RM) $(HFILESDIR)$(PS)CSTA-security.h 
	$(RM) CSTA-call-connection-identifiersEnc.cpp
	$(RM) CSTA-call-connection-identifiersDec.cpp
	$(RM) CSTA-call-connection-identifiers.cpp
	$(RM) CSTA-call-connection-identifiersPrint.cpp
	$(RM) $(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h 
	$(RM) Remote-Operations-Information-ObjectsEnc.cpp
	$(RM) Remote-Operations-Information-ObjectsDec.cpp
	$(RM) Remote-Operations-Information-Objects.cpp
	$(RM) Remote-Operations-Information-ObjectsPrint.cpp
	$(RM) $(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h 
	$(RM) Remote-Operations-Generic-ROS-PDUsEnc.cpp
	$(RM) Remote-Operations-Generic-ROS-PDUsDec.cpp
	$(RM) Remote-Operations-Generic-ROS-PDUs.cpp
	$(RM) Remote-Operations-Generic-ROS-PDUsPrint.cpp
	$(RM) $(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h 
	$(RM) $(HFILESDIR)$(PS)Remote-Operations-Useful-Definitions.h 
	$(RM) CSTA-error-definitionEnc.cpp
	$(RM) CSTA-error-definitionDec.cpp
	$(RM) CSTA-error-definition.cpp
	$(RM) CSTA-error-definitionPrint.cpp
	$(RM) $(HFILESDIR)$(PS)CSTA-error-definition.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) *.dat

