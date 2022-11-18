# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = bigInt.asn
HFILES = $(BERCPPHFILES)
LIBS = $(LLBER) $(LLRT) $(LLSYS)

writer$(EXE) : writer$(OBJ) BigInt$(OBJ) $(LIBDIR)/$(BERLIBNAME) \
$(LIBDIR)/$(RTLIBNAME)
	$(LINK) writer$(OBJ) BigInt$(OBJ) $(LINKOPT) $(LPATHS) $(LIBS)

reader$(EXE) : reader$(OBJ) print$(OBJ) BigInt$(OBJ) $(LIBDIR)/$(BERLIBNAME) \
$(LIBDIR)/$(RTLIBNAME)
	$(LINK) reader$(OBJ) print$(OBJ) BigInt$(OBJ) $(LINKOPT) \
	   $(LPATHS) $(LIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

BigInt.cpp BigInt.h : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c++ -der -print print.cpp -config bigInt.cfg \
	-cfile BigInt.cpp

depends: BigInt.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

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
