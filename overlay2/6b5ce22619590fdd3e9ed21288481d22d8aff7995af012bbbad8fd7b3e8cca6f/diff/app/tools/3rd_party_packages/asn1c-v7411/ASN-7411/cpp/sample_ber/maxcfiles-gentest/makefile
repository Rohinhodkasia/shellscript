# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

LPATHS = $(LPPFX)$(LIBDIR) $(LPATHS_) $(LPPFX).

# run-time libraries
Employee_OBJECTS = \
Asn1External$(OBJ)\
Asn1EmbeddedPDV$(OBJ)\
asn1E_EmployeeNumber$(OBJ)\
asn1E_Date$(OBJ)\
asn1E_Name$(OBJ)\
asn1E_ChildInformation$(OBJ)\
asn1E__SeqOfChildInformation$(OBJ)\
asn1E_PersonnelRecord$(OBJ)\
asn1D_EmployeeNumber$(OBJ)\
asn1D_Date$(OBJ)\
asn1D_Name$(OBJ)\
asn1D_ChildInformation$(OBJ)\
asn1D__SeqOfChildInformation$(OBJ)\
asn1D_PersonnelRecord$(OBJ)\
asn1Init_Name$(OBJ)\
asn1Init_ChildInformation$(OBJ)\
asn1Init__SeqOfChildInformation$(OBJ)\
asn1Init_PersonnelRecord$(OBJ)\
asn1Free_Date$(OBJ)\
asn1Free_Name$(OBJ)\
asn1Free_ChildInformation$(OBJ)\
asn1Free__SeqOfChildInformation$(OBJ)\
asn1Free_PersonnelRecord$(OBJ)\
asn1Print_EmployeeNumber$(OBJ)\
asn1Print_Date$(OBJ)\
asn1Print_Name$(OBJ)\
asn1Print_ChildInformation$(OBJ)\
asn1Print__SeqOfChildInformation$(OBJ)\
asn1Print_PersonnelRecord$(OBJ)\
asn1Test_PersonnelRecord$(OBJ)\
ASN1C__SeqOfChildInformation$(OBJ)\
ASN1C_PersonnelRecord$(OBJ)\
ASN1T_Name$(OBJ)\
ASN1T_ChildInformation$(OBJ)\
ASN1T_PersonnelRecord$(OBJ)


all : writer$(EXE) reader$(EXE)

writer$(EXE) : writer$(OBJ) $(LIBPFX)Employee.$(LIBEXT) \
$(LIBDIR)/$(BERLIBNAME)
	$(LINK) writer$(OBJ) $(LINKOPT) $(LPATHS) $(LLPFX)Employee$(LLEXT) $(BSLIBS)

reader$(EXE) : reader$(OBJ) $(LIBPFX)Employee.$(LIBEXT) \
$(LIBDIR)/$(BERLIBNAME)
	$(LINK) reader$(OBJ) $(LINKOPT) $(LPATHS) $(LLPFX)Employee$(LLEXT) $(BSLIBS)

writer$(OBJ) : writer.cpp Employee.h $(HFILES)
reader$(OBJ) : reader.cpp Employee.h $(HFILES)

# .obj -> .lib rules
$(LIBPFX)Employee.$(LIBEXT) : $(Employee_OBJECTS)
	$(LIBCMD) $(Employee_OBJECTS)

# .cpp -> .obj rules
Asn1External$(OBJ) : Asn1External.cpp \
Asn1External.h $(HFILES)

Asn1EmbeddedPDV$(OBJ) : Asn1EmbeddedPDV.cpp \
Asn1EmbeddedPDV.h $(HFILES)

# common files rules
asn1Init_Date$(OBJ) : asn1Init_Date.cpp \
Employee.h $(HFILES)

asn1Init_Name$(OBJ) : asn1Init_Name.cpp \
Employee.h $(HFILES)

asn1Init_ChildInformation$(OBJ) : asn1Init_ChildInformation.cpp \
Employee.h $(HFILES)

asn1Init__SeqOfChildInformation$(OBJ) : asn1Init__SeqOfChildInformation.cpp \
Employee.h $(HFILES)

asn1Init_PersonnelRecord$(OBJ) : asn1Init_PersonnelRecord.cpp \
Employee.h $(HFILES)

asn1Free_Date$(OBJ) : asn1Free_Date.cpp \
Employee.h $(HFILES)

asn1Free_Name$(OBJ) : asn1Free_Name.cpp \
Employee.h $(HFILES)

asn1Free_ChildInformation$(OBJ) : asn1Free_ChildInformation.cpp \
Employee.h $(HFILES)

asn1Free__SeqOfChildInformation$(OBJ) : asn1Free__SeqOfChildInformation.cpp \
Employee.h $(HFILES)

asn1Free_PersonnelRecord$(OBJ) : asn1Free_PersonnelRecord.cpp \
Employee.h $(HFILES)

# decode files rules
asn1D_EmployeeNumber$(OBJ) : asn1D_EmployeeNumber.cpp \
Employee.h $(HFILES)

asn1D_Date$(OBJ) : asn1D_Date.cpp \
Employee.h $(HFILES)

asn1D_Name$(OBJ) : asn1D_Name.cpp \
Employee.h $(HFILES)

asn1D_ChildInformation$(OBJ) : asn1D_ChildInformation.cpp \
Employee.h $(HFILES)

asn1D__SeqOfChildInformation$(OBJ) : asn1D__SeqOfChildInformation.cpp \
Employee.h $(HFILES)

asn1D_PersonnelRecord$(OBJ) : asn1D_PersonnelRecord.cpp \
Employee.h $(HFILES)

