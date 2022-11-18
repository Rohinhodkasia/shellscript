# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

OBJECTS = \
Test$(OBJ) \
TestPrint$(OBJ)

all : reader$(EXE) 

ASN1FILE = Test.asn
HFILES = $(BERCPPHFILES)

reader$(EXE) : reader$(OBJ) Test$(OBJ) TestPrint$(OBJ) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) Test$(OBJ) TestPrint$(OBJ) $(LINKOPT) $(LPATHS) \
	    $(BSLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Test.cpp TestPrint.cpp Test.h : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c++ -der -trace -print TestPrint.cpp \
	-config Test.cfg -noencode -cfile Test.cpp

depends: Test.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

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
