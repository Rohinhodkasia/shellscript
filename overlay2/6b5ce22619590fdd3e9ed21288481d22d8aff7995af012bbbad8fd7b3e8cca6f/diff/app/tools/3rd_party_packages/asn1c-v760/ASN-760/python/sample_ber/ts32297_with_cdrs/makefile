include ../../../platform.mk
include ../../../sample.mk

ASN1FILES = IMS-R8-2009-03.asn
PYFILES = IMS_R8_2009_03.py

all : reader.log

reader.log : $(PYFILES)
	$(PYTHON) reader.py > reader.log

$(PYFILES) : $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -ber -python -print

clean:
	$(RM) $(PYFILES)
	$(RM) *~
	$(RM) *.log
