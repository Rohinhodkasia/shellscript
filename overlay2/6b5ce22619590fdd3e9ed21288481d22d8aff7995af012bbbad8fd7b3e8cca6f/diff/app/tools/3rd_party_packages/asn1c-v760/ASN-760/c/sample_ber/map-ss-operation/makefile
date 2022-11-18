# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

HFILES = $(RTSRCDIR)/asn1type.h \
$(RTSRCDIR)/rtContext.h \
$(RTXSRCDIR)/rtxContext.h \
$(BERSRCDIR)/asn1ber.h 

LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_)

OBJECTS =  \
SS-Protocol$(OBJ) \
Remote-Operations-Generic-ROS-PDUs$(OBJ) \
Remote-Operations-Information-Objects$(OBJ) \
MAP-SS-DataTypes$(OBJ) \
MAP-SS-Code$(OBJ) \
MAP-CommonDataTypes$(OBJ) \
MAP-BS-Code$(OBJ) \
MAP-TS-Code$(OBJ) \
SS-DataTypes$(OBJ) \
MAP-MS-DataTypes$(OBJ) \
MAP-LCS-DataTypes$(OBJ) \
MAP-ExtensionDataTypes$(OBJ) \
MAP-ER-DataTypes$(OBJ)

ENCOBJECTS =  \
SS-ProtocolEnc$(OBJ) \
Remote-Operations-Generic-ROS-PDUsEnc$(OBJ) \
Remote-Operations-Information-ObjectsEnc$(OBJ) \
MAP-SS-DataTypesEnc$(OBJ) \
MAP-SS-CodeEnc$(OBJ) \
MAP-CommonDataTypesEnc$(OBJ) \
MAP-BS-CodeEnc$(OBJ) \
MAP-TS-CodeEnc$(OBJ) \
SS-DataTypesEnc$(OBJ) \
MAP-MS-DataTypesEnc$(OBJ) \
MAP-LCS-DataTypesEnc$(OBJ) \
MAP-ExtensionDataTypesEnc$(OBJ) \
MAP-ER-DataTypesEnc$(OBJ)

DECOBJECTS =  \
SS-ProtocolDec$(OBJ) \
Remote-Operations-Generic-ROS-PDUsDec$(OBJ) \
Remote-Operations-Information-ObjectsDec$(OBJ) \
MAP-SS-DataTypesDec$(OBJ) \
MAP-SS-CodeDec$(OBJ) \
MAP-CommonDataTypesDec$(OBJ) \
MAP-BS-CodeDec$(OBJ) \
MAP-TS-CodeDec$(OBJ) \
SS-DataTypesDec$(OBJ) \
MAP-MS-DataTypesDec$(OBJ) \
MAP-LCS-DataTypesDec$(OBJ) \
MAP-ExtensionDataTypesDec$(OBJ) \
MAP-ER-DataTypesDec$(OBJ)

P2MOBJECTS =  \
SS-ProtocolPrtToStrm$(OBJ) \
Remote-Operations-Generic-ROS-PDUsPrtToStrm$(OBJ) \
Remote-Operations-Information-ObjectsPrtToStrm$(OBJ) \
MAP-SS-DataTypesPrtToStrm$(OBJ) \
MAP-SS-CodePrtToStrm$(OBJ) \
MAP-CommonDataTypesPrtToStrm$(OBJ) \
MAP-BS-CodePrtToStrm$(OBJ) \
MAP-TS-CodePrtToStrm$(OBJ) \
SS-DataTypesPrtToStrm$(OBJ) \
MAP-MS-DataTypesPrtToStrm$(OBJ) \
MAP-LCS-DataTypesPrtToStrm$(OBJ) \
MAP-ExtensionDataTypesPrtToStrm$(OBJ) \
MAP-ER-DataTypesPrtToStrm$(OBJ)

