# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES   = $(JSONCPPHFILES)
LIBNAMES = $(LIBDIR)/$(JSONLIBNAME) $(LIBDIR)/$(RTLIBNAME)
LINKLIBS = $(LLJSON) $(LLRT) $(LLSYS)

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
	$(ASN1C) test.asn -c++ -json -print print.cpp -cfile TimeString.cpp -pdu all -usepdu TimesSeq

clean :
	$(RM) TimeString*.cpp
	$(RM) TimeString.h
	$(RM) print.cpp
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.json
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
