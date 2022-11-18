# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)cpp$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
BERSRCDIR = $(OSROOTDIR)$(PS)rtbersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(RTSRCDIR)$(PS)asn1CppTypes.h  \
$(BERSRCDIR)$(PS)asn1ber.h $(BERSRCDIR)$(PS)asn1BerCppTypes.h 
# compiler defs
CFLAGS = -c $(CVARSMTD_) $(CFLAGS_) $(CBLDTYPE_)
CCFLAGS = $(CFLAGS)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I../../../specs/camel -I../../../specs/gsm_map -I../../../specs/cap -I../../../specs/ROSE -I$(RTSRCDIR) -I$(BERSRCDIR) $(IPATHS_)
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
$(P2SOBJECTS) $(P2MOBJECTS) $(TESTOBJECTS) $(CPYOBJECTS) $(CMPOBJECTS) writer$(EXE)  \
reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
 $(TESTOBJECTS) $(PRTOBJECTS) $(P2MOBJECTS) $(P2SOBJECTS) $(CPYOBJECTS) $(CMPOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS) $(P2MOBJECTS) $(P2SOBJECTS) $(CPYOBJECTS) $(CMPOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)CAP-datatypes.h $(HFILESDIR)$(PS)CAP-errortypes.h  \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)MAP-TS-Code.h  \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h  \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

writer$(OBJ) : $(SRCDIR)$(PS)writer.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)/writer.cpp

reader$(OBJ) : $(SRCDIR)$(PS)reader.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)/reader.cpp

# .cpp -> .obj rules
# common file rules
CAP-datatypes$(OBJ) : $(SRCDIR)$(PS)CAP-datatypes.cpp \
$(HFILESDIR)$(PS)CAP-datatypes.h  \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-MS-DataTypes.h  \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CAP-datatypes.cpp

# decode file rules
CAP-datatypesDec$(OBJ) : $(SRCDIR)$(PS)CAP-datatypesDec.cpp \
$(HFILESDIR)$(PS)CAP-datatypes.h  \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-MS-DataTypes.h  \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CAP-datatypesDec.cpp

# encode file rules
CAP-datatypesEnc$(OBJ) : $(SRCDIR)$(PS)CAP-datatypesEnc.cpp \
$(HFILESDIR)$(PS)CAP-datatypes.h  \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-MS-DataTypes.h  \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CAP-datatypesEnc.cpp

# print file rules
CAP-datatypesPrint$(OBJ) : $(SRCDIR)$(PS)CAP-datatypesPrint.cpp \
$(HFILESDIR)$(PS)CAP-datatypes.h  \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-MS-DataTypes.h  \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CAP-datatypesPrint.cpp

# print-to-string file rules
CAP-datatypesPrtToStr$(OBJ) : $(SRCDIR)$(PS)CAP-datatypesPrtToStr.cpp \
$(HFILESDIR)$(PS)CAP-datatypes.h  \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-MS-DataTypes.h  \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CAP-datatypesPrtToStr.cpp

# print-to-stream file rules
CAP-datatypesPrtToStrm$(OBJ) : $(SRCDIR)$(PS)CAP-datatypesPrtToStrm.cpp \
$(HFILESDIR)$(PS)CAP-datatypes.h  \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-MS-DataTypes.h  \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CAP-datatypesPrtToStrm.cpp

# test file rules
CAP-datatypesTest$(OBJ) : $(SRCDIR)$(PS)CAP-datatypesTest.cpp \
$(HFILESDIR)$(PS)CAP-datatypes.h  \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-MS-DataTypes.h  \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CAP-datatypesTest.cpp

# copy file rules
CAP-datatypesCopy$(OBJ) : $(SRCDIR)$(PS)CAP-datatypesCopy.cpp \
$(HFILESDIR)$(PS)CAP-datatypes.h  \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-MS-DataTypes.h  \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CAP-datatypesCopy.cpp

