# makefile to build the extChoice sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = extChoice.asn
HFILES = ExtChoice.h $(PERHFILES)

writer$(EXE) : writer$(OBJ) ExtChoice$(OBJ) ExtChoiceEnc$(OBJ) print$(OBJ) \
$(LIBDIR)/$(PERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
	$(LINK) writer$(OBJ) ExtChoice$(OBJ) ExtChoiceEnc$(OBJ) print$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) ExtChoice$(OBJ) ExtChoiceDec$(OBJ) print$(OBJ) \
$(LIBDIR)/$(PERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
	$(LINK) reader$(OBJ) ExtChoice$(OBJ) ExtChoiceDec$(OBJ) print$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(PSLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

ExtChoice.c ExtChoiceEnc.c ExtChoiceDec.c ExtChoice.h print.c : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c -per -trace -strict-size -print print.c

depends: ExtChoice.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) ExtChoice*.c
	$(RM) ExtChoice.h
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



