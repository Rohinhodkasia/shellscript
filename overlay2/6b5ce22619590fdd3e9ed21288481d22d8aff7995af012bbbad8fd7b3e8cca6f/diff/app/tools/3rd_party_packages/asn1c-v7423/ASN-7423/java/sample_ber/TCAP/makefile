.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = MessageType.java

all: $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : tcap.asn
	$(ASN1C) tcap.asn -1990 -ber -java -print -pkgname sample_ber.TCAP

clean:
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~