# compare file rules
CAP-datatypesCompare$(OBJ) : $(SRCDIR)$(PS)CAP-datatypesCompare.cpp \
$(HFILESDIR)$(PS)CAP-datatypes.h  \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-MS-DataTypes.h  \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CAP-datatypesCompare.cpp

# common file rules
CAP-errortypes$(OBJ) : $(SRCDIR)$(PS)CAP-errortypes.cpp \
$(HFILESDIR)$(PS)CAP-errortypes.h $(HFILESDIR)$(PS)CAP-datatypes.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CAP-errortypes.cpp

# decode file rules
CAP-errortypesDec$(OBJ) : $(SRCDIR)$(PS)CAP-errortypesDec.cpp \
$(HFILESDIR)$(PS)CAP-errortypes.h $(HFILESDIR)$(PS)CAP-datatypes.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CAP-errortypesDec.cpp

# encode file rules
CAP-errortypesEnc$(OBJ) : $(SRCDIR)$(PS)CAP-errortypesEnc.cpp \
$(HFILESDIR)$(PS)CAP-errortypes.h $(HFILESDIR)$(PS)CAP-datatypes.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CAP-errortypesEnc.cpp

# print file rules
CAP-errortypesPrint$(OBJ) : $(SRCDIR)$(PS)CAP-errortypesPrint.cpp \
$(HFILESDIR)$(PS)CAP-errortypes.h $(HFILESDIR)$(PS)CAP-datatypes.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CAP-errortypesPrint.cpp

# print-to-string file rules
CAP-errortypesPrtToStr$(OBJ) : $(SRCDIR)$(PS)CAP-errortypesPrtToStr.cpp \
$(HFILESDIR)$(PS)CAP-errortypes.h $(HFILESDIR)$(PS)CAP-datatypes.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CAP-errortypesPrtToStr.cpp

# print-to-stream file rules
CAP-errortypesPrtToStrm$(OBJ) : $(SRCDIR)$(PS)CAP-errortypesPrtToStrm.cpp \
$(HFILESDIR)$(PS)CAP-errortypes.h $(HFILESDIR)$(PS)CAP-datatypes.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CAP-errortypesPrtToStrm.cpp

# test file rules
CAP-errortypesTest$(OBJ) : $(SRCDIR)$(PS)CAP-errortypesTest.cpp \
$(HFILESDIR)$(PS)CAP-errortypes.h $(HFILESDIR)$(PS)CAP-datatypes.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CAP-errortypesTest.cpp

# copy file rules
CAP-errortypesCopy$(OBJ) : $(SRCDIR)$(PS)CAP-errortypesCopy.cpp \
$(HFILESDIR)$(PS)CAP-errortypes.h $(HFILESDIR)$(PS)CAP-datatypes.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CAP-errortypesCopy.cpp

# compare file rules
CAP-errortypesCompare$(OBJ) : $(SRCDIR)$(PS)CAP-errortypesCompare.cpp \
$(HFILESDIR)$(PS)CAP-errortypes.h $(HFILESDIR)$(PS)CAP-datatypes.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)CAP-errortypesCompare.cpp

