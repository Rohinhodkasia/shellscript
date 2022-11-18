# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(XERSRCDIR) -I$(XMLSRCDIR) \
-I$(RTSRCDIR) $(XMLINC) 

LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

ASN1FILE = bigInt.asn
HFILES = $(RTSRCDIR)/asn1type.h \
$(RTSRCDIR)/asn1intl.h \
$(RTSRCDIR)/asn1CppTypes.h \
$(XMLSRCDIR)/asn1xml.h \
$(RTXSRCDIR)/rtxCommon.h

OBJECTS = BigInt$(OBJ) BigIntEnc$(OBJ) BigIntDec$(OBJ)

all : writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(OBJECTS) \
$(LIBDIR)/$(RTLIBNAME) 
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(XMLLIBS)

reader$(EXE) : reader$(OBJ) print$(OBJ) $(OBJECTS) \
$(LIBDIR)/$(RTLIBNAME) 
	$(LINK) reader$(OBJ) print$(OBJ) $(OBJECTS) \
	   $(LINKOPT) $(LPATHS) $(XMLLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

BigInt.cpp BigIntDec.cpp BigIntEnc.cpp BigInt.h BigInt.xsd print.cpp : \
$(ASN1FILE) bigInt.cfg
	$(ASN1C) $(ASN1FILE) -c++ -xml -xsd -print print.cpp -config bigInt.cfg

depends: BigInt.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) BigInt*.cpp
	$(RM) BigInt.h
	$(RM) BigInt.xsd
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


