include ../../../platform.mk
include ../../../sample.mk

all : reader.log

reader.log : msg05.bin MEDIA_GATEWAY_CONTROL.py
	$(PYTHON) reader.py -i msg05.bin > reader.log

MEDIA_GATEWAY_CONTROL.py : megaco.asn $(ASN1C)
	$(ASN1C) megaco.asn -ber -python -print -compare

clean:
	$(RM) MEDIA_GATEWAY_CONTROL.py
	$(RM) *~
	$(RM) *.log
