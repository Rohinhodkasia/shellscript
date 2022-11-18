# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

SPECSDIR = ..$(PS)..$(PS)..$(PS)specs$(PS)
ASN1FILE = $(SPECSDIR)camel$(PS)camel.asn

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
BERSRCDIR = $(OSROOTDIR)$(PS)rtbersrc
XMLSRCDIR = $(OSROOTDIR)$(PS)rtxmlsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(BERSRCDIR)$(PS)asn1ber.h  \
$(XMLSRCDIR)$(PS)osrtxml.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(SPECSDIR)gsm_map -I$(SPECSDIR)cap \
-I$(SPECSDIR)ROSE -I$(SPECSDIR)camel -I$(RTSRCDIR) -I$(BERSRCDIR) \
-I$(XMLSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)$(PS)$(LIBPFX)asn1ber$(A) $(LIBDIR)$(PS)$(LIBPFX)asn1xml$(A) \
$(LIBDIR)$(PS)$(LIBPFX)asn1rt$(A)
LLIBS = $(LLBER) $(LLXML) $(LLRT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
CAP-datatypes$(OBJ) \
CAP-errortypes$(OBJ) \
MAP-CommonDataTypes$(OBJ) \
MAP-BS-Code$(OBJ) \
MAP-TS-Code$(OBJ) \
MAP-MS-DataTypes$(OBJ) \
MAP-ExtensionDataTypes$(OBJ) \
MAP-CH-DataTypes$(OBJ)

ENCOBJECTS =  \
CAP-datatypesEnc$(OBJ) \
CAP-errortypesEnc$(OBJ) \
MAP-CommonDataTypesEnc$(OBJ) \
MAP-BS-CodeEnc$(OBJ) \
MAP-TS-CodeEnc$(OBJ) \
MAP-MS-DataTypesEnc$(OBJ) \
MAP-ExtensionDataTypesEnc$(OBJ) \
MAP-CH-DataTypesEnc$(OBJ)

DECOBJECTS =  \
CAP-datatypesDec$(OBJ) \
CAP-errortypesDec$(OBJ) \
MAP-CommonDataTypesDec$(OBJ) \
MAP-BS-CodeDec$(OBJ) \
MAP-TS-CodeDec$(OBJ) \
MAP-MS-DataTypesDec$(OBJ) \
MAP-ExtensionDataTypesDec$(OBJ) \
MAP-CH-DataTypesDec$(OBJ)

PRTOBJECTS =  \
CAP-datatypesPrint$(OBJ) \
CAP-errortypesPrint$(OBJ) \
MAP-CommonDataTypesPrint$(OBJ) \
MAP-BS-CodePrint$(OBJ) \
MAP-TS-CodePrint$(OBJ) \
MAP-MS-DataTypesPrint$(OBJ) \
MAP-ExtensionDataTypesPrint$(OBJ) \
MAP-CH-DataTypesPrint$(OBJ)

P2SOBJECTS =  \
CAP-datatypesPrtToStr$(OBJ) \
CAP-errortypesPrtToStr$(OBJ) \
MAP-CommonDataTypesPrtToStr$(OBJ) \
MAP-BS-CodePrtToStr$(OBJ) \
MAP-TS-CodePrtToStr$(OBJ) \
MAP-MS-DataTypesPrtToStr$(OBJ) \
MAP-ExtensionDataTypesPrtToStr$(OBJ) \
MAP-CH-DataTypesPrtToStr$(OBJ)

P2MOBJECTS =  \
CAP-datatypesPrtToStrm$(OBJ) \
CAP-errortypesPrtToStrm$(OBJ) \
MAP-CommonDataTypesPrtToStrm$(OBJ) \
MAP-BS-CodePrtToStrm$(OBJ) \
MAP-TS-CodePrtToStrm$(OBJ) \
MAP-MS-DataTypesPrtToStrm$(OBJ) \
MAP-ExtensionDataTypesPrtToStrm$(OBJ) \
MAP-CH-DataTypesPrtToStrm$(OBJ)

TESTOBJECTS =  \
CAP-datatypesTest$(OBJ) \
CAP-errortypesTest$(OBJ) \
MAP-CommonDataTypesTest$(OBJ) \
MAP-BS-CodeTest$(OBJ) \
MAP-TS-CodeTest$(OBJ) \
MAP-MS-DataTypesTest$(OBJ) \
MAP-ExtensionDataTypesTest$(OBJ) \
MAP-CH-DataTypesTest$(OBJ)

CPYOBJECTS =  \
CAP-datatypesCopy$(OBJ) \
CAP-errortypesCopy$(OBJ) \
MAP-CommonDataTypesCopy$(OBJ) \
MAP-BS-CodeCopy$(OBJ) \
MAP-TS-CodeCopy$(OBJ) \
MAP-MS-DataTypesCopy$(OBJ) \
MAP-ExtensionDataTypesCopy$(OBJ) \
MAP-CH-DataTypesCopy$(OBJ)

CMPOBJECTS =  \
CAP-datatypesCompare$(OBJ) \
CAP-errortypesCompare$(OBJ) \
MAP-CommonDataTypesCompare$(OBJ) \
MAP-BS-CodeCompare$(OBJ) \
MAP-TS-CodeCompare$(OBJ) \
MAP-MS-DataTypesCompare$(OBJ) \
MAP-ExtensionDataTypesCompare$(OBJ) \
MAP-CH-DataTypesCompare$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
$(P2SOBJECTS) $(P2MOBJECTS) $(TESTOBJECTS) $(CPYOBJECTS) $(CMPOBJECTS) \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(TESTOBJECTS) \
 $(PRTOBJECTS) $(P2MOBJECTS) $(P2SOBJECTS) $(CPYOBJECTS) $(CMPOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS) $(P2MOBJECTS) $(P2SOBJECTS) $(CPYOBJECTS) $(CMPOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)CAP-datatypes.h $(HFILESDIR)$(PS)CAP-errortypes.h \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-BS-Code.h \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)MAP-MS-DataTypes.h \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)MAP-CH-DataTypes.h \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
