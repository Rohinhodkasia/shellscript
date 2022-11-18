# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = t38.asn
HFILES = T38.h $(PERHFILES)

writer$(EXE) : writer$(OBJ) T38Enc$(OBJ) T38$(OBJ) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) writer$(OBJ) T38Enc$(OBJ) T38$(OBJ) $(LINKOPT) $(LPATHS) \
	   $(PSLIBS)

reader$(EXE) : reader$(OBJ) T38Dec$(OBJ) T38$(OBJ) print$(OBJ) \
$(LIBDIR)/$(PERLIBNAME)
	$(LINK) reader$(OBJ) T38Dec$(OBJ) print$(OBJ) T38$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(PSLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

T38Enc.c T38Dec.c T38.c T38.h : $(ASN1FILE) $(ASN1C)
	$(ASN1C) $(ASN1FILE) -c -per -trace -print print.c -strict-size -use-enum-types

depends: T38.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) T38*.c
	$(RM) T38.h
	$(RM) print.c
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
