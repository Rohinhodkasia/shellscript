# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(RTSRCDIR) \
$(XMLINC) $(XMLDEFS) 

LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

HFILES = $(RTSRCDIR)/asn1type.h

ASN1FILE = bigInt.asn

all : writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) BigIntEnc$(OBJ)
	$(LINK) writer$(OBJ) BigIntEnc$(OBJ) $(LINKOPT) $(LPATHS) $(XMLLIBS)

reader$(EXE) : reader$(OBJ) print$(OBJ) BigIntDec$(OBJ) 
	$(LINK) reader$(OBJ) print$(OBJ) BigIntDec$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(XMLLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

BigIntEnc.c BigIntDec.c BigInt.h : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c -xer -print print.c -config bigInt.cfg

depends: BigIntEnc.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) BigInt*.c
	$(RM) BigInt.h
	$(RM) print.c
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.xml
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
