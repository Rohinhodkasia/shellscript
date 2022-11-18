# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(RTSRCDIR) $(XMLINC)
LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

HFILES = \
Test.h \
$(RTSRCDIR)/asn1type.h \
$(RTSRCDIR)/asn1CppTypes.h \

ASN1FILE = test.asn

LIBNAMES = $(LIBDIR)/$(RTLIBNAME)

all : writer$(EXE) reader$(EXE)

reader$(EXE) : reader$(OBJ) Test$(OBJ) TestPrint$(OBJ) $(LIBNAMES)
	$(LINK) reader$(OBJ) Test$(OBJ) TestPrint$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(XMLLIBS)

writer$(EXE) : writer$(OBJ) Test$(OBJ) $(LIBNAMES)
	$(LINK) writer$(OBJ) Test$(OBJ) $(LINKOPT) $(LPATHS) $(XMLLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Test.cpp Test.h TestPrint.cpp : $(ASN1FILE) 
	$(ASN1C) $(ASN1FILE) -c++ -xer -trace -print TestPrint.cpp \
	-events -warnings -cfile Test.cpp

depends: Test.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

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


