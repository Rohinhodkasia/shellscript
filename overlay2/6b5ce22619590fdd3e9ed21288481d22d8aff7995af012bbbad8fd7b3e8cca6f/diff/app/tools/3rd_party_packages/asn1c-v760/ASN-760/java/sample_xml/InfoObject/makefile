# makefile to build sample program

.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = Format.java
XCLASSPATHS = $(CLASSPATHS)$(FS)../../xmlpull/kxml2-2.3.0.tiny.jar

all: writer.log reader.log 

reader.log : Reader.class 
	java $(XCLASSPATHS) sample_xml.InfoObject.Reader > reader.log

writer.log : Writer.class 
	java $(XCLASSPATHS) sample_xml.InfoObject.Writer > writer.log

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	javac $(XCLASSPATHS) *.java

$(JSOURCES) : test.asn
	$(ASN1C) test.asn -xml -xmlpull -java -print -pkgname sample_xml.InfoObject -trace
	$(ASN1C) test.asn -xsd

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) writer*.log 
	$(RM) reader*.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java

