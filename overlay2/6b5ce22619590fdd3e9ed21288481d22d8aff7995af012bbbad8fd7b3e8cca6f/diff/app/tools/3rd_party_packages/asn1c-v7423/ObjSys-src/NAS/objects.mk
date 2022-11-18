OBJECTS =  \
TS24007L3$(OBJ) \
TS24008IES$(OBJ) \
TS24008Msgs$(OBJ) \
TS24011IES$(OBJ) \
TS24011Msgs$(OBJ) \
TS24301IES$(OBJ) \
TS24301Msgs$(OBJ) \
TS24501Msgs$(OBJ) \
TS44018Msgs$(OBJ) \
TS44018IES$(OBJ) \
TS44060IES$(OBJ)

ENCOBJECTS =  \
TS24007L3Enc$(OBJ) \
TS24008IESEnc$(OBJ) \
TS24008MsgsEnc$(OBJ) \
TS24011IESEnc$(OBJ) \
TS24011MsgsEnc$(OBJ) \
TS24301IESEnc$(OBJ) \
TS24301MsgsEnc$(OBJ) \
TS24501MsgsEnc$(OBJ) \
TS44018MsgsEnc$(OBJ) \
TS44018IESEnc$(OBJ) \
TS44060IESEnc$(OBJ)

DECOBJECTS =  \
TS24007L3Dec$(OBJ) \
TS24008IESDec$(OBJ) \
TS24008MsgsDec$(OBJ) \
TS24011IESDec$(OBJ) \
TS24011MsgsDec$(OBJ) \
TS24301IESDec$(OBJ) \
TS24301MsgsDec$(OBJ) \
TS24501MsgsDec$(OBJ) \
TS44018MsgsDec$(OBJ) \
TS44018IESDec$(OBJ) \
TS44060IESDec$(OBJ)

P2MOBJECTS =  \
TS24007L3PrtToStrm$(OBJ) \
TS24008IESPrtToStrm$(OBJ) \
TS24008MsgsPrtToStrm$(OBJ) \
TS24011IESPrtToStrm$(OBJ) \
TS24011MsgsPrtToStrm$(OBJ) \
TS24301IESPrtToStrm$(OBJ) \
TS24301MsgsPrtToStrm$(OBJ) \
TS24501MsgsPrtToStrm$(OBJ) \
TS44018MsgsPrtToStrm$(OBJ) \
TS44018IESPrtToStrm$(OBJ) \
TS44060IESPrtToStrm$(OBJ) 

TESTOBJECTS =  \
TS24007L3Test$(OBJ) \
TS24008IESTest$(OBJ) \
TS24008MsgsTest$(OBJ) \
TS24011IESTest$(OBJ) \
TS24011MsgsTest$(OBJ) \
TS24301IESTest$(OBJ) \
TS24301MsgsTest$(OBJ) \
TS24501MsgsTest$(OBJ) \
TS44018MsgsTest$(OBJ) \
TS44018IESTest$(OBJ) \
TS44060IESTest$(OBJ)

ALLOBJECTS = $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(P2MOBJECTS) $(TESTOBJECTS)
