# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

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

writer$(OBJ) : writer.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) writer.cpp

reader$(OBJ) : reader.cpp $(RWHFILES)
	$(CCC) -c $(CCFLAGS) $(IPATHS) reader.cpp

# .cpp -> .obj rules
# common file rules
CAP-1-2$(OBJ) : CAP-1-2.cpp CAP-1-2.h rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) CAP-1-2.cpp

# decode file rules
CAP-1-2Dec$(OBJ) : CAP-1-2Dec.cpp CAP-1-2.h rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) CAP-1-2Dec.cpp

# encode file rules
CAP-1-2Enc$(OBJ) : CAP-1-2Enc.cpp CAP-1-2.h rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) CAP-1-2Enc.cpp

# print file rules
CAP-1-2Print$(OBJ) : CAP-1-2Print.cpp CAP-1-2.h rtkey.h $(HFILES)
	$(CCC) $(CCFLAGS) -c $(IPATHS) CAP-1-2Print.cpp

# .asn -> .cpp .h rules
CAP-1-2Enc.cpp \
CAP-1-2Dec.cpp \
CAP-1-2.cpp \
CAP-1-2Print.cpp \
CAP-1-2.h \
rtkey.h \
: cap.asn $(OSROOTDIR)/bin/asn1c$(EXE)
	$(ASN1C) cap.asn -cpp -per -print -trace

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