# encode files rules
asn1E_EmployeeNumber$(OBJ) : asn1E_EmployeeNumber.cpp \
Employee.h $(HFILES)

asn1E_Date$(OBJ) : asn1E_Date.cpp \
Employee.h $(HFILES)

asn1E_Name$(OBJ) : asn1E_Name.cpp \
Employee.h $(HFILES)

asn1E_ChildInformation$(OBJ) : asn1E_ChildInformation.cpp \
Employee.h $(HFILES)

asn1E__SeqOfChildInformation$(OBJ) : asn1E__SeqOfChildInformation.cpp \
Employee.h $(HFILES)

asn1E_PersonnelRecord$(OBJ) : asn1E_PersonnelRecord.cpp \
Employee.h $(HFILES)

# encode files rules
asn1Print_EmployeeNumber$(OBJ) : asn1Print_EmployeeNumber.cpp \
Employee.h $(HFILES)

asn1Print_Date$(OBJ) : asn1Print_Date.cpp \
Employee.h $(HFILES)

asn1Print_Name$(OBJ) : asn1Print_Name.cpp \
Employee.h $(HFILES)

asn1Print_ChildInformation$(OBJ) : asn1Print_ChildInformation.cpp \
Employee.h $(HFILES)

asn1Print__SeqOfChildInformation$(OBJ) : asn1Print__SeqOfChildInformation.cpp \
Employee.h $(HFILES)

asn1Print_PersonnelRecord$(OBJ) : asn1Print_PersonnelRecord.cpp \
Employee.h $(HFILES)

# .asn -> .cpp .h rules
Asn1External.cpp \
Asn1EmbeddedPDV.cpp \
asn1E_EmployeeNumber.cpp \
asn1E_Date.cpp \
asn1E_Name.cpp \
asn1E_ChildInformation.cpp \
asn1E__SeqOfChildInformation.cpp \
asn1E_PersonnelRecord.cpp \
asn1D_EmployeeNumber.cpp \
asn1D_Date.cpp \
asn1D_Name.cpp \
asn1D_ChildInformation.cpp \
asn1D__SeqOfChildInformation.cpp \
asn1D_PersonnelRecord.cpp \
asn1Init_Name.cpp \
asn1Init_ChildInformation.cpp \
asn1Init__SeqOfChildInformation.cpp \
asn1Init_PersonnelRecord.cpp \
asn1Free_Date.cpp \
asn1Free_Name.cpp \
asn1Free_ChildInformation.cpp \
asn1Free__SeqOfChildInformation.cpp \
asn1Free_PersonnelRecord.cpp \
asn1Print_EmployeeNumber.cpp \
asn1Print_Date.cpp \
asn1Print_Name.cpp \
asn1Print_ChildInformation.cpp \
asn1Print__SeqOfChildInformation.cpp \
asn1Print_PersonnelRecord.cpp \
asn1Test_PersonnelRecord.cpp \
ASN1C__SeqOfChildInformation.cpp \
ASN1C_PersonnelRecord.cpp \
ASN1T_Name.cpp \
ASN1T_ChildInformation.cpp \
ASN1T_PersonnelRecord.cpp \
Employee.h \
Asn1External.h \
Asn1EmbeddedPDV.h \
: employee.asn $(ASN1C)
	$(ASN1C) employee.asn -cpp -ber -print -test -trace -geninit -maxcfiles

clean:
	$(RM) Asn1External.*
	$(RM) Asn1EmbeddedPDV.*
	$(RM) asn1Global_*.cpp
	$(RM) asn1Init_Name.cpp
	$(RM) asn1Init_ChildInformation.cpp
	$(RM) asn1Init__SeqOfChildInformation.cpp
	$(RM) asn1Init_PersonnelRecord.cpp
	$(RM) asn1E_EmployeeNumber.cpp
	$(RM) asn1E_Date.cpp
	$(RM) asn1E_Name.cpp
	$(RM) asn1E_ChildInformation.cpp
	$(RM) asn1E__SeqOfChildInformation.cpp
	$(RM) asn1E_PersonnelRecord.cpp
	$(RM) asn1D_EmployeeNumber.cpp
	$(RM) asn1D_Date.cpp
	$(RM) asn1D_Name.cpp
	$(RM) asn1D_ChildInformation.cpp
	$(RM) asn1D__SeqOfChildInformation.cpp
	$(RM) asn1D_PersonnelRecord.cpp
	$(RM) asn1Free_Date.cpp
	$(RM) asn1Free_Name.cpp
	$(RM) asn1Free_ChildInformation.cpp
	$(RM) asn1Free__SeqOfChildInformation.cpp
	$(RM) asn1Free_PersonnelRecord.cpp
	$(RM) asn1Print_EmployeeNumber.cpp
	$(RM) asn1Print_Date.cpp
	$(RM) asn1Print_Name.cpp
	$(RM) asn1Print_ChildInformation.cpp
	$(RM) asn1Print__SeqOfChildInformation.cpp
	$(RM) asn1Print_PersonnelRecord.cpp
	$(RM) asn1Test_PersonnelRecord.cpp
	$(RM) ASN1C__SeqOfChildInformation.cpp
	$(RM) ASN1C_PersonnelRecord.cpp
	$(RM) ASN1T_Name.cpp
	$(RM) ASN1T_ChildInformation.cpp
	$(RM) ASN1T_PersonnelRecord.cpp
	$(RM) Employee.h
	$(RM) rtkey.h
	$(RM) *$(OBJ)
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM_MSVC_FILES)
	$(RM) *.dat
	$(RM) *~
	$(RM) *.$(LIBEXT)
