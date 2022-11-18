# makefile to build generated files

include ../../platform.mk

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)cpp$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(RTSRCDIR)$(PS)asn1CppTypes.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_) -D_TRACE
CCFLAGS = -c $(CVARS_) $(CCFLAGS_) $(CBLDTYPE_) -D_TRACE
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1rt$(LLAEXT) $(LLSYS)
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

RWHFILES = $(HFILESDIR)$(PS)NBAP-PDU-Descriptions.h  \
$(HFILESDIR)$(PS)NBAP-PDU-Contents.h $(HFILESDIR)$(PS)NBAP-IEs.h $(HFILESDIR)$(PS)NBAP-CommonDataTypes.h  \
$(HFILESDIR)$(PS)NBAP-Constants.h $(HFILESDIR)$(PS)NBAP-Containers.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

writer$(OBJ) : $(SRCDIR)$(PS)writer.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)$(PS)writer.cpp

reader$(OBJ) : $(SRCDIR)$(PS)reader.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)$(PS)reader.cpp

# .cpp -> .obj rules
# common file rules
NBAP-PDU-Descriptions$(OBJ) : $(SRCDIR)$(PS)NBAP-PDU-Descriptions.cpp \
$(HFILESDIR)$(PS)NBAP-PDU-Descriptions.h  \
$(HFILESDIR)$(PS)NBAP-CommonDataTypes.h $(HFILESDIR)$(PS)NBAP-PDU-Contents.h  \
$(HFILESDIR)$(PS)NBAP-Constants.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NBAP-PDU-Descriptions.cpp

# decode file rules
NBAP-PDU-DescriptionsDec$(OBJ) : $(SRCDIR)$(PS)NBAP-PDU-DescriptionsDec.cpp \
$(HFILESDIR)$(PS)NBAP-PDU-Descriptions.h  \
$(HFILESDIR)$(PS)NBAP-CommonDataTypes.h $(HFILESDIR)$(PS)NBAP-PDU-Contents.h  \
$(HFILESDIR)$(PS)NBAP-Constants.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NBAP-PDU-DescriptionsDec.cpp

# encode file rules
NBAP-PDU-DescriptionsEnc$(OBJ) : $(SRCDIR)$(PS)NBAP-PDU-DescriptionsEnc.cpp \
$(HFILESDIR)$(PS)NBAP-PDU-Descriptions.h  \
$(HFILESDIR)$(PS)NBAP-CommonDataTypes.h $(HFILESDIR)$(PS)NBAP-PDU-Contents.h  \
$(HFILESDIR)$(PS)NBAP-Constants.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NBAP-PDU-DescriptionsEnc.cpp

# print file rules
NBAP-PDU-DescriptionsPrint$(OBJ) : $(SRCDIR)$(PS)NBAP-PDU-DescriptionsPrint.cpp \
$(HFILESDIR)$(PS)NBAP-PDU-Descriptions.h  \
$(HFILESDIR)$(PS)NBAP-CommonDataTypes.h $(HFILESDIR)$(PS)NBAP-PDU-Contents.h  \
$(HFILESDIR)$(PS)NBAP-Constants.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NBAP-PDU-DescriptionsPrint.cpp

# common file rules
NBAP-PDU-Contents$(OBJ) : $(SRCDIR)$(PS)NBAP-PDU-Contents.cpp \
$(HFILESDIR)$(PS)NBAP-PDU-Contents.h $(HFILESDIR)$(PS)NBAP-IEs.h  \
$(HFILESDIR)$(PS)NBAP-Containers.h $(HFILESDIR)$(PS)NBAP-Constants.h  \
$(HFILESDIR)$(PS)NBAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NBAP-PDU-Contents.cpp

# decode file rules
NBAP-PDU-ContentsDec$(OBJ) : $(SRCDIR)$(PS)NBAP-PDU-ContentsDec.cpp \
$(HFILESDIR)$(PS)NBAP-PDU-Contents.h $(HFILESDIR)$(PS)NBAP-IEs.h  \
$(HFILESDIR)$(PS)NBAP-Containers.h $(HFILESDIR)$(PS)NBAP-Constants.h  \
$(HFILESDIR)$(PS)NBAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NBAP-PDU-ContentsDec.cpp

# encode file rules
NBAP-PDU-ContentsEnc$(OBJ) : $(SRCDIR)$(PS)NBAP-PDU-ContentsEnc.cpp \
$(HFILESDIR)$(PS)NBAP-PDU-Contents.h $(HFILESDIR)$(PS)NBAP-IEs.h  \
$(HFILESDIR)$(PS)NBAP-Containers.h $(HFILESDIR)$(PS)NBAP-Constants.h  \
$(HFILESDIR)$(PS)NBAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NBAP-PDU-ContentsEnc.cpp

# print file rules
NBAP-PDU-ContentsPrint$(OBJ) : $(SRCDIR)$(PS)NBAP-PDU-ContentsPrint.cpp \
$(HFILESDIR)$(PS)NBAP-PDU-Contents.h $(HFILESDIR)$(PS)NBAP-IEs.h  \
$(HFILESDIR)$(PS)NBAP-Containers.h $(HFILESDIR)$(PS)NBAP-Constants.h  \
$(HFILESDIR)$(PS)NBAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NBAP-PDU-ContentsPrint.cpp

