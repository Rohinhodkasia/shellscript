# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(RTSRCDIR) $(XMLINC)
LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

HFILES = \
Test.h \
$(RTSRCDIR)/asn1type.h \
$(RTSRCDIR)/asn1CppTypes.h \



LIBNAMES = $(LIBDIR)/$(RTLIBNAME)

all : writer$(EXE) reader$(EXE)

reader$(EXE) : reader$(OBJ) Test$(OBJ) TestPrint$(OBJ) $(LIBNAMES)
	$(LINK) reader$(OBJ) Test$(OBJ) TestPrint$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(XMLLIBS)

writer$(EXE) : writer$(OBJ) Test$(OBJ) $(LIBNAMES)
	$(LINK) writer$(OBJ) Test$(OBJ) $(LINKOPT) $(LPATHS) $(XMLLIBS)

reader$(OBJ) : reader.cpp $(HFILES)
writer$(OBJ) : writer.cpp $(HFILES)
Test$(OBJ)   : Test.cpp $(HFILES)

Test.cpp Test.h TestPrint.cpp : test.asn 
	$(ASN1C) test.asn -c++ -xer -trace -print TestPrint.cpp \
	-events -warnings -cfile Test.cpp

clean :
	$(RM) Test*.cpp
	$(RM) Test.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.xml
	$(RM) *.lib
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM) rtkey.h


