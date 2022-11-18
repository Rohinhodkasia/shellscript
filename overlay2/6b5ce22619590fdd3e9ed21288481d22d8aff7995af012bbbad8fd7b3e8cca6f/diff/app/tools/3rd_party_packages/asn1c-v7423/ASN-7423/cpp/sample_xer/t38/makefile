# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(RTSRCDIR) $(XMLINC)
LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

HFILES = \
$(RTSRCDIR)/asn1type.h \
$(RTSRCDIR)/asn1CppTypes.h 

OBJECTS = T38$(OBJ) T38Enc$(OBJ) T38Dec$(OBJ)

all : writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(OBJECTS)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(XMLLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) print$(OBJ) 
	$(LINK) reader$(OBJ) $(OBJECTS) print$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(XMLLIBS)

writer$(OBJ) : writer.cpp T38.h $(HFILES)
reader$(OBJ) : reader.cpp T38.h $(HFILES)
print$(OBJ)  : print.cpp T38.h $(HFILES)

T38$(OBJ) : T38.cpp T38.h $(HFILES)
T38Enc$(OBJ) : T38Enc.cpp T38.h $(HFILES)
T38Dec$(OBJ) : T38Dec.cpp T38.h $(HFILES)

T38.cpp T38Enc.cpp T38Dec.cpp T38.h print.cpp : t38.asn
	$(ASN1C) t38.asn -c++ -xer -trace -print print.cpp -geninit

clean :
	$(RM) T38*.cpp
	$(RM) T38.h
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


