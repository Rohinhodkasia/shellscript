.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = TokenInfo.java

all: writer.log reader.log

reader.log : Reader.class
	java $(CLASSPATHS) sample_der.PKCS15TokenInfo.Reader > reader.log

writer.log : Writer.class
	java $(CLASSPATHS) sample_der.PKCS15TokenInfo.Writer > writer.log

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : PKCS15TokenInfo.asn
	$(ASN1C) PKCS15TokenInfo.asn -der -java -print -pkgpfx sample_der

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java

