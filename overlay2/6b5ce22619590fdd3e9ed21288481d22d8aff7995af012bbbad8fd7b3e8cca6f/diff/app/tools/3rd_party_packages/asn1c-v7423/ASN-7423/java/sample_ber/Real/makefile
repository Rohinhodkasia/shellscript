.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = PersonnelRecord.java

all: $(CLASSES) writer.log reader.log readeri.log

writer.log message.dat : Writer.class
	java $(CLASSPATHS) sample_ber.Real.Writer > writer.log

reader.log : Reader.class message.dat
	java $(CLASSPATHS) sample_ber.Real.Reader > reader.log

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	javac $(CLASSPATHS) Reader.java Writer.java $(JSOURCES)

# indefinite length test

readeri.log : Reader.class messagei.dat
	java $(CLASSPATHS) sample_ber.Real.Reader -i messagei.dat > readeri.log

messagei.dat : message.dat ../../../bin/ber2indef$(EXE)
	$(BER2INDEF) message.dat messagei.dat

$(JSOURCES) : realTest.asn
	$(ASN1C) realTest.asn -ber -java -print -pkgpfx sample_ber

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java
	$(RM) *.class
	$(RM) *.log
	$(RM) *~

