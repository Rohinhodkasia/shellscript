# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(RTSRCDIR) $(XMLINC)
LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

ASN1FILE = t38.asn
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

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

T38.cpp T38Enc.cpp T38Dec.cpp T38.h print.cpp : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c++ -xer -trace -print print.cpp -geninit

depends: T38.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

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


