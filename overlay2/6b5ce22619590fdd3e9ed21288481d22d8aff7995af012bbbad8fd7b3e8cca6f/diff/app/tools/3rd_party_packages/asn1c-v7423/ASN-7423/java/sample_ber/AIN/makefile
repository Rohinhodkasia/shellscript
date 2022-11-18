.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = AINDigits.java

all: $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : ainop.asn
	$(ASN1C) ainop.asn -asnstd x208 -ber -java -print -pkgname sample_ber.AIN

clean:
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~

