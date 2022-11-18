.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = MegacoMessage.java

all: reader.log

reader.log : Reader.class
	java $(CLASSPATHS) sample_ber.Megaco.Reader > reader.log

Reader.class : Reader.java $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : megaco.asn
	$(ASN1C) megaco.asn -ber -java -print -pkgname sample_ber.Megaco

clean:
	$(MV) Reader.java Reader.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java


