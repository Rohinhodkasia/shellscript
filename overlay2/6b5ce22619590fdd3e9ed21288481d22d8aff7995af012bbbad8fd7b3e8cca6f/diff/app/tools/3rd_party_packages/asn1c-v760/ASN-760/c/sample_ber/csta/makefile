# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

# include directories
OSROOTDIR = ../../..
RTSRCDIR = $(OSROOTDIR)/rtsrc
BERSRCDIR = $(OSROOTDIR)/rtbersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)/asn1type.h $(BERSRCDIR)/asn1ber.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I../rose -I$(RTSRCDIR) -I$(BERSRCDIR) \
$(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
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

writer$(EXE) : $(WRITEROBJ) 
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(BSLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(BSLIBS)

RWHFILES = $(HFILESDIR)/CSTA-make-call.h $(HFILESDIR)/CSTA-ROSE-PDU-types.h \
$(HFILESDIR)/CSTA-device-identifiers.h $(HFILESDIR)/CSTA-extension-types.h \
$(HFILESDIR)/CSTA-security.h $(HFILESDIR)/CSTA-call-connection-identifiers.h \
$(HFILESDIR)/Remote-Operations-Information-Objects.h \
$(HFILESDIR)/Remote-Operations-Generic-ROS-PDUs.h \
$(HFILESDIR)/CSTA-error-definition.h $(HFILESDIR)/rtkey.h $(HFILES)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
$(SRCDIR)/CSTA-make-callEnc.c \
$(SRCDIR)/CSTA-make-callDec.c \
$(SRCDIR)/CSTA-make-call.c \
$(SRCDIR)/CSTA-make-callPrint.c \
$(HFILESDIR)/CSTA-make-call.h \
$(SRCDIR)/CSTA-ROSE-PDU-typesEnc.c \
$(SRCDIR)/CSTA-ROSE-PDU-typesDec.c \
$(SRCDIR)/CSTA-ROSE-PDU-types.c \
$(SRCDIR)/CSTA-ROSE-PDU-typesPrint.c \
$(HFILESDIR)/CSTA-ROSE-PDU-types.h \
$(SRCDIR)/CSTA-device-identifiersEnc.c \
$(SRCDIR)/CSTA-device-identifiersDec.c \
$(SRCDIR)/CSTA-device-identifiers.c \
$(SRCDIR)/CSTA-device-identifiersPrint.c \
$(HFILESDIR)/CSTA-device-identifiers.h \
$(SRCDIR)/CSTA-extension-typesEnc.c \
$(SRCDIR)/CSTA-extension-typesDec.c \
$(SRCDIR)/CSTA-extension-types.c \
$(SRCDIR)/CSTA-extension-typesPrint.c \
$(HFILESDIR)/CSTA-extension-types.h \
$(SRCDIR)/CSTA-securityEnc.c \
$(SRCDIR)/CSTA-securityDec.c \
$(SRCDIR)/CSTA-security.c \
$(SRCDIR)/CSTA-securityPrint.c \
$(HFILESDIR)/CSTA-security.h \
$(SRCDIR)/CSTA-call-connection-identifiersEnc.c \
$(SRCDIR)/CSTA-call-connection-identifiersDec.c \
$(SRCDIR)/CSTA-call-connection-identifiers.c \
$(SRCDIR)/CSTA-call-connection-identifiersPrint.c \
$(HFILESDIR)/CSTA-call-connection-identifiers.h \
$(SRCDIR)/Remote-Operations-Information-ObjectsEnc.c \
$(SRCDIR)/Remote-Operations-Information-ObjectsDec.c \
$(SRCDIR)/Remote-Operations-Information-Objects.c \
$(SRCDIR)/Remote-Operations-Information-ObjectsPrint.c \
$(HFILESDIR)/Remote-Operations-Information-Objects.h \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUsEnc.c \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUsDec.c \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUs.c \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUsPrint.c \
$(HFILESDIR)/Remote-Operations-Generic-ROS-PDUs.h \
$(SRCDIR)/CSTA-error-definitionEnc.c \
$(SRCDIR)/CSTA-error-definitionDec.c \
$(SRCDIR)/CSTA-error-definition.c \
$(SRCDIR)/CSTA-error-definitionPrint.c \
$(HFILESDIR)/CSTA-error-definition.h \
$(HFILESDIR)/rtkey.h \
: CSTA-make-call.asn CSTA-ROSE-PDU-types.asn $(OSROOTDIR)/bin/asn1c$(EXE)
	$(ASN1C) CSTA-make-call.asn CSTA-ROSE-PDU-types.asn -c -ber -depends -I ../rose -print -table-unions -html

depends: CSTA-make-call.c CSTA-ROSE-PDU-types.c CSTA-device-identifiers.c \
CSTA-extension-types.c CSTA-security.c CSTA-call-connection-identifiers.c \
Remote-Operations-Information-Objects.c Remote-Operations-Generic-ROS-PDUs.c \
CSTA-error-definition.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) CSTA-make-callEnc.c
	$(RM) CSTA-make-callDec.c
	$(RM) CSTA-make-call.c
	$(RM) CSTA-make-callPrint.c
	$(RM) $(HFILESDIR)$(PS)CSTA-make-call.h 
	$(RM) CSTA-ROSE-PDU-typesEnc.c
	$(RM) CSTA-ROSE-PDU-typesDec.c
	$(RM) CSTA-ROSE-PDU-types.c
	$(RM) CSTA-ROSE-PDU-typesPrint.c
	$(RM) $(HFILESDIR)$(PS)CSTA-ROSE-PDU-types.h 
	$(RM) CSTA-device-identifiersEnc.c
	$(RM) CSTA-device-identifiersDec.c
	$(RM) CSTA-device-identifiers.c
	$(RM) CSTA-device-identifiersPrint.c
	$(RM) $(HFILESDIR)$(PS)CSTA-device-identifiers.h 
	$(RM) CSTA-extension-typesEnc.c
	$(RM) CSTA-extension-typesDec.c
	$(RM) CSTA-extension-types.c
	$(RM) CSTA-extension-typesPrint.c
	$(RM) $(HFILESDIR)$(PS)CSTA-extension-types.h 
	$(RM) CSTA-securityEnc.c
	$(RM) CSTA-securityDec.c
	$(RM) CSTA-security.c
	$(RM) CSTA-securityPrint.c
	$(RM) $(HFILESDIR)$(PS)CSTA-security.h 
	$(RM) CSTA-call-connection-identifiersEnc.c
	$(RM) CSTA-call-connection-identifiersDec.c
	$(RM) CSTA-call-connection-identifiers.c
	$(RM) CSTA-call-connection-identifiersPrint.c
	$(RM) $(HFILESDIR)$(PS)CSTA-call-connection-identifiers.h 
	$(RM) Remote-Operations-Information-ObjectsEnc.c
	$(RM) Remote-Operations-Information-ObjectsDec.c
	$(RM) Remote-Operations-Information-Objects.c
	$(RM) Remote-Operations-Information-ObjectsPrint.c
	$(RM) $(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h 
	$(RM) Remote-Operations-Generic-ROS-PDUsEnc.c
	$(RM) Remote-Operations-Generic-ROS-PDUsDec.c
	$(RM) Remote-Operations-Generic-ROS-PDUs.c
	$(RM) Remote-Operations-Generic-ROS-PDUsPrint.c
	$(RM) $(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h 
	$(RM) $(HFILESDIR)$(PS)Remote-Operations-Useful-Definitions.h 
	$(RM) CSTA-error-definitionEnc.c
	$(RM) CSTA-error-definitionDec.c
	$(RM) CSTA-error-definition.c
	$(RM) CSTA-error-definitionPrint.c
	$(RM) $(HFILESDIR)$(PS)CSTA-error-definition.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) *.html
	$(RM) asn1-style.css
	$(RM) message.dat
	$(RM) messagei.dat
