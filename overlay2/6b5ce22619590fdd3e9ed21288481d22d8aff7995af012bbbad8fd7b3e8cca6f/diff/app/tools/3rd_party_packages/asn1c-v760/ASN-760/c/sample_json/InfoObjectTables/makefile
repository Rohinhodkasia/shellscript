# makefile to build generated files

include ../../platform.mk

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)c$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_)
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(RTSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1json$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1json$(LLAEXT) $(LLPFX)asn1rt$(LLAEXT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
InfoObject$(OBJ)

ENCOBJECTS =  \
InfoObjectEnc$(OBJ)

DECOBJECTS =  \
InfoObjectDec$(OBJ)

PRTOBJECTS =  \
InfoObjectPrint$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)InfoObject.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

writer$(OBJ) : $(SRCDIR)$(PS)writer.c $(RWHFILES)
	$(CC) -c $(CFLAGS) $(IPATHS) $(SRCDIR)$(PS)writer.c

reader$(OBJ) : $(SRCDIR)$(PS)reader.c $(RWHFILES)
	$(CC) -c $(CFLAGS) $(IPATHS) $(SRCDIR)$(PS)reader.c

# .c -> .obj rules
# common file rules
InfoObject$(OBJ) : $(SRCDIR)$(PS)InfoObject.c \
$(HFILESDIR)$(PS)InfoObject.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)InfoObject.c

# decode file rules
InfoObjectDec$(OBJ) : $(SRCDIR)$(PS)InfoObjectDec.c \
$(HFILESDIR)$(PS)InfoObject.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)InfoObjectDec.c

# encode file rules
InfoObjectEnc$(OBJ) : $(SRCDIR)$(PS)InfoObjectEnc.c \
$(HFILESDIR)$(PS)InfoObject.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)InfoObjectEnc.c

# print file rules
InfoObjectPrint$(OBJ) : $(SRCDIR)$(PS)InfoObjectPrint.c \
$(HFILESDIR)$(PS)InfoObject.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRCDIR)$(PS)InfoObjectPrint.c

# .asn -> .c .h rules
$(SRCDIR)/InfoObjectEnc.c \
$(SRCDIR)/InfoObjectDec.c \
$(SRCDIR)/InfoObject.c \
$(SRCDIR)/InfoObjectPrint.c \
$(HFILESDIR)$(PS)InfoObject.h \
$(HFILESDIR)$(PS)rtkey.h \
: ../../sample_per/infoObject/infoObject.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(OSROOTDIR)$(PS)bin$(PS)asn1c ../../sample_per/infoObject/infoObject.asn -c -json -print -table-unions -fqtvalue

clean:
	$(RM) InfoObjectEnc.c
	$(RM) InfoObjectDec.c
	$(RM) InfoObject.c
	$(RM) InfoObjectPrint.c
	$(RM) $(HFILESDIR)$(PS)InfoObject.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
