# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : TAP-0302.xsd
	java -classpath ../../../java/util/Val Val message.xml *.xsd

TAP-0302.xsd : tap3.asn
	$(ASN1C) tap3.asn -xsd -pdu "DataInterChange" -appinfo tags

clean :
	$(RM) *.xsd

