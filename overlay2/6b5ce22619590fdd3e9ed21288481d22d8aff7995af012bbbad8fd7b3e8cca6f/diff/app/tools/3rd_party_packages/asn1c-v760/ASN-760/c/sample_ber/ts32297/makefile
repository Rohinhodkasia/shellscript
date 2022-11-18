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
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(BERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1ber$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1ber$(LLAEXT) $(LLPFX)asn1rt$(LLAEXT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
IMS-R8-2009-03$(OBJ)

ENCOBJECTS =  \
IMS-R8-2009-03Enc$(OBJ)

DECOBJECTS =  \
IMS-R8-2009-03Dec$(OBJ)

PRTOBJECTS =  \
IMS-R8-2009-03Print$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
reader$(EXE)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)IMS-R8-2009-03.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

reader$(OBJ) : $(SRCDIR)$(PS)reader.c $(RWHFILES)
	$(CC) -c $(CFLAGS) $(IPATHS) $(SRCDIR)$(PS)reader.c

# .c -> .obj rules
# common file rules
IMS-R8-2009-03$(OBJ) : $(SRCDIR)$(PS)IMS-R8-2009-03.c \
$(HFILESDIR)$(PS)IMS-R8-2009-03.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IMS-R8-2009-03.c

# decode file rules
IMS-R8-2009-03Dec$(OBJ) : $(SRCDIR)$(PS)IMS-R8-2009-03Dec.c \
$(HFILESDIR)$(PS)IMS-R8-2009-03.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IMS-R8-2009-03Dec.c

# encode file rules
IMS-R8-2009-03Enc$(OBJ) : $(SRCDIR)$(PS)IMS-R8-2009-03Enc.c \
$(HFILESDIR)$(PS)IMS-R8-2009-03.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IMS-R8-2009-03Enc.c

# print file rules
IMS-R8-2009-03Print$(OBJ) : $(SRCDIR)$(PS)IMS-R8-2009-03Print.c \
$(HFILESDIR)$(PS)IMS-R8-2009-03.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)IMS-R8-2009-03Print.c

# .asn -> .c .h rules
$(SRCDIR)/IMS-R8-2009-03Enc.c \
$(SRCDIR)/IMS-R8-2009-03Dec.c \
$(SRCDIR)/IMS-R8-2009-03.c \
$(SRCDIR)/IMS-R8-2009-03Print.c \
$(HFILESDIR)$(PS)IMS-R8-2009-03.h \
$(HFILESDIR)$(PS)rtkey.h \
: IMS-R8-2009-03.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(OSROOTDIR)$(PS)bin$(PS)asn1c IMS-R8-2009-03.asn -c -ber -print -fqtvalue

clean:
	$(RM) IMS-R8-2009-03Enc.c
	$(RM) IMS-R8-2009-03Dec.c
	$(RM) IMS-R8-2009-03.c
	$(RM) IMS-R8-2009-03Print.c
	$(RM) $(HFILESDIR)$(PS)IMS-R8-2009-03.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) *.exe
	$(RM_MSVC_FILES)
