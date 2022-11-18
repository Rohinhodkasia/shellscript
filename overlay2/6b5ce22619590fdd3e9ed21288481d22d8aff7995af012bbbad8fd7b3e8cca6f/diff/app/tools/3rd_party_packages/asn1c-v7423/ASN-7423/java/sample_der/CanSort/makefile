.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = SetOfInt.java

all: writer.log reader.log

reader.log : Reader.class
	java $(CLASSPATHS) sample_der.CanSort.Reader > reader.log

writer.log : Writer.class
	java $(CLASSPATHS) sample_der.CanSort.Writer > writer.log

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : setOfInt.asn
	$(ASN1C) setOfInt.asn -java -print -der -pkgname sample_der.CanSort

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java

