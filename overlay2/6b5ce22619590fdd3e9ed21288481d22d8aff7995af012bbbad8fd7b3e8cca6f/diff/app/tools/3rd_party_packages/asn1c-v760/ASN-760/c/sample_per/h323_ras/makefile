# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = H323RAS.asn
HFILES = $(PERHFILES)
LIBFILES = $(LIBDIR)/$(PERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
LINKLIBS = $(PSLIBS)
OBJECTS = H323RAS$(OBJ) H323RASPrint$(OBJ)
ENCOBJECTS = H323RASEnc$(OBJ) $(OBJECTS)
DECOBJECTS = H323RASDec$(OBJ) $(OBJECTS)

writer$(EXE) : writer$(OBJ) $(ENCOBJECTS) $(LIBFILES)
	$(LINK) writer$(OBJ) $(ENCOBJECTS) $(LINKOPT) $(LPATHS) $(LINKLIBS)

reader$(EXE) : reader$(OBJ) $(DECOBJECTS) $(LIBFILES)
	$(LINK) reader$(OBJ) $(DECOBJECTS) $(LINKOPT) $(LPATHS) $(LINKLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

H323RAS.c H323RASEnc.c H323RASDec.c H323RAS.h H323RASPrint.c : \
$(ASN1FILE) $(ASN1C)
	$(ASN1C) $(ASN1FILE) -per -c -print -trace -strict-size

depends: H323RAS.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) H323RAS*.c
	$(RM) H323RAS.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
