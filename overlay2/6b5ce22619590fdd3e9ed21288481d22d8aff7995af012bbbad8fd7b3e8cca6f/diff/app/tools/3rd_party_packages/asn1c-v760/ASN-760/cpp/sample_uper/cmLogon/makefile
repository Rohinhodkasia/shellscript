# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = $(PERCPPHFILES)
LIBNAMES = $(LIBDIR)/$(PERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
OBJECTS = CMMessageSetVersion1$(OBJ) ACSE-1$(OBJ) Asn1External$(OBJ) \
CMMessageSetVersion1Enc$(OBJ) ACSE-1Enc$(OBJ) \
CMMessageSetVersion1Dec$(OBJ) ACSE-1Dec$(OBJ) \
CMMessageSetVersion1Print$(OBJ) ACSE-1Print$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBNAMES)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(LIBNAMES)
	$(LINK) reader$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(PSLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

CMMessageSetVersion1.cpp CMMessageSetVersion1Enc.cpp \
CMMessageSetVersion1Dec.cpp CMMessageSetVersion1.h \
CMMessageSetVersion1Print.cpp : cm-v1.asn $(ASN1C)
	$(ASN1C) cm-v1.asn -c++ -uper -trace -print -strict-size -x64

ACSE-1.cpp ACSE-1Enc.cpp ACSE-1Dec.cpp ACSE-1Print.cpp ACSE-1.h : \
acse-1.asn $(ASN1C)
	$(ASN1C) acse-1.asn -c++ -uper -trace -print -strict-size -x64

depends: CMMessageSetVersion1.cpp ACSE-1.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) CMMessageSetVersion1*.cpp
	$(RM) CMMessageSetVersion1.h
	$(RM) A*.cpp
	$(RM) A*.h
	$(RM) rtkey.h
	$(RM) message.dat
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
