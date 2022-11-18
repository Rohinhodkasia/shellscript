.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk


JSOURCES = TokenInfo.java
XCLASSPATHS = $(CLASSPATHS)

all: message.json reader.log 

message.json : Writer.class
	java $(XCLASSPATHS) sample_json.PKCS15TokenInfo.Writer > writer.log

reader.log : Reader.class message.json
	java $(XCLASSPATHS) sample_json.PKCS15TokenInfo.Reader > reader.log

Writer.class Reader.class : Writer.java Reader.java $(JSOURCES)
	javac $(XCLASSPATHS) *.java

$(JSOURCES) : PKCS15TokenInfo.asn
	$(ASN1C) PKCS15TokenInfo.asn -json -java -print -pkgpfx sample_json

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java



