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
CFLAGS = -c $(CVARSMTD_) $(CFLAGS_) $(CBLDTYPE_)
CCFLAGS = -c $(CVARSMTD_) $(CCFLAGS_) $(CBLDTYPE_)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I../../../specs/PKIX/Certificate -I../../../specs/PKIX/Common -I$(RTSRCDIR) -I$(BERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1ber$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1ber$(LLAEXT) $(LLPFX)asn1rt$(LLAEXT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
PKIX1Explicit-2009$(OBJ) \
PKIX-CommonTypes-2009$(OBJ) \
AlgorithmInformation-2009$(OBJ) \
PKIX1Implicit-2009$(OBJ) \
PKIX-X400Address-2009$(OBJ) \
PKIXAlgs-2009$(OBJ) \
PKIX1-PSS-OAEP-Algorithms-2009$(OBJ)

ENCOBJECTS =  \
PKIX1Explicit-2009Enc$(OBJ) \
PKIX-CommonTypes-2009Enc$(OBJ) \
AlgorithmInformation-2009Enc$(OBJ) \
PKIX1Implicit-2009Enc$(OBJ) \
PKIX-X400Address-2009Enc$(OBJ) \
PKIXAlgs-2009Enc$(OBJ) \
PKIX1-PSS-OAEP-Algorithms-2009Enc$(OBJ)

DECOBJECTS =  \
PKIX1Explicit-2009Dec$(OBJ) \
PKIX-CommonTypes-2009Dec$(OBJ) \
AlgorithmInformation-2009Dec$(OBJ) \
PKIX1Implicit-2009Dec$(OBJ) \
PKIX-X400Address-2009Dec$(OBJ) \
PKIXAlgs-2009Dec$(OBJ) \
PKIX1-PSS-OAEP-Algorithms-2009Dec$(OBJ)

PRTOBJECTS =  \
PKIX1Explicit-2009Print$(OBJ) \
PKIX-CommonTypes-2009Print$(OBJ) \
AlgorithmInformation-2009Print$(OBJ) \
PKIX1Implicit-2009Print$(OBJ) \
PKIX-X400Address-2009Print$(OBJ) \
PKIXAlgs-2009Print$(OBJ) \
PKIX1-PSS-OAEP-Algorithms-2009Print$(OBJ)


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

RWHFILES = $(HFILESDIR)$(PS)PKIX1Explicit-2009.h  \
$(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h $(HFILESDIR)$(PS)AlgorithmInformation-2009.h  \
$(HFILESDIR)$(PS)PKIX1Implicit-2009.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

writer$(OBJ) : $(SRCDIR)$(PS)writer.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)/writer.cpp

reader$(OBJ) : $(SRCDIR)$(PS)reader.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) $(SRCDIR)/reader.cpp

# .cpp -> .obj rules
# common file rules
PKIX1Explicit-2009$(OBJ) : $(SRCDIR)$(PS)PKIX1Explicit-2009.cpp \
$(HFILESDIR)$(PS)PKIX1Explicit-2009.h  \
$(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h $(HFILESDIR)$(PS)AlgorithmInformation-2009.h  \
$(HFILESDIR)$(PS)PKIX1Implicit-2009.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX1Explicit-2009.cpp

# decode file rules
PKIX1Explicit-2009Dec$(OBJ) : $(SRCDIR)$(PS)PKIX1Explicit-2009Dec.cpp \
$(HFILESDIR)$(PS)PKIX1Explicit-2009.h  \
$(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h $(HFILESDIR)$(PS)AlgorithmInformation-2009.h  \
$(HFILESDIR)$(PS)PKIX1Implicit-2009.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX1Explicit-2009Dec.cpp

# encode file rules
PKIX1Explicit-2009Enc$(OBJ) : $(SRCDIR)$(PS)PKIX1Explicit-2009Enc.cpp \
$(HFILESDIR)$(PS)PKIX1Explicit-2009.h  \
$(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h $(HFILESDIR)$(PS)AlgorithmInformation-2009.h  \
$(HFILESDIR)$(PS)PKIX1Implicit-2009.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX1Explicit-2009Enc.cpp

# print file rules
PKIX1Explicit-2009Print$(OBJ) : $(SRCDIR)$(PS)PKIX1Explicit-2009Print.cpp \
$(HFILESDIR)$(PS)PKIX1Explicit-2009.h  \
$(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h $(HFILESDIR)$(PS)AlgorithmInformation-2009.h  \
$(HFILESDIR)$(PS)PKIX1Implicit-2009.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX1Explicit-2009Print.cpp

# common file rules
PKIX-CommonTypes-2009$(OBJ) : $(SRCDIR)$(PS)PKIX-CommonTypes-2009.cpp \
$(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX-CommonTypes-2009.cpp

# decode file rules
PKIX-CommonTypes-2009Dec$(OBJ) : $(SRCDIR)$(PS)PKIX-CommonTypes-2009Dec.cpp \
$(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX-CommonTypes-2009Dec.cpp

# encode file rules
PKIX-CommonTypes-2009Enc$(OBJ) : $(SRCDIR)$(PS)PKIX-CommonTypes-2009Enc.cpp \
$(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX-CommonTypes-2009Enc.cpp

# print file rules
PKIX-CommonTypes-2009Print$(OBJ) : $(SRCDIR)$(PS)PKIX-CommonTypes-2009Print.cpp \
$(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX-CommonTypes-2009Print.cpp

# common file rules
AlgorithmInformation-2009$(OBJ) : $(SRCDIR)$(PS)AlgorithmInformation-2009.cpp \
$(HFILESDIR)$(PS)AlgorithmInformation-2009.h  \
$(HFILESDIR)$(PS)PKIX1Implicit-2009.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)AlgorithmInformation-2009.cpp

# decode file rules
AlgorithmInformation-2009Dec$(OBJ) : $(SRCDIR)$(PS)AlgorithmInformation-2009Dec.cpp \
$(HFILESDIR)$(PS)AlgorithmInformation-2009.h  \
$(HFILESDIR)$(PS)PKIX1Implicit-2009.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)AlgorithmInformation-2009Dec.cpp

# encode file rules
AlgorithmInformation-2009Enc$(OBJ) : $(SRCDIR)$(PS)AlgorithmInformation-2009Enc.cpp \
$(HFILESDIR)$(PS)AlgorithmInformation-2009.h  \
$(HFILESDIR)$(PS)PKIX1Implicit-2009.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)AlgorithmInformation-2009Enc.cpp

# print file rules
AlgorithmInformation-2009Print$(OBJ) : $(SRCDIR)$(PS)AlgorithmInformation-2009Print.cpp \
$(HFILESDIR)$(PS)AlgorithmInformation-2009.h  \
$(HFILESDIR)$(PS)PKIX1Implicit-2009.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)AlgorithmInformation-2009Print.cpp

# common file rules
PKIX1Implicit-2009$(OBJ) : $(SRCDIR)$(PS)PKIX1Implicit-2009.cpp \
$(HFILESDIR)$(PS)PKIX1Implicit-2009.h  \
$(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h $(HFILESDIR)$(PS)PKIX1Explicit-2009.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX1Implicit-2009.cpp

# decode file rules
PKIX1Implicit-2009Dec$(OBJ) : $(SRCDIR)$(PS)PKIX1Implicit-2009Dec.cpp \
$(HFILESDIR)$(PS)PKIX1Implicit-2009.h  \
$(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h $(HFILESDIR)$(PS)PKIX1Explicit-2009.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX1Implicit-2009Dec.cpp

# encode file rules
PKIX1Implicit-2009Enc$(OBJ) : $(SRCDIR)$(PS)PKIX1Implicit-2009Enc.cpp \
$(HFILESDIR)$(PS)PKIX1Implicit-2009.h  \
$(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h $(HFILESDIR)$(PS)PKIX1Explicit-2009.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX1Implicit-2009Enc.cpp

# print file rules
PKIX1Implicit-2009Print$(OBJ) : $(SRCDIR)$(PS)PKIX1Implicit-2009Print.cpp \
$(HFILESDIR)$(PS)PKIX1Implicit-2009.h  \
$(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h $(HFILESDIR)$(PS)PKIX1Explicit-2009.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX1Implicit-2009Print.cpp

# common file rules
PKIX-X400Address-2009$(OBJ) : $(SRCDIR)$(PS)PKIX-X400Address-2009.cpp \
$(HFILESDIR)$(PS)PKIX-X400Address-2009.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX-X400Address-2009.cpp

# decode file rules
PKIX-X400Address-2009Dec$(OBJ) : $(SRCDIR)$(PS)PKIX-X400Address-2009Dec.cpp \
$(HFILESDIR)$(PS)PKIX-X400Address-2009.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX-X400Address-2009Dec.cpp

# encode file rules
PKIX-X400Address-2009Enc$(OBJ) : $(SRCDIR)$(PS)PKIX-X400Address-2009Enc.cpp \
$(HFILESDIR)$(PS)PKIX-X400Address-2009.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX-X400Address-2009Enc.cpp

# print file rules
PKIX-X400Address-2009Print$(OBJ) : $(SRCDIR)$(PS)PKIX-X400Address-2009Print.cpp \
$(HFILESDIR)$(PS)PKIX-X400Address-2009.h $(HFILESDIR)$(PS)rtkey.h  \
$(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX-X400Address-2009Print.cpp

# common file rules
PKIXAlgs-2009$(OBJ) : $(SRCDIR)$(PS)PKIXAlgs-2009.cpp \
$(HFILESDIR)$(PS)PKIXAlgs-2009.h  \
$(HFILESDIR)$(PS)AlgorithmInformation-2009.h $(HFILESDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIXAlgs-2009.cpp

# decode file rules
PKIXAlgs-2009Dec$(OBJ) : $(SRCDIR)$(PS)PKIXAlgs-2009Dec.cpp \
$(HFILESDIR)$(PS)PKIXAlgs-2009.h  \
$(HFILESDIR)$(PS)AlgorithmInformation-2009.h $(HFILESDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIXAlgs-2009Dec.cpp

# encode file rules
PKIXAlgs-2009Enc$(OBJ) : $(SRCDIR)$(PS)PKIXAlgs-2009Enc.cpp \
$(HFILESDIR)$(PS)PKIXAlgs-2009.h  \
$(HFILESDIR)$(PS)AlgorithmInformation-2009.h $(HFILESDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIXAlgs-2009Enc.cpp

# print file rules
PKIXAlgs-2009Print$(OBJ) : $(SRCDIR)$(PS)PKIXAlgs-2009Print.cpp \
$(HFILESDIR)$(PS)PKIXAlgs-2009.h  \
$(HFILESDIR)$(PS)AlgorithmInformation-2009.h $(HFILESDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIXAlgs-2009Print.cpp

# common file rules
PKIX1-PSS-OAEP-Algorithms-2009$(OBJ) : $(SRCDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009.cpp \
$(HFILESDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009.h  \
$(HFILESDIR)$(PS)AlgorithmInformation-2009.h $(HFILESDIR)$(PS)PKIXAlgs-2009.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009.cpp

# decode file rules
PKIX1-PSS-OAEP-Algorithms-2009Dec$(OBJ) : $(SRCDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009Dec.cpp \
$(HFILESDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009.h  \
$(HFILESDIR)$(PS)AlgorithmInformation-2009.h $(HFILESDIR)$(PS)PKIXAlgs-2009.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009Dec.cpp

# encode file rules
PKIX1-PSS-OAEP-Algorithms-2009Enc$(OBJ) : $(SRCDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009Enc.cpp \
$(HFILESDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009.h  \
$(HFILESDIR)$(PS)AlgorithmInformation-2009.h $(HFILESDIR)$(PS)PKIXAlgs-2009.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009Enc.cpp

# print file rules
PKIX1-PSS-OAEP-Algorithms-2009Print$(OBJ) : $(SRCDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009Print.cpp \
$(HFILESDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009.h  \
$(HFILESDIR)$(PS)AlgorithmInformation-2009.h $(HFILESDIR)$(PS)PKIXAlgs-2009.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009Print.cpp

# .asn -> .cpp .h rules
$(SRCDIR)/PKIX1Explicit-2009Enc.cpp \
$(SRCDIR)/PKIX1Explicit-2009Dec.cpp \
$(SRCDIR)/PKIX1Explicit-2009.cpp \
$(SRCDIR)/PKIX1Explicit-2009Print.cpp \
$(HFILESDIR)$(PS)PKIX1Explicit-2009.h \
$(SRCDIR)/PKIX-CommonTypes-2009Enc.cpp \
$(SRCDIR)/PKIX-CommonTypes-2009Dec.cpp \
$(SRCDIR)/PKIX-CommonTypes-2009.cpp \
$(SRCDIR)/PKIX-CommonTypes-2009Print.cpp \
$(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h \
$(SRCDIR)/AlgorithmInformation-2009Enc.cpp \
$(SRCDIR)/AlgorithmInformation-2009Dec.cpp \
$(SRCDIR)/AlgorithmInformation-2009.cpp \
$(SRCDIR)/AlgorithmInformation-2009Print.cpp \
$(HFILESDIR)$(PS)AlgorithmInformation-2009.h \
$(SRCDIR)/PKIX1Implicit-2009Enc.cpp \
$(SRCDIR)/PKIX1Implicit-2009Dec.cpp \
$(SRCDIR)/PKIX1Implicit-2009.cpp \
$(SRCDIR)/PKIX1Implicit-2009Print.cpp \
$(HFILESDIR)$(PS)PKIX1Implicit-2009.h \
$(SRCDIR)/PKIX-X400Address-2009Enc.cpp \
$(SRCDIR)/PKIX-X400Address-2009Dec.cpp \
$(SRCDIR)/PKIX-X400Address-2009.cpp \
$(SRCDIR)/PKIX-X400Address-2009Print.cpp \
$(HFILESDIR)$(PS)PKIX-X400Address-2009.h \
$(SRCDIR)/PKIXAlgs-2009Enc.cpp \
$(SRCDIR)/PKIXAlgs-2009Dec.cpp \
$(SRCDIR)/PKIXAlgs-2009.cpp \
$(SRCDIR)/PKIXAlgs-2009Print.cpp \
$(HFILESDIR)$(PS)PKIXAlgs-2009.h \
$(SRCDIR)/PKIX1-PSS-OAEP-Algorithms-2009Enc.cpp \
$(SRCDIR)/PKIX1-PSS-OAEP-Algorithms-2009Dec.cpp \
$(SRCDIR)/PKIX1-PSS-OAEP-Algorithms-2009.cpp \
$(SRCDIR)/PKIX1-PSS-OAEP-Algorithms-2009Print.cpp \
$(HFILESDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009.h \
$(HFILESDIR)$(PS)rtkey.h \
: ../../../specs/PKIX/Certificate/acconfig.xml ../../../specs/PKIX/Certificate/PKIX1Explicit-2009.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(OSROOTDIR)$(PS)bin$(PS)asn1c ../../../specs/PKIX/Certificate/PKIX1Explicit-2009.asn -cpp -der -config ../../../specs/PKIX/Certificate/acconfig.xml -depends -I ../../../specs/PKIX/Certificate -I ../../../specs/PKIX/Common -noindeflen -print

clean:
	$(RM) PKIX1Explicit-2009Enc.cpp
	$(RM) PKIX1Explicit-2009Dec.cpp
	$(RM) PKIX1Explicit-2009.cpp
	$(RM) PKIX1Explicit-2009Print.cpp
	$(RM) $(HFILESDIR)$(PS)PKIX1Explicit-2009.h 
	$(RM) PKIX-CommonTypes-2009Enc.cpp
	$(RM) PKIX-CommonTypes-2009Dec.cpp
	$(RM) PKIX-CommonTypes-2009.cpp
	$(RM) PKIX-CommonTypes-2009Print.cpp
	$(RM) $(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h 
	$(RM) AlgorithmInformation-2009Enc.cpp
	$(RM) AlgorithmInformation-2009Dec.cpp
	$(RM) AlgorithmInformation-2009.cpp
	$(RM) AlgorithmInformation-2009Print.cpp
	$(RM) $(HFILESDIR)$(PS)AlgorithmInformation-2009.h 
	$(RM) PKIX1Implicit-2009Enc.cpp
	$(RM) PKIX1Implicit-2009Dec.cpp
	$(RM) PKIX1Implicit-2009.cpp
	$(RM) PKIX1Implicit-2009Print.cpp
	$(RM) $(HFILESDIR)$(PS)PKIX1Implicit-2009.h 
	$(RM) PKIX-X400Address-2009Enc.cpp
	$(RM) PKIX-X400Address-2009Dec.cpp
	$(RM) PKIX-X400Address-2009.cpp
	$(RM) PKIX-X400Address-2009Print.cpp
	$(RM) $(HFILESDIR)$(PS)PKIX-X400Address-2009.h 
	$(RM) PKIXAlgs-2009Enc.cpp
	$(RM) PKIXAlgs-2009Dec.cpp
	$(RM) PKIXAlgs-2009.cpp
	$(RM) PKIXAlgs-2009Print.cpp
	$(RM) $(HFILESDIR)$(PS)PKIXAlgs-2009.h 
	$(RM) PKIX1-PSS-OAEP-Algorithms-2009Enc.cpp
	$(RM) PKIX1-PSS-OAEP-Algorithms-2009Dec.cpp
	$(RM) PKIX1-PSS-OAEP-Algorithms-2009.cpp
	$(RM) PKIX1-PSS-OAEP-Algorithms-2009Print.cpp
	$(RM) $(HFILESDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.dat

