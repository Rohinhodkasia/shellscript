# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : X9-84-Biometrics.xsd
	java -classpath ../../../java/util/Val Val - *.xsd

X9-84-Biometrics.xsd : biometrics.asn
	$(ASN1C) biometrics.asn -xsd -pdu "BiometricSyntax"

clean :
	$(RM) *.xsd