# common file rules
NBAP-IEs$(OBJ) : $(SRCDIR)$(PS)NBAP-IEs.cpp \
$(HFILESDIR)$(PS)NBAP-IEs.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NBAP-IEs.cpp

# decode file rules
NBAP-IEsDec$(OBJ) : $(SRCDIR)$(PS)NBAP-IEsDec.cpp \
$(HFILESDIR)$(PS)NBAP-IEs.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NBAP-IEsDec.cpp

# encode file rules
NBAP-IEsEnc$(OBJ) : $(SRCDIR)$(PS)NBAP-IEsEnc.cpp \
$(HFILESDIR)$(PS)NBAP-IEs.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NBAP-IEsEnc.cpp

# print file rules
NBAP-IEsPrint$(OBJ) : $(SRCDIR)$(PS)NBAP-IEsPrint.cpp \
$(HFILESDIR)$(PS)NBAP-IEs.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NBAP-IEsPrint.cpp

# common file rules
NBAP-CommonDataTypes$(OBJ) : $(SRCDIR)$(PS)NBAP-CommonDataTypes.cpp \
$(HFILESDIR)$(PS)NBAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NBAP-CommonDataTypes.cpp

# decode file rules
NBAP-CommonDataTypesDec$(OBJ) : $(SRCDIR)$(PS)NBAP-CommonDataTypesDec.cpp \
$(HFILESDIR)$(PS)NBAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NBAP-CommonDataTypesDec.cpp

# encode file rules
NBAP-CommonDataTypesEnc$(OBJ) : $(SRCDIR)$(PS)NBAP-CommonDataTypesEnc.cpp \
$(HFILESDIR)$(PS)NBAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NBAP-CommonDataTypesEnc.cpp

# print file rules
NBAP-CommonDataTypesPrint$(OBJ) : $(SRCDIR)$(PS)NBAP-CommonDataTypesPrint.cpp \
$(HFILESDIR)$(PS)NBAP-CommonDataTypes.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)NBAP-CommonDataTypesPrint.cpp

# .asn -> .cpp .h rules
$(SRCDIR)/NBAP-PDU-DescriptionsEnc.cpp \
$(SRCDIR)/NBAP-PDU-DescriptionsDec.cpp \
$(SRCDIR)/NBAP-PDU-Descriptions.cpp \
$(SRCDIR)/NBAP-PDU-DescriptionsPrint.cpp \
$(HFILESDIR)$(PS)NBAP-PDU-Descriptions.h \
$(SRCDIR)/NBAP-PDU-ContentsEnc.cpp \
$(SRCDIR)/NBAP-PDU-ContentsDec.cpp \
$(SRCDIR)/NBAP-PDU-Contents.cpp \
$(SRCDIR)/NBAP-PDU-ContentsPrint.cpp \
$(HFILESDIR)$(PS)NBAP-PDU-Contents.h \
$(SRCDIR)/NBAP-IEsEnc.cpp \
$(SRCDIR)/NBAP-IEsDec.cpp \
$(SRCDIR)/NBAP-IEs.cpp \
$(SRCDIR)/NBAP-IEsPrint.cpp \
$(HFILESDIR)$(PS)NBAP-IEs.h \
$(SRCDIR)/NBAP-CommonDataTypesEnc.cpp \
$(SRCDIR)/NBAP-CommonDataTypesDec.cpp \
$(SRCDIR)/NBAP-CommonDataTypes.cpp \
$(SRCDIR)/NBAP-CommonDataTypesPrint.cpp \
$(HFILESDIR)$(PS)NBAP-CommonDataTypes.h \
$(HFILESDIR)$(PS)NBAP-Constants.h \
$(HFILESDIR)$(PS)NBAP-Containers.h \
$(HFILESDIR)$(PS)rtkey.h \
: nbapSample.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(OSROOTDIR)$(PS)bin$(PS)asn1c nbapSample.asn -cpp -avn -print -table-unions -trace

clean:
	$(RM) NBAP-PDU-DescriptionsEnc.cpp
	$(RM) NBAP-PDU-DescriptionsDec.cpp
	$(RM) NBAP-PDU-Descriptions.cpp
	$(RM) NBAP-PDU-DescriptionsPrint.cpp
	$(RM) $(HFILESDIR)$(PS)NBAP-PDU-Descriptions.h 
	$(RM) NBAP-PDU-ContentsEnc.cpp
	$(RM) NBAP-PDU-ContentsDec.cpp
	$(RM) NBAP-PDU-Contents.cpp
	$(RM) NBAP-PDU-ContentsPrint.cpp
	$(RM) $(HFILESDIR)$(PS)NBAP-PDU-Contents.h 
	$(RM) NBAP-IEsEnc.cpp
	$(RM) NBAP-IEsDec.cpp
	$(RM) NBAP-IEs.cpp
	$(RM) NBAP-IEsPrint.cpp
	$(RM) $(HFILESDIR)$(PS)NBAP-IEs.h 
	$(RM) NBAP-CommonDataTypesEnc.cpp
	$(RM) NBAP-CommonDataTypesDec.cpp
	$(RM) NBAP-CommonDataTypes.cpp
	$(RM) NBAP-CommonDataTypesPrint.cpp
	$(RM) $(HFILESDIR)$(PS)NBAP-CommonDataTypes.h 
	$(RM) $(HFILESDIR)$(PS)NBAP-Constants.h 
	$(RM) $(HFILESDIR)$(PS)NBAP-Containers.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
