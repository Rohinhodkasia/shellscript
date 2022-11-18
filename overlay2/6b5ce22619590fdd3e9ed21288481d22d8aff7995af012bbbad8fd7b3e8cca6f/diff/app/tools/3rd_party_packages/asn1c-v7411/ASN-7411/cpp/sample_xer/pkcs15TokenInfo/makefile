# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(RTSRCDIR) $(XMLINC)
LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

HFILES = $(RTSRCDIR)/asn1type.h \
$(RTSRCDIR)/asn1CppTypes.h \



OBJECTS = PKCS15TokenInfo$(OBJ) PKCS15TokenInfoDec$(OBJ) PKCS15TokenInfoEnc$(OBJ)

all : writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(OBJECTS)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(XMLLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) PKCS15TokenInfoPrint$(OBJ) \
$(LIBDIR)/$(XMLLIBNAME) 
	$(LINK) reader$(OBJ) $(OBJECTS) PKCS15TokenInfoPrint$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(XMLLIBS)

writer$(OBJ) : writer.cpp PKCS15TokenInfo.h $(HFILES)
reader$(OBJ) : reader.cpp PKCS15TokenInfo.h $(HFILES)

PKCS15TokenInfo$(OBJ) : PKCS15TokenInfo.cpp PKCS15TokenInfo.h $(HFILES)
PKCS15TokenInfoDec$(OBJ) : PKCS15TokenInfoDec.cpp PKCS15TokenInfo.h $(HFILES)
PKCS15TokenInfoEnc$(OBJ) : PKCS15TokenInfoEnc.cpp PKCS15TokenInfo.h $(HFILES)
PKCS15TokenInfoPrint$(OBJ) : \
PKCS15TokenInfoPrint.cpp PKCS15TokenInfo.h $(HFILES)

PKCS15TokenInfo.cpp PKCS15TokenInfoDec.cpp PKCS15TokenInfoEnc.cpp \
PKCS15TokenInfo.h PKCS15TokenInfoPrint.cpp : \
PKCS15TokenInfo.asn
	$(ASN1C) PKCS15TokenInfo.asn -c++ -xer -trace -print

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
