# makefile to build generated files

include ../../platform.mk

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)cpp$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(RTSRCDIR)$(PS)asn1CppTypes.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_)
CCFLAGS = -c $(CVARS_) $(CCFLAGS_) $(CBLDTYPE_)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1rt$(LLAEXT) $(LLSYS)
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
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)CSTA-make-call.h  \
$(HFILESDIR)$(PS)CSTA-ROSE-PDU-types.h $(HFILESDIR)$(PS)CSTA-device-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-extension-types.h $(HFILESDIR)$(PS)CSTA-security.h  \
$(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h $(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h  \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h $(HFILESDIR)$(PS)CSTA-error-definition.h  \
$(HFILESDIR)$(PS)Remote-Operations-Useful-Definitions.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

writer$(OBJ) : $(SRCDIR)$(PS)writer.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)$(PS)writer.cpp

reader$(OBJ) : $(SRCDIR)$(PS)reader.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)$(PS)reader.cpp

# .cpp -> .obj rules
# common file rules
CSTA-make-call$(OBJ) : $(SRCDIR)$(PS)CSTA-make-call.cpp \
$(HFILESDIR)$(PS)CSTA-make-call.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-extension-types.h $(HFILESDIR)$(PS)CSTA-device-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-error-definition.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-make-call.cpp

# decode file rules
CSTA-make-callDec$(OBJ) : $(SRCDIR)$(PS)CSTA-make-callDec.cpp \
$(HFILESDIR)$(PS)CSTA-make-call.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-extension-types.h $(HFILESDIR)$(PS)CSTA-device-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-error-definition.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-make-callDec.cpp

# encode file rules
CSTA-make-callEnc$(OBJ) : $(SRCDIR)$(PS)CSTA-make-callEnc.cpp \
$(HFILESDIR)$(PS)CSTA-make-call.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-extension-types.h $(HFILESDIR)$(PS)CSTA-device-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-error-definition.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-make-callEnc.cpp

# print file rules
CSTA-make-callPrint$(OBJ) : $(SRCDIR)$(PS)CSTA-make-callPrint.cpp \
$(HFILESDIR)$(PS)CSTA-make-call.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-extension-types.h $(HFILESDIR)$(PS)CSTA-device-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-error-definition.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-make-callPrint.cpp