$(SRCDIR)$(PS)CAP-datatypesEnc.c \
$(SRCDIR)$(PS)CAP-datatypesDec.c \
$(SRCDIR)$(PS)CAP-datatypes.c \
$(SRCDIR)$(PS)CAP-datatypesPrint.c \
$(SRCDIR)$(PS)CAP-datatypesCopy.c \
$(SRCDIR)$(PS)CAP-datatypesCompare.c \
$(SRCDIR)$(PS)CAP-datatypesPrtToStr.c \
$(SRCDIR)$(PS)CAP-datatypesPrtToStrm.c \
$(SRCDIR)$(PS)CAP-datatypesTest.c \
$(HFILESDIR)$(PS)CAP-datatypes.h \
$(SRCDIR)$(PS)CAP-errortypesEnc.c \
$(SRCDIR)$(PS)CAP-errortypesDec.c \
$(SRCDIR)$(PS)CAP-errortypes.c \
$(SRCDIR)$(PS)CAP-errortypesPrint.c \
$(SRCDIR)$(PS)CAP-errortypesCopy.c \
$(SRCDIR)$(PS)CAP-errortypesCompare.c \
$(SRCDIR)$(PS)CAP-errortypesPrtToStr.c \
$(SRCDIR)$(PS)CAP-errortypesPrtToStrm.c \
$(SRCDIR)$(PS)CAP-errortypesTest.c \
$(HFILESDIR)$(PS)CAP-errortypes.h \
$(SRCDIR)$(PS)MAP-CommonDataTypesEnc.c \
$(SRCDIR)$(PS)MAP-CommonDataTypesDec.c \
$(SRCDIR)$(PS)MAP-CommonDataTypes.c \
$(SRCDIR)$(PS)MAP-CommonDataTypesPrint.c \
$(SRCDIR)$(PS)MAP-CommonDataTypesCopy.c \
$(SRCDIR)$(PS)MAP-CommonDataTypesCompare.c \
$(SRCDIR)$(PS)MAP-CommonDataTypesPrtToStr.c \
$(SRCDIR)$(PS)MAP-CommonDataTypesPrtToStrm.c \
$(SRCDIR)$(PS)MAP-CommonDataTypesTest.c \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h \
$(SRCDIR)$(PS)MAP-BS-CodeEnc.c \
$(SRCDIR)$(PS)MAP-BS-CodeDec.c \
$(SRCDIR)$(PS)MAP-BS-Code.c \
$(SRCDIR)$(PS)MAP-BS-CodePrint.c \
$(SRCDIR)$(PS)MAP-BS-CodeCopy.c \
$(SRCDIR)$(PS)MAP-BS-CodeCompare.c \
$(SRCDIR)$(PS)MAP-BS-CodePrtToStr.c \
$(SRCDIR)$(PS)MAP-BS-CodePrtToStrm.c \
$(SRCDIR)$(PS)MAP-BS-CodeTest.c \
$(HFILESDIR)$(PS)MAP-BS-Code.h \
$(SRCDIR)$(PS)MAP-TS-CodeEnc.c \
$(SRCDIR)$(PS)MAP-TS-CodeDec.c \
$(SRCDIR)$(PS)MAP-TS-Code.c \
$(SRCDIR)$(PS)MAP-TS-CodePrint.c \
$(SRCDIR)$(PS)MAP-TS-CodeCopy.c \
$(SRCDIR)$(PS)MAP-TS-CodeCompare.c \
$(SRCDIR)$(PS)MAP-TS-CodePrtToStr.c \
$(SRCDIR)$(PS)MAP-TS-CodePrtToStrm.c \
$(SRCDIR)$(PS)MAP-TS-CodeTest.c \
$(HFILESDIR)$(PS)MAP-TS-Code.h \
$(SRCDIR)$(PS)MAP-MS-DataTypesEnc.c \
$(SRCDIR)$(PS)MAP-MS-DataTypesDec.c \
$(SRCDIR)$(PS)MAP-MS-DataTypes.c \
$(SRCDIR)$(PS)MAP-MS-DataTypesPrint.c \
$(SRCDIR)$(PS)MAP-MS-DataTypesCopy.c \
$(SRCDIR)$(PS)MAP-MS-DataTypesCompare.c \
$(SRCDIR)$(PS)MAP-MS-DataTypesPrtToStr.c \
$(SRCDIR)$(PS)MAP-MS-DataTypesPrtToStrm.c \
$(SRCDIR)$(PS)MAP-MS-DataTypesTest.c \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h \
$(SRCDIR)$(PS)MAP-ExtensionDataTypesEnc.c \
$(SRCDIR)$(PS)MAP-ExtensionDataTypesDec.c \
$(SRCDIR)$(PS)MAP-ExtensionDataTypes.c \
$(SRCDIR)$(PS)MAP-ExtensionDataTypesPrint.c \
$(SRCDIR)$(PS)MAP-ExtensionDataTypesCopy.c \
$(SRCDIR)$(PS)MAP-ExtensionDataTypesCompare.c \
$(SRCDIR)$(PS)MAP-ExtensionDataTypesPrtToStr.c \
$(SRCDIR)$(PS)MAP-ExtensionDataTypesPrtToStrm.c \
$(SRCDIR)$(PS)MAP-ExtensionDataTypesTest.c \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h \
$(SRCDIR)$(PS)MAP-CH-DataTypesEnc.c \
$(SRCDIR)$(PS)MAP-CH-DataTypesDec.c \
$(SRCDIR)$(PS)MAP-CH-DataTypes.c \
$(SRCDIR)$(PS)MAP-CH-DataTypesPrint.c \
$(SRCDIR)$(PS)MAP-CH-DataTypesCopy.c \
$(SRCDIR)$(PS)MAP-CH-DataTypesCompare.c \
$(SRCDIR)$(PS)MAP-CH-DataTypesPrtToStr.c \
$(SRCDIR)$(PS)MAP-CH-DataTypesPrtToStrm.c \
$(SRCDIR)$(PS)MAP-CH-DataTypesTest.c \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h \
$(HFILESDIR)$(PS)rtkey.h \
: $(ASN1FILE) $(ASN1C)
	$(ASN1C) $(ASN1FILE) -c -ber -xml -compare -copy -depends -html -I $(SPECSDIR)gsm_map -I $(SPECSDIR)cap -I $(SPECSDIR)ROSE -I $(SPECSDIR)camel -print -prttostr -prttostrm -strict-size -table-unions -test -fqtvalue

