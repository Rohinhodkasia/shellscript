# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : Lightweight-Directory-Access-Protocol-V3.xsd
	java -classpath ../../../java/util/Val Val - *.xsd

Lightweight-Directory-Access-Protocol-V3.xsd : ldap.asn
	$(ASN1C) ldap.asn -xsd 

clean :
	$(RM) *.xsd

