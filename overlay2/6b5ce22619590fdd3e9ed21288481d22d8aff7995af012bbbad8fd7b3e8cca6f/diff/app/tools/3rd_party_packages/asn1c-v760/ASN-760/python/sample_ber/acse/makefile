include ../../../platform.mk
include ../../../sample.mk

ASN1FILES = ACSE-1.asn InformationFramework.asn UsefulDefinitions.asn
PYFILES = ACSE_1.py Asn1External.py InformationFramework.py UsefulDefinitions.py

all : message.dat writer.log reader.log

reader.log : message.dat ACSE_1.py
	$(PYTHON) reader.py > reader.log

writer.log message.dat : writer.py ACSE_1.py
	$(PYTHON) writer.py > writer.log

$(PYFILES): $(ASN1FILES)
	$(ASN1C) ACSE-1.asn -python -ber -depends -print

clean:
	$(RM) $(PYFILES)
	$(RM) *~
	$(RM) *.log
