include ../../../platform.mk
include ../../../sample.mk

all : message.dat writer.log reader.log

reader.log : message.dat SetOfInt.py
	$(PYTHON) reader.py > reader.log

writer.log message.dat : writer.py SetOfInt.py
	$(PYTHON) writer.py > writer.log

SetOfInt.py : setOfInt.asn $(ASN1C)
	$(ASN1C) setOfInt.asn -der -python -print

clean:
	$(RM) SetOfInt.py
	$(RM) *~
	$(RM) *.log
