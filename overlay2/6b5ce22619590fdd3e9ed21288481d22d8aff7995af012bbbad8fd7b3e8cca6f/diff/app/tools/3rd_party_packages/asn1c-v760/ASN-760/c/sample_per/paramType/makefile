# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = param.asn
HFILES = ParamType.h $(PERHFILES)

writer$(EXE) : writer$(OBJ) print$(OBJ) ParamType$(OBJ) ParamTypeEnc$(OBJ) \
$(LIBDIR)/$(PERLIBNAME)
	$(LINK) writer$(OBJ) print$(OBJ) ParamType$(OBJ) ParamTypeEnc$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) print$(OBJ) ParamType$(OBJ) ParamTypeDec$(OBJ) \
$(LIBDIR)/$(PERLIBNAME)
	$(LINK) reader$(OBJ) print$(OBJ) ParamType$(OBJ) ParamTypeDec$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(PSLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

ParamType.c ParamTypeEnc.c ParamTypeDec.c ParamType.h print.c : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c -per -trace -print print.c

depends: ParamType.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) ParamType*.c
	$(RM) ParamType.h
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