depends: CAP-datatypes.c CAP-errortypes.c MAP-CommonDataTypes.c MAP-BS-Code.c MAP-MS-DataTypes.c MAP-ExtensionDataTypes.c MAP-CH-DataTypes.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) CAP-datatypesEnc.c
	$(RM) CAP-datatypesDec.c
	$(RM) CAP-datatypes.c
	$(RM) CAP-datatypesPrint.c
	$(RM) CAP-datatypesCopy.c
	$(RM) CAP-datatypesCompare.c
	$(RM) CAP-datatypesPrtToStr.c
	$(RM) CAP-datatypesPrtToStrm.c
	$(RM) CAP-datatypesTest.c
	$(RM) $(HFILESDIR)$(PS)CAP-datatypes.h 
	$(RM) CAP-datatypes.html
	$(RM) CAP-errortypesEnc.c
	$(RM) CAP-errortypesDec.c
	$(RM) CAP-errortypes.c
	$(RM) CAP-errortypesPrint.c
	$(RM) CAP-errortypesCopy.c
	$(RM) CAP-errortypesCompare.c
	$(RM) CAP-errortypesPrtToStr.c
	$(RM) CAP-errortypesPrtToStrm.c
	$(RM) CAP-errortypesTest.c
	$(RM) $(HFILESDIR)$(PS)CAP-errortypes.h 
	$(RM) CAP-errortypes.html
	$(RM) MAP-CommonDataTypesEnc.c
	$(RM) MAP-CommonDataTypesDec.c
	$(RM) MAP-CommonDataTypes.c
	$(RM) MAP-CommonDataTypesPrint.c
	$(RM) MAP-CommonDataTypesCopy.c
	$(RM) MAP-CommonDataTypesCompare.c
	$(RM) MAP-CommonDataTypesPrtToStr.c
	$(RM) MAP-CommonDataTypesPrtToStrm.c
	$(RM) MAP-CommonDataTypesTest.c
	$(RM) $(HFILESDIR)$(PS)MAP-CommonDataTypes.h 
	$(RM) MAP-CommonDataTypes.html
	$(RM) MAP-BS-CodeEnc.c
	$(RM) MAP-BS-CodeDec.c
	$(RM) MAP-BS-Code.c
	$(RM) MAP-BS-CodePrint.c
	$(RM) MAP-BS-CodeCopy.c
	$(RM) MAP-BS-CodeCompare.c
	$(RM) MAP-BS-CodePrtToStr.c
	$(RM) MAP-BS-CodePrtToStrm.c
	$(RM) MAP-BS-CodeTest.c
	$(RM) $(HFILESDIR)$(PS)MAP-BS-Code.h 
	$(RM) MAP-BS-Code.html
	$(RM) MAP-TS-CodeEnc.c
	$(RM) MAP-TS-CodeDec.c
	$(RM) MAP-TS-Code.c
	$(RM) MAP-TS-CodePrint.c
	$(RM) MAP-TS-CodeCopy.c
	$(RM) MAP-TS-CodeCompare.c
	$(RM) MAP-TS-CodePrtToStr.c
	$(RM) MAP-TS-CodePrtToStrm.c
	$(RM) MAP-TS-CodeTest.c
	$(RM) $(HFILESDIR)$(PS)MAP-TS-Code.h 
	$(RM) MAP-TS-Code.html
	$(RM) MAP-MS-DataTypesEnc.c
	$(RM) MAP-MS-DataTypesDec.c
	$(RM) MAP-MS-DataTypes.c
	$(RM) MAP-MS-DataTypesPrint.c
	$(RM) MAP-MS-DataTypesCopy.c
	$(RM) MAP-MS-DataTypesCompare.c
	$(RM) MAP-MS-DataTypesPrtToStr.c
	$(RM) MAP-MS-DataTypesPrtToStrm.c
	$(RM) MAP-MS-DataTypesTest.c
	$(RM) $(HFILESDIR)$(PS)MAP-MS-DataTypes.h 
	$(RM) MAP-MS-DataTypes.html
	$(RM) MAP-ExtensionDataTypesEnc.c
	$(RM) MAP-ExtensionDataTypesDec.c
	$(RM) MAP-ExtensionDataTypes.c
	$(RM) MAP-ExtensionDataTypesPrint.c
	$(RM) MAP-ExtensionDataTypesCopy.c
	$(RM) MAP-ExtensionDataTypesCompare.c
	$(RM) MAP-ExtensionDataTypesPrtToStr.c
	$(RM) MAP-ExtensionDataTypesPrtToStrm.c
	$(RM) MAP-ExtensionDataTypesTest.c
	$(RM) $(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h 
	$(RM) MAP-ExtensionDataTypes.html
	$(RM) MAP-CH-DataTypesEnc.c
	$(RM) MAP-CH-DataTypesDec.c
	$(RM) MAP-CH-DataTypes.c
	$(RM) MAP-CH-DataTypesPrint.c
	$(RM) MAP-CH-DataTypesCopy.c
	$(RM) MAP-CH-DataTypesCompare.c
	$(RM) MAP-CH-DataTypesPrtToStr.c
	$(RM) MAP-CH-DataTypesPrtToStrm.c
	$(RM) MAP-CH-DataTypesTest.c
	$(RM) $(HFILESDIR)$(PS)MAP-CH-DataTypes.h 
	$(RM) MAP-CH-DataTypes.html
	$(RM) $(HFILESDIR)$(PS)MAP-ER-DataTypes.h 
	$(RM) MAP-ER-DataTypes.html
	$(RM) $(HFILESDIR)$(PS)MAP-OM-DataTypes.h 
	$(RM) MAP-OM-DataTypes.html
	$(RM) $(HFILESDIR)$(PS)MAP-SS-DataTypes.h 
	$(RM) MAP-SS-DataTypes.html
	$(RM) $(HFILESDIR)$(PS)MAP-SS-Code.h 
	$(RM) MAP-SS-Code.html
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM) message.dat
	$(RM_MSVC_FILES)
	$(RM) *.dat
	$(RM) asn1-style.css
