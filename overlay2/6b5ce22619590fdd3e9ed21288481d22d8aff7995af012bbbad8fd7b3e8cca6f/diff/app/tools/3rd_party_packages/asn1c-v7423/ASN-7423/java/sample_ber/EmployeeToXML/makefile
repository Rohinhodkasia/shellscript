.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = PersonnelRecord.java

all: reader.log

reader.log : Reader.class message.ber
	java $(CLASSPATHS) sample_ber.EmployeeToXML.Reader > reader.log

Reader.class : Reader.java $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : employee.asn
	$(ASN1C) employee.asn -ber -xml -noxmlns -java -print -compare -pkgname sample_ber.EmployeeToXML

clean:
	$(MV) Reader.java Reader.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java