# common file rules
CSTA-ROSE-PDU-types$(OBJ) : $(SRCDIR)$(PS)CSTA-ROSE-PDU-types.cpp \
$(HFILESDIR)$(PS)CSTA-ROSE-PDU-types.h  \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h $(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h  \
$(HFILESDIR)$(PS)CSTA-make-call.h $(HFILESDIR)$(PS)CSTA-error-definition.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-ROSE-PDU-types.cpp

# decode file rules
CSTA-ROSE-PDU-typesDec$(OBJ) : $(SRCDIR)$(PS)CSTA-ROSE-PDU-typesDec.cpp \
$(HFILESDIR)$(PS)CSTA-ROSE-PDU-types.h  \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h $(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h  \
$(HFILESDIR)$(PS)CSTA-make-call.h $(HFILESDIR)$(PS)CSTA-error-definition.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-ROSE-PDU-typesDec.cpp

# encode file rules
CSTA-ROSE-PDU-typesEnc$(OBJ) : $(SRCDIR)$(PS)CSTA-ROSE-PDU-typesEnc.cpp \
$(HFILESDIR)$(PS)CSTA-ROSE-PDU-types.h  \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h $(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h  \
$(HFILESDIR)$(PS)CSTA-make-call.h $(HFILESDIR)$(PS)CSTA-error-definition.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-ROSE-PDU-typesEnc.cpp

# print file rules
CSTA-ROSE-PDU-typesPrint$(OBJ) : $(SRCDIR)$(PS)CSTA-ROSE-PDU-typesPrint.cpp \
$(HFILESDIR)$(PS)CSTA-ROSE-PDU-types.h  \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h $(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h  \
$(HFILESDIR)$(PS)CSTA-make-call.h $(HFILESDIR)$(PS)CSTA-error-definition.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-ROSE-PDU-typesPrint.cpp

# common file rules
CSTA-device-identifiers$(OBJ) : $(SRCDIR)$(PS)CSTA-device-identifiers.cpp \
$(HFILESDIR)$(PS)CSTA-device-identifiers.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-device-identifiers.cpp

# decode file rules
CSTA-device-identifiersDec$(OBJ) : $(SRCDIR)$(PS)CSTA-device-identifiersDec.cpp \
$(HFILESDIR)$(PS)CSTA-device-identifiers.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-device-identifiersDec.cpp

# encode file rules
CSTA-device-identifiersEnc$(OBJ) : $(SRCDIR)$(PS)CSTA-device-identifiersEnc.cpp \
$(HFILESDIR)$(PS)CSTA-device-identifiers.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-device-identifiersEnc.cpp

# print file rules
CSTA-device-identifiersPrint$(OBJ) : $(SRCDIR)$(PS)CSTA-device-identifiersPrint.cpp \
$(HFILESDIR)$(PS)CSTA-device-identifiers.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-device-identifiersPrint.cpp

# common file rules
CSTA-extension-types$(OBJ) : $(SRCDIR)$(PS)CSTA-extension-types.cpp \
$(HFILESDIR)$(PS)CSTA-extension-types.h  \
$(HFILESDIR)$(PS)CSTA-security.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-extension-types.cpp

# decode file rules
CSTA-extension-typesDec$(OBJ) : $(SRCDIR)$(PS)CSTA-extension-typesDec.cpp \
$(HFILESDIR)$(PS)CSTA-extension-types.h  \
$(HFILESDIR)$(PS)CSTA-security.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-extension-typesDec.cpp

# encode file rules
CSTA-extension-typesEnc$(OBJ) : $(SRCDIR)$(PS)CSTA-extension-typesEnc.cpp \
$(HFILESDIR)$(PS)CSTA-extension-types.h  \
$(HFILESDIR)$(PS)CSTA-security.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-extension-typesEnc.cpp

# print file rules
CSTA-extension-typesPrint$(OBJ) : $(SRCDIR)$(PS)CSTA-extension-typesPrint.cpp \
$(HFILESDIR)$(PS)CSTA-extension-types.h  \
$(HFILESDIR)$(PS)CSTA-security.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-extension-typesPrint.cpp

# common file rules
CSTA-security$(OBJ) : $(SRCDIR)$(PS)CSTA-security.cpp \
$(HFILESDIR)$(PS)CSTA-security.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-security.cpp

# decode file rules
CSTA-securityDec$(OBJ) : $(SRCDIR)$(PS)CSTA-securityDec.cpp \
$(HFILESDIR)$(PS)CSTA-security.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-securityDec.cpp

# encode file rules
CSTA-securityEnc$(OBJ) : $(SRCDIR)$(PS)CSTA-securityEnc.cpp \
$(HFILESDIR)$(PS)CSTA-security.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-securityEnc.cpp

# print file rules
CSTA-securityPrint$(OBJ) : $(SRCDIR)$(PS)CSTA-securityPrint.cpp \
$(HFILESDIR)$(PS)CSTA-security.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-securityPrint.cpp

# common file rules
CSTA-call-connection-identifiers$(OBJ) : $(SRCDIR)$(PS)CSTA-call-connection-identifiers.cpp \
$(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-device-identifiers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-call-connection-identifiers.cpp

# decode file rules
CSTA-call-connection-identifiersDec$(OBJ) : $(SRCDIR)$(PS)CSTA-call-connection-identifiersDec.cpp \
$(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-device-identifiers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-call-connection-identifiersDec.cpp

# encode file rules
CSTA-call-connection-identifiersEnc$(OBJ) : $(SRCDIR)$(PS)CSTA-call-connection-identifiersEnc.cpp \
$(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-device-identifiers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-call-connection-identifiersEnc.cpp

# print file rules
CSTA-call-connection-identifiersPrint$(OBJ) : $(SRCDIR)$(PS)CSTA-call-connection-identifiersPrint.cpp \
$(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-device-identifiers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-call-connection-identifiersPrint.cpp

# common file rules
Remote-Operations-Information-Objects$(OBJ) : $(SRCDIR)$(PS)Remote-Operations-Information-Objects.cpp \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h  \
$(HFILESDIR)$(PS)Remote-Operations-Useful-Definitions.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Remote-Operations-Information-Objects.cpp

# decode file rules
Remote-Operations-Information-ObjectsDec$(OBJ) : $(SRCDIR)$(PS)Remote-Operations-Information-ObjectsDec.cpp \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h  \
$(HFILESDIR)$(PS)Remote-Operations-Useful-Definitions.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Remote-Operations-Information-ObjectsDec.cpp

# encode file rules
Remote-Operations-Information-ObjectsEnc$(OBJ) : $(SRCDIR)$(PS)Remote-Operations-Information-ObjectsEnc.cpp \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h  \
$(HFILESDIR)$(PS)Remote-Operations-Useful-Definitions.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Remote-Operations-Information-ObjectsEnc.cpp

# print file rules
Remote-Operations-Information-ObjectsPrint$(OBJ) : $(SRCDIR)$(PS)Remote-Operations-Information-ObjectsPrint.cpp \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h  \
$(HFILESDIR)$(PS)Remote-Operations-Useful-Definitions.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Remote-Operations-Information-ObjectsPrint.cpp

# common file rules
Remote-Operations-Generic-ROS-PDUs$(OBJ) : $(SRCDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.cpp \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.cpp

# decode file rules
Remote-Operations-Generic-ROS-PDUsDec$(OBJ) : $(SRCDIR)$(PS)Remote-Operations-Generic-ROS-PDUsDec.cpp \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Remote-Operations-Generic-ROS-PDUsDec.cpp

# encode file rules
Remote-Operations-Generic-ROS-PDUsEnc$(OBJ) : $(SRCDIR)$(PS)Remote-Operations-Generic-ROS-PDUsEnc.cpp \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Remote-Operations-Generic-ROS-PDUsEnc.cpp

# print file rules
Remote-Operations-Generic-ROS-PDUsPrint$(OBJ) : $(SRCDIR)$(PS)Remote-Operations-Generic-ROS-PDUsPrint.cpp \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Remote-Operations-Generic-ROS-PDUsPrint.cpp

# common file rules
CSTA-error-definition$(OBJ) : $(SRCDIR)$(PS)CSTA-error-definition.cpp \
$(HFILESDIR)$(PS)CSTA-error-definition.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)CSTA-extension-types.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-error-definition.cpp

# decode file rules
CSTA-error-definitionDec$(OBJ) : $(SRCDIR)$(PS)CSTA-error-definitionDec.cpp \
$(HFILESDIR)$(PS)CSTA-error-definition.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)CSTA-extension-types.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-error-definitionDec.cpp

# encode file rules
CSTA-error-definitionEnc$(OBJ) : $(SRCDIR)$(PS)CSTA-error-definitionEnc.cpp \
$(HFILESDIR)$(PS)CSTA-error-definition.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)CSTA-extension-types.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-error-definitionEnc.cpp

# print file rules
CSTA-error-definitionPrint$(OBJ) : $(SRCDIR)$(PS)CSTA-error-definitionPrint.cpp \
$(HFILESDIR)$(PS)CSTA-error-definition.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)CSTA-extension-types.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-error-definitionPrint.cpp

# .asn -> .cpp .h rules
$(SRCDIR)/CSTA-make-callEnc.cpp \
$(SRCDIR)/CSTA-make-callDec.cpp \
$(SRCDIR)/CSTA-make-call.cpp \
$(SRCDIR)/CSTA-make-callPrint.cpp \
$(HFILESDIR)$(PS)CSTA-make-call.h \
$(SRCDIR)/CSTA-ROSE-PDU-typesEnc.cpp \
$(SRCDIR)/CSTA-ROSE-PDU-typesDec.cpp \
$(SRCDIR)/CSTA-ROSE-PDU-types.cpp \
$(SRCDIR)/CSTA-ROSE-PDU-typesPrint.cpp \
$(HFILESDIR)$(PS)CSTA-ROSE-PDU-types.h \
$(SRCDIR)/CSTA-device-identifiersEnc.cpp \
$(SRCDIR)/CSTA-device-identifiersDec.cpp \
$(SRCDIR)/CSTA-device-identifiers.cpp \
$(SRCDIR)/CSTA-device-identifiersPrint.cpp \
$(HFILESDIR)$(PS)CSTA-device-identifiers.h \
$(SRCDIR)/CSTA-extension-typesEnc.cpp \
$(SRCDIR)/CSTA-extension-typesDec.cpp \
$(SRCDIR)/CSTA-extension-types.cpp \
$(SRCDIR)/CSTA-extension-typesPrint.cpp \
$(HFILESDIR)$(PS)CSTA-extension-types.h \
$(SRCDIR)/CSTA-securityEnc.cpp \
$(SRCDIR)/CSTA-securityDec.cpp \
$(SRCDIR)/CSTA-security.cpp \
$(SRCDIR)/CSTA-securityPrint.cpp \
$(HFILESDIR)$(PS)CSTA-security.h \
$(SRCDIR)/CSTA-call-connection-identifiersEnc.cpp \
$(SRCDIR)/CSTA-call-connection-identifiersDec.cpp \
$(SRCDIR)/CSTA-call-connection-identifiers.cpp \
$(SRCDIR)/CSTA-call-connection-identifiersPrint.cpp \
$(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h \
$(SRCDIR)/Remote-Operations-Information-ObjectsEnc.cpp \
$(SRCDIR)/Remote-Operations-Information-ObjectsDec.cpp \
$(SRCDIR)/Remote-Operations-Information-Objects.cpp \
$(SRCDIR)/Remote-Operations-Information-ObjectsPrint.cpp \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUsEnc.cpp \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUsDec.cpp \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUs.cpp \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUsPrint.cpp \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h \
$(SRCDIR)/CSTA-error-definitionEnc.cpp \
$(SRCDIR)/CSTA-error-definitionDec.cpp \
$(SRCDIR)/CSTA-error-definition.cpp \
$(SRCDIR)/CSTA-error-definitionPrint.cpp \
$(HFILESDIR)$(PS)CSTA-error-definition.h \
$(HFILESDIR)$(PS)Remote-Operations-Useful-Definitions.h \
$(HFILESDIR)$(PS)rtkey.h \
: CSTA-make-call.asn CSTA-ROSE-PDU-types.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(OSROOTDIR)$(PS)bin$(PS)asn1c CSTA-make-call.asn CSTA-ROSE-PDU-types.asn -cpp -avn -depends -print -table-unions

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
	$(RM) CSTA-error-definitionEnc.cpp
	$(RM) CSTA-error-definitionDec.cpp
	$(RM) CSTA-error-definition.cpp
	$(RM) CSTA-error-definitionPrint.cpp
	$(RM) $(HFILESDIR)$(PS)CSTA-error-definition.h 
	$(RM) $(HFILESDIR)$(PS)Remote-Operations-Useful-Definitions.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
