include ../../../platform.mk
include ../../../sample.mk

all : message.dat writer.log reader.log

reader.log : message.dat MakeCallArgument.py SimpleROSE.py
	$(PYTHON) reader.py > reader.log

writer.log message.dat : writer.py MakeCallArgument.py SimpleROSE.py
	$(PYTHON) writer.py > writer.log

MakeCallArgument.py : makeCallArgument.asn $(ASN1C)
	$(ASN1C) makeCallArgument.asn -ber -python -print

SimpleROSE.py : simple-ROSE.asn $(ASN1C)
	$(ASN1C) simple-ROSE.asn -ber -python -print

clean:
	$(RM) MakeCallArgument.py
	$(RM) SimpleROSE.py
