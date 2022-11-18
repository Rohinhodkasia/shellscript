# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = $(JSONCPPHFILES)
OBJECTS = TAP-0311$(OBJ) TAP-0311Enc$(OBJ) TAP-0311Dec$(OBJ)
LIBPATHS = $(LIBDIR)/$(JSONLIBNAME) $(LIBDIR)/$(RTLIBNAME)

writer$(EXE) : writer$(OBJ) print$(OBJ) $(OBJECTS) $(LIBPATHS)
	$(LINK) writer$(OBJ) print$(OBJ) $(OBJECTS) $(LINKOPT) \
	   $(LPATHS) $(JSONLIBS)

reader$(EXE) : reader$(OBJ) print$(OBJ) $(OBJECTS) $(LIBPATHS)
	$(LINK) reader$(OBJ) print$(OBJ) $(OBJECTS) $(LINKOPT) \
	   $(LPATHS) $(JSONLIBS)

writer$(OBJ) : writer.cpp TAP-0311.h $(HFILES)
reader$(OBJ) : reader.cpp TAP-0311.h $(HFILES)
print$(OBJ)  : print.cpp  TAP-0311.h $(HFILES)
TAP-0311$(OBJ) : TAP-0311.cpp TAP-0311.h $(HFILES)
TAP-0311Enc$(OBJ) : TAP-0311Enc.cpp TAP-0311.h $(HFILES)
TAP-0311Dec$(OBJ) : TAP-0311Dec.cpp TAP-0311.h $(HFILES)

TAP-0311.cpp TAP-0311Dec.cpp TAP-0311Enc.cpp TAP-0311.h print.cpp : \
TAP-0311.asn
	$(ASN1C) TAP-0311.asn -c++ -json -print print.cpp

clean :
	$(RM) TAP-0311*.cpp
	$(RM) TAP-0311.h
	$(RM) print.cpp
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.json
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
