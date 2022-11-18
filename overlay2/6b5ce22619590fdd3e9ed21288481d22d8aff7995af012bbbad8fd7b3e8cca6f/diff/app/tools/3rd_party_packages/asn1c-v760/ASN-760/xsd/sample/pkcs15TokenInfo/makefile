# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : PKCS15TokenInfo.xsd
	java -classpath ../../../java/util/Val Val message.xml *.xsd

PKCS15TokenInfo.xsd : PKCS15TokenInfo.asn
	$(ASN1C) PKCS15TokenInfo.asn -xsd -pdu "TokenInfo"

clean :
	$(RM) *.xsd

