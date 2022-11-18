# makefile to build the employee sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = employee.asn
HFILES = Employee.h $(PERHFILES)

writer$(EXE) : writer$(OBJ) WrEmployee$(OBJ) \
$(PERLIBNAMES)
	$(LINK) writer$(OBJ) WrEmployee$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(LLPER) \
	   $(LLRT) $(LLSYS)

reader$(EXE) : reader$(OBJ) RdEmployee$(OBJ) \
$(PERLIBNAMES)
	$(LINK) reader$(OBJ) RdEmployee$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(LLPER) \
	   $(LLRT) $(LLSYS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

WrEmployee.c WrEmployee.h : \
$(ASN1FILE) ../../../bin/asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -c -per -trace -print -prtfmt bracetext -geninit -hfile WrEmployee.h -cfile WrEmployee.c

RdEmployee.c RdEmployee.h : \
$(ASN1FILE) ../../../bin/asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -c -per -noencode -config rd.config.xml -trace -print -prtfmt bracetext -geninit -hfile RdEmployee.h -cfile RdEmployee.c

depends: WrEmployee.c RdEmployee.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) WrEmployee.h
	$(RM) WrEmployee.c
	$(RM) RdEmployee.h
	$(RM) RdEmployee.c
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.dat
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) rtkey.h
