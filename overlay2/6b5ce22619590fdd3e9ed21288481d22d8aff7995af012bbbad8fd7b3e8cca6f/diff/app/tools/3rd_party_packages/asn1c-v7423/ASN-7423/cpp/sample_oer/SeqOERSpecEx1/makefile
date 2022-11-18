# makefile to build generated files

include ../../platform.mk

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)cpp$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
OERSRCDIR = $(OSROOTDIR)$(PS)rtoersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(RTSRCDIR)$(PS)asn1CppTypes.h \
$(OERSRCDIR)$(PS)asn1oer.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_) -D_TRAC
CCFLAGS = -c $(CVARS_) $(CCFLAGS_) $(CBLDTYPE_) -D_TRACE
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(OERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1oer$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLOER) $(LLRT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
Test$(OBJ)

ENCOBJECTS =  \
TestEnc$(OBJ)

DECOBJECTS =  \
TestDec$(OBJ)

PRTOBJECTS =  \
TestPrint$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS)  \
 $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)Test.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

writer$(OBJ) : $(SRCDIR)$(PS)writer.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)$(PS)writer.cpp

reader$(OBJ) : $(SRCDIR)$(PS)reader.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)$(PS)reader.cpp

# .cpp -> .obj rules
# common file rules
Test$(OBJ) : $(SRCDIR)$(PS)Test.cpp \
$(HFILESDIR)$(PS)Test.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)Test.cpp

# decode file rules
TestDec$(OBJ) : $(SRCDIR)$(PS)TestDec.cpp \
$(HFILESDIR)$(PS)Test.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TestDec.cpp

# encode file rules
TestEnc$(OBJ) : $(SRCDIR)$(PS)TestEnc.cpp \
$(HFILESDIR)$(PS)Test.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TestEnc.cpp

# print file rules
TestPrint$(OBJ) : $(SRCDIR)$(PS)TestPrint.cpp \
$(HFILESDIR)$(PS)Test.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)TestPrint.cpp

# .asn -> .cpp .h rules
$(SRCDIR)$(PS)TestEnc.cpp \
$(SRCDIR)$(PS)TestDec.cpp \
$(SRCDIR)$(PS)Test.cpp \
$(SRCDIR)$(PS)TestPrint.cpp \
$(HFILESDIR)$(PS)Test.h \
$(HFILESDIR)$(PS)rtkey.h \
: test.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	..$(PS)..$(PS)..$(PS)bin$(PS)asn1c test.asn -cpp -oer -print -trace -fqtvalue

clean:
	$(RM) TestEnc.cpp
	$(RM) TestDec.cpp
	$(RM) Test.cpp
	$(RM) TestPrint.cpp
	$(RM) $(HFILESDIR)$(PS)Test.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.dat

