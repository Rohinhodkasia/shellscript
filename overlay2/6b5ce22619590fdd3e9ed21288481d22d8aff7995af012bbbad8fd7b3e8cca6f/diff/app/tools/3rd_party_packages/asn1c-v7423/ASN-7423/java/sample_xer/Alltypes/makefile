.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = TestType.java
XCLASSPATHS = $(CLASSPATHS)$(FS)../../xmlpull/kxml2-2.3.0.tiny.jar

all: message.xml reader.log 

message.xml : Writer.class
	java $(XCLASSPATHS) sample_xer.Alltypes.Writer > writer.log

reader.log : Reader.class message.xml
	java $(XCLASSPATHS) sample_xer.Alltypes.Reader > reader.log

Writer.class Reader.class : Writer.java Reader.java $(JSOURCES)
	javac $(XCLASSPATHS) *.java


$(JSOURCES) : test.asn $(ASN1C)
	$(ASN1C) test.asn -xer -java -print -pkgname sample_xer.Alltypes

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java

