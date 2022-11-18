# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : T38.xsd
	java -classpath ../../../java/util/Val Val message.xml *.xsd

T38.xsd : t38.asn
	$(ASN1C) t38.asn -xsd -pdu "UDPTLPacket"

clean :
	$(RM) *.xsd

