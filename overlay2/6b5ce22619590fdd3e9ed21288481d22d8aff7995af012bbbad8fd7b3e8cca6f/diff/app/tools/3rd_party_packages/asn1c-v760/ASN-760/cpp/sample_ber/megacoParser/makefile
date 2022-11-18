# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : reader$(EXE)

ASN1FILE = megaco.asn
HFILES = $(BERCPPHFILES)

reader$(EXE) : reader$(OBJ) MEDIA-GATEWAY-CONTROL$(OBJ) printHandler$(OBJ) \
$(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) MEDIA-GATEWAY-CONTROL$(OBJ) printHandler$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(BSLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

MEDIA-GATEWAY-CONTROL.cpp MEDIA-GATEWAY-CONTROL.h print.cpp : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c++ -ber -events -notypes -x64 -cfile MEDIA-GATEWAY-CONTROL.cpp

depends: MEDIA-GATEWAY-CONTROL.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) MEDIA-GATEWAY-CONTROL.cpp
	$(RM) MEDIA-GATEWAY-CONTROL.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.lib
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) rtkey.h
