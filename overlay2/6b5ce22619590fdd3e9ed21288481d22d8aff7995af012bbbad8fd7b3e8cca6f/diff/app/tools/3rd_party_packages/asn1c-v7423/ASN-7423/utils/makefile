# makefile to build test program

include ../platform.mk

all : ../bin/berfdump$(EXE)  ../bin/ber2indef$(EXE) \
../bin/ber2def$(EXE) ../bin/dumpasn1$(EXE) ../bin/dumppcap$(EXE) \
../bin/dumppcapng$(EXE) ../bin/hexdump$(EXE)

OSROOTDIR = ..
CFLAGS  = $(CFLAGS_) $(CVARS_) 
HFILES  = ../rtbersrc/asn1ber.h ../rtsrc/asn1type.h ../rtsrc/asn1intl.h
IPATHS  = -I. -I.. -I../rtsrc -I../rtbersrc $(IPATHS_)
LINKOPT	= $(LINKOPT_)
RTCLIBDIR = ../c$(RTDIRSFX)/lib

RTCPPLIBDIR = ../cpp$(RTDIRSFX)/lib_opt

LPATHS  = $(LPPFX)$(RTCLIBDIR) $(LPATHS_)

../bin/berfdump$(EXE) : berfdump$(OBJ) $(RTCLIBDIR)/$(BERLIBNAME)
	$(CC) berfdump$(OBJ) $(LINKOPT) $(LPATHS) $(LLBER) $(LLRT) $(LLSYS)

../bin/ber2indef$(EXE) : ber2indef$(OBJ) $(RTCLIBDIR)/$(BERLIBNAME) \
$(RTCLIBDIR)/$(RTLIBNAME)
	$(CC) ber2indef$(OBJ) $(LINKOPT) $(LPATHS) $(LLBER) $(LLRT) $(LLSYS)

../bin/ber2def$(EXE) : ber2def$(OBJ) $(RTCLIBDIR)/$(BERLIBNAME) \
$(RTCLIBDIR)/$(RTLIBNAME)
	$(CC) ber2def$(OBJ) $(LINKOPT) $(LPATHS) $(LLBER) $(LLRT) $(LLSYS)

../bin/dumpasn1$(EXE) : dumpasn1$(OBJ)
	$(CC) dumpasn1$(OBJ) $(LINKOPT) $(LLSYS)

../bin/dumppcap$(EXE) : dumppcap$(OBJ)
	$(CC) dumppcap$(OBJ) $(LINKOPT) $(LPATHS) $(LLRT) $(LLSYS)

../bin/dumppcapng$(EXE) : dumppcapng$(OBJ)
	$(CC) dumppcapng$(OBJ) $(LINKOPT) $(LPATHS) $(LLRT) $(LLSYS)

../bin/hexdump$(EXE) : hexdump$(OBJ)
	$(CC) hexdump$(OBJ) $(LINKOPT) $(LPATHS) $(LLSYS)

berfdump$(OBJ)  : berfdump.c $(HFILES)
ber2indef$(OBJ) : ber2indef.c $(HFILES)
ber2def$(OBJ)   : ber2def.c $(HFILES)
dumpasn1$(OBJ)  : dumpasn1.c
dumppcap$(OBJ)  : dumppcap.c
dumppcapng$(OBJ)  : dumppcapng.c
hexdump$(OBJ)   : hexdump.c

clean :
	$(RM) ..$(PS)bin$(PS)berfdump*
	$(RM) ..$(PS)bin$(PS)ber2indef*
	$(RM) ..$(PS)bin$(PS)ber2def*
	$(RM) ..$(PS)bin$(PS)dumpasn1*
	$(RM) ..$(PS)bin$(PS)dumppcap*
	$(RM) ..$(PS)bin$(PS)hexdump*
	$(RM) *$(OBJ)
	$(RM) *~
