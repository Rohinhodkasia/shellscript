include ../../platform.mk
include ../../../bench.mk

all : outdirs bench$(EXE)

OBJECTS = MEDIA-GATEWAY-CONTROL$(OBJ) \
MEDIA-GATEWAY-CONTROLPrint$(OBJ) $(BENCHOBJ)

ACSRCFILES = MEDIA-GATEWAY-CONTROL.c \
MEDIA-GATEWAY-CONTROL.h MEDIA-GATEWAY-CONTROLPrint.c

outdirs :
	$(MKDIR) $(OBJDIR)

bench$(EXE) : bench$(OBJ) $(OBJECTS) $(LIBDIR)/$(PERLIBNAME) $(LIBDIR)/$(RTLIBNAME)
	$(LINK) bench$(OBJ) $(OBJECTS) $(LINKOPT) $(LPATHS) $(PSLIBS)

bench$(OBJ): bench.c MEDIA-GATEWAY-CONTROL.h rtkey.h \
 ../../../rtpersrc/asn1per.h ../../../rtsrc/asn1type.h \
 ../../../rtxsrc/rtxExternDefs.h ../../../rtxsrc/rtxSList.h \
 ../../../rtxsrc/rtxContext.h ../../../rtxsrc/rtxDList.h \
 ../../../rtxsrc/osSysTypes.h ../../../rtxsrc/rtxCommonDefs.h \
 ../../../rtxsrc/osMacros.h ../../../rtxsrc/rtxStack.h \
 ../../../rtxsrc/rtxUTF8.h ../../../rtsrc/asn1tag.h \
 ../../../rtsrc/asn1ErrCodes.h ../../../rtsrc/asn1version.h \
 ../../../rtsrc/rtExternDefs.h ../../../rtxsrc/rtxBitString.h \
 ../../../rtsrc/rtContext.h ../../../rtsrc/asn1CEvtHndlr.h \
 ../../../rtxsrc/rtxError.h ../../../rtxsrc/rtxErrCodes.h \
 ../../../rtxsrc/rtxMemory.h ../../../rtsrc/asn1CharSet.h \
 ../../../rtxsrc/rtxBitEncode.h ../../../rtxsrc/rtxBitDecode.h \
 ../../../rtxsrc/rtxBuffer.h ../../../rtxsrc/rtxDiagBitTrace.h \
 ../../../rtxsrc/rtxMemBuf.h ../../../rtxsrc/rtxPrintToStream.h \
 ../../../rtxsrc/rtxBench.h ../../../rtxsrc/rtxDiag.h

MEDIA-GATEWAY-CONTROL$(OBJ): MEDIA-GATEWAY-CONTROL.c MEDIA-GATEWAY-CONTROL.h \
 rtkey.h ../../../rtpersrc/asn1per.h ../../../rtsrc/asn1type.h \
 ../../../rtxsrc/rtxExternDefs.h ../../../rtxsrc/rtxSList.h \
 ../../../rtxsrc/rtxContext.h ../../../rtxsrc/rtxDList.h \
 ../../../rtxsrc/osSysTypes.h ../../../rtxsrc/rtxCommonDefs.h \
 ../../../rtxsrc/osMacros.h ../../../rtxsrc/rtxStack.h \
 ../../../rtxsrc/rtxUTF8.h ../../../rtsrc/asn1tag.h \
 ../../../rtsrc/asn1ErrCodes.h ../../../rtsrc/asn1version.h \
 ../../../rtsrc/rtExternDefs.h ../../../rtxsrc/rtxBitString.h \
 ../../../rtsrc/rtContext.h ../../../rtsrc/asn1CEvtHndlr.h \
 ../../../rtxsrc/rtxError.h ../../../rtxsrc/rtxErrCodes.h \
 ../../../rtxsrc/rtxMemory.h ../../../rtsrc/asn1CharSet.h \
 ../../../rtxsrc/rtxBitEncode.h ../../../rtxsrc/rtxBitDecode.h \
 ../../../rtxsrc/rtxBuffer.h ../../../rtxsrc/rtxDiagBitTrace.h \
 ../../../rtxsrc/rtxMemBuf.h ../../../rtxsrc/rtxPrintToStream.h \
 ../../../rtxsrc/rtxCommon.h ../../../rtxsrc/rtxBigInt.h \
 ../../../rtxsrc/rtxCharStr.h ../../../rtxsrc/rtxDateTime.h \
 ../../../rtxsrc/rtxDiag.h ../../../rtxsrc/rtxEnum.h \
 ../../../rtxsrc/rtxFile.h ../../../rtxsrc/rtxPattern.h \
 ../../../rtxsrc/rtxReal.h ../../../rtxsrc/rtxUtil.h

