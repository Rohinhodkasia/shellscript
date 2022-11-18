# makefile to build generated files

include ../../platform.mk

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)cpp$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
XMLSRCDIR = $(OSROOTDIR)$(PS)rtxmlsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(RTSRCDIR)$(PS)asn1CppTypes.h  \
$(XMLSRCDIR)$(PS)osrtxml.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_)
CCFLAGS = -c $(CVARS_) $(CCFLAGS_) $(CBLDTYPE_)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(XMLSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1xml$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1xml$(LLAEXT) $(LLPFX)asn1rt$(LLAEXT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
Asn1TagFilter$(OBJ)

ENCOBJECTS =  \
Asn1TagFilterEnc$(OBJ)

DECOBJECTS =  \
Asn1TagFilterDec$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) writer$(EXE)  \
reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)Asn1TagFilter.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

writer$(OBJ) : $(SRCDIR)$(PS)writer.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)$(PS)writer.cpp

reader$(OBJ) : $(SRCDIR)$(PS)reader.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)$(PS)reader.cpp

# .cpp -> .obj rules
# common file rules
Asn1TagFilter$(OBJ) : $(SRCDIR)$(PS)Asn1TagFilter.cpp \
$(HFILESDIR)$(PS)Asn1TagFilter.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Asn1TagFilter.cpp

# decode file rules
Asn1TagFilterDec$(OBJ) : $(SRCDIR)$(PS)Asn1TagFilterDec.cpp \
$(HFILESDIR)$(PS)Asn1TagFilter.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Asn1TagFilterDec.cpp

# encode file rules
Asn1TagFilterEnc$(OBJ) : $(SRCDIR)$(PS)Asn1TagFilterEnc.cpp \
$(HFILESDIR)$(PS)Asn1TagFilter.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Asn1TagFilterEnc.cpp

# .asn -> .cpp .h rules
$(SRCDIR)/Asn1TagFilterEnc.cpp \
$(SRCDIR)/Asn1TagFilterDec.cpp \
$(SRCDIR)/Asn1TagFilter.cpp \
$(HFILESDIR)$(PS)Asn1TagFilter.h \
$(HFILESDIR)$(PS)rtkey.h \
: asn1TagFilter.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(OSROOTDIR)$(PS)bin$(PS)asn1c asn1TagFilter.asn -cpp -xml -noxmlns

clean:
	$(RM) Asn1TagFilterEnc.cpp
	$(RM) Asn1TagFilterDec.cpp
	$(RM) Asn1TagFilter.cpp
	$(RM) $(HFILESDIR)$(PS)Asn1TagFilter.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.xml

