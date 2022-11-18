.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = TimesSeq.java

all: writer.log reader.log

reader.log : Reader.class
	java $(CLASSPATHS) sample_ber.TimeString.Reader > reader.log

writer.log : Writer.class
	java $(CLASSPATHS) sample_ber.TimeString.Writer > writer.log

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	javac $(CLASSPATHS) Reader.java Writer.java $(JSOURCES)

$(JSOURCES) : time.asn
	$(ASN1C) time.asn -ber -java -print -pkgpfx sample_ber

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java
	$(RM) *.class
	$(RM) *.log
	$(RM) *~

