.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = TokenInfo.java
XCLASSPATHS = $(CLASSPATHS)$(FS)../../xmlpull/kxml2-2.3.0.tiny.jar

all: message.xml reader.log 

message.xml : Writer.class
	java $(XCLASSPATHS) sample_xml.PKCS15TokenInfo.Writer > writer.log

reader.log : Reader.class message.xml
	java $(XCLASSPATHS) sample_xml.PKCS15TokenInfo.Reader > reader.log

Writer.class Reader.class : Writer.java Reader.java $(JSOURCES)
	javac $(XCLASSPATHS) *.java

$(JSOURCES) : PKCS15TokenInfo.asn
	$(ASN1C) PKCS15TokenInfo.asn -xml -xmlpull -xsd -java -print -pkgname sample_xml.PKCS15TokenInfo

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) PKCS15TokenInfo.xsd
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java