# common file rules
MAP-CommonDataTypes$(OBJ) : $(SRCDIR)$(PS)MAP-CommonDataTypes.cpp \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-TS-Code.h  \
$(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-CommonDataTypes.cpp

# decode file rules
MAP-CommonDataTypesDec$(OBJ) : $(SRCDIR)$(PS)MAP-CommonDataTypesDec.cpp \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-TS-Code.h  \
$(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-CommonDataTypesDec.cpp

# encode file rules
MAP-CommonDataTypesEnc$(OBJ) : $(SRCDIR)$(PS)MAP-CommonDataTypesEnc.cpp \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-TS-Code.h  \
$(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-CommonDataTypesEnc.cpp

# print file rules
MAP-CommonDataTypesPrint$(OBJ) : $(SRCDIR)$(PS)MAP-CommonDataTypesPrint.cpp \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-TS-Code.h  \
$(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-CommonDataTypesPrint.cpp

# print-to-string file rules
MAP-CommonDataTypesPrtToStr$(OBJ) : $(SRCDIR)$(PS)MAP-CommonDataTypesPrtToStr.cpp \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-TS-Code.h  \
$(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-CommonDataTypesPrtToStr.cpp

# print-to-stream file rules
MAP-CommonDataTypesPrtToStrm$(OBJ) : $(SRCDIR)$(PS)MAP-CommonDataTypesPrtToStrm.cpp \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-TS-Code.h  \
$(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-CommonDataTypesPrtToStrm.cpp

# test file rules
MAP-CommonDataTypesTest$(OBJ) : $(SRCDIR)$(PS)MAP-CommonDataTypesTest.cpp \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-TS-Code.h  \
$(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-CommonDataTypesTest.cpp

# copy file rules
MAP-CommonDataTypesCopy$(OBJ) : $(SRCDIR)$(PS)MAP-CommonDataTypesCopy.cpp \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-TS-Code.h  \
$(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-CommonDataTypesCopy.cpp

# compare file rules
MAP-CommonDataTypesCompare$(OBJ) : $(SRCDIR)$(PS)MAP-CommonDataTypesCompare.cpp \
$(HFILESDIR)$(PS)MAP-CommonDataTypes.h $(HFILESDIR)$(PS)MAP-TS-Code.h  \
$(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-CommonDataTypesCompare.cpp

# common file rules
MAP-BS-Code$(OBJ) : $(SRCDIR)$(PS)MAP-BS-Code.cpp \
$(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-BS-Code.cpp

# decode file rules
MAP-BS-CodeDec$(OBJ) : $(SRCDIR)$(PS)MAP-BS-CodeDec.cpp \
$(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-BS-CodeDec.cpp

# encode file rules
MAP-BS-CodeEnc$(OBJ) : $(SRCDIR)$(PS)MAP-BS-CodeEnc.cpp \
$(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-BS-CodeEnc.cpp

# print file rules
MAP-BS-CodePrint$(OBJ) : $(SRCDIR)$(PS)MAP-BS-CodePrint.cpp \
$(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-BS-CodePrint.cpp

# print-to-string file rules
MAP-BS-CodePrtToStr$(OBJ) : $(SRCDIR)$(PS)MAP-BS-CodePrtToStr.cpp \
$(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-BS-CodePrtToStr.cpp

# print-to-stream file rules
MAP-BS-CodePrtToStrm$(OBJ) : $(SRCDIR)$(PS)MAP-BS-CodePrtToStrm.cpp \
$(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-BS-CodePrtToStrm.cpp

# test file rules
MAP-BS-CodeTest$(OBJ) : $(SRCDIR)$(PS)MAP-BS-CodeTest.cpp \
$(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-BS-CodeTest.cpp

# copy file rules
MAP-BS-CodeCopy$(OBJ) : $(SRCDIR)$(PS)MAP-BS-CodeCopy.cpp \
$(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-BS-CodeCopy.cpp

# compare file rules
MAP-BS-CodeCompare$(OBJ) : $(SRCDIR)$(PS)MAP-BS-CodeCompare.cpp \
$(HFILESDIR)$(PS)MAP-BS-Code.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-BS-CodeCompare.cpp

# common file rules
MAP-TS-Code$(OBJ) : $(SRCDIR)$(PS)MAP-TS-Code.cpp \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-TS-Code.cpp

# decode file rules
MAP-TS-CodeDec$(OBJ) : $(SRCDIR)$(PS)MAP-TS-CodeDec.cpp \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-TS-CodeDec.cpp

# encode file rules
MAP-TS-CodeEnc$(OBJ) : $(SRCDIR)$(PS)MAP-TS-CodeEnc.cpp \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-TS-CodeEnc.cpp

# print file rules
MAP-TS-CodePrint$(OBJ) : $(SRCDIR)$(PS)MAP-TS-CodePrint.cpp \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-TS-CodePrint.cpp

# print-to-string file rules
MAP-TS-CodePrtToStr$(OBJ) : $(SRCDIR)$(PS)MAP-TS-CodePrtToStr.cpp \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-TS-CodePrtToStr.cpp

# print-to-stream file rules
MAP-TS-CodePrtToStrm$(OBJ) : $(SRCDIR)$(PS)MAP-TS-CodePrtToStrm.cpp \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-TS-CodePrtToStrm.cpp

# test file rules
MAP-TS-CodeTest$(OBJ) : $(SRCDIR)$(PS)MAP-TS-CodeTest.cpp \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-TS-CodeTest.cpp

# copy file rules
MAP-TS-CodeCopy$(OBJ) : $(SRCDIR)$(PS)MAP-TS-CodeCopy.cpp \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-TS-CodeCopy.cpp

# compare file rules
MAP-TS-CodeCompare$(OBJ) : $(SRCDIR)$(PS)MAP-TS-CodeCompare.cpp \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-TS-CodeCompare.cpp

# common file rules
MAP-MS-DataTypes$(OBJ) : $(SRCDIR)$(PS)MAP-MS-DataTypes.cpp \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-BS-Code.h  \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)MAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-MS-DataTypes.cpp

# decode file rules
MAP-MS-DataTypesDec$(OBJ) : $(SRCDIR)$(PS)MAP-MS-DataTypesDec.cpp \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-BS-Code.h  \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)MAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-MS-DataTypesDec.cpp

# encode file rules
MAP-MS-DataTypesEnc$(OBJ) : $(SRCDIR)$(PS)MAP-MS-DataTypesEnc.cpp \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-BS-Code.h  \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)MAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-MS-DataTypesEnc.cpp

# print file rules
MAP-MS-DataTypesPrint$(OBJ) : $(SRCDIR)$(PS)MAP-MS-DataTypesPrint.cpp \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-BS-Code.h  \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)MAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-MS-DataTypesPrint.cpp

# print-to-string file rules
MAP-MS-DataTypesPrtToStr$(OBJ) : $(SRCDIR)$(PS)MAP-MS-DataTypesPrtToStr.cpp \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-BS-Code.h  \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)MAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-MS-DataTypesPrtToStr.cpp

# print-to-stream file rules
MAP-MS-DataTypesPrtToStrm$(OBJ) : $(SRCDIR)$(PS)MAP-MS-DataTypesPrtToStrm.cpp \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-BS-Code.h  \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)MAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-MS-DataTypesPrtToStrm.cpp

# test file rules
MAP-MS-DataTypesTest$(OBJ) : $(SRCDIR)$(PS)MAP-MS-DataTypesTest.cpp \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-BS-Code.h  \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)MAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-MS-DataTypesTest.cpp

# copy file rules
MAP-MS-DataTypesCopy$(OBJ) : $(SRCDIR)$(PS)MAP-MS-DataTypesCopy.cpp \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-BS-Code.h  \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)MAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-MS-DataTypesCopy.cpp

# compare file rules
MAP-MS-DataTypesCompare$(OBJ) : $(SRCDIR)$(PS)MAP-MS-DataTypesCompare.cpp \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-BS-Code.h  \
$(HFILESDIR)$(PS)MAP-TS-Code.h $(HFILESDIR)$(PS)MAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-MS-DataTypesCompare.cpp

# common file rules
MAP-ExtensionDataTypes$(OBJ) : $(SRCDIR)$(PS)MAP-ExtensionDataTypes.cpp \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-ExtensionDataTypes.cpp

# decode file rules
MAP-ExtensionDataTypesDec$(OBJ) : $(SRCDIR)$(PS)MAP-ExtensionDataTypesDec.cpp \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-ExtensionDataTypesDec.cpp

# encode file rules
MAP-ExtensionDataTypesEnc$(OBJ) : $(SRCDIR)$(PS)MAP-ExtensionDataTypesEnc.cpp \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-ExtensionDataTypesEnc.cpp

# print file rules
MAP-ExtensionDataTypesPrint$(OBJ) : $(SRCDIR)$(PS)MAP-ExtensionDataTypesPrint.cpp \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-ExtensionDataTypesPrint.cpp

# print-to-string file rules
MAP-ExtensionDataTypesPrtToStr$(OBJ) : $(SRCDIR)$(PS)MAP-ExtensionDataTypesPrtToStr.cpp \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-ExtensionDataTypesPrtToStr.cpp

# print-to-stream file rules
MAP-ExtensionDataTypesPrtToStrm$(OBJ) : $(SRCDIR)$(PS)MAP-ExtensionDataTypesPrtToStrm.cpp \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-ExtensionDataTypesPrtToStrm.cpp

# test file rules
MAP-ExtensionDataTypesTest$(OBJ) : $(SRCDIR)$(PS)MAP-ExtensionDataTypesTest.cpp \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-ExtensionDataTypesTest.cpp

# copy file rules
MAP-ExtensionDataTypesCopy$(OBJ) : $(SRCDIR)$(PS)MAP-ExtensionDataTypesCopy.cpp \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-ExtensionDataTypesCopy.cpp

# compare file rules
MAP-ExtensionDataTypesCompare$(OBJ) : $(SRCDIR)$(PS)MAP-ExtensionDataTypesCompare.cpp \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-ExtensionDataTypesCompare.cpp

# common file rules
MAP-CH-DataTypes$(OBJ) : $(SRCDIR)$(PS)MAP-CH-DataTypes.cpp \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h  \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-CH-DataTypes.cpp

# decode file rules
MAP-CH-DataTypesDec$(OBJ) : $(SRCDIR)$(PS)MAP-CH-DataTypesDec.cpp \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h  \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-CH-DataTypesDec.cpp

# encode file rules
MAP-CH-DataTypesEnc$(OBJ) : $(SRCDIR)$(PS)MAP-CH-DataTypesEnc.cpp \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h  \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-CH-DataTypesEnc.cpp

# print file rules
MAP-CH-DataTypesPrint$(OBJ) : $(SRCDIR)$(PS)MAP-CH-DataTypesPrint.cpp \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h  \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-CH-DataTypesPrint.cpp

# print-to-string file rules
MAP-CH-DataTypesPrtToStr$(OBJ) : $(SRCDIR)$(PS)MAP-CH-DataTypesPrtToStr.cpp \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h  \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-CH-DataTypesPrtToStr.cpp

# print-to-stream file rules
MAP-CH-DataTypesPrtToStrm$(OBJ) : $(SRCDIR)$(PS)MAP-CH-DataTypesPrtToStrm.cpp \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h  \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-CH-DataTypesPrtToStrm.cpp

# test file rules
MAP-CH-DataTypesTest$(OBJ) : $(SRCDIR)$(PS)MAP-CH-DataTypesTest.cpp \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h  \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-CH-DataTypesTest.cpp

# copy file rules
MAP-CH-DataTypesCopy$(OBJ) : $(SRCDIR)$(PS)MAP-CH-DataTypesCopy.cpp \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h  \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-CH-DataTypesCopy.cpp

# compare file rules
MAP-CH-DataTypesCompare$(OBJ) : $(SRCDIR)$(PS)MAP-CH-DataTypesCompare.cpp \
$(HFILESDIR)$(PS)MAP-CH-DataTypes.h  \
$(HFILESDIR)$(PS)MAP-MS-DataTypes.h $(HFILESDIR)$(PS)MAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)MAP-ExtensionDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)MAP-CH-DataTypesCompare.cpp

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
: ..$(PS)..$(PS)..$(PS)specs$(PS)camel$(PS)camel.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(OSROOTDIR)$(PS)bin$(PS)asn1c ..$(PS)..$(PS)..$(PS)specs$(PS)camel$(PS)camel.asn -cpp -ber -compare -copy -depends -html -I ..$(PS)..$(PS)..$(PS)specs$(PS)camel -I ..$(PS)..$(PS)..$(PS)specs$(PS)gsm_map -I ..$(PS)..$(PS)..$(PS)specs$(PS)cap -I ..$(PS)..$(PS)..$(PS)specs$(PS)ROSE -print -prttostr -prttostrm -strict-size -table-unions -test

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
