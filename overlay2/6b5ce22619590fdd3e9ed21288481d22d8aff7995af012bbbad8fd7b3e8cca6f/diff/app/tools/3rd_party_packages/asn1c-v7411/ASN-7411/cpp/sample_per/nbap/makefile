# makefile to build generated files

include ../../platform.mk

# include directories
OSROOTDIR = ../../..
LIBDIR  = $(OSROOTDIR)/cpp$(RTDIRSFX)/lib
RTSRCDIR = $(OSROOTDIR)/rtsrc
PERSRCDIR = $(OSROOTDIR)/rtpersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)/asn1type.h $(RTSRCDIR)/asn1CppTypes.h  \
$(PERSRCDIR)/asn1per.h $(PERSRCDIR)/asn1PerCppTypes.h 
# compiler defs
CFLAGS = -c $(CVARSMTD_) $(CFLAGS_) $(CBLDTYPE_) -D_TRACE
CCFLAGS = $(CFLAGS)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(PERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(PERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
LLIBS = $(LLPER) $(LLRT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
NBAP-PDU-Descriptions$(OBJ) \
NBAP-PDU-Contents$(OBJ) \
NBAP-IEs$(OBJ) \
NBAP-CommonDataTypes$(OBJ) 

ENCOBJECTS =  \
NBAP-PDU-DescriptionsEnc$(OBJ) \
NBAP-PDU-ContentsEnc$(OBJ) \
NBAP-IEsEnc$(OBJ) \
NBAP-CommonDataTypesEnc$(OBJ)

DECOBJECTS =  \
NBAP-PDU-DescriptionsDec$(OBJ) \
NBAP-PDU-ContentsDec$(OBJ) \
NBAP-IEsDec$(OBJ) \
NBAP-CommonDataTypesDec$(OBJ)

PRTOBJECTS =  \
NBAP-PDU-DescriptionsPrint$(OBJ) \
NBAP-PDU-ContentsPrint$(OBJ) \
NBAP-IEsPrint$(OBJ) \
NBAP-CommonDataTypesPrint$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
 $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)/NBAP-PDU-Descriptions.h $(HFILESDIR)/NBAP-PDU-Contents.h  \
$(HFILESDIR)/NBAP-IEs.h $(HFILESDIR)/NBAP-CommonDataTypes.h $(HFILESDIR)/NBAP-Constants.h  \
$(HFILESDIR)/NBAP-Containers.h $(HFILESDIR)/rtkey.h $(HFILES)

writer$(OBJ) : $(SRCDIR)/writer.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)/writer.cpp

reader$(OBJ) : $(SRCDIR)/reader.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)/reader.cpp

