# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

# include directories
OSROOTDIR = ../../..
LIBDIR  = $(OSROOTDIR)/c/lib
RTSRCDIR = $(OSROOTDIR)/rtsrc
BERSRCDIR = $(OSROOTDIR)/rtbersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)/asn1type.h $(BERSRCDIR)/asn1ber.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(BERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/asn1ber_a.lib $(LIBDIR)/asn1rt_a.lib
LLIBS = asn1ber_a.lib asn1rt_a.lib
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
Remote-Operations-Generic-ROS-PDUs$(OBJ) \
Remote-Operations-Information-Objects$(OBJ) \
Remote-Operations-Useful-Definitions$(OBJ)

ENCOBJECTS =  \
Remote-Operations-Generic-ROS-PDUsEnc$(OBJ) \
Remote-Operations-Information-ObjectsEnc$(OBJ) \
Remote-Operations-Useful-DefinitionsEnc$(OBJ)

DECOBJECTS =  \
Remote-Operations-Generic-ROS-PDUsDec$(OBJ) \
Remote-Operations-Information-ObjectsDec$(OBJ) \
Remote-Operations-Useful-DefinitionsDec$(OBJ)

PRTOBJECTS =  \
Remote-Operations-Generic-ROS-PDUsPrint$(OBJ) \
Remote-Operations-Information-ObjectsPrint$(OBJ) \
Remote-Operations-Useful-DefinitionsPrint$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUsEnc.c \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUsDec.c \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUs.c \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUsPrint.c \
$(HFILESDIR)/Remote-Operations-Generic-ROS-PDUs.h \
$(SRCDIR)/Remote-Operations-Information-ObjectsEnc.c \
$(SRCDIR)/Remote-Operations-Information-ObjectsDec.c \
$(SRCDIR)/Remote-Operations-Information-Objects.c \
$(SRCDIR)/Remote-Operations-Information-ObjectsPrint.c \
$(HFILESDIR)/Remote-Operations-Information-Objects.h \
$(SRCDIR)/Remote-Operations-Useful-DefinitionsEnc.c \
$(SRCDIR)/Remote-Operations-Useful-DefinitionsDec.c \
$(SRCDIR)/Remote-Operations-Useful-Definitions.c \
$(SRCDIR)/Remote-Operations-Useful-DefinitionsPrint.c \
$(HFILESDIR)/Remote-Operations-Useful-Definitions.h \
$(HFILESDIR)/rtkey.h \
: Remote-Operations-Generic-ROS-PDUs.asn Remote-Operations-Information-Objects.asn Remote-Operations-Useful-Definitions.asn
	$(ASN1C) Remote-Operations-Generic-ROS-PDUs.asn Remote-Operations-Information-Objects.asn Remote-Operations-Useful-Definitions.asn -c -ber -print

depends: Remote-Operations-Generic-ROS-PDUs.c \
Remote-Operations-Information-Objects.c Remote-Operations-Useful-Definitions.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) Remote-Operations-Generic-ROS-PDUsEnc.c
	$(RM) Remote-Operations-Generic-ROS-PDUsDec.c
	$(RM) Remote-Operations-Generic-ROS-PDUs.c
	$(RM) Remote-Operations-Generic-ROS-PDUsPrint.c
	$(RM) $(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h 
	$(RM) Remote-Operations-Information-ObjectsEnc.c
	$(RM) Remote-Operations-Information-ObjectsDec.c
	$(RM) Remote-Operations-Information-Objects.c
	$(RM) Remote-Operations-Information-ObjectsPrint.c
	$(RM) $(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h 
	$(RM) Remote-Operations-Useful-DefinitionsEnc.c
	$(RM) Remote-Operations-Useful-DefinitionsDec.c
	$(RM) Remote-Operations-Useful-Definitions.c
	$(RM) Remote-Operations-Useful-DefinitionsPrint.c
	$(RM) $(HFILESDIR)$(PS)Remote-Operations-Useful-Definitions.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM_MSVC_FILES)

