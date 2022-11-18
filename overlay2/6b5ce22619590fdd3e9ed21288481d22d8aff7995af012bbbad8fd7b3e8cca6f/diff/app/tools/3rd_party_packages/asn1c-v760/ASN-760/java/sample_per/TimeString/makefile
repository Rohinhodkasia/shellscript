.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = TimesSeq.java

all: writer.log reader.log

.java.class:
	javac $(CLASSPATHS) $<

reader.log : Reader.class
	java $(CLASSPATHS) sample_per.TimeString.Reader > reader.log

writer.log : Writer.class
	java $(CLASSPATHS) sample_per.TimeString.Writer > writer.log

Writer.class Reader.class : Writer.java Reader.java $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : time.asn
	$(ASN1C) time.asn -per -java -print -pkgpfx sample_per

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java
	$(RM) *.class
	$(RM) *.log
	$(RM) *~

