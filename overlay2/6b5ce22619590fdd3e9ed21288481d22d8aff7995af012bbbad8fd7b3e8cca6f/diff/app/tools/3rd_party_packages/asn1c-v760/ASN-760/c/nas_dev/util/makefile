# makefile to build test program

include ../../platform.mk

LIBDIR = ../../lib
RT3GPPLIBDIR = ../debug/lib
RT3GPPLIBDIR2 = ../../build_lib/lcobj
RT3GPPSRCDIR = ../../../rt3gppsrc
RTSRCDIR  = ../../../rtsrc
RTXSRCDIR = ../../../rtxsrc
SRCDIR = ../src
SRC2DIR = ../src2

CFLAGS  = -D_TRACE $(CBLDTYPE_) $(CVARS_) $(MCFLAGS) $(CFLAGS_)
IPATHS  = -I. -I../../.. -I$(RTXSRCDIR) -I$(RT3GPPSRCDIR) -I$(SRCDIR) \
				-I$(SRC2DIR)

LINKOPT	= $(LINKOPT_)
LPATHS  = $(LPPFX)$(RT3GPPLIBDIR) $(LPPFX)$(LIBDIR) $(LPATHS_)

all : nas_decoder$(EXE) # nas_rwr$(EXE)

nas_decoder$(EXE) : nas_decoder$(OBJ) \
$(RT3GPPLIBDIR)/$(LIBPFX)osys3gpp$(A) \
$(LIBDIR)/$(RTLIBNAME) $(LIBDIR)/$(A3GPPLIBNAME)
	$(LINK) nas_decoder$(OBJ) $(LINKOPT) $(LPATHS) \
	   $(LLPFX)osys3gpp$(LLAEXT) $(LLRT) $(LLASN1RT3GPP) $(LLSYS)

nas_decoder$(OBJ) : nas_decoder.c \
 $(SRCDIR)/TS24008Msgs.h $(SRCDIR)/rtkey.h \
 $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
 $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
 $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/osMacros.h \
 $(RTSRCDIR)/asn1type.h $(RTXSRCDIR)/rtxSList.h \
 $(RTXSRCDIR)/rtxStack.h $(RTXSRCDIR)/rtxUTF8.h \
 $(RTSRCDIR)/asn1tag.h $(RTSRCDIR)/asn1ErrCodes.h \
 $(RTSRCDIR)/asn1version.h $(RTSRCDIR)/rtExternDefs.h \
 $(RTXSRCDIR)/rtxBitString.h $(RTSRCDIR)/rtContext.h \
 $(RTXSRCDIR)/rtxError.h $(RTXSRCDIR)/rtxErrCodes.h \
 $(RTXSRCDIR)/rtxMemory.h $(SRCDIR)/TS24007L3.h $(SRCDIR)/TS24008IES.h \
 $(SRCDIR)/TS24011Msgs.h $(SRCDIR)/TS24011IES.h $(SRCDIR)/TS24301Msgs.h \
 $(SRCDIR)/TS24301IES.h $(SRCDIR)/TS24501Msgs.h $(RTXSRCDIR)/rtxBitDecode.h \
 $(RTXSRCDIR)/rtxCharStr.h $(RTXSRCDIR)/rtxDiag.h \
 $(RTXSRCDIR)/rtxDiagBitTrace.h $(RTXSRCDIR)/rtxMemBuf.h \
 $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxFile.h \
 $(RTXSRCDIR)/rtxMemLeakCheck.h $(RTXSRCDIR)/rtxPrint.h \
 $(RTXSRCDIR)/rtxPrintStream.h $(RT3GPPSRCDIR)/rt3gppNasSec.h \
 $(RT3GPPSRCDIR)/osCrypto.h

nas_rwr$(EXE) : nas_rwr$(OBJ) $(RT3GPPLIBDIR)/$(LIBPFX)osys3gpp$(A) \
$(LIBDIR)/$(RTLIBNAME)
	$(LINK) nas_rwr$(OBJ) $(LINKOPT) $(LPATHS) \
	   $(LLPFX)osys3gpp$(LLAEXT) $(LLRT) $(LLASN1RT3GPP) $(LLSYS)

nas_rwr$(OBJ) : nas_rwr.c \
  $(SRCDIR)/TS24008Msgs.h \
  $(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h \
  $(RTXSRCDIR)/osSysTypes.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/osMacros.h \
  $(RTSRCDIR)/asn1type.h $(RTXSRCDIR)/rtxExternDefs.h \
  $(RTXSRCDIR)/rtxSList.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxStack.h $(RTXSRCDIR)/rtxUTF8.h \
  $(RTSRCDIR)/asn1tag.h $(RTXSRCDIR)/osSysTypes.h \
  $(RTSRCDIR)/asn1ErrCodes.h $(RTSRCDIR)/asn1version.h \
  $(RTSRCDIR)/rtExternDefs.h $(RTXSRCDIR)/rtxBitString.h \
  $(RTSRCDIR)/rtContext.h $(RTXSRCDIR)/rtxContext.h \
  $(RTXSRCDIR)/rtxCommonDefs.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h \
  $(SRCDIR)/TS24007L3.h $(SRCDIR)/TS24008IES.h \
  $(SRCDIR)/TS24011Msgs.h $(SRCDIR)/TS24011IES.h \
  $(SRCDIR)/TS24301Msgs.h $(SRCDIR)/TS24301IES.h $(SRCDIR)/TS24501Msgs.h \
  $(RTXSRCDIR)/rtxBitDecode.h $(RTXSRCDIR)/rtxCharStr.h \
  $(RTXSRCDIR)/rtxDiag.h $(RTXSRCDIR)/rtxDiagBitTrace.h \
  $(RTXSRCDIR)/rtxMemBuf.h $(RTXSRCDIR)/rtxSList.h \
  $(RTXSRCDIR)/rtxPrintToStream.h $(RTXSRCDIR)/rtxError.h \
  $(RTXSRCDIR)/rtxFile.h $(RTXSRCDIR)/rtxMemLeakCheck.h \
  $(RTXSRCDIR)/rtxPrintStream.h

clean :
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM) *.pdb
	$(RM) *.map
	$(RM) *.lib
	$(RM) *~
	$(RM) nas_decoder$(EXE)
	$(RM) nas_rwr$(EXE)

