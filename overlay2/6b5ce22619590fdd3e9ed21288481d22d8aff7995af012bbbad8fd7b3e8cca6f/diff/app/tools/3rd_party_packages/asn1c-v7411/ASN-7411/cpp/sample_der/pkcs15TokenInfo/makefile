# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

OBJECTS = PKCS15TokenInfo$(OBJ) PKCS15TokenInfoEnc$(OBJ) \
PKCS15TokenInfoDec$(OBJ) PKCS15TokenInfoPrint$(OBJ)
HFILES  = $(BERCPPHFILES)

all : $(OBJECTS) writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBDIR)/$(BERLIBNAME) \
$(LIBDIR)/$(RTLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(BSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(LIBDIR)/$(BERLIBNAME) \
$(LIBDIR)/$(RTLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(BSLIBS)

writer$(OBJ) : writer.cpp PKCS15TokenInfo.h $(HFILES)
reader$(OBJ) : reader.cpp PKCS15TokenInfo.h $(HFILES)
PKCS15TokenInfo$(OBJ) : PKCS15TokenInfo.cpp PKCS15TokenInfo.h
PKCS15TokenInfoEnc$(OBJ) : PKCS15TokenInfoEnc.cpp PKCS15TokenInfo.h
PKCS15TokenInfoDec$(OBJ) : PKCS15TokenInfoDec.cpp PKCS15TokenInfo.h
PKCS15TokenInfoPrint$(OBJ) : PKCS15TokenInfoPrint.cpp PKCS15TokenInfo.h

PKCS15TokenInfo.cpp PKCS15TokenInfoEnc.cpp \
PKCS15TokenInfoDec.cpp PKCS15TokenInfo.h PKCS15TokenInfoPrint.cpp : \
PKCS15TokenInfo.asn
	$(ASN1C) PKCS15TokenInfo.asn -c++ -der -print -geninit

clean:
	$(RM) PKCS*.h
	$(RM) PKCS*.cpp
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
