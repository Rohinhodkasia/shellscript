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
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_)
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

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(PRTOBJECTS)

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

writer$(OBJ) : $(SRCDIR)$(PS)writer.c $(RWHFILES)
	$(CC) -c $(CFLAGS) $(IPATHS) $(SRCDIR)$(PS)writer.c

reader$(OBJ) : $(SRCDIR)$(PS)reader.c $(RWHFILES)
	$(CC) -c $(CFLAGS) $(IPATHS) $(SRCDIR)$(PS)reader.c

# .c -> .obj rules
# common file rules
CSTA-make-call$(OBJ) : $(SRCDIR)$(PS)CSTA-make-call.c \
$(HFILESDIR)$(PS)CSTA-make-call.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-extension-types.h $(HFILESDIR)$(PS)CSTA-device-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-error-definition.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-make-call.c

# decode file rules
CSTA-make-callDec$(OBJ) : $(SRCDIR)$(PS)CSTA-make-callDec.c \
$(HFILESDIR)$(PS)CSTA-make-call.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-extension-types.h $(HFILESDIR)$(PS)CSTA-device-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-error-definition.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-make-callDec.c

# encode file rules
CSTA-make-callEnc$(OBJ) : $(SRCDIR)$(PS)CSTA-make-callEnc.c \
$(HFILESDIR)$(PS)CSTA-make-call.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-extension-types.h $(HFILESDIR)$(PS)CSTA-device-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-error-definition.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-make-callEnc.c

# print file rules
CSTA-make-callPrint$(OBJ) : $(SRCDIR)$(PS)CSTA-make-callPrint.c \
$(HFILESDIR)$(PS)CSTA-make-call.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-extension-types.h $(HFILESDIR)$(PS)CSTA-device-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-error-definition.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-make-callPrint.c

