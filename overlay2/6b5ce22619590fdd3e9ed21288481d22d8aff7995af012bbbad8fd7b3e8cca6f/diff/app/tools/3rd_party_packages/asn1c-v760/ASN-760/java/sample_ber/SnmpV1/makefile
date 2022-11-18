# makefile to build sample program

.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = _RFC1213_MIBValues.java

all: writer.log reader.log

reader.log : Reader.class
	java $(CLASSPATHS) sample_ber.SnmpV1.Reader > reader.log

writer.log : Writer.class
	java $(CLASSPATHS) sample_ber.SnmpV1.Writer > writer.log

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : RFC1155-SMI.asn RFC1157-SNMP.asn RFC1213-MIB2.asn 
	$(ASN1C) RFC1155-SMI.asn -1990 -ber -java -print -pkgname sample_ber.SnmpV1
	$(ASN1C) RFC1157-SNMP.asn -1990 -ber -java -print -pkgname sample_ber.SnmpV1
	$(ASN1C) RFC1213-MIB2.asn -1990 -ber -java -print -pkgname sample_ber.SnmpV1

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java

