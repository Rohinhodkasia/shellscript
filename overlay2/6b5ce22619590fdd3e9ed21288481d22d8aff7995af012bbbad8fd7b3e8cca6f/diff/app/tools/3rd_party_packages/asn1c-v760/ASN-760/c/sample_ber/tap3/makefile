# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = TAP-0311.asn
HFILES = $(RTSRCDIR)/asn1type.h

LIBS = $(LLBER) $(LLRT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_)

writer$(EXE) : writer$(OBJ) print$(OBJ) TAP-0311$(OBJ) TAP-0311Enc$(OBJ) \
$(LIBDIR)/$(BERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
	$(LINK) writer$(OBJ) print$(OBJ) TAP-0311$(OBJ) TAP-0311Enc$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(LIBS)

reader$(EXE) : reader$(OBJ) print$(OBJ) TAP-0311$(OBJ) TAP-0311Dec$(OBJ) \
$(LIBDIR)/$(BERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
	$(LINK) reader$(OBJ) print$(OBJ) TAP-0311$(OBJ) TAP-0311Dec$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(LIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

TAP-0311.c TAP-0311Enc.c TAP-0311Dec.c TAP-0311.h : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -ber -c -stream -print print.c -geninit

depends: TAP-0311.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) TAP-0311*.c
	$(RM) TAP-0311.h
	$(RM) print.c
	$(RM) *$(OBJ)
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM_MSVC_FILES)
	$(RM) *~
	$(RM) rtkey.h
	$(RM) message.dat
	$(RM) messagei.dat
