# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = $(BERCPPHFILES)
LIBS = $(LLBER) $(LLRT) $(LLSYS)

writer$(EXE) : writer$(OBJ) BigInt$(OBJ) $(LIBDIR)/$(BERLIBNAME) \
$(LIBDIR)/$(RTLIBNAME)
	$(LINK) writer$(OBJ) BigInt$(OBJ) $(LINKOPT) $(LPATHS) $(LIBS)

reader$(EXE) : reader$(OBJ) print$(OBJ) BigInt$(OBJ) $(LIBDIR)/$(BERLIBNAME) \
$(LIBDIR)/$(RTLIBNAME)
	$(LINK) reader$(OBJ) print$(OBJ) BigInt$(OBJ) $(LINKOPT) \
	   $(LPATHS) $(LIBS)

writer$(OBJ) : writer.cpp BigInt.h $(HFILES)
reader$(OBJ) : reader.cpp BigInt.h $(HFILES)
print$(OBJ)  : print.cpp BigInt.h $(HFILES)

BigInt$(OBJ)  : BigInt.cpp BigInt.h $(HFILES)

BigInt.cpp BigInt.h : bigInt.asn
	$(ASN1C) bigInt.asn -c++ -der -print print.cpp -config bigInt.cfg \
	-cfile BigInt.cpp

clean :
	$(RM) BigInt.cpp
	$(RM) BigInt.h
	$(RM) print.cpp
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
