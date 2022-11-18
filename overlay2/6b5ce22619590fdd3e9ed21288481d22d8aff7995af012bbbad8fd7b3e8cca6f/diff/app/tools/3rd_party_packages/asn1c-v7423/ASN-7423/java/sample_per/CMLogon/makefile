# makefile to build sample program

.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = CMAircraftMessage.java

all: writer_a.log reader_a.log writer_u.log reader_u.log

reader_a.log : Reader.class 
	java $(CLASSPATHS) sample_per.CMLogon.Reader -a > reader_a.log

writer_a.log : Writer.class 
	java $(CLASSPATHS) sample_per.CMLogon.Writer -a > writer_a.log

reader_u.log : Reader.class 
	java $(CLASSPATHS) sample_per.CMLogon.Reader -u > reader_u.log

writer_u.log : Writer.class 
	java $(CLASSPATHS) sample_per.CMLogon.Writer -u > writer_u.log

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : acse-1.asn cm-v1.asn
	$(ASN1C) acse-1.asn -per -java -print -pkgname sample_per.CMLogon -trace
	$(ASN1C) cm-v1.asn -per -java -print -pkgname sample_per.CMLogon -trace

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(RM) *.dmp
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java

