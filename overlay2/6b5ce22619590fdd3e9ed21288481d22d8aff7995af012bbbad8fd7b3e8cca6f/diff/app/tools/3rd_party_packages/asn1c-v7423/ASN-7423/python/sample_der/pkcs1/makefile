include ../../../platform.mk
include ../../../sample.mk

all : message.dat writer.log reader.log

reader.log : message.dat PKCS_1.py
	$(PYTHON) reader.py > reader.log

writer.log message.dat : writer.py PKCS_1.py
	$(PYTHON) writer.py > writer.log

PKCS_1.py : pkcs-1v2.asn $(ASN1C)
	$(ASN1C) pkcs-1v2.asn -der -python -print -tables

clean:
	$(RM) PKCS_1.py
	$(RM) *~
	$(RM) *.log
