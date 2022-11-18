# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)cpp$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(RTSRCDIR)$(PS)asn1CppTypes.h 
# compiler defs
CFLAGS = -c $(CVARSMTD_) $(CFLAGS_) $(CBLDTYPE_)
CCFLAGS = $(CFLAGS)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)$(PS)$(LIBPFX)asn1json$(A) $(LIBDIR)$(PS)$(LIBPFX)asn1rt$(A)
LLIBS = $(LLJSON) $(LLRT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
AllTypes$(OBJ)

ENCOBJECTS =  \
AllTypesEnc$(OBJ)

DECOBJECTS =  \
AllTypesDec$(OBJ)

PRTOBJECTS =  \
AllTypesPrint$(OBJ)

TESTOBJECTS =  \
AllTypesTest$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
$(TESTOBJECTS) writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
 $(TESTOBJECTS) $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)AllTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

writer$(OBJ) : $(SRCDIR)$(PS)writer.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)$(PS)writer.cpp

reader$(OBJ) : $(SRCDIR)$(PS)reader.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)$(PS)reader.cpp

# .cpp -> .obj rules
# common file rules
AllTypes$(OBJ) : $(SRCDIR)$(PS)AllTypes.cpp \
$(HFILESDIR)$(PS)AllTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)AllTypes.cpp

# decode file rules
AllTypesDec$(OBJ) : $(SRCDIR)$(PS)AllTypesDec.cpp \
$(HFILESDIR)$(PS)AllTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)AllTypesDec.cpp

# encode file rules
AllTypesEnc$(OBJ) : $(SRCDIR)$(PS)AllTypesEnc.cpp \
$(HFILESDIR)$(PS)AllTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)AllTypesEnc.cpp

# print file rules
AllTypesPrint$(OBJ) : $(SRCDIR)$(PS)AllTypesPrint.cpp \
$(HFILESDIR)$(PS)AllTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)AllTypesPrint.cpp

# test file rules
AllTypesTest$(OBJ) : $(SRCDIR)$(PS)AllTypesTest.cpp \
$(HFILESDIR)$(PS)AllTypes.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)AllTypesTest.cpp

# .asn -> .cpp .h rules
$(SRCDIR)$(PS)AllTypesEnc.cpp \
$(SRCDIR)$(PS)AllTypesDec.cpp \
$(SRCDIR)$(PS)AllTypes.cpp \
$(SRCDIR)$(PS)AllTypesPrint.cpp \
$(SRCDIR)$(PS)AllTypesTest.cpp \
$(HFILESDIR)$(PS)AllTypes.h \
$(HFILESDIR)$(PS)rtkey.h \
: .$(PS)employee.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	..$(PS)..$(PS)..$(PS)bin$(PS)asn1c .$(PS)employee.asn -cpp -json -print -test

clean:
	$(RM) AllTypesEnc.cpp
	$(RM) AllTypesDec.cpp
	$(RM) AllTypes.cpp
	$(RM) AllTypesPrint.cpp
	$(RM) AllTypesTest.cpp
	$(RM) $(HFILESDIR)$(PS)AllTypes.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) .$(PS)rtkey.h
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.json

