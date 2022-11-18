# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

OBJECTS = \
Test$(OBJ) \
TestPrint$(OBJ)

all : reader$(EXE) 

HFILES = $(BERCPPHFILES)

reader$(EXE) : reader$(OBJ) Test$(OBJ) TestPrint$(OBJ) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) Test$(OBJ) TestPrint$(OBJ) $(LINKOPT) $(LPATHS) $(BSLIBS)

reader$(OBJ) : reader.cpp Test.h $(HFILES)

Test$(OBJ)  : Test.cpp Test.h $(HFILES)
TestPrint$(OBJ)  : TestPrint.cpp Test.h $(HFILES)

Test.cpp TestPrint.cpp Test.h : Test.asn
	$(ASN1C) Test.asn -c++ -der -trace -print TestPrint.cpp \
	-config Test.cfg -noencode -cfile Test.cpp

clean :
	$(RM) Test*.cpp
	$(RM) Test.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
