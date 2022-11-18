# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(RTSRCDIR) $(XMLINC) $(XMLDEFS)
LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

HFILES = $(RTSRCDIR)/asn1type.h \

ASN1FILE = PKCS15TokenInfo.asn

all : reader$(EXE) writer$(EXE) 

writer$(EXE) : writer$(OBJ) PKCS15TokenInfoEnc$(OBJ) PKCS15TokenInfo$(OBJ) \
$(LIBDIR)/$(XMLLIBNAME) 
	$(LINK) writer$(OBJ) PKCS15TokenInfo$(OBJ) PKCS15TokenInfoEnc$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(XMLLIBS)

reader$(EXE) : reader$(OBJ) PKCS15TokenInfoDec$(OBJ) PKCS15TokenInfo$(OBJ) \
PKCS15TokenInfoPrint$(OBJ)
	$(LINK) reader$(OBJ) PKCS15TokenInfoDec$(OBJ) PKCS15TokenInfo$(OBJ) \
	   PKCS15TokenInfoPrint$(OBJ) $(LINKOPT) $(LPATHS) $(XMLLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

PKCS15TokenInfoDec.c PKCS15TokenInfoEnc.c PKCS15TokenInfo.h PKCS15TokenInfo.c \
PKCS15TokenInfoPrint.c : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c -xer -strict-size -trace -print

depends: PKCS15TokenInfo.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) PKCS15TokenInfo*.c
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
