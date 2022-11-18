# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : reader$(EXE)

ASN1FILE = megaco.asn
HFILES = MEDIA-GATEWAY-CONTROL.h $(PERHFILES)

reader$(EXE) : reader$(OBJ) MEDIA-GATEWAY-CONTROL$(OBJ) print$(OBJ) \
$(LIBDIR)/$(PERLIBNAME)
	$(LINK) reader$(OBJ) MEDIA-GATEWAY-CONTROL$(OBJ) print$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(PSLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

MEDIA-GATEWAY-CONTROL.c MEDIA-GATEWAY-CONTROL.h print.c : $(ASN1FILE) $(ASN1C)
	$(ASN1C) $(ASN1FILE) -c -per -trace -print print.c -cfile MEDIA-GATEWAY-CONTROL.c -noencode -strict-size

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
	$(RM) *.lib
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) rtkey.h
