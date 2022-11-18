# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(RTSRCDIR) \
$(XMLINC) $(XMLDEFS)

LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

HFILES = $(RTSRCDIR)/asn1type.h \

ASN1FILE = test.asn

all : writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) Test$(OBJ) TestEnc$(OBJ)
	$(LINK) writer$(OBJ) Test$(OBJ) TestEnc$(OBJ) \
	   $(LINKOPT) $(LINKDBG_) $(LPATHS) $(XMLLIBS)

reader$(EXE) : reader$(OBJ) Test$(OBJ) TestDec$(OBJ) TestPrint$(OBJ) \
$(LIBDIR)/$(XMLLIBNAME)
	$(LINK) reader$(OBJ) Test$(OBJ) TestDec$(OBJ) TestPrint$(OBJ) \
	   $(LINKOPT) $(LINKDBG_) $(LPATHS) $(XMLLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Test.c TestDec.c TestEnc.c Test.h TestPrint.c Test.xsd : $(ASN1FILE) $(ASN1C)
	$(ASN1C) $(ASN1FILE) -c -xer -xsd -trace -print -geninit -config bigInt.cfg

depends: Test.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) Test.xsd
	$(RM) Test*.c
	$(RM) TestPrint.c
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


