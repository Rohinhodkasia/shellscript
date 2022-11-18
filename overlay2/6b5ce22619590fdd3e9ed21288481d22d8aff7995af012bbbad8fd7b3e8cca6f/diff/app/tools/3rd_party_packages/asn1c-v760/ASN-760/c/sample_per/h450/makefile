# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

IPATHS  = -I. -I../h323_ui -I$(SRCDIR) -I$(RTSRCDIR) -I$(PERSRCDIR) \
-I$(OSROOTDIR) $(IPATHS_)

H323_OBJECTS = \
../h323_ui/H323-MESSAGES$(OBJ) \
../h323_ui/H323-MESSAGESEnc$(OBJ) \
../h323_ui/H323-MESSAGESDec$(OBJ) \
../h323_ui/H235-SECURITY-MESSAGES$(OBJ) \
../h323_ui/H235-SECURITY-MESSAGESEnc$(OBJ) \
../h323_ui/H235-SECURITY-MESSAGESDec$(OBJ) \
../h323_ui/H323-MESSAGESPrint$(OBJ) \
../h323_ui/H235-SECURITY-MESSAGESPrint$(OBJ)

H4501_OBJECTS = \
H4501-Supplementary-ServiceAPDU-Structure$(OBJ) \
Remote-Operations-Apdus$(OBJ) \
Addressing-Data-Elements$(OBJ) \
H225-generic-parameters-definition$(OBJ) \
Manufacturer-specific-service-extension-definition$(OBJ) \
H4501-Supplementary-ServiceAPDU-StructurePrint$(OBJ) \
Remote-Operations-ApdusPrint$(OBJ) \
Addressing-Data-ElementsPrint$(OBJ) \
H225-generic-parameters-definitionPrint$(OBJ) \
Manufacturer-specific-service-extension-definitionPrint$(OBJ)

H4501_DECOBJECTS = \
H4501-Supplementary-ServiceAPDU-StructureDec$(OBJ) \
Remote-Operations-ApdusDec$(OBJ) \
Addressing-Data-ElementsDec$(OBJ) \
H225-generic-parameters-definitionDec$(OBJ) \
Manufacturer-specific-service-extension-definitionDec$(OBJ)

H4501_ENCOBJECTS = \
H4501-Supplementary-ServiceAPDU-StructureEnc$(OBJ) \
Remote-Operations-ApdusEnc$(OBJ) \
Addressing-Data-ElementsEnc$(OBJ) \
H225-generic-parameters-definitionEnc$(OBJ) \
Manufacturer-specific-service-extension-definitionEnc$(OBJ)

ROSE_OBJECTS = \
Remote-Operations-Information-Objects$(OBJ) \
Remote-Operations-Information-ObjectsPrint$(OBJ) 

ROSE_DECOBJECTS = \
Remote-Operations-Information-ObjectsDec$(OBJ) 

ROSE_ENCOBJECTS = \
Remote-Operations-Information-ObjectsEnc$(OBJ) 

OBJECTS  = $(ROSE_OBJECTS) $(H4501_OBJECTS) 
DECOBJECTS  = $(ROSE_DECOBJECTS) $(H4501_DECOBJECTS) 
ENCOBJECTS  = $(ROSE_ENCOBJECTS) $(H4501_ENCOBJECTS) 
HFILES   = $(PERHFILES)
LIBNAMES = $(LIBDIR)/$(PERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
LINKLIBS = $(PSLIBS)

all : $(OBJECTS) reader$(EXE)

reader$(EXE) : $(OBJECTS) reader$(OBJ) $(LIBNAMES) $(DECOBJECTS) $(ENCOBJECTS)
	$(LINK) reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
	   $(H323_OBJECTS) $(LINKOPT) $(LPATHS) $(LINKLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

H4501-Supplementary-ServiceAPDU-Structure.c \
H4501-Supplementary-ServiceAPDU-StructureDec.c \
H4501-Supplementary-ServiceAPDU-StructureEnc.c \
H4501-Supplementary-ServiceAPDU-StructurePrint.c \
H4501-Supplementary-ServiceAPDU-Structure.h \
Remote-Operations-Apdus.c \
Remote-Operations-ApdusDec.c \
Remote-Operations-ApdusEnc.c \
Remote-Operations-ApdusPrint.c \
Remote-Operations-Apdus.h \
Addressing-Data-Elements.c \
Addressing-Data-ElementsDec.c \
Addressing-Data-ElementsEnc.c \
Addressing-Data-ElementsPrint.c \
Addressing-Data-Elements.h \
H225-generic-parameters-definition.c \
H225-generic-parameters-definitionDec.c \
H225-generic-parameters-definitionEnc.c \
H225-generic-parameters-definitionPrint.c \
H225-generic-parameters-definition.h \
Manufacturer-specific-service-extension-definition.c \
Manufacturer-specific-service-extension-definitionDec.c \
Manufacturer-specific-service-extension-definitionEnc.c \
Manufacturer-specific-service-extension-definitionPrint.c \
Manufacturer-specific-service-extension-definition.h : \
h4501.asn h450.cfg $(ASN1C)
	$(ASN1C) h4501.asn -c -per -config h450.cfg -trace -print -strict-size

Remote-Operations-Information-Objects.c \
Remote-Operations-Information-ObjectsDec.c \
Remote-Operations-Information-ObjectsEnc.c \
Remote-Operations-Information-ObjectsPrint.c \
Remote-Operations-Information-Objects.h : x880.asn h450.cfg $(ASN1C)
	$(ASN1C) x880.asn -c -per -config h450.cfg -trace -print -strict-size

depends: H4501-Supplementary-ServiceAPDU-Structure.c Remote-Operations-Apdus.c \
Addressing-Data-Elements.c H225-generic-parameters-definition.c \
Manufacturer-specific-service-extension-definition.c \
Remote-Operations-Information-Objects.c ../h323_ui/H323-MESSAGES.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) *$(OBJ)
	$(RM) H4501-Supplementary-ServiceAPDU-Structure*.c
	$(RM) H4501-Supplementary-ServiceAPDU-Structure.h
	$(RM) Remote*.c
	$(RM) Remote*.h
	$(RM) Addressing-Data-Elements*.c
	$(RM) Addressing-Data-Elements.h
	$(RM) H225-generic-parameters-definition*.c
	$(RM) H225-generic-parameters-definition.h
	$(RM) Manufacturer-specific-service-extension-definition*.c
	$(RM) Manufacturer-specific-service-extension-definition.h
	$(RM) reader$(EXE)
	$(RM_MSVC_FILES)
	$(RM) *.opt
	$(RM) *.log
	$(RM) *~
	$(RM) rtkey.h
