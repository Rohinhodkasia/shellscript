# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(RTSRCDIR) $(XMLINC) $(XMLDEFS)
LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

HFILES = $(RTSRCDIR)/asn1type.h \

ASN1FILE = extChoice.asn

all : writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) ExtChoice$(OBJ) ExtChoiceEnc$(OBJ) \
$(LIBDIR)/$(XMLLIBNAME) 
	$(LINK) writer$(OBJ) ExtChoice$(OBJ) ExtChoiceEnc$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(XMLLIBS)

reader$(EXE) : reader$(OBJ) ExtChoice$(OBJ) ExtChoiceDec$(OBJ) print$(OBJ) \
$(LIBDIR)/$(XMLLIBNAME) 
	$(LINK) reader$(OBJ) ExtChoice$(OBJ) ExtChoiceDec$(OBJ) print$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(XMLLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

ExtChoice.c ExtChoiceDec.c ExtChoiceEnc.c ExtChoice.h print.c : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c -xer -trace -print print.c

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
	$(RM) message.xml
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h

