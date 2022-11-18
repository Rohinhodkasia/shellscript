# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : client$(EXE) server$(EXE)

ASN1FILE = employee.asn
HFILES = $(RTSRCDIR)/asn1type.h $(RTSRCDIR)/rtContext.h \
$(RTXSRCDIR)/rtxContext.h $(RTXSRCDIR)/rtxDList.h $(BERSRCDIR)/asn1ber.h

LIBDIR2 = ../../lib
LPATHS = $(LPPFX)$(LIBDIR2) $(LPATHS_)

client$(EXE) : client$(OBJ) Employee$(OBJ) EmployeeEnc$(OBJ) \
../../lib/$(BERLIBNAME) ../../lib/$(RTLIBNAME)
	$(LINK) client$(OBJ) Employee$(OBJ) EmployeeEnc$(OBJ) $(LINKOPT) \
	  $(LPATHS) $(LLBER) $(LLRT) $(LLSYS)

server$(EXE) : server$(OBJ) Employee$(OBJ) EmployeeDec$(OBJ) \
EmployeePrint$(OBJ) ../../lib/$(BERLIBNAME) ../../lib/$(RTLIBNAME)
	$(LINK) server$(OBJ) Employee$(OBJ) EmployeeDec$(OBJ) \
	  EmployeePrint$(OBJ) $(LINKOPT) $(LPATHS) $(LLBER) $(LLRT) \
	  $(LLSYS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Employee.c EmployeeEnc.c EmployeeDec.c EmployeePrint.c Employee.h : \
$(ASN1FILE) 
	$(ASN1C) $(ASN1FILE) -c -ber -trace -stream -print

depends: Employee.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) Employee*.c
	$(RM) Employee.h
	$(RM) rtkey.h
	$(RM) *$(OBJ)
	$(RM) client$(EXE)
	$(RM) server$(EXE)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.lib
	$(RM) *~
