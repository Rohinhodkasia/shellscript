# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : reader$(EXE)

HFILES = $(BERCPPHFILES)

reader$(EXE) : reader$(OBJ) MEDIA-GATEWAY-CONTROL$(OBJ) printHandler$(OBJ) \
$(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) MEDIA-GATEWAY-CONTROL$(OBJ) printHandler$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(BSLIBS)

reader$(OBJ) : reader.cpp MEDIA-GATEWAY-CONTROL.h $(HFILES)
printHandler$(OBJ) : printHandler.cpp printHandler.h $(HFILES)

MEDIA-GATEWAY-CONTROL$(OBJ) : \
MEDIA-GATEWAY-CONTROL.cpp MEDIA-GATEWAY-CONTROL.h $(HFILES)

MEDIA-GATEWAY-CONTROL.cpp MEDIA-GATEWAY-CONTROL.h print.cpp : megaco.asn
	$(ASN1C) megaco.asn -c++ -ber -events -notypes -x64 -cfile MEDIA-GATEWAY-CONTROL.cpp

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
