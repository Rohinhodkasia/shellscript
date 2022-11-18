# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(XERSRCDIR) -I$(XMLSRCDIR) \
-I$(RTSRCDIR) $(XMLINC) 

LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

ASN1FILE = test.asn
HFILES = $(RTSRCDIR)/asn1type.h \
$(RTSRCDIR)/asn1intl.h \
$(RTSRCDIR)/asn1CppTypes.h \
$(XMLSRCDIR)/asn1xml.h \
$(RTXSRCDIR)/rtxCommon.h

OBJECTS = Test$(OBJ) TestDec$(OBJ) TestEnc$(OBJ)

all : writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(OBJECTS) \
$(LIBDIR)/$(RTLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(XMLLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) TestPrint$(OBJ) \
$(LIBDIR)/$(RTLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) TestPrint$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(XMLLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Test.cpp TestDec.cpp TestEnc.cpp Test.h Test.xsd TestPrint.cpp : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c++ -xml -xsd -trace -print

depends: Test.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) Test*.cpp
	$(RM) Test.h
	$(RM) Test.xsd
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.xml
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h


