# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = tap3.asn
HFILES = \
$(RTSRCDIR)/asn1type.h \
$(RTSRCDIR)/asn1CppTypes.h

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(XERSRCDIR) -I$(RTSRCDIR) $(XMLINC)
LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_)
LIBNAMES = $(LIBDIR)/$(RTLIBNAME)
OBJECTS = print$(OBJ) TAP-0310$(OBJ) TAP-0310Enc$(OBJ) TAP-0310Dec$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBNAMES)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(XMLLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(LIBNAMES)
	$(LINK) reader$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(XMLLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

TAP-0310.cpp TAP-0310Enc.cpp TAP-0310Dec.cpp TAP-0310.h print.cpp : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c++ -xml -xsd -print print.cpp

runtest : writer$(EXE) reader$(EXE)
	.$(PS)writer
	java -cp ../../../java/util/Val Val message.xml *.xsd
	.$(PS)reader

depends: TAP-0310.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) TAP-0310*.cpp
	$(RM) TAP-0310.h
	$(RM) TAP-0310.xsd
	$(RM) print.cpp
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.xml
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
