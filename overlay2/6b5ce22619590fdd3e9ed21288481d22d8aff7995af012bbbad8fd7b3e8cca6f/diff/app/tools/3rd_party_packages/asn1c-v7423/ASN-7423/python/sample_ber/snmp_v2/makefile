include ../../../platform.mk
include ../../../sample.mk

ASN1FILES = rfc1905-snmpv2.asn rfc2578-smiv2.asn udpMib.asn
PYFILES = SNMPv2_PDU.py SNMPv2_SMI.py UDP_MIB.py

all : message.dat writer.log reader.log

reader.log : message.dat SNMPv2_PDU.py
	$(PYTHON) reader.py > reader.log

writer.log message.dat : writer.py SNMPv2_PDU.py
	$(PYTHON) writer.py > writer.log

$(PYFILES) : $(ASN1FILES) $(ASN1C) snmpV2.cfg
	$(ASN1C) rfc2578-smiv2.asn -asnstd x208 -ber -python -print
	$(ASN1C) rfc1905-snmpv2.asn -asnstd x208 -ber -python -print \
	   -config snmpV2.cfg 
	$(ASN1C) udpMib.asn -asnstd x208 -ber -python -print \
	   -config snmpV2.cfg -noencode -nodecode

clean:
	$(RM) $(PYFILES)
	$(RM) *~
	$(RM) *.log
