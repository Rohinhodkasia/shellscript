# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = TAP-0311.asn
HFILES = $(BERCPPHFILES)
OBJECTS = TAP-0311$(OBJ) TAP-0311Enc$(OBJ) TAP-0311Dec$(OBJ)
LIBPATHS = $(LIBDIR)/$(BERLIBNAME) $(LIBDIR)/$(RTLIBNAME)

writer$(EXE) : writer$(OBJ) print$(OBJ) $(OBJECTS) $(LIBPATHS)
	$(LINK) writer$(OBJ) print$(OBJ) $(OBJECTS) $(LINKOPT) \
	   $(LPATHS) $(BSLIBS)

reader$(EXE) : reader$(OBJ) print$(OBJ) $(OBJECTS) $(LIBPATHS)
	$(LINK) reader$(OBJ) print$(OBJ) $(OBJECTS) $(LINKOPT) \
	   $(LPATHS) $(BSLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

TAP-0311.cpp TAP-0311Dec.cpp TAP-0311Enc.cpp TAP-0311.h print.cpp : \
$(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c++ -ber -print print.cpp

depends: TAP-0311.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) TAP-0311*.cpp
	$(RM) TAP-0311.h
	$(RM) print.cpp
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
