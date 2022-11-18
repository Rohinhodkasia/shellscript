.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = RosePDU.java

all: $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : simple-ROSE.asn
	$(ASN1C) simple-ROSE.asn -ber -java -print -pkgpfx sample_ber

clean:
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
