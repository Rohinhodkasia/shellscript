# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)/asn1type.h $(RTSRCDIR)/asn1CppTypes.h  \
$(BERSRCDIR)/asn1ber.h $(BERSRCDIR)/asn1BerCppTypes.h 

# run-time libraries
LIBS = $(LIBDIR)/$(BERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
LLIBS = $(BSLIBS)

OBJECTS =  \
PKCS-1$(OBJ)

ENCOBJECTS =  \
PKCS-1Enc$(OBJ)

DECOBJECTS =  \
PKCS-1Dec$(OBJ)

PRTOBJECTS =  \
PKCS-1Print$(OBJ)

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

RWHFILES = $(HFILESDIR)/PKCS-1.h $(HFILESDIR)/rtkey.h $(HFILES)

writer$(OBJ) : $(SRCDIR)$(PS)writer.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)/writer.cpp

reader$(OBJ) : $(SRCDIR)$(PS)reader.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)/reader.cpp

# .cpp -> .obj rules
# common file rules
PKCS-1$(OBJ) : $(SRCDIR)/PKCS-1.cpp \
$(HFILESDIR)/PKCS-1.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/PKCS-1.cpp

# decode file rules
PKCS-1Dec$(OBJ) : $(SRCDIR)/PKCS-1Dec.cpp \
$(HFILESDIR)/PKCS-1.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/PKCS-1Dec.cpp

# encode file rules
PKCS-1Enc$(OBJ) : $(SRCDIR)/PKCS-1Enc.cpp \
$(HFILESDIR)/PKCS-1.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/PKCS-1Enc.cpp

# print file rules
PKCS-1Print$(OBJ) : $(SRCDIR)/PKCS-1Print.cpp \
$(HFILESDIR)/PKCS-1.h $(HFILESDIR)/rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)/PKCS-1Print.cpp

# .asn -> .cpp .h rules
$(SRCDIR)/PKCS-1Enc.cpp \
$(SRCDIR)/PKCS-1Dec.cpp \
$(SRCDIR)/PKCS-1.cpp \
$(SRCDIR)/PKCS-1Print.cpp \
$(HFILESDIR)/PKCS-1.h \
$(HFILESDIR)/rtkey.h \
: pkcs1.cfg pkcs-1v2.asn $(OSROOTDIR)/bin/asn1c$(EXE)
	..$(PS)..$(PS)..$(PS)bin$(PS)asn1c pkcs-1v2.asn -cpp -der -config pkcs1.cfg -events -noindeflen -print -table-unions

clean:
	$(RM) PKCS-1Enc.cpp
	$(RM) PKCS-1Dec.cpp
	$(RM) PKCS-1.cpp
	$(RM) PKCS-1Print.cpp
	$(RM) $(HFILESDIR)$(PS)PKCS-1.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.dat

