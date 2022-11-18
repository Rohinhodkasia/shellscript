include ../../../platform.mk
include ../../../sample.mk

PYFILES = \
AlgorithmInformation_2009.py \
PKIX1Explicit_2009.py \
PKIX1Implicit_2009.py \
PKIX1_PSS_OAEP_Algorithms_2009.py \
PKIXAlgs_2009.py \
PKIX_CommonTypes_2009.py \
PKIX_X400Address_2009.py

all : message.dat writer.log reader.log

reader.log : message.dat reader.py $(PYFILES)
	$(PYTHON) reader.py > reader.log

writer.log message.dat : writer.py $(PYFILES)
	$(PYTHON) writer.py > writer.log

$(PYFILES) : $(SPECSDIR)/PKIX/Certificate/PKIX1Explicit-2009.asn $(ASN1C)
	$(ASN1C) $(SPECSDIR)/PKIX/Certificate/PKIX1Explicit-2009.asn -python -der -depends -print -tables -I $(SPECSDIR)/PKIX/Certificate -I $(SPECSDIR)/PKIX/Common -config $(SPECSDIR)/PKIX/Certificate/acconfig.xml -pdu Certificate

clean:
	$(RM) $(PYFILES)
	$(RM) *~
	$(RM) *.log
