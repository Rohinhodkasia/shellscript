# makefile to build generated files

include ../../platform.mk

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)c$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
BERSRCDIR = $(OSROOTDIR)$(PS)rtbersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(BERSRCDIR)$(PS)asn1ber.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I../../../specs/PKIX/Certificate \
-I../../../specs/PKIX/Common -I$(RTSRCDIR) -I$(BERSRCDIR) $(IPATHS_)
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
PKIX1-PSS-OAEP-Algorithms-2009$(OBJ)

ENCOBJECTS =  \
PKIX1Explicit-2009Enc$(OBJ) \
PKIX-CommonTypes-2009Enc$(OBJ) \
AlgorithmInformation-2009Enc$(OBJ) \
PKIX1Implicit-2009Enc$(OBJ) \
PKIX-X400Address-2009Enc$(OBJ) \
PKIX1-PSS-OAEP-Algorithms-2009Enc$(OBJ)

DECOBJECTS =  \
PKIX1Explicit-2009Dec$(OBJ) \
PKIX-CommonTypes-2009Dec$(OBJ) \
AlgorithmInformation-2009Dec$(OBJ) \
PKIX1Implicit-2009Dec$(OBJ) \
PKIX-X400Address-2009Dec$(OBJ) \
PKIX1-PSS-OAEP-Algorithms-2009Dec$(OBJ)

PRTOBJECTS =  \
PKIX1Explicit-2009Print$(OBJ) \
PKIX-CommonTypes-2009Print$(OBJ) \
AlgorithmInformation-2009Print$(OBJ) \
PKIX1Implicit-2009Print$(OBJ) \
PKIX-X400Address-2009Print$(OBJ) \
PKIX1-PSS-OAEP-Algorithms-2009Print$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS) \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)PKIX1Explicit-2009.h \
$(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h \
$(HFILESDIR)$(PS)AlgorithmInformation-2009.h \
$(HFILESDIR)$(PS)PKIX1Implicit-2009.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
$(SRCDIR)/PKIX1Explicit-2009Enc.c \
$(SRCDIR)/PKIX1Explicit-2009Dec.c \
$(SRCDIR)/PKIX1Explicit-2009.c \
$(SRCDIR)/PKIX1Explicit-2009Print.c \
$(HFILESDIR)$(PS)PKIX1Explicit-2009.h \
$(SRCDIR)/PKIX-CommonTypes-2009Enc.c \
$(SRCDIR)/PKIX-CommonTypes-2009Dec.c \
$(SRCDIR)/PKIX-CommonTypes-2009.c \
$(SRCDIR)/PKIX-CommonTypes-2009Print.c \
$(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h \
$(SRCDIR)/AlgorithmInformation-2009Enc.c \
$(SRCDIR)/AlgorithmInformation-2009Dec.c \
$(SRCDIR)/AlgorithmInformation-2009.c \
$(SRCDIR)/AlgorithmInformation-2009Print.c \
$(HFILESDIR)$(PS)AlgorithmInformation-2009.h \
$(SRCDIR)/PKIX1Implicit-2009Enc.c \
$(SRCDIR)/PKIX1Implicit-2009Dec.c \
$(SRCDIR)/PKIX1Implicit-2009.c \
$(SRCDIR)/PKIX1Implicit-2009Print.c \
$(HFILESDIR)$(PS)PKIX1Implicit-2009.h \
$(SRCDIR)/PKIX-X400Address-2009Enc.c \
$(SRCDIR)/PKIX-X400Address-2009Dec.c \
$(SRCDIR)/PKIX-X400Address-2009.c \
$(SRCDIR)/PKIX-X400Address-2009Print.c \
$(HFILESDIR)$(PS)PKIX-X400Address-2009.h \
$(SRCDIR)/PKIX1-PSS-OAEP-Algorithms-2009Enc.c \
$(SRCDIR)/PKIX1-PSS-OAEP-Algorithms-2009Dec.c \
$(SRCDIR)/PKIX1-PSS-OAEP-Algorithms-2009.c \
$(SRCDIR)/PKIX1-PSS-OAEP-Algorithms-2009Print.c \
$(HFILESDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009.h \
$(HFILESDIR)$(PS)rtkey.h \
: ../../../specs/PKIX/Certificate/acconfig.xml ../../../specs/PKIX/Certificate/PKIX1Explicit-2009.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(OSROOTDIR)$(PS)bin$(PS)asn1c ../../../specs/PKIX/Certificate/PKIX1Explicit-2009.asn -c -der -config ../../../specs/PKIX/Certificate/acconfig.xml -depends -I ../../../specs/PKIX/Certificate -I ../../../specs/PKIX/Common -noindeflen -print -fqtvalue

depends: PKIX1Explicit-2009.c PKIX-CommonTypes-2009.c \
AlgorithmInformation-2009.c PKIX1Implicit-2009.c PKIX-X400Address-2009.c \
PKIX1-PSS-OAEP-Algorithms-2009.c PKIXAlgs-2009.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) PKIX1Explicit-2009Enc.c
	$(RM) PKIX1Explicit-2009Dec.c
	$(RM) PKIX1Explicit-2009.c
	$(RM) PKIX1Explicit-2009Print.c
	$(RM) $(HFILESDIR)$(PS)PKIX1Explicit-2009.h 
	$(RM) PKIX-CommonTypes-2009Enc.c
	$(RM) PKIX-CommonTypes-2009Dec.c
	$(RM) PKIX-CommonTypes-2009.c
	$(RM) PKIX-CommonTypes-2009Print.c
	$(RM) $(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h 
	$(RM) AlgorithmInformation-2009Enc.c
	$(RM) AlgorithmInformation-2009Dec.c
	$(RM) AlgorithmInformation-2009.c
	$(RM) AlgorithmInformation-2009Print.c
	$(RM) $(HFILESDIR)$(PS)AlgorithmInformation-2009.h 
	$(RM) PKIX1Implicit-2009Enc.c
	$(RM) PKIX1Implicit-2009Dec.c
	$(RM) PKIX1Implicit-2009.c
	$(RM) PKIX1Implicit-2009Print.c
	$(RM) $(HFILESDIR)$(PS)PKIX1Implicit-2009.h 
	$(RM) PKIX-X400Address-2009Enc.c
	$(RM) PKIX-X400Address-2009Dec.c
	$(RM) PKIX-X400Address-2009.c
	$(RM) PKIX-X400Address-2009Print.c
	$(RM) $(HFILESDIR)$(PS)PKIX-X400Address-2009.h 
	$(RM) PKIX1-PSS-OAEP-Algorithms-2009Enc.c
	$(RM) PKIX1-PSS-OAEP-Algorithms-2009Dec.c
	$(RM) PKIX1-PSS-OAEP-Algorithms-2009.c
	$(RM) PKIX1-PSS-OAEP-Algorithms-2009Print.c
	$(RM) $(HFILESDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009.h 
	$(RM) PKIXAlgs-2009Enc.c
	$(RM) PKIXAlgs-2009Dec.c
	$(RM) PKIXAlgs-2009.c
	$(RM) PKIXAlgs-2009Print.c
	$(RM) $(HFILESDIR)$(PS)PKIXAlgs-2009.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) *.dat

