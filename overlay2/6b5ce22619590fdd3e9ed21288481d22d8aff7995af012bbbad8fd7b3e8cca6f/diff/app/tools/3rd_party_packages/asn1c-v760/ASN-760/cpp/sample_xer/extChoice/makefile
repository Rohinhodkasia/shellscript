# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(RTSRCDIR) $(XMLINC)
LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

HFILES = $(RTSRCDIR)/asn1type.h \
$(RTSRCDIR)/asn1CppTypes.h \

ASN1FILE = extChoice.asn

OBJECTS = ExtChoice$(OBJ) ExtChoiceEnc$(OBJ) ExtChoiceDec$(OBJ) print$(OBJ)

all : writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(OBJECTS)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(XMLLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS)
	$(LINK) reader$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(XMLLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

ExtChoice.cpp ExtChoiceEnc.cpp ExtChoiceDec.cpp ExtChoice.h \
print.cpp : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c++ -xer -trace -print print.cpp

depends: ExtChoice.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) ExtChoice*.cpp
	$(RM) ExtChoice.h
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




