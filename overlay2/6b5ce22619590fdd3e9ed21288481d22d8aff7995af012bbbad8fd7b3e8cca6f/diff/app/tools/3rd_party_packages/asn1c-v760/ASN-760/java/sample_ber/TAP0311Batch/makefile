.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = Notification.java

all: writer.log reader.log

reader.log : Reader.class
	java $(CLASSPATHS) sample_ber.TAP0311Batch.Reader > reader.log

writer.log : Writer.class input.dat
	java $(CLASSPATHS) sample_ber.TAP0311Batch.Writer > writer.log

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : TAP-0311.asn
	$(ASN1C) TAP-0311.asn -ber -java -print -compact -stream -pkgname sample_ber.TAP0311Batch

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