# common file rules
CSTA-ROSE-PDU-types$(OBJ) : $(SRCDIR)$(PS)CSTA-ROSE-PDU-types.c \
$(HFILESDIR)$(PS)CSTA-ROSE-PDU-types.h  \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h $(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h  \
$(HFILESDIR)$(PS)CSTA-make-call.h $(HFILESDIR)$(PS)CSTA-error-definition.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-ROSE-PDU-types.c

# decode file rules
CSTA-ROSE-PDU-typesDec$(OBJ) : $(SRCDIR)$(PS)CSTA-ROSE-PDU-typesDec.c \
$(HFILESDIR)$(PS)CSTA-ROSE-PDU-types.h  \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h $(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h  \
$(HFILESDIR)$(PS)CSTA-make-call.h $(HFILESDIR)$(PS)CSTA-error-definition.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-ROSE-PDU-typesDec.c

# encode file rules
CSTA-ROSE-PDU-typesEnc$(OBJ) : $(SRCDIR)$(PS)CSTA-ROSE-PDU-typesEnc.c \
$(HFILESDIR)$(PS)CSTA-ROSE-PDU-types.h  \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h $(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h  \
$(HFILESDIR)$(PS)CSTA-make-call.h $(HFILESDIR)$(PS)CSTA-error-definition.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-ROSE-PDU-typesEnc.c

# print file rules
CSTA-ROSE-PDU-typesPrint$(OBJ) : $(SRCDIR)$(PS)CSTA-ROSE-PDU-typesPrint.c \
$(HFILESDIR)$(PS)CSTA-ROSE-PDU-types.h  \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h $(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h  \
$(HFILESDIR)$(PS)CSTA-make-call.h $(HFILESDIR)$(PS)CSTA-error-definition.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-ROSE-PDU-typesPrint.c

# common file rules
CSTA-device-identifiers$(OBJ) : $(SRCDIR)$(PS)CSTA-device-identifiers.c \
$(HFILESDIR)$(PS)CSTA-device-identifiers.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-device-identifiers.c

# decode file rules
CSTA-device-identifiersDec$(OBJ) : $(SRCDIR)$(PS)CSTA-device-identifiersDec.c \
$(HFILESDIR)$(PS)CSTA-device-identifiers.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-device-identifiersDec.c

# encode file rules
CSTA-device-identifiersEnc$(OBJ) : $(SRCDIR)$(PS)CSTA-device-identifiersEnc.c \
$(HFILESDIR)$(PS)CSTA-device-identifiers.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-device-identifiersEnc.c

# print file rules
CSTA-device-identifiersPrint$(OBJ) : $(SRCDIR)$(PS)CSTA-device-identifiersPrint.c \
$(HFILESDIR)$(PS)CSTA-device-identifiers.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-device-identifiersPrint.c

# common file rules
CSTA-extension-types$(OBJ) : $(SRCDIR)$(PS)CSTA-extension-types.c \
$(HFILESDIR)$(PS)CSTA-extension-types.h  \
$(HFILESDIR)$(PS)CSTA-security.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-extension-types.c

# decode file rules
CSTA-extension-typesDec$(OBJ) : $(SRCDIR)$(PS)CSTA-extension-typesDec.c \
$(HFILESDIR)$(PS)CSTA-extension-types.h  \
$(HFILESDIR)$(PS)CSTA-security.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-extension-typesDec.c

# encode file rules
CSTA-extension-typesEnc$(OBJ) : $(SRCDIR)$(PS)CSTA-extension-typesEnc.c \
$(HFILESDIR)$(PS)CSTA-extension-types.h  \
$(HFILESDIR)$(PS)CSTA-security.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-extension-typesEnc.c

# print file rules
CSTA-extension-typesPrint$(OBJ) : $(SRCDIR)$(PS)CSTA-extension-typesPrint.c \
$(HFILESDIR)$(PS)CSTA-extension-types.h  \
$(HFILESDIR)$(PS)CSTA-security.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-extension-typesPrint.c

# common file rules
CSTA-security$(OBJ) : $(SRCDIR)$(PS)CSTA-security.c \
$(HFILESDIR)$(PS)CSTA-security.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-security.c

# decode file rules
CSTA-securityDec$(OBJ) : $(SRCDIR)$(PS)CSTA-securityDec.c \
$(HFILESDIR)$(PS)CSTA-security.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-securityDec.c

# encode file rules
CSTA-securityEnc$(OBJ) : $(SRCDIR)$(PS)CSTA-securityEnc.c \
$(HFILESDIR)$(PS)CSTA-security.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-securityEnc.c

# print file rules
CSTA-securityPrint$(OBJ) : $(SRCDIR)$(PS)CSTA-securityPrint.c \
$(HFILESDIR)$(PS)CSTA-security.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-securityPrint.c

# common file rules
CSTA-call-connection-identifiers$(OBJ) : $(SRCDIR)$(PS)CSTA-call-connection-identifiers.c \
$(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-device-identifiers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-call-connection-identifiers.c

# decode file rules
CSTA-call-connection-identifiersDec$(OBJ) : $(SRCDIR)$(PS)CSTA-call-connection-identifiersDec.c \
$(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-device-identifiers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-call-connection-identifiersDec.c

# encode file rules
CSTA-call-connection-identifiersEnc$(OBJ) : $(SRCDIR)$(PS)CSTA-call-connection-identifiersEnc.c \
$(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-device-identifiers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-call-connection-identifiersEnc.c

# print file rules
CSTA-call-connection-identifiersPrint$(OBJ) : $(SRCDIR)$(PS)CSTA-call-connection-identifiersPrint.c \
$(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h  \
$(HFILESDIR)$(PS)CSTA-device-identifiers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-call-connection-identifiersPrint.c

# common file rules
Remote-Operations-Information-Objects$(OBJ) : $(SRCDIR)$(PS)Remote-Operations-Information-Objects.c \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h  \
$(HFILESDIR)$(PS)Remote-Operations-Useful-Definitions.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Remote-Operations-Information-Objects.c

# decode file rules
Remote-Operations-Information-ObjectsDec$(OBJ) : $(SRCDIR)$(PS)Remote-Operations-Information-ObjectsDec.c \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h  \
$(HFILESDIR)$(PS)Remote-Operations-Useful-Definitions.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Remote-Operations-Information-ObjectsDec.c

# encode file rules
Remote-Operations-Information-ObjectsEnc$(OBJ) : $(SRCDIR)$(PS)Remote-Operations-Information-ObjectsEnc.c \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h  \
$(HFILESDIR)$(PS)Remote-Operations-Useful-Definitions.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Remote-Operations-Information-ObjectsEnc.c

# print file rules
Remote-Operations-Information-ObjectsPrint$(OBJ) : $(SRCDIR)$(PS)Remote-Operations-Information-ObjectsPrint.c \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h  \
$(HFILESDIR)$(PS)Remote-Operations-Useful-Definitions.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Remote-Operations-Information-ObjectsPrint.c

# common file rules
Remote-Operations-Generic-ROS-PDUs$(OBJ) : $(SRCDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.c \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.c

# decode file rules
Remote-Operations-Generic-ROS-PDUsDec$(OBJ) : $(SRCDIR)$(PS)Remote-Operations-Generic-ROS-PDUsDec.c \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Remote-Operations-Generic-ROS-PDUsDec.c

# encode file rules
Remote-Operations-Generic-ROS-PDUsEnc$(OBJ) : $(SRCDIR)$(PS)Remote-Operations-Generic-ROS-PDUsEnc.c \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Remote-Operations-Generic-ROS-PDUsEnc.c

# print file rules
Remote-Operations-Generic-ROS-PDUsPrint$(OBJ) : $(SRCDIR)$(PS)Remote-Operations-Generic-ROS-PDUsPrint.c \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Remote-Operations-Generic-ROS-PDUsPrint.c

# common file rules
CSTA-error-definition$(OBJ) : $(SRCDIR)$(PS)CSTA-error-definition.c \
$(HFILESDIR)$(PS)CSTA-error-definition.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)CSTA-extension-types.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-error-definition.c

# decode file rules
CSTA-error-definitionDec$(OBJ) : $(SRCDIR)$(PS)CSTA-error-definitionDec.c \
$(HFILESDIR)$(PS)CSTA-error-definition.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)CSTA-extension-types.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-error-definitionDec.c

# encode file rules
CSTA-error-definitionEnc$(OBJ) : $(SRCDIR)$(PS)CSTA-error-definitionEnc.c \
$(HFILESDIR)$(PS)CSTA-error-definition.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)CSTA-extension-types.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-error-definitionEnc.c

# print file rules
CSTA-error-definitionPrint$(OBJ) : $(SRCDIR)$(PS)CSTA-error-definitionPrint.c \
$(HFILESDIR)$(PS)CSTA-error-definition.h  \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h $(HFILESDIR)$(PS)CSTA-extension-types.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CSTA-error-definitionPrint.c

# .asn -> .c .h rules
$(SRCDIR)/CSTA-make-callEnc.c \
$(SRCDIR)/CSTA-make-callDec.c \
$(SRCDIR)/CSTA-make-call.c \
$(SRCDIR)/CSTA-make-callPrint.c \
$(HFILESDIR)$(PS)CSTA-make-call.h \
$(SRCDIR)/CSTA-ROSE-PDU-typesEnc.c \
$(SRCDIR)/CSTA-ROSE-PDU-typesDec.c \
$(SRCDIR)/CSTA-ROSE-PDU-types.c \
$(SRCDIR)/CSTA-ROSE-PDU-typesPrint.c \
$(HFILESDIR)$(PS)CSTA-ROSE-PDU-types.h \
$(SRCDIR)/CSTA-device-identifiersEnc.c \
$(SRCDIR)/CSTA-device-identifiersDec.c \
$(SRCDIR)/CSTA-device-identifiers.c \
$(SRCDIR)/CSTA-device-identifiersPrint.c \
$(HFILESDIR)$(PS)CSTA-device-identifiers.h \
$(SRCDIR)/CSTA-extension-typesEnc.c \
$(SRCDIR)/CSTA-extension-typesDec.c \
$(SRCDIR)/CSTA-extension-types.c \
$(SRCDIR)/CSTA-extension-typesPrint.c \
$(HFILESDIR)$(PS)CSTA-extension-types.h \
$(SRCDIR)/CSTA-securityEnc.c \
$(SRCDIR)/CSTA-securityDec.c \
$(SRCDIR)/CSTA-security.c \
$(SRCDIR)/CSTA-securityPrint.c \
$(HFILESDIR)$(PS)CSTA-security.h \
$(SRCDIR)/CSTA-call-connection-identifiersEnc.c \
$(SRCDIR)/CSTA-call-connection-identifiersDec.c \
$(SRCDIR)/CSTA-call-connection-identifiers.c \
$(SRCDIR)/CSTA-call-connection-identifiersPrint.c \
$(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h \
$(SRCDIR)/Remote-Operations-Information-ObjectsEnc.c \
$(SRCDIR)/Remote-Operations-Information-ObjectsDec.c \
$(SRCDIR)/Remote-Operations-Information-Objects.c \
$(SRCDIR)/Remote-Operations-Information-ObjectsPrint.c \
$(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUsEnc.c \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUsDec.c \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUs.c \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUsPrint.c \
$(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h \
$(SRCDIR)/CSTA-error-definitionEnc.c \
$(SRCDIR)/CSTA-error-definitionDec.c \
$(SRCDIR)/CSTA-error-definition.c \
$(SRCDIR)/CSTA-error-definitionPrint.c \
$(HFILESDIR)$(PS)CSTA-error-definition.h \
$(HFILESDIR)$(PS)Remote-Operations-Useful-Definitions.h \
$(HFILESDIR)$(PS)rtkey.h \
: CSTA-make-call.asn CSTA-ROSE-PDU-types.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(OSROOTDIR)$(PS)bin$(PS)asn1c CSTA-make-call.asn CSTA-ROSE-PDU-types.asn -c -avn -depends -html -print -table-unions -fqtvalue

clean:
	$(RM) CSTA-make-callEnc.c
	$(RM) CSTA-make-callDec.c
	$(RM) CSTA-make-call.c
	$(RM) CSTA-make-callPrint.c
	$(RM) $(HFILESDIR)$(PS)CSTA-make-call.h 
	$(RM) CSTA-make-call.html
	$(RM) CSTA-ROSE-PDU-typesEnc.c
	$(RM) CSTA-ROSE-PDU-typesDec.c
	$(RM) CSTA-ROSE-PDU-types.c
	$(RM) CSTA-ROSE-PDU-typesPrint.c
	$(RM) $(HFILESDIR)$(PS)CSTA-ROSE-PDU-types.h 
	$(RM) CSTA-ROSE-PDU-types.html
	$(RM) CSTA-device-identifiersEnc.c
	$(RM) CSTA-device-identifiersDec.c
	$(RM) CSTA-device-identifiers.c
	$(RM) CSTA-device-identifiersPrint.c
	$(RM) $(HFILESDIR)$(PS)CSTA-device-identifiers.h 
	$(RM) CSTA-device-identifiers.html
	$(RM) CSTA-extension-typesEnc.c
	$(RM) CSTA-extension-typesDec.c
	$(RM) CSTA-extension-types.c
	$(RM) CSTA-extension-typesPrint.c
	$(RM) $(HFILESDIR)$(PS)CSTA-extension-types.h 
	$(RM) CSTA-extension-types.html
	$(RM) CSTA-securityEnc.c
	$(RM) CSTA-securityDec.c
	$(RM) CSTA-security.c
	$(RM) CSTA-securityPrint.c
	$(RM) $(HFILESDIR)$(PS)CSTA-security.h 
	$(RM) CSTA-security.html
	$(RM) CSTA-call-connection-identifiersEnc.c
	$(RM) CSTA-call-connection-identifiersDec.c
	$(RM) CSTA-call-connection-identifiers.c
	$(RM) CSTA-call-connection-identifiersPrint.c
	$(RM) $(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h 
	$(RM) CSTA-call-connection-identifiers.html
	$(RM) Remote-Operations-Information-ObjectsEnc.c
	$(RM) Remote-Operations-Information-ObjectsDec.c
	$(RM) Remote-Operations-Information-Objects.c
	$(RM) Remote-Operations-Information-ObjectsPrint.c
	$(RM) $(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h 
	$(RM) Remote-Operations-Information-Objects.html
	$(RM) Remote-Operations-Generic-ROS-PDUsEnc.c
	$(RM) Remote-Operations-Generic-ROS-PDUsDec.c
	$(RM) Remote-Operations-Generic-ROS-PDUs.c
	$(RM) Remote-Operations-Generic-ROS-PDUsPrint.c
	$(RM) $(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h 
	$(RM) Remote-Operations-Generic-ROS-PDUs.html
	$(RM) CSTA-error-definitionEnc.c
	$(RM) CSTA-error-definitionDec.c
	$(RM) CSTA-error-definition.c
	$(RM) CSTA-error-definitionPrint.c
	$(RM) $(HFILESDIR)$(PS)CSTA-error-definition.h 
	$(RM) CSTA-error-definition.html
	$(RM) $(HFILESDIR)$(PS)Remote-Operations-Useful-Definitions.h 
	$(RM) Remote-Operations-Useful-Definitions.html
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) asn1-style.css
