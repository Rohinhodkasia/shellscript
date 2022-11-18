# makefile to build sample program

.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = MegacoMessage.java

all: reader_a.log 

reader_a.log : Reader.class 
	java $(CLASSPATHS) sample_per.Megaco.Reader -a > reader_a.log

Reader.class : Reader.java $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : megaco.asn
	$(ASN1C) megaco.asn -per -java -print -pkgname sample_per.Megaco -trace

clean:
	$(MV) Reader.java Reader.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java

