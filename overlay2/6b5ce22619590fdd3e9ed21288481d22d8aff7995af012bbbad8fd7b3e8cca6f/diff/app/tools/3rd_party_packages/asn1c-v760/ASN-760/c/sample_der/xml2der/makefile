# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = employee.asn

IPATHS = $(IPATHS_) -I$(OSROOTDIR) -I$(XMLSRCDIR) -I$(RTSRCDIR) \
-I$(BERSRCDIR) $(XMLINC) $(XMLDEFS)
LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(XMLLPATHS)

HFILES = \
$(RTSRCDIR)/asn1type.h \
$(XMLSRCDIR)/asn1xml.h \
$(XMLSRCDIR)/osrtxml.h \
$(BERHFILES) 

all : xml2der$(EXE) writer$(EXE)

xml2der$(EXE) : xml2der$(OBJ) Employee$(OBJ) EmployeePrint$(OBJ) \
$(LIBDIR)/$(BERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
	$(LINK) xml2der$(OBJ) Employee$(OBJ) EmployeePrint$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(LLXML) \
		$(BSLIBS)

writer$(EXE) : writer$(OBJ) Employee$(OBJ) \
$(LIBDIR)/$(RTLIBNAME)
	$(LINK) writer$(OBJ) Employee$(OBJ) \
	   $(LINKOPT) $(LPATHS) $(LLXML) $(BSLIBS) 

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Employee.c Employee.h EmployeePrint.c : $(ASN1FILE)
	$(ASN1C) $(ASN1FILE) -c -xml -der -xsd -trace -print EmployeePrint.c \
	   -cfile Employee.c

depends: Employee.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean :
	$(RM) Employee.c
	$(RM) EmployeePrint.c
	$(RM) Employee.h
	$(RM) Employee.xsd
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) message.*
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) xml2der$(EXE)
	$(RM) rtkey.h
