# makefile to build generated files

include ../../platform.mk
include ../../../sample.mk

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)c$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
PERSRCDIR = $(OSROOTDIR)$(PS)rtpersrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(PERSRCDIR)$(PS)asn1per.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_) -D_TRACE
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I../../../specs/SUPL/v2_1 -I$(RTSRCDIR) \
-I$(PERSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1per$(A) $(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1per$(LLAEXT) $(LLPFX)asn1rt$(LLAEXT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
ULP$(OBJ) \
SUPL-INIT$(OBJ) \
ULP-Components$(OBJ) \
ULP-Version-2-parameter-extensions$(OBJ) \
ULP-Version-2-message-extensions$(OBJ) \
Ver2-ULP-Components$(OBJ) \
SUPL-TRIGGERED-START$(OBJ) \
ULP-Version-3-message-extensions$(OBJ) \
ULP-Version-3-parameter-extensions$(OBJ) \
SUPL-START$(OBJ) \
OMA-LPPE$(OBJ) \
SUPL-RESPONSE$(OBJ) \
SUPL-POS-INIT$(OBJ) \
SUPL-POS$(OBJ) \
SUPL-END$(OBJ) \
SUPL-AUTH-REQ$(OBJ) \
SUPL-AUTH-RESP$(OBJ) \
SUPL-TRIGGERED-RESPONSE$(OBJ) \
SUPL-TRIGGERED-STOP$(OBJ) \
SUPL-NOTIFY$(OBJ) \
SUPL-NOTIFY-RESPONSE$(OBJ) \
SUPL-SET-INIT$(OBJ) \
SUPL-REPORT$(OBJ)

ENCOBJECTS =  \
ULPEnc$(OBJ) \
SUPL-INITEnc$(OBJ) \
ULP-ComponentsEnc$(OBJ) \
ULP-Version-2-parameter-extensionsEnc$(OBJ) \
ULP-Version-2-message-extensionsEnc$(OBJ) \
Ver2-ULP-ComponentsEnc$(OBJ) \
SUPL-TRIGGERED-STARTEnc$(OBJ) \
ULP-Version-3-message-extensionsEnc$(OBJ) \
ULP-Version-3-parameter-extensionsEnc$(OBJ) \
SUPL-STARTEnc$(OBJ) \
OMA-LPPEEnc$(OBJ) \
SUPL-RESPONSEEnc$(OBJ) \
SUPL-POS-INITEnc$(OBJ) \
SUPL-POSEnc$(OBJ) \
SUPL-ENDEnc$(OBJ) \
SUPL-AUTH-REQEnc$(OBJ) \
SUPL-AUTH-RESPEnc$(OBJ) \
SUPL-TRIGGERED-RESPONSEEnc$(OBJ) \
SUPL-TRIGGERED-STOPEnc$(OBJ) \
SUPL-NOTIFYEnc$(OBJ) \
SUPL-NOTIFY-RESPONSEEnc$(OBJ) \
SUPL-SET-INITEnc$(OBJ) \
SUPL-REPORTEnc$(OBJ)

DECOBJECTS =  \
ULPDec$(OBJ) \
SUPL-INITDec$(OBJ) \
ULP-ComponentsDec$(OBJ) \
ULP-Version-2-parameter-extensionsDec$(OBJ) \
ULP-Version-2-message-extensionsDec$(OBJ) \
Ver2-ULP-ComponentsDec$(OBJ) \
SUPL-TRIGGERED-STARTDec$(OBJ) \
ULP-Version-3-message-extensionsDec$(OBJ) \
ULP-Version-3-parameter-extensionsDec$(OBJ) \
SUPL-STARTDec$(OBJ) \
OMA-LPPEDec$(OBJ) \
SUPL-RESPONSEDec$(OBJ) \
SUPL-POS-INITDec$(OBJ) \
SUPL-POSDec$(OBJ) \
SUPL-ENDDec$(OBJ) \
SUPL-AUTH-REQDec$(OBJ) \
SUPL-AUTH-RESPDec$(OBJ) \
SUPL-TRIGGERED-RESPONSEDec$(OBJ) \
SUPL-TRIGGERED-STOPDec$(OBJ) \
SUPL-NOTIFYDec$(OBJ) \
SUPL-NOTIFY-RESPONSEDec$(OBJ) \
SUPL-SET-INITDec$(OBJ) \
SUPL-REPORTDec$(OBJ)

PRTOBJECTS =  \
ULPPrint$(OBJ) \
SUPL-INITPrint$(OBJ) \
ULP-ComponentsPrint$(OBJ) \
ULP-Version-2-parameter-extensionsPrint$(OBJ) \
ULP-Version-2-message-extensionsPrint$(OBJ) \
Ver2-ULP-ComponentsPrint$(OBJ) \
SUPL-TRIGGERED-STARTPrint$(OBJ) \
ULP-Version-3-message-extensionsPrint$(OBJ) \
ULP-Version-3-parameter-extensionsPrint$(OBJ) \
SUPL-STARTPrint$(OBJ) \
OMA-LPPEPrint$(OBJ) \
SUPL-RESPONSEPrint$(OBJ) \
SUPL-POS-INITPrint$(OBJ) \
SUPL-POSPrint$(OBJ) \
SUPL-ENDPrint$(OBJ) \
SUPL-AUTH-REQPrint$(OBJ) \
SUPL-AUTH-RESPPrint$(OBJ) \
SUPL-TRIGGERED-RESPONSEPrint$(OBJ) \
SUPL-TRIGGERED-STOPPrint$(OBJ) \
SUPL-NOTIFYPrint$(OBJ) \
SUPL-NOTIFY-RESPONSEPrint$(OBJ) \
SUPL-SET-INITPrint$(OBJ) \
SUPL-REPORTPrint$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(PRTOBJECTS)  \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(PRTOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(PRTOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)ULP.h $(HFILESDIR)$(PS)SUPL-INIT.h  \
$(HFILESDIR)$(PS)ULP-Components.h $(HFILESDIR)$(PS)ULP-Version-2-parameter-extensions.h  \
$(HFILESDIR)$(PS)ULP-Version-2-message-extensions.h $(HFILESDIR)$(PS)Ver2-ULP-Components.h  \
$(HFILESDIR)$(PS)SUPL-TRIGGERED-START.h $(HFILESDIR)$(PS)ULP-Version-3-message-extensions.h  \
$(HFILESDIR)$(PS)ULP-Version-3-parameter-extensions.h $(HFILESDIR)$(PS)SUPL-START.h $(HFILESDIR)$(PS)OMA-LPPE.h  \
$(HFILESDIR)$(PS)SUPL-RESPONSE.h $(HFILESDIR)$(PS)SUPL-POS-INIT.h $(HFILESDIR)$(PS)SUPL-POS.h  \
$(HFILESDIR)$(PS)SUPL-END.h $(HFILESDIR)$(PS)SUPL-AUTH-REQ.h $(HFILESDIR)$(PS)SUPL-AUTH-RESP.h  \
$(HFILESDIR)$(PS)SUPL-TRIGGERED-RESPONSE.h $(HFILESDIR)$(PS)SUPL-TRIGGERED-STOP.h $(HFILESDIR)$(PS)SUPL-NOTIFY.h  \
$(HFILESDIR)$(PS)SUPL-NOTIFY-RESPONSE.h $(HFILESDIR)$(PS)SUPL-SET-INIT.h $(HFILESDIR)$(PS)SUPL-REPORT.h  \
$(HFILESDIR)$(PS)rtkey.h $(HFILES)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
$(SRCDIR)/ULPEnc.c \
$(SRCDIR)/ULPDec.c \
$(SRCDIR)/ULP.c \
$(SRCDIR)/ULPPrint.c \
$(HFILESDIR)$(PS)ULP.h \
$(SRCDIR)/SUPL-INITEnc.c \
$(SRCDIR)/SUPL-INITDec.c \
$(SRCDIR)/SUPL-INIT.c \
$(SRCDIR)/SUPL-INITPrint.c \
$(HFILESDIR)$(PS)SUPL-INIT.h \
$(SRCDIR)/ULP-ComponentsEnc.c \
$(SRCDIR)/ULP-ComponentsDec.c \
$(SRCDIR)/ULP-Components.c \
$(SRCDIR)/ULP-ComponentsPrint.c \
$(HFILESDIR)$(PS)ULP-Components.h \
$(SRCDIR)/ULP-Version-2-parameter-extensionsEnc.c \
$(SRCDIR)/ULP-Version-2-parameter-extensionsDec.c \
$(SRCDIR)/ULP-Version-2-parameter-extensions.c \
$(SRCDIR)/ULP-Version-2-parameter-extensionsPrint.c \
$(HFILESDIR)$(PS)ULP-Version-2-parameter-extensions.h \
$(SRCDIR)/ULP-Version-2-message-extensionsEnc.c \
$(SRCDIR)/ULP-Version-2-message-extensionsDec.c \
$(SRCDIR)/ULP-Version-2-message-extensions.c \
$(SRCDIR)/ULP-Version-2-message-extensionsPrint.c \
$(HFILESDIR)$(PS)ULP-Version-2-message-extensions.h \
$(SRCDIR)/Ver2-ULP-ComponentsEnc.c \
$(SRCDIR)/Ver2-ULP-ComponentsDec.c \
$(SRCDIR)/Ver2-ULP-Components.c \
$(SRCDIR)/Ver2-ULP-ComponentsPrint.c \
$(HFILESDIR)$(PS)Ver2-ULP-Components.h \
$(SRCDIR)/SUPL-TRIGGERED-STARTEnc.c \
$(SRCDIR)/SUPL-TRIGGERED-STARTDec.c \
$(SRCDIR)/SUPL-TRIGGERED-START.c \
$(SRCDIR)/SUPL-TRIGGERED-STARTPrint.c \
$(HFILESDIR)$(PS)SUPL-TRIGGERED-START.h \
$(SRCDIR)/ULP-Version-3-message-extensionsEnc.c \
$(SRCDIR)/ULP-Version-3-message-extensionsDec.c \
$(SRCDIR)/ULP-Version-3-message-extensions.c \
$(SRCDIR)/ULP-Version-3-message-extensionsPrint.c \
$(HFILESDIR)$(PS)ULP-Version-3-message-extensions.h \
$(SRCDIR)/ULP-Version-3-parameter-extensionsEnc.c \
$(SRCDIR)/ULP-Version-3-parameter-extensionsDec.c \
$(SRCDIR)/ULP-Version-3-parameter-extensions.c \
$(SRCDIR)/ULP-Version-3-parameter-extensionsPrint.c \
$(HFILESDIR)$(PS)ULP-Version-3-parameter-extensions.h \
$(SRCDIR)/SUPL-STARTEnc.c \
$(SRCDIR)/SUPL-STARTDec.c \
$(SRCDIR)/SUPL-START.c \
$(SRCDIR)/SUPL-STARTPrint.c \
$(HFILESDIR)$(PS)SUPL-START.h \
$(SRCDIR)/OMA-LPPEEnc.c \
$(SRCDIR)/OMA-LPPEDec.c \
$(SRCDIR)/OMA-LPPE.c \
$(SRCDIR)/OMA-LPPEPrint.c \
$(HFILESDIR)$(PS)OMA-LPPE.h \
$(SRCDIR)/SUPL-RESPONSEEnc.c \
$(SRCDIR)/SUPL-RESPONSEDec.c \
$(SRCDIR)/SUPL-RESPONSE.c \
$(SRCDIR)/SUPL-RESPONSEPrint.c \
$(HFILESDIR)$(PS)SUPL-RESPONSE.h \
$(SRCDIR)/SUPL-POS-INITEnc.c \
$(SRCDIR)/SUPL-POS-INITDec.c \
$(SRCDIR)/SUPL-POS-INIT.c \
$(SRCDIR)/SUPL-POS-INITPrint.c \
$(HFILESDIR)$(PS)SUPL-POS-INIT.h \
$(SRCDIR)/SUPL-POSEnc.c \
$(SRCDIR)/SUPL-POSDec.c \
$(SRCDIR)/SUPL-POS.c \
$(SRCDIR)/SUPL-POSPrint.c \
$(HFILESDIR)$(PS)SUPL-POS.h \
$(SRCDIR)/SUPL-ENDEnc.c \
$(SRCDIR)/SUPL-ENDDec.c \
$(SRCDIR)/SUPL-END.c \
$(SRCDIR)/SUPL-ENDPrint.c \
$(HFILESDIR)$(PS)SUPL-END.h \
$(SRCDIR)/SUPL-AUTH-REQEnc.c \
$(SRCDIR)/SUPL-AUTH-REQDec.c \
$(SRCDIR)/SUPL-AUTH-REQ.c \
$(SRCDIR)/SUPL-AUTH-REQPrint.c \
$(HFILESDIR)$(PS)SUPL-AUTH-REQ.h \
$(SRCDIR)/SUPL-AUTH-RESPEnc.c \
$(SRCDIR)/SUPL-AUTH-RESPDec.c \
$(SRCDIR)/SUPL-AUTH-RESP.c \
$(SRCDIR)/SUPL-AUTH-RESPPrint.c \
$(HFILESDIR)$(PS)SUPL-AUTH-RESP.h \
$(SRCDIR)/SUPL-TRIGGERED-RESPONSEEnc.c \
$(SRCDIR)/SUPL-TRIGGERED-RESPONSEDec.c \
$(SRCDIR)/SUPL-TRIGGERED-RESPONSE.c \
$(SRCDIR)/SUPL-TRIGGERED-RESPONSEPrint.c \
$(HFILESDIR)$(PS)SUPL-TRIGGERED-RESPONSE.h \
$(SRCDIR)/SUPL-TRIGGERED-STOPEnc.c \
$(SRCDIR)/SUPL-TRIGGERED-STOPDec.c \
$(SRCDIR)/SUPL-TRIGGERED-STOP.c \
$(SRCDIR)/SUPL-TRIGGERED-STOPPrint.c \
$(HFILESDIR)$(PS)SUPL-TRIGGERED-STOP.h \
$(SRCDIR)/SUPL-NOTIFYEnc.c \
$(SRCDIR)/SUPL-NOTIFYDec.c \
$(SRCDIR)/SUPL-NOTIFY.c \
$(SRCDIR)/SUPL-NOTIFYPrint.c \
$(HFILESDIR)$(PS)SUPL-NOTIFY.h \
$(SRCDIR)/SUPL-NOTIFY-RESPONSEEnc.c \
$(SRCDIR)/SUPL-NOTIFY-RESPONSEDec.c \
$(SRCDIR)/SUPL-NOTIFY-RESPONSE.c \
$(SRCDIR)/SUPL-NOTIFY-RESPONSEPrint.c \
$(HFILESDIR)$(PS)SUPL-NOTIFY-RESPONSE.h \
$(SRCDIR)/SUPL-SET-INITEnc.c \
$(SRCDIR)/SUPL-SET-INITDec.c \
$(SRCDIR)/SUPL-SET-INIT.c \
$(SRCDIR)/SUPL-SET-INITPrint.c \
$(HFILESDIR)$(PS)SUPL-SET-INIT.h \
$(SRCDIR)/SUPL-REPORTEnc.c \
$(SRCDIR)/SUPL-REPORTDec.c \
$(SRCDIR)/SUPL-REPORT.c \
$(SRCDIR)/SUPL-REPORTPrint.c \
$(HFILESDIR)$(PS)SUPL-REPORT.h \
$(HFILESDIR)$(PS)rtkey.h \
: ../../../specs/SUPL/v2_1/ULP.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(ASN1C) ../../../specs/SUPL/v2_1/ULP.asn -c -uper -depends -I ../../../specs/SUPL/v2_1 -config ../../../specs/SUPL/v2_1/acconfig.xml -print -trace -fqtvalue -x64

depends: ULP.c SUPL-INIT.c ULP-Components.c \
ULP-Version-2-parameter-extensions.c ULP-Version-2-message-extensions.c \
Ver2-ULP-Components.c SUPL-TRIGGERED-START.c \
ULP-Version-3-message-extensions.c ULP-Version-3-parameter-extensions.c \
SUPL-START.c OMA-LPPE.c SUPL-RESPONSE.c SUPL-POS-INIT.c SUPL-POS.c SUPL-END.c \
SUPL-AUTH-REQ.c SUPL-AUTH-RESP.c SUPL-TRIGGERED-RESPONSE.c \
SUPL-TRIGGERED-STOP.c SUPL-NOTIFY.c SUPL-NOTIFY-RESPONSE.c SUPL-SET-INIT.c \
SUPL-REPORT.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) ULPEnc.c
	$(RM) ULPDec.c
	$(RM) ULP.c
	$(RM) ULPPrint.c
	$(RM) $(HFILESDIR)$(PS)ULP.h 
	$(RM) SUPL-INITEnc.c
	$(RM) SUPL-INITDec.c
	$(RM) SUPL-INIT.c
	$(RM) SUPL-INITPrint.c
	$(RM) $(HFILESDIR)$(PS)SUPL-INIT.h 
	$(RM) ULP-ComponentsEnc.c
	$(RM) ULP-ComponentsDec.c
	$(RM) ULP-Components.c
	$(RM) ULP-ComponentsPrint.c
	$(RM) $(HFILESDIR)$(PS)ULP-Components.h 
	$(RM) ULP-Version-2-parameter-extensionsEnc.c
	$(RM) ULP-Version-2-parameter-extensionsDec.c
	$(RM) ULP-Version-2-parameter-extensions.c
	$(RM) ULP-Version-2-parameter-extensionsPrint.c
	$(RM) $(HFILESDIR)$(PS)ULP-Version-2-parameter-extensions.h 
	$(RM) ULP-Version-2-message-extensionsEnc.c
	$(RM) ULP-Version-2-message-extensionsDec.c
	$(RM) ULP-Version-2-message-extensions.c
	$(RM) ULP-Version-2-message-extensionsPrint.c
	$(RM) $(HFILESDIR)$(PS)ULP-Version-2-message-extensions.h 
	$(RM) Ver2-ULP-ComponentsEnc.c
	$(RM) Ver2-ULP-ComponentsDec.c
	$(RM) Ver2-ULP-Components.c
	$(RM) Ver2-ULP-ComponentsPrint.c
	$(RM) $(HFILESDIR)$(PS)Ver2-ULP-Components.h 
	$(RM) SUPL-TRIGGERED-STARTEnc.c
	$(RM) SUPL-TRIGGERED-STARTDec.c
	$(RM) SUPL-TRIGGERED-START.c
	$(RM) SUPL-TRIGGERED-STARTPrint.c
	$(RM) $(HFILESDIR)$(PS)SUPL-TRIGGERED-START.h 
	$(RM) ULP-Version-3-message-extensionsEnc.c
	$(RM) ULP-Version-3-message-extensionsDec.c
	$(RM) ULP-Version-3-message-extensions.c
	$(RM) ULP-Version-3-message-extensionsPrint.c
	$(RM) $(HFILESDIR)$(PS)ULP-Version-3-message-extensions.h 
	$(RM) ULP-Version-3-parameter-extensionsEnc.c
	$(RM) ULP-Version-3-parameter-extensionsDec.c
	$(RM) ULP-Version-3-parameter-extensions.c
	$(RM) ULP-Version-3-parameter-extensionsPrint.c
	$(RM) $(HFILESDIR)$(PS)ULP-Version-3-parameter-extensions.h 
	$(RM) SUPL-STARTEnc.c
	$(RM) SUPL-STARTDec.c
	$(RM) SUPL-START.c
	$(RM) SUPL-STARTPrint.c
	$(RM) $(HFILESDIR)$(PS)SUPL-START.h 
	$(RM) OMA-LPPEEnc.c
	$(RM) OMA-LPPEDec.c
	$(RM) OMA-LPPE.c
	$(RM) OMA-LPPEPrint.c
	$(RM) $(HFILESDIR)$(PS)OMA-LPPE.h 
	$(RM) SUPL-RESPONSEEnc.c
	$(RM) SUPL-RESPONSEDec.c
	$(RM) SUPL-RESPONSE.c
	$(RM) SUPL-RESPONSEPrint.c
	$(RM) $(HFILESDIR)$(PS)SUPL-RESPONSE.h 
	$(RM) SUPL-POS-INITEnc.c
	$(RM) SUPL-POS-INITDec.c
	$(RM) SUPL-POS-INIT.c
	$(RM) SUPL-POS-INITPrint.c
	$(RM) $(HFILESDIR)$(PS)SUPL-POS-INIT.h 
	$(RM) SUPL-POSEnc.c
	$(RM) SUPL-POSDec.c
	$(RM) SUPL-POS.c
	$(RM) SUPL-POSPrint.c
	$(RM) $(HFILESDIR)$(PS)SUPL-POS.h 
	$(RM) SUPL-ENDEnc.c
	$(RM) SUPL-ENDDec.c
	$(RM) SUPL-END.c
	$(RM) SUPL-ENDPrint.c
	$(RM) $(HFILESDIR)$(PS)SUPL-END.h 
	$(RM) SUPL-AUTH-REQEnc.c
	$(RM) SUPL-AUTH-REQDec.c
	$(RM) SUPL-AUTH-REQ.c
	$(RM) SUPL-AUTH-REQPrint.c
	$(RM) $(HFILESDIR)$(PS)SUPL-AUTH-REQ.h 
	$(RM) SUPL-AUTH-RESPEnc.c
	$(RM) SUPL-AUTH-RESPDec.c
	$(RM) SUPL-AUTH-RESP.c
	$(RM) SUPL-AUTH-RESPPrint.c
	$(RM) $(HFILESDIR)$(PS)SUPL-AUTH-RESP.h 
	$(RM) SUPL-TRIGGERED-RESPONSEEnc.c
	$(RM) SUPL-TRIGGERED-RESPONSEDec.c
	$(RM) SUPL-TRIGGERED-RESPONSE.c
	$(RM) SUPL-TRIGGERED-RESPONSEPrint.c
	$(RM) $(HFILESDIR)$(PS)SUPL-TRIGGERED-RESPONSE.h 
	$(RM) SUPL-TRIGGERED-STOPEnc.c
	$(RM) SUPL-TRIGGERED-STOPDec.c
	$(RM) SUPL-TRIGGERED-STOP.c
	$(RM) SUPL-TRIGGERED-STOPPrint.c
	$(RM) $(HFILESDIR)$(PS)SUPL-TRIGGERED-STOP.h 
	$(RM) SUPL-NOTIFYEnc.c
	$(RM) SUPL-NOTIFYDec.c
	$(RM) SUPL-NOTIFY.c
	$(RM) SUPL-NOTIFYPrint.c
	$(RM) $(HFILESDIR)$(PS)SUPL-NOTIFY.h 
	$(RM) SUPL-NOTIFY-RESPONSEEnc.c
	$(RM) SUPL-NOTIFY-RESPONSEDec.c
	$(RM) SUPL-NOTIFY-RESPONSE.c
	$(RM) SUPL-NOTIFY-RESPONSEPrint.c
	$(RM) $(HFILESDIR)$(PS)SUPL-NOTIFY-RESPONSE.h 
	$(RM) SUPL-SET-INITEnc.c
	$(RM) SUPL-SET-INITDec.c
	$(RM) SUPL-SET-INIT.c
	$(RM) SUPL-SET-INITPrint.c
	$(RM) $(HFILESDIR)$(PS)SUPL-SET-INIT.h 
	$(RM) SUPL-REPORTEnc.c
	$(RM) SUPL-REPORTDec.c
	$(RM) SUPL-REPORT.c
	$(RM) SUPL-REPORTPrint.c
	$(RM) $(HFILESDIR)$(PS)SUPL-REPORT.h 
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) writer$(EXE)
	$(RM) reader$(EXE)
	$(RM) message.dat
	$(RM_MSVC_FILES)
