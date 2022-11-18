# makefile to build the employee sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = employee.asn
HFILES = $(PERCPPHFILES)

writer$(EXE) : writer$(OBJ) WrEmployee$(OBJ) $(LIBDIR)/$(PERLIBNAME)
	$(LINK) writer$(OBJ) WrEmployee$(OBJ) $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) RdEmployee$(OBJ) \
$(LIBDIR)/$(PERLIBNAME)
	$(LINK) reader$(OBJ) RdEmployee$(OBJ) $(LINKOPT) $(LPATHS) \
	    $(PSLIBS)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

WrEmployee.cpp rtkey.h \
WrEmployee.h : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c++ -per -trace -print -hfile WrEmployee.h -cfile WrEmployee.cpp

RdEmployee.cpp \
RdEmployee.h : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c++ -per -noencode -config rd.config.xml -trace -print -hfile RdEmployee.h -cfile RdEmployee.cpp

depends: WrEmployee.cpp RdEmployee.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) WrEmployee.cpp
	$(RM) WrEmployee.h
	$(RM) RdEmployee.cpp
	$(RM) RdEmployee.h
	$(RM) rtkey.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)