MEDIA-GATEWAY-CONTROLPrint$(OBJ): MEDIA-GATEWAY-CONTROLPrint.c \
 MEDIA-GATEWAY-CONTROL.h rtkey.h ../../../rtpersrc/asn1per.h \
 ../../../rtsrc/asn1type.h ../../../rtxsrc/rtxExternDefs.h \
 ../../../rtxsrc/rtxSList.h ../../../rtxsrc/rtxContext.h \
 ../../../rtxsrc/rtxDList.h ../../../rtxsrc/osSysTypes.h \
 ../../../rtxsrc/rtxCommonDefs.h ../../../rtxsrc/osMacros.h \
 ../../../rtxsrc/rtxStack.h ../../../rtxsrc/rtxUTF8.h \
 ../../../rtsrc/asn1tag.h ../../../rtsrc/asn1ErrCodes.h \
 ../../../rtsrc/asn1version.h ../../../rtsrc/rtExternDefs.h \
 ../../../rtxsrc/rtxBitString.h ../../../rtsrc/rtContext.h \
 ../../../rtsrc/asn1CEvtHndlr.h ../../../rtxsrc/rtxError.h \
 ../../../rtxsrc/rtxErrCodes.h ../../../rtxsrc/rtxMemory.h \
 ../../../rtsrc/asn1CharSet.h ../../../rtxsrc/rtxBitEncode.h \
 ../../../rtxsrc/rtxBitDecode.h ../../../rtxsrc/rtxBuffer.h \
 ../../../rtxsrc/rtxDiagBitTrace.h ../../../rtxsrc/rtxMemBuf.h \
 ../../../rtxsrc/rtxPrintToStream.h ../../../rtsrc/rtPrint.h \
 ../../../rtxsrc/rtxPrint.h ../../../rtxsrc/rtxCommon.h \
 ../../../rtxsrc/rtxBigInt.h ../../../rtxsrc/rtxCharStr.h \
 ../../../rtxsrc/rtxDateTime.h ../../../rtxsrc/rtxDiag.h \
 ../../../rtxsrc/rtxEnum.h ../../../rtxsrc/rtxFile.h \
 ../../../rtxsrc/rtxPattern.h ../../../rtxsrc/rtxReal.h \
 ../../../rtxsrc/rtxUtil.h

$(ACSRCFILES) : megaco.asn
	$(ASN1C) megaco.asn -c -per -compact -cfile MEDIA-GATEWAY-CONTROL.c \
	  -print MEDIA-GATEWAY-CONTROLPrint.c

depends: $(ACSRCFILES)
	gcc -E -MM bench.c $(IPATHS)
	gcc -E -MM MEDIA-GATEWAY-CONTROL.c $(IPATHS)
	gcc -E -MM MEDIA-GATEWAY-CONTROLPrint.c $(IPATHS)

clean:
	$(RM) MEDIA-GATEWAY-CONTROL*.c
	$(RM) MEDIA-GATEWAY-CONTROL.h
	$(RM) *$(OBJ)
	$(RM) *.exp
	$(RM) *.pdb
	$(RM) *.map
	$(RM) *.lib
	$(RM) *~
	$(RM) bench$(EXE)
	$(RM) rtkey.h

