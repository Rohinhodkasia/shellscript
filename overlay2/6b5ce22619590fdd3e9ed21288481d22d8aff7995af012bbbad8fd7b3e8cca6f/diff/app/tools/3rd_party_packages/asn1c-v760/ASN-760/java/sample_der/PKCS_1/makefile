.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = _PKCS_1Values.java

all: writer.log reader.log

reader.log : Reader.class
	java $(CLASSPATHS) sample_der.PKCS_1.Reader > reader.log

writer.log : Writer.class
	java $(CLASSPATHS) sample_der.PKCS_1.Writer > writer.log

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : pkcs-1v2.asn
	$(ASN1C) pkcs-1v2.asn -der -java -print -tables -pkgpfx sample_der

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java

