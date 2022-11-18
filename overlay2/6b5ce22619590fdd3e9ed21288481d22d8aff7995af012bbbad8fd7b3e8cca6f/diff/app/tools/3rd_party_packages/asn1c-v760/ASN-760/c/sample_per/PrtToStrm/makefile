# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = $(PERHFILES)
LIBFILES = $(LIBDIR)/$(PERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
LINKLIBS = $(PSLIBS)

OBJECTS = \
H323-MESSAGES$(OBJ) \
H235-SECURITY-MESSAGES$(OBJ) \
H323-MESSAGESEnc$(OBJ) \
H235-SECURITY-MESSAGESEnc$(OBJ) \
H323-MESSAGESDec$(OBJ) \
H235-SECURITY-MESSAGESDec$(OBJ) 

PRINT_OBJECTS = \
H323-MESSAGESPrtToStrm$(OBJ) \
H235-SECURITY-MESSAGESPrtToStrm$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBFILES)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(LINKLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(PRINT_OBJECTS) $(LIBFILES)
	$(LINK) reader$(OBJ) $(OBJECTS) $(PRINT_OBJECTS) $(LINKOPT) \
	   $(LPATHS) $(LINKLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

H323-MESSAGES.c H323-MESSAGESEnc.c H323-MESSAGESDec.c \
H323-MESSAGESPrtToStrm.c H323-MESSAGES.h : h225.asn h323.cfg $(ASN1C)
	$(ASN1C) h225.asn -c -per -trace -prttostrm -config h323.cfg -strict-size

H235-SECURITY-MESSAGES.c H235-SECURITY-MESSAGESEnc.c \
H235-SECURITY-MESSAGESDec.c \
H235-SECURITY-MESSAGESPrtToStrm.c \
H235-SECURITY-MESSAGES.h : h235.asn h323.cfg $(ASN1C)
	$(ASN1C) h235.asn -c -per -trace -prttostrm -config h323.cfg -strict-size

depends: H323-MESSAGES.c H235-SECURITY-MESSAGES.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) H*-MESSAGES*.c
	$(RM) H*-MESSAGES*.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) *.log
	$(RM) rtkey.h


