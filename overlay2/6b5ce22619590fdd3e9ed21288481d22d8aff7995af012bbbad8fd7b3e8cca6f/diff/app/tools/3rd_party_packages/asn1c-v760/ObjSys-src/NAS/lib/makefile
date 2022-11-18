# makefile to build generated files

include ../../../ASN-760/platform.mk

# include directories
OSROOTDIR = ../../../ASN-760
LIBDIR = .
RTSRCDIR = $(OSROOTDIR)/rtsrc
RTXSRCDIR = $(OSROOTDIR)/rtxsrc
RT3GPPSRCDIR = $(OSROOTDIR)/rt3gppsrc
SRCDIR = ..
SRC2DIR = ..

# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CDEBUG_) -D_TRACE -std=gnu99
IPATHS = -I$(SRCDIR) -I$(SRC2DIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(RTXSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

include ../objects.mk
include ../objects.mk

$(LIBDIR)/$(LIBPFX)NAS$(A) : $(ALLOBJECTS) $(SRC2OBJECTS)
	$(LIBCMD) $(ALLOBJECTS) $(SRC2OBJECTS)

# .c -> .obj rules
include ../rules.mk

TS44018Misc$(OBJ): $(SRC2DIR)$(PS)TS44018Misc.c \
 $(SRC2DIR)$(PS)TS44018Misc.h $(SRCDIR)$(PS)TS44018IES.h \
 $(RTXSRCDIR)$(PS)rtxContext.h $(RTXSRCDIR)$(PS)rtxDList.h \
 $(RTXSRCDIR)$(PS)osSysTypes.h $(RTXSRCDIR)$(PS)rtxExternDefs.h \
 $(RTXSRCDIR)$(PS)rtxCommonDefs.h $(RTXSRCDIR)$(PS)osMacros.h \
 $(RTXSRCDIR)$(PS)rtxStack.h $(RTSRCDIR)$(PS)asn1type.h \
 $(RTXSRCDIR)$(PS)rtxSList.h $(RTXSRCDIR)$(PS)rtxUTF8.h \
 $(RTSRCDIR)$(PS)asn1tag.h $(RTSRCDIR)$(PS)asn1ErrCodes.h \
 $(RTSRCDIR)$(PS)asn1version.h $(RTSRCDIR)$(PS)rtExternDefs.h \
 $(RTXSRCDIR)$(PS)rtxBitString.h $(RTSRCDIR)$(PS)rtContext.h \
 $(RTSRCDIR)$(PS)asn1CEvtHndlr.h $(RTXSRCDIR)$(PS)rtxError.h \
 $(RTXSRCDIR)$(PS)rtxErrCodes.h $(RTXSRCDIR)$(PS)rtxMemory.h \
 $(SRCDIR)$(PS)TS44060IES.h $(RTXSRCDIR)$(PS)rtxDiag.h \
 $(RTXSRCDIR)$(PS)rtxDiagBitTrace.h $(RTXSRCDIR)$(PS)rtxMemBuf.h \
 $(RTXSRCDIR)$(PS)rtxPrintToStream.h $(RTXSRCDIR)$(PS)rtxFile.h \
 $(RTXSRCDIR)$(PS)rtxMemLeakCheck.h $(RTXSRCDIR)$(PS)rtxPrintStream.h \
 $(RT3GPPSRCDIR)$(PS)rtx3GPP.h $(RTXSRCDIR)$(PS)rtxTBCD.h
	$(CC) $(CFLAGS) -c $(IPATHS) $(SRC2DIR)$(PS)TS44018Misc.c

clean:
	$(RM) *$(OBJ)
	$(RM) *.pdb
	$(RM) $(LIBDIR)/$(LIBPFX)NAS$(A)

