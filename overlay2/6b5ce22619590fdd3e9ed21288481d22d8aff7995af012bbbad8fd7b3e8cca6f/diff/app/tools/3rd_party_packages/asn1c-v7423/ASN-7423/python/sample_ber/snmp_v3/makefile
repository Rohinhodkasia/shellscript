include ../../../platform.mk
include ../../../sample.mk

ASN1FILES = SNMPv3.asn
PYFILES = SNMPv3MessageSyntax.py SNMPv2_PDU.py

all : message.dat writer.log reader.log

reader.log : message.dat SNMPv3MessageSyntax.py
	$(PYTHON) reader.py > reader.log

writer.log message.dat : writer.py SNMPv3MessageSyntax.py
	$(PYTHON) writer.py > writer.log

$(PYFILES) : $(ASN1FILES) $(ASN1C)
	$(ASN1C) SNMPv3.asn -asnstd x208 -ber -python -print

clean:
	$(RM) $(PYFILES)
	$(RM) *~
	$(RM) *.log
