# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = test.asn

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)c$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
OERSRCDIR = $(OSROOTDIR)$(PS)rtoersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(OERSRCDIR)$(PS)asn1oer.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(OERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)$(PS)$(LIBPFX)asn1oer$(A) $(LIBDIR)$(PS)$(LIBPFX)asn1rt$(A)
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

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)Test.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
$(SRCDIR)$(PS)TestEnc.c \
$(SRCDIR)$(PS)TestDec.c \
$(SRCDIR)$(PS)Test.c \
$(SRCDIR)$(PS)TestPrint.c \
$(SRCDIR)$(PS)TestTest.c \
$(HFILESDIR)$(PS)Test.h \
$(HFILESDIR)$(PS)rtkey.h \
: $(ASN1FILE) $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -c -oer -print -fqtvalue

depends: Test.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) TestEnc.c
	$(RM) TestDec.c
	$(RM) Test.c
	$(RM) TestPrint.c
	$(RM) TestTest.c
	$(RM) $(HFILESDIR)$(PS)Test.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.dat

