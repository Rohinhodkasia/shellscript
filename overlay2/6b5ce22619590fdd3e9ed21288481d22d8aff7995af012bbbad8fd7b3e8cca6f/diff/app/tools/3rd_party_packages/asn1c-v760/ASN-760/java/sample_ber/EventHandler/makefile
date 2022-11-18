.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = PersonnelRecord.java

all: writer.log reader.log

reader.log : Reader.class
	java $(CLASSPATHS) sample_ber.EventHandler.Reader > reader.log

writer.log : Writer.class
	java $(CLASSPATHS) sample_ber.EventHandler.Writer > writer.log

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : employee.asn
	$(ASN1C) employee.asn -ber -java -print -events -pkgname sample_ber.EventHandler

clean:
	$(RM) Date.java
	$(RM) EmployeeNumber.java
	$(RM) Name.java
	$(RM) ChildInformation.java
	$(RM) _SeqOfChildInformation.java
	$(RM) PersonnelRecord.java
	$(RM) *.class
	$(RM) *~
	$(RM) *.log

