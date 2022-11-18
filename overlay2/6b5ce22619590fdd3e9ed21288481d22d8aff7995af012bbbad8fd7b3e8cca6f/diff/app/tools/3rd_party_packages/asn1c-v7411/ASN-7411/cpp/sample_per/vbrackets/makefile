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
VersionBrackets$(OBJ)

ENCOBJECTS =  \
VersionBracketsEnc$(OBJ)

DECOBJECTS =  \
VersionBracketsDec$(OBJ)

PRTOBJECTS =  \
VersionBracketsPrint$(OBJ)

CPYOBJECTS =  \
VersionBracketsCopy$(OBJ)

CMPOBJECTS =  \
VersionBracketsCompare$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
$(CPYOBJECTS) $(CMPOBJECTS) writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
 $(PRTOBJECTS) $(CPYOBJECTS) $(CMPOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS) $(CPYOBJECTS) $(CMPOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)/VersionBrackets.h $(HFILESDIR)/rtkey.h $(HFILES)

writer$(OBJ) : $(SRCDIR)/writer.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)/writer.cpp

reader$(OBJ) : $(SRCDIR)/reader.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)/reader.cpp

# .cpp -> .obj rules
# common file rules
VersionBrackets$(OBJ) : $(SRCDIR)/VersionBrackets.cpp \
$(HFILESDIR)/VersionBrackets.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/VersionBrackets.cpp

# decode file rules
VersionBracketsDec$(OBJ) : $(SRCDIR)/VersionBracketsDec.cpp \
$(HFILESDIR)/VersionBrackets.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/VersionBracketsDec.cpp

# encode file rules
VersionBracketsEnc$(OBJ) : $(SRCDIR)/VersionBracketsEnc.cpp \
$(HFILESDIR)/VersionBrackets.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/VersionBracketsEnc.cpp

# print file rules
VersionBracketsPrint$(OBJ) : $(SRCDIR)/VersionBracketsPrint.cpp \
$(HFILESDIR)/VersionBrackets.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/VersionBracketsPrint.cpp

# copy file rules
VersionBracketsCopy$(OBJ) : $(SRCDIR)/VersionBracketsCopy.cpp \
$(HFILESDIR)/VersionBrackets.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/VersionBracketsCopy.cpp

# compare file rules
VersionBracketsCompare$(OBJ) : $(SRCDIR)/VersionBracketsCompare.cpp \
$(HFILESDIR)/VersionBrackets.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/VersionBracketsCompare.cpp

# .asn -> .cpp .h rules
$(SRCDIR)/VersionBracketsEnc.cpp \
$(SRCDIR)/VersionBracketsDec.cpp \
$(SRCDIR)/VersionBrackets.cpp \
$(SRCDIR)/VersionBracketsPrint.cpp \
$(SRCDIR)/VersionBracketsCopy.cpp \
$(SRCDIR)/VersionBracketsCompare.cpp \
$(HFILESDIR)/VersionBrackets.h \
$(HFILESDIR)/rtkey.h \
: vbrackets.asn $(OSROOTDIR)/bin/asn1c$(EXE)
	..$(PS)..$(PS)..$(PS)bin$(PS)asn1c vbrackets.asn -cpp -per -compare -copy -print -trace

clean:
	$(RM) VersionBracketsEnc.cpp
	$(RM) VersionBracketsDec.cpp
	$(RM) VersionBrackets.cpp
	$(RM) VersionBracketsPrint.cpp
	$(RM) VersionBracketsCopy.cpp
	$(RM) VersionBracketsCompare.cpp
	$(RM) VersionBrackets.h 
	$(RM) rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.dat

