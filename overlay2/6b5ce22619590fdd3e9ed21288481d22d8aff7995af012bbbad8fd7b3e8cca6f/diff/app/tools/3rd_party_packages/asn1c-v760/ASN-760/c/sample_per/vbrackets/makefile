# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = vbrackets.asn
HFILES = VersionBrackets.h $(PERHFILES)

writer$(EXE) : writer$(OBJ) VersionBracketsEnc$(OBJ) print$(OBJ) \
$(LIBDIR)/$(PERLIBNAME)
	$(LINK) writer$(OBJ) VersionBracketsEnc$(OBJ) print$(OBJ) $(LINKOPT) \
	   $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) VersionBracketsDec$(OBJ) print$(OBJ) \
$(LIBDIR)/$(PERLIBNAME)
	$(LINK) reader$(OBJ) VersionBracketsDec$(OBJ) print$(OBJ) $(LINKOPT) \
	   $(LPATHS) $(PSLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

VersionBrackets.c VersionBracketsEnc.c VersionBracketsDec.c VersionBrackets.h \
print.c : $(ASN1FILE) $(ASN1C)
	$(ASN1C) $(ASN1FILE) -c -per -trace -print print.c

depends: VersionBrackets.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) VersionBrackets*.c
	$(RM) VersionBrackets.h
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


