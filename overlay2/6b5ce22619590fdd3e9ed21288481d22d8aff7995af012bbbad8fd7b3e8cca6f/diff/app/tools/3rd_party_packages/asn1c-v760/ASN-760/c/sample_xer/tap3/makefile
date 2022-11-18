# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : reader$(EXE) writer$(EXE)

ASN1FILE = tap3.asn
HFILES = $(RTSRCDIR)/asn1type.h

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(RTSRCDIR) \
$(XMLINC) $(XMLDEFS)
LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)
LIBNAMES = $(LIBDIR)/$(RTLIBNAME) 

writer$(EXE) : writer$(OBJ) print$(OBJ) TAP-0311Enc$(OBJ) TAP-0311$(OBJ) \
$(LIBNAMES)
	$(LINK) writer$(OBJ) print$(OBJ) TAP-0311Enc$(OBJ) TAP-0311$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(XMLLIBS)

reader$(EXE) : reader$(OBJ) print$(OBJ) TAP-0311Dec$(OBJ) TAP-0311$(OBJ) \
$(LIBNAMES)
	$(LINK) reader$(OBJ) print$(OBJ) TAP-0311Dec$(OBJ) TAP-0311$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(XMLLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

TAP-0311Dec.c TAP-0311Enc.c TAP-0311.c TAP-0311.h print.c : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c -xer -print print.c

depends: TAP-0311.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) TAP-0311*.c
	$(RM) TAP-0311.h
	$(RM) print.c
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.xml
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
