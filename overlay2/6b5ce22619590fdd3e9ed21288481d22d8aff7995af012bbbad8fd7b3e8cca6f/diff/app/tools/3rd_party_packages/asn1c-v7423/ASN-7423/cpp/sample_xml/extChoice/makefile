# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(XERSRCDIR) -I$(XMLSRCDIR) \
-I$(RTSRCDIR) $(XMLINC) 

LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

HFILES = $(RTSRCDIR)/asn1type.h \
$(RTSRCDIR)/asn1intl.h \
$(RTSRCDIR)/asn1CppTypes.h \
$(XMLSRCDIR)/asn1xml.h \
$(RTXSRCDIR)/rtxCommon.h

OBJECTS = ExtChoice$(OBJ) ExtChoiceEnc$(OBJ) ExtChoiceDec$(OBJ) print$(OBJ)

all : writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(OBJECTS) \
$(LIBDIR)/$(RTLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(XMLLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) \
$(LIBDIR)/$(RTLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(XMLLIBS)

writer$(OBJ) : writer.cpp ExtChoice.h $(HFILES)
reader$(OBJ) : reader.cpp ExtChoice.h $(HFILES)
print$(OBJ)  : print.cpp  $(HFILES)
ExtChoice$(OBJ) : ExtChoice.cpp $(HFILES)
ExtChoiceEnc$(OBJ) : ExtChoiceEnc.cpp $(HFILES)
ExtChoiceDec$(OBJ) : ExtChoiceDec.cpp $(HFILES)

ExtChoice.cpp ExtChoiceEnc.cpp ExtChoiceDec.cpp ExtChoice.h ExtChoice.xsd \
print.cpp : extChoice.asn
	$(ASN1C) extChoice.asn -c++ -xml -xsd -trace -print print.cpp -noxmlns

clean :
	$(RM) ExtChoice*.cpp
	$(RM) ExtChoice.h
	$(RM) ExtChoice.xsd
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




