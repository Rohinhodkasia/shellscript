.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = Alert.java
XCLASSPATHS = $(CLASSPATHS)$(FS)../../xmlpull/kxml2-2.3.0.tiny.jar

all: message.xml reader.log 

message.xml : Writer.class $(ACJAVAROOT)/asn1rt.jar
	java $(XCLASSPATHS) sample_xml.CAP.Writer > writer.log

reader.log : Reader.class message.xml
	java $(XCLASSPATHS) sample_xml.CAP.Reader > reader.log

Writer.class : Writer.java $(JSOURCES)
	javac $(XCLASSPATHS) *.java

$(JSOURCES) : cap.xsd $(OSROOTDIR)/bin/asn1c$(EXE)
	$(ASN1C) cap.xsd -xml -xmlpull -java -print -pkgname sample_xml.CAP

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java
