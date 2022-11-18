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

OBJECTS = BigInt$(OBJ) BigIntEnc$(OBJ) BigIntDec$(OBJ)

all : writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(OBJECTS) \
$(LIBDIR)/$(RTLIBNAME) 
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(XMLLIBS)

reader$(EXE) : reader$(OBJ) print$(OBJ) $(OBJECTS) \
$(LIBDIR)/$(RTLIBNAME) 
	$(LINK) reader$(OBJ) print$(OBJ) $(OBJECTS) \
	   $(LINKOPT) $(LPATHS) $(XMLLIBS)

writer$(OBJ) : writer.cpp BigInt.h $(HFILES)
reader$(OBJ) : reader.cpp BigInt.h $(HFILES)
print$(OBJ)  : print.cpp BigInt.h $(HFILES)

BigInt$(OBJ)  : BigInt.cpp BigInt.h $(HFILES)
BigIntDec$(OBJ)  : BigIntDec.cpp BigInt.h $(HFILES)
BigIntEnc$(OBJ)  : BigIntEnc.cpp BigInt.h $(HFILES)

BigInt.cpp BigIntDec.cpp BigIntEnc.cpp BigInt.h BigInt.xsd print.cpp : \
bigInt.asn bigInt.cfg
	$(ASN1C) bigInt.asn -c++ -xml -xsd -print print.cpp -config bigInt.cfg

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


