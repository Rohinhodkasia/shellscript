# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = PKCS15TokenInfo.asn
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

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

PKCS15TokenInfo.cpp PKCS15TokenInfoEnc.cpp \
PKCS15TokenInfoDec.cpp PKCS15TokenInfo.h PKCS15TokenInfoPrint.cpp : \
$(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c++ -der -print -geninit

depends: PKCS15TokenInfo.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

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
