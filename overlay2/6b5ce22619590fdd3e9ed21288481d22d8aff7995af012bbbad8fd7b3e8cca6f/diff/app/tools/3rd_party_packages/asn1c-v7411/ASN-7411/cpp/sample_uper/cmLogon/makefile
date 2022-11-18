# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : writer$(EXE) reader$(EXE)

HFILES = $(PERCPPHFILES)
LIBNAMES = $(LIBDIR)/$(PERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
OBJECTS = CMMessageSetVersion1$(OBJ) ACSE-1$(OBJ) Asn1External$(OBJ) \
CMMessageSetVersion1Enc$(OBJ) ACSE-1Enc$(OBJ) \
CMMessageSetVersion1Dec$(OBJ) ACSE-1Dec$(OBJ) \
CMMessageSetVersion1Print$(OBJ) ACSE-1Print$(OBJ)

writer$(EXE) : writer$(OBJ) $(OBJECTS) $(LIBNAMES)
	$(LINK) writer$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(PSLIBS)

reader$(EXE) : reader$(OBJ) $(OBJECTS) $(LIBNAMES)
	$(LINK) reader$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(PSLIBS)

ACSE-1$(OBJ): ACSE-1.cpp ACSE-1.h rtkey.h ../../../rtpersrc/asn1PerCppTypes.h \
 ../../../rtpersrc/asn1per.h ../../../rtsrc/asn1type.h \
 ../../../rtxsrc/rtxExternDefs.h ../../../rtxsrc/rtxSList.h \
 ../../../rtxsrc/rtxContext.h ../../../rtxsrc/rtxDList.h \
 ../../../rtxsrc/osSysTypes.h ../../../rtxsrc/rtxCommonDefs.h \
 ../../../rtxsrc/osMacros.h ../../../rtxsrc/rtxStack.h \
 ../../../rtxsrc/rtxUTF8.h ../../../rtsrc/asn1tag.h \
 ../../../rtsrc/asn1ErrCodes.h ../../../rtsrc/rtExternDefs.h \
 ../../../rtxsrc/rtxBitString.h ../../../rtsrc/rtContext.h \
 ../../../rtsrc/asn1CEvtHndlr.h ../../../rtxsrc/rtxError.h \
 ../../../rtxsrc/rtxErrCodes.h ../../../rtxsrc/rtxMemory.h \
 ../../../rtsrc/asn1CharSet.h ../../../rtxsrc/rtxBitEncode.h \
 ../../../rtxsrc/rtxBitDecode.h ../../../rtxsrc/rtxBuffer.h \
 ../../../rtxsrc/rtxDiagBitTrace.h ../../../rtxsrc/rtxMemBuf.h \
 ../../../rtxsrc/rtxPrintToStream.h ../../../rtsrc/asn1CppTypes.h \
 ../../../rtxsrc/rtxDiag.h ../../../rtsrc/asn1CppEvtHndlr64.h \
 ../../../rtsrc/asn1CppEvtHndlr.h ../../../rtsrc/ASN1Context.h \
 ../../../rtxsrc/OSRTContext.h ../../../rtxsrc/OSRTMsgBuf.h \
 ../../../rtxsrc/OSRTCtxtHolder.h ../../../rtxsrc/OSRTCtxtHolderIF.h \
 ../../../rtxsrc/OSRTMsgBufIF.h ../../../rtsrc/ASN1TOctStr.h \
 ../../../rtsrc/ASN1TOctStr64.h ../../../rtsrc/ASN1TObjId.h \
 Asn1External.h ../../../rtsrc/ASN1CBitStr.h \
 ../../../rtsrc/ASN1CSeqOfList.h ../../../rtxsrc/rtxCommon.h \
 ../../../rtxsrc/rtxBigInt.h ../../../rtxsrc/rtxCharStr.h \
 ../../../rtxsrc/rtxDateTime.h ../../../rtxsrc/rtxEnum.h \
 ../../../rtxsrc/rtxFile.h ../../../rtxsrc/rtxPattern.h \
 ../../../rtxsrc/rtxReal.h ../../../rtxsrc/rtxUtil.h

ACSE-1Dec$(OBJ): ACSE-1Dec.cpp ACSE-1.h rtkey.h \
 ../../../rtpersrc/asn1PerCppTypes.h ../../../rtpersrc/asn1per.h \
 ../../../rtsrc/asn1type.h ../../../rtxsrc/rtxExternDefs.h \
 ../../../rtxsrc/rtxSList.h ../../../rtxsrc/rtxContext.h \
 ../../../rtxsrc/rtxDList.h ../../../rtxsrc/osSysTypes.h \
 ../../../rtxsrc/rtxCommonDefs.h ../../../rtxsrc/osMacros.h \
 ../../../rtxsrc/rtxStack.h ../../../rtxsrc/rtxUTF8.h \
 ../../../rtsrc/asn1tag.h ../../../rtsrc/asn1ErrCodes.h \
 ../../../rtsrc/rtExternDefs.h ../../../rtxsrc/rtxBitString.h \
 ../../../rtsrc/rtContext.h ../../../rtsrc/asn1CEvtHndlr.h \
 ../../../rtxsrc/rtxError.h ../../../rtxsrc/rtxErrCodes.h \
 ../../../rtxsrc/rtxMemory.h ../../../rtsrc/asn1CharSet.h \
 ../../../rtxsrc/rtxBitEncode.h ../../../rtxsrc/rtxBitDecode.h \
 ../../../rtxsrc/rtxBuffer.h ../../../rtxsrc/rtxDiagBitTrace.h \
 ../../../rtxsrc/rtxMemBuf.h ../../../rtxsrc/rtxPrintToStream.h \
 ../../../rtsrc/asn1CppTypes.h ../../../rtxsrc/rtxDiag.h \
 ../../../rtsrc/asn1CppEvtHndlr64.h ../../../rtsrc/asn1CppEvtHndlr.h \
 ../../../rtsrc/ASN1Context.h ../../../rtxsrc/OSRTContext.h \
 ../../../rtxsrc/OSRTMsgBuf.h ../../../rtxsrc/OSRTCtxtHolder.h \
 ../../../rtxsrc/OSRTCtxtHolderIF.h ../../../rtxsrc/OSRTMsgBufIF.h \
 ../../../rtsrc/ASN1TOctStr.h ../../../rtsrc/ASN1TOctStr64.h \
 ../../../rtsrc/ASN1TObjId.h Asn1External.h ../../../rtsrc/ASN1CBitStr.h \
 ../../../rtsrc/ASN1CSeqOfList.h ../../../rtxsrc/rtxCommon.h \
 ../../../rtxsrc/rtxBigInt.h ../../../rtxsrc/rtxCharStr.h \
 ../../../rtxsrc/rtxDateTime.h ../../../rtxsrc/rtxEnum.h \
 ../../../rtxsrc/rtxFile.h ../../../rtxsrc/rtxPattern.h \
 ../../../rtxsrc/rtxReal.h ../../../rtxsrc/rtxUtil.h

ACSE-1Enc$(OBJ): ACSE-1Enc.cpp ACSE-1.h rtkey.h \
 ../../../rtpersrc/asn1PerCppTypes.h ../../../rtpersrc/asn1per.h \
 ../../../rtsrc/asn1type.h ../../../rtxsrc/rtxExternDefs.h \
 ../../../rtxsrc/rtxSList.h ../../../rtxsrc/rtxContext.h \
 ../../../rtxsrc/rtxDList.h ../../../rtxsrc/osSysTypes.h \
 ../../../rtxsrc/rtxCommonDefs.h ../../../rtxsrc/osMacros.h \
 ../../../rtxsrc/rtxStack.h ../../../rtxsrc/rtxUTF8.h \
 ../../../rtsrc/asn1tag.h ../../../rtsrc/asn1ErrCodes.h \
 ../../../rtsrc/rtExternDefs.h ../../../rtxsrc/rtxBitString.h \
 ../../../rtsrc/rtContext.h ../../../rtsrc/asn1CEvtHndlr.h \
 ../../../rtxsrc/rtxError.h ../../../rtxsrc/rtxErrCodes.h \
 ../../../rtxsrc/rtxMemory.h ../../../rtsrc/asn1CharSet.h \
 ../../../rtxsrc/rtxBitEncode.h ../../../rtxsrc/rtxBitDecode.h \
 ../../../rtxsrc/rtxBuffer.h ../../../rtxsrc/rtxDiagBitTrace.h \
 ../../../rtxsrc/rtxMemBuf.h ../../../rtxsrc/rtxPrintToStream.h \
 ../../../rtsrc/asn1CppTypes.h ../../../rtxsrc/rtxDiag.h \
 ../../../rtsrc/asn1CppEvtHndlr64.h ../../../rtsrc/asn1CppEvtHndlr.h \
 ../../../rtsrc/ASN1Context.h ../../../rtxsrc/OSRTContext.h \
 ../../../rtxsrc/OSRTMsgBuf.h ../../../rtxsrc/OSRTCtxtHolder.h \
 ../../../rtxsrc/OSRTCtxtHolderIF.h ../../../rtxsrc/OSRTMsgBufIF.h \
 ../../../rtsrc/ASN1TOctStr.h ../../../rtsrc/ASN1TOctStr64.h \
 ../../../rtsrc/ASN1TObjId.h Asn1External.h ../../../rtsrc/ASN1CBitStr.h \
 ../../../rtsrc/ASN1CSeqOfList.h ../../../rtxsrc/rtxCommon.h \
 ../../../rtxsrc/rtxBigInt.h ../../../rtxsrc/rtxCharStr.h \
 ../../../rtxsrc/rtxDateTime.h ../../../rtxsrc/rtxEnum.h \
 ../../../rtxsrc/rtxFile.h ../../../rtxsrc/rtxPattern.h \
 ../../../rtxsrc/rtxReal.h ../../../rtxsrc/rtxUtil.h

ACSE-1Print$(OBJ): ACSE-1Print.cpp ACSE-1.h rtkey.h \
 ../../../rtpersrc/asn1PerCppTypes.h ../../../rtpersrc/asn1per.h \
 ../../../rtsrc/asn1type.h ../../../rtxsrc/rtxExternDefs.h \
 ../../../rtxsrc/rtxSList.h ../../../rtxsrc/rtxContext.h \
 ../../../rtxsrc/rtxDList.h ../../../rtxsrc/osSysTypes.h \
 ../../../rtxsrc/rtxCommonDefs.h ../../../rtxsrc/osMacros.h \
 ../../../rtxsrc/rtxStack.h ../../../rtxsrc/rtxUTF8.h \
 ../../../rtsrc/asn1tag.h ../../../rtsrc/asn1ErrCodes.h \
 ../../../rtsrc/rtExternDefs.h ../../../rtxsrc/rtxBitString.h \
 ../../../rtsrc/rtContext.h ../../../rtsrc/asn1CEvtHndlr.h \
 ../../../rtxsrc/rtxError.h ../../../rtxsrc/rtxErrCodes.h \
 ../../../rtxsrc/rtxMemory.h ../../../rtsrc/asn1CharSet.h \
 ../../../rtxsrc/rtxBitEncode.h ../../../rtxsrc/rtxBitDecode.h \
 ../../../rtxsrc/rtxBuffer.h ../../../rtxsrc/rtxDiagBitTrace.h \
 ../../../rtxsrc/rtxMemBuf.h ../../../rtxsrc/rtxPrintToStream.h \
 ../../../rtsrc/asn1CppTypes.h ../../../rtxsrc/rtxDiag.h \
 ../../../rtsrc/asn1CppEvtHndlr64.h ../../../rtsrc/asn1CppEvtHndlr.h \
 ../../../rtsrc/ASN1Context.h ../../../rtxsrc/OSRTContext.h \
 ../../../rtxsrc/OSRTMsgBuf.h ../../../rtxsrc/OSRTCtxtHolder.h \
 ../../../rtxsrc/OSRTCtxtHolderIF.h ../../../rtxsrc/OSRTMsgBufIF.h \
 ../../../rtsrc/ASN1TOctStr.h ../../../rtsrc/ASN1TOctStr64.h \
 ../../../rtsrc/ASN1TObjId.h Asn1External.h ../../../rtsrc/ASN1CBitStr.h \
 ../../../rtsrc/ASN1CSeqOfList.h ../../../rtsrc/rtPrint.h \
 ../../../rtxsrc/rtxPrint.h ../../../rtxsrc/rtxHexDump.h \
 ../../../rtxsrc/rtxCommon.h ../../../rtxsrc/rtxBigInt.h \
 ../../../rtxsrc/rtxCharStr.h ../../../rtxsrc/rtxDateTime.h \
 ../../../rtxsrc/rtxEnum.h ../../../rtxsrc/rtxFile.h \
 ../../../rtxsrc/rtxPattern.h ../../../rtxsrc/rtxReal.h \
 ../../../rtxsrc/rtxUtil.h

Asn1External$(OBJ): Asn1External.cpp ACSE-1.h rtkey.h \
 ../../../rtpersrc/asn1PerCppTypes.h ../../../rtpersrc/asn1per.h \
 ../../../rtsrc/asn1type.h ../../../rtxsrc/rtxExternDefs.h \
 ../../../rtxsrc/rtxSList.h ../../../rtxsrc/rtxContext.h \
 ../../../rtxsrc/rtxDList.h ../../../rtxsrc/osSysTypes.h \
 ../../../rtxsrc/rtxCommonDefs.h ../../../rtxsrc/osMacros.h \
 ../../../rtxsrc/rtxStack.h ../../../rtxsrc/rtxUTF8.h \
 ../../../rtsrc/asn1tag.h ../../../rtsrc/asn1ErrCodes.h \
 ../../../rtsrc/rtExternDefs.h ../../../rtxsrc/rtxBitString.h \
 ../../../rtsrc/rtContext.h ../../../rtsrc/asn1CEvtHndlr.h \
 ../../../rtxsrc/rtxError.h ../../../rtxsrc/rtxErrCodes.h \
 ../../../rtxsrc/rtxMemory.h ../../../rtsrc/asn1CharSet.h \
 ../../../rtxsrc/rtxBitEncode.h ../../../rtxsrc/rtxBitDecode.h \
 ../../../rtxsrc/rtxBuffer.h ../../../rtxsrc/rtxDiagBitTrace.h \
 ../../../rtxsrc/rtxMemBuf.h ../../../rtxsrc/rtxPrintToStream.h \
 ../../../rtsrc/asn1CppTypes.h ../../../rtxsrc/rtxDiag.h \
 ../../../rtsrc/asn1CppEvtHndlr64.h ../../../rtsrc/asn1CppEvtHndlr.h \
 ../../../rtsrc/ASN1Context.h ../../../rtxsrc/OSRTContext.h \
 ../../../rtxsrc/OSRTMsgBuf.h ../../../rtxsrc/OSRTCtxtHolder.h \
 ../../../rtxsrc/OSRTCtxtHolderIF.h ../../../rtxsrc/OSRTMsgBufIF.h \
 ../../../rtsrc/ASN1TOctStr.h ../../../rtsrc/ASN1TOctStr64.h \
 ../../../rtsrc/ASN1TObjId.h Asn1External.h ../../../rtsrc/ASN1CBitStr.h \
 ../../../rtsrc/ASN1CSeqOfList.h ../../../rtsrc/rtPrint.h \
 ../../../rtxsrc/rtxPrint.h ../../../rtxsrc/rtxHexDump.h \
 ../../../rtxsrc/rtxCommon.h ../../../rtxsrc/rtxBigInt.h \
 ../../../rtxsrc/rtxCharStr.h ../../../rtxsrc/rtxDateTime.h \
 ../../../rtxsrc/rtxEnum.h ../../../rtxsrc/rtxFile.h \
 ../../../rtxsrc/rtxPattern.h ../../../rtxsrc/rtxReal.h \
 ../../../rtxsrc/rtxUtil.h

CMMessageSetVersion1$(OBJ): CMMessageSetVersion1.cpp CMMessageSetVersion1.h \
 rtkey.h ../../../rtpersrc/asn1PerCppTypes.h ../../../rtpersrc/asn1per.h \
 ../../../rtsrc/asn1type.h ../../../rtxsrc/rtxExternDefs.h \
 ../../../rtxsrc/rtxSList.h ../../../rtxsrc/rtxContext.h \
 ../../../rtxsrc/rtxDList.h ../../../rtxsrc/osSysTypes.h \
 ../../../rtxsrc/rtxCommonDefs.h ../../../rtxsrc/osMacros.h \
 ../../../rtxsrc/rtxStack.h ../../../rtxsrc/rtxUTF8.h \
 ../../../rtsrc/asn1tag.h ../../../rtsrc/asn1ErrCodes.h \
 ../../../rtsrc/rtExternDefs.h ../../../rtxsrc/rtxBitString.h \
 ../../../rtsrc/rtContext.h ../../../rtsrc/asn1CEvtHndlr.h \
 ../../../rtxsrc/rtxError.h ../../../rtxsrc/rtxErrCodes.h \
 ../../../rtxsrc/rtxMemory.h ../../../rtsrc/asn1CharSet.h \
 ../../../rtxsrc/rtxBitEncode.h ../../../rtxsrc/rtxBitDecode.h \
 ../../../rtxsrc/rtxBuffer.h ../../../rtxsrc/rtxDiagBitTrace.h \
 ../../../rtxsrc/rtxMemBuf.h ../../../rtxsrc/rtxPrintToStream.h \
 ../../../rtsrc/asn1CppTypes.h ../../../rtxsrc/rtxDiag.h \
 ../../../rtsrc/asn1CppEvtHndlr64.h ../../../rtsrc/asn1CppEvtHndlr.h \
 ../../../rtsrc/ASN1Context.h ../../../rtxsrc/OSRTContext.h \
 ../../../rtxsrc/OSRTMsgBuf.h ../../../rtxsrc/OSRTCtxtHolder.h \
 ../../../rtxsrc/OSRTCtxtHolderIF.h ../../../rtxsrc/OSRTMsgBufIF.h \
 ../../../rtsrc/ASN1TOctStr.h ../../../rtsrc/ASN1TOctStr64.h \
 ../../../rtsrc/ASN1TObjId.h ../../../rtsrc/ASN1CSeqOfList.h \
 ../../../rtxsrc/rtxCommon.h ../../../rtxsrc/rtxBigInt.h \
 ../../../rtxsrc/rtxCharStr.h ../../../rtxsrc/rtxDateTime.h \
 ../../../rtxsrc/rtxEnum.h ../../../rtxsrc/rtxFile.h \
 ../../../rtxsrc/rtxPattern.h ../../../rtxsrc/rtxReal.h \
 ../../../rtxsrc/rtxUtil.h

CMMessageSetVersion1Dec$(OBJ): CMMessageSetVersion1Dec.cpp \
 CMMessageSetVersion1.h rtkey.h ../../../rtpersrc/asn1PerCppTypes.h \
 ../../../rtpersrc/asn1per.h ../../../rtsrc/asn1type.h \
 ../../../rtxsrc/rtxExternDefs.h ../../../rtxsrc/rtxSList.h \
 ../../../rtxsrc/rtxContext.h ../../../rtxsrc/rtxDList.h \
 ../../../rtxsrc/osSysTypes.h ../../../rtxsrc/rtxCommonDefs.h \
 ../../../rtxsrc/osMacros.h ../../../rtxsrc/rtxStack.h \
 ../../../rtxsrc/rtxUTF8.h ../../../rtsrc/asn1tag.h \
 ../../../rtsrc/asn1ErrCodes.h ../../../rtsrc/rtExternDefs.h \
 ../../../rtxsrc/rtxBitString.h ../../../rtsrc/rtContext.h \
 ../../../rtsrc/asn1CEvtHndlr.h ../../../rtxsrc/rtxError.h \
 ../../../rtxsrc/rtxErrCodes.h ../../../rtxsrc/rtxMemory.h \
 ../../../rtsrc/asn1CharSet.h ../../../rtxsrc/rtxBitEncode.h \
 ../../../rtxsrc/rtxBitDecode.h ../../../rtxsrc/rtxBuffer.h \
 ../../../rtxsrc/rtxDiagBitTrace.h ../../../rtxsrc/rtxMemBuf.h \
 ../../../rtxsrc/rtxPrintToStream.h ../../../rtsrc/asn1CppTypes.h \
 ../../../rtxsrc/rtxDiag.h ../../../rtsrc/asn1CppEvtHndlr64.h \
 ../../../rtsrc/asn1CppEvtHndlr.h ../../../rtsrc/ASN1Context.h \
 ../../../rtxsrc/OSRTContext.h ../../../rtxsrc/OSRTMsgBuf.h \
 ../../../rtxsrc/OSRTCtxtHolder.h ../../../rtxsrc/OSRTCtxtHolderIF.h \
 ../../../rtxsrc/OSRTMsgBufIF.h ../../../rtsrc/ASN1TOctStr.h \
 ../../../rtsrc/ASN1TOctStr64.h ../../../rtsrc/ASN1TObjId.h \
 ../../../rtsrc/ASN1CSeqOfList.h ../../../rtxsrc/rtxCommon.h \
 ../../../rtxsrc/rtxBigInt.h ../../../rtxsrc/rtxCharStr.h \
 ../../../rtxsrc/rtxDateTime.h ../../../rtxsrc/rtxEnum.h \
 ../../../rtxsrc/rtxFile.h ../../../rtxsrc/rtxPattern.h \
 ../../../rtxsrc/rtxReal.h ../../../rtxsrc/rtxUtil.h

CMMessageSetVersion1Enc$(OBJ): CMMessageSetVersion1Enc.cpp \
 CMMessageSetVersion1.h rtkey.h ../../../rtpersrc/asn1PerCppTypes.h \
 ../../../rtpersrc/asn1per.h ../../../rtsrc/asn1type.h \
 ../../../rtxsrc/rtxExternDefs.h ../../../rtxsrc/rtxSList.h \
 ../../../rtxsrc/rtxContext.h ../../../rtxsrc/rtxDList.h \
 ../../../rtxsrc/osSysTypes.h ../../../rtxsrc/rtxCommonDefs.h \
 ../../../rtxsrc/osMacros.h ../../../rtxsrc/rtxStack.h \
 ../../../rtxsrc/rtxUTF8.h ../../../rtsrc/asn1tag.h \
 ../../../rtsrc/asn1ErrCodes.h ../../../rtsrc/rtExternDefs.h \
 ../../../rtxsrc/rtxBitString.h ../../../rtsrc/rtContext.h \
 ../../../rtsrc/asn1CEvtHndlr.h ../../../rtxsrc/rtxError.h \
 ../../../rtxsrc/rtxErrCodes.h ../../../rtxsrc/rtxMemory.h \
 ../../../rtsrc/asn1CharSet.h ../../../rtxsrc/rtxBitEncode.h \
 ../../../rtxsrc/rtxBitDecode.h ../../../rtxsrc/rtxBuffer.h \
 ../../../rtxsrc/rtxDiagBitTrace.h ../../../rtxsrc/rtxMemBuf.h \
 ../../../rtxsrc/rtxPrintToStream.h ../../../rtsrc/asn1CppTypes.h \
 ../../../rtxsrc/rtxDiag.h ../../../rtsrc/asn1CppEvtHndlr64.h \
 ../../../rtsrc/asn1CppEvtHndlr.h ../../../rtsrc/ASN1Context.h \
 ../../../rtxsrc/OSRTContext.h ../../../rtxsrc/OSRTMsgBuf.h \
 ../../../rtxsrc/OSRTCtxtHolder.h ../../../rtxsrc/OSRTCtxtHolderIF.h \
 ../../../rtxsrc/OSRTMsgBufIF.h ../../../rtsrc/ASN1TOctStr.h \
 ../../../rtsrc/ASN1TOctStr64.h ../../../rtsrc/ASN1TObjId.h \
 ../../../rtsrc/ASN1CSeqOfList.h ../../../rtxsrc/rtxCommon.h \
 ../../../rtxsrc/rtxBigInt.h ../../../rtxsrc/rtxCharStr.h \
 ../../../rtxsrc/rtxDateTime.h ../../../rtxsrc/rtxEnum.h \
 ../../../rtxsrc/rtxFile.h ../../../rtxsrc/rtxPattern.h \
 ../../../rtxsrc/rtxReal.h ../../../rtxsrc/rtxUtil.h

CMMessageSetVersion1Print$(OBJ): CMMessageSetVersion1Print.cpp \
 CMMessageSetVersion1.h rtkey.h ../../../rtpersrc/asn1PerCppTypes.h \
 ../../../rtpersrc/asn1per.h ../../../rtsrc/asn1type.h \
 ../../../rtxsrc/rtxExternDefs.h ../../../rtxsrc/rtxSList.h \
 ../../../rtxsrc/rtxContext.h ../../../rtxsrc/rtxDList.h \
 ../../../rtxsrc/osSysTypes.h ../../../rtxsrc/rtxCommonDefs.h \
 ../../../rtxsrc/osMacros.h ../../../rtxsrc/rtxStack.h \
 ../../../rtxsrc/rtxUTF8.h ../../../rtsrc/asn1tag.h \
 ../../../rtsrc/asn1ErrCodes.h ../../../rtsrc/rtExternDefs.h \
 ../../../rtxsrc/rtxBitString.h ../../../rtsrc/rtContext.h \
 ../../../rtsrc/asn1CEvtHndlr.h ../../../rtxsrc/rtxError.h \
 ../../../rtxsrc/rtxErrCodes.h ../../../rtxsrc/rtxMemory.h \
 ../../../rtsrc/asn1CharSet.h ../../../rtxsrc/rtxBitEncode.h \
 ../../../rtxsrc/rtxBitDecode.h ../../../rtxsrc/rtxBuffer.h \
 ../../../rtxsrc/rtxDiagBitTrace.h ../../../rtxsrc/rtxMemBuf.h \
 ../../../rtxsrc/rtxPrintToStream.h ../../../rtsrc/asn1CppTypes.h \
 ../../../rtxsrc/rtxDiag.h ../../../rtsrc/asn1CppEvtHndlr64.h \
 ../../../rtsrc/asn1CppEvtHndlr.h ../../../rtsrc/ASN1Context.h \
 ../../../rtxsrc/OSRTContext.h ../../../rtxsrc/OSRTMsgBuf.h \
 ../../../rtxsrc/OSRTCtxtHolder.h ../../../rtxsrc/OSRTCtxtHolderIF.h \
 ../../../rtxsrc/OSRTMsgBufIF.h ../../../rtsrc/ASN1TOctStr.h \
 ../../../rtsrc/ASN1TOctStr64.h ../../../rtsrc/ASN1TObjId.h \
 ../../../rtsrc/ASN1CSeqOfList.h ../../../rtsrc/rtPrint.h \
 ../../../rtxsrc/rtxPrint.h ../../../rtxsrc/rtxHexDump.h \
 ../../../rtxsrc/rtxCommon.h ../../../rtxsrc/rtxBigInt.h \
 ../../../rtxsrc/rtxCharStr.h ../../../rtxsrc/rtxDateTime.h \
 ../../../rtxsrc/rtxEnum.h ../../../rtxsrc/rtxFile.h \
 ../../../rtxsrc/rtxPattern.h ../../../rtxsrc/rtxReal.h \
 ../../../rtxsrc/rtxUtil.h

reader$(OBJ): reader.cpp ACSE-1.h rtkey.h ../../../rtpersrc/asn1PerCppTypes.h \
 ../../../rtpersrc/asn1per.h ../../../rtsrc/asn1type.h \
 ../../../rtxsrc/rtxExternDefs.h ../../../rtxsrc/rtxSList.h \
 ../../../rtxsrc/rtxContext.h ../../../rtxsrc/rtxDList.h \
 ../../../rtxsrc/osSysTypes.h ../../../rtxsrc/rtxCommonDefs.h \
 ../../../rtxsrc/osMacros.h ../../../rtxsrc/rtxStack.h \
 ../../../rtxsrc/rtxUTF8.h ../../../rtsrc/asn1tag.h \
 ../../../rtsrc/asn1ErrCodes.h ../../../rtsrc/rtExternDefs.h \
 ../../../rtxsrc/rtxBitString.h ../../../rtsrc/rtContext.h \
 ../../../rtsrc/asn1CEvtHndlr.h ../../../rtxsrc/rtxError.h \
 ../../../rtxsrc/rtxErrCodes.h ../../../rtxsrc/rtxMemory.h \
 ../../../rtsrc/asn1CharSet.h ../../../rtxsrc/rtxBitEncode.h \
 ../../../rtxsrc/rtxBitDecode.h ../../../rtxsrc/rtxBuffer.h \
 ../../../rtxsrc/rtxDiagBitTrace.h ../../../rtxsrc/rtxMemBuf.h \
 ../../../rtxsrc/rtxPrintToStream.h ../../../rtsrc/asn1CppTypes.h \
 ../../../rtxsrc/rtxDiag.h ../../../rtsrc/asn1CppEvtHndlr64.h \
 ../../../rtsrc/asn1CppEvtHndlr.h ../../../rtsrc/ASN1Context.h \
 ../../../rtxsrc/OSRTContext.h ../../../rtxsrc/OSRTMsgBuf.h \
 ../../../rtxsrc/OSRTCtxtHolder.h ../../../rtxsrc/OSRTCtxtHolderIF.h \
 ../../../rtxsrc/OSRTMsgBufIF.h ../../../rtsrc/ASN1TOctStr.h \
 ../../../rtsrc/ASN1TOctStr64.h ../../../rtsrc/ASN1TObjId.h \
 Asn1External.h ../../../rtsrc/ASN1CBitStr.h \
 ../../../rtsrc/ASN1CSeqOfList.h CMMessageSetVersion1.h \
 ../../../rtxsrc/rtxMemLeakCheck.h

writer$(OBJ): writer.cpp ACSE-1.h rtkey.h ../../../rtpersrc/asn1PerCppTypes.h \
 ../../../rtpersrc/asn1per.h ../../../rtsrc/asn1type.h \
 ../../../rtxsrc/rtxExternDefs.h ../../../rtxsrc/rtxSList.h \
 ../../../rtxsrc/rtxContext.h ../../../rtxsrc/rtxDList.h \
 ../../../rtxsrc/osSysTypes.h ../../../rtxsrc/rtxCommonDefs.h \
 ../../../rtxsrc/osMacros.h ../../../rtxsrc/rtxStack.h \
 ../../../rtxsrc/rtxUTF8.h ../../../rtsrc/asn1tag.h \
 ../../../rtsrc/asn1ErrCodes.h ../../../rtsrc/rtExternDefs.h \
 ../../../rtxsrc/rtxBitString.h ../../../rtsrc/rtContext.h \
 ../../../rtsrc/asn1CEvtHndlr.h ../../../rtxsrc/rtxError.h \
 ../../../rtxsrc/rtxErrCodes.h ../../../rtxsrc/rtxMemory.h \
 ../../../rtsrc/asn1CharSet.h ../../../rtxsrc/rtxBitEncode.h \
 ../../../rtxsrc/rtxBitDecode.h ../../../rtxsrc/rtxBuffer.h \
 ../../../rtxsrc/rtxDiagBitTrace.h ../../../rtxsrc/rtxMemBuf.h \
 ../../../rtxsrc/rtxPrintToStream.h ../../../rtsrc/asn1CppTypes.h \
 ../../../rtxsrc/rtxDiag.h ../../../rtsrc/asn1CppEvtHndlr64.h \
 ../../../rtsrc/asn1CppEvtHndlr.h ../../../rtsrc/ASN1Context.h \
 ../../../rtxsrc/OSRTContext.h ../../../rtxsrc/OSRTMsgBuf.h \
 ../../../rtxsrc/OSRTCtxtHolder.h ../../../rtxsrc/OSRTCtxtHolderIF.h \
 ../../../rtxsrc/OSRTMsgBufIF.h ../../../rtsrc/ASN1TOctStr.h \
 ../../../rtsrc/ASN1TOctStr64.h ../../../rtsrc/ASN1TObjId.h \
 Asn1External.h ../../../rtsrc/ASN1CBitStr.h \
 ../../../rtsrc/ASN1CSeqOfList.h CMMessageSetVersion1.h \
 ../../../rtxsrc/rtxMemLeakCheck.h ../../../rtxsrc/rtxFile.h

CMMessageSetVersion1.cpp CMMessageSetVersion1Enc.cpp \
CMMessageSetVersion1Dec.cpp CMMessageSetVersion1.h \
CMMessageSetVersion1Print.cpp : cm-v1.asn $(ASN1C)
	$(ASN1C) cm-v1.asn -c++ -uper -trace -print -strict-size -x64

ACSE-1.cpp ACSE-1Enc.cpp ACSE-1Dec.cpp ACSE-1Print.cpp ACSE-1.h : \
acse-1.asn $(ASN1C)
	$(ASN1C) acse-1.asn -c++ -uper -trace -print -strict-size -x64

depends:
	gcc -E -MM -I../../.. *.cpp

clean :
	$(RM) CMMessageSetVersion1*.cpp
	$(RM) CMMessageSetVersion1.h
	$(RM) A*.cpp
	$(RM) A*.h
	$(RM) rtkey.h
	$(RM) message.dat
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM_MSVC_FILES)
	$(RM) *.lib
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
