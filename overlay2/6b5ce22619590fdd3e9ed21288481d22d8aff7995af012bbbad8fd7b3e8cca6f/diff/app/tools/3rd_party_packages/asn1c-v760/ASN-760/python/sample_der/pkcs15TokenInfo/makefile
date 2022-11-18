include ../../../platform.mk
include ../../../sample.mk

all : message.dat writer.log reader.log

reader.log : message.dat PKCS15TokenInfo.py
	$(PYTHON) reader.py > reader.log

writer.log message.dat : writer.py PKCS15TokenInfo.py
	$(PYTHON) writer.py > writer.log

PKCS15TokenInfo.py : PKCS15TokenInfo.asn $(ASN1C)
	$(ASN1C) PKCS15TokenInfo.asn -der -python -print

clean:
	$(RM) PKCS15TokenInfo.py
	$(RM) *~
	$(RM) *.log
