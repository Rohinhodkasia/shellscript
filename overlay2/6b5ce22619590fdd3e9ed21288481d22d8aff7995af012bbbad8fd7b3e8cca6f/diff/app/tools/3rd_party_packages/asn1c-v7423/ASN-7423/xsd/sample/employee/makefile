# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

all : employee.xsd
	java -classpath ../../../java/util/Val Val - Employee.xsd

employee.xsd : employee.asn
	$(ASN1C) employee.asn -xsd -pdu "PersonnelRecord"

clean :
	$(RM) *.xsd

