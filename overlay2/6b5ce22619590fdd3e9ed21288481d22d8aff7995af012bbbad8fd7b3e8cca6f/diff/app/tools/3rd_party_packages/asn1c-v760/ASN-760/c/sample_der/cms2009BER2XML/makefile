# makefile to build generated files

include ../../platform.mk

SPECSDIR = ../../../specs/CryptoMsgSyntax

# include directories
OSROOTDIR = ..$(PS)..$(PS)..
LIBDIR  = $(OSROOTDIR)$(PS)c$(RTDIRSFX)$(PS)lib
RTSRCDIR = $(OSROOTDIR)$(PS)rtsrc
BERSRCDIR = $(OSROOTDIR)$(PS)rtbersrc
XMLSRCDIR = $(OSROOTDIR)$(PS)rtxmlsrc
SRCDIR = .
HFILESDIR = .
HFILES = $(RTSRCDIR)$(PS)asn1type.h $(BERSRCDIR)$(PS)asn1ber.h  \
$(XMLSRCDIR)$(PS)osrtxml.h 
# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(CBLDTYPE_) -D_TRACE
IPATHS = -I$(SRCDIR) -I$(OSROOTDIR) -I$(SPECSDIR) -I$(RTSRCDIR) \
-I$(BERSRCDIR) -I$(XMLSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

# run-time libraries
LIBS = $(LIBDIR)/$(LIBPFX)asn1ber$(A) $(LIBDIR)/$(LIBPFX)asn1xml$(A) \
$(LIBDIR)/$(LIBPFX)asn1rt$(A)
LLIBS = $(LLPFX)asn1ber$(LLAEXT) $(LLPFX)asn1xml$(LLAEXT) \
$(LLPFX)asn1rt$(LLAEXT) $(LLSYS)
LPATHS = $(LPPFX)$(LIBDIR)

OBJECTS =  \
CMS-AES-CCM-and-AES-GCM-2009$(OBJ) \
CMS-AuthEnvelopedData-2009$(OBJ) \
CMSAesRsaesOaep-2009$(OBJ) \
CMSFirmwareWrapper-2009$(OBJ) \
CryptographicMessageSyntax-2009$(OBJ) \
CryptographicMessageSyntaxAlgorithms-2009$(OBJ) \
ERS$(OBJ) \
ExtendedSecurityServices-2009$(OBJ) \
SecureMimeMessageV3dot1-2009$(OBJ) \
SMIMESymmetricKeyDistribution-2009$(OBJ) \
AlgorithmInformation-2009$(OBJ) \
PKIX1Explicit-2009$(OBJ) \
PKIX1Implicit-2009$(OBJ) \
PKIXAlgs-2009$(OBJ) \
PKIX1-PSS-OAEP-Algorithms-2009$(OBJ) \
PKIX-X400Address-2009$(OBJ) \
AttributeCertificateVersion1-2009$(OBJ) \
PKIXAttributeCertificate-2009$(OBJ)

ENCOBJECTS =  \
CMS-AES-CCM-and-AES-GCM-2009Enc$(OBJ) \
CMS-AuthEnvelopedData-2009Enc$(OBJ) \
CMSAesRsaesOaep-2009Enc$(OBJ) \
CMSFirmwareWrapper-2009Enc$(OBJ) \
CryptographicMessageSyntax-2009Enc$(OBJ) \
CryptographicMessageSyntaxAlgorithms-2009Enc$(OBJ) \
ERSEnc$(OBJ) \
ExtendedSecurityServices-2009Enc$(OBJ) \
SecureMimeMessageV3dot1-2009Enc$(OBJ) \
SMIMESymmetricKeyDistribution-2009Enc$(OBJ) \
AlgorithmInformation-2009Enc$(OBJ) \
PKIX1Explicit-2009Enc$(OBJ) \
PKIX1Implicit-2009Enc$(OBJ) \
PKIXAlgs-2009Enc$(OBJ) \
PKIX1-PSS-OAEP-Algorithms-2009Enc$(OBJ) \
PKIX-X400Address-2009Enc$(OBJ) \
AttributeCertificateVersion1-2009Enc$(OBJ) \
PKIXAttributeCertificate-2009Enc$(OBJ)

DECOBJECTS =  \
CMS-AES-CCM-and-AES-GCM-2009Dec$(OBJ) \
CMS-AuthEnvelopedData-2009Dec$(OBJ) \
CMSAesRsaesOaep-2009Dec$(OBJ) \
CMSFirmwareWrapper-2009Dec$(OBJ) \
CryptographicMessageSyntax-2009Dec$(OBJ) \
CryptographicMessageSyntaxAlgorithms-2009Dec$(OBJ) \
ERSDec$(OBJ) \
ExtendedSecurityServices-2009Dec$(OBJ) \
SecureMimeMessageV3dot1-2009Dec$(OBJ) \
SMIMESymmetricKeyDistribution-2009Dec$(OBJ) \
AlgorithmInformation-2009Dec$(OBJ) \
PKIX1Explicit-2009Dec$(OBJ) \
PKIX1Implicit-2009Dec$(OBJ) \
PKIXAlgs-2009Dec$(OBJ) \
PKIX1-PSS-OAEP-Algorithms-2009Dec$(OBJ) \
PKIX-X400Address-2009Dec$(OBJ) \
AttributeCertificateVersion1-2009Dec$(OBJ) \
PKIXAttributeCertificate-2009Dec$(OBJ)

P2MOBJECTS =  \
CMS-AES-CCM-and-AES-GCM-2009PrtToStrm$(OBJ) \
CMS-AuthEnvelopedData-2009PrtToStrm$(OBJ) \
CMSAesRsaesOaep-2009PrtToStrm$(OBJ) \
CMSFirmwareWrapper-2009PrtToStrm$(OBJ) \
CryptographicMessageSyntax-2009PrtToStrm$(OBJ) \
CryptographicMessageSyntaxAlgorithms-2009PrtToStrm$(OBJ) \
ERSPrtToStrm$(OBJ) \
ExtendedSecurityServices-2009PrtToStrm$(OBJ) \
SecureMimeMessageV3dot1-2009PrtToStrm$(OBJ) \
SMIMESymmetricKeyDistribution-2009PrtToStrm$(OBJ) \
AlgorithmInformation-2009PrtToStrm$(OBJ) \
PKIX1Explicit-2009PrtToStrm$(OBJ) \
PKIX1Implicit-2009PrtToStrm$(OBJ) \
PKIXAlgs-2009PrtToStrm$(OBJ) \
PKIX1-PSS-OAEP-Algorithms-2009PrtToStrm$(OBJ) \
PKIX-X400Address-2009PrtToStrm$(OBJ) \
AttributeCertificateVersion1-2009PrtToStrm$(OBJ) \
PKIXAttributeCertificate-2009PrtToStrm$(OBJ)

all : $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(P2MOBJECTS)  \
writer$(EXE) reader$(EXE)

WRITEROBJ = writer$(OBJ) $(OBJECTS) $(ENCOBJECTS) $(DECOBJECTS) $(P2MOBJECTS)

writer$(EXE) : $(WRITEROBJ) $(LIBS)
	$(LINK) $(WRITEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

READEROBJ = reader$(OBJ) $(OBJECTS) $(DECOBJECTS) $(ENCOBJECTS) \
 $(P2MOBJECTS)

reader$(EXE) : $(READEROBJ) $(LIBS)
	$(LINK) $(READEROBJ) $(LINKOPT) $(LPATHS) $(LLIBS)

RWHFILES = $(HFILESDIR)$(PS)CMS-AES-CCM-and-AES-GCM-2009.h  \
$(HFILESDIR)$(PS)CMS-AuthEnvelopedData-2009.h $(HFILESDIR)$(PS)CMSAesRsaesOaep-2009.h \
$(HFILESDIR)$(PS)CMSFirmwareWrapper-2009.h $(HFILESDIR)$(PS)CryptographicMessageSyntax-2009.h \
$(HFILESDIR)$(PS)CryptographicMessageSyntaxAlgorithms-2009.h $(HFILESDIR)$(PS)ERS.h \
$(HFILESDIR)$(PS)ExtendedSecurityServices-2009.h $(HFILESDIR)$(PS)SecureMimeMessageV3dot1-2009.h \
$(HFILESDIR)$(PS)SMIMESymmetricKeyDistribution-2009.h $(HFILESDIR)$(PS)AlgorithmInformation-2009.h \
$(HFILESDIR)$(PS)PKIX1Explicit-2009.h $(HFILESDIR)$(PS)PKIX1Implicit-2009.h \
$(HFILESDIR)$(PS)PKIXAlgs-2009.h $(HFILESDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009.h \
$(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h $(HFILESDIR)$(PS)PKIX-X400Address-2009.h \
$(HFILESDIR)$(PS)AttributeCertificateVersion1-2009.h $(HFILESDIR)$(PS)PKIXAttributeCertificate-2009.h \
$(HFILESDIR)$(PS)EnrollmentMessageSyntax-2009.h $(HFILESDIR)$(PS)rtkey.h $(HFILES)

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

# .asn -> .c .h rules
$(SRCDIR)/CMS-AES-CCM-and-AES-GCM-2009Enc.c \
$(SRCDIR)/CMS-AES-CCM-and-AES-GCM-2009Dec.c \
$(SRCDIR)/CMS-AES-CCM-and-AES-GCM-2009.c \
$(SRCDIR)/CMS-AES-CCM-and-AES-GCM-2009PrtToStrm.c \
$(HFILESDIR)$(PS)CMS-AES-CCM-and-AES-GCM-2009.h \
$(SRCDIR)/CMS-AuthEnvelopedData-2009Enc.c \
$(SRCDIR)/CMS-AuthEnvelopedData-2009Dec.c \
$(SRCDIR)/CMS-AuthEnvelopedData-2009.c \
$(SRCDIR)/CMS-AuthEnvelopedData-2009PrtToStrm.c \
$(HFILESDIR)$(PS)CMS-AuthEnvelopedData-2009.h \
$(SRCDIR)/CMSAesRsaesOaep-2009Enc.c \
$(SRCDIR)/CMSAesRsaesOaep-2009Dec.c \
$(SRCDIR)/CMSAesRsaesOaep-2009.c \
$(SRCDIR)/CMSAesRsaesOaep-2009PrtToStrm.c \
$(HFILESDIR)$(PS)CMSAesRsaesOaep-2009.h \
$(SRCDIR)/CMSFirmwareWrapper-2009Enc.c \
$(SRCDIR)/CMSFirmwareWrapper-2009Dec.c \
$(SRCDIR)/CMSFirmwareWrapper-2009.c \
$(SRCDIR)/CMSFirmwareWrapper-2009PrtToStrm.c \
$(HFILESDIR)$(PS)CMSFirmwareWrapper-2009.h \
$(SRCDIR)/CryptographicMessageSyntax-2009Enc.c \
$(SRCDIR)/CryptographicMessageSyntax-2009Dec.c \
$(SRCDIR)/CryptographicMessageSyntax-2009.c \
$(SRCDIR)/CryptographicMessageSyntax-2009PrtToStrm.c \
$(HFILESDIR)$(PS)CryptographicMessageSyntax-2009.h \
$(SRCDIR)/CryptographicMessageSyntaxAlgorithms-2009Enc.c \
$(SRCDIR)/CryptographicMessageSyntaxAlgorithms-2009Dec.c \
$(SRCDIR)/CryptographicMessageSyntaxAlgorithms-2009.c \
$(SRCDIR)/CryptographicMessageSyntaxAlgorithms-2009PrtToStrm.c \
$(HFILESDIR)$(PS)CryptographicMessageSyntaxAlgorithms-2009.h \
$(SRCDIR)/ERSEnc.c \
$(SRCDIR)/ERSDec.c \
$(SRCDIR)/ERS.c \
$(SRCDIR)/ERSPrtToStrm.c \
$(HFILESDIR)$(PS)ERS.h \
$(SRCDIR)/ExtendedSecurityServices-2009Enc.c \
$(SRCDIR)/ExtendedSecurityServices-2009Dec.c \
$(SRCDIR)/ExtendedSecurityServices-2009.c \
$(SRCDIR)/ExtendedSecurityServices-2009PrtToStrm.c \
$(HFILESDIR)$(PS)ExtendedSecurityServices-2009.h \
$(SRCDIR)/SecureMimeMessageV3dot1-2009Enc.c \
$(SRCDIR)/SecureMimeMessageV3dot1-2009Dec.c \
$(SRCDIR)/SecureMimeMessageV3dot1-2009.c \
$(SRCDIR)/SecureMimeMessageV3dot1-2009PrtToStrm.c \
$(HFILESDIR)$(PS)SecureMimeMessageV3dot1-2009.h \
$(SRCDIR)/SMIMESymmetricKeyDistribution-2009Enc.c \
$(SRCDIR)/SMIMESymmetricKeyDistribution-2009Dec.c \
$(SRCDIR)/SMIMESymmetricKeyDistribution-2009.c \
$(SRCDIR)/SMIMESymmetricKeyDistribution-2009PrtToStrm.c \
$(HFILESDIR)$(PS)SMIMESymmetricKeyDistribution-2009.h \
$(SRCDIR)/AlgorithmInformation-2009Enc.c \
$(SRCDIR)/AlgorithmInformation-2009Dec.c \
$(SRCDIR)/AlgorithmInformation-2009.c \
$(SRCDIR)/AlgorithmInformation-2009PrtToStrm.c \
$(HFILESDIR)$(PS)AlgorithmInformation-2009.h \
$(SRCDIR)/PKIX1Explicit-2009Enc.c \
$(SRCDIR)/PKIX1Explicit-2009Dec.c \
$(SRCDIR)/PKIX1Explicit-2009.c \
$(SRCDIR)/PKIX1Explicit-2009PrtToStrm.c \
$(HFILESDIR)$(PS)PKIX1Explicit-2009.h \
$(SRCDIR)/PKIX1Implicit-2009Enc.c \
$(SRCDIR)/PKIX1Implicit-2009Dec.c \
$(SRCDIR)/PKIX1Implicit-2009.c \
$(SRCDIR)/PKIX1Implicit-2009PrtToStrm.c \
$(HFILESDIR)$(PS)PKIX1Implicit-2009.h \
$(SRCDIR)/PKIXAlgs-2009Enc.c \
$(SRCDIR)/PKIXAlgs-2009Dec.c \
$(SRCDIR)/PKIXAlgs-2009.c \
$(SRCDIR)/PKIXAlgs-2009PrtToStrm.c \
$(HFILESDIR)$(PS)PKIXAlgs-2009.h \
$(SRCDIR)/PKIX1-PSS-OAEP-Algorithms-2009Enc.c \
$(SRCDIR)/PKIX1-PSS-OAEP-Algorithms-2009Dec.c \
$(SRCDIR)/PKIX1-PSS-OAEP-Algorithms-2009.c \
$(SRCDIR)/PKIX1-PSS-OAEP-Algorithms-2009PrtToStrm.c \
$(HFILESDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009.h \
$(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h \
$(SRCDIR)/PKIX-X400Address-2009Enc.c \
$(SRCDIR)/PKIX-X400Address-2009Dec.c \
$(SRCDIR)/PKIX-X400Address-2009.c \
$(SRCDIR)/PKIX-X400Address-2009PrtToStrm.c \
$(HFILESDIR)$(PS)PKIX-X400Address-2009.h \
$(SRCDIR)/AttributeCertificateVersion1-2009Enc.c \
$(SRCDIR)/AttributeCertificateVersion1-2009Dec.c \
$(SRCDIR)/AttributeCertificateVersion1-2009.c \
$(SRCDIR)/AttributeCertificateVersion1-2009PrtToStrm.c \
$(HFILESDIR)$(PS)AttributeCertificateVersion1-2009.h \
$(SRCDIR)/PKIXAttributeCertificate-2009Enc.c \
$(SRCDIR)/PKIXAttributeCertificate-2009Dec.c \
$(SRCDIR)/PKIXAttributeCertificate-2009.c \
$(SRCDIR)/PKIXAttributeCertificate-2009PrtToStrm.c \
$(HFILESDIR)$(PS)PKIXAttributeCertificate-2009.h \
$(HFILESDIR)$(PS)EnrollmentMessageSyntax-2009.h \
$(HFILESDIR)$(PS)rtkey.h \
: $(SPECSDIR)/acconfig.xml $(SPECSDIR)/CMS-AES-CCM-and-AES-GCM-2009.asn $(SPECSDIR)/CMS-AuthEnvelopedData-2009.asn $(SPECSDIR)/CMSAesRsaesOaep-2009.asn $(SPECSDIR)/CMSFirmwareWrapper-2009.asn $(SPECSDIR)/CryptographicMessageSyntax-2009.asn $(SPECSDIR)/CryptographicMessageSyntaxAlgorithms-2009.asn $(SPECSDIR)/ERS-2009.asn $(SPECSDIR)/ExtendedSecurityServices-2009.asn $(SPECSDIR)/SecureMimeMessageV3dot1-2009.asn $(SPECSDIR)/SMIMESymmetricKeyDistribution-2009.asn $(OSROOTDIR)$(PS)bin$(PS)asn1c$(EXE)
	$(OSROOTDIR)$(PS)bin$(PS)asn1c $(SPECSDIR)/CMS-AES-CCM-and-AES-GCM-2009.asn $(SPECSDIR)/CMS-AuthEnvelopedData-2009.asn $(SPECSDIR)/CMSAesRsaesOaep-2009.asn $(SPECSDIR)/CMSFirmwareWrapper-2009.asn $(SPECSDIR)/CryptographicMessageSyntax-2009.asn $(SPECSDIR)/CryptographicMessageSyntaxAlgorithms-2009.asn $(SPECSDIR)/ERS-2009.asn $(SPECSDIR)/ExtendedSecurityServices-2009.asn $(SPECSDIR)/SecureMimeMessageV3dot1-2009.asn $(SPECSDIR)/SMIMESymmetricKeyDistribution-2009.asn -c -der -xml -config $(SPECSDIR)/acconfig.xml -depends -I $(SPECSDIR) -noindeflen -prttostrm -strict-size -table-unions -trace -fqtvalue -pdu ContentInfo

depends: CMS-AES-CCM-and-AES-GCM-2009.c CMS-AuthEnvelopedData-2009.c \
CMSAesRsaesOaep-2009.c CMSFirmwareWrapper-2009.c \
CryptographicMessageSyntax-2009.c CryptographicMessageSyntaxAlgorithms-2009.c \
ERS.c ExtendedSecurityServices-2009.c SecureMimeMessageV3dot1-2009.c \
SMIMESymmetricKeyDistribution-2009.c AlgorithmInformation-2009.c \
PKIX1Explicit-2009.c PKIX1Implicit-2009.c PKIXAlgs-2009.c \
PKIX1-PSS-OAEP-Algorithms-2009.c PKIX-X400Address-2009.c \
AttributeCertificateVersion1-2009.c PKIXAttributeCertificate-2009.c
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) CMS-AES-CCM-and-AES-GCM-2009Enc.c
	$(RM) CMS-AES-CCM-and-AES-GCM-2009Dec.c
	$(RM) CMS-AES-CCM-and-AES-GCM-2009.c
	$(RM) CMS-AES-CCM-and-AES-GCM-2009PrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)CMS-AES-CCM-and-AES-GCM-2009.h 
	$(RM) CMS-AuthEnvelopedData-2009Enc.c
	$(RM) CMS-AuthEnvelopedData-2009Dec.c
	$(RM) CMS-AuthEnvelopedData-2009.c
	$(RM) CMS-AuthEnvelopedData-2009PrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)CMS-AuthEnvelopedData-2009.h 
	$(RM) CMSAesRsaesOaep-2009Enc.c
	$(RM) CMSAesRsaesOaep-2009Dec.c
	$(RM) CMSAesRsaesOaep-2009.c
	$(RM) CMSAesRsaesOaep-2009PrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)CMSAesRsaesOaep-2009.h 
	$(RM) CMSFirmwareWrapper-2009Enc.c
	$(RM) CMSFirmwareWrapper-2009Dec.c
	$(RM) CMSFirmwareWrapper-2009.c
	$(RM) CMSFirmwareWrapper-2009PrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)CMSFirmwareWrapper-2009.h 
	$(RM) CryptographicMessageSyntax-2009Enc.c
	$(RM) CryptographicMessageSyntax-2009Dec.c
	$(RM) CryptographicMessageSyntax-2009.c
	$(RM) CryptographicMessageSyntax-2009PrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)CryptographicMessageSyntax-2009.h 
	$(RM) CryptographicMessageSyntaxAlgorithms-2009Enc.c
	$(RM) CryptographicMessageSyntaxAlgorithms-2009Dec.c
	$(RM) CryptographicMessageSyntaxAlgorithms-2009.c
	$(RM) CryptographicMessageSyntaxAlgorithms-2009PrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)CryptographicMessageSyntaxAlgorithms-2009.h 
	$(RM) ERSEnc.c
	$(RM) ERSDec.c
	$(RM) ERS.c
	$(RM) ERSPrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)ERS.h 
	$(RM) ExtendedSecurityServices-2009Enc.c
	$(RM) ExtendedSecurityServices-2009Dec.c
	$(RM) ExtendedSecurityServices-2009.c
	$(RM) ExtendedSecurityServices-2009PrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)ExtendedSecurityServices-2009.h 
	$(RM) SecureMimeMessageV3dot1-2009Enc.c
	$(RM) SecureMimeMessageV3dot1-2009Dec.c
	$(RM) SecureMimeMessageV3dot1-2009.c
	$(RM) SecureMimeMessageV3dot1-2009PrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)SecureMimeMessageV3dot1-2009.h 
	$(RM) SMIMESymmetricKeyDistribution-2009Enc.c
	$(RM) SMIMESymmetricKeyDistribution-2009Dec.c
	$(RM) SMIMESymmetricKeyDistribution-2009.c
	$(RM) SMIMESymmetricKeyDistribution-2009PrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)SMIMESymmetricKeyDistribution-2009.h 
	$(RM) AlgorithmInformation-2009Enc.c
	$(RM) AlgorithmInformation-2009Dec.c
	$(RM) AlgorithmInformation-2009.c
	$(RM) AlgorithmInformation-2009PrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)AlgorithmInformation-2009.h 
	$(RM) PKIX1Explicit-2009Enc.c
	$(RM) PKIX1Explicit-2009Dec.c
	$(RM) PKIX1Explicit-2009.c
	$(RM) PKIX1Explicit-2009PrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)PKIX1Explicit-2009.h 
	$(RM) PKIX1Implicit-2009Enc.c
	$(RM) PKIX1Implicit-2009Dec.c
	$(RM) PKIX1Implicit-2009.c
	$(RM) PKIX1Implicit-2009PrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)PKIX1Implicit-2009.h 
	$(RM) PKIXAlgs-2009Enc.c
	$(RM) PKIXAlgs-2009Dec.c
	$(RM) PKIXAlgs-2009.c
	$(RM) PKIXAlgs-2009PrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)PKIXAlgs-2009.h 
	$(RM) PKIX1-PSS-OAEP-Algorithms-2009Enc.c
	$(RM) PKIX1-PSS-OAEP-Algorithms-2009Dec.c
	$(RM) PKIX1-PSS-OAEP-Algorithms-2009.c
	$(RM) PKIX1-PSS-OAEP-Algorithms-2009PrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)PKIX1-PSS-OAEP-Algorithms-2009.h 
	$(RM) $(HFILESDIR)$(PS)PKIX-CommonTypes-2009.h 
	$(RM) PKIX-X400Address-2009Enc.c
	$(RM) PKIX-X400Address-2009Dec.c
	$(RM) PKIX-X400Address-2009.c
	$(RM) PKIX-X400Address-2009PrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)PKIX-X400Address-2009.h 
	$(RM) AttributeCertificateVersion1-2009Enc.c
	$(RM) AttributeCertificateVersion1-2009Dec.c
	$(RM) AttributeCertificateVersion1-2009.c
	$(RM) AttributeCertificateVersion1-2009PrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)AttributeCertificateVersion1-2009.h 
	$(RM) PKIXAttributeCertificate-2009Enc.c
	$(RM) PKIXAttributeCertificate-2009Dec.c
	$(RM) PKIXAttributeCertificate-2009.c
	$(RM) PKIXAttributeCertificate-2009PrtToStrm.c
	$(RM) $(HFILESDIR)$(PS)PKIXAttributeCertificate-2009.h 
	$(RM) $(HFILESDIR)$(PS)EnrollmentMessageSyntax-2009.h
	$(RM) $(HFILESDIR)$(PS)PKIXCRMF-2009.h
	$(RM) $(HFILESDIR)$(PS)rtkey.h 
	$(RM) *$(OBJ)
	$(RM) *~
	$(RM) reader$(EXE)
	$(RM) writer$(EXE)
	$(RM_MSVC_FILES)
	$(RM) message.*

