# common makefile defs for all sample programs

OSROOTDIR = ../../..
LIBDIR  = ../../lib
LIBDIRCOMPACT  = ../../lib_compact
RTSRCDIR = ../../../rtsrc
RTXSRCDIR = ../../../rtxsrc
BERSRCDIR = ../../../rtbersrc
JSONSRCDIR = ../../../rtjsonsrc
PERSRCDIR = ../../../rtpersrc
XMLSRCDIR = ../../../rtxmlsrc
SPECSDIR = ../../../specs

BERHFILES = $(RTSRCDIR)/asn1type.h $(BERSRCDIR)/asn1ber.h
BERCPPHFILES = \
$(BERHFILES) $(RTSRCDIR)/asn1CppTypes.h $(BERSRCDIR)/asn1BerCppTypes.h
PERHFILES = $(RTSRCDIR)/asn1type.h $(PERSRCDIR)/asn1per.h
PERCPPHFILES = \
$(PERHFILES) $(RTSRCDIR)/asn1CppTypes.h $(PERSRCDIR)/asn1PerCppTypes.h

ASN1C	= ..$(PS)..$(PS)..$(PS)bin$(PS)asn1c$(EXE)
BER2INDEF = ..$(PS)..$(PS)..$(PS)bin$(PS)ber2indef
COMFLAGS = -D_TRACE $(CBLDTYPE_) $(CVARSMTD_) $(MCFLAGS) 
CFLAGS	= $(COMFLAGS) $(CFLAGS_) -DCPP
CCFLAGS = $(COMFLAGS) $(CCFLAGS_) $(XMLDEFS)
RTCFLAGS = $(CFLAGS)
BERCFLAGS = $(CFLAGS)
PERCFLAGS = $(CFLAGS)
RTCPPFLAGS = $(CCFLAGS)
BERCCFLAGS = $(CCFLAGS)
JSONCCFLAGS = $(CCFLAGS)
PERCCFLAGS = $(CCFLAGS)
IPATHS = \
-I. -I$(RTSRCDIR) -I$(RTXSRCDIR) -I$(BERSRCDIR) -I$(PERSRCDIR) \
-I$(OSROOTDIR) $(IPATHS_)
LINKOPT	= $(LINKOPT_)
LPATHS    = $(LPPFX)$(LIBDIR) $(LPATHS_)
LDPATHS   = $(LPPFX)$(LIBDDIR) $(LPATHS_) 
LDLLPATHS = $(LPPFX)$(DLLDIR) $(LPATHS_)
BSLIBS  = $(LLBER) $(LLRT) $(LLSYS) 
PSLIBS  = $(LLPER) $(LLRT) $(LLSYS) 
XMLLIBS = $(LLXML) $(LLRT) $(LLSYS) 
JSONLIBS = $(LLJSON) $(LLRT) $(LLSYS)
