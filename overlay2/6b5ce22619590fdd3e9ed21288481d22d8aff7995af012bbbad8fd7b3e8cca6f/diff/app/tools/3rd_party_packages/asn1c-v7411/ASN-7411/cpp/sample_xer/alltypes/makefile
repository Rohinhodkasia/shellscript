# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(RTSRCDIR) $(XMLINC) $(XMLDEFS)
LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

HFILES = $(RTSRCDIR)/asn1type.h \
$(RTSRCDIR)/asn1CppTypes.h \



OBJECTS = Test$(OBJ) TestDec$(OBJ) TestEnc$(OBJ)

all : writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBDIR)/$(RTLIBNAME) \
$(LIBDIR)/$(XMLLIBNAME)
	$(LINK) writer$(OBJ) $(OBJECTS) \
	   $(LINKOPT) $(LPATHS) $(XMLLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) TestPrint$(OBJ) \
$(LIBDIR)/$(RTLIBNAME)
	$(LINK) reader$(OBJ) $(OBJECTS) TestPrint$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(XMLLIBS)

writer$(OBJ) : writer.cpp Test.h $(HFILES)
reader$(OBJ) : reader.cpp Test.h $(HFILES)

Test$(OBJ) : Test.cpp Test.h $(HFILES)
TestDec$(OBJ) : TestDec.cpp Test.h $(HFILES)
TestEnc$(OBJ) : TestEnc.cpp Test.h $(HFILES)
TestPrint$(OBJ) : TestPrint.cpp Test.h $(HFILES)

Test.cpp TestDec.cpp TestEnc.cpp Test.h TestPrint.cpp : test.asn
	$(ASN1C) test.asn -c++ -xer -trace -print

clean :
	$(RM) Test*.cpp
	$(RM) Test.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.xml
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h


