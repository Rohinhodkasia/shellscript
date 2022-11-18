# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

SPECSDIR = ../../../specs/lte-rrc/rel15

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)c$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
PERSRCDIR = $(OSROOTDIR)$(PS)rtpersrc
XMLSRCDIR = $(OSROOTDIR)$(PS)rtxmlsrc
SRCDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(PERSRCDIR)$(PS)asn1per.h  \
$(XMLSRCDIR)$(PS)osrtxml.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(PERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1per$(A) $(LIBDIR)/$(LIBPFX)asn1xml$(A) \
$(LIBDIR)/$(LIBPFX)asn1rt$(A)

LLIBS = $(LLPFX)asn1per$(LLAEXT) $(LLPFX)asn1xml$(LLAEXT) \
$(LLPFX)asn1rt$(LLAEXT) $(LLSYS)

LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
EUTRA-InterNodeDefinitions$(OBJ) \
EUTRA-RRC-Definitions$(OBJ) \
EUTRA-Sidelink-Preconf$(OBJ) \
EUTRA-UE-Variables$(OBJ) \
NBIOT-InterNodeDefinitions$(OBJ) \
NBIOT-RRC-Definitions$(OBJ) \
NBIOT-UE-Variables$(OBJ) \
PC5-RRC-Definitions$(OBJ)

ENCOBJECTS =  \
EUTRA-InterNodeDefinitionsEnc$(OBJ) \
EUTRA-RRC-DefinitionsEnc$(OBJ) \
EUTRA-Sidelink-PreconfEnc$(OBJ) \
EUTRA-UE-VariablesEnc$(OBJ) \
NBIOT-InterNodeDefinitionsEnc$(OBJ) \
NBIOT-RRC-DefinitionsEnc$(OBJ) \
NBIOT-UE-VariablesEnc$(OBJ) \
PC5-RRC-DefinitionsEnc$(OBJ)

DECOBJECTS =  \
EUTRA-InterNodeDefinitionsDec$(OBJ) \
EUTRA-RRC-DefinitionsDec$(OBJ) \
EUTRA-Sidelink-PreconfDec$(OBJ) \
EUTRA-UE-VariablesDec$(OBJ) \
NBIOT-InterNodeDefinitionsDec$(OBJ) \
NBIOT-RRC-DefinitionsDec$(OBJ) \
NBIOT-UE-VariablesDec$(OBJ) \
PC5-RRC-DefinitionsDec$(OBJ)

PRTOBJECTS =  \
EUTRA-InterNodeDefinitionsPrint$(OBJ) \
EUTRA-RRC-DefinitionsPrint$(OBJ) \
EUTRA-Sidelink-PreconfPrint$(OBJ) \
EUTRA-UE-VariablesPrint$(OBJ) \
NBIOT-InterNodeDefinitionsPrint$(OBJ) \
NBIOT-RRC-DefinitionsPrint$(OBJ) \
NBIOT-UE-VariablesPrint$(OBJ) \
PC5-RRC-DefinitionsPrint$(OBJ)

P2MOBJECTS =  \
EUTRA-InterNodeDefinitionsPrtToStrm$(OBJ) \
EUTRA-RRC-DefinitionsPrtToStrm$(OBJ) \
EUTRA-Sidelink-PreconfPrtToStrm$(OBJ) \
EUTRA-UE-VariablesPrtToStrm$(OBJ) \
NBIOT-InterNodeDefinitionsPrtToStrm$(OBJ) \
NBIOT-RRC-DefinitionsPrtToStrm$(OBJ) \
NBIOT-UE-VariablesPrtToStrm$(OBJ) \
PC5-RRC-DefinitionsPrtToStrm$(OBJ)

TESTOBJECTS =  \
EUTRA-InterNodeDefinitionsTest$(OBJ) \
EUTRA-RRC-DefinitionsTest$(OBJ) \
EUTRA-Sidelink-PreconfTest$(OBJ) \
EUTRA-UE-VariablesTest$(OBJ) \
NBIOT-InterNodeDefinitionsTest$(OBJ) \
NBIOT-RRC-DefinitionsTest$(OBJ) \
NBIOT-UE-VariablesTest$(OBJ) \
PC5-RRC-DefinitionsTest$(OBJ)

CPYOBJECTS =  \
EUTRA-InterNodeDefinitionsCopy$(OBJ) \
EUTRA-RRC-DefinitionsCopy$(OBJ) \
EUTRA-Sidelink-PreconfCopy$(OBJ) \
EUTRA-UE-VariablesCopy$(OBJ) \
NBIOT-InterNodeDefinitionsCopy$(OBJ) \
NBIOT-RRC-DefinitionsCopy$(OBJ) \
NBIOT-UE-VariablesCopy$(OBJ) \
PC5-RRC-DefinitionsCopy$(OBJ)

CMPOBJECTS =  \
EUTRA-InterNodeDefinitionsCompare$(OBJ) \
EUTRA-RRC-DefinitionsCompare$(OBJ) \
EUTRA-Sidelink-PreconfCompare$(OBJ) \
EUTRA-UE-VariablesCompare$(OBJ) \
NBIOT-InterNodeDefinitionsCompare$(OBJ) \
NBIOT-RRC-DefinitionsCompare$(OBJ) \
NBIOT-UE-VariablesCompare$(OBJ) \
PC5-RRC-DefinitionsCompare$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
$(P2SOBJECTS) $(P2MOBJECTS) $(TESTOBJECTS) $(CPYOBJECTS) $(CMPOBJECTS) \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
 $(PRTOBJECTS) $(P2MOBJECTS) $(P2SOBJECTS) $(CPYOBJECTS) $(CMPOBJECTS)

# Note: add -Xlinker -Map=writer.map on Linux to get map
writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS) $(P2MOBJECTS) $(P2SOBJECTS) $(CPYOBJECTS) $(CMPOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
EUTRA-InterNodeDefinitionsEnc.c \
EUTRA-InterNodeDefinitionsDec.c \
EUTRA-InterNodeDefinitions.c \
EUTRA-InterNodeDefinitionsPrint.c \
EUTRA-InterNodeDefinitionsCopy.c \
EUTRA-InterNodeDefinitionsCompare.c \
EUTRA-InterNodeDefinitionsPrtToStrm.c \
EUTRA-InterNodeDefinitionsTest.c \
EUTRA-InterNodeDefinitions.h \
EUTRA-RRC-DefinitionsEnc.c \
EUTRA-RRC-DefinitionsDec.c \
EUTRA-RRC-Definitions.c \
EUTRA-RRC-DefinitionsPrint.c \
EUTRA-RRC-DefinitionsCopy.c \
EUTRA-RRC-DefinitionsCompare.c \
EUTRA-RRC-DefinitionsPrtToStrm.c \
EUTRA-RRC-DefinitionsTest.c \
EUTRA-RRC-Definitions.h \
EUTRA-Sidelink-PreconfEnc.c \
EUTRA-Sidelink-PreconfDec.c \
EUTRA-Sidelink-Preconf.c \
EUTRA-Sidelink-PreconfPrint.c \
EUTRA-Sidelink-PreconfCopy.c \
EUTRA-Sidelink-PreconfCompare.c \
EUTRA-Sidelink-PreconfPrtToStrm.c \
EUTRA-Sidelink-PreconfTest.c \
EUTRA-Sidelink-Preconf.h \
EUTRA-UE-VariablesEnc.c \
EUTRA-UE-VariablesDec.c \
EUTRA-UE-Variables.c \
EUTRA-UE-VariablesPrint.c \
EUTRA-UE-VariablesCopy.c \
EUTRA-UE-VariablesCompare.c \
EUTRA-UE-VariablesPrtToStrm.c \
EUTRA-UE-VariablesTest.c \
EUTRA-UE-Variables.h \
NBIOT-InterNodeDefinitionsEnc.c \
NBIOT-InterNodeDefinitionsDec.c \
NBIOT-InterNodeDefinitions.c \
NBIOT-InterNodeDefinitionsPrint.c \
NBIOT-InterNodeDefinitionsCopy.c \
NBIOT-InterNodeDefinitionsCompare.c \
NBIOT-InterNodeDefinitionsPrtToStrm.c \
NBIOT-InterNodeDefinitionsTest.c \
NBIOT-InterNodeDefinitions.h \
NBIOT-RRC-DefinitionsEnc.c \
NBIOT-RRC-DefinitionsDec.c \
NBIOT-RRC-Definitions.c \
NBIOT-RRC-DefinitionsPrint.c \
NBIOT-RRC-DefinitionsCopy.c \
NBIOT-RRC-DefinitionsCompare.c \
NBIOT-RRC-DefinitionsPrtToStrm.c \
NBIOT-RRC-DefinitionsTest.c \
NBIOT-RRC-Definitions.h \
NBIOT-UE-VariablesEnc.c \
NBIOT-UE-VariablesDec.c \
NBIOT-UE-Variables.c \
NBIOT-UE-VariablesPrint.c \
NBIOT-UE-VariablesCopy.c \
NBIOT-UE-VariablesCompare.c \
NBIOT-UE-VariablesPrtToStr.c \
NBIOT-UE-VariablesPrtToStrm.c \
NBIOT-UE-VariablesTest.c \
NBIOT-UE-Variables.h \
PC5-RRC-DefinitionsEnc.c \
PC5-RRC-DefinitionsDec.c \
PC5-RRC-Definitions.c \
PC5-RRC-DefinitionsPrint.c \
PC5-RRC-DefinitionsCopy.c \
PC5-RRC-DefinitionsCompare.c \
PC5-RRC-DefinitionsPrtToStrm.c \
PC5-RRC-DefinitionsTest.c \
PC5-RRC-Definitions.h \
rtkey.h \
: $(SPECSDIR)/EUTRA-InterNodeDefinitions.asn $(SPECSDIR)/EUTRA-RRC-Definitions.asn $(SPECSDIR)/EUTRA-Sidelink-Preconf.asn $(SPECSDIR)/EUTRA-UE-Variables.asn $(SPECSDIR)/NBIOT-InterNodeDefinitions.asn $(SPECSDIR)/NBIOT-RRC-Definitions.asn $(SPECSDIR)/NBIOT-UE-Variables.asn $(SPECSDIR)/PC5-RRC-Definitions.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(ASN1C) $(SPECSDIR)/EUTRA-InterNodeDefinitions.asn $(SPECSDIR)/EUTRA-RRC-Definitions.asn $(SPECSDIR)/EUTRA-Sidelink-Preconf.asn $(SPECSDIR)/EUTRA-UE-Variables.asn $(SPECSDIR)/NBIOT-InterNodeDefinitions.asn $(SPECSDIR)/NBIOT-RRC-Definitions.asn $(SPECSDIR)/NBIOT-UE-Variables.asn $(SPECSDIR)/PC5-RRC-Definitions.asn -c -uper -xml -compare -copy -html -I $(SPECSDIR) -pdu DL-CCCH-Message -print -prttostrm -table-unions -test -fqenum -fqtvalue -trace

depends: EUTRA-InterNodeDefinitions.c EUTRA-RRC-Definitions.c \
EUTRA-Sidelink-Preconf.c EUTRA-UE-Variables.c NBIOT-InterNodeDefinitions.c \
NBIOT-RRC-Definitions.c NBIOT-UE-Variables.c PC5-RRC-Definitions.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk


clean:
	$(RM) EUTRA-InterNodeDefinitionsEnc.c
	$(RM) EUTRA-InterNodeDefinitionsDec.c
	$(RM) EUTRA-InterNodeDefinitions.c
	$(RM) EUTRA-InterNodeDefinitionsPrint.c
	$(RM) EUTRA-InterNodeDefinitionsCopy.c
	$(RM) EUTRA-InterNodeDefinitionsCompare.c
	$(RM) EUTRA-InterNodeDefinitionsPrtToStrm.c
	$(RM) EUTRA-InterNodeDefinitionsTest.c
	$(RM) EUTRA-InterNodeDefinitions.h 
	$(RM) EUTRA-InterNodeDefinitions.html
	$(RM) EUTRA-RRC-DefinitionsEnc.c
	$(RM) EUTRA-RRC-DefinitionsDec.c
	$(RM) EUTRA-RRC-Definitions.c
	$(RM) EUTRA-RRC-DefinitionsPrint.c
	$(RM) EUTRA-RRC-DefinitionsCopy.c
	$(RM) EUTRA-RRC-DefinitionsCompare.c
	$(RM) EUTRA-RRC-DefinitionsPrtToStrm.c
	$(RM) EUTRA-RRC-DefinitionsTest.c
	$(RM) EUTRA-RRC-Definitions.h 
	$(RM) EUTRA-RRC-Definitions.html
	$(RM) EUTRA-Sidelink-PreconfEnc.c
	$(RM) EUTRA-Sidelink-PreconfDec.c
	$(RM) EUTRA-Sidelink-Preconf.c
	$(RM) EUTRA-Sidelink-PreconfPrint.c
	$(RM) EUTRA-Sidelink-PreconfCopy.c
	$(RM) EUTRA-Sidelink-PreconfCompare.c
	$(RM) EUTRA-Sidelink-PreconfPrtToStrm.c
	$(RM) EUTRA-Sidelink-PreconfTest.c
	$(RM) EUTRA-Sidelink-Preconf.h 
	$(RM) EUTRA-Sidelink-Preconf.html
	$(RM) EUTRA-UE-VariablesEnc.c
	$(RM) EUTRA-UE-VariablesDec.c
	$(RM) EUTRA-UE-Variables.c
	$(RM) EUTRA-UE-VariablesPrint.c
	$(RM) EUTRA-UE-VariablesCopy.c
	$(RM) EUTRA-UE-VariablesCompare.c
	$(RM) EUTRA-UE-VariablesPrtToStrm.c
	$(RM) EUTRA-UE-VariablesTest.c
	$(RM) EUTRA-UE-Variables.h 
	$(RM) EUTRA-UE-Variables.html
	$(RM) NBIOT-InterNodeDefinitionsEnc.c
	$(RM) NBIOT-InterNodeDefinitionsDec.c
	$(RM) NBIOT-InterNodeDefinitions.c
	$(RM) NBIOT-InterNodeDefinitionsPrint.c
	$(RM) NBIOT-InterNodeDefinitionsCopy.c
	$(RM) NBIOT-InterNodeDefinitionsCompare.c
	$(RM) NBIOT-InterNodeDefinitionsPrtToStrm.c
	$(RM) NBIOT-InterNodeDefinitionsTest.c
	$(RM) NBIOT-InterNodeDefinitions.h 
	$(RM) NBIOT-InterNodeDefinitions.html
	$(RM) NBIOT-RRC-DefinitionsEnc.c
	$(RM) NBIOT-RRC-DefinitionsDec.c
	$(RM) NBIOT-RRC-Definitions.c
	$(RM) NBIOT-RRC-DefinitionsPrint.c
	$(RM) NBIOT-RRC-DefinitionsCopy.c
	$(RM) NBIOT-RRC-DefinitionsCompare.c
	$(RM) NBIOT-RRC-DefinitionsPrtToStrm.c
	$(RM) NBIOT-RRC-DefinitionsTest.c
	$(RM) NBIOT-RRC-Definitions.h 
	$(RM) NBIOT-RRC-Definitions.html
	$(RM) NBIOT-UE-VariablesEnc.c
	$(RM) NBIOT-UE-VariablesDec.c
	$(RM) NBIOT-UE-Variables.c
	$(RM) NBIOT-UE-VariablesPrint.c
	$(RM) NBIOT-UE-VariablesCopy.c
	$(RM) NBIOT-UE-VariablesCompare.c
	$(RM) NBIOT-UE-VariablesPrtToStrm.c
	$(RM) NBIOT-UE-VariablesTest.c
	$(RM) NBIOT-UE-Variables.h 
	$(RM) NBIOT-UE-Variables.html
	$(RM) PC5-RRC-DefinitionsEnc.c
	$(RM) PC5-RRC-DefinitionsDec.c
	$(RM) PC5-RRC-Definitions.c
	$(RM) PC5-RRC-DefinitionsPrint.c
	$(RM) PC5-RRC-DefinitionsCopy.c
	$(RM) PC5-RRC-DefinitionsCompare.c
	$(RM) PC5-RRC-DefinitionsPrtToStrm.c
	$(RM) PC5-RRC-DefinitionsTest.c
	$(RM) PC5-RRC-Definitions.h 
	$(RM) PC5-RRC-Definitions.html
	$(RM) rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *.map
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.dat
	$(RM) asn1-style.css
