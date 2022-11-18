.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = BiometricSyntaxSets.java

XCLASSPATHS = $(CLASSPATHS)

all: message.json reader.log 

message.json : Writer.class
	java $(XCLASSPATHS) sample_json.Biometrics.Writer > writer.log

reader.log : Reader.class message.json
	java $(XCLASSPATHS) sample_json.Biometrics.Reader > reader.log

Writer.class Reader.class : Writer.java Reader.java $(JSOURCES)
	javac $(XCLASSPATHS) *.java 


$(JSOURCES) : biometrics.asn
	$(ASN1C) biometrics.asn -json -java -print -pkgname sample_json.Biometrics -config xcbf.cfg

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


