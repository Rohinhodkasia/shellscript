# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

OBJECTS = \
Test$(OBJ) \
TestPrint$(OBJ)

all : reader$(EXE) 

ASN1FILE = Test.asn
HFILES = $(BERcHFILES)

reader$(EXE) : reader$(OBJ) Test$(OBJ) TestPrint$(OBJ) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) Test$(OBJ) TestPrint$(OBJ) $(LINKOPT) $(LPATHS) $(BSLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Test.c TestPrint.c Test.h : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c -der -trace -print TestPrint.c -config Test.cfg -cfile Test.c -noencode

depends: Test.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) Test*.c
	$(RM) Test.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.lib
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) rtkey.h