# .cpp -> .obj rules
# common file rules
NBAP-PDU-Descriptions$(OBJ) : $(SRCDIR)/NBAP-PDU-Descriptions.cpp \
$(HFILESDIR)/NBAP-PDU-Descriptions.h  \
$(HFILESDIR)/NBAP-CommonDataTypes.h $(HFILESDIR)/NBAP-PDU-Contents.h $(HFILESDIR)/NBAP-Constants.h  \
$(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/NBAP-PDU-Descriptions.cpp

# decode file rules
NBAP-PDU-DescriptionsDec$(OBJ) : $(SRCDIR)/NBAP-PDU-DescriptionsDec.cpp \
$(HFILESDIR)/NBAP-PDU-Descriptions.h  \
$(HFILESDIR)/NBAP-CommonDataTypes.h $(HFILESDIR)/NBAP-PDU-Contents.h $(HFILESDIR)/NBAP-Constants.h  \
$(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/NBAP-PDU-DescriptionsDec.cpp

# encode file rules
NBAP-PDU-DescriptionsEnc$(OBJ) : $(SRCDIR)/NBAP-PDU-DescriptionsEnc.cpp \
$(HFILESDIR)/NBAP-PDU-Descriptions.h  \
$(HFILESDIR)/NBAP-CommonDataTypes.h $(HFILESDIR)/NBAP-PDU-Contents.h $(HFILESDIR)/NBAP-Constants.h  \
$(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/NBAP-PDU-DescriptionsEnc.cpp

# print file rules
NBAP-PDU-DescriptionsPrint$(OBJ) : $(SRCDIR)/NBAP-PDU-DescriptionsPrint.cpp \
$(HFILESDIR)/NBAP-PDU-Descriptions.h  \
$(HFILESDIR)/NBAP-CommonDataTypes.h $(HFILESDIR)/NBAP-PDU-Contents.h $(HFILESDIR)/NBAP-Constants.h  \
$(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/NBAP-PDU-DescriptionsPrint.cpp

# common file rules
NBAP-PDU-Contents$(OBJ) : $(SRCDIR)/NBAP-PDU-Contents.cpp \
$(HFILESDIR)/NBAP-PDU-Contents.h $(HFILESDIR)/NBAP-IEs.h  \
$(HFILESDIR)/NBAP-Containers.h $(HFILESDIR)/NBAP-Constants.h $(HFILESDIR)/NBAP-CommonDataTypes.h  \
$(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/NBAP-PDU-Contents.cpp

# decode file rules
NBAP-PDU-ContentsDec$(OBJ) : $(SRCDIR)/NBAP-PDU-ContentsDec.cpp \
$(HFILESDIR)/NBAP-PDU-Contents.h $(HFILESDIR)/NBAP-IEs.h  \
$(HFILESDIR)/NBAP-Containers.h $(HFILESDIR)/NBAP-Constants.h $(HFILESDIR)/NBAP-CommonDataTypes.h  \
$(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/NBAP-PDU-ContentsDec.cpp

# encode file rules
NBAP-PDU-ContentsEnc$(OBJ) : $(SRCDIR)/NBAP-PDU-ContentsEnc.cpp \
$(HFILESDIR)/NBAP-PDU-Contents.h $(HFILESDIR)/NBAP-IEs.h  \
$(HFILESDIR)/NBAP-Containers.h $(HFILESDIR)/NBAP-Constants.h $(HFILESDIR)/NBAP-CommonDataTypes.h  \
$(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/NBAP-PDU-ContentsEnc.cpp

# print file rules
NBAP-PDU-ContentsPrint$(OBJ) : $(SRCDIR)/NBAP-PDU-ContentsPrint.cpp \
$(HFILESDIR)/NBAP-PDU-Contents.h $(HFILESDIR)/NBAP-IEs.h  \
$(HFILESDIR)/NBAP-Containers.h $(HFILESDIR)/NBAP-Constants.h $(HFILESDIR)/NBAP-CommonDataTypes.h  \
$(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/NBAP-PDU-ContentsPrint.cpp

# common file rules
NBAP-IEs$(OBJ) : $(SRCDIR)/NBAP-IEs.cpp \
$(HFILESDIR)/NBAP-IEs.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/NBAP-IEs.cpp

# decode file rules
NBAP-IEsDec$(OBJ) : $(SRCDIR)/NBAP-IEsDec.cpp \
$(HFILESDIR)/NBAP-IEs.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/NBAP-IEsDec.cpp

# encode file rules
NBAP-IEsEnc$(OBJ) : $(SRCDIR)/NBAP-IEsEnc.cpp \
$(HFILESDIR)/NBAP-IEs.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/NBAP-IEsEnc.cpp

# print file rules
NBAP-IEsPrint$(OBJ) : $(SRCDIR)/NBAP-IEsPrint.cpp \
$(HFILESDIR)/NBAP-IEs.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/NBAP-IEsPrint.cpp

# common file rules
NBAP-CommonDataTypes$(OBJ) : $(SRCDIR)/NBAP-CommonDataTypes.cpp \
$(HFILESDIR)/NBAP-CommonDataTypes.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/NBAP-CommonDataTypes.cpp

# decode file rules
NBAP-CommonDataTypesDec$(OBJ) : $(SRCDIR)/NBAP-CommonDataTypesDec.cpp \
$(HFILESDIR)/NBAP-CommonDataTypes.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/NBAP-CommonDataTypesDec.cpp

# encode file rules
NBAP-CommonDataTypesEnc$(OBJ) : $(SRCDIR)/NBAP-CommonDataTypesEnc.cpp \
$(HFILESDIR)/NBAP-CommonDataTypes.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/NBAP-CommonDataTypesEnc.cpp

# print file rules
NBAP-CommonDataTypesPrint$(OBJ) : $(SRCDIR)/NBAP-CommonDataTypesPrint.cpp \
$(HFILESDIR)/NBAP-CommonDataTypes.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/NBAP-CommonDataTypesPrint.cpp

# .asn -> .cpp .h rules
$(SRCDIR)/NBAP-PDU-DescriptionsEnc.cpp \
$(SRCDIR)/NBAP-PDU-DescriptionsDec.cpp \
$(SRCDIR)/NBAP-PDU-Descriptions.cpp \
$(SRCDIR)/NBAP-PDU-DescriptionsPrint.cpp \
$(HFILESDIR)/NBAP-PDU-Descriptions.h \
$(SRCDIR)/NBAP-PDU-ContentsEnc.cpp \
$(SRCDIR)/NBAP-PDU-ContentsDec.cpp \
$(SRCDIR)/NBAP-PDU-Contents.cpp \
$(SRCDIR)/NBAP-PDU-ContentsPrint.cpp \
$(HFILESDIR)/NBAP-PDU-Contents.h \
$(SRCDIR)/NBAP-IEsEnc.cpp \
$(SRCDIR)/NBAP-IEsDec.cpp \
$(SRCDIR)/NBAP-IEs.cpp \
$(SRCDIR)/NBAP-IEsPrint.cpp \
$(HFILESDIR)/NBAP-IEs.h \
$(SRCDIR)/NBAP-CommonDataTypesEnc.cpp \
$(SRCDIR)/NBAP-CommonDataTypesDec.cpp \
$(SRCDIR)/NBAP-CommonDataTypes.cpp \
$(SRCDIR)/NBAP-CommonDataTypesPrint.cpp \
$(HFILESDIR)/NBAP-CommonDataTypes.h \
$(HFILESDIR)/NBAP-Constants.h \
$(HFILESDIR)/NBAP-Containers.h \
$(HFILESDIR)/rtkey.h \
: nbapSample.asn $(OSROOTDIR)/bin/asn1c$(EXE)
	..$(PS)..$(PS)..$(PS)bin$(PS)asn1c nbapSample.asn -cpp -per -print -table-unions -trace

clean:
	$(RM) NBAP-PDU-DescriptionsEnc.cpp
	$(RM) NBAP-PDU-DescriptionsDec.cpp
	$(RM) NBAP-PDU-Descriptions.cpp
	$(RM) NBAP-PDU-DescriptionsPrint.cpp
	$(RM) NBAP-PDU-Descriptions.h 
	$(RM) NBAP-PDU-ContentsEnc.cpp
	$(RM) NBAP-PDU-ContentsDec.cpp
	$(RM) NBAP-PDU-Contents.cpp
	$(RM) NBAP-PDU-ContentsPrint.cpp
	$(RM) NBAP-PDU-Contents.h 
	$(RM) NBAP-IEsEnc.cpp
	$(RM) NBAP-IEsDec.cpp
	$(RM) NBAP-IEs.cpp
	$(RM) NBAP-IEsPrint.cpp
	$(RM) NBAP-IEs.h 
	$(RM) NBAP-CommonDataTypesEnc.cpp
	$(RM) NBAP-CommonDataTypesDec.cpp
	$(RM) NBAP-CommonDataTypes.cpp
	$(RM) NBAP-CommonDataTypesPrint.cpp
	$(RM) NBAP-CommonDataTypes.h 
	$(RM) NBAP-Constants.h 
	$(RM) NBAP-Containers.h 
	$(RM) rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.dat

