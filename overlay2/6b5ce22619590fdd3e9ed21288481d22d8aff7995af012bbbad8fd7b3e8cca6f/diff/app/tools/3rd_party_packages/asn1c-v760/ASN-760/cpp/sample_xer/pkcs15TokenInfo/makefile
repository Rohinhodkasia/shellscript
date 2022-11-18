# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(RTSRCDIR) $(XMLINC)
LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

HFILES = $(RTSRCDIR)/asn1type.h \
$(RTSRCDIR)/asn1CppTypes.h \

ASN1FILE = PKCS15TokenInfo.asn

OBJECTS = PKCS15TokenInfo$(OBJ) PKCS15TokenInfoDec$(OBJ) \
PKCS15TokenInfoEnc$(OBJ)

all : writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(OBJECTS)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(XMLLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) PKCS15TokenInfoPrint$(OBJ) \
$(LIBDIR)/$(XMLLIBNAME) 
	$(LINK) reader$(OBJ) $(OBJECTS) PKCS15TokenInfoPrint$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(XMLLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

PKCS15TokenInfo.cpp PKCS15TokenInfoDec.cpp PKCS15TokenInfoEnc.cpp \
PKCS15TokenInfo.h PKCS15TokenInfoPrint.cpp : \
$(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c++ -xer -trace -print

depends: PKCS15TokenInfo.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) PKCS15TokenInfo*.cpp
	$(RM) PKCS15TokenInfo.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.xml
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
