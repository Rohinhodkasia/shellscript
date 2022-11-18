# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

# include directories
OSROOTDIR = ../../..
LIBDIR  = $(OSROOTDIR)/cpp/lib
RTSRCDIR = $(OSROOTDIR)/rtsrc
BERSRCDIR = $(OSROOTDIR)/rtbersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)/asn1type.h $(RTSRCDIR)/asn1CppTypes.h  \
$(BERSRCDIR)/asn1ber.h $(BERSRCDIR)/asn1BerCppTypes.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_)
CCFLAGS = $(CFLAGS)
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

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .cpp .h rules
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUsEnc.cpp \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUsDec.cpp \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUs.cpp \
$(SRCDIR)/Remote-Operations-Generic-ROS-PDUsPrint.cpp \
$(HFILESDIR)/Remote-Operations-Generic-ROS-PDUs.h \
$(SRCDIR)/Remote-Operations-Information-ObjectsEnc.cpp \
$(SRCDIR)/Remote-Operations-Information-ObjectsDec.cpp \
$(SRCDIR)/Remote-Operations-Information-Objects.cpp \
$(SRCDIR)/Remote-Operations-Information-ObjectsPrint.cpp \
$(HFILESDIR)/Remote-Operations-Information-Objects.h \
$(SRCDIR)/Remote-Operations-Useful-DefinitionsEnc.cpp \
$(SRCDIR)/Remote-Operations-Useful-DefinitionsDec.cpp \
$(SRCDIR)/Remote-Operations-Useful-Definitions.cpp \
$(SRCDIR)/Remote-Operations-Useful-DefinitionsPrint.cpp \
$(HFILESDIR)/Remote-Operations-Useful-Definitions.h \
$(HFILESDIR)/rtkey.h \
: Remote-Operations-Generic-ROS-PDUs.asn Remote-Operations-Information-Objects.asn Remote-Operations-Useful-Definitions.asn $(OSROOTDIR)/bin/asn1c$(EXE)
	$(ASN1C) Remote-Operations-Generic-ROS-PDUs.asn Remote-Operations-Information-Objects.asn Remote-Operations-Useful-Definitions.asn -cpp -ber -print

depends: Remote-Operations-Generic-ROS-PDUs.cpp \
Remote-Operations-Information-Objects.cpp \
Remote-Operations-Useful-Definitions.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) Remote-Operations-Generic-ROS-PDUsEnc.cpp
	$(RM) Remote-Operations-Generic-ROS-PDUsDec.cpp
	$(RM) Remote-Operations-Generic-ROS-PDUs.cpp
	$(RM) Remote-Operations-Generic-ROS-PDUsPrint.cpp
	$(RM) $(HFILESDIR)$(PS)Remote-Operations-Generic-ROS-PDUs.h 
	$(RM) Remote-Operations-Information-ObjectsEnc.cpp
	$(RM) Remote-Operations-Information-ObjectsDec.cpp
	$(RM) Remote-Operations-Information-Objects.cpp
	$(RM) Remote-Operations-Information-ObjectsPrint.cpp
	$(RM) $(HFILESDIR)$(PS)Remote-Operations-Information-Objects.h 
	$(RM) Remote-Operations-Useful-DefinitionsEnc.cpp
	$(RM) Remote-Operations-Useful-DefinitionsDec.cpp
	$(RM) Remote-Operations-Useful-Definitions.cpp
	$(RM) Remote-Operations-Useful-DefinitionsPrint.cpp
	$(RM) $(HFILESDIR)$(PS)Remote-Operations-Useful-Definitions.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM_MSVC_FILES)

