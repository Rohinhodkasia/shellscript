# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = test.asn1

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)c$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
BERSRCDIR = $(OSROOTDIR)$(PS)rtbersrc
OERSRCDIR = $(OSROOTDIR)$(PS)rtoersrc
PERSRCDIR = $(OSROOTDIR)$(PS)rtpersrc
XMLSRCDIR = $(OSROOTDIR)$(PS)rtxmlsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(BERSRCDIR)$(PS)asn1ber.h  \
$(OERSRCDIR)$(PS)asn1oer.h $(PERSRCDIR)$(PS)asn1per.h \
$(XMLSRCDIR)$(PS)osrtxml.h
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_) -D_TRACE
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(BERSRCDIR) \
-I$(OERSRCDIR) -I$(PERSRCDIR) -I$(XMLSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)$(PS)$(LIBPFX)asn1ber$(A) $(LIBDIR)$(PS)$(LIBPFX)asn1oer$(A) \
$(LIBDIR)$(PS)$(LIBPFX)asn1per$(A) $(LIBDIR)$(PS)$(LIBPFX)asn1xml$(A) \
$(LIBDIR)$(PS)$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1ber$(LLAEXT) $(LLPFX)asn1oer$(LLAEXT) \
$(LLPFX)asn1per$(LLAEXT) $(LLPFX)asn1xml$(LLAEXT) $(LLPFX)asn1rt$(LLAEXT) \
$(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
Test$(OBJ)

ENCOBJECTS =  \
TestEnc$(OBJ)

DECOBJECTS =  \
TestDec$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
$(SRCDIR)$(PS)TestEnc.c \
$(SRCDIR)$(PS)TestDec.c \
$(SRCDIR)$(PS)Test.c \
$(HFILESDIR)$(PS)Test.h \
$(HFILESDIR)$(PS)rtkey.h \
: $(ASN1FILE) $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -c -oer -trace -fqtvalue

depends: Test.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) TestEnc.c
	$(RM) TestDec.c
	$(RM) Test.c
	$(RM) $(HFILESDIR)$(PS)Test.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM_MSVC_FILES)

