# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : client$(EXE) server$(EXE)

ASN1FILE = employee.asn
HFILES = $(RTSRCDIR)/asn1type.h $(BERSRCDIR)/asn1ber.h \
$(BERSRCDIR)/asn1berStream.h

client$(EXE) : client$(OBJ) Employee$(OBJ) EmployeeEnc$(OBJ) \
$(LIBDIR)/$(BERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
	$(LINK) client$(OBJ) Employee$(OBJ) EmployeeEnc$(OBJ) $(LINKOPT) \
	   $(LPATHS) $(BSLIBS)

server$(EXE) : server$(OBJ) Employee$(OBJ) EmployeeDec$(OBJ) \
EmployeePrint$(OBJ) $(LIBDIR)/$(BERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
	$(LINK) server$(OBJ) Employee$(OBJ) EmployeeDec$(OBJ) \
	   EmployeePrint$(OBJ) $(LINKOPT) $(LPATHS) $(BSLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Employee.c EmployeeEnc.c EmployeeDec.c EmployeePrint.c Employee.h : \
$(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c -ber -trace -print -stream -geninit

depends: Employee.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) Employee*.c
	$(RM) Employee.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.lib
	$(RM) *~
	$(RM) client$(EXE)
	$(RM) server$(EXE)
	$(RM) rtkey.h
