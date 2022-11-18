# makefile to build generated files

include ../../platform.mk

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
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_)
CCFLAGS = -c $(CVARS_) $(CCFLAGS_) $(CBLDTYPE_)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(BERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1ber$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1ber$(LLAEXT) $(LLPFX)asn1rt$(LLAEXT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
IMS-R8-2009-03$(OBJ)

ENCOBJECTS =  \
IMS-R8-2009-03Enc$(OBJ)

DECOBJECTS =  \
IMS-R8-2009-03Dec$(OBJ)

PRTOBJECTS =  \
IMS-R8-2009-03Print$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
reader$(EXE)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)IMS-R8-2009-03.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

reader$(OBJ) : $(SRCDIR)$(PS)reader.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)$(PS)reader.cpp

# .cpp -> .obj rules
# common file rules
IMS-R8-2009-03$(OBJ) : $(SRCDIR)$(PS)IMS-R8-2009-03.cpp \
$(HFILESDIR)$(PS)IMS-R8-2009-03.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IMS-R8-2009-03.cpp

# decode file rules
IMS-R8-2009-03Dec$(OBJ) : $(SRCDIR)$(PS)IMS-R8-2009-03Dec.cpp \
$(HFILESDIR)$(PS)IMS-R8-2009-03.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IMS-R8-2009-03Dec.cpp

# encode file rules
IMS-R8-2009-03Enc$(OBJ) : $(SRCDIR)$(PS)IMS-R8-2009-03Enc.cpp \
$(HFILESDIR)$(PS)IMS-R8-2009-03.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IMS-R8-2009-03Enc.cpp

# print file rules
IMS-R8-2009-03Print$(OBJ) : $(SRCDIR)$(PS)IMS-R8-2009-03Print.cpp \
$(HFILESDIR)$(PS)IMS-R8-2009-03.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IMS-R8-2009-03Print.cpp

# .asn -> .cpp .h rules
$(SRCDIR)/IMS-R8-2009-03Enc.cpp \
$(SRCDIR)/IMS-R8-2009-03Dec.cpp \
$(SRCDIR)/IMS-R8-2009-03.cpp \
$(SRCDIR)/IMS-R8-2009-03Print.cpp \
$(HFILESDIR)$(PS)IMS-R8-2009-03.h \
$(HFILESDIR)$(PS)rtkey.h \
: IMS-R8-2009-03.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(OSROOTDIR)$(PS)bin$(PS)asn1c IMS-R8-2009-03.asn -cpp -ber -print -fqtvalue -stream

clean:
	$(RM) IMS-R8-2009-03Enc.cpp
	$(RM) IMS-R8-2009-03Dec.cpp
	$(RM) IMS-R8-2009-03.cpp
	$(RM) IMS-R8-2009-03Print.cpp
	$(RM) $(HFILESDIR)$(PS)IMS-R8-2009-03.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) *.exe
	$(RM_MSVC_FILES)
