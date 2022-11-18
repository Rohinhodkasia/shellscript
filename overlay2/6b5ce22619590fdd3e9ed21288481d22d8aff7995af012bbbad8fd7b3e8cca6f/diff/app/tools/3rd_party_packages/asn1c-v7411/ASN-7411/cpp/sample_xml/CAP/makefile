# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

# include directories
OSROOTDIR = ../../..
RTSRCDIR = $(OSROOTDIR)/rtsrc
XMLSRCDIR = $(OSROOTDIR)/rtxmlsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)/asn1type.h $(RTSRCDIR)/asn1CppTypes.h  \
$(XMLSRCDIR)/osrtxml.h 
# compiler defs
CFLAGS = -c $(CVARSMTD_) $(CFLAGS_) $(CBLDTYPE_)
CCFLAGS = $(CFLAGS)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(XMLSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(RTLIBNAME)
LLIBS = $(LLXML) $(LLRT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
Cap$(OBJ) \
XSD$(OBJ)

ENCOBJECTS =  \
CapEnc$(OBJ) \
XSDEnc$(OBJ)

DECOBJECTS =  \
CapDec$(OBJ) \
XSDDec$(OBJ)

PRTOBJECTS =  \
CapPrint$(OBJ) \
XSDPrint$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(PRTOBJECTS) $(DECOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)/Cap.h $(HFILESDIR)/rtkey.h $(HFILES)

writer$(OBJ) : writer.cpp $(RWHFILES)
reader$(OBJ) : reader.cpp $(RWHFILES)

# .cpp -> .obj rules
# common file rules
Cap$(OBJ) : $(SRCDIR)/Cap.cpp \
$(HFILESDIR)/Cap.h $(HFILESDIR)/XSD.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/Cap.cpp

# decode file rules
CapDec$(OBJ) : $(SRCDIR)/CapDec.cpp \
$(HFILESDIR)/Cap.h $(HFILESDIR)/XSD.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/CapDec.cpp

# encode file rules
CapEnc$(OBJ) : $(SRCDIR)/CapEnc.cpp \
$(HFILESDIR)/Cap.h $(HFILESDIR)/XSD.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/CapEnc.cpp

# print file rules
CapPrint$(OBJ) : $(SRCDIR)/CapPrint.cpp \
$(HFILESDIR)/Cap.h $(HFILESDIR)/XSD.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/CapPrint.cpp

# reader file rules
reader$(OBJ) : $(SRCDIR)/reader.cpp \
$(HFILESDIR)/Cap.h $(HFILESDIR)/rtkey.h $(HFILES)

# writer file rules
writer$(OBJ) : $(SRCDIR)/writer.cpp \
$(HFILESDIR)/Cap.h $(HFILESDIR)/rtkey.h $(HFILES)

# common file rules
XSD$(OBJ) : $(SRCDIR)/XSD.cpp \
$(HFILESDIR)/XSD.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/XSD.cpp

# decode file rules
XSDDec$(OBJ) : $(SRCDIR)/XSDDec.cpp \
$(HFILESDIR)/XSD.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/XSDDec.cpp

# encode file rules
XSDEnc$(OBJ) : $(SRCDIR)/XSDEnc.cpp \
$(HFILESDIR)/XSD.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/XSDEnc.cpp

# print file rules
XSDPrint$(OBJ) : $(SRCDIR)/XSDPrint.cpp \
$(HFILESDIR)/XSD.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/XSDPrint.cpp

# .asn -> .cpp .h rules
$(SRCDIR)/CapEnc.cpp \
$(SRCDIR)/CapDec.cpp \
$(SRCDIR)/Cap.cpp \
$(SRCDIR)/CapPrint.cpp \
$(HFILESDIR)/Cap.h \
$(SRCDIR)/XSDEnc.cpp \
$(SRCDIR)/XSDDec.cpp \
$(SRCDIR)/XSD.cpp \
$(SRCDIR)/XSDPrint.cpp \
$(HFILESDIR)/XSD.h \
$(HFILESDIR)/Namespace.h \
$(HFILESDIR)/rtkey.h \
: cap.xsd $(OSROOTDIR)/bin/asn1c$(EXE)
	..$(PS)..$(PS)..$(PS)bin$(PS)asn1c cap.xsd -cpp -xml -print -trace

clean:
	$(RM) CapEnc.cpp
	$(RM) CapDec.cpp
	$(RM) Cap.cpp
	$(RM) CapPrint.cpp
	$(RM) $(HFILESDIR)$(PS)Cap.h 
	$(RM) XSDEnc.cpp
	$(RM) XSDDec.cpp
	$(RM) XSD.cpp
	$(RM) XSDPrint.cpp
	$(RM) $(HFILESDIR)$(PS)XSD.h 
	$(RM) $(HFILESDIR)$(PS)Namespace.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.xml

