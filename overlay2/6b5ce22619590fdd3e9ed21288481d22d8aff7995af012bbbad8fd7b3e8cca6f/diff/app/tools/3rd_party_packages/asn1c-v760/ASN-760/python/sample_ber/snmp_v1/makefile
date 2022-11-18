include ../../../platform.mk
include ../../../sample.mk

ASN1FILES = RFC1155-SMI.asn RFC1157-SNMP.asn RFC1213-MIB2.asn
PYFILES = RFC1155_SMI.py RFC1157_SNMP.py RFC1213_MIB2.py

all : message.dat writer.log reader.log

reader.log : message.dat RFC1157_SNMP.py
	$(PYTHON) reader.py > reader.log

writer.log message.dat : writer.py RFC1157_SNMP.py
	$(PYTHON) writer.py > writer.log

$(PYFILES) : $(ASN1FILES)
	$(ASN1C) $(ASN1FILES) -ber -python -print -asnstd x208

clean:
	$(RM) $(PYFILES)
	$(RM) *~
	$(RM) *.log
