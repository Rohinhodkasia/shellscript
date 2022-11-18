# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

SPECSDIR = ..$(PS)..$(PS)..$(PS)specs
ASN1FILE = $(SPECSDIR)$(PS)camel$(PS)camel.asn

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)cpp$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
BERSRCDIR = $(OSROOTDIR)$(PS)rtbersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(RTSRCDIR)$(PS)asn1CppTypes.h \
$(BERSRCDIR)$(PS)asn1ber.h $(BERSRCDIR)$(PS)asn1BerCppTypes.h 
# compiler defs
CFLAGS = -c $(CVARSMTD_) $(CFLAGS_) $(CBLDTYPE_)
CCFLAGS = $(CFLAGS)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(SPECSDIR)$(PS)camel \
-I$(SPECSDIR)$(PS)gsm_map -I$(SPECSDIR)$(PS)cap -I$(SPECSDIR)$(PS)ROSE \
-I$(RTSRCDIR) -I$(BERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1ber$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1ber$(LLAEXT) $(LLPFX)asn1rt$(LLAEXT) $(LLSYS)
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

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
 $(TESTOBJECTS) $(PRTOBJECTS) $(P2MOBJECTS) $(P2SOBJECTS) $(CPYOBJECTS) \
 $(CMPOBJECTS)

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

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .cpp .h rules
$(SRCDIR)/CAP-datatypesEnc.cpp \
$(SRCDIR)/CAP-datatypesDec.cpp \
$(SRCDIR)/CAP-datatypes.cpp \
$(SRCDIR)/CAP-datatypesPrint.cpp \
$(SRCDIR)/CAP-datatypesCopy.cpp \
$(SRCDIR)/CAP-datatypesCompare.cpp \
$(SRCDIR)/CAP-datatypesPrtToStr.cpp \
$(SRCDIR)/CAP-datatypesPrtToStrm.cpp \
$(SRCDIR)/CAP-datatypesTest.cpp \
$(HFILESDIR)$(PS)CAP-datatypes.h \
$(SRCDIR)/CAP-errortypesEnc.cpp \
$(SRCDIR)/CAP-errortypesDec.cpp \
$(SRCDIR)/CAP-errortypes.cpp \
$(SRCDIR)/CAP-errortypesPrint.cpp \
$(SRCDIR)/CAP-errortypesCopy.cpp \
$(SRCDIR)/CAP-errortypesCompare.cpp \
$(SRCDIR)/CAP-errortypesPrtToStr.cpp \
$(SRCDIR)/CAP-errortypesPrtToStrm.cpp \
$(SRCDIR)/CAP-errortypesTest.cpp \
$(HFILESDIR)$(PS)CAP-errortypes.h \
$(SRCDIR)/MAP-CommonDataTypesEnc.cpp \
$(SRCDIR)/MAP-CommonDataTypesDec.cpp \
$(SRCDIR)/MAP-CommonDataTypes.cpp \
$(SRCDIR)/MAP-CommonDataTypesPrint.cpp \
$(SRCDIR)/MAP-CommonDataTypesCopy.cpp \
$(SRCDIR)/MAP-CommonDataTypesCompare.cpp \
$(SRCDIR)/MAP-CommonDataTypesPrtToStr.cpp \
$(SRCDIR)/MAP-CommonDataTypesPrtToStrm.cpp \
$(SRCDIR)/MAP-CommonDataTypesTest.cpp \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h \
$(SRCDIR)/MAP-BS-CodeEnc.cpp \
$(SRCDIR)/MAP-BS-CodeDec.cpp \
$(SRCDIR)/MAP-BS-Code.cpp \
$(SRCDIR)/MAP-BS-CodePrint.cpp \
$(SRCDIR)/MAP-BS-CodeCopy.cpp \
$(SRCDIR)/MAP-BS-CodeCompare.cpp \
$(SRCDIR)/MAP-BS-CodePrtToStr.cpp \
$(SRCDIR)/MAP-BS-CodePrtToStrm.cpp \
$(SRCDIR)/MAP-BS-CodeTest.cpp \
$(HFILESDIR)$(PS)MAP-BS-Code.h \
$(SRCDIR)/MAP-TS-CodeEnc.cpp \
$(SRCDIR)/MAP-TS-CodeDec.cpp \
$(SRCDIR)/MAP-TS-Code.cpp \
$(SRCDIR)/MAP-TS-CodePrint.cpp \
$(SRCDIR)/MAP-TS-CodeCopy.cpp \
$(SRCDIR)/MAP-TS-CodeCompare.cpp \
$(SRCDIR)/MAP-TS-CodePrtToStr.cpp \
$(SRCDIR)/MAP-TS-CodePrtToStrm.cpp \
$(SRCDIR)/MAP-TS-CodeTest.cpp \
$(HFILESDIR)$(PS)MAP-TS-Code.h \
$(SRCDIR)/MAP-MS-DataTypesEnc.cpp \
$(SRCDIR)/MAP-MS-DataTypesDec.cpp \
$(SRCDIR)/MAP-MS-DataTypes.cpp \
$(SRCDIR)/MAP-MS-DataTypesPrint.cpp \
$(SRCDIR)/MAP-MS-DataTypesCopy.cpp \
$(SRCDIR)/MAP-MS-DataTypesCompare.cpp \
$(SRCDIR)/MAP-MS-DataTypesPrtToStr.cpp \
$(SRCDIR)/MAP-MS-DataTypesPrtToStrm.cpp \
$(SRCDIR)/MAP-MS-DataTypesTest.cpp \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h \
$(SRCDIR)/MAP-ExtensionDataTypesEnc.cpp \
$(SRCDIR)/MAP-ExtensionDataTypesDec.cpp \
$(SRCDIR)/MAP-ExtensionDataTypes.cpp \
$(SRCDIR)/MAP-ExtensionDataTypesPrint.cpp \
$(SRCDIR)/MAP-ExtensionDataTypesCopy.cpp \
$(SRCDIR)/MAP-ExtensionDataTypesCompare.cpp \
$(SRCDIR)/MAP-ExtensionDataTypesPrtToStr.cpp \
$(SRCDIR)/MAP-ExtensionDataTypesPrtToStrm.cpp \
$(SRCDIR)/MAP-ExtensionDataTypesTest.cpp \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h \
$(SRCDIR)/MAP-CH-DataTypesEnc.cpp \
$(SRCDIR)/MAP-CH-DataTypesDec.cpp \
$(SRCDIR)/MAP-CH-DataTypes.cpp \
$(SRCDIR)/MAP-CH-DataTypesPrint.cpp \
$(SRCDIR)/MAP-CH-DataTypesCopy.cpp \
$(SRCDIR)/MAP-CH-DataTypesCompare.cpp \
$(SRCDIR)/MAP-CH-DataTypesPrtToStr.cpp \
$(SRCDIR)/MAP-CH-DataTypesPrtToStrm.cpp \
$(SRCDIR)/MAP-CH-DataTypesTest.cpp \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h \
$(HFILESDIR)$(PS)rtkey.h \
: $(ASN1FILE) $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -cpp -ber -compare -copy -depends -html -I $(SPECSDIR)$(PS)camel -I $(SPECSDIR)$(PS)gsm_map -I $(SPECSDIR)$(PS)cap -I $(SPECSDIR)$(PS)ROSE -print -prttostr -prttostrm -strict-size -table-unions -test

depends: CAP-datatypes.cpp CAP-errortypes.cpp MAP-CommonDataTypes.cpp \
MAP-BS-Code.cpp MAP-TS-Code.cpp MAP-MS-DataTypes.cpp \
MAP-ExtensionDataTypes.cpp MAP-CH-DataTypes.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) CAP-datatypesEnc.cpp
	$(RM) CAP-datatypesDec.cpp
	$(RM) CAP-datatypes.cpp
	$(RM) CAP-datatypesPrint.cpp
	$(RM) CAP-datatypesCopy.cpp
	$(RM) CAP-datatypesCompare.cpp
	$(RM) CAP-datatypesPrtToStr.cpp
	$(RM) CAP-datatypesPrtToStrm.cpp
	$(RM) CAP-datatypesTest.cpp
	$(RM) $(HFILESDIR)$(PS)CAP-datatypes.h 
	$(RM) CAP-datatypes.html
	$(RM) CAP-errortypesEnc.cpp
	$(RM) CAP-errortypesDec.cpp
	$(RM) CAP-errortypes.cpp
	$(RM) CAP-errortypesPrint.cpp
	$(RM) CAP-errortypesCopy.cpp
	$(RM) CAP-errortypesCompare.cpp
	$(RM) CAP-errortypesPrtToStr.cpp
	$(RM) CAP-errortypesPrtToStrm.cpp
	$(RM) CAP-errortypesTest.cpp
	$(RM) $(HFILESDIR)$(PS)CAP-errortypes.h 
	$(RM) CAP-errortypes.html
	$(RM) MAP-CommonDataTypesEnc.cpp
	$(RM) MAP-CommonDataTypesDec.cpp
	$(RM) MAP-CommonDataTypes.cpp
	$(RM) MAP-CommonDataTypesPrint.cpp
	$(RM) MAP-CommonDataTypesCopy.cpp
	$(RM) MAP-CommonDataTypesCompare.cpp
	$(RM) MAP-CommonDataTypesPrtToStr.cpp
	$(RM) MAP-CommonDataTypesPrtToStrm.cpp
	$(RM) MAP-CommonDataTypesTest.cpp
	$(RM) $(HFILESDIR)$(PS)MAP-CommonDataTypes.h 
	$(RM) MAP-CommonDataTypes.html
	$(RM) MAP-BS-CodeEnc.cpp
	$(RM) MAP-BS-CodeDec.cpp
	$(RM) MAP-BS-Code.cpp
	$(RM) MAP-BS-CodePrint.cpp
	$(RM) MAP-BS-CodeCopy.cpp
	$(RM) MAP-BS-CodeCompare.cpp
	$(RM) MAP-BS-CodePrtToStr.cpp
	$(RM) MAP-BS-CodePrtToStrm.cpp
	$(RM) MAP-BS-CodeTest.cpp
	$(RM) $(HFILESDIR)$(PS)MAP-BS-Code.h 
	$(RM) MAP-BS-Code.html
	$(RM) MAP-TS-CodeEnc.cpp
	$(RM) MAP-TS-CodeDec.cpp
	$(RM) MAP-TS-Code.cpp
	$(RM) MAP-TS-CodePrint.cpp
	$(RM) MAP-TS-CodeCopy.cpp
	$(RM) MAP-TS-CodeCompare.cpp
	$(RM) MAP-TS-CodePrtToStr.cpp
	$(RM) MAP-TS-CodePrtToStrm.cpp
	$(RM) MAP-TS-CodeTest.cpp
	$(RM) $(HFILESDIR)$(PS)MAP-TS-Code.h 
	$(RM) MAP-TS-Code.html
	$(RM) MAP-MS-DataTypesEnc.cpp
	$(RM) MAP-MS-DataTypesDec.cpp
	$(RM) MAP-MS-DataTypes.cpp
	$(RM) MAP-MS-DataTypesPrint.cpp
	$(RM) MAP-MS-DataTypesCopy.cpp
	$(RM) MAP-MS-DataTypesCompare.cpp
	$(RM) MAP-MS-DataTypesPrtToStr.cpp
	$(RM) MAP-MS-DataTypesPrtToStrm.cpp
	$(RM) MAP-MS-DataTypesTest.cpp
	$(RM) $(HFILESDIR)$(PS)MAP-MS-DataTypes.h 
	$(RM) MAP-MS-DataTypes.html
	$(RM) $(HFILESDIR)$(PS)MAP-ER-DataTypes.h 
	$(RM) MAP-ER-DataTypes.html
	$(RM) $(HFILESDIR)$(PS)MAP-OM-DataTypes.h 
	$(RM) MAP-OM-DataTypes.html
	$(RM) $(HFILESDIR)$(PS)MAP-SS-DataTypes.h 
	$(RM) MAP-SS-DataTypes.html
	$(RM) $(HFILESDIR)$(PS)MAP-SS-Code.h 
	$(RM) MAP-SS-Code.html
	$(RM) MAP-ExtensionDataTypesEnc.cpp
	$(RM) MAP-ExtensionDataTypesDec.cpp
	$(RM) MAP-ExtensionDataTypes.cpp
	$(RM) MAP-ExtensionDataTypesPrint.cpp
	$(RM) MAP-ExtensionDataTypesCopy.cpp
	$(RM) MAP-ExtensionDataTypesCompare.cpp
	$(RM) MAP-ExtensionDataTypesPrtToStr.cpp
	$(RM) MAP-ExtensionDataTypesPrtToStrm.cpp
	$(RM) MAP-ExtensionDataTypesTest.cpp
	$(RM) $(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h 
	$(RM) MAP-ExtensionDataTypes.html
	$(RM) MAP-CH-DataTypesEnc.cpp
	$(RM) MAP-CH-DataTypesDec.cpp
	$(RM) MAP-CH-DataTypes.cpp
	$(RM) MAP-CH-DataTypesPrint.cpp
	$(RM) MAP-CH-DataTypesCopy.cpp
	$(RM) MAP-CH-DataTypesCompare.cpp
	$(RM) MAP-CH-DataTypesPrtToStr.cpp
	$(RM) MAP-CH-DataTypesPrtToStrm.cpp
	$(RM) MAP-CH-DataTypesTest.cpp
	$(RM) $(HFILESDIR)$(PS)MAP-CH-DataTypes.h 
	$(RM) MAP-CH-DataTypes.html
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) *.dat
	$(RM) asn1-style.css
