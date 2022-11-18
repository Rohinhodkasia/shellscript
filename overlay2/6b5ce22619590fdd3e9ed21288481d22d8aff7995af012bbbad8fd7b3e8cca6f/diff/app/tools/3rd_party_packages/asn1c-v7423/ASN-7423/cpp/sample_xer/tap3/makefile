# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = \
$(RTSRCDIR)/asn1type.h \
$(RTSRCDIR)/asn1CppTypes.h

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(XERSRCDIR) -I$(RTSRCDIR) $(XMLINC)
LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)
LIBNAMES = $(LIBDIR)/$(RTLIBNAME)

OBJECTS = print$(OBJ) TAP-0302$(OBJ) TAP-0302Enc$(OBJ) TAP-0302Dec$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBNAMES)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(XMLLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(LIBNAMES)
	$(LINK) reader$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(XMLLIBS)

writer$(OBJ) : writer.cpp TAP-0302.h $(HFILES)
reader$(OBJ) : reader.cpp TAP-0302.h $(HFILES)
print$(OBJ)  : print.cpp  TAP-0302.h $(HFILES)
TAP-0302$(OBJ) : TAP-0302.cpp TAP-0302.h $(HFILES)
TAP-0302Enc$(OBJ) : TAP-0302Enc.cpp TAP-0302.h $(HFILES)
TAP-0302Dec$(OBJ) : TAP-0302Dec.cpp TAP-0302.h $(HFILES)

TAP-0302.cpp TAP-0302Enc.cpp TAP-0302Dec.cpp TAP-0302.h print.cpp : tap3.asn
	$(ASN1C) tap3.asn -c++ -xer -print print.cpp

clean :
	$(RM) TAP-0302*.cpp
	$(RM) TAP-0302.h
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
