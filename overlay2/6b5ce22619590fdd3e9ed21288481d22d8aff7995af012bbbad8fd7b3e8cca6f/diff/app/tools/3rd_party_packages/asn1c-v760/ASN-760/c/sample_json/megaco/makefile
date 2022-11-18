# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : reader$(EXE)

ASN1FILE = megaco.asn
HFILES = $(RTSRCDIR)$(PS)asn1type.h \
$(RTSRCDIR)$(PS)rtContext.h \
$(RTXSRCDIR)$(PS)rtxContext.h \
$(JSONSRCDIR)$(PS)asn1json.h \
$(BERSRCDIR)$(PS)asn1ber.h

LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_)

reader$(EXE) : reader$(OBJ) MEDIA-GATEWAY-CONTROL$(OBJ) print$(OBJ) \
..$(PS)..$(PS)lib$(PS)$(BERLIBNAME) ..$(PS)..$(PS)lib$(PS)$(RTLIBNAME)
	$(LINK) reader$(OBJ) MEDIA-GATEWAY-CONTROL$(OBJ) print$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(LLJSON) $(LLBER) $(LLRT) $(LLSYS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

MEDIA-GATEWAY-CONTROL.c MEDIA-GATEWAY-CONTROL.h print.c : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c -ber -json -trace -print print.c -cfile MEDIA-GATEWAY-CONTROL.c -use-enum-types

depends: MEDIA-GATEWAY-CONTROL.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) MEDIA-GATEWAY-CONTROL.c
	$(RM) MEDIA-GATEWAY-CONTROL.h
	$(RM) print.c
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.json
	$(RM) *.lib
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) rtkey.h
