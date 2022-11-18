# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = $(PERCPPHFILES)
LIBFILES = $(LIBDIR)/$(PERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
LINKLIBS = $(PSLIBS)
OBJECTS = H323RAS$(OBJ) H323RASDec$(OBJ) H323RASEnc$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBFILES)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(LINKLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) H323RASPrint$(OBJ) $(LIBFILES)
	$(LINK) reader$(OBJ) $(OBJECTS) H323RASPrint$(OBJ) $(LINKOPT) $(LPATHS) $(LINKLIBS)

reader$(OBJ) : reader.cpp H323RAS.h $(HFILES)
writer$(OBJ) : writer.cpp H323RAS.h $(HFILES)
H323RAS$(OBJ) : H323RAS.cpp H323RAS.h $(HFILES)
H323RASEnc$(OBJ) : H323RASEnc.cpp H323RAS.h $(HFILES)
H323RASDec$(OBJ) : H323RASDec.cpp H323RAS.h $(HFILES)
H323RASPrint$(OBJ) : H323RASPrint.cpp H323RAS.h $(HFILES)

H323RAS.cpp H323RASEnc.cpp H323RASDec.cpp \
H323RAS.h H323RASPrint.cpp : H323RAS.asn $(ASN1C)
	$(ASN1C) H323RAS.asn -per -c++ -print -trace -strict-size

clean :
	$(RM) H323RAS*.cpp
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
