.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

.java.class:
	javac $(CLASSPATHS) $<

CLASSES = \
Date.class \
EmployeeNumber.class \
Name.class \
ChildInformation.class \
_SeqOfChildInformation.class \
PersonnelRecord.class \
XMLHandler.class

all: $(CLASSES) writer.log reader.log

reader.log : Reader.class
	java $(CLASSPATHS) sample_ber.ToXML.Reader > reader.log

writer.log : Writer.class
	java $(CLASSPATHS) sample_ber.ToXML.Writer > writer.log

ChildInformation.class : ChildInformation.java
_SeqOfChildInformation.class : _SeqOfChildInformation.java
Date.class : Date.java
EmployeeNumber.class : EmployeeNumber.java
Name.class : Name.java
PersonnelRecord.class : PersonnelRecord.java
XMLHandler.class : XMLHandler.java

ChildInformation.java _SeqOfChildInformation.java Date.java \
EmployeeNumber.java Name.java PersonnelRecord.java : employee.asn
	$(ASN1C) employee.asn -ber -java -print -events -pkgname sample_ber.ToXML

clean:
	$(RM) Date.java
	$(RM) EmployeeNumber.java
	$(RM) Name.java
	$(RM) ChildInformation.java
	$(RM) _SeqOfChildInformation.java
	$(RM) PersonnelRecord.java
	$(RM) *.class
	$(RM) *~
	$(RM) writer.log 
	$(RM) reader.log