LIBS = ../../lib/$(BERLIBNAME) ../../lib/$(RTLIBNAME)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(P2MOBJECTS) \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(P2MOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(BSLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(P2MOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(BSLIBS)

RWHFILES = SS-Protocol.h  \
Remote-Operations-Generic-ROS-PDUs.h Remote-Operations-Information-Objects.h \
MAP-MobileServiceOperations.h MAP-SupplementaryServiceOperations.h \
MAP-SS-DataTypes.h MAP-SS-Code.h MAP-CommonDataTypes.h \
MAP-BS-Code.h MAP-TS-Code.h SS-Operations.h \
SS-DataTypes.h MAP-MS-DataTypes.h MAP-LCS-DataTypes.h \
MAP-ExtensionDataTypes.h MAP-Errors.h MAP-ER-DataTypes.h \
SS-Errors.h rtkey.h $(HFILES)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
SS-ProtocolEnc.c \
SS-ProtocolDec.c \
SS-Protocol.c \
SS-ProtocolPrtToStrm.c \
SS-Protocol.h \
Remote-Operations-Generic-ROS-PDUsEnc.c \
Remote-Operations-Generic-ROS-PDUsDec.c \
Remote-Operations-Generic-ROS-PDUs.c \
Remote-Operations-Generic-ROS-PDUsPrtToStrm.c \
Remote-Operations-Generic-ROS-PDUs.h \
Remote-Operations-Information-ObjectsEnc.c \
Remote-Operations-Information-ObjectsDec.c \
Remote-Operations-Information-Objects.c \
Remote-Operations-Information-ObjectsPrtToStrm.c \
Remote-Operations-Information-Objects.h \
MAP-MobileServiceOperations.h \
MAP-SupplementaryServiceOperations.h \
MAP-SS-DataTypesEnc.c \
MAP-SS-DataTypesDec.c \
MAP-SS-DataTypes.c \
MAP-SS-DataTypesPrtToStrm.c \
MAP-SS-DataTypes.h \
MAP-SS-CodeEnc.c \
MAP-SS-CodeDec.c \
MAP-SS-Code.c \
MAP-SS-CodePrtToStrm.c \
MAP-SS-Code.h \
MAP-CommonDataTypesEnc.c \
MAP-CommonDataTypesDec.c \
MAP-CommonDataTypes.c \
MAP-CommonDataTypesPrtToStrm.c \
MAP-CommonDataTypes.h \
MAP-BS-CodeEnc.c \
MAP-BS-CodeDec.c \
MAP-BS-Code.c \
MAP-BS-CodePrtToStrm.c \
MAP-BS-Code.h \
MAP-TS-CodeEnc.c \
MAP-TS-CodeDec.c \
MAP-TS-Code.c \
MAP-TS-CodePrtToStrm.c \
MAP-TS-Code.h \
SS-Operations.h \
SS-DataTypesEnc.c \
SS-DataTypesDec.c \
SS-DataTypes.c \
SS-DataTypesPrtToStrm.c \
SS-DataTypes.h \
MAP-MS-DataTypesEnc.c \
MAP-MS-DataTypesDec.c \
MAP-MS-DataTypes.c \
MAP-MS-DataTypesPrtToStrm.c \
MAP-MS-DataTypes.h \
MAP-LCS-DataTypesEnc.c \
MAP-LCS-DataTypesDec.c \
MAP-LCS-DataTypes.c \
MAP-LCS-DataTypesPrtToStrm.c \
MAP-LCS-DataTypes.h \
MAP-ExtensionDataTypesEnc.c \
MAP-ExtensionDataTypesDec.c \
MAP-ExtensionDataTypes.c \
MAP-ExtensionDataTypesPrtToStrm.c \
MAP-ExtensionDataTypes.h \
MAP-Errors.h \
MAP-ER-DataTypesEnc.c \
MAP-ER-DataTypesDec.c \
MAP-ER-DataTypes.c \
MAP-ER-DataTypesPrtToStrm.c \
MAP-ER-DataTypes.h \
SS-Errors.h \
rtkey.h \
: ../../../specs/3GPP-MAP/acconfig.xml ../../../specs/3GPP-MAP/SS-Protocol.asn $(OSROOTDIR)/bin/asn1c$(EXE)
	$(ASN1C) ../../../specs/3GPP-MAP/SS-Protocol.asn -c -ber -config ../../../specs/3GPP-MAP/acconfig.xml -depends -I ../../../specs/3GPP-MAP -prttostrm -strict-size -table-unions -fqtvalue

depends: SS-Protocol.c Remote-Operations-Generic-ROS-PDUs.c \
Remote-Operations-Information-Objects.c MAP-SS-DataTypes.c MAP-SS-Code.c \
MAP-CommonDataTypes.c MAP-BS-Code.c MAP-TS-Code.c SS-DataTypes.c \
MAP-MS-DataTypes.c MAP-LCS-DataTypes.c MAP-ExtensionDataTypes.c \
MAP-ER-DataTypes.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) SS-ProtocolEnc.c
	$(RM) SS-ProtocolDec.c
	$(RM) SS-Protocol.c
	$(RM) SS-ProtocolPrtToStrm.c
	$(RM) SS-Protocol.h 
	$(RM) Remote-Operations-Generic-ROS-PDUsEnc.c
	$(RM) Remote-Operations-Generic-ROS-PDUsDec.c
	$(RM) Remote-Operations-Generic-ROS-PDUs.c
	$(RM) Remote-Operations-Generic-ROS-PDUsPrtToStrm.c
	$(RM) Remote-Operations-Generic-ROS-PDUs.h 
	$(RM) Remote-Operations-Information-ObjectsEnc.c
	$(RM) Remote-Operations-Information-ObjectsDec.c
	$(RM) Remote-Operations-Information-Objects.c
	$(RM) Remote-Operations-Information-ObjectsPrtToStrm.c
	$(RM) Remote-Operations-Information-Objects.h 
	$(RM) Remote-Operations-Useful-Definitions.h 
	$(RM) MAP-MobileServiceOperations.h 
	$(RM) MAP-SupplementaryServiceOperations.h 
	$(RM) MAP-SS-DataTypesEnc.c
	$(RM) MAP-SS-DataTypesDec.c
	$(RM) MAP-SS-DataTypes.c
	$(RM) MAP-SS-DataTypesPrtToStrm.c
	$(RM) MAP-SS-DataTypes.h 
	$(RM) MAP-SS-CodeEnc.c
	$(RM) MAP-SS-CodeDec.c
	$(RM) MAP-SS-Code.c
	$(RM) MAP-SS-CodePrtToStrm.c
	$(RM) MAP-SS-Code.h 
	$(RM) MAP-CommonDataTypesEnc.c
	$(RM) MAP-CommonDataTypesDec.c
	$(RM) MAP-CommonDataTypes.c
	$(RM) MAP-CommonDataTypesPrtToStrm.c
	$(RM) MAP-CommonDataTypes.h 
	$(RM) MAP-BS-CodeEnc.c
	$(RM) MAP-BS-CodeDec.c
	$(RM) MAP-BS-Code.c
	$(RM) MAP-BS-CodePrtToStrm.c
	$(RM) MAP-BS-Code.h 
	$(RM) MAP-TS-CodeEnc.c
	$(RM) MAP-TS-CodeDec.c
	$(RM) MAP-TS-Code.c
	$(RM) MAP-TS-CodePrtToStrm.c
	$(RM) MAP-TS-Code.h 
	$(RM) SS-Operations.h 
	$(RM) SS-DataTypesEnc.c
	$(RM) SS-DataTypesDec.c
	$(RM) SS-DataTypes.c
	$(RM) SS-DataTypesPrtToStrm.c
	$(RM) SS-DataTypes.h 
	$(RM) MAP-MS-DataTypesEnc.c
	$(RM) MAP-MS-DataTypesDec.c
	$(RM) MAP-MS-DataTypes.c
	$(RM) MAP-MS-DataTypesPrtToStrm.c
	$(RM) MAP-MS-DataTypes.h 
	$(RM) MAP-LCS-DataTypesEnc.c
	$(RM) MAP-LCS-DataTypesDec.c
	$(RM) MAP-LCS-DataTypes.c
	$(RM) MAP-LCS-DataTypesPrtToStrm.c
	$(RM) MAP-LCS-DataTypes.h 
	$(RM) MAP-ExtensionDataTypesEnc.c
	$(RM) MAP-ExtensionDataTypesDec.c
	$(RM) MAP-ExtensionDataTypes.c
	$(RM) MAP-ExtensionDataTypesPrtToStrm.c
	$(RM) MAP-ExtensionDataTypes.h 
	$(RM) MAP-Errors.h 
	$(RM) MAP-ER-DataTypesEnc.c
	$(RM) MAP-ER-DataTypesDec.c
	$(RM) MAP-ER-DataTypes.c
	$(RM) MAP-ER-DataTypesPrtToStrm.c
	$(RM) MAP-ER-DataTypes.h 
	$(RM) MAP-OM-DataTypes.h 
	$(RM) MAP-SM-DataTypes.h 
	$(RM) SS-Errors.h 
	$(RM) rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM_MSVC_FILES)
	$(RM) *.dat

