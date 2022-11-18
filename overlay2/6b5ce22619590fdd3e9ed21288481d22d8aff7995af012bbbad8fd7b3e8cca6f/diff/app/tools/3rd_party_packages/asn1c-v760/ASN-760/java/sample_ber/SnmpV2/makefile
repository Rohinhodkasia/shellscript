# makefile to build sample program

.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = PDUs.java

all: writer.log reader.log

reader.log : Reader.class
	java $(CLASSPATHS) sample_ber.SnmpV2.Reader > reader.log

writer.log : Writer.class
	java $(CLASSPATHS) sample_ber.SnmpV2.Writer > writer.log

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : rfc2578-smiv2.asn rfc1905-snmpv2.asn udpMib.asn 
	$(ASN1C) rfc2578-smiv2.asn -asnstd x208 -ber -java -print \
	   -pkgname sample_ber.SnmpV2
	$(ASN1C) rfc1905-snmpv2.asn -asnstd x208 -ber -java -print \
	   -pkgname sample_ber.SnmpV2 -config snmpV2.cfg 
	$(ASN1C) udpMib.asn -asnstd x208 -ber -java -print \
	   -pkgname sample_ber.SnmpV2 -config snmpV2.cfg -noencode -nodecode
	javac $(CLASSPATHS) *.java

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java

