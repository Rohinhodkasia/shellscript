.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = BiometricSyntaxSets.java

XCLASSPATHS = $(CLASSPATHS)$(FS)../../xmlpull/kxml2-2.3.0.tiny.jar

all: message.xml reader.log 

message.xml : Writer.class
	java $(XCLASSPATHS) sample_xer.Biometrics.Writer > writer.log

reader.log : Reader.class message.xml
	java $(XCLASSPATHS) sample_xer.Biometrics.Reader > reader.log

Writer.class Reader.class : Writer.java Reader.java $(JSOURCES)
	javac $(XCLASSPATHS) *.java 

$(JSOURCES) : biometrics.asn
	$(ASN1C) biometrics.asn -xer -xmlpull -java -print -pkgname sample_xer.Biometrics -config xcbf.cfg

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) writer.log 
	$(RM) reader.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java


