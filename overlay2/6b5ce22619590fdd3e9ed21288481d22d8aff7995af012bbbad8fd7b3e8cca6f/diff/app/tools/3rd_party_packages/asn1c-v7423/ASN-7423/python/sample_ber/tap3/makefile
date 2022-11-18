include ../../../platform.mk
include ../../../sample.mk

all : message.dat writer.log reader.log

reader.log : message.dat TAP_0312.py
	$(PYTHON) reader.py > reader.log

writer.log message.dat : writer.py TAP_0312.py
	$(PYTHON) writer.py > writer.log

TAP_0312.py : ../../../specs/TAP3/TAP-0312.asn $(ASN1C)
	$(ASN1C) ../../../specs/TAP3/TAP-0312.asn -ber -python -print

clean:
	$(RM) TAP_0312.py
	$(RM) *~
	$(RM) *.log
