.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = Notification.java
CLASSPATHS2 = $(CLASSPATHS)$(FS)..$(PS)..$(PS)xmlpull$(PS)kxml2-2.3.0.tiny.jar

all: reader.log

reader.log : Reader.class
	java $(CLASSPATHS2) sample_ber.TAP0311OpenType.Reader > reader.log

Reader.class : Reader.java $(JSOURCES)
	javac $(CLASSPATHS2) *.java

$(JSOURCES) : TAP-0311.asn
	$(ASN1C) TAP-0311.asn -ber -java -print -pkgname sample_ber.TAP0311OpenType -config TAP3.cfg -xer

clean:
	$(MV) Reader.java Reader.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) reader.log
	$(MV) Reader.java_save Reader.java

