include ../../../platform.mk
include ../../../sample.mk

all : message.dat writer.log reader.log

reader.log : message.dat BigInt.py
	$(PYTHON) reader.py > reader.log

writer.log message.dat : writer.py BigInt.py
	$(PYTHON) writer.py > writer.log

BigInt.py : bigInt.asn $(ASN1C)
	$(ASN1C) bigInt.asn -der -python -print

clean:
	$(RM) BigInt.py
	$(RM) *~
	$(RM) *.log
