# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = infoObject.asn
HFILES = $(PERHFILES)
OBJECTS = InfoObject$(OBJ) print$(OBJ) 
ENCOBJECTS = InfoObjectEnc$(OBJ) $(OBJECTS) 
DECOBJECTS = InfoObjectDec$(OBJ) $(OBJECTS) 

writer$(EXE) : writer$(OBJ) $(ENCOBJECTS) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) writer$(OBJ) $(ENCOBJECTS) $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) $(DECOBJECTS) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) reader$(OBJ) $(DECOBJECTS) $(LINKOPT) $(LPATHS) $(PSLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

InfoObject.c InfoObjectEnc.c InfoObjectDec.c InfoObject.h print.c : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c -per -trace -print print.c -geninit

depends: InfoObject.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) InfoObject*.c
	$(RM) InfoObject.h
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
