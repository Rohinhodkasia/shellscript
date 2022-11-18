# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = employee.asn
all : writer$(EXE) reader$(EXE)

HFILES = $(RTSRCDIR)/asn1type.h \
$(RTSRCDIR)/rtContext.h \
$(RTXSRCDIR)/rtxContext.h \
$(RTXSRCDIR)/rtxDList.h \
$(BERSRCDIR)/asn1ber.h 

writer$(EXE) : writer$(OBJ) Employee$(OBJ) EmployeeEnc$(OBJ) \
$(LIBDIR)/$(BERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
	$(LINK) writer$(OBJ) Employee$(OBJ) EmployeeEnc$(OBJ) $(LINKOPT) \
	  $(LPATHS) $(BSLIBS)

reader$(EXE) : reader$(OBJ) Employee$(OBJ) EmployeeDec$(OBJ) \
EmployeePrint$(OBJ) $(LIBDIR)/$(BERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
	$(LINK) reader$(OBJ) Employee$(OBJ) EmployeeDec$(OBJ) \
	  EmployeePrint$(OBJ) $(LINKOPT) $(LPATHS) $(BSLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Employee.c EmployeeEnc.c EmployeeDec.c EmployeePrint.c Employee.h : \
$(ASN1FILE) $(ASN1C) 
	$(ASN1C) $(ASN1FILE) -c -ber -trace -print -html

depends: Employee.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) Employee*.c
	$(RM) Employee.h
	$(RM) Employee.html
	$(RM) asn1-style.css
	$(RM) *.dat
	$(RM) *$(OBJ)
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.lib
	$(RM) *~
	$(RM) rtkey.h
