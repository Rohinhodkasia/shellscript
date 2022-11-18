# makefile to build test program

include ../../../platform.mk

LIBDIR  = ../../../lib
RT3GPPLIBDIR  = ../../$(BLDSUBDIR)/lib
RT3GPPSRCDIR = ../../src
RTXSRCDIR = ../../../../rtxsrc

CFLAGS  = -D_TRACE $(CBLDTYPE_) $(CVARS_) $(MCFLAGS) $(CFLAGS_)
IPATHS  = -I. -I../../../.. -I$(RTXSRCDIR) -I$(RT3GPPSRCDIR)
LINKOPT	= $(LINKOPT_)
LPATHS  = $(LPPFX)$(RT3GPPLIBDIR) $(LPPFX)$(LIBDIR) $(LPATHS_)

all : writer$(EXE) reader$(EXE)

HFILES = $(RT3GPPSRCDIR)/TS24501Msgs.h \
$(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxError.h \
$(RTXSRCDIR)/rtxErrCodes.h $(RTXSRCDIR)/rtxMemory.h

writer$(EXE) : writer$(OBJ) $(RT3GPPLIBDIR)/$(LIBPFX)osys3gpp$(A) \
$(LIBDIR)/$(RTLIBNAME)
	$(LINK) writer$(OBJ) $(LINKOPT) $(LPATHS) $(LLPFX)osys3gpp$(LLAEXT) $(LLASN1RT3GPP) $(LLRT) $(LLSYS)

reader$(EXE) : reader$(OBJ) $(RT3GPPLIBDIR)/$(LIBPFX)osys3gpp$(A) \
$(LIBDIR)/$(RTLIBNAME)
	$(LINK) reader$(OBJ) $(LINKOPT) $(LPATHS) $(LLPFX)osys3gpp$(LLAEXT) $(LLASN1RT3GPP) $(LLRT) $(LLSYS)

writer$(OBJ) : writer.c $(HFILES)
reader$(OBJ) : reader.c $(HFILES)

clean :
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM) *.pdb
	$(RM) *.map
	$(RM) *.lib
	$(RM) *~
	$(RM) *.log
	$(RM) message.dat
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) swriter$(EXE)
	$(RM) sreader$(EXE)
