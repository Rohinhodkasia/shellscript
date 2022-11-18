# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = bigInt.asn
HFILES = $(RTSRCDIR)/asn1type.h

writer$(EXE) : writer$(OBJ) BigIntEnc$(OBJ) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) BigIntEnc$(OBJ) $(LINKOPT) $(LPATHS) $(BSLIBS)

reader$(EXE) : reader$(OBJ) print$(OBJ) BigIntDec$(OBJ) $(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) print$(OBJ) BigIntDec$(OBJ) $(LINKOPT) \
	   $(LPATHS) $(BSLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

BigInt.c BigIntEnc.c BigIntDec.c BigInt.h : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c -der -print print.c -config bigInt.cfg

depends: BigInt.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) BigInt*.c
	$(RM) BigInt.h
	$(RM) print.c
	$(RM) *$(OBJ)
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) *.dat
	$(RM) *~
	$(RM) rtkey.h
