# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = test.asn

# include directories
OSROOTDIR = ../../..
RTSRCDIR = $(OSROOTDIR)/rtsrc
XMLSRCDIR = $(OSROOTDIR)/rtxmlsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)/asn1type.h $(XMLSRCDIR)/osrtxml.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_) -D_TRACE
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(XMLSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(RTLIBNAME)
LLIBS = $(LLXML) $(LLRT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR) $(XMLLPATHS)

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
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS) $(LLSYS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRTOBJECTS) 

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS) $(LLSYS)

RWHFILES = $(HFILESDIR)/Test.h $(HFILESDIR)/rtkey.h $(HFILES)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
$(SRCDIR)/TestEnc.c \
$(SRCDIR)/TestDec.c \
$(SRCDIR)/Test.c \
$(SRCDIR)/TestPrint.c \
$(HFILESDIR)/Test.h \
$(HFILESDIR)/rtkey.h \
: $(ASN1FILE) $(OSROOTDIR)/bin/asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -c -xml -xsd -geninit -print -trace

runtest : writer$(EXE) reader$(EXE)
	.$(PS)writer
	java -cp ../../../java/util/Val Val message.xml *.xsd
	.$(PS)reader

depends: Test.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) TestEnc.c
	$(RM) TestDec.c
	$(RM) Test.c
	$(RM) Test.xsd
	$(RM) TestPrint.c
	$(RM) $(HFILESDIR)$(PS)Test.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.xml

