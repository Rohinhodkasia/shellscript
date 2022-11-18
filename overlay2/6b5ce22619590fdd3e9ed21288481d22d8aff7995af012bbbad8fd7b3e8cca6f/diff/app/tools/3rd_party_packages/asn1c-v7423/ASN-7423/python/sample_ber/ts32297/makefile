include ../../../platform.mk
include ../../../sample.mk

ASN1FILES = GPRSChargingDataTypes.asn1 GenericChargingDataTypes.asn1
PYFILES = GPRSChargingDataTypes.py GenericChargingDataTypes.py

all : test2.cdr writer.log reader.log

reader.log : test2.cdr GPRSChargingDataTypes.py
	$(PYTHON) reader.py > reader.log

writer.log test2.cdr : writer.py GPRSChargingDataTypes.py
	$(PYTHON) writer.py > writer.log

$(PYFILES) : $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -ber -python -print

clean:
	$(RM) $(PYFILES)
	$(RM) *~
	$(RM) *.log
