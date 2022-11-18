.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = PersonnelRecord.java

all: message.dat writer.log reader.log readeri.log

reader.log : Reader.class message.dat
	java $(CLASSPATHS) sample_ber.Employee.Reader > reader.log

writer.log message.dat : Writer.class
	java $(CLASSPATHS) sample_ber.Employee.Writer > writer.log

# indefinite length test

readeri.log : Reader.class messagei.dat
	java $(CLASSPATHS) sample_ber.Employee.Reader -i messagei.dat > readeri.log

messagei.dat : message.dat ../../../bin/ber2indef$(EXE)
	$(BER2INDEF) message.dat messagei.dat

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : employee.asn
	$(ASN1C) employee.asn -ber -java -print -compare -pkgpfx sample_ber

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java

