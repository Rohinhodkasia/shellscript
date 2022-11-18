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
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_)
CCFLAGS = -c $(CVARS_) $(CCFLAGS_) $(CBLDTYPE_)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1json$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1json$(LLAEXT) $(LLPFX)asn1rt$(LLAEXT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
Extensions$(OBJ)

ENCOBJECTS =  \
ExtensionsEnc$(OBJ)

DECOBJECTS =  \
ExtensionsDec$(OBJ)

PRTOBJECTS =  \
ExtensionsPrint$(OBJ)

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

RWHFILES = $(HFILESDIR)$(PS)Extensions.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

writer$(OBJ) : $(SRCDIR)$(PS)writer.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)$(PS)writer.cpp

reader$(OBJ) : $(SRCDIR)$(PS)reader.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)$(PS)reader.cpp

# .cpp -> .obj rules
# common file rules
Extensions$(OBJ) : $(SRCDIR)$(PS)Extensions.cpp \
$(HFILESDIR)$(PS)Extensions.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Extensions.cpp

# decode file rules
ExtensionsDec$(OBJ) : $(SRCDIR)$(PS)ExtensionsDec.cpp \
$(HFILESDIR)$(PS)Extensions.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)ExtensionsDec.cpp

# encode file rules
ExtensionsEnc$(OBJ) : $(SRCDIR)$(PS)ExtensionsEnc.cpp \
$(HFILESDIR)$(PS)Extensions.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)ExtensionsEnc.cpp

# print file rules
ExtensionsPrint$(OBJ) : $(SRCDIR)$(PS)ExtensionsPrint.cpp \
$(HFILESDIR)$(PS)Extensions.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)ExtensionsPrint.cpp

# .asn -> .cpp .h rules
$(SRCDIR)/ExtensionsEnc.cpp \
$(SRCDIR)/ExtensionsDec.cpp \
$(SRCDIR)/Extensions.cpp \
$(SRCDIR)/ExtensionsPrint.cpp \
$(HFILESDIR)$(PS)Extensions.h \
$(HFILESDIR)$(PS)rtkey.h \
: extensions.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(OSROOTDIR)$(PS)bin$(PS)asn1c extensions.asn -cpp -jer+ -print

clean:
	$(RM) ExtensionsEnc.cpp
	$(RM) ExtensionsDec.cpp
	$(RM) Extensions.cpp
	$(RM) ExtensionsPrint.cpp
	$(RM) $(HFILESDIR)$(PS)Extensions.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
