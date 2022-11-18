# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

ASN1FILE = cap.asn

OBJECTS =  \
CAP-1-2$(OBJ)

ENCOBJECTS =  \
CAP-1-2Enc$(OBJ)

DECOBJECTS =  \
CAP-1-2Dec$(OBJ)

PRTOBJECTS =  \
CAP-1-2Print$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) \
 $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(PSLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(PSLIBS)

RWHFILES = CAP-1-2.h rtkey.h $(HFILES)

# .cpp -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .cpp .h rules
CAP-1-2Enc.cpp \
CAP-1-2Dec.cpp \
CAP-1-2.cpp \
CAP-1-2Print.cpp \
CAP-1-2.h \
rtkey.h \
: $(ASN1FILE) $(OSROOTDIR)/bin/asn1c$(EXE)
	$(ASN1C) $(ASN1FILE) -cpp -per -print -trace

depends: CAP-1-2.cpp
	gcc *.cpp -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) CAP-1-2Enc.cpp
	$(RM) CAP-1-2Dec.cpp
	$(RM) CAP-1-2.cpp
	$(RM) CAP-1-2Print.cpp
	$(RM) CAP-1-2.h 
	$(RM) rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.dat

