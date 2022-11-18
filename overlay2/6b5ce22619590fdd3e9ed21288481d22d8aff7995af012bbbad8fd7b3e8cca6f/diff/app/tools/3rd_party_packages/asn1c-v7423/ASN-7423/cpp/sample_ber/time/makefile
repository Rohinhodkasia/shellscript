# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES   = $(BERCPPHFILES)
LIBNAMES = $(LIBDIR)/$(BERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
LINKLIBS = $(LLBER) $(LLRT) $(LLSYS)

writer$(EXE) : writer$(OBJ) TimeString$(OBJ) $(LIBNAMES)
	$(LINK) writer$(OBJ) TimeString$(OBJ) $(LINKOPT) $(LPATHS) $(LINKLIBS)

reader$(EXE) : reader$(OBJ) print$(OBJ) TimeString$(OBJ) $(LIBNAMES)
	$(LINK) reader$(OBJ) print$(OBJ) TimeString$(OBJ) $(LINKOPT) \
	   $(LPATHS) $(LINKLIBS)

writer$(OBJ) : writer.cpp TimeString.h $(HFILES)
reader$(OBJ) : reader.cpp TimeString.h $(HFILES)
print$(OBJ)  : print.cpp TimeString.h $(HFILES)

TimeString$(OBJ)  : TimeString.cpp TimeString.h $(HFILES)

TimeString.cpp TimeString.h : test.asn
	$(ASN1C) test.asn -c++ -ber -print print.cpp -cfile TimeString.cpp -pdu "*"

clean :
	$(RM) TimeString*.cpp
	$(RM) TimeString.h
	$(RM) print.cpp
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
