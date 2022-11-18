include ../../../platform.mk
include ../../../sample.mk

all : message.dat message2.json writer.log reader.log

message2.json reader.log : message.dat TAP_0310.py
	$(PYTHON) reader.py > reader.log

writer.log message.dat : writer.py TAP_0310.py message.json
	$(PYTHON) writer.py > writer.log

TAP_0310.py : TAP-0310.asn $(ASN1C)
	$(ASN1C) TAP-0310.asn -ber -json -python -print

clean:
	$(RM) TAP_0310.py
	$(RM) *~
	$(RM) *.log
