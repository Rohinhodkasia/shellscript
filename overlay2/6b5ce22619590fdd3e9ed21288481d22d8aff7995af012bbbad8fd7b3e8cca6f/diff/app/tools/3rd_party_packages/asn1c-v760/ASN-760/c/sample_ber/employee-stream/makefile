# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

#ASN1C = ..\..\..\bin\asn1c
#RTXSRCDIR = ../../../rtxsrc

all : writer$(EXE) reader$(EXE)

ASN1FILE = employee.asn
HFILES = $(RTSRCDIR)/asn1type.h \ $(RTSRCDIR)/rtContext.h \
$(RTXSRCDIR)/rtxContext.h \ $(RTXSRCDIR)/rtxDList.h $(BERSRCDIR)/asn1ber.h

LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_)

writer$(EXE) : writer$(OBJ) Employee$(OBJ) EmployeeEnc$(OBJ) \
../../lib/$(BERLIBNAME) ../../lib/$(RTLIBNAME)
	$(LINK) writer$(OBJ) Employee$(OBJ) EmployeeEnc$(OBJ) $(LINKOPT) \
	  $(LPATHS) $(LLBER) $(LLRT) $(LLSYS)

reader$(EXE) : reader$(OBJ) Employee$(OBJ) EmployeeDec$(OBJ) \
EmployeePrint$(OBJ) ../../lib/$(BERLIBNAME) ../../lib/$(RTLIBNAME)
	$(LINK) reader$(OBJ) Employee$(OBJ) EmployeeDec$(OBJ) \
	  EmployeePrint$(OBJ) $(LINKOPT) $(LPATHS) $(LLBER) $(LLRT) \
	  $(LLSYS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Employee.c EmployeeEnc.c EmployeeDec.c EmployeePrint.c Employee.h : \
$(ASN1FILE) $(ASN1C) 
	$(ASN1C) $(ASN1FILE) -c -ber -trace -stream -print

depends: Employee.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) Employee*.c
	$(RM) Employee.h
	$(RM) rtkey.h
	$(RM) *$(OBJ)
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.lib
	$(RM) *~
	$(RM) message.dat
	$(RM) messagei.dat
