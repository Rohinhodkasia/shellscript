# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : ExtChoice.xsd
	java -classpath ../../../java/util/Val Val message.xml *.xsd

ExtChoice.xsd : extChoice.asn
	$(ASN1C) extChoice.asn -xsd -pdu "AliasAddressList"

clean :
	$(RM) *.xsd

