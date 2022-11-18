include ../../../platform.mk
include ../../../sample.mk

all : message.dat writer.log reader.log

reader.log : message.dat employee.py
	$(PYTHON) reader.py > reader.log

writer.log message.dat : writer.py employee.py
	$(PYTHON) writer.py > writer.log

employee.py : employee.asn
	$(ASN1C) employee.asn -ber -python -print -compare -stream

clean:
	$(RM) employee.py
	$(RM) *~
	$(RM) *.log
