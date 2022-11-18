# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

ASN1FILE = employee.asn
HFILES = $(RTSRCDIR)$(PS)asn1type.h \
$(RTSRCDIR)$(PS)rtContext.h \
$(RTXSRCDIR)$(PS)rtxContext.h \
$(RTXSRCDIR)$(PS)rtxDList.h \
$(JSONSRCDIR)$(PS)asn1json.h 

LIBDIR2 = ..$(PS)..$(PS)lib
LPATHS = $(LPPFX)$(LIBDIR2) $(LPATHS_)

writer$(EXE) : writer$(OBJ) Employee$(OBJ) EmployeeEnc$(OBJ) \
..$(PS)..$(PS)lib$(PS)$(RTLIBNAME)
	$(LINK) writer$(OBJ) Employee$(OBJ) EmployeeEnc$(OBJ) $(LINKOPT) \
	  $(LPATHS) $(JSONLIBS)

reader$(EXE) : reader$(OBJ) Employee$(OBJ) EmployeeDec$(OBJ) \
EmployeePrint$(OBJ) ..$(PS)..$(PS)lib$(PS)$(RTLIBNAME)
	$(LINK) reader$(OBJ) Employee$(OBJ) EmployeeDec$(OBJ) \
	  EmployeePrint$(OBJ) $(LINKOPT) $(LPATHS) $(JSONLIBS)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Employee.c EmployeeEnc.c EmployeeDec.c EmployeePrint.c Employee.h : \
$(ASN1FILE) $(ASN1C) 
	$(ASN1C) $(ASN1FILE) -c -json -trace -print -html

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
	$(RM) message.json
	$(RM) *.lib
	$(RM) *~
	$(RM) rtkey.h
