# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = test.asn
HFILES   = $(JSONCPPHFILES)
LIBNAMES = $(LIBDIR)/$(JSONLIBNAME) $(LIBDIR)/$(RTLIBNAME)
LINKLIBS = $(LLJSON) $(LLRT) $(LLSYS)

writer$(EXE) : writer$(OBJ) TimeString$(OBJ) $(LIBNAMES)
	$(LINK) writer$(OBJ) TimeString$(OBJ) $(LINKOPT) $(LPATHS) $(LINKLIBS)

reader$(EXE) : reader$(OBJ) print$(OBJ) TimeString$(OBJ) $(LIBNAMES)
	$(LINK) reader$(OBJ) print$(OBJ) TimeString$(OBJ) $(LINKOPT) \
	   $(LPATHS) $(LINKLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

TimeString.cpp TimeString.h : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c++ -json -print print.cpp -cfile TimeString.cpp -pdu all -usepdu TimesSeq

depends: TimeString.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

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
